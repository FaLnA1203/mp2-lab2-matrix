#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(8);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(8);
	TDynamicVector<int> v1(v);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(8);
	TDynamicVector<int> v1(v);
	ASSERT_NE(&v[0], &v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;
	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	ASSERT_NO_THROW(v = v1);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(6);
	ASSERT_NO_THROW(v = v1);
	ASSERT_EQ(v.size(), 6);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	for (int i = 0; i < 3; i++) {
		v[i] = i * 10;
	}
	for (int i = 0; i < 6; i++) {
		v1[i] = i;
	}
	ASSERT_NO_THROW(v = v1);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);
	ASSERT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_NE(v, v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
	}
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = v + 3);
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(v[i] + 3, res[i]);
	}
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
	}
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = v - 3);
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(v[i] - 3, res[i]);
	}
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i;
	}
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = v * 3);
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(v[i] * 3, res[i]);
	}
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	for (int i = 0; i < 3; i++) {
		v[i] = i+1;
	}
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = v + v);
	TDynamicVector<int> true_res(3);
	true_res[0] = 2; true_res[1] = 4; true_res[2] = 6;
	ASSERT_EQ(true_res, res);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = v - v1);
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(v[i] - v1[i], res[i]);
	}
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);
	int res;
	ASSERT_NO_THROW(res = v * v1);
	ASSERT_EQ(v * v1, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_DEATH(v * v1, "");
}

