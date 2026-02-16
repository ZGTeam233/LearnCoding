#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>
#include "spark_flow.h"

int spark_flow() {
    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "粒子系统演示 - 按空格键生成粒子");
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
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    spacePressed = true;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
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
        if (font.loadFromFile("arial.ttf")) {
            sf::Text text("按住空格键生成更多粒子", font, 20);
            text.setFillColor(sf::Color::White);
            text.setPosition(10, 10);
            window.draw(text);
        }

        // 绘制粒子
        for (const auto& particle : particles) {
            particle.draw(window);
        }

        // 显示粒子数量
        if (font.loadFromFile("arial.ttf")) {
            sf::Text countText("粒子数量: " + std::to_string(particles.size()), font, 18);
            countText.setFillColor(sf::Color::Green);
            countText.setPosition(10, 40);
            window.draw(countText);
        }

        window.display();
    }

    return 0;
}