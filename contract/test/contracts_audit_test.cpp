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
TEST(AuditModeContractViolations, ExpectDefaultWillAbort)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestExpectDefault(nullptr),
      ::testing::KilledBySignal(SIGABRT),
      ".*");
#else
  ASSERT_DEATH(TestExpectDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, EnsureDefaultWillAbort)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestEnsureDefault(nullptr),
      ::testing::KilledBySignal(SIGABRT),
      ".*");
#else
  ASSERT_DEATH(TestEnsureDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, AssertDefaultWillAbort)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestAssertDefault(nullptr),
      ::testing::KilledBySignal(SIGABRT),
      ".*");
#else
  ASSERT_DEATH(TestAssertDefault(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, ExpectAuditWillAbort)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestExpectAudit(nullptr),
      ::testing::KilledBySignal(SIGABRT),
      ".*");
#else
  ASSERT_DEATH(TestExpectAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, EnsureAuditWillAbort)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestEnsureAudit(nullptr),
      ::testing::KilledBySignal(SIGABRT),
      ".*");
#else
  ASSERT_DEATH(TestEnsureAudit(nullptr), "");
#endif
}

// NOLINTNEXTLINE
TEST(AuditModeContractViolations, AssertAuditWillAbort)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(
      TestAssertAudit(nullptr),
      ::testing::KilledBySignal(SIGABRT),
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
TEST(AuditModeConstexprAssertions, AbortsInNonConstExprContext)
{
  constexpr int b{0};
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(divide(10, b), ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(divide(10, b), "");
#endif
}

void unreachable(int value)
{
  if (value == 5) {
    value += 2;
  }
  ASAP_ASSERT_UNREACHABLE("")
}

// NOLINTNEXTLINE
TEST(AuditModeUnreachableAssertions, AbortsIfUnreachable)
{
#if !defined(ASAP_WINDOWS)
  // NOLINTNEXTLINE
  ASSERT_EXIT(unreachable(1), ::testing::KilledBySignal(SIGSEGV), ".*");
#else
  ASSERT_DEATH(unreachable(1), "");
#endif
}
