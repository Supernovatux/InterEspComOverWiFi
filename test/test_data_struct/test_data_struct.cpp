#include <unity.h>
#include <data_struct.hpp>
void test_WithSaneDefaults(){
    devices test_Dev = devices();
    test_Dev.saneDefaults();
    TEST_ASSERT_EQUAL(0, test_Dev.nodes[0].id);
    TEST_ASSERT_EQUAL(0, test_Dev.nodes[0].sensors[0].id);
    String doc = "";
    test_Dev.devicesTotext(doc);
    TEST_ASSERT_EQUAL_STRING("0;0,1;1,1;2,1;3,1;4,1;|1;0,1;1,1;2,1;3,1;4,1;|",doc.c_str());
}
void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_WithSaneDefaults);
    UNITY_END();
}
int main(int argc, char **argv) {
    RUN_UNITY_TESTS();
    return 0;
}