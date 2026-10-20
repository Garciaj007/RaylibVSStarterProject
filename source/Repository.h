#pragma once

#include <raylib.h>
#include <unordered_map>
#include <optional>
#include <string>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

bool ensure_directory_exists(const std::string& path) {
	try {
		fs::path dir_path = fs::path(path).parent_path();
		if (!dir_path.empty() && !fs::exists(dir_path)) {
			fs::create_directories(dir_path);
			TraceLog(LOG_INFO, "Created directory: %s", dir_path.string().c_str());
		}
		return true;
	}
	catch (const fs::filesystem_error& e) {
		TraceLog(LOG_ERROR, "Failed to create directory for path %s: %s", path.c_str(), e.what());
		return false;
	}
}

template<typename T>
class Repository {
	static constexpr std::string_view ITEMS_KEY = "items";
	static constexpr std::string_view ID_KEY = "id";

	std::string path;
	std::unordered_map<std::string, T> items;
	bool autoSave;

public:
	explicit Repository(std::string path, bool auto_save = true)
		: path(std::move(path)), autoSave(auto_save) {
		load();
	}

	~Repository() {
		if (autoSave) save();
	}

	Repository(const Repository&) = delete;
	Repository& operator=(const Repository&) = delete;

	void load() {
		items.clear();

		if (!fs::exists(path))
		{
			TraceLog(LOG_INFO, "Repository::Load() - File does not exist: %s", path.c_str());
			return;
		}

		std::ifstream in(path);
		if (!in)
		{
			TraceLog(LOG_WARNING, "Repository::Load() - Failed to open file: %s", path.c_str());
			return;
		}

		nlohmann::json j;
		try {
			in >> j;
		}
		catch (const nlohmann::json::parse_error& e) {
			TraceLog(LOG_WARNING, "Repository::Load() - JSON parse error in file %s: %s", path.c_str(), e.what());
			return;
		}


		for (const auto& v : j.at(ITEMS_KEY))
			items.emplace(v.at(ID_KEY).template get<std::string>(), v.template get<T>());
	}

	void save() const {
		if (!ensure_directory_exists(path)) return;

		nlohmann::json j;
		j[ITEMS_KEY] = nlohmann::json::array();
		for (const auto& [id, item] : items)
			j[ITEMS_KEY].push_back(item);

		std::ofstream out(path);
		if (!out) {
			TraceLog(LOG_WARNING, "Repository::Save() - Failed to open file for writing: %s", path.c_str());
			return;
		}

		out << j.dump(2);
		if (!out) {
			TraceLog(LOG_WARNING, "Repository::Save() - Failed to write to file: %s", path.c_str());
			return;
		}
	}

	const T* get(const std::string& id) const {
		auto it = items.find(id);
		return it == items.end() ? nullptr : &it->second;
	}

	void upsert(T entity) { items.insert_or_assign(entity.id, std::move(entity)); }
	void remove(const std::string& id) { items.erase(id); }
	std::size_t count() const { return items.size(); }

	auto begin() const { return items.begin(); }
	auto end()   const { return items.end(); }
};