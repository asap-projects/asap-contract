# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message("=> [third-party modules]")

# ------------------------------------------------------------------------------
# asap::common
# ------------------------------------------------------------------------------

cpmaddpackage(
  NAME
  asap_common
  GIT_TAG
  master
  GITHUB_REPOSITORY
  asap-projects/asap-common
  "ASAP_COMMON_INSTALL OFF"
  "ASAP_BUILD_TESTS OFF"
  "ASAP_BUILD_EXAMPLES OFF")
