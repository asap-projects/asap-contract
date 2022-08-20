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
TEST(OffModeContractViolations, ExpectDefaultWillSegFault) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestExpectDefault(nullptr),
      ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(testing::TestExpectDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, EnsureDefaultWillSegFault) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestEnsureDefault(nullptr),
      ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(testing::TestEnsureDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, AssertDefaultWillSegFault) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestAssertDefault(nullptr),
      ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(testing::TestAssertDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, ExpectAuditWillSegFault) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestExpectAudit(nullptr),
      ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(testing::TestExpectAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, EnsureAuditWillSegFault) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestEnsureAudit(nullptr),
      ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(testing::TestEnsureAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, AssertAuditWillSegFault) {
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(testing::TestAssertAudit(nullptr),
      ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(testing::TestAssertAudit(nullptr), "");
#endif
}

} // namespace
} // namespace asap::contract
