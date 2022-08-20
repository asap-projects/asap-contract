//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "test_helper.h"

namespace asap::contract {
namespace {

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#if defined(ASAP_CONTRACT_DEFAULT)
#define INTERNAL_ACT_TESTSUITE_NAME DefaultModeContrcatsHonored
#elif defined(ASAP_CONTRACT_OFF)
#define INTERNAL_ACT_TESTSUITE_NAME OffModeContrcatsHonored
#elif defined(ASAP_CONTRACT_AUDIT)
#define INTERNAL_ACT_TESTSUITE_NAME AuditModeContrcatsHonored
#else
#define INTERNAL_ACT_TESTSUITE_NAME ContrcatsHonored
#endif
// NOLINTEND(cppcoreguidelines-macro-usage)

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, Expect) {
  static int value = 1;
  testing::TestExpectDefault(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, Ensure) {
  static int value = 1;
  testing::TestEnsureDefault(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, Assert) {
  static int value = 1;
  testing::TestAssertDefault(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, ExpectAudit) {
  static int value = 1;
  testing::TestExpectAudit(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, EnsureAudit) {
  static int value = 1;
  testing::TestEnsureAudit(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, AssertAudit) {
  static int value = 1;
  testing::TestAssertAudit(&value);
}

} // namespace
} // namespace asap::contract
