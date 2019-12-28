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
// #include "../src/constraint.h"

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

	if((NULL==CU_add_test(suite2, "Test new variables", test_new_variables)||
		(NULL==CU_add_test(suite2, "Test var size", test_variables_size))||
		(NULL==CU_add_test(suite2, "Test var it", test_variables_iteration))||
		(NULL==CU_add_test(suite2, "Test insert", test_insert_in_variables))||
		(NULL==CU_add_test(suite2, "Test rm", test_remove_from_variables))||
		(NULL==CU_add_test(suite2, "Test rm value", test_remove_value))))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_pSuite suite3 = CU_add_suite("tuple_test",setup,teardown);

	if((NULL==CU_add_test(suite3, "Test new tuples", test_new_tuples)||
		(NULL==CU_add_test(suite3, "Test tup size", test_tuples_size))||
		(NULL==CU_add_test(suite3, "Test tup it", test_tuples_iteration))||
		(NULL==CU_add_test(suite3, "Test insert", test_insert_in_tuples))||
		(NULL==CU_add_test(suite3, "Test rm", test_remove_from_tuples))||
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

void test_new_variables(void){

	Pvariables v = new_variables();

	CU_ASSERT_NOT_EQUAL(v,NULL);

	free_variables(v);
}

void test_variables_size(void){
	int i;
	Pvariables v = new_variables();
	int size = get_variables_number(v);

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
	insert_variables(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variables(v,var_name2,d2);

	size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,2);

	free_variables(v);
}

void test_variables_iteration(void){
	int i;
	Pdomain value;
	Pvariables v = new_variables();
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
	insert_variables(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variables(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variables(v,var_name3,d3);

	CU_ASSERT_EQUAL(get_var_iterator(v),0);
	begin_variables_iteration(v);
	CU_ASSERT_EQUAL(get_var_iterator(v),0);

	int size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,3);

	i = 0;
	while(variables_can_iterate(v)){
		value = get_var_current_value(v);
		CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
		i++;
	};
	CU_ASSERT_EQUAL(get_var_iterator(v),0);

	free_variables(v);
}

void test_insert_in_variables(void){
	int i;
	Pvariables v = new_variables();
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
	insert_variables(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variables(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variables(v,var_name3,d3);

	Pdomain d11 = query_variables(v,var_name1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_variables(v,var_name2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_variables(v,var_name3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	free_variables(v);
}

void test_remove_from_variables(void){
	int i,size;
	Pvariables v = new_variables();
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
	insert_variables(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variables(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variables(v,var_name3,d3);

	Pdomain d11 = query_variables(v,var_name1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_variables(v,var_name2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_variables(v,var_name3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,3);

	remove_variables(v,var_name3);
	CU_ASSERT_EQUAL(query_variables(v,var_name3),NULL);

	size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,2);

	remove_variables(v,var_name1);
	CU_ASSERT_EQUAL(query_variables(v,var_name1),NULL);

	size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,1);

	remove_variables(v,var_name2);
	CU_ASSERT_EQUAL(query_variables(v,var_name2),NULL);

	size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,0);

	free_variables(v);
}

void test_remove_value(void){
	int i,size;
	Pvariables v = new_variables();

	Pdomain d1 = new_domain();
	int tab1[4] = {1,2,5,6};
	for (i = 0; i < 4; ++i) insert_in_domain(d1,&tab1[i]);

		Pdomain d2 = new_domain();
	int tab2[2] = {3,8};
	for (i = 0; i < 2; ++i) insert_in_domain(d2,&tab2[i]);

		Pdomain d3 = new_domain();
	int tab3[6] = {6,7,8,9,10,11};
	for (i = 0; i < 6; ++i) insert_in_domain(d3,&tab3[i]);

		char var_name1[256] = "test1";
	insert_variables(v,var_name1,d1);

	char var_name2[256] = "test2";
	insert_variables(v,var_name2,d2);

	char var_name3[256] = "test3";
	insert_variables(v,var_name3,d3);

	size = get_variables_number(v);
	CU_ASSERT_EQUAL(size,3);

	int val_test = 8;
	remove_value_of_variable_domain(v,var_name3,&val_test);

	Pdomain d13 = query_variables(v,var_name3);
	size = get_domain_size(d13);

	CU_ASSERT_EQUAL(size,5);

	free_variables_bis(v);
}

/* ########################################################## */
/* ##################### TUPLE.C TESTS ###################### */
/* ########################################################## */

void test_new_tuples(void){

	Ptuples t = new_tuples();

	CU_ASSERT_NOT_EQUAL(t,NULL);

	free_tuples(t);
}

void test_tuples_size(void){
	int i;
	Ptuples t = new_tuples();
	int size = get_tuples_number(t);

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
	insert_tuples(t,&content1,d1);

	int content2 = 2;
	insert_tuples(t,&content2,d2);

	size = get_tuples_number(t);
	CU_ASSERT_EQUAL(size,2);

	free_tuples(t);
}

void test_tuples_iteration(void){
	int i;
	Pdomain value;
	Ptuples t = new_tuples();
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
	insert_tuples(t,&content1,d1);

	int content2 = 2;
	insert_tuples(t,&content2,d2);

	int content3 = 3;
	insert_tuples(t,&content3,d3);

	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);
	begin_tuples_iteration(t);
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);

	int size = get_tuples_number(t);
	CU_ASSERT_EQUAL(size,3);

	i = 0;
	while(tuples_can_iterate(t)){
		value = get_tuple_current_value(t);
		CU_ASSERT_EQUAL(get_domain_size(value),data_size[i]);
		i++;
	};
	CU_ASSERT_EQUAL(get_tuple_iterator(t),0);

	free_tuples(t);
}

void test_insert_in_tuples(void){
	int i;
	Ptuples t = new_tuples();
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
	insert_tuples(t,&content1,d1);

	int content2 = 2;
	insert_tuples(t,&content2,d2);

	int content3 = 3;
	insert_tuples(t,&content3,d3);

	Pdomain d11 = query_tuples(t,&content1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_tuples(t,&content2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_tuples(t,&content3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	free_tuples(t);
}

void test_remove_from_tuples(void){
	int i,size;
	Ptuples t = new_tuples();
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
	insert_tuples(t,&content1,d1);

	int content2 = 2;
	insert_tuples(t,&content2,d2);

	int content3 = 3;
	insert_tuples(t,&content3,d3);

	Pdomain d11 = query_tuples(t,&content1);
	CU_ASSERT_EQUAL(get_domain_size(d11),data_size[0]);
	Pdomain d12 = query_tuples(t,&content2);
	CU_ASSERT_EQUAL(get_domain_size(d12),data_size[1]);
	Pdomain d13 = query_tuples(t,&content3);
	CU_ASSERT_EQUAL(get_domain_size(d13),data_size[2]);

	size = get_tuples_number(t);
	print_tuples(t);
	CU_ASSERT_EQUAL(size,3);

	remove_tuples(t,&content3);
	CU_ASSERT_EQUAL(query_tuples(t,&content3),NULL);

	size = get_tuples_number(t);
	CU_ASSERT_EQUAL(size,2);

	remove_tuples(t,&content1);
	CU_ASSERT_EQUAL(query_tuples(t,&content1),NULL);

	size = get_tuples_number(t);
	CU_ASSERT_EQUAL(size,1);

	remove_tuples(t,&content2);
	CU_ASSERT_EQUAL(query_tuples(t,&content2),NULL);

	size = get_tuples_number(t);
	CU_ASSERT_EQUAL(size,0);

	free_tuples(t);
}

void test_remove_content(void){
	int i,size;
	Ptuples t = new_tuples();

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
	insert_tuples(t,&content1,d1);

	int content2 = 2;
	insert_tuples(t,&content2,d2);

	int content3 = 3;
	insert_tuples(t,&content3,d3);

	size = get_tuples_number(t);
	CU_ASSERT_EQUAL(size,3);

	int val_test = 8;
	remove_value_of_content_domain(t,&content3,&val_test);

	Pdomain d13 = query_tuples(t,&content3);
	size = get_domain_size(d13);

	CU_ASSERT_EQUAL(size,5);

	free_tuples_bis(t);
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