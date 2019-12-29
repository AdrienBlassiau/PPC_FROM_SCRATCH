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
#include "../src/domain.h"
#include "../src/variable.h"
#include "../src/tuple.h"
#include "../src/compare_tuple.h"
#include "../src/constraint.h"

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

	if((NULL==CU_add_test(suite2, "Test new variable", test_new_variable)||
		(NULL==CU_add_test(suite2, "Test var size", test_variable_size))||
		(NULL==CU_add_test(suite2, "Test var it", test_variable_iteration))||
		(NULL==CU_add_test(suite2, "Test insert", test_insert_in_variable))||
		(NULL==CU_add_test(suite2, "Test rm", test_remove_from_variable))||
		(NULL==CU_add_test(suite2, "Test rm value", test_remove_value))))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite3 = CU_add_suite("tuple_test",setup,teardown);

	if((NULL==CU_add_test(suite3, "Test new tuple", test_new_tuple)||
		(NULL==CU_add_test(suite3, "Test tup size", test_tuple_size))||
		(NULL==CU_add_test(suite3, "Test tup it", test_tuple_iteration))||
		(NULL==CU_add_test(suite3, "Test insert", test_insert_in_tuple))||
		(NULL==CU_add_test(suite3, "Test rm", test_remove_from_tuple))||
		(NULL==CU_add_test(suite3, "Test rm content", test_remove_content))))
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
		(NULL==CU_add_test(suite5, "Test ins 2", test_insert_constraint_2))||
		(NULL==CU_add_test(suite5, "Test ins 3", test_insert_constraint_3))||
		(NULL==CU_add_test(suite5, "Test ins 4", test_insert_constraint_4))||
		(NULL==CU_add_test(suite5, "Test iter", test_constraint_iteration))||
		(NULL==CU_add_test(suite5, "Test rm", test_constraint_remove)))
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

	Pvariable v = new_variable();

	CU_ASSERT_NOT_EQUAL(v,NULL);

	free_variable(v);
}

void test_variable_size(void){
	int i;
	Pvariable v = new_variable();
	int size = get_variable_number(v);

	CU_ASSERT_EQUAL(size,0);

	Pdomain d1 = new_domain();
	int tab1[6] = {1,2,5,6,12,23};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d1,&tab1[i]);

	Pdomain d2 = new_domain();
	int tab2[6] = {1,2,5,6,12,23};
	for (i = 0; i < 6; ++i)
		insert_in_domain(d2,&tab2[i]);

	char var_name1[256] = "test1";
	insert_variable(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variable(v,var_name2,d2);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,2);

	free_variable(v);
}

void test_variable_iteration(void){
	int i;
	Pdomain value;
	char * key;
	Pvariable v = new_variable();
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

	char var_name1[256] = "test1";
	insert_variable(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variable(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variable(v,var_name3,d3);

	CU_ASSERT_EQUAL(get_var_iterator(v),0);
	begin_variable_iteration(v);
	CU_ASSERT_EQUAL(get_var_iterator(v),0);

	int size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,3);

	i = 0;
	while(variable_can_iterate(v)){
		value = get_var_current_value(v);
		key = get_var_current_key(v);
		if (i==0)
		{
			CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
			CU_ASSERT_STRING_EQUAL(key,var_name1);
		}
		else if(i==1){
			CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
			CU_ASSERT_EQUAL(key,var_name2);
		}
		else{
			CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
			CU_ASSERT_EQUAL(key,var_name3);
		}
		get_next_var(v);
		i++;
	};
	CU_ASSERT_EQUAL(get_var_iterator(v),0);


	CU_ASSERT_EQUAL(get_var_iterator(v),0);
	begin_variable_iteration(v);
	CU_ASSERT_EQUAL(get_var_iterator(v),0);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,3);

	i = 0;
	while(variable_can_iterate(v)){
		value = get_var_current_value(v);
		key = get_var_current_key(v);
		if (i==0)
		{
			CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
			CU_ASSERT_STRING_EQUAL(key,var_name1);
		}
		else if(i==1){
			CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
			CU_ASSERT_EQUAL(key,var_name2);
		}
		else{
			CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
			CU_ASSERT_EQUAL(key,var_name3);
		}
		get_next_var(v);
		i++;
	};
	CU_ASSERT_EQUAL(get_var_iterator(v),0);

	free_variable(v);
}

