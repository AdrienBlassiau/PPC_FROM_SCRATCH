/*

Copyright (c) 2019-2020, Adrien BLASSIAU

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

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "test_unit.h"

#include "../src/include.h"
#include "../src/tools.h"
#include "../src/domain.h"
#include "../src/variable.h"
#include "../src/tuple.h"
#include "../src/compare_tuple.h"
#include "../src/constraint.h"
#include "../src/instance.h"

int setup(void)  { return 0; }
int teardown(void) { return 0; }

int init_test(void){

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite suite1 = CU_add_suite("domain_test",setup,teardown);

	if((NULL==CU_add_test(suite1, "Test new domain", test_new_domain))||
		(NULL==CU_add_test(suite1, "Test domain size", test_get_domain_size))||
		(NULL==CU_add_test(suite1, "Test domain it", test_domain_iteration))||
		(NULL==CU_add_test(suite1, "Test insert", test_insert_in_domain))||
		(NULL==CU_add_test(suite1, "Test remove", test_remove_from_domain)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite2 = CU_add_suite("variable_test",setup,teardown);

	if((NULL==CU_add_test(suite2, "Test new variable", test_new_variable))||
		(NULL==CU_add_test(suite2, "Test var size", test_variable_size))||
		(NULL==CU_add_test(suite2, "Test insert", test_insert_in_variable))||
		(NULL==CU_add_test(suite2, "Test rm", test_remove_from_variable)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite3 = CU_add_suite("tuple_test",setup,teardown);

	if((NULL==CU_add_test(suite3, "Test new tuple", test_new_tuple))||
		(NULL==CU_add_test(suite3, "Test tup size", test_tuple_size))||
		(NULL==CU_add_test(suite3, "Test tup it", test_tuple_iteration))||
		(NULL==CU_add_test(suite3, "Test insert", test_insert_in_tuple))||
		(NULL==CU_add_test(suite3, "Test rm", test_remove_from_tuple))||
		(NULL==CU_add_test(suite3, "Test rm content", test_remove_content)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite4 = CU_add_suite("tuple_test",setup,teardown);

	if((NULL==CU_add_test(suite4, "Test compare tuple", test_compare_tuple)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite5 = CU_add_suite("tuple_test",setup,teardown);

	if((NULL==CU_add_test(suite5, "Test new cons", test_new_constraint))||
		(NULL==CU_add_test(suite5, "Test ins 1", test_insert_constraint_1))||
		(NULL==CU_add_test(suite5, "Test ins 2", test_insert_constraint_2)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite6 = CU_add_suite("tuple_test",setup,teardown);

	if((NULL==CU_add_test(suite6, "Test new inst", test_new_instance))||
		(NULL==CU_add_test(suite6, "Test add inst", test_add_instance))||
		(NULL==CU_add_test(suite6, "Test rm inst", test_remove_instance)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());
	CU_cleanup_registry();

	return 0;
}


/* ########################################################## */
/* #################### DOMAIN.C TESTS ###################### */
/* ########################################################## */

void test_new_domain(void){

	Pdomain d = new_domain();

	CU_ASSERT_NOT_EQUAL(d,NULL);

	free_domain(d);
}

void test_get_domain_size(void){

	Pdomain d = new_domain();
	int size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,0);

	int val1 = 1;
	int val2 = 2;
	insert_in_domain(d,&val1);
	insert_in_domain(d,&val2);

	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,2);

	free_domain(d);
}

void test_domain_iteration(void){

	Pdomain d = new_domain();
	int value;
	int tab[4] = {1,2,5,6};
	int i = 0;
	int size;

	for (i = 0; i < 4; ++i)
	{
		insert_in_domain(d,&tab[i]);
	}

	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,4);

	for (i = 0; i < 4; ++i)
	{
		CU_ASSERT_NOT_EQUAL(query_domain(d,&tab[i]),0);
	}

	begin_domain_iteration(d);

	i = 0;
	while(domain_can_iterate(d)){
		value = get_current_value(d);
		CU_ASSERT_EQUAL(value,tab[i]);
		i++;
	};

	begin_domain_iteration(d);

	i = 0;
	while(domain_can_iterate(d)){
		value = get_current_value(d);
		CU_ASSERT_EQUAL(value,tab[i]);
		i++;
	};

	// print_domain(d);
	free_domain(d);
}

