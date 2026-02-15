import pygame
import pyaudio
import numpy as np
import time
import sys


class MultidimensionalFractalMusic:
    def __init__(self):
        pygame.init()
        self.screen_width, self.screen_height = 800, 600
        self.screen = pygame.display.set_mode((self.screen_width, self.screen_height))
        pygame.display.set_caption('多维分形宇宙音乐生成器')

        self.pa = pyaudio.PyAudio()
        self.sample_rate = 44100
        self.chunk_size = 1024
        self.stream = self.pa.open(format=pyaudio.paFloat32,
                                    channels=1,
                                    rate=self.sample_rate,
                                    output=True,
                                    frames_per_buffer=self.chunk_size)

        self.freq_base = 220
        self.time = 0
        self.playing = True
        self.fractal_type = 0
        self.fractal_params = {
            'mandelbrot': {'c_real': 0.0, 'c_imag': 0.0, 'x_pos': -2.0, 'y_pos': -1.5},
            'julia': {'c_real': -0.7, 'c_imag': 0.27015},
            'burning_ship': {'x_pos': -2.0, 'y_pos': -1.5}
        }

    def mandelbrot(self, x, y, max_iter=100):
        z_real, z_imag = 0, 0
        for i in range(max_iter):
            z_real_sq = z_real * z_real
            z_imag_sq = z_imag * z_imag
            if z_real_sq + z_imag_sq > 4.0:
                return i
            z_imag = 2 * z_real * z_imag + y
            z_real = z_real_sq - z_imag_sq + x
        return max_iter

    def julia(self, x, y, max_iter=100):
        c_real = self.fractal_params['julia']['c_real']
        c_imag = self.fractal_params['julia']['c_imag']
        z_real, z_imag = x, y
        for i in range(max_iter):
            z_real_sq = z_real * z_real
            z_imag_sq = z_imag * z_imag
            if z_real_sq + z_imag_sq > 4.0:
                return i
            z_imag = 2 * z_real * z_imag + c_imag
            z_real = z_real_sq - z_imag_sq + c_real
        return max_iter

    def burning_ship(self, x, y, max_iter=100):
        z_real, z_imag = 0, 0
        for i in range(max_iter):
            z_real_sq = z_real * z_real
            z_imag_sq = z_imag * z_imag
            if z_real_sq + z_imag_sq > 4.0:
                return i
            z_imag = abs(2 * z_real * z_imag) + y
            z_real = abs(z_real_sq - z_imag_sq) + x
        return max_iter

    def generate_fractal_image(self):
        fractal_image = np.zeros((self.screen_height, self.screen_width))
        if self.fractal_type == 0:
            for y in range(self.screen_height):
                for x in range(self.screen_width):
                    ny = self.fractal_params['mandelbrot']['y_pos'] + y / self.screen_height * 3
                    nx = self.fractal_params['mandelbrot']['x_pos'] + x / self.screen_width * 3
                    fractal_image[y, x] = self.mandelbrot(nx, ny)
        elif self.fractal_type == 1:
            for y in range(self.screen_height):
                for x in range(self.screen_width):
                    ny = -1.5 + y / self.screen_height * 3
                    nx = -2.0 + x / self.screen_width * 3
                    fractal_image[y, x] = self.julia(nx, ny)
        elif self.fractal_type == 2:
            for y in range(self.screen_height):
                for x in range(self.screen_width):
                    ny = self.fractal_params['burning_ship']['y_pos'] + y / self.screen_height * 3
                    nx = self.fractal_params['burning_ship']['x_pos'] + x / self.screen_width * 3
                    fractal_image[y, x] = self.burning_ship(nx, ny)
        return fractal_image

    def generate_frame(self, frame_count):
        t = np.arange(self.time, self.time + frame_count / self.sample_rate,
                      1 / self.sample_rate)
        self.time += frame_count / self.sample_rate

        signal = np.zeros(frame_count)
        for i in range(frame_count):
            if self.fractal_type == 0:
                escape = self.mandelbrot(
                    self.fractal_params['mandelbrot']['x_pos'] + 0.01 * np.sin(0.3 * self.time) + (i / frame_count) * 3.0 / 10,
                    self.fractal_params['mandelbrot']['y_pos'] + 0.01 * np.cos(0.2 * self.time))
            elif self.fractal_type == 1:
                escape = self.julia(
                    -2.0 + 0.01 * np.sin(0.3 * self.time) + (i / frame_count) * 3.0 / 10,
                    -1.5 + 0.01 * np.cos(0.2 * self.time))
            elif self.fractal_type == 2:
                escape = self.burning_ship(
                    self.fractal_params['burning_ship']['x_pos'] + 0.01 * np.sin(0.3 * self.time) + (i / frame_count) * 3.0 / 10,
                    self.fractal_params['burning_ship']['y_pos'] + 0.01 * np.cos(0.2 * self.time))

            if escape < 50:
                freq = self.freq_base * (1 + (escape % 12) / 12)
                signal[i] = 0.0
                for harmonic in range(1, 6):
                    amplitude = 0.7 / harmonic
                    phase = 2 * np.pi * freq * harmonic * t[i]
                    signal[i] += amplitude * np.sin(phase)
                envelope = np.exp(-0.001 * (i % 100))
                signal[i] *= envelope

        return signal * 0.3

    def audio_callback(self):
        while self.playing:
            audio = self.generate_frame(self.chunk_size)
            self.stream.write(audio.astype(np.float32).tobytes())

    def run(self):
        print("🎵 多维分形宇宙音乐生成器启动中...")
        print("按 'm' 切换分形类型，按 'q' 退出")

        audio_thread = threading.Thread(target=self.audio_callback)
        audio_thread.start()

        while self.playing:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.playing = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        self.playing = False
                    elif event.key == pygame.K_m:
                        self.fractal_type = (self.fractal_type + 1) % 3

            fractal_image = self.generate_fractal_image()
            pygame.surfarray.blit_array(self.screen, (fractal_image / fractal_image.max() * 255).astype(np.uint8))
            pygame.display.flip()

        self.stream.stop_stream()
        self.stream.close()
        self.pa.terminate()
        pygame.quit()
        sys.exit()


if __name__ == "__main__":
    try:
        import pygame
        import pyaudio
        import numpy as np
    except ImportError:
        print("请先安装依赖: pip install pygame pyaudio numpy")
        sys.exit(1)

    generator = MultidimensionalFractalMusic()
    generator.run()
