//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <asap/contract/contract.h>

using ::testing::IsNull;
using ::testing::NotNull;

using asap::contract::GetViolationHandler;
using asap::contract::Violation;
using asap::contract::ViolationHandler;

/// The signature of functions which can be used as violation handler
/// implementation.
using FunctionType = void (*)(const Violation*);

// NOLINTNEXTLINE
TEST(DefaultHandler, IsDefined)
{
  ViolationHandler::WrapperType dummy_handler;
  auto& default_handler = GetViolationHandler();

  default_handler.SwapHandler(dummy_handler);
  auto* handler_function = dummy_handler.target<FunctionType>();
  ASSERT_THAT(handler_function, NotNull());

  // Restore the handler
  default_handler.SwapHandler(dummy_handler);
  handler_function = dummy_handler.target<FunctionType>();
  ASSERT_THAT(handler_function, IsNull());
}

// NOLINTNEXTLINE
TEST(DefaultHandlerDeathTest, AbortOnViolation)
{
  auto& default_handler = GetViolationHandler();

  constexpr struct asap::contract::Violation violation =
      {__FILE__, __LINE__, "my_function", "precondition", "1 == 2", nullptr};

  // We don't want to be too stringent on what is printed when a contract
  // violation is being handled. We just require that the output contains the
  // word violated. NOLINTNEXTLINE
  ASSERT_DEATH(default_handler.HandleViolation(&violation), "violated");
}

// NOLINTNEXTLINE
TEST(CustomHandler, HandleViolationCallsRegisteredHandler)
{
  ::testing::MockFunction<void(const Violation*)> violation_handler_mock{};
  auto function_mock = violation_handler_mock.AsStdFunction();
  auto& default_handler = GetViolationHandler();
  default_handler.SwapHandler(function_mock);
  auto* handler_function = function_mock.target<FunctionType>();
  ASSERT_THAT(handler_function, NotNull());

  constexpr asap::contract::Violation violation =
      {__FILE__, __LINE__, "my_function", "precondition", "1 == 2", nullptr};

  EXPECT_CALL(violation_handler_mock, Call(&violation)).Times(1);
  default_handler.HandleViolation(&violation);

  default_handler.SwapHandler(function_mock);
  handler_function = function_mock.target<FunctionType>();
  ASSERT_THAT(handler_function, IsNull());
}
