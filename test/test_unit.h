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

void test_new_variable(void);

void test_variable_size(void);

void test_insert_in_variable(void);

void test_remove_from_variable(void);

void test_copy_variable(void);

/* ########################################################## */
/* ##################### TUPLE.C TESTS ###################### */
/* ########################################################## */

void test_new_tuple(void);

void test_tuple_size(void);

void test_tuple_iteration(void);

void test_insert_in_tuple(void);

void test_remove_from_tuple(void);

void test_remove_content(void);

/* ########################################################## */
/* ################## COMPARE_TUPLE.C TESTS ################# */
/* ########################################################## */

void test_compare_tuple(void);

/* ########################################################## */
/* ################### CONSTRAINT.C TESTS ################### */
/* ########################################################## */

void test_new_constraint(void);

void test_insert_constraint_1(void);

void test_insert_constraint_2(void);

/* ########################################################## */
/* ################### INSTANCE.C TESTS ##################### */
/* ########################################################## */

void test_new_instance(void);

void test_add_instance(void);

void test_remove_instance(void);

/* ########################################################## */
/* ####################### DUO.C TESTS ###################### */
/* ########################################################## */

void test_new_duo(void);

/* ########################################################## */
/* ##################### SSTRUCT.C TESTS #################### */
/* ########################################################## */

void test_new_SStruct(void);

void test_add_and_query_SStruct(void);

/* ########################################################## */
/* ##################### COUNTER.C TESTS #################### */
/* ########################################################## */

void test_new_counter(void);

void test_counter_size(void);

void test_counter_iteration(void);

void test_insert_in_counter(void);

void test_remove_from_counter(void);

void test_change_counter(void);

/* ########################################################## */
/* ###################### COUNT.C TESTS ##################### */
/* ########################################################## */

void test_new_count(void);

void test_insert_count(void);

#endif