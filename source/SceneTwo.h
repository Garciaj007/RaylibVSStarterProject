#pragma once

#include <iostream>

#include "Scene.h"
#include "Repository.h"
#include "Consumable.h"
#include "Weapon.h"

using Consumables = Repository<Consumable>;
using Weapons = Repository<Weapon>;

class SceneTwo : public Scene
{
	std::unique_ptr<Consumables> consumables = nullptr;
	std::unique_ptr<Weapons> weapons = nullptr;

public:
	SceneTwo()
	{
		consumables = std::make_unique<Consumables>("data/consumables.json");
		weapons = std::make_unique<Weapons>("data/weapons.json");

		if (consumables->count() > 0) {
			printf("\nFound %zu consumables->", consumables->count());
			for (const auto& [id, c] : *consumables)
				std::cout << nlohmann::json(c).dump(4) << "\n";
		}

		if (weapons->count() > 0) {
			printf("\nFound %zu weapons->", weapons->count());
			for (const auto& [id, w] : *weapons)
				std::cout << nlohmann::json(w).dump(4) << "\n";
		}

		consumables->upsert({ "HealthPotion", 10, 20, 0 });
		consumables->upsert({ "ManaPotion",    0, 20, 0 });
		consumables->upsert({ "StaminaPotion", 0,  0, 30 });

		weapons->upsert({ "manaSword", "Mana Sword", 5, 0, 1 });
		weapons->upsert({ "staminaSword", "Stamina Sword", 5, 5, 0 });
		weapons->upsert({ "ultimateSword", "Ultimate Sword", 20, 10, 5 });
	}

	~SceneTwo() {}

	std::string_view get_name() const override { return "Scene Two"; }

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