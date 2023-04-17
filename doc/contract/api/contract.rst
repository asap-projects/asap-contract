.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

*****************
Contract checking
*****************

Contract checking macros
========================

There are three contract checking modes that can be set at build time by
defining the appropriate symbol. Each mode has a specific behavior for the
contract checking at runtime as described in the table below:

.. list-table::
  :header-rows: 1
  :widths: 15 30 55

  * - Build mode
    - Symbol to be defined
    - Behavior

  * - OFF
    - ASAP_CONTRACT_OFF
    - None of the conditions are enforced.

  * - DEFAULT
    - ASAP_CONTRACT_DEFAULT
    - Default mode conditions are enforced and execution will abort if the
      contract is not honored. Audit mode conditions are ignored.

  * - AUDIT
    - ASAP_CONTRACT_AUDIT
    - All conditions are enforced and execution will abort if the contract is
      not honored.

Default mode macros
-------------------

.. doxygendefine:: ASAP_EXPECT

.. doxygendefine:: ASAP_ENSURE

.. doxygendefine:: ASAP_ASSERT

Audit mode macros
-------------------

.. doxygendefine:: ASAP_EXPECT_AUDIT

.. doxygendefine:: ASAP_ENSURE_AUDIT

.. doxygendefine:: ASAP_ASSERT_AUDIT

Violation Handler
=================

There is a single violation handler in the system. Its implementation, however,
can be switched at runtime to install a custom handler.

.. doxygenfunction:: GetViolationHandler

.. doxygenclass:: asap::contract::ViolationHandler
   :members:
