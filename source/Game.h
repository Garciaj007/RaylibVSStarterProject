#pragma once

#include "SceneOne.h"
#include "SceneTwo.h"
#include "SceneThree.h"

extern std::string_view PROJECT_NAME = "Hello Raylib";
extern float PPM = 10.0f; // Pixel Per Meter
extern int WIDTH = 800;
extern int HEIGHT = 450;

class Game
{
	std::unique_ptr<SceneManager> scene_manager = nullptr;

public:
	Game()
	{
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		InitWindow(WIDTH, HEIGHT, PROJECT_NAME.data());
		SetTargetFPS(60);

		scene_manager = std::make_unique<SceneManager>();
		scene_manager->add_scene(KEY_ONE, std::make_unique<SceneOneFactory>());
		scene_manager->add_scene(KEY_TWO, std::make_unique<SceneTwoFactory>());
		scene_manager->add_scene(KEY_THREE, std::make_unique<SceneThreeFactory>());
	}

	~Game()
	{
		CloseWindow();
	}

	void run()
	{
		const auto manager = get_scene_manager();
		while (!WindowShouldClose())
		{
			manager->update();

			const auto scene = manager->get_current_scene();

			if (IsWindowResized())
				scene->resize(GetScreenWidth(), GetScreenHeight());

			scene->update((float)GetTime(), GetFrameTime());

			BeginDrawing();
			scene->render();
			EndDrawing();
		}
	}

	SceneManager* get_scene_manager() const { return scene_manager.get(); }
};