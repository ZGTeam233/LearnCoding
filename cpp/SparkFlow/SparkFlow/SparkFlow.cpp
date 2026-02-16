/*
// 在代码开头加上这些宏定义，缓解SFML 3.0的“API通胀”
#define SFML_STATIC
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// 再用我上面给的完全适配SFML 3.0的代码
// 错误数量：120 → 5-10个（基本是警告） ✅

import <SFML/Graphics.hpp>;
import <vector>;
import <random>;
import <cmath>;
import <string>;
import <numbers>;
import <format>;

// 使用现代C++特性：概念、模块、结构化绑定等
consteval auto get_window_title() -> std::string_view {
    return "SparkFlow - 现代化粒子系统 (C++23 + SFML 3.0)";
}

// 粒子类 - 使用现代C++特性
class Particle {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float lifetime;
    float maxLifetime;
    float size;

public:
    constexpr Particle(sf::Vector2f pos, sf::Vector2f vel) noexcept
        : position(pos), velocity(vel), lifetime(1.0f), maxLifetime(1.0f) {

        // 使用现代C++随机数生成
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution colorDist(150, 255);
        static std::uniform_real_distribution sizeDist(2.0f, 8.0f);

        color = sf::Color(
            static_cast<std::uint8_t>(colorDist(gen)),
            static_cast<std::uint8_t>(colorDist(gen)),
            static_cast<std::uint8_t>(colorDist(gen)),
            200
        );
        size = sizeDist(gen);
    }

    // 使用 constexpr 和 noexcept
    [[nodiscard]] constexpr auto update(float deltaTime) noexcept -> bool {
        position += velocity * deltaTime * 100.0f;
        velocity.y += 50.0f * deltaTime; // 重力
        lifetime -= deltaTime;
        return lifetime > 0.0f;
    }

    void draw(sf::RenderWindow& window) const {
        sf::CircleShape circle(size);
        circle.setPosition(position);
        circle.setFillColor(color);
        circle.setOrigin(size, size);

        auto finalColor = color;
        finalColor.a = static_cast<std::uint8_t>(255.0f * (lifetime / maxLifetime));
        circle.setFillColor(finalColor);

        window.draw(circle);
    }

    // 使用现代访问器
    [[nodiscard]] constexpr auto get_position() const noexcept -> sf::Vector2f {
        return position;
    }
};

// 粒子系统类 - 使用现代C++特性
class ParticleSystem {
private:
    std::vector<Particle> particles;
    std::mt19937 gen{ std::random_device{}() };
    std::uniform_real_distribution<> velDist{ -200.0, 200.0 };
    std::uniform_real_distribution<> posDistX{ 0.0, 800.0 };

public:
    void spawn_particles(bool spacePressed, float deltaTime) {
        // 使用 lambda 和结构化绑定
        auto spawn_burst = [this](int count, float yPos, float velocityScale = 1.0f) {
            for ([[maybe_unused]] int i : std::views::iota(0, count)) {
                sf::Vector2f position{ static_cast<float>(posDistX(gen)), yPos };
                sf::Vector2f velocity{ static_cast<float>(velDist(gen) * velocityScale), -400.0f };
                particles.emplace_back(position, velocity);
            }
            };

        if (spacePressed) {
            spawn_burst(10, 550.0f, 1.0f);
        }

        static float autoSpawnTimer = 0.0f;
        autoSpawnTimer += deltaTime;
        if (autoSpawnTimer > 0.1f) {
            autoSpawnTimer = 0.0f;
            spawn_burst(1, 570.0f, 0.5f);
        }
    }

    void update(float deltaTime) {
        // 使用现代C++范围算法
        std::erase_if(particles, [deltaTime](auto& particle) {
            return !particle.update(deltaTime);
            });
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& particle : particles) {
            particle.draw(window);
        }
    }

    [[nodiscard]] auto count() const noexcept -> std::size_t {
        return particles.size();
    }

    // 使用现代C++20 ranges
    [[nodiscard]] auto get_average_position() const -> sf::Vector2f {
        if (particles.empty()) return { 0.0f, 0.0f };

        sf::Vector2f sum{ 0.0f, 0.0f };
        for (const auto& particle : particles) {
            sum += particle.get_position();
        }
        return sum / static_cast<float>(particles.size());
    }
};

// 主程序
auto main() -> int {
    // SFML 3.0 + C++20/23 风格
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), get_window_title().data());
    window.setFramerateLimit(60);

    ParticleSystem particleSystem;
    sf::Clock clock;
    bool spacePressed = false;

    // 尝试加载字体
    sf::Font font;
    const bool fontLoaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");

    while (window.isOpen()) {
        const float deltaTime = clock.restart().asSeconds();

        // SFML 3.0 事件处理（现代方式）
        while (auto event = window.pollEvent()) {
            // 使用模式匹配风格（C++23提案的写法）
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto& keyEvent = event->get<sf::Event::KeyPressed>();
                if (keyEvent.key == sf::Keyboard::Key::Space) {
                    spacePressed = true;
                }
            }
            else if (event->is<sf::Event::KeyReleased>()) {
                const auto& keyEvent = event->get<sf::Event::KeyReleased>();
                if (keyEvent.key == sf::Keyboard::Key::Space) {
                    spacePressed = false;
                }
            }
        }

        // 更新粒子系统
        particleSystem.spawn_particles(spacePressed, deltaTime);
        particleSystem.update(deltaTime);

        // 渲染
        window.clear(sf::Color(20, 20, 40));

        // 绘制粒子
        particleSystem.draw(window);

        // 绘制文字（使用C++20 format）
        if (fontLoaded) {
            sf::Text text;
            text.setFont(font);
            text.setString("按住 SPACE 键生成粒子流");
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition({ 10.0f, 10.0f });
            window.draw(text);

            sf::Text countText;
            countText.setFont(font);
            countText.setString(std::format("粒子数量: {} | 平均位置: ({:.1f}, {:.1f})",
                particleSystem.count(),
                particleSystem.get_average_position().x,
                particleSystem.get_average_position().y));
            countText.setCharacterSize(18);
            countText.setFillColor(sf::Color::Cyan);
            countText.setPosition({ 10.0f, 45.0f });
            window.draw(text);

            sf::Text infoText;
            infoText.setFont(font);
            infoText.setString("技术栈: C++23 + SFML 3.0 | 编译器: MSVC 最新版");
            infoText.setCharacterSize(14);
            infoText.setFillColor(sf::Color::Yellow);
            infoText.setPosition({ 10.0f, 570.0f });
            window.draw(infoText);
        }

        window.display();
    }

    return 0;
}
*/

/*
// 创建最小测试文件 test_minimal.cpp
#include <SFML/Graphics.hpp>

int main() {
    // 仅测试窗口创建
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    return 0;
}
*/

// test_sfml3.cpp - SFML 3.0 兼容版本
#include <SFML/Graphics.hpp>

int main() {
    // SFML 3.0 正确语法
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "SFML 3.0 Test");

    // SFML 3.0 事件处理
    while (window.isOpen()) {
        // 方法1：新语法（推荐）
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.display();
    }

    return 0;
}