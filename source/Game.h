#pragma once

#include "SceneOne.h"
#include "SceneTwo.h"

class Game
{
	std::unique_ptr<SceneManager> scene_manager = nullptr;

public:
	Game()
	{
		InitWindow(800, 450, "Hello Raylib");
		SetTargetFPS(60);

		scene_manager = std::make_unique<SceneManager>();
		scene_manager->add_scene(KEY_ONE, std::make_unique<SceneOneFactory>());
		scene_manager->add_scene(KEY_TWO, std::make_unique<SceneTwoFactory>());
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

			scene->update((float)GetTime(), GetFrameTime());

			BeginDrawing();
			scene->render();
			EndDrawing();
		}
	}

	SceneManager* get_scene_manager() const { return scene_manager.get(); }
};