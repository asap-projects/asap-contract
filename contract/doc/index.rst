#############################
ASAP contract's documentation
#############################

.. toctree::
   :maxdepth: 2
   :hidden:

   API <api>
   Build time configuration <build>
   License <license>
   Version <version>

Welcome! This is the documentation for the *contract* module, part of the *asap*
project.

Contracts are usually expressed in the form of preconditions, post-conditions
and assertions. Some programming languages have built-in support for contracts.
So far, the closest in C++ is assertions. But assertions are not expressive and
are not consistent. This simple API is intended at offering some rudimentary
support of contract programming in the form of preconditions, post-conditions
and assertions with three levels of contract enforcement at build time: `off`,
`default` and `audit`, while waiting for it to become part of the C++ language
in a near future.

Alternative libraries and references
====================================

- `Contract Checking in C++: A (long-term) Road Map
  <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1332r0.txt>`_.

- `libcontract <https://github.com/alexeiz/contract>`_ Library to support
   contract programming in C++11.

- `Boost.Contract
  <https://www.boost.org/doc/libs/1_78_0/libs/contract/doc/html/index.html>`_
  implements contract programming (a.k.a., Design by Contract or DbC) [1] for
  the C++ programming language..

- `N3753 <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3753.pdf>`_,
  "Centralized Defensive-Programming Support for Narrow Contracts" proposed for
  C++14 Standard.

- `N1962 <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1962.html>`_,
  "Proposal to add Contract Programming to C++ (revision 4)" (not adopted for
  C++11 Standard).


Parts of the documentation
==========================

:doc:`API reference <api>`
------------------------------
*check this out to see the documentation of classes, macros, etc. offered by
this module*

:doc:`Build time configuration <build>`
---------------------------------------
*refer to this document to understand how you can set the bahvior of this
library with regard to contract enforcement by using a specific compiler
definition at build time*