void test_insert_in_domain(void){
	Pdomain d = new_domain();
	int tab[6] = {1,2,5,6,12,23};
	int i = 0;
	int size;

	for (i = 0; i < 6; ++i)
	{
		insert_in_domain(d,&tab[i]);
	}

	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,6);

	for (i = 0; i < 4; ++i)
	{
		CU_ASSERT_NOT_EQUAL(query_domain(d,&tab[i]),0);
	}

	// print_domain(d);
	free_domain(d);
}

void test_remove_from_domain(void){
	Pdomain d = new_domain();
	int tab[6] = {1,2,5,6,12,23};
	int i = 0;
	int size;

	for (i = 0; i < 6; ++i)
	{
		insert_in_domain(d,&tab[i]);
	}

	int val1 = 6;
	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,val1);

	int val2 = 2;
	remove_from_domain(d,&val2);
	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,5);

	int val3 = 1;
	remove_from_domain(d,&val3);
	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,4);

	int val4 = 10;
	remove_from_domain(d,&val4);
	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,4);

	int val5 = 5;
	remove_from_domain(d,&val5);
	int val6 = 6;
	remove_from_domain(d,&val6);
	int val7 = 12;
	remove_from_domain(d,&val7);
	int val8 = 23;
	remove_from_domain(d,&val8);
	size = get_domain_size(d);
	CU_ASSERT_EQUAL(size,0);
	free_domain_bis(d);
}

/* ########################################################## */
/* ################### VARIABLE.C TESTS ##################### */
/* ########################################################## */

void test_new_variable(void){
	int size = 10;
	Pvariable v = new_variable(size);

	CU_ASSERT_NOT_EQUAL(v,NULL);

	free_variable(v);
}

void test_variable_size(void){
	int i;
	int size = 2;
	Pvariable v = new_variable(size);
	int size_result = get_variable_number(v);

	CU_ASSERT_EQUAL(size_result,size);

	Pdomain d1 = new_domain();
	int tab1[6] = {1,2,5,6,12,23};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[6] = {1,2,5,6,12,23};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d2,&tab2[i]);

	char var_name1[100] = "test1";
	insert_variable(v,0,var_name1,d1);

	char var_name2[100] = "test2";
	insert_variable(v,1,var_name2,d2);

	CU_ASSERT_STRING_EQUAL(get_variable_name(v,0),var_name1);
	CU_ASSERT_STRING_EQUAL(get_variable_name(v,1),var_name2);
	// print_variable(v);

	free_variable(v);
}


void test_insert_in_variable(void){
	int i;
	int size = 3;

	Pvariable v = new_variable(size);

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i)
		insert_in_domain(d2,&tab2[i]);

	Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d3,&tab3[i]);

	char var_name1[100] = "test1";
	insert_variable(v,0,var_name1,d1);

	char var_name2[100] = "test2";
	insert_variable(v,1,var_name2,d2);

	char var_name3[100] = "test3";
	insert_variable(v,2,var_name3,d3);


	CU_ASSERT_EQUAL(get_variable_index(v,var_name1),0);
	CU_ASSERT_EQUAL(get_variable_index(v,var_name2),1);
	CU_ASSERT_EQUAL(get_variable_index(v,var_name3),2);

	int val = 1;
	int res = query_value_of_variable_domain(v,0,&val);
	CU_ASSERT_EQUAL(res,1);

	val = 7;
	res = query_value_of_variable_domain(v,0,&val);
	CU_ASSERT_EQUAL(res,0);

	// print_variable(v);
	free_variable(v);
}

void test_remove_from_variable(void){
	int i;
	int size = 3;
	Pvariable v = new_variable(size);

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i)
		insert_in_domain(d2,&tab2[i]);

	Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d3,&tab3[i]);

	char var_name1[256] = "test1";
	insert_variable(v,0,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variable(v,1,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variable(v,2,var_name3,d3);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,3);

	int val = 1;
	int re1 = remove_value_of_variable_domain(v,0,&val);
	CU_ASSERT_EQUAL(re1,1);

	val = 1;
	re1 = remove_value_of_variable_domain(v,0,&val);
	CU_ASSERT_EQUAL(re1,0);

	// print_variable(v);
	free_variable(v);
}

