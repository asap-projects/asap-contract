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
# Unit Test Macros
# ------------------------------------------------------------------------------

set(target_name ${MODULE_TARGET_NAME}_contract_ut_test)

asap_add_test(
  ${target_name}
  UNIT_TEST
  VALGRIND_MEMCHECK
  SRCS
  # headers
  "test_helper.h"
  # sources
  "test_helper.cpp"
  "contract_ut_gtest_test.cpp"
  "main.cpp"
  LINK
  asap::contract-ut
  asap::common
  gtest
  gmock
  COMMENT
  "Contract unit test macros tests")

target_compile_definitions(${target_name} PRIVATE ASAP_CONTRACT_DEFAULT)

gtest_discover_tests(${target_name})
