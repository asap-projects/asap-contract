//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "test_helper.h"

#include <gtest/gtest.h>

using asap::contract::testing::TestAssertAudit;
using asap::contract::testing::TestAssertDefault;
using asap::contract::testing::TestEnsureAudit;
using asap::contract::testing::TestEnsureDefault;
using asap::contract::testing::TestExpectAudit;
using asap::contract::testing::TestExpectDefault;

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#if defined(ASAP_CONTRACT_DEFAULT)
# define INTERNAL_ACT_TESTSUITE_NAME DefaultModeContrcatsHonored
#elif defined(ASAP_CONTRACT_OFF)
# define INTERNAL_ACT_TESTSUITE_NAME OffModeContrcatsHonored
#elif defined(ASAP_CONTRACT_AUDIT)
# define INTERNAL_ACT_TESTSUITE_NAME AuditModeContrcatsHonored
#else
# define INTERNAL_ACT_TESTSUITE_NAME ContrcatsHonored
#endif
// NOLINTEND(cppcoreguidelines-macro-usage)

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, Expect)
{
  static int value = 1;
  TestExpectDefault(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, Ensure)
{
  static int value = 1;
  TestEnsureDefault(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, Assert)
{
  static int value = 1;
  TestAssertDefault(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, ExpectAudit)
{
  static int value = 1;
  TestExpectAudit(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, EnsureAudit)
{
  static int value = 1;
  TestEnsureAudit(&value);
}

// NOLINTNEXTLINE
TEST(INTERNAL_ACT_TESTSUITE_NAME, AssertAudit)
{
  static int value = 1;
  TestAssertAudit(&value);
}
