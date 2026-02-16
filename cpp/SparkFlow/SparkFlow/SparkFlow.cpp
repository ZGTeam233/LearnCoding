#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>
#include <string>

// 粒子类定义
class Particle {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float lifetime;
    float maxLifetime;
    float size;

public:
    Particle(sf::Vector2f pos, sf::Vector2f vel)
        : position(pos), velocity(vel), lifetime(1.0f), maxLifetime(1.0f) {

        // 随机颜色和大小
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> colorDist(150, 255);
        static std::uniform_real_distribution<> sizeDist(2.0f, 8.0f);

        color = sf::Color(
            static_cast<sf::Uint8>(colorDist(gen)),
            static_cast<sf::Uint8>(colorDist(gen)),
            static_cast<sf::Uint8>(colorDist(gen)),
            200
        );
        size = sizeDist(gen);
    }

    bool update(float deltaTime) {
        position += velocity * deltaTime * 100.0f;
        velocity.y += 50.0f * deltaTime; // 重力效果
        lifetime -= deltaTime;

        return lifetime > 0;
    }

    void draw(sf::RenderWindow& window) const {
        sf::CircleShape circle(size);
        circle.setPosition(position);
        circle.setFillColor(color);
        circle.setOrigin(size, size); // 中心点对齐

        // 根据生命周期设置透明度
        sf::Color finalColor = color;
        finalColor.a = static_cast<sf::Uint8>(255 * (lifetime / maxLifetime));
        circle.setFillColor(finalColor);

        window.draw(circle);
    }
};

int main() {
    // SFML 3.0: VideoMode参数变化
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "粒子系统演示 - 按空格键生成粒子");
    window.setFramerateLimit(60);

    // 粒子容器
    std::vector<Particle> particles;

    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> velDist(-200.0f, 200.0f);
    std::uniform_real_distribution<> posDistX(0.0f, 800.0f);

    sf::Clock clock;
    bool spacePressed = false;

    // 主循环
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // 事件处理
        sf::Event event;
        while (window.pollEvent(event)) {
            // SFML 3.0: Event::Closed -> Event::Closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // SFML 3.0: 使用枚举类
            if (event.type == sf::Event::KeyPressed) {
                // SFML 3.0: Keyboard::Space -> Keyboard::Key::Space
                if (event.key.code == sf::Keyboard::Key::Space) {
                    spacePressed = true;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Key::Space) {
                    spacePressed = false;
                }
            }
        }

        // 生成新粒子
        if (spacePressed) {
            for (int i = 0; i < 10; ++i) {
                sf::Vector2f position(posDistX(gen), 550.0f);
                sf::Vector2f velocity(velDist(gen), -400.0f);
                particles.emplace_back(position, velocity);
            }
        }

        // 自动生成一些粒子
        static float autoSpawnTimer = 0.0f;
        autoSpawnTimer += deltaTime;
        if (autoSpawnTimer > 0.1f) {
            autoSpawnTimer = 0.0f;
            sf::Vector2f position(posDistX(gen), 570.0f);
            sf::Vector2f velocity(velDist(gen) * 0.5f, -300.0f);
            particles.emplace_back(position, velocity);
        }

        // 更新粒子
        for (auto it = particles.begin(); it != particles.end();) {
            if (!it->update(deltaTime)) {
                it = particles.erase(it);
            }
            else {
                ++it;
            }
        }

        // 渲染
        window.clear(sf::Color(20, 20, 40)); // 深蓝色背景

        // 绘制说明文字
        sf::Font font;
        if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            // SFML 3.0: Text构造函数参数变化
            sf::Text text;
            text.setString("按住空格键生成更多粒子");
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
            // SFML 3.0: setPosition需要Vector2f
            text.setPosition(sf::Vector2f(10.f, 10.f));
            window.draw(text);

            // 显示粒子数量
            sf::Text countText;
            countText.setString("粒子数量: " + std::to_string(particles.size()));
            countText.setFont(font);
            countText.setCharacterSize(18);
            countText.setFillColor(sf::Color::Green);
            countText.setPosition(sf::Vector2f(10.f, 40.f));
            window.draw(countText);
        }

        // 绘制粒子
        for (const auto& particle : particles) {
            particle.draw(window);
        }

        window.display();
    }

    return 0;
}