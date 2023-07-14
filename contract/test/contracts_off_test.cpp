//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "test_helper.h"

#include <gtest/gtest.h>

#include <common/platform.h>
#include <contract/contract.h>

using asap::contract::testing::TestAssertAudit;
using asap::contract::testing::TestAssertDefault;
using asap::contract::testing::TestEnsureAudit;
using asap::contract::testing::TestEnsureDefault;
using asap::contract::testing::TestExpectAudit;
using asap::contract::testing::TestExpectDefault;

// NOLINTNEXTLINE
TEST(OffModeContractViolations, ExpectDefaultWillSegFault)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestExpectDefault(nullptr),
      ::testing::KilledBySignal(SIGSEGV),
      ".*");
#else
  ASSERT_DEATH(TestExpectDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, EnsureDefaultWillSegFault)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestEnsureDefault(nullptr),
      ::testing::KilledBySignal(SIGSEGV),
      ".*");
#else
  ASSERT_DEATH(TestEnsureDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, AssertDefaultWillSegFault)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestAssertDefault(nullptr),
      ::testing::KilledBySignal(SIGSEGV),
      ".*");
#else
  ASSERT_DEATH(TestAssertDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, ExpectAuditWillSegFault)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestExpectAudit(nullptr),
      ::testing::KilledBySignal(SIGSEGV),
      ".*");
#else
  ASSERT_DEATH(TestExpectAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, EnsureAuditWillSegFault)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestEnsureAudit(nullptr),
      ::testing::KilledBySignal(SIGSEGV),
      ".*");
#else
  ASSERT_DEATH(TestEnsureAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(OffModeContractViolations, AssertAuditWillSegFault)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestAssertAudit(nullptr),
      ::testing::KilledBySignal(SIGSEGV),
      ".*");
#else
  ASSERT_DEATH(TestAssertAudit(nullptr), "");
#endif
}

constexpr int divide(int a, int b)
{
  return ASAP_CONSTEXPR_ASSERT(b, "divide(): can't divide by zero"), a / b;
}

// NOLINTNEXTLINE
TEST(OffModeConstexprAssertions, Ignored)
{
  constexpr int b{-1};
  divide(10, b);
}

void Unreachable(int value)
{
  if (value == 5) {
    value += 2;
    (void)value;
  } else {
    ASAP_ASSERT_UNREACHABLE()
  }
}

// NOLINTNEXTLINE
TEST(OffModeUnreachableAssertions, DoesNotAbortInUnreachableCode)
{
  Unreachable(5);
}

// NOLINTNEXTLINE
TEST(DefaultModeUnreachableAssertions, MayAbortIfReached)
{
#if defined(_MSC_VER)
  Unreachable(1);
  Unreachable(5);
#else
  Unreachable(5);
#endif
}
