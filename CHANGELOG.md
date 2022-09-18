# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

## [4.4.6](http://github.com/abdes/asap/compare/v4.4.5...v4.4.6) (2022-09-18)

### Bug Fixes

* top level install not working properly ([4ac4a31](http://github.com/abdes/asap/commit/4ac4a31001a2ab73764e3d9fe3f279b1e7b25aee))

  `CMAKE_MODULE_PATH` should be reset at the top level project to make sure that
  every sub-project uses its own version of the `cmake` files. Additionally,
  refactor the top-level install code to simplify it and remove the need to call
  a function in the top-level project `cmake` script.

## [4.4.5](http://github.com/abdes/asap/compare/v4.4.4...v4.4.5) (2022-09-18)

### Bug Fixes

* [#20](http://github.com/abdes/asap/issues/20) local install should use CMAKE_INSTALL_PREFIX to set variables ([2e1f1d4](http://github.com/abdes/asap/commit/2e1f1d49baff64dbf47dbbda234886ad2dfdbf1c))
* [#20](http://github.com/abdes/asap/issues/20) use CMAKE_INSTALL_PREFIX to set variables ([2fffd96](http://github.com/abdes/asap/commit/2fffd96392114993bbb72e3f614725f867d61ab1))
* wrong variable used of target name ([04b5343](http://github.com/abdes/asap/commit/04b5343ae541bd6d4f5ae1c1fa2eb85b93e0b5a3))

## [4.4.4](http://github.com/abdes/asap/compare/v4.4.3...v4.4.4) (2022-09-18)

### Bug Fixes

* wrong variable used for target name ([04b5343](http://github.com/abdes/asap/commit/04b5343ae541bd6d4f5ae1c1fa2eb85b93e0b5a3))

## [4.4.3](http://github.com/abdes/asap/compare/v4.4.2...v4.4.3) (2022-09-18)

### Bug Fixes

* [#19](http://github.com/abdes/asap/issues/19) use generator expressions instead of CMAKE_BUILD_TYPE ([857d299](http://github.com/abdes/asap/commit/857d2997d4ec6c879036e10234b8baf907e91089))

  Code that checks CMAKE_BUILD_TYPE to set specific compiler flags or defines is
  problematic. Generator expressions should be used instead to handle
  configuration-specific logic correctly, regardless of the generator used.

* use cmake-format extension default behavior ([a5d5c5e](http://github.com/abdes/asap/commit/a5d5c5eae39e4d3d0094c00848cfe777d331a219))

  No need to force the `cmake-format` config file location as the command is run
  in the workspace root by default and it will look for and find the config file
  named `cmake-format.yaml`.

## [4.4.2](http://github.com/abdes/asap/compare/v4.4.1...v4.4.2) (2022-09-16)

### Bug Fixes

* [#13](http://github.com/abdes/asap/issues/13) move "caexcludepath" to dev-windows and exclude CPM cache ([0571714](http://github.com/abdes/asap/commit/0571714e9436bfec26d6450b5bc37f2a5f478a55))
* [#14](http://github.com/abdes/asap/issues/14) upgrade CPM to 0.35.6
  ([695414b](http://github.com/abdes/asap/commit/695414b8e66d4d42d7ef3aaef3c6a4b8399d16c2))
* [#15](http://github.com/abdes/asap/issues/15) get target type before testing it ([b8bd378](https://github.com/abdes/asap/commit/b8bd378f52bc131b84c13b08cfe70d649e9d9be0))
* [#16](http://github.com/abdes/asap/issues/16) use CMAKE_CURRENT_SOURCE_DIR instead of CMAKE_SOURCE_DIR for cmake includes ([4ac6928](http://github.com/abdes/asap/commit/4ac6928fc2a0bf806bbcaa3bea898b5ff018a164))
* [#17](http://github.com/abdes/asap/issues/17) git should not be required ([2c76104](http://github.com/abdes/asap/commit/2c761046d0801f643aa0215d34f2795ff0093dfc))
* [#18](http://github.com/abdes/asap/issues/18) enforce end of line to LF ([943ae47](http://github.com/abdes/asap/commit/943ae479e09de999c324a9cfe3bbf8d688d255a3))

## [1.0.2](http://github.com/abdes/asap/compare/v1.0.1...v1.0.2) (2022-08-20)

### Features

* add ccache support to dev container
  ([202c27a](http://github.com/abdes/asap/commit/202c27a628f7f35ae17f2df91c1d95f67360abea))
* make ccache usable on all platforms
  ([412730f](http://github.com/abdes/asap/commit/412730f86679d7ccd350cadf5649b7a489376cae))

### Bug Fixes

* [#10](http://github.com/abdes/asap/issues/10) no more template export header
  ([dd8ffd5](http://github.com/abdes/asap/commit/dd8ffd5a8f36340963349c7ebcb7c1713c2f880a))
* [#11](http://github.com/abdes/asap/issues/11) refactor compiler options
  management
  ([78ae493](http://github.com/abdes/asap/commit/78ae4933f2e263a55f6537e66347c6b11a24b961))
* [#12](http://github.com/abdes/asap/issues/12) disable used-but-marked-unused
  ([6d42d83](http://github.com/abdes/asap/commit/6d42d83bfdd16123f05a69726058dc5f103143be))
* [#5](http://github.com/abdes/asap/issues/5) update cmake/common to latest
  ([5034b22](http://github.com/abdes/asap/commit/5034b22d39e5cb54acd51baa0bf815dbdd82093b))
* [#9](http://github.com/abdes/asap/issues/9) remove no longer used function
  ([5a7416f](http://github.com/abdes/asap/commit/5a7416f9563aae303d68ca2bb878fef97fbb7130))
* **#6:** properly setup install layout
  ([71fd5d5](http://github.com/abdes/asap/commit/71fd5d5ee6f4694a8d7d6994e3a09d5b2f18ce24)),
  closes [#6](http://github.com/abdes/asap/issues/6)
* **#7:** add `build` and `ops` commit types
  ([0d9187e](http://github.com/abdes/asap/commit/0d9187e9d20788d3f0c5048bcb4deca4cf5280e3)),
  closes [#7](http://github.com/abdes/asap/issues/7)
* **#8:** add standard ccov excluded directories by default
  ([a8aabb3](http://github.com/abdes/asap/commit/a8aabb31d3ea6b0c5a50e13bf366f092ca724537)),
  closes [#8](http://github.com/abdes/asap/issues/8)
* add alaises used by cmake common functions
  ([9c33906](http://github.com/abdes/asap/commit/9c339069acd9ab6355f8156f2e8eaf81c382342c))
* alias variable to enable/disable building tests
  ([3992b0f](http://github.com/abdes/asap/commit/3992b0f7d500e653532bd0f206489058d99ad2d0))
* incorrect dll export preprocessor macros
  ([4c077ee](http://github.com/abdes/asap/commit/4c077ee0c0b608ee83d0a50943206016c507033f))
* typo in variable name to enable/disable building tests
  ([9950fe2](http://github.com/abdes/asap/commit/9950fe2dcbe6c284e9ce32ce6a455e4a3a499ec4))
* use only white-listed properties for interface library
  ([227de02](http://github.com/abdes/asap/commit/227de026878beb9dd9679d0cad12cf25bce16c4a))

### Documentation

* add badge for OpenSSF best practices
  ([26c01c8](http://github.com/abdes/asap/commit/26c01c8bcf98c6b47e6622dea91a6c6e10bc978c))
* add CPM as preferred way of managing third party deps
  ([5a33f70](http://github.com/abdes/asap/commit/5a33f70a15a64c84f0a13b4286460f9df20459a5))
* add tutorial videos
  ([cb13248](http://github.com/abdes/asap/commit/cb13248244cddd0dc2c187893556fad7aa4f08b7))
* fix thumbnail and links of project docs video
  ([1a6269e](http://github.com/abdes/asap/commit/1a6269eef8999504aba8105d4c446a93e41c988b))
* how to report security vulnerabilities
  ([46426e9](http://github.com/abdes/asap/commit/46426e9d44f3c4e8ee0b3fdd98e2ee56d13f8890))
* improve the key features section
  ([79119ba](http://github.com/abdes/asap/commit/79119ba52f578a28dfdeb1ce59bba67c3fbcd3c1))
* include build status badges for all branches
  ([2b98ae1](http://github.com/abdes/asap/commit/2b98ae11ace8fa756c825686018a3a328ce27eca))
* revamp the project README
  ([e72c4c3](http://github.com/abdes/asap/commit/e72c4c3288d565b34b137ab785abe90370052258))
* rewrite the contributing section
  ([c7e39c4](http://github.com/abdes/asap/commit/c7e39c4cfa6033aac42befe5ed994089e601b6a0))
* update instructions for repo from template scenario
  ([1cafdb5](http://github.com/abdes/asap/commit/1cafdb57f86a4b61a736b3411791ae96ca684f33))
* update project docs video
  ([c7f79fc](http://github.com/abdes/asap/commit/c7f79fc64900cfa9ec3d2466300d1d32830b32f1))

## [1.0.1](http://github.com/abdes/asap/compare/v1.0.0...v1.0.1) (2022-03-15)

* refactor build to use CPM for cmake dependencies and speedup build with
  ccache.

## 1.0.0 (2022-03-08)

This is the initial version of the contract checking library for C++ and its
optional helper for unit testing contracts without death tests. For a full
documentation of what is available refer to the [project
docs](https://asap-projects.github.io/asap-contract/).
