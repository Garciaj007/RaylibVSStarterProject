#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct Consumable {
	std::string id;
	int healthGain = 0;
	int manaGain = 0;
	int staminaGain = 0;

	bool operator==(const Consumable&) const = default;
};

inline void to_json(nlohmann::json& j, const Consumable& c) {
	j = { { "id", c.id },{ "healthGain", c.healthGain },
		  { "manaGain", c.manaGain },{ "staminaGain", c.staminaGain } };
}
inline void from_json(const nlohmann::json& j, Consumable& c) {
	j.at("id").get_to(c.id);
	j.at("healthGain").get_to(c.healthGain);
	j.at("manaGain").get_to(c.manaGain);
	j.at("staminaGain").get_to(c.staminaGain);
}