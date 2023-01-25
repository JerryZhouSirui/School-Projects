// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  ostringstream s;
  ostringstream correct;
  correct << "3 5\n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";
  correct << "42 42 42 \n";

  Matrix_print(mat, s);

  ASSERT_EQUAL(s.str(), correct.str());


  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

TEST(test_matrix_equal_r_and_c_odd) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 3;
  Matrix_init(mat, 3, 3);
  int value = 1;
  for(int r = 0; r < height; ++r){
    for(int c = width - 1; c >= 0; --c) {
      *Matrix_at(mat, r, c) = value;
      value++;
    }
  }

  ASSERT_EQUAL(Matrix_max(mat), 9);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 2), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 2), 2);
  delete mat;
}

TEST(test_matrix_one){
  Matrix *mat = new Matrix;

  Matrix_init(mat, 1, 1);
  Matrix_fill_border(mat, 1);

  ASSERT_EQUAL(Matrix_max(mat), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0 ,1), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0 , 0 , 1), 1);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
  delete mat;
}

TEST(test_matrix_equal_min) {
  Matrix *mat = new Matrix;
  const int width = 3;
  const int height = 3;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 1);
  ASSERT_EQUAL( Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0 , 3), 1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 3), 1)
  delete mat;
}

TEST(test_matrix_r_and_c_not_equal){
  Matrix *mat = new Matrix;
  const int width = 4;
  const int height = 3;
  Matrix_init(mat, width, height);

  ASSERT_EQUAL( Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);
  int value = 0;
  
  for(int i = 0; i < height; i++) {
    
    for (int j = 0; j< width; j++) {
      *Matrix_at(mat, i, j) = value;
    }
    value++;
  }
  ostringstream s;
  ostringstream correct;
  correct << "4 3\n";
  correct << "0 0 0 0 \n";
  correct << "1 1 1 1 \n";
  correct << "2 2 2 2 \n";

  Matrix_print(mat, s);

  ASSERT_EQUAL(s.str(), correct.str());

  ASSERT_EQUAL(Matrix_max(mat), 2);

  for(int i = 0; i < height; i++) {
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, i, 0, width), i);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, i, 0, width), 0);
  }

  delete mat;
}

TEST(test_matrix_r_and_c){
  Matrix *mat = new Matrix;
  const int width = 3;
  const int height = 3;


  Matrix_init(mat, width, height);
  ASSERT_EQUAL( Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);
  Matrix_fill(mat, 1);
  for (int i = 0; i < height; i++) {
    for(int j = 0; j< width; j++) {
      ASSERT_EQUAL(Matrix_row(mat, Matrix_at(mat, i, j)), i);
      ASSERT_EQUAL(Matrix_column(mat, Matrix_at(mat, i, j)), j);
    }
  }
  delete mat;
}

TEST(test_matrix_line) {
  Matrix *mat = new Matrix;
  Matrix *mat_two = new Matrix;
  const int height = 1;
  const int width = 3;

  Matrix_init(mat, width, height);
  Matrix_init(mat_two, width, height);
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  Matrix_fill(mat, 2);
  Matrix_fill_border(mat_two, 2);
  ASSERT_TRUE(Matrix_equal(mat, mat_two));

  for(int i = 0; i < width; i++) {
    ASSERT_EQUAL(*Matrix_at(mat, 0, i), 2);
    ASSERT_EQUAL(*Matrix_at(mat_two, 0, i), 2);
  }


  ostringstream s;
  ostringstream correct;
  correct << "3 1\n";
  correct << "2 2 2 \n";
  Matrix_print(mat, s);

  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
  delete mat_two;
}

TEST(matrix_fill_border) {
  Matrix *mat = new Matrix;
  Matrix *mat_two = new Matrix;
  const int width = 3;
  const int height = 3;
  Matrix_init(mat, width, height);
  Matrix_init(mat_two, width, height);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, 1);

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      *Matrix_at(mat_two, i, j) = 1;
    }
  }
  *Matrix_at(mat_two, 1, 1) = 0;

  ASSERT_TRUE(Matrix_equal(mat, mat_two))
  delete mat;
  delete mat_two;
}
TEST(matrix_line_v){
  Matrix *mat = new Matrix;
  Matrix *mat_two = new Matrix;
  const int height = 3;
  const int width = 1;

  Matrix_init(mat, width, height);
  Matrix_init(mat_two, width, height);
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  Matrix_fill(mat, 2);
  Matrix_fill_border(mat_two, 2);
  ASSERT_TRUE(Matrix_equal(mat, mat_two));

  for(int i = 0; i < height; i++) {
    ASSERT_EQUAL(*Matrix_at(mat, i, 0), 2);
    ASSERT_EQUAL(*Matrix_at(mat_two, i, 0), 2);
  }
  ostringstream s;
  ostringstream correct;
  correct << "1 3\n";
  correct << "2 \n";
  correct << "2 \n";
  correct << "2 \n";
  Matrix_print(mat, s);

  ASSERT_EQUAL(s.str(), correct.str());

  delete mat;
  delete mat_two;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
