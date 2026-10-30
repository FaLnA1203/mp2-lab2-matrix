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
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> v1(v);

  EXPECT_TRUE(v == v1);
  EXPECT_FALSE(v != v1);
  EXPECT_EQ(1, v1[0]);
  EXPECT_EQ(2, v1[1]);
  EXPECT_EQ(3, v1[2]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> v1(v);
  v1[0] = 100;
  v1[1] = 200;
  v1[2] = 300;

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(100, v1[0]);
  EXPECT_EQ(200, v1[1]);
  EXPECT_EQ(300, v1[2]);
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
  TDynamicVector<int> v(3);
  v[0] = 5; v[1] = 6; v[2] = 7;

  v = v;

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(5, v[0]);
  EXPECT_EQ(6, v[1]);
  EXPECT_EQ(7, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 4; v2[1] = 5; v2[2] = 6;

  v1 = v2;

  EXPECT_TRUE(v1 == v2);
  EXPECT_EQ(4, v1[0]);
  EXPECT_EQ(5, v1[1]);
  EXPECT_EQ(6, v1[2]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v1(3), v2(5);
  v2[0] = 1; v2[1] = 2; v2[2] = 3; v2[3] = 4; v2[4] = 5;

  v1 = v2;

  EXPECT_EQ(5, v1.size());
  EXPECT_EQ(4, v1[3]);
  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v1(2), v2(4);
  v2[0] = 1; v2[1] = 2; v2[2] = 3; v2[3] = 4;

  v1 = v2;

  EXPECT_EQ(4, v1.size());
  EXPECT_EQ(3, v1[2]);
  EXPECT_EQ(4, v1[3]);
  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 1; v2[1] = 2; v2[2] = 3;

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 != v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  EXPECT_TRUE(v == v);
  EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_NE(v, v1);
}

TEST(TDynamicVector, vectors_with_equal_size_but_different_elements_are_not_equal)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 1; v2[1] = 2; v2[2] = 4;

  EXPECT_TRUE(v1 != v2);
  EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  v = v + 5;

  EXPECT_EQ(6, v[0]);
  EXPECT_EQ(7, v[1]);
  EXPECT_EQ(8, v[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  v = v - 1;

  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  v = v * 3;

  EXPECT_EQ(3, v[0]);
  EXPECT_EQ(6, v[1]);
  EXPECT_EQ(9, v[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 10; v2[1] = 20; v2[2] = 30;

  v1 = v1 + v2;

  EXPECT_EQ(11, v1[0]);
  EXPECT_EQ(22, v1[1]);
  EXPECT_EQ(33, v1[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(6);
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 10; v2[1] = 20; v2[2] = 30;

  v1 = v1 - v2;

  EXPECT_EQ(-9, v1[0]);
  EXPECT_EQ(-18, v1[1]);
  EXPECT_EQ(-27, v1[2]);
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

TEST(TDynamicVector, can_write_vector_to_stream)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  std::ostringstream out;
  out << v;

  EXPECT_EQ("1 2 3 ", out.str());
}