/* ########################################################## */
/* ##################### TUPLE.C TESTS ###################### */
/* ########################################################## */

void test_new_tuple(void){

	Ptuple t = new_tuple();

	CU_ASSERT_NOT_EQUAL(t,NULL);

	free_tuple(t);
}

void test_tuple_size(void){
	int i;
	Ptuple t = new_tuple();
	int size = get_tuple_number(t);

	CU_ASSERT_EQUAL(size,0);

	Pdomain d1 = new_domain();
	int tab1[6] = {1,2,5,6,12,23};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[6] = {1,2,5,6,12,23};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d2,&tab2[i]);


	int content1 = 1;
	insert_tuple(t,&content1,d1);

	int content2 = 2;
	insert_tuple(t,&content2,d2);

	size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,2);

	free_tuple(t);
}

void test_tuple_iteration(void){
	int i,key;
	Pdomain value;
	Ptuple t = new_tuple();
	int data_size[3] = {4,2,6};

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i)
		insert_in_domain(d2,&tab2[i]);

	Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d3,&tab3[i]);

	int content1 = 0;
	insert_tuple(t,&content1,d1);

	int content2 = 1;
	insert_tuple(t,&content2,d2);

	int content3 = 2;
	insert_tuple(t,&content3,d3);

	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);
	begin_tuple_iteration(t);
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);

	int size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,3);

	i = 0;
	while(tuple_can_iterate(t)){
		value = get_tuple_current_value(t);
		key = get_tuple_current_key(t);

		CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
		CU_ASSERT_EQUAL(key,i);

		get_next_tuple(t);
		i++;
	}
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);

	//test good interanm memory free.
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);
	begin_tuple_iteration(t);
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);

	size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,3);

	i = 0;
	while(tuple_can_iterate(t)){
		value = get_tuple_current_value(t);
		key = get_tuple_current_key(t);

		CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
		CU_ASSERT_EQUAL(key,i);

		get_next_tuple(t);
		i++;
	}
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);

	free_tuple(t);
}

void test_insert_in_tuple(void){
	int i;
	Ptuple t = new_tuple();
	int data_size[3] = {4,2,6};

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i)
		insert_in_domain(d2,&tab2[i]);

	Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d3,&tab3[i]);

	int content1 = 1;
	insert_tuple(t,&content1,d1);

	int content2 = 2;
	insert_tuple(t,&content2,d2);

	int content3 = 3;
	insert_tuple(t,&content3,d3);

	Pdomain d11 = query_tuple(t,&content1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_tuple(t,&content2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_tuple(t,&content3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	free_tuple(t);
}

void test_remove_from_tuple(void){
	int i,size;
	Ptuple t = new_tuple();
	int data_size[3] = {4,2,6};

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i)
		insert_in_domain(d2,&tab2[i]);

	Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d3,&tab3[i]);

	int content1 = 1;
	insert_tuple(t,&content1,d1);

	int content2 = 2;
	insert_tuple(t,&content2,d2);

	int content3 = 3;
	insert_tuple(t,&content3,d3);

	Pdomain d11 = query_tuple(t,&content1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_tuple(t,&content2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_tuple(t,&content3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	size = get_tuple_number(t);

	CU_ASSERT_EQUAL(size,3);

	remove_tuple(t,&content3);
	CU_ASSERT_EQUAL(query_tuple(t,&content3),NULL);

	size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,2);

	remove_tuple(t,&content1);
	CU_ASSERT_EQUAL(query_tuple(t,&content1),NULL);

	size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,1);

	remove_tuple(t,&content2);
	CU_ASSERT_EQUAL(query_tuple(t,&content2),NULL);

	size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,0);

	free_tuple(t);
}

