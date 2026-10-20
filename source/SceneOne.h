#pragma once

#include "Scene.h"

class SceneOne : public Scene
{
public:
	SceneOne() = default;
	~SceneOne() = default;

	std::string_view get_name() const override { return "Scene One"; }

	void start() override {}
	void resize(int width, int height) override {}
	void update(float time, float dt) override {}
	void render() override
	{
		ClearBackground(DARKGRAY);
		DrawText(get_name().data(), 10, 10, 20, WHITE);
	}
};

struct SceneOneFactory : public SceneFactory
{
	std::unique_ptr<Scene> create() override { return std::make_unique<SceneOne>(); }
};