void test_insert_in_variable(void){
	int i;
	Pvariable v = new_variable();
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

	char var_name1[256] = "test1";
	insert_variable(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variable(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variable(v,var_name3,d3);

	Pdomain d11 = query_variable(v,var_name1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_variable(v,var_name2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_variable(v,var_name3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	free_variable(v);
}

void test_remove_from_variable(void){
	int i,size;
	Pvariable v = new_variable();
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

	char var_name1[256] = "test1";
	insert_variable(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variable(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variable(v,var_name3,d3);

	Pdomain d11 = query_variable(v,var_name1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_variable(v,var_name2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_variable(v,var_name3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,3);

	remove_variable(v,var_name3);
	CU_ASSERT_EQUAL(query_variable(v,var_name3),NULL);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,2);

	remove_variable(v,var_name1);
	CU_ASSERT_EQUAL(query_variable(v,var_name1),NULL);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,1);

	remove_variable(v,var_name2);
	CU_ASSERT_EQUAL(query_variable(v,var_name2),NULL);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,0);

	free_variable(v);
}

void test_remove_value(void){
	int i,size;
	Pvariable v = new_variable();

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
	insert_variable(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variable(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variable(v,var_name3,d3);

	size = get_variable_number(v);
	CU_ASSERT_EQUAL(size,3);

	int val_test = 8;
	remove_value_of_variable_domain(v,var_name3,&val_test);

	Pdomain d13 = query_variable(v,var_name3);
	size = get_domain_size(d13);

	CU_ASSERT_EQUAL(size,5);

	free_variable_bis(v);
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
	Pconstraint c = new_constraint();

	CU_ASSERT_NOT_EQUAL(c,NULL);
	// print_constraint(c);
	free_constraint(c);
}

void test_insert_constraint_1(void){
	Pconstraint c = new_constraint();

	char var_name1[256] = "A";
	int res = insert_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,1);
	res = insert_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,0);

	PAVLTree a = query_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(avl_tree_num_entries(a),0);
	CU_ASSERT_EQUAL(get_constraint_number1(c),1);

	char var_name2[256] = "B";

	res = insert_all_constraint(c,var_name2);
	CU_ASSERT_EQUAL(res,1);

	CU_ASSERT_EQUAL(get_constraint_number1(c),2);
	// print_constraint(c);
	free_constraint(c);
}

void test_insert_constraint_2(void){
	Pconstraint c = new_constraint();

	char var_name1[256] = "A";
	char var_name2[256] = "B";
	char var_name3[256] = "C";
	char var_name4[256] = "D";
	char var_name5[256] = "E";
	char var_name6[256] = "F";

	int res = insert_constraint(c,var_name1,var_name2);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint(c,var_name1,var_name3);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint(c,var_name1,var_name4);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint(c,var_name1,var_name5);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint(c,var_name1,var_name6);
	CU_ASSERT_EQUAL(res,1);
	res = insert_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,0);
	res = insert_constraint(c,var_name1,var_name2);
	CU_ASSERT_EQUAL(res,0);
	res = insert_constraint(c,var_name2,var_name1);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint(c,var_name2,var_name3);
	CU_ASSERT_EQUAL(res,1);
	res = insert_constraint(c,var_name2,var_name6);
	CU_ASSERT_EQUAL(res,1);

	PAVLTree a = query_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(avl_tree_num_entries(a),5);
	CU_ASSERT_EQUAL(get_constraint_number1(c),2);

	Ptuple t = query_constraint(c,var_name1,var_name3);
	CU_ASSERT_NOT_EQUAL(t,NULL);
	t = query_constraint(c,var_name3,var_name1);
	CU_ASSERT_EQUAL(t,NULL);

	// print_constraint(c);
	free_constraint(c);
}

void test_insert_constraint_3(void){
	Pconstraint c = new_constraint();
	int i;
	char var_name1[256] = "A";
	char var_name2[256] = "B";
	char var_name3[256] = "C";
	char var_name4[256] = "D";

	int content[10] = {0,1,2,3,4,5,6,7,8,9};

	PAVLTree a = query_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(a,NULL);
	Ptuple t = query_constraint(c,var_name1,var_name2);
	CU_ASSERT_EQUAL(t,NULL);
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

	a = query_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(avl_tree_num_entries(a),3);
	a = query_all_constraint(c,var_name2);
	CU_ASSERT_EQUAL(a,NULL);

	Ptuple ttest = query_constraint(c,var_name1,var_name2);

	CU_ASSERT_EQUAL(get_tuple_number(ttest),10);

	// print_constraint(c);
	free_constraint(c);
}

void test_insert_constraint_4(void){
	Pconstraint c = new_constraint();
	int test;
	char var_name1[256] = "A";
	char var_name2[256] = "B";
	char var_name3[256] = "C";

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

	dtest = query_constraint_tuples(c,var_name1,var_name2,&content[1]);
	CU_ASSERT_EQUAL(dtest,NULL);

	test = query_constraint_tuple(c,var_name1,var_name2,&content[0],&content[0]);
	CU_ASSERT_EQUAL(test,1);
	test = query_constraint_tuple(c,var_name1,var_name2,&content[0],&content[4]);
	CU_ASSERT_EQUAL(test,0);

	// print_constraint(c);
	free_constraint(c);
}

void test_constraint_iteration(void){
	Pconstraint c = new_constraint();
	char* key;
	int i,j;
	PAVLTree value;
	Ptuple value2;
	char var_name1[256] = "A";
	char var_name2[256] = "B";
	char var_name3[256] = "C";

	int tab[2][2] = {{2,0},{3,3}};

	int content[10] = {0,1,2,3,4,5,6,7,8,9};

	insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[1]);
	insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[2]);
	insert_constraint_tuple(c,var_name1,var_name2,&content[1],&content[3]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[1],&content[2]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[1],&content[3]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[2],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[4],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[0],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[0],&content[2]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[0],&content[0]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[2],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[3],&content[0]);

	begin_constraint_iteration1(c);
	i = 0;
	j = 0;
	while(constraint_can_iterate1(c)){
		key = get_constraint_current_key1(c);
		value = get_constraint_current_value1(c);

		if (i==0){
			CU_ASSERT_STRING_EQUAL(key,var_name1);
			CU_ASSERT_EQUAL(avl_tree_num_entries(value),1);
		}
		else if(i==1){
			CU_ASSERT_STRING_EQUAL(key,var_name2);
			CU_ASSERT_EQUAL(avl_tree_num_entries(value),2);
		}

		begin_constraint_iteration2(c);
		j=0;
		while(constraint_can_iterate2(c)){
			key = get_constraint_current_key2(c);
			value2 = get_constraint_current_value2(c);
			CU_ASSERT_EQUAL(get_tuple_number(value2),tab[i][j]);
			get_next_constraint2(c);
			j++;
		}

		get_next_constraint1(c);
		i++;
	}

	begin_constraint_iteration1(c);
	i = 0;
	j = 0;
	while(constraint_can_iterate1(c)){
		key = get_constraint_current_key1(c);
		value = get_constraint_current_value1(c);

		if (i==0){
			CU_ASSERT_STRING_EQUAL(key,var_name1);
			CU_ASSERT_EQUAL(avl_tree_num_entries(value),1);
		}
		else if(i==1){
			CU_ASSERT_STRING_EQUAL(key,var_name2);
			CU_ASSERT_EQUAL(avl_tree_num_entries(value),2);
		}

		begin_constraint_iteration2(c);
		j=0;
		while(constraint_can_iterate2(c)){
			key = get_constraint_current_key2(c);
			value2 = get_constraint_current_value2(c);
			CU_ASSERT_EQUAL(get_tuple_number(value2),tab[i][j]);
			get_next_constraint2(c);
			j++;
		}

		get_next_constraint1(c);
		i++;
	}

	CU_ASSERT_EQUAL(get_constraint_number1(c),2);
	CU_ASSERT_EQUAL(get_constraint_number2(c,var_name1),1);
	CU_ASSERT_EQUAL(get_constraint_number2(c,var_name2),2);
	CU_ASSERT_EQUAL(get_constraint_total_number(c),3);
	CU_ASSERT_EQUAL(get_constraint_total_number(c),3);
	// print_constraint(c);
	free_constraint(c);
}

void test_constraint_remove(void){
	Pconstraint c = new_constraint();

	char var_name1[256] = "A";
	char var_name2[256] = "B";
	char var_name3[256] = "C";

	int content[10] = {0,1,2,3,4,5,6,7,8,9};

	insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[1]);
	insert_constraint_tuple(c,var_name1,var_name2,&content[0],&content[2]);
	insert_constraint_tuple(c,var_name1,var_name2,&content[1],&content[3]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[1],&content[2]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[1],&content[3]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[2],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name1,&content[4],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[0],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[0],&content[2]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[0],&content[0]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[2],&content[1]);
	insert_constraint_tuple(c,var_name2,var_name3,&content[3],&content[0]);

	CU_ASSERT_EQUAL(get_constraint_number1(c),2);
	int res = remove_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,1);
	CU_ASSERT_EQUAL(get_constraint_number1(c),1);

	res = remove_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,0);


	CU_ASSERT_EQUAL(get_constraint_total_number(c),2);
	res = remove_constraint(c,var_name2,var_name1);
	CU_ASSERT_EQUAL(res,1);
	CU_ASSERT_EQUAL(get_constraint_total_number(c),1);

	res = remove_constraint(c,var_name2,var_name1);
	CU_ASSERT_EQUAL(res,0);




	Ptuple ttest = query_constraint(c,var_name2,var_name3);

	CU_ASSERT_EQUAL(get_tuple_number(ttest),3);
	res = remove_constraint_tuples(c,var_name2,var_name3,&content[2]);
	CU_ASSERT_EQUAL(res,1);
	ttest = query_constraint(c,var_name2,var_name3);
	CU_ASSERT_EQUAL(get_tuple_number(ttest),2);

	res = remove_constraint_tuples(c,var_name2,var_name3,&content[2]);
	CU_ASSERT_EQUAL(res,0);



	Pdomain dtest = query_constraint_tuples(c,var_name2,var_name3,&content[0]);

	CU_ASSERT_EQUAL(get_domain_size(dtest),3);
	res = remove_constraint_tuple(c,var_name2,var_name3,&content[0],&content[0]);
	CU_ASSERT_EQUAL(res,1);
	dtest = query_constraint_tuples(c,var_name2,var_name3,&content[0]);
	CU_ASSERT_EQUAL(get_domain_size(dtest),2);

	res = remove_constraint_tuple(c,var_name2,var_name3,&content[0],&content[0]);
	CU_ASSERT_EQUAL(res,0);




	CU_ASSERT_EQUAL(get_constraint_number1(c),1);
	res = remove_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,0);
	CU_ASSERT_EQUAL(get_constraint_number1(c),1);

	res = remove_all_constraint(c,var_name1);
	CU_ASSERT_EQUAL(res,0);


	CU_ASSERT_EQUAL(get_constraint_total_number(c),1);
	res = remove_constraint(c,var_name2,var_name1);
	CU_ASSERT_EQUAL(res,0);
	CU_ASSERT_EQUAL(get_constraint_total_number(c),1);

	res = remove_constraint(c,var_name2,var_name1);
	CU_ASSERT_EQUAL(res,0);


	ttest = query_constraint(c,var_name2,var_name3);

	CU_ASSERT_EQUAL(get_tuple_number(ttest),2);
	res = remove_constraint_tuples(c,var_name2,var_name3,&content[2]);
	CU_ASSERT_EQUAL(res,0);
	ttest = query_constraint(c,var_name2,var_name3);
	CU_ASSERT_EQUAL(get_tuple_number(ttest),2);

	res = remove_constraint_tuples(c,var_name2,var_name3,&content[2]);
	CU_ASSERT_EQUAL(res,0);

	dtest = query_constraint_tuples(c,var_name2,var_name3,&content[0]);

	CU_ASSERT_EQUAL(get_domain_size(dtest),2);
	res = remove_constraint_tuple(c,var_name2,var_name3,&content[0],&content[0]);
	CU_ASSERT_EQUAL(res,0);
	dtest = query_constraint_tuples(c,var_name2,var_name3,&content[0]);
	CU_ASSERT_EQUAL(get_domain_size(dtest),2);

	res = remove_constraint_tuple(c,var_name2,var_name3,&content[0],&content[0]);
	CU_ASSERT_EQUAL(res,0);

	// print_constraint(c);
	free_constraint(c);
}