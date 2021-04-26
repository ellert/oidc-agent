#include "tc_setJSONValue.h"

#include "utils/json.h"
#include "utils/memory.h"
#include "utils/stringUtils.h"

START_TEST(test_update) {
  cJSON* cjson1 = generateJSONObject("key", cJSON_String, "value1", "otherKey",
                                     cJSON_String, "otherValue", NULL);
  cJSON* cjson2 = generateJSONObject("key", cJSON_String, "value2", "otherKey",
                                     cJSON_String, "otherValue", NULL);
  ck_assert_int_eq(setJSONValue(cjson1, "key", "value2"), OIDC_SUCCESS);
  char* error_msg =
      oidc_sprintf("cjson1 and cjson2 not equal: cjson1 = '%s', cjson2 = '%s'",
                   cJSON_Print(cjson1), cJSON_Print(cjson2));
  // Ignore -Werror=format-security as we can be sure our string does not
  // contain any user input
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat-security"
  ck_assert_msg(cJSON_Compare(cjson1, cjson2, 1), error_msg);
  #pragma GCC diagnostic push
}
END_TEST

START_TEST(test_insert) {
  cJSON* cjson1 =
      generateJSONObject("otherKey", cJSON_String, "otherValue", NULL);
  cJSON* cjson2 = generateJSONObject("key", cJSON_String, "value2", "otherKey",
                                     cJSON_String, "otherValue", NULL);
  ck_assert_int_eq(setJSONValue(cjson1, "key", "value2"), OIDC_SUCCESS);
  char* error_msg =
      oidc_sprintf("cjson1 and cjson2 not equal: cjson1 = '%s' cjson2 = '%s'",
                   cJSON_Print(cjson1), cJSON_Print(cjson2));
  // Ignore -Werror=format-security as we can be sure our string does not
  // contain any user input
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat-security"
  ck_assert_msg(cJSON_Compare(cjson1, cjson2, 1), error_msg);
  #pragma GCC diagnostic push
}
END_TEST

START_TEST(test_cjsonNULL) {
  ck_assert_int_eq(setJSONValue(NULL, "key", "value2"), OIDC_EARGNULLFUNC);
}
END_TEST

START_TEST(test_keyNULL) {
  ck_assert_int_eq(setJSONValue((cJSON*)"dummy", NULL, "value2"),
                   OIDC_EARGNULLFUNC);
}
END_TEST

START_TEST(test_valueNULL) {
  ck_assert_int_eq(setJSONValue((cJSON*)"dummy", "key", NULL),
                   OIDC_EARGNULLFUNC);
}
END_TEST

TCase* test_case_setJSONValue() {
  TCase* tc = tcase_create("setJSONValue");
  tcase_add_test(tc, test_update);
  tcase_add_test(tc, test_insert);
  tcase_add_test(tc, test_cjsonNULL);
  tcase_add_test(tc, test_keyNULL);
  tcase_add_test(tc, test_valueNULL);
  return tc;
}
