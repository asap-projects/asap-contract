.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

##############################
ASAP contract's documentation!
##############################

.. |date| date::

Last Updated on |date|

.. toctree::
   :maxdepth: 2
   :titlesonly:
   :hidden:

   license
   changelog.md
   version

Welcome! This is the documentation for the
`asap-contract <https://github.com/asap-projects/asap-contract>`_ |version|
project.

This is a build container for the :doc:`contract <contract:index>` module. It
uses the `asap <https://github.com/abdes/asap>`_ integrated build system and
follows its development workflow.

Parts of the documentation
==========================

:doc:`contract <contract:api>`
------------------------------
  *start here to understand the classes provided by the library and how to use
  them to write contract checks in your code.*

:doc:`contract unit testing <contract-ut:api>`
----------------------------------------------
  *start here to understand how to unit test contract checks even when your unit
  testing framework does not support death tests.*

`Developer Guides <https://abdes.github.io/asap/asap_master/html/project-development/index.html>`_
--------------------------------------------------------------------------------------------------
  *head over to the `asap` project documentation for detailed guides on how to
  build and maintain the different targets in this project.*

Acknowledgements
================

.. figure:: https://executablebooks.org/en/latest/_static/logo-wide.png
  :figclass: margin
  :alt: Executable Books Project
  :name: executable_book_logo

This documentation uses the theme provided by the `Executable Books Project
<https://executablebooks.org/>`_ Project.
