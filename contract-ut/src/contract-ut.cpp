//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

/*!
 * \file
 *
 * \brief Implementation details for the contract checking API.
 */

#include <cassert>
#include <csetjmp>
#include <iostream>

#include <contract/contract.h>
#include <contract/ut/framework.h>

namespace asap::contract {

// -----------------------------------------------------------------------------
// Unit Testing stuff
// -----------------------------------------------------------------------------

namespace {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
int contract_check_active = 0;

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
Verbosity verbosity_level = Verbosity::QUIET;

} // namespace

namespace details {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
jmp_buf jmp_env;

void ContractCheckPush() {
  contract_check_active++;
}

void ContractCheckPop() {
  contract_check_active--;
}

} // namespace details

namespace {

void PrintViolation(const Violation *violation) {
  std::cerr << violation->file << ":" << violation->line << ": in "
            << violation->function << ": " << violation->type << " '"
            << violation->condition << "' violated" << std::endl;
}

[[noreturn]] void DefaultViolationHandler(const Violation *violation) {
  PrintViolation(violation);
  abort();
}

[[noreturn]] void TestViolationHandler(const Violation *violation) {
  if (contract_check_active == 0) {
    std::cerr << "Unexpected contract violation:" << std::endl;
    DefaultViolationHandler(violation);
  }

  if (verbosity_level == Verbosity::VERBOSE) {
    PrintViolation(violation);
  }

  // Restore calling environment and jump back to setjmp. Return
  // -1 so that setjmp will return false for conditional test.
  // NOLINTNEXTLINE
  longjmp(details::jmp_env, 1);
}

} // namespace

void SetVerbosity(Verbosity verbosity) {
  verbosity_level = verbosity;
}

void PrepareForTesting() {
  auto test_handler = ViolationHandler::WrapperType{TestViolationHandler};
  GetViolationHandler().SwapHandler(test_handler);
}

} // namespace asap::contract
