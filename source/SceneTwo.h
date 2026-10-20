#pragma once

#include "Scene.h"

class SceneTwo : public Scene
{
public:
	SceneTwo() = default;
	~SceneTwo() = default;

	std::string_view get_name() const override { return "Scene Two"; }

	void start() override {}
	void resize(int width, int height) override {}
	void update(float time, float dt) override {}
	void render() override
	{
		ClearBackground(LIGHTGRAY);
		DrawText(get_name().data(), 10, 10, 20, BLACK);
	}
};


struct SceneTwoFactory : public SceneFactory
{
	std::unique_ptr<Scene> create() override { return std::make_unique<SceneTwo>(); }
};