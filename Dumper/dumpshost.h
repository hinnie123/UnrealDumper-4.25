#pragma once

#include "defs.h"

#include <string>
#include <filesystem>

#include <json.hpp>

namespace DumpsHost
{
  void AddOffset(const std::string& string, uint64 offset);

  void AddClass(const nlohmann::json& json);
  void AddFunction(const nlohmann::json& json);

  void AddStruct(const nlohmann::json& json);
  void AddEnum(const nlohmann::json& json);

  void AddInheritInfo(const nlohmann::json& json);

  void Dump(std::filesystem::path directory);
}