//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

// clang-format off
/*!
 * \file
 *
 * \brief Types and and macros used for contract checking.
 *
 * Behavior of the contract checking macros can be changed by setting the
 * contract checking build mode to one of the values: `OFF`, `DEFAULT` or
 * `AUDIT` by defining the corresponding symbol as per the table below:
 *
 * Build Mode | Symbol to be defined  | Behavior
 * ---------- | --------------------- | --------
 *  OFF       | ASAP_CONTRACT_OFF     | None of the conditions are enforced.
 *  DEFAULT   | ASAP_CONTRACT_DEFAULT | Default mode conditions are enforced and execution will abort if the contract is not honored. Audit mode conditions are ignored.
 *  AUDIT     | ASAP_CONTRACT_AUDIT   | All conditions are enforced and execution will abort if the contract is not honored.
 */
// clang-format on

#pragma once

#include <cstdlib>
#include <functional>
#include <sstream>

#include <contract/asap_contract_export.h>

// -----------------------------------------------------------------------------
// Types used to implement the contract checking macros/apis
// -----------------------------------------------------------------------------

/// Contract checking namespace.
namespace asap::contract {

/// Encapsulates the information related to a contract violation.
struct ASAP_CONTRACT_API Violation
{
  /// The name of the source file in which the violation occurred.
  const char* file{};
  /// The line number at which the violation occurred.
  size_t line{};
  /// The function name inside which the contract violation occurred.
  const char* function{};
  /// The type of the violation (`precondition`, `post-condition` or
  /// `assertion`).
  const char* type{};
  /// The expression that specifies the predicate of the contract.
  const char* condition{};
  /// A custom message that could be used to describe the violation.
  const char* message{};
};

/*!
 * \brief Interface for a violation handler which can switch its implementation
 * at runtime.
 *
 * We expect to have a single violation handler instance in the system, although
 * its implementation can be changed at runtime. Therefore, the interface
 * clearly deletes the copy constructors and assignment operators.
 *
 * \see GetViolationHandler
 */
class ASAP_CONTRACT_API ViolationHandler
{
 public:
  /// A wrapper using std::function around violation handler implementation
  /// functions.
  using WrapperType = std::function<void(const Violation*)>;

  /// Constructor.
  ViolationHandler() = default;

  /// Destructor.
  virtual ~ViolationHandler();

  /// Copy constructor (deleted).
  ViolationHandler(const ViolationHandler&) = delete;

  /// Move constructor (default)
  ViolationHandler(ViolationHandler&&) = default;

  /// Copy assignment operator (deleted)
  auto operator=(const ViolationHandler&) -> ViolationHandler& = delete;

  /// Move assignment operator (default)
  auto operator=(ViolationHandler&&) -> ViolationHandler& = default;

  /*!
   * \brief Handle a contract violation.
   *
   * This method is called when a contract violation occurs. The information
   * related to the violation is provided by the `violation` parameter.
   *
   * \note This function *may* never return.
   *
   * \param violation violation details. Will never be null and is allocated on
   * the stack.
   */
  virtual void HandleViolation(const Violation* violation) = 0;

  /*!
   * \brief Swap the existing violation handler implementation with the give
   * one.
   *
   * \param other_handler at the call time this holds the new violation handler
   * implementation function. Upon return, it will hold the old violation
   * handler function.
   */
  virtual void SwapHandler(WrapperType& other_handler) = 0;
};

/*!
 * \brief Obtain the single instance of the violation handler.
 *
 * \note This function is very lightweight and can be called as often as
 * required. It is preferred to exclusively call it every time the violation
 * handler is needed instead of storing the returned reference.
 *
 * \return a reference to the violation handler.
 */
ASAP_CONTRACT_API auto GetViolationHandler() -> ViolationHandler&;

}  // namespace asap::contract

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

// -----------------------------------------------------------------------------
// Contract checking macros
// -----------------------------------------------------------------------------

// --- Default mode macros -----------------------------------------------------

