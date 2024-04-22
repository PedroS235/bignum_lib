#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Functions to add test cases from other files
void bignum_compare_tests_to_suite(CU_pSuite suite);  // From test_bignum_compare.c
void bignum_add_tests_to_suite(CU_pSuite suite);      // From test_bignum_add.c
void bignum_sub_tests_to_suite(CU_pSuite suite);      // From test_bignum_sub.c
void bignum_mul_tests_to_suite(CU_pSuite suite);      // From test_bignum_mul.c
void bignum_div_tests_to_suite(CU_pSuite suite);      // From test_bignum_div.c
void bignum_mod_tests_to_suite(CU_pSuite suite);      // From test_bignum_remainder.c
void bignum_addmod_tests_to_suite(CU_pSuite suite);   // From test_bignum_add.c
void bignum_multmod_tests_to_suite(CU_pSuite suite);  // From test_bignum_add.c
void bignum_expmod_tests_to_suite(CU_pSuite suite);   // From test_bignum_expmod.c
void bignum_extended_gcd_tests_to_suite(
    CU_pSuite suite);  // From test_bignum_extended_gcd.c
void bignum_inversemod_tests_to_suite(
    CU_pSuite suite);  // From test_bignum_inversemod.c

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) return CU_get_error();

    CU_pSuite compare_suite = CU_add_suite("Comparison Tests", NULL, NULL);
    if (NULL == compare_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_compare_tests_to_suite(compare_suite);

    CU_pSuite add_suite = CU_add_suite("Addition Tests", NULL, NULL);
    if (NULL == add_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_add_tests_to_suite(add_suite);

    CU_pSuite subtract_suite = CU_add_suite("Subtraction Tests", NULL, NULL);
    if (NULL == subtract_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_sub_tests_to_suite(subtract_suite);

    CU_pSuite multiplication_suite = CU_add_suite("Multiplication Tests", NULL, NULL);
    if (NULL == multiplication_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_mul_tests_to_suite(multiplication_suite);

    CU_pSuite division_suite = CU_add_suite("Division Tests", NULL, NULL);
    if (NULL == division_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_div_tests_to_suite(division_suite);

    CU_pSuite mod_suite = CU_add_suite("mod Tests", NULL, NULL);
    if (NULL == mod_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_mod_tests_to_suite(mod_suite);

    CU_pSuite addmod_suite = CU_add_suite("Addition with mod Tests", NULL, NULL);
    if (NULL == addmod_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_addmod_tests_to_suite(addmod_suite);

    CU_pSuite multmod_suite = CU_add_suite("Multiplication with mod Tests", NULL, NULL);
    if (NULL == multmod_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_multmod_tests_to_suite(multmod_suite);

    CU_pSuite expmod_suite = CU_add_suite("Modular Exponentiation Tests", NULL, NULL);
    if (NULL == expmod_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_expmod_tests_to_suite(expmod_suite);

    CU_pSuite extended_gcd_suite = CU_add_suite("Extended GCD Tests", NULL, NULL);
    if (NULL == extended_gcd_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_extended_gcd_tests_to_suite(extended_gcd_suite);

    CU_pSuite inversemod_suite = CU_add_suite("Inverse Mod Tests", NULL, NULL);
    if (NULL == inversemod_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    bignum_inversemod_tests_to_suite(inversemod_suite);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
