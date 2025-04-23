/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:19:16 by megardes          #+#    #+#             */
/*   Updated: 2025/04/23 11:01:06 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "libft.h"

#define TEST(func, ...) test_##func(__VA_ARGS__)

// Helper functions
void print_memory(const void *ptr, size_t size) {
    const unsigned char *p = ptr;
    for (size_t i = 0; i < size; i++) printf("%02x ", p[i]);
    printf("\n");
}

void print_test_result(const char *func_name, int passed, const char *comment) {
    printf("%-8s: %s %s\n", func_name, passed ? "✅ PASS" : "❌ FAIL", comment);
}

// Test functions
void test_isalpha() {
    int passed = 1;
    for (int c = -1; c <= 255; c++) {
        if (ft_isalpha(c) != isalpha(c)) {
            passed = 0;
            break;
        }
    }
    print_test_result("isalpha", passed, "");
}

void test_isdigit() {
    int passed = 1;
    for (int c = -1; c <= 255; c++) {
        if (isdigit(c) != ft_isdigit(c)) {
            passed = 0;
            break;
        }
    }
    print_test_result("isdigit", passed, "");
}

// [...] Similar tests for isalnum, isascii, isprint

void test_strlen() {
    struct { const char *s; size_t len; } tests[] = {
        {"hello", 5}, {"", 0}, {"1234567890", 10}, {NULL, 0}
    };
    int passed = 1;
    for (int i = 0; tests[i].s; i++) {
        if (ft_strlen(tests[i].s) != tests[i].len) {
            passed = 0;
            break;
        }
    }
    print_test_result("strlen", passed, "");
}

// [...] Tests for all other functions following the same pattern

int main() {
    printf("=== Testing ft_* functions ===\n\n");
    
    TEST(isalpha);
	printf("%d", isalpha(65));
    /*TEST(isdigit);
    TEST(isalnum);
    TEST(isascii);
    TEST(isprint);
    TEST(strlen);
    TEST(memset);
    TEST(bzero);
    TEST(memcpy);
    TEST(memmove);
    TEST(strlcpy);
    TEST(strlcat);
    TEST(toupper);
    TEST(tolower);
    TEST(strchr);
    TEST(strrchr);
    TEST(strncmp);
    TEST(memchr);
    TEST(memcmp);
    TEST(strnstr);
    TEST(atoi);
    */
    printf("\n=== Tests complete ===\n");
    return 0;
}