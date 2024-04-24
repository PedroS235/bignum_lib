cmake_minimum_required(VERSION 3.10)
project(BignumLib)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Enable the generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES 
    src/bignum/bignum.c
    src/bignum/common.c
    src/bignum/bitwise.c
    src/bignum/arithmetic.c
    src/bignum/modular_arithmetic.c
    src/bignum/random.c
)

set(TEST_SOURCES 
    test/arithmetic/test_bignum_add.c
    test/arithmetic/test_bignum_addmod.c
    test/arithmetic/test_bignum_compare.c
    test/arithmetic/test_bignum_div.c
    test/arithmetic/test_bignum_expmod.c
    test/arithmetic/test_bignum_extended_gcd.c
    test/arithmetic/test_bignum_inverse_mod.c
    test/arithmetic/test_bignum_mod.c
    test/arithmetic/test_bignum_mul.c
    test/arithmetic/test_bignum_mulmod.c
    test/arithmetic/test_bignum_subtract.c
)

include_directories(${PROJECT_SOURCE_DIR}/include)
 

# Mai executable
add_executable(bignum src/main.c ${SOURCES})

# Test executable
add_executable(bignum_test test/main.c ${SOURCES} ${TEST_SOURCES})
target_link_libraries(bignum_test -lcunit)

# enable_testing()
# add_test(NAME bignumLibTest COMMAND bignumLibTest)

