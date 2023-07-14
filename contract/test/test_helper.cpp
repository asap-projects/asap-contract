//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "test_helper.h"

#include <contract/contract.h>

namespace asap::contract::testing {

auto TestExpectDefault(const int* ptr) -> int
{
  ASAP_EXPECT(ptr, "expecting a valid pointer", 0);
  return *ptr;
}

auto TestEnsureDefault(const int* ptr) -> int
{
  ASAP_ENSURE(ptr, "ensuring a valid pointer", 0);
  return *ptr;
}

auto TestAssertDefault(const int* ptr) -> int
{
  ASAP_ASSERT(ptr, "asserting a valid pointer", 0);
  return *ptr;
}

auto TestExpectAudit(const int* ptr) -> int
{
  ASAP_EXPECT_AUDIT(ptr, "audit - expecting a valid pointer", 0);
  return *ptr;
}

auto TestEnsureAudit(const int* ptr) -> int
{
  ASAP_ENSURE_AUDIT(ptr, "audit - ensuring a valid pointer", 0);
  return *ptr;
}

auto TestAssertAudit(const int* ptr) -> int
{
  ASAP_ASSERT_AUDIT(ptr, "audit - asserting a valid pointer", 0);
  return *ptr;
}

}  // namespace asap::contract::testing
