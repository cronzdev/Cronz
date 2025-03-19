# brotli (Optional; 1.1+); See https://github.com/google/brotli
option(CRONZ_ENABLE_BROTLI "Enable Brotli support." ON)

if (CRONZ_ENABLE_BROTLI)
    cronz_add_dependency(Brotli 1.1 FALSE)
endif ()

# ws2_32 (Conditional)
if (WIN32)
    cronz_add_dependency_link_library(ws2_32)
endif ()

# zlib (Optional; 1.3+); See https://zlib.net
option(CRONZ_ENABLE_ZLIB "Enable Zlib support." ON)

if (CRONZ_ENABLE_ZLIB)
    cronz_add_dependency(ZLIB 1.3 FALSE)
endif ()
