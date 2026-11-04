#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<double> m(10);
	TDynamicMatrix m2(m);
	EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	//TDynamicMatrix<double> m(10);
	//TDynamicMatrix m2(m);
	//m = m + 3.0;
	//EXPECT_NE(m, m2);
	ADD_FAILURE();
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<double> m(7);
	size_t sz = m.size();
	EXPECT_EQ(7, sz);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<double> m(10);
	for (int i = 0; i < 10; i++) {
		m[i] = (double)(i + 1);
	}
	TDynamicMatrix<double> m2(10);
	for (int i = 0; i < 10; i++) {
		m2.at(i) = (double)(i + 1);
	}
	int flag = 0;
	for (int i = 0; i < 10; i++) {
		if (m[i] != (double)(i + 1)) flag = 1;
	}
	for (int i = 0; i < 10; i++) {
		if (m.at(i) != (double)(i + 1)) flag = 1;
	}
	if (flag)
		ADD_FAILURE();
	EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<double> m(10);
	ASSERT_ANY_THROW(m.at(-1));

}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<double> m(10);
	ASSERT_ANY_THROW(m.at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_read_matrix)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_write_matrix)
{
  ADD_FAILURE();
}
