#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct Weapon {
	std::string id;
	std::string name;
	int damage = 0;
	int manaCost = 0;
	int staminaCost = 0;

	bool operator==(const Weapon&) const = default;
};

inline void to_json(nlohmann::json& j, const Weapon& w) {
	j = { { "id", w.id },{ "name", w.name },
		  { "damage", w.damage },{ "manaCost", w.manaCost },
		  { "staminaCost", w.staminaCost } };
}

inline void from_json(const nlohmann::json& j, Weapon& w) {
	j.at("id").get_to(w.id);
	j.at("name").get_to(w.name);
	j.at("damage").get_to(w.damage);
	j.at("manaCost").get_to(w.manaCost);
	j.at("staminaCost").get_to(w.staminaCost);
}