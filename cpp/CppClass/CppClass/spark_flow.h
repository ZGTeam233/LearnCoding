#ifndef SPARK_FLOW_H
#define SPARK_FLOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>

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

        color = sf::Color(colorDist(gen), colorDist(gen), colorDist(gen), 200);
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

int spark_flow();

#endif // SPARK_FLOW_H