/*!
 * \brief Defines a precondition.
 *
 * A precondition describes the function's expectation of its arguments and/or
 * the state of other objects upon entry into the function and is usually placed
 * at the start of a function body.
 *
 * \note The prediction is ignored if the contract checking build mode is `OFF`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_EX_3_(condition, message, return_value)                           \
  ASAP_EX_CHECK_(ASAP_CONTRACT_MODE_DEFAULT_, condition, message, return_value)
#define ASAP_EX_2_(condition, message) ASAP_EX_3_(condition, message, )
#define ASAP_EX_1_(condition) ASAP_EX_2_(condition, "")
// #define ASAP_EX_0_()
#define ASAP_EX_BY_ARG_COUNT_(...)                                             \
  ASAP_COMPOSE_4_((__VA_ARGS__, ASAP_EX_3_, ASAP_EX_2_, ASAP_EX_1_, ))
#define ASAP_EX_NO_ARG_EXPANDER_() , , , ASAP_EX_0_()
#define ASAP_EX_SELECT_(...)                                                   \
  ASAP_EX_BY_ARG_COUNT_(ASAP_EX_NO_ARG_EXPANDER_ __VA_ARGS__())
#define ASAP_EXPECT(...) ASAP_EX_SELECT_(__VA_ARGS__)(__VA_ARGS__)

/*!
 * Defines a post-condition.
 *
 * A post-condition is a condition that a function should ensure for the return
 * value and/or the state of objects upon exit from the function and is usually
 * placed immediately before returning control to the caller of the function.
 *
 * \note The post-condition is ignored if the contract checking build mode is
 * `OFF`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_EN_3_(condition, message, return_value)                           \
  ASAP_EN_CHECK_(ASAP_CONTRACT_MODE_DEFAULT_, condition, message, return_value)
#define ASAP_EN_2_(condition, message) ASAP_EN_3_(condition, message, )
#define ASAP_EN_1_(condition) ASAP_EN_2_(condition, "")
// #define ASAP_EN_0_()
#define ASAP_EN_BY_ARG_COUNT_(...)                                             \
  ASAP_COMPOSE_4_((__VA_ARGS__, ASAP_EN_3_, ASAP_EN_2_, ASAP_EN_1_, ))
#define ASAP_EN_NO_ARG_EXPANDER_() , , ASAP_EN_0_()
#define ASAP_EN_CHOOSE_(...)                                                   \
  ASAP_EN_BY_ARG_COUNT_(ASAP_EN_NO_ARG_EXPANDER_ __VA_ARGS__())
#define ASAP_ENSURE(...) ASAP_EN_CHOOSE_(__VA_ARGS__)(__VA_ARGS__)

/*!
 * \brief Defines an assertion.
 *
 * An assertion is a condition that should be satisfied where it appears in a
 * function body and can be placed anywhere within the body of a function.
 *
 * \note The assertion is ignored if the contract checking build mode is `OFF`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_A_3_(condition, message, return_value)                            \
  ASAP_A_CHECK_(ASAP_CONTRACT_MODE_DEFAULT_, condition, message, return_value)
#define ASAP_A_2_(condition, message) ASAP_A_3_(condition, message, )
#define ASAP_A_1_(condition) ASAP_A_2_(condition, "")
// #define ASAP_A_0_()
#define ASAP_A_BY_ARG_COUNT_(...)                                              \
  ASAP_COMPOSE_4_((__VA_ARGS__, ASAP_A_3_, ASAP_A_2_, ASAP_A_1_, ))
#define ASAP_A_NO_ARG_EXPANDER_() , , , ASAP_A_0_()
#define ASAP_A_CHOOSE_(...)                                                    \
  ASAP_A_BY_ARG_COUNT_(ASAP_A_NO_ARG_EXPANDER_ __VA_ARGS__())
#define ASAP_ASSERT(...) ASAP_A_CHOOSE_(__VA_ARGS__)(__VA_ARGS__)

/*!
 * \brief Defines a constexpr assertion macro.
 *
 * In a `constexpr` context, if the condition fails, the code fails to compile.
 * In a non-`constexpr` context, if the condition fails, message is printed to
 * error output and the application aborts.
 *
 * \note The assertion is ignored if the contract checking build mode is `OFF`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_C_A_2_(condition, message)                                        \
  ASAP_C_A_CHECK_(ASAP_C_A_MODE_DEFAULT_, condition, message)
#define ASAP_C_A_1_(condition) ASAP_C_A_2_(condition, )
// #define ASAP_C_A_0_()
#define ASAP_C_A_BY_ARG_COUNT_(...)                                            \
  ASAP_COMPOSE_3_((__VA_ARGS__, ASAP_C_A_2_, ASAP_C_A_1_, ))
#define ASAP_C_A_NO_ARG_EXPANDER_() , , ASAP_C_A_0_()
#define ASAP_C_A_CHOOSE_(...)                                                  \
  ASAP_C_A_BY_ARG_COUNT_(ASAP_C_A_NO_ARG_EXPANDER_ __VA_ARGS__())
#define ASAP_CONSTEXPR_ASSERT(...) ASAP_C_A_CHOOSE_(__VA_ARGS__)(__VA_ARGS__)

/*!
 * \brief Defines an assertion macro for unreachable code.
 *
 * If code marked with this macro is reached, `message` is printed to error
 * output and the application aborts.
 *
 * \note The assertion is ignored if the contract checking build mode is `OFF`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */

