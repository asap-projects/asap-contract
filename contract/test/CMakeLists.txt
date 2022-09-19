# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

# ==============================================================================
# Build instructions
# ==============================================================================

# If running with google sanitizers, skill all these targets as they are abort
# and segmentation fault tests that do not make sense to run under sanitizers
if(ASAP_WITH_GOOGLE_ASAN
   OR ASAP_WITH_GOOGLE_UBSAN
   OR ASAP_WITH_GOOGLE_TSAN)
  return()
endif()

# Set this to ON to inhibit adding compiler definitions for contract modes
set(ASAP_CONTRACT_TESTING ON)

# ------------------------------------------------------------------------------
# Default mode tests
# ------------------------------------------------------------------------------

set(target_name ${MODULE_TARGET_NAME}_contract_default_test)

asap_add_test(
  ${target_name}
  UNIT_TEST
  VALGRIND_MEMCHECK
  SRCS
  # headers
  "test_helper.h"
  # sources
  "contracts_default_test.cpp"
  "contract_handlers_test.cpp"
  "contracts_honored_test.cpp"
  "test_helper.cpp"
  "main.cpp"
  LINK
  asap::contract
  asap::common
  gtest
  gmock
  COMMENT
  "Contract unit tests in DEFAULT build mode")

target_compile_definitions(${target_name} PRIVATE ASAP_CONTRACT_DEFAULT)

gtest_discover_tests(${target_name})

# ------------------------------------------------------------------------------
# OFF mode tests
# ------------------------------------------------------------------------------

set(target_name ${MODULE_TARGET_NAME}_contract_off_test)

asap_add_test(
  ${target_name}
  UNIT_TEST
  VALGRIND_MEMCHECK
  SRCS
  # headers
  "test_helper.h"
  # sources
  "contracts_off_test.cpp"
  "contracts_honored_test.cpp"
  "test_helper.cpp"
  "main.cpp"
  LINK
  asap::contract
  asap::common
  gtest
  gmock
  COMMENT
  "Contract unit tests in OFF build mode")

target_compile_definitions(${target_name} PRIVATE ASAP_CONTRACT_OFF)

gtest_discover_tests(${target_name})

# ------------------------------------------------------------------------------
# Audit mode tests
# ------------------------------------------------------------------------------

set(target_name ${MODULE_TARGET_NAME}_contract_audit_test)

asap_add_test(
  ${target_name}
  UNIT_TEST
  VALGRIND_MEMCHECK
  SRCS
  # headers
  "test_helper.h"
  # sources
  "contracts_audit_test.cpp"
  "contracts_honored_test.cpp"
  "test_helper.cpp"
  "main.cpp"
  LINK
  asap::contract
  asap::common
  gtest
  gmock
  COMMENT
  "Contract unit tests in AUDIT build mode")

target_compile_definitions(${target_name} PRIVATE ASAP_CONTRACT_AUDIT)

gtest_discover_tests(${target_name})
