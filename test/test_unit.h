/*

Copyright (c) 2019-2020, Adrien BLASSIAU and Corentin JUVIGNY

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

/** @file test_unit.h
 *
 * @brief Unit tests of the projects
 *
 */

#ifndef _TEST_UNIT_
#define _TEST_UNIT_

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"



/**
 * @brief	This function inits all tests
 * @return  an integer
 */
int init_test(void);


/* ########################################################## */
/* #################### DOMAIN.C TESTS ###################### */
/* ########################################################## */

void test_new_domain(void);

void test_get_domain_size(void);

void test_domain_iteration(void);

void test_insert_in_domain(void);

void test_remove_from_domain(void);

/* ########################################################## */
/* ################### VARIABLE.C TESTS ##################### */
/* ########################################################## */

void test_new_variables(void);

void test_variables_size(void);

void test_variables_iteration(void);

void test_insert_in_variables(void);

void test_remove_from_variables(void);

void test_remove_value(void);

/* ########################################################## */
/* ################## COMPARE_TUPLE.C TESTS ################# */
/* ########################################################## */

void test_compare_tuple(void);

/* ########################################################## */
/* ################### CONSTRAINT.C TESTS ################### */
/* ########################################################## */

#endif