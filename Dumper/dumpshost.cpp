#include "dumpshost.h"

#include "wrappers.h"

#include <fstream>

namespace DumpsHost
{
  std::string dumpTimeStamp = {};

  // Last std::string isn't used atm, but dumps.host expects it.
  std::vector<std::tuple<std::string, uintptr_t, std::string>> offsets = {};
  void AddOffset(const std::string& string, uint64 offset) {
    offsets.push_back(std::make_tuple(string, offset, "Offset"));
  }

  nlohmann::json classes = nlohmann::json::array();
  void AddClass(const nlohmann::json& json) {
    classes.push_back(json);
  }

  nlohmann::json functions = nlohmann::json::array();
  void AddFunction(const nlohmann::json& json) {
    functions.push_back(json);
  }

  nlohmann::json structs = nlohmann::json::array();
  void AddStruct(const nlohmann::json& json) {
    structs.push_back(json);
  }

  nlohmann::json enums = nlohmann::json::array();
  void AddEnum(const nlohmann::json& json) {
    enums.push_back(json);
  }

  nlohmann::json inherits = nlohmann::json::array();
  void AddInheritInfo(const nlohmann::json& json) {
    inherits.push_back(json);
  }

  void DumpOffsets(const std::filesystem::path& directory) {
    nlohmann::json j;
    j["updated_at"] = dumpTimeStamp;
    j["offsets"] = nlohmann::json(offsets);

    std::ofstream file(directory / "OffsetsInfo.json");
    file << j.dump();
  }

  void DumpClasses(const std::filesystem::path& directory) {
    nlohmann::json j;
    j["updated_at"] = dumpTimeStamp;
    j["classes"] = classes;

    std::ofstream file(directory / "ClassesInfo.json");
    file << j.dump();
  }

  void DumpFunctions(const std::filesystem::path& directory) {
    nlohmann::json j;
    j["updated_at"] = dumpTimeStamp;
    j["functions"] = functions;

    std::ofstream file(directory / "FunctionsInfo.json");
    file << j.dump();
  }

  void DumpInheritInfo(const std::filesystem::path& directory) {
    std::ofstream file(directory / "InheritInfo.json");
    file << inherits.dump();
  }

  void DumpStructs(const std::filesystem::path& directory) {
    nlohmann::json j;
    j["updated_at"] = dumpTimeStamp;
    j["structs"] = structs;

    std::ofstream file(directory / "StructsInfo.json");
    file << j.dump();
  }

  void DumpEnums(const std::filesystem::path& directory) {
    nlohmann::json j;
    j["updated_at"] = dumpTimeStamp;
    j["enums"] = enums;

    std::ofstream file(directory / "EnumsInfo.json");
    file << j.dump();
  }

  void Dump(std::filesystem::path directory) {
    directory /= "Dumps.host";
    std::filesystem::create_directories(directory);

    dumpTimeStamp = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    // Now we're ready to dump all our acquired information
    DumpOffsets(directory);
    DumpClasses(directory);
    DumpFunctions(directory);
    DumpInheritInfo(directory);
    DumpStructs(directory);
    DumpEnums(directory);
  }
}