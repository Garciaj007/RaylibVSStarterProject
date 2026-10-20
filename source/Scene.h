#pragma once

#include <string_view>
#include <raylib.h>
#include <memory>
#include <unordered_map>
#include <vector>

extern std::string_view PROJECT_NAME;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual std::string_view get_name() const = 0;

	virtual void start() = 0;
	virtual void resize(int width, int height) = 0;
	virtual void update(float time, float dt) = 0;
	virtual void render() = 0;
};

class SceneFactory
{
public:
	virtual ~SceneFactory() = default;
	virtual std::unique_ptr<Scene> create() = 0;
};

class SceneManager
{
	KeyboardKey current_key = KEY_NULL;
	std::unique_ptr<Scene> current_scene = nullptr;
	std::unordered_map<KeyboardKey, std::unique_ptr<SceneFactory>> scene_factories_by_key;
	std::vector<KeyboardKey> keys;

public:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	Scene* get_current_scene() const { return current_scene.get(); }

	void update()
	{
		for (const auto& key : keys)
		{
			if (IsKeyReleased(key))
				swap_scene(key);
		}
	}

	void add_scene(KeyboardKey key, std::unique_ptr<SceneFactory> factory)
	{
		keys.push_back(key);
		scene_factories_by_key.emplace(key, std::move(factory));
		if (current_key == KEY_NULL) swap_scene(key);
	}

	void swap_scene(KeyboardKey key)
	{
		if (key == current_key) return;

		auto it = scene_factories_by_key.find(key);
		if (it != scene_factories_by_key.end())
		{
			current_key = key;
			current_scene = std::unique_ptr<Scene>(it->second->create());
			current_scene->start();
			current_scene->resize(GetScreenWidth(), GetScreenHeight());
			SetWindowTitle(TextFormat("%s - %s", PROJECT_NAME.data(), current_scene->get_name().data()));
		}
	}
};