void test_remove_content(void){
	int i,size;
	Ptuple t = new_tuple();

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i)
		insert_in_domain(d2,&tab2[i]);

	Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d3,&tab3[i]);

	int content1 = 1;
	insert_tuple(t,&content1,d1);

	int content2 = 2;
	insert_tuple(t,&content2,d2);

	int content3 = 3;
	insert_tuple(t,&content3,d3);

	size = get_tuple_number(t);
	CU_ASSERT_EQUAL(size,3);

	int val_test = 8;
	remove_value_of_content_domain(t,&content3,&val_test);

	Pdomain d13 = query_tuple(t,&content3);
	size = get_domain_size(d13);

	CU_ASSERT_EQUAL(size,5);

	free_tuple_bis(t);
}

/* ########################################################## */
/* ################## COMPARE_TUPLE.C TESTS ################# */
/* ########################################################## */

void test_compare_tuple(void){
	char *tuple1[2] = {"A", "B"};
	char *tuple2[2] = {"A", "C"};
	char *tuple3[2] = {"C", "D"};
	char *tuple4[2] = {"A", "B"};

	CU_ASSERT_EQUAL(tuple_compare(tuple1,tuple2),-1);
	CU_ASSERT_EQUAL(tuple_compare(tuple2,tuple1),1);
	CU_ASSERT_EQUAL(tuple_compare(tuple1,tuple3),-1);
	CU_ASSERT_EQUAL(tuple_compare(tuple1,tuple4),0);
}

/* ########################################################## */
/* ################### CONSTRAINT.C TESTS ################### */
/* ########################################################## */

void test_new_constraint(void){
	int size = 10;
	Pconstraint c = new_constraint(size);

	CU_ASSERT_NOT_EQUAL(c,NULL);
	// print_constraint(c);
	free_constraint(c);
}

void test_insert_constraint_1(void){
	int size = 4;
	Pconstraint c = new_constraint(size);
	int i;
	int var_name1 = 0;
	int var_name2 = 1;
	int var_name3 = 2;
	int var_name4 = 3;

	int content[10] = {0,1,2,3,4,5,6,7,8,9};

	Ptuple t = query_constraint(c,var_name1,var_name2);
	CU_ASSERT_EQUAL(get_tuple_number(t),0);
	Pdomain d = query_constraint_tuples(c,var_name1,var_name2,&content[0]);
	CU_ASSERT_EQUAL(d,NULL);

	int res = insert_constraint_tuples(c,var_name1,var_name2,&content[0]);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint_tuples(c,var_name1,var_name2,&content[0]);
	CU_ASSERT_EQUAL(res,0);

	for (i = 1; i < 10; ++i)
	{
		res = insert_constraint_tuples(c,var_name1,var_name2,&content[i]);
		CU_ASSERT_EQUAL(res,1);

		res = insert_constraint_tuples(c,var_name1,var_name3,&content[i]);
		CU_ASSERT_EQUAL(res,1);

		res = insert_constraint_tuples(c,var_name1,var_name4,&content[i]);
		CU_ASSERT_EQUAL(res,1);
	}

	Ptuple ttest = query_constraint(c,var_name1,var_name2);

	CU_ASSERT_EQUAL(get_tuple_number(ttest),10);

	// print_constraint(c);
	free_constraint(c);
}

