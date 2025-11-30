#include "Scene.hpp"
#include "raylib.h"

int screenWidth  = 1280;
int screenHeight = 900;

struct Position final : secs::Component
{
    Position(const int x, const int y) : x(x), y(y) { }

    int x, y;
};

struct Velocity final : secs::Component
{
    Velocity(const float vx, const float vy) : vx(vx), vy(vy) { }

    float vx, vy;
};

struct RGBA final : secs::Component
{
    RGBA(const uint8_t r, const uint8_t g, const uint8_t b) : color(r, g, b, 255) { }

    Color color;
};

class RenderUpdateSystem final : public secs::System
{
public:
    void onUpdate(float delta, secs::Scene& scene) override
    {
        for (const auto e: scene.getWith<Velocity, Position>()) {
            auto& vel = scene.get<Velocity>(e);
            auto& pos = scene.get<Position>(e);

            if (pos.x <= 0 || pos.x >= screenWidth) {
                vel.vx = -vel.vx;
            }

            if (pos.y <= 0 || pos.y >= screenHeight) {
                vel.vy = -vel.vy;
            }

            pos.x += vel.vx * delta * 60;
            pos.y += vel.vy * delta * 60;
        }
    }

    void onRender(secs::Scene& scene) override
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        for (const auto e: scene.getWith<RGBA, Position>()) {
            const auto& rgba = scene.get<RGBA>(e);
            const auto& pos = scene.get<Position>(e);

            DrawCircle(pos.x, pos.y, 3, rgba.color);
        }

        const std::string fpsText = "FPS: " + std::to_string(GetFPS());
        DrawText(fpsText.c_str(), 10, 10, 28, WHITE);
        const std::string deltaText = "FrameTime: " + std::to_string(GetFrameTime());
        DrawText(deltaText.c_str(), 10, 40, 28, WHITE);

        EndDrawing();
    }
};

int main()
{
    secs::Scene scene{ };
    scene.start<RenderUpdateSystem>(secs::SystemPhase::RENDER_PHASE);

    for (int i = 0; i < 1000; i++) {
        const auto e = scene.create();
        scene.emplace<Position>(
            e,
            std::rand() % screenWidth,
            std::rand() % screenHeight
        );
        scene.emplace<Velocity>(
            e,
            static_cast<float>(std::rand() % 25) + 25,
            static_cast<float>(std::rand() % 25) + 25
        );
        scene.emplace<RGBA>(
            e,
            static_cast<uint8_t>(std::rand() % 255),
            static_cast<uint8_t>(std::rand() % 255),
            static_cast<uint8_t>(std::rand() % 255)
        );
    }

    InitWindow(screenWidth, screenHeight, "stress test");
    SetTargetFPS(0);

    while (!WindowShouldClose()) {
        scene.onUpdate(GetFrameTime());
        scene.onRender();
    }

    CloseWindow();
}
