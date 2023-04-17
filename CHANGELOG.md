# Changelog

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
