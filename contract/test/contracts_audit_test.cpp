//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <common/platform.h>

#include "test_helper.h"

namespace asap::contract {
namespace {

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, ExpectDefaultWillAbort) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestExpectDefault(nullptr),
      ::testing::KilledBySignal(SIGABRT), ".*");
#else
  ASSERT_DEATH(testing::TestExpectDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, EnsureDefaultWillAbort) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestEnsureDefault(nullptr),
      ::testing::KilledBySignal(SIGABRT), ".*");
#else
  ASSERT_DEATH(testing::TestEnsureDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, AssertDefaultWillAbort) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestAssertDefault(nullptr),
      ::testing::KilledBySignal(SIGABRT), ".*");
#else
  ASSERT_DEATH(testing::TestAssertDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, ExpectAuditWillAbort) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestExpectAudit(nullptr),
      ::testing::KilledBySignal(SIGABRT), ".*");
#else
  ASSERT_DEATH(testing::TestExpectAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, EnsureAuditWillAbort) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestEnsureAudit(nullptr),
      ::testing::KilledBySignal(SIGABRT), ".*");
#else
  ASSERT_DEATH(testing::TestEnsureAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, AssertAuditWillAbort) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestAssertAudit(nullptr),
      ::testing::KilledBySignal(SIGABRT), ".*");
#else
  ASSERT_DEATH(testing::TestAssertAudit(nullptr), "");
#endif
}

} // namespace
} // namespace asap::contract
