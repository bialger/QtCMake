#include "ProjectIntegrationTestSuite.hpp"

#include <filesystem>

const std::filesystem::path ProjectIntegrationTestSuite::kTemporaryDirectoryName =
    std::filesystem::temp_directory_path() / "gtest_tmp";

void ProjectIntegrationTestSuite::SetUp() {
  std::filesystem::create_directory(kTemporaryDirectoryName);
}

void ProjectIntegrationTestSuite::TearDown() {
  std::filesystem::remove_all(kTemporaryDirectoryName);
}