void test_insert_constraint_2(void){
	int size = 4;
	Pconstraint c = new_constraint(size);
	int test;
	int var_name1 = 1;
	int var_name2 = 2;
	int var_name3 = 3;

	int content[10] = {0,1,2,3,4,5,6,7,8,9};

	int res = insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[0]);
	CU_ASSERT_EQUAL(res,1);
	res =  insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[0]);
	CU_ASSERT_EQUAL(res,0);
	res =  insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[1]);
	CU_ASSERT_EQUAL(res,1);
	res =  insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[2]);
	CU_ASSERT_EQUAL(res,1);

	res =  insert_constraint_tuple(c,var_name1,var_name3,&content[1],&content[2]);
	CU_ASSERT_EQUAL(res,1);

	res =  insert_constraint_tuple(c,var_name1,var_name3,&content[1],&content[3]);
	CU_ASSERT_EQUAL(res,1);

	res =  insert_constraint_tuple(c,var_name1,var_name3,&content[3],&content[1]);
	CU_ASSERT_EQUAL(res,1);

	Pdomain dtest = query_constraint_tuples(c,var_name1,var_name2,&content[0]);
	CU_ASSERT_EQUAL(get_domain_size(dtest),3);

	dtest = query_constraint_tuples(c,var_name1,var_name3,&content[1]);
	CU_ASSERT_EQUAL(get_domain_size(dtest),2);

	dtest = query_constraint_tuples(c,var_name1,var_name3,&content[3]);
	CU_ASSERT_EQUAL(get_domain_size(dtest),1);

	res = test_contraint_value_exists(c,var_name1,var_name3,content[3]);
	CU_ASSERT_EQUAL(res,1);

	dtest = query_constraint_tuples(c,var_name1,var_name2,&content[1]);
	CU_ASSERT_EQUAL(dtest,NULL);

	res = test_contraint_value_exists(c,var_name1,var_name2,content[1]);
	CU_ASSERT_EQUAL(res,0);

	test = query_constraint_tuple(c,var_name1,var_name2,&content[0],&content[0]);
	CU_ASSERT_EQUAL(test,1);
	test = query_constraint_tuple(c,var_name1,var_name2,&content[0],&content[4]);
	CU_ASSERT_EQUAL(test,0);

	CU_ASSERT_NOT_EQUAL(test_contraint_exists(c,1,2),0);
	CU_ASSERT_EQUAL(test_contraint_exists(c,3,2),0);

	// print_constraint_light(c);
	free_constraint(c);
}

/* ########################################################## */
/* ################### INSTANCE.C TESTS ##################### */
/* ########################################################## */

void test_new_instance(void){
	int size = 10;
	Pinstance inst =  new_instance(size);
	CU_ASSERT_NOT_EQUAL(inst,NULL);
	free_instance(inst);
}

void test_add_instance(void){
	int size = 10;
	Pinstance inst =  new_instance(size);

	CU_ASSERT_EQUAL(get_number_of_linked(inst),0);
	int res = add_linked_variable(inst,0,3);
	CU_ASSERT_EQUAL(res,1);
	CU_ASSERT_EQUAL(get_number_of_linked(inst),1);
	CU_ASSERT_EQUAL(is_linked(inst,0),1);
	CU_ASSERT_EQUAL(is_free(inst,0),0);
	add_linked_variable(inst,5,12);
	add_linked_variable(inst,4,-4);
	CU_ASSERT_EQUAL(is_linked(inst,5),1);
	CU_ASSERT_EQUAL(is_linked(inst,4),1);
	CU_ASSERT_EQUAL(is_linked(inst,2),0);

	CU_ASSERT_EQUAL(get_number_of_linked(inst),3);
	CU_ASSERT_EQUAL(get_number_of_free(inst),10);
	int val = 2;
	add_free_variable(inst,val);
	CU_ASSERT_EQUAL(get_number_of_free(inst),11);
	res = add_linked_variable(inst,4,-4);
	CU_ASSERT_EQUAL(res,0);
	val = 4;
	res = add_free_variable(inst,val);
	CU_ASSERT_EQUAL(res,0);
	res = remove_linked_variable(inst,4);
	CU_ASSERT_EQUAL(res,1);
	res = add_free_variable(inst,val);
	CU_ASSERT_EQUAL(res,1);
	CU_ASSERT_EQUAL(get_number_of_free(inst),12);
	CU_ASSERT_EQUAL(get_linked_val(inst,5),12);

	free_instance(inst);
}

void test_remove_instance(void){
	int size = 10;

	Pinstance inst =  new_instance(size);

	CU_ASSERT_EQUAL(get_number_of_linked(inst),0);
	CU_ASSERT_EQUAL(get_number_of_free(inst),10);
	int res = pop_free_list(inst);
	print_instance(inst);
	CU_ASSERT_EQUAL(get_number_of_free(inst),9);
	CU_ASSERT_EQUAL(res,9)
	int res1 = pop_free_list(inst);
	CU_ASSERT_EQUAL(res1,8)
	// print_instance(inst);
	free_instance(inst);
}