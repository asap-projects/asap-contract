.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

**********************
Unit testing contracts
**********************

Testing contracts is tricky as violations often result in the program execution
being abruptly terminated rendering it quite difficult to test without death
test support by the testing framework.

To simplify this situation, we provide special macros for unit testing with
Google Test (other frameworks can be easily added) that do not require the use
of death tests.

.. doxygendefine:: CHECK_VIOLATES_CONTRACT

.. doxygendefine:: EXPECT_VIOLATES_CONTRACT

.. doxygendefine:: ASSERT_VIOLATES_CONTRACT

Example
=======

.. code-block:: c++

  // Some function to be tested in some .cpp file
  auto TestExpectDefault(const int *ptr) -> int {
    ASAP_EXPECT(ptr);
    return *ptr;
  }

.. code-block:: c++

  #include "contract/ut/framework.h"
  #include "contract/ut/gtest.h"

  #include <gtest/gtest.h>

  TEST(GoogleTestDeathMacros, DefaultModeExpectDeath) {
    CHECK_VIOLATES_CONTRACT(testing::TestExpectDefault(nullptr));
  }

  auto main(int argc, char **argv) -> int {
    asap::contract::PrepareForTesting();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }

Limitations
===========

The mechanism that allows contract checks to be tested during unit tests is
implemented with setjmp and longjmp. It uses global variables to save the stack
environment during the setjmp/longjmp which is not thread safe.
