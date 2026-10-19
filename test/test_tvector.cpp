#include "tmatrix.h"

#include <gtest.h>
#include <sstream>

// Заполняет вектор элементами 1, 2, 3, ...
static void fillVector(TDynamicVector<int>& v)
{
  for (size_t i = 0; i < v.size(); i++)
    v[i] = static_cast<int>(i + 1);
}

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

TEST(TDynamicVector, throws_when_create_vector_with_zero_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(0));
}

TEST(TDynamicVector, can_create_vector_from_array)
{
  int arr[] = { 1, 2, 3 };

  TDynamicVector<int> v(arr, 3);

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(3);
  fillVector(v);

  TDynamicVector<int> v1(v);

  EXPECT_TRUE(v == v1);
  EXPECT_FALSE(v != v1);
  EXPECT_EQ(v.size(), v1.size());
  for (size_t i = 0; i < v.size(); i++)
    EXPECT_EQ(v[i], v1[i]);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 1;
  v[1] = 2;

  TDynamicVector<int> v1(v);
  v1[0] = 100;
  v1[1] = 200;

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(100, v1[0]);
  EXPECT_EQ(200, v1[1]);
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

  // отрицательный индекс преобразуется в size_t и выходит за границы
  EXPECT_ANY_THROW(v.at(static_cast<size_t>(-1)) = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);

  EXPECT_ANY_THROW(v.at(4) = 5);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 5;

  v = v;

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(5, v[0]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1;
  v2[0] = 2;

  v1 = v2;

  EXPECT_TRUE(v1 == v2);
  EXPECT_EQ(2, v1[0]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v1(3), v2(5);
  fillVector(v2);

  v1 = v2;

  EXPECT_EQ(5, v1.size());
  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v1(2), v2(4);
  v2[3] = 42;

  v1 = v2;

  EXPECT_EQ(4, v1.size());
  EXPECT_EQ(42, v1[3]);
  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v1(3), v2(3);
  fillVector(v1);
  fillVector(v2);

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 != v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  fillVector(v);

  EXPECT_TRUE(v == v);
  EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v1(3), v2(4);

  EXPECT_TRUE(v1 != v2);
  EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, vectors_with_equal_size_but_different_elements_are_not_equal)
{
  TDynamicVector<int> v1(3), v2(3);
  fillVector(v1);
  fillVector(v2);
  v2[1] = 0;

  EXPECT_TRUE(v1 != v2);
  EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  fillVector(v);

  v = v + 5;

  EXPECT_EQ(6, v[0]);
  EXPECT_EQ(7, v[1]);
  EXPECT_EQ(8, v[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  fillVector(v);

  v = v - 1;

  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(2, v[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3);
  fillVector(v);

  v = v * 3;

  EXPECT_EQ(3, v[0]);
  EXPECT_EQ(6, v[1]);
  EXPECT_EQ(9, v[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  fillVector(v1);
  fillVector(v2);

  v1 = v1 + v2;

  EXPECT_EQ(2, v1[0]);
  EXPECT_EQ(4, v1[1]);
  EXPECT_EQ(6, v1[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(4);

  EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  fillVector(v1);
  fillVector(v2);

  v1 = v1 - v2;

  EXPECT_EQ(0, v1[0]);
  EXPECT_EQ(0, v1[1]);
  EXPECT_EQ(0, v1[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(4);

  EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;
  v2[0] = 4; v2[1] = 5; v2[2] = 6;

  // скалярное произведение
  EXPECT_EQ(32, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(4);

  EXPECT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, can_read_vector_from_stream)
{
  TDynamicVector<int> v(3);
  std::istringstream in("1 2 3");

  in >> v;

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_write_vector_to_stream)
{
  TDynamicVector<int> v(3);
  fillVector(v);

  std::ostringstream out;
  out << v;

  EXPECT_EQ("1 2 3 ", out.str());
}
