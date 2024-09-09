# Cronz

Cronz is a header-only networking library.

## Requirements

Any `C++` compiler that supports `C++20` and above.

## Dependencies

There are no must-have dependencies (other than the
[C++ Standard Library](https://en.cppreference.com/w/cpp/standard_library)) required to use this library. Certain
libraries can be optionally added for advanced features.

See the table below for the current support for third-party libraries:

| Library                                            | Version |   Type   | Notes                          |
|:---------------------------------------------------|:-------:|:--------:|:-------------------------------|
| [googletest](https://github.com/google/googletest) |  1.14+  | Optional | Required if tests are enabled. |

## Components

The library consists of the following components. Components currently being built are also listed.

- [X] IP
  - [X] IPv4 parser
  - [X] IPv6 parser
- [X] URL
  - [X] Builder/Parser
  - [ ] Unicode hostname support
- [ ] Session Manager
- [ ] HTTP
  - [ ] Header Manager
  - [ ] Cookie Manager
  - [ ] Server
    - [ ] HTTP/1.0
    - [ ] HTTP/1.1
    - [ ] HTTP/2
    - [ ] HTTP/3
    - [ ] Extensions
      - [ ] Router
  - [ ] Client
      - [ ] HTTP/1.0
      - [ ] HTTP/1.1
      - [ ] HTTP/2
      - [ ] HTTP/3
