//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <asap/contract/ut/framework.h>

auto main(int argc, char** argv) -> int
{
  asap::contract::PrepareForTesting();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
