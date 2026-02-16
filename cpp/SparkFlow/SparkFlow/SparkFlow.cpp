#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <optional>  // 添加这个头文件

// 粒子类保持不变
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

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> colorDist(150, 255);
        static std::uniform_real_distribution<> sizeDist(2.0f, 8.0f);

        color = sf::Color(
            static_cast<std::uint8_t>(colorDist(gen)),
            static_cast<std::uint8_t>(colorDist(gen)),
            static_cast<std::uint8_t>(colorDist(gen)),
            200
        );
        size = sizeDist(gen);
    }

    bool update(float deltaTime) {
        position += velocity * deltaTime * 100.0f;
        velocity.y += 50.0f * deltaTime;
        lifetime -= deltaTime;
        return lifetime > 0;
    }

    void draw(sf::RenderWindow& window) const {
        sf::CircleShape circle(size);
        circle.setPosition(position);
        circle.setFillColor(color);
        circle.setOrigin(sf::Vector2f{ size, size });

        sf::Color finalColor = color;
        finalColor.a = static_cast<std::uint8_t>(255 * (lifetime / maxLifetime));
        circle.setFillColor(finalColor);

        window.draw(circle);
    }
};

int main() {
    // 创建窗口（SFML 3.0语法）
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "SparkFlow - 粒子系统");
    window.setFramerateLimit(60);

    // 粒子容器和随机数生成器
    std::vector<Particle> particles;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> velDist(-200.0f, 200.0f);
    std::uniform_real_distribution<> posDistX(0.0f, 800.0f);

    sf::Clock clock;
    bool spacePressed = false;

    // 主循环
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // ===================== 修正点1：SFML 3.0 事件处理 =====================
        while (std::optional<sf::Event> event = window.pollEvent()) {
            // 检查是否为关闭事件
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // 检查是否为按键按下事件
            else if (event->is<sf::Event::KeyPressed>()) {
                // 获取KeyPressed事件数据
                const auto& keyEvent = event->get<sf::Event::KeyPressed>();
                if (keyEvent.key == sf::Keyboard::Key::Space) {
                    spacePressed = true;
                }
            }
            // 检查是否为按键释放事件
            else if (event->is<sf::Event::KeyReleased>()) {
                const auto& keyEvent = event->get<sf::Event::KeyReleased>();
                if (keyEvent.key == sf::Keyboard::Key::Space) {
                    spacePressed = false;
                }
            }
        }

        // 粒子生成逻辑（保持不变）
        if (spacePressed) {
            for (int i = 0; i < 10; ++i) {
                sf::Vector2f position{ posDistX(gen), 550.0f };
                sf::Vector2f velocity{ velDist(gen), -400.0f };
                particles.emplace_back(position, velocity);
            }
        }

        static float autoSpawnTimer = 0.0f;
        autoSpawnTimer += deltaTime;
        if (autoSpawnTimer > 0.1f) {
            autoSpawnTimer = 0.0f;
            sf::Vector2f position{ posDistX(gen), 570.0f };
            sf::Vector2f velocity{ velDist(gen) * 0.5f, -300.0f };
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
        window.clear(sf::Color(20, 20, 40));

        // 绘制粒子
        for (const auto& particle : particles) {
            particle.draw(window);
        }

        // ===================== 修正点2：SFML 3.0 Text 创建 =====================
        // 尝试加载字体
        sf::Font font;
        if (font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
            // SFML 3.0 创建Text的正确方式
            // 1. 先创建Text对象，传入空字符串和字体
            sf::Text text("", font, 20);
            // 2. 然后设置字符串内容
            text.setString("按住空格键生成更多粒子");
            text.setFillColor(sf::Color::White);
            text.setPosition(sf::Vector2f{ 10.f, 10.f });
            window.draw(text);

            // 同样的方式创建第二个文本
            sf::Text countText("", font, 18);
            countText.setString("粒子数量: " + std::to_string(particles.size()));
            countText.setFillColor(sf::Color::Green);
            countText.setPosition(sf::Vector2f{ 10.f, 40.f });
            window.draw(countText);
        }
        // 如果字体加载失败，程序仍然可以运行，只是没有文字显示
        else {
            // 可选：输出调试信息
            // std::cout << "无法加载字体" << std::endl;
        }

        window.display();
    }

    return 0;
}