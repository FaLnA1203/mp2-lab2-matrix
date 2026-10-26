#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(10));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-1));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(10);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[1][1] = 2; m[2][2] = 3;
	TDynamicMatrix<int> m1(m);
	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(m);
	ASSERT_NE(&m[0], &m1[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);
	ASSERT_NO_THROW(m[3][3] = 10);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[1][2] = 42;
	ASSERT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m[0].at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);
	ASSERT_ANY_THROW(m[0].at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(4);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(4);
	m1[1][1] = 5;
	ASSERT_NO_THROW(m = m1);
	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(4);
	TDynamicMatrix<int> m1(6);
	ASSERT_NO_THROW(m = m1);
	ASSERT_NO_THROW(m[5][5] = 1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	m1[4][4] = 99;
	ASSERT_NO_THROW(m = m1);
	ASSERT_EQ(m, m1);
	ASSERT_EQ(m[4][4], 99);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	ASSERT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	ASSERT_NE(m, m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 5; m2[0][1] = 6; m2[1][0] = 7; m2[1][1] = 8;

	TDynamicMatrix<int> res = m1 + m2;

	ASSERT_EQ(res[0][0], 6);
	ASSERT_EQ(res[0][1], 8);
	ASSERT_EQ(res[1][0], 10);
	ASSERT_EQ(res[1][1], 12);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 5; m1[0][1] = 6; m1[1][0] = 7; m1[1][1] = 8;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1; m2[0][1] = 2; m2[1][0] = 3; m2[1][1] = 4;

	TDynamicMatrix<int> res = m1 - m2;

	ASSERT_EQ(res[0][0], 4);
	ASSERT_EQ(res[0][1], 4);
	ASSERT_EQ(res[1][0], 4);
	ASSERT_EQ(res[1][1], 4);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);
	ASSERT_ANY_THROW(m1 - m2);
}