#define ASAP_A_U_1_(message) ASAP_A_U_CHECK_(ASAP_A_U_MODE_DEFAULT_, message)
#define ASAP_A_U_0_() ASAP_A_U_1_("")
#define ASAP_A_U_BY_ARG_COUNT_(...)                                            \
  ASAP_COMPOSE_2_((__VA_ARGS__, ASAP_A_U_1_, ))
#define ASAP_A_U_NO_ARG_EXPANDER_() , ASAP_A_U_0_
#define ASAP_A_U_SELECT_(...)                                                  \
  ASAP_A_U_BY_ARG_COUNT_(ASAP_A_U_NO_ARG_EXPANDER_ __VA_ARGS__())
#define ASAP_ASSERT_UNREACHABLE(...) ASAP_A_U_SELECT_(__VA_ARGS__)(__VA_ARGS__)

// --- Audit mode macros -------------------------------------------------------

/*!
 * \brief Defines a precondition for the `AUDIT` contract checking mode.
 *
 * A precondition describes the function's expectation of its arguments and/or
 * the state of other objects upon entry into the function and is usually placed
 * at the start of a function body.
 *
 * \note The precondition is enforced only if the contract checking build mode
 * is `AUDIT`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_EXPECT_AUDIT(condition, message, return_value)                    \
  ASAP_EX_CHECK_(ASAP_CONTRACT_MODE_AUDIT_, condition, message, return_value)

/*!
 * \brief Defines a post-condition for the `AUDIT` contract checking mode.
 *
 * A post-condition is a condition that a function should ensure for the return
 * value and/or the state of objects upon exit from the function and is usually
 * placed immediately before returning control to the caller of the function.
 *
 * \note The post-condition is enforced only if the contract checking build mode
 * is `AUDIT`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_ENSURE_AUDIT(condition, message, return_value)                    \
  ASAP_EN_CHECK_(ASAP_CONTRACT_MODE_AUDIT_, condition, message, return_value)

/*!
 * \brief Defines an assertion for the `AUDIT` contract checking mode.
 *
 * An assertion is a condition that should be satisfied where it appears in a
 * function body and can be placed anywhere within the body of a function.
 *
 * \note The assertion is enforced only if the contract checking build mode is
 * `AUDIT`.
 *
 * \param cond an expression, that specifies the predicate of the contract.
 */
#define ASAP_ASSERT_AUDIT(condition, message, return_value)                    \
  ASAP_A_CHECK_(ASAP_CONTRACT_MODE_AUDIT_, condition, message, return_value)

// -----------------------------------------------------------------------------
// Internal macros
// -----------------------------------------------------------------------------

#define ASAP_SELECT_4_(_f1, _f2, _f3, _f4, ...) _f4
#define ASAP_COMPOSE_4_(args) ASAP_SELECT_4_ args
#define ASAP_SELECT_3_(_f1, _f2, _f3, ...) _f3
#define ASAP_COMPOSE_3_(args) ASAP_SELECT_3_ args
#define ASAP_SELECT_2_(_f1, _f2, ...) _f2
#define ASAP_COMPOSE_2_(args) ASAP_SELECT_2_ args

