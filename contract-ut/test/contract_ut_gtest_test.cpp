//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "test_helper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <contract/ut/framework.h>
#include <contract/ut/gtest.h>

using asap::contract::testing::TestAssertDefault;
using asap::contract::testing::TestEnsureDefault;
using asap::contract::testing::TestExpectDefault;

using asap::contract::SetVerbosity;
using asap::contract::Verbosity;

// NOLINTNEXTLINE
TEST(GoogleTestDeathMacros, DefaultModeExpectDeath)
{
  CHECK_VIOLATES_CONTRACT(TestExpectDefault(nullptr));
}

// NOLINTNEXTLINE
TEST(GoogleTestDeathMacros, DefaultModeEnsureDeath)
{
  CHECK_VIOLATES_CONTRACT(TestEnsureDefault(nullptr));
}

// NOLINTNEXTLINE
TEST(GoogleTestDeathMacros, DefaultModeAssertDeath)
{
  CHECK_VIOLATES_CONTRACT(TestAssertDefault(nullptr));
}

void NestedViolator(const int* ptr)
{
  CHECK_VIOLATES_CONTRACT(TestAssertDefault(ptr));
  TestEnsureDefault(nullptr);
}
void Violator(int* ptr)
{
  CHECK_VIOLATES_CONTRACT(TestAssertDefault(ptr));
  CHECK_VIOLATES_CONTRACT(NestedViolator(ptr));
  TestExpectDefault(nullptr);
}

// NOLINTNEXTLINE
TEST(GoogleTestDeathMacros, NestedChecks)
{
  CHECK_VIOLATES_CONTRACT(Violator(nullptr));
}

// NOLINTNEXTLINE
TEST(GoogleTestDeathMacros, VerboseTestPrintsViolationInfo)
{
  class ErrorOutputRedirect
  {
   public:
    explicit ErrorOutputRedirect(std::streambuf* new_buffer)
        : old(std::cerr.rdbuf(new_buffer))
    {
    }

    ErrorOutputRedirect(const ErrorOutputRedirect&) = delete;
    ErrorOutputRedirect(const ErrorOutputRedirect&&) = delete;
    auto operator=(const ErrorOutputRedirect&) -> ErrorOutputRedirect& = delete;
    auto operator=(const ErrorOutputRedirect&&)
        -> ErrorOutputRedirect& = delete;

    ~ErrorOutputRedirect() { std::cerr.rdbuf(old); }

   private:
    std::streambuf* old;
  };

  const std::stringstream buffer;
  ErrorOutputRedirect output(buffer.rdbuf());
  SetVerbosity(Verbosity::VERBOSE);
  CHECK_VIOLATES_CONTRACT(TestExpectDefault(nullptr));
  const auto text = buffer.str();
  EXPECT_THAT(text, ::testing::ContainsRegex("violated"));
}
