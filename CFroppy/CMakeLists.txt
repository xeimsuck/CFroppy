# Source
file(GLOB_RECURSE CFroppy_SOURCE
        "source/*.cpp")

# Build
## CFroppy (cfp)
add_executable(cfp ${CFroppy_SOURCE})