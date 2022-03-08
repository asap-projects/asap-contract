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
#include <memory>

#include <contract/contract.h>

namespace asap::contract {

// -----------------------------------------------------------------------------
// Unit Testing stuff
// -----------------------------------------------------------------------------

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

} // namespace

ViolationHandler::~ViolationHandler() = default;

// Internal implementation of the singleton violation handler.
class ViolationHandler_impl : public ViolationHandler {
public:
  /*!
   * Get the single instance of the singleton.
   *
   * \return the single instance of the singleton.
   */
  static auto instance() -> ViolationHandler_impl & {
    // We do expect a clang compiler warning here about the exit time destructor
    // required for this statement. The risk present here is that some other
    // global variable destructor would use contract validation macros after the
    // violation handler is destroyed. We can't really fix this warning and just
    // storing a function pointer instead of a function object would create way
    // too many more warnings...
    //
    // ==> It is acceptable to not use contract checks in global destructors.
#if defined(__clang__)
#if __has_warning("-Wexit-time-destructors")
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
#endif
    static const std::unique_ptr<ViolationHandler_impl> _instance{
        new ViolationHandler_impl()};
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

    return *_instance;
  }

  /// Destructor.
  ~ViolationHandler_impl() override = default;

  /// Copy constructor (deleted).
  ViolationHandler_impl(const ViolationHandler_impl &) = delete;

  /// Assignment operator (deleted).
  auto operator=(const ViolationHandler_impl)
      -> ViolationHandler_impl & = delete;

  /// Move constructor (deleted).
  ViolationHandler_impl(ViolationHandler_impl &&) = delete;

  /// Move assignment operator (deleted).
  auto operator=(ViolationHandler_impl &&) -> ViolationHandler_impl & = delete;

  void HandleViolation(const Violation *violation) override;
  void SwapHandler(WrapperType &other_handler) override;

private:
  /// Default constructor.
  ViolationHandler_impl() = default;

  WrapperType handler = WrapperType{DefaultViolationHandler};
};

void ViolationHandler_impl::HandleViolation(const Violation *violation) {
  assert(violation != nullptr); // NOLINT
  handler(violation);
}

void ViolationHandler_impl::SwapHandler(WrapperType &other_handler) {
  other_handler.swap(handler);
}

auto GetViolationHandler() -> ViolationHandler & {
  return ViolationHandler_impl::instance();
}

} // namespace asap::contract