// Exclude internal macros from doxygen documentation
#if !defined(DOXYGEN_DOCUMENTATION_BUILD)

/* Helper macros */
# define ASAP_EX_CHECK_(check, condition, message, return_value)               \
   check(ASAP_CONTRACT_TYPE_EXPECT_, condition, message, return_value)

# define ASAP_EN_CHECK_(check, condition, message, return_value)               \
   check(ASAP_CONTRACT_TYPE_ENSURE_, condition, message, return_value)

# define ASAP_A_CHECK_(check, condition, message, return_value)                \
   check(ASAP_CONTRACT_TYPE_ASSERT_, condition, message, return_value)

# define ASAP_C_A_CHECK_(check, condition, message)                            \
   check(ASAP_CONTRACT_TYPE_ASSERT_, condition, message)

# define ASAP_A_U_CHECK_(check, message) check(message)

/* Contract names */
# define ASAP_CONTRACT_TYPE_EXPECT_ "precondition"
# define ASAP_CONTRACT_TYPE_ENSURE_ "post-condition"
# define ASAP_CONTRACT_TYPE_ASSERT_ "assertion"

/* Create violation handler call */
# define ASAP_CONTRACT_HANDLE_VIOLATION_(                                      \
     type,                                                                     \
     condition,                                                                \
     message,                                                                  \
     return_value)                                                             \
   std::ostringstream debug;                                                   \
   debug << message;                                                           \
   const auto& message_str = debug.str();                                      \
   const struct asap::contract::Violation violation = {                        \
       __FILE__,                                                               \
       __LINE__,                                                               \
       static_cast<const char*>(__func__),                                     \
       type,                                                                   \
       #condition,                                                             \
       message_str.empty() ? nullptr : message_str.c_str()};                   \
   asap::contract::GetViolationHandler().HandleViolation(&violation)

/* Contract modes */

# define ASAP_CONTRACT_IGNORE_(type, condition, message, return_value)         \
   (void)sizeof((condition) ? 1 : 0)

# define ASAP_CONTRACT_CHECK_NEVER_CONTINUE_(                                  \
     type,                                                                     \
     condition,                                                                \
     message,                                                                  \
     return_value)                                                             \
   do {                                                                        \
     if (!(condition)) {                                                       \
       ASAP_CONTRACT_HANDLE_VIOLATION_(                                        \
           type,                                                               \
           condition,                                                          \
           message,                                                            \
           return_value);                                                      \
       return return_value;                                                    \
     }                                                                         \
   } while (0)

/* Constexpr assertions modes */

# define ASAP_C_A_IGNORE_(type, condition, message) static_cast<void>(0)

# define ASAP_C_A_CHECK_NEVER_CONTINUE_(type, condition, message)              \
   static_cast<void>(                                                          \
       (condition)                                                             \
           ? 0                                                                 \
           : (                                                                 \
                 [&]() {                                                       \
                  ASAP_CONTRACT_HANDLE_VIOLATION_(type, condition, message, ); \
                 }(),                                                          \
                 0))

/* Assert unreachable modes */

# if defined(__clang__)
#  if __has_builtin(__builtin_unreachable)
#   define ASAP_A_U_IGNORE_(message) __builtin_unreachable();
#  endif
# elif defined(__GNUC__)
#  if __GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#   define ASAP_A_U_IGNORE_(message) __builtin_unreachable();
#  endif
# elif defined(_MSC_VER)
#  define ASAP_A_U_IGNORE_(message) __assume(0);
# else
#  define ASAP_A_U_IGNORE_(message) std::abort();
# endif

# define ASAP_A_U_CHECK_NEVER_CONTINUE_(message)                               \
   do {                                                                        \
     ASAP_CONTRACT_HANDLE_VIOLATION_("assertion", "unreachable", message, );   \
   } while (false);

/* Build configuration options */

