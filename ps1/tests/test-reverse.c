#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../bmp.h"

void test_invokeWithNull_returnNull()
{
    char* result = reverse(NULL);

    assert(result == NULL);
}

void test_invokeWithEmptyString_returnEmptyString()
{
    char* result = reverse("");

    assert(result != NULL && "Result can't be NULL.");
    assert(!strcmp(result, ""));
}

void test_invokeWithString_returnReversedString()
{
    const char* input = "jano";
    const char* expected = "ONAJ";

    char* result = reverse(input);

    assert(result != NULL && "Result can't be NULL.");
    assert(!strcmp(result, expected));

    free(result);
}

int main()
{
    printf("Starting tests for reverse()\n");

    test_invokeWithNull_returnNull();
    test_invokeWithEmptyString_returnEmptyString();
    test_invokeWithString_returnReversedString();

    printf("All tests passed\n");
}