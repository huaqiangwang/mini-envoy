# bazel

Other like CMake, [bazel](https://www.bazel.build/) retains enough mystery, even from its name. 

bazel is the compiling tool that used by a small group of projects, generally by google. It invents several concepts such as `workspace`, `target`, `repository` ... , which are not hard to understand. But there is no enough confidence in reading source code of big project.

To eliminate the un-confident mood, you should be quite familiar with official pages, listed in:
- [Concepts and Terminology](https://docs.bazel.build/versions/5.0.0/build-ref.html)
- [overview](https://docs.bazel.build/versions/5.0.0/be/overview.html)


## Build with clang

Bazel natively supports gcc for compiling and linking. It treats llvm toolchain as a general toolchain that builds binaries for other hardware CPU platform. You have to specify each tool that involved in the process, the comping, linking, and binary manipulating tools.

Refer to [page](https://docs.bazel.build/versions/main/tutorial/cc-toolchain-config.html)

### Small fix to the cross-compiling guide page

The ':empty' target should be replaced with ":x86_64_clang_config" target.

```
cc_toolchain(
    name = "x86_64_clang",
    toolchain_identifier = "x86_64_clang",
    toolchain_config = ":x86_64_clang_config",
    all_files = ":x86_64_clang_config",
    #all_files = ":empty",
    compiler_files = ":x86_64_clang_config",
    #compiler_files = ":empty",
    dwp_files = ":x86_64_clang_config",
    linker_files = ":x86_64_clang_config",
    objcopy_files = ":x86_64_clang_config",
    strip_files = ":x86_64_clang_config",
    supports_param_files = 0,
)
```

### command using clang:

```shell
bazel build --config=clang_config //source/server:mini_envoy
```
With the output:

> huaqiang@jfz1r01h09:~/2022/mini-envoy/mini-envoy$ bazel run --config=clang_config //source/server:mini_envoy
> INFO: Analyzed target //source/server:mini_envoy (0 packages loaded, 0 targets configured).
> INFO: Found 1 target...
> Target //source/server:mini_envoy up-to-date:
>   bazel-bin/source/server/mini_envoy
> INFO: Elapsed time: 0.102s, Critical Path: 0.00s
> INFO: 1 process: 1 internal.
> INFO: Build completed successfully, 1 total action
> INFO: Build completed successfully, 1 total action
> Mini-Envoy Project
