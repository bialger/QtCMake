#ifndef PROJECTINTEGRATIONUNITTESTSUITE_HPP
#define PROJECTINTEGRATIONUNITTESTSUITE_HPP

#include <filesystem>

#include <gtest/gtest.h>

class ProjectIntegrationTestSuite : public testing::Test {
protected:
  static const std::filesystem::path kTemporaryDirectoryName;

  void SetUp() override;
  void TearDown() override;
};

#endif // PROJECTINTEGRATIONUNITTESTSUITE_HPP
