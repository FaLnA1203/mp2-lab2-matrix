#include "tmatrix.h"

#include <gtest.h>
#include <sstream>

// Заполняет матрицу элементами вида i * 10 + j
static void fillMatrix(TDynamicMatrix<int>& m)
{
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = static_cast<int>(i * 10 + j);
}

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

TEST(TDynamicMatrix, throws_when_create_matrix_with_zero_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(0));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(3);
  fillMatrix(m);

  TDynamicMatrix<int> m1(m);

  EXPECT_TRUE(m == m1);
  EXPECT_FALSE(m != m1);
  EXPECT_EQ(m.size(), m1.size());
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      EXPECT_EQ(m[i][j], m1[i][j]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 1;
  m[1][1] = 2;

  TDynamicMatrix<int> m1(m);
  m1[0][0] = 100;
  m1[1][1] = 200;

  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[1][1]);
  EXPECT_EQ(100, m1[0][0]);
  EXPECT_EQ(200, m1[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);

  EXPECT_EQ(4, m.size());
  EXPECT_EQ(4, m[0].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(4);
  m[1][2] = 42;

  EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(4);

  // отрицательный индекс преобразуется в size_t и выходит за границы
  EXPECT_ANY_THROW(m.at(static_cast<size_t>(-1)));
  EXPECT_ANY_THROW(m[0].at(static_cast<size_t>(-1)) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(4);

  EXPECT_ANY_THROW(m.at(4));
  EXPECT_ANY_THROW(m[0].at(4) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 7;

  m = m;

  EXPECT_EQ(3, m.size());
  EXPECT_EQ(7, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(3), b(3);
  fillMatrix(a);
  fillMatrix(b);

  a = b;

  EXPECT_TRUE(a == b);
  EXPECT_EQ(3, a.size());
  EXPECT_EQ(11, a[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> a(3), b(5);
  fillMatrix(a);
  fillMatrix(b);

  a = b;

  EXPECT_EQ(5, a.size());
  EXPECT_EQ(5, a[0].size());
  EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> a(2), b(4);
  fillMatrix(a);
  fillMatrix(b);

  a = b;

  EXPECT_EQ(4, a.size());
  EXPECT_EQ(4, a[0].size());
  EXPECT_EQ(11, a[1][1]);
  EXPECT_EQ(33, a[3][3]);
  EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(3), b(3);
  fillMatrix(a);
  fillMatrix(b);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(3);
  fillMatrix(a);

  EXPECT_TRUE(a == a);
  EXPECT_FALSE(a != a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(3), b(4);

  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, matrices_with_equal_size_but_different_elements_are_not_equal)
{
  TDynamicMatrix<int> a(3), b(3);
  fillMatrix(a);
  fillMatrix(b);
  b[2][2] = 0;

  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(3), b(3);
  fillMatrix(a);
  fillMatrix(b);

  TDynamicMatrix<int> c = a + b;

  EXPECT_EQ(3, c.size());
  for (size_t i = 0; i < c.size(); i++)
    for (size_t j = 0; j < c.size(); j++)
      EXPECT_EQ(2 * (i * 10 + j), c[i][j]);
  // исходные матрицы не изменяются
  EXPECT_EQ(0, a[0][0]);
  EXPECT_EQ(0, b[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(3), b(4);

  EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(3), b(3);
  fillMatrix(a);
  fillMatrix(b);

  TDynamicMatrix<int> c = a - b;

  EXPECT_EQ(3, c.size());
  for (size_t i = 0; i < c.size(); i++)
    for (size_t j = 0; j < c.size(); j++)
      EXPECT_EQ(0, c[i][j]);
  // исходные матрицы не изменяются
  EXPECT_EQ(11, a[1][1]);
  EXPECT_EQ(11, b[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(3), b(4);

  EXPECT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> a(3);
  fillMatrix(a);

  TDynamicMatrix<int> b = a * 2;

  EXPECT_EQ(3, b.size());
  for (size_t i = 0; i < b.size(); i++)
    for (size_t j = 0; j < b.size(); j++)
      EXPECT_EQ(2 * (i * 10 + j), b[i][j]);
}

TEST(TDynamicMatrix, multiplying_matrix_by_scalar_does_not_change_source)
{
  TDynamicMatrix<int> a(3);
  fillMatrix(a);

  TDynamicMatrix<int> b = a * 2;

  EXPECT_EQ(11, a[1][1]);
  EXPECT_EQ(22, a[2][2]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> a(3);
  fillMatrix(a);
  TDynamicVector<int> v(3);
  v[0] = 1;
  v[1] = 1;
  v[2] = 1;

  TDynamicVector<int> res = a * v;

  EXPECT_EQ(3, res.size());
  EXPECT_EQ(0 + 1 + 2, res[0]);
  EXPECT_EQ(10 + 11 + 12, res[1]);
  EXPECT_EQ(20 + 21 + 22, res[2]);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_of_different_size)
{
  TDynamicMatrix<int> a(3);
  TDynamicVector<int> v(4);

  EXPECT_ANY_THROW(a * v);
}

TEST(TDynamicMatrix, can_multiply_matrices)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;

  TDynamicMatrix<int> c = a * b;

  EXPECT_EQ(2, c.size());
  EXPECT_EQ(19, c[0][0]);
  EXPECT_EQ(22, c[0][1]);
  EXPECT_EQ(43, c[1][0]);
  EXPECT_EQ(50, c[1][1]);
}

TEST(TDynamicMatrix, multiplying_matrices_does_not_change_sources)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;

  TDynamicMatrix<int> c = a * b;

  EXPECT_EQ(1, a[0][0]);
  EXPECT_EQ(4, a[1][1]);
  EXPECT_EQ(5, b[0][0]);
  EXPECT_EQ(8, b[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_of_different_size)
{
  TDynamicMatrix<int> a(2), b(3);

  EXPECT_ANY_THROW(a * b);
}

TEST(TDynamicMatrix, can_read_matrix_from_stream)
{
  TDynamicMatrix<int> m(2);
  std::istringstream in("1 2 3 4");

  in >> m;

  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[0][1]);
  EXPECT_EQ(3, m[1][0]);
  EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_write_matrix_to_stream)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;

  std::ostringstream out;
  out << m;

  EXPECT_EQ("1 2 \n3 4 \n", out.str());
}