# if defined ASAP_CONTRACT_OFF
#  if defined ASAP_CONTRACT_DEFAULT
#   error At most one of ASAP_CONTRACT_OFF, ASAP_CONTRACT_DEFAULT, ASAP_CONTRACT_AUDIT must be specified
#  endif
#  define ASAP_CONTRACT_BUILD__ ASAP_CONTRACT_BUILD_MODE_OFF_
# elif defined ASAP_CONTRACT_DEFAULT
#  if defined ASAP_CONTRACT_AUDIT
#   error At most one of ASAP_CONTRACT_OFF, ASAP_CONTRACT_DEFAULT, ASAP_CONTRACT_AUDIT must be specified
#  endif
#  define ASAP_CONTRACT_BUILD__ ASAP_CONTRACT_BUILD_MODE_DEFAULT_
# elif defined ASAP_CONTRACT_AUDIT
#  define ASAP_CONTRACT_BUILD__ ASAP_CONTRACT_BUILD_MODE_AUDIT_
# else /* Default build */
#  define ASAP_CONTRACT_BUILD__ ASAP_CONTRACT_BUILD_MODE_DEFAULT_
# endif

# define ASAP_CONTRACT_BUILD_MODE_OFF__ 0
# define ASAP_CONTRACT_BUILD_MODE_DEFAULT_ 1
# define ASAP_CONTRACT_BUILD_MODE_AUDIT_ 2

/* Standard build configurations */
# if ASAP_CONTRACT_BUILD__ == ASAP_CONTRACT_BUILD_MODE_OFF_
#  define ASAP_CONTRACT_MODE_DEFAULT_ ASAP_CONTRACT_IGNORE_
#  define ASAP_C_A_MODE_DEFAULT_ ASAP_C_A_IGNORE_
#  define ASAP_A_U_MODE_DEFAULT_ ASAP_A_U_IGNORE_
#  define ASAP_CONTRACT_MODE_AUDIT_ ASAP_CONTRACT_IGNORE_
# elif ASAP_CONTRACT_BUILD__ == ASAP_CONTRACT_BUILD_MODE_DEFAULT_
#  define ASAP_CONTRACT_MODE_DEFAULT_ ASAP_CONTRACT_CHECK_NEVER_CONTINUE_
#  define ASAP_C_A_MODE_DEFAULT_ ASAP_C_A_CHECK_NEVER_CONTINUE_
#  define ASAP_A_U_MODE_DEFAULT_ ASAP_A_U_CHECK_NEVER_CONTINUE_
#  define ASAP_CONTRACT_MODE_AUDIT_ ASAP_CONTRACT_IGNORE_
# elif ASAP_CONTRACT_BUILD__ == ASAP_CONTRACT_BUILD_MODE_AUDIT_
#  define ASAP_CONTRACT_MODE_DEFAULT_ ASAP_CONTRACT_CHECK_NEVER_CONTINUE_
#  define ASAP_C_A_MODE_DEFAULT_ ASAP_C_A_CHECK_NEVER_CONTINUE_
#  define ASAP_A_U_MODE_DEFAULT_ ASAP_A_U_CHECK_NEVER_CONTINUE_
#  define ASAP_CONTRACT_MODE_AUDIT_ ASAP_CONTRACT_CHECK_NEVER_CONTINUE_
# endif

/* Options to override standard build configurations */
# if defined ASAP_CONTRACT_MODE_DEFAULT
#  undef ASAP_CONTRACT_MODE_DEFAULT_
#  define ASAP_CONTRACT_MODE_DEFAULT_ ASAP_CONTRACT_MODE_DEFAULT
# endif

# if defined ASAP_CONSTEXPR_MODE_DEFAULT
#  undef ASAP_C_A_MODE_DEFAULT_
#  define ASAP_C_A_MODE_DEFAULT_ ASAP_CONSTEXPR_MODE_DEFAULT
# endif

# if defined ASAP_UNREACHABLE_MODE_DEFAULT
#  undef ASAP_A_U_MODE_DEFAULT_
#  define ASAP_A_U_MODE_DEFAULT_ ASAP_UNREACHABLE_MODE_DEFAULT
# endif

# if defined ASAP_CONTRACT_MODE_AUDIT
#  undef ASAP_CONTRACT_MODE_AUDIT_
#  define ASAP_CONTRACT_MODE_AUDIT_ ASAP_CONTRACT_MODE_AUDIT
# endif

#endif  // DOXYGEN_DOCUMENTATION_BUILD

// NOLINTEND(cppcoreguidelines-macro-usage)
