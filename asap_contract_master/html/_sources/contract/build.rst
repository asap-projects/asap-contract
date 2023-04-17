.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

************************
Build time configuration
************************

.. toctree::
   :maxdepth: 2
   :hidden:

The behavior of the contract checking macros can be changed by setting the
contract checking build mode to one of the values: `OFF`, `DEFAULT` or `AUDIT`
by defining the corresponding symbol as per the table below:

.. list-table:: Title
   :widths: 20 25 55
   :header-rows: 1

   * - Build Mode
     - Symbol to be defined
     - Behavior
   * - OFF
     - ASAP_CONTRACT_OFF
     - None of the conditions are enforced.
   * - DEFAULT
     - ASAP_CONTRACT_DEFAULT
     - Default mode conditions are enforced and execution will abort if the contract is not honored. Audit mode conditions are ignored.
   * - AUDIT
     - ASAP_CONTRACT_AUDIT
     - All conditions are enforced and execution will abort if the contract is not honored.

When using ASAP
===============

If you are using `asap <https://github.com/abdes/asap>`_ as your project base
for the build framework, then things get even easier. All target-creating cmake
functions provides by `asap` such as `asap_add_library`, `asap_add_executable`
and `asap_add_test`, etc., take a parameter `CONTRACTS` that can have a value of
'OFF', 'DEFAULT', 'AUDIT' or 'AUTO' and will set the appropriate compiler
definition based on the requested contracts enforcement mode.

When 'AUTO' is chosen, contract checking mode will be set using as a first
priority the value passed in the cmake option `OPTION_CONTRACT_MODE`. If none is
present, automatically set the mode based on the build configuration.

* For `Debug` it's `AUDIT`,
* for `Release` and `RelMinSize` it's OFF, and
* for `RelWithDebInfo` it's DEFAULT.

Only for the purpose of internal testing, a special value of `TESTING` can be
used which indicates that contracts are being testing and the  target needs to
have full control on the contract checking mode. Nothing will be done behind the
scene.

Example
-------

.. code-block:: cmake

  asap_add_test(my-test
    CONTRACTS  DEFAULT
    UNIT_TEST
    SRCS
    "main.cpp"
    LINK
    asap::contract
    asap::common
    gtest
    gmock
    COMMENT
    "A simple unit test using asap contracts")
