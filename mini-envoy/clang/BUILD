package(default_visibility = ["//visibility:public"])

load(":cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_suite(
    name = "clang",
    toolchains = {
        # maps the target(toolchain) of a CPU
        "x86_64": ":x86_64_clang",
    },
)

cc_toolchain_config(name = "x86_64_clang_config")

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