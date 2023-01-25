// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_init_hw) {
  Image *img = new Image;

  int width1 = 5;
  int height1 = 11;
  int width2 = 1;
  int height2 = 9;

  Image_init(img, width1, height1);

  ASSERT_TRUE(Image_width(img) == width1);
  ASSERT_TRUE(Image_height(img) == height1);

  Image_init(img, width2, height2);

  ASSERT_TRUE(Image_width(img) == width2);
  ASSERT_TRUE(Image_height(img) == height2);

  delete img;
}

TEST(test_image_width) {
  Image *img = new Image;
  
  Image_init(img, 6, 20);
  ASSERT_TRUE(Image_width(img) == 6);
  
  Image_init(img, 145, 300);
  ASSERT_TRUE(Image_width(img) == 145);

  delete img;
}

TEST(test_image_height) {
  Image *img = new Image;
  
  Image_init(img, 2, 19);

  ASSERT_TRUE(Image_height(img) == 19);
  ASSERT_TRUE(Image_width(img) == 2);

  delete img;
}

TEST(test_get_pixel) {
  Image *img = new Image;
  Pixel p1 = {10, 30, 70};
  string input = "P3\n3 3\n255\n200 10 0 110 15 240 0 200 0 \n0 220 10 30 40 60 10 30 70 \n0 0 255 255 0 235 60 10 0 ";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 2), p1));

  delete img;
}

TEST(test_image_set_pixel) {
  Image *img = new Image;
  Pixel p1 = {45, 0, 255};

  Image_init(img, 3, 3);

  Image_set_pixel(img, 2, 2, p1);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), p1));

  delete img;
}

TEST(test_image_fill){
  Image *img = new Image;
  Pixel p1 = {45, 255, 0};

  Image_init(img, 2, 2);
  Image_fill(img, p1);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), p1));

  Image *img1 = new Image;
  
  Pixel p2 = {45, 255, 0};
  Image_init(img1, 2, 2);
  Image_set_pixel(img1, 0, 0, p2);
  Image_set_pixel(img1, 0, 1, p2);
  Image_set_pixel(img1, 1, 0, p2);
  Image_set_pixel(img1, 1, 1, p2);

  ASSERT_TRUE(Image_equal(img, img1));

  delete img;
  delete img1;
}

TEST(image_pring){
  Image *img = new Image;

  Image_init(img, 2, 2);

  Pixel p1 = {10, 20, 30};
  Pixel p2 = {40, 50, 60};
  Pixel p3 = {70, 80, 90};
  Pixel p4 = {100, 110, 120};

  Image_set_pixel(img, 0, 0, p1);
  Image_set_pixel(img, 0, 1, p2);
  Image_set_pixel(img, 1, 0, p3);
  Image_set_pixel(img, 1, 1, p4);

  string output_correct = "P3\n2 2\n255\n10 20 30 40 50 60 \n70 80 90 100 110 120 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string output = ss_output.str();

  ASSERT_EQUAL(output, output_correct);

  delete img;
}

TEST(image_init_rw){
  Image *img = new Image;

  string input = "P3\n2 2\n255\n1 2 3 4 5 6\n7 8 9 10 11 12 \n";
  std::istringstream test_input(input);
  Image_init(img, test_input);

  ASSERT_EQUAL(Image_width(img), 2);

  Pixel p1 = {7, 8, 9};

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), p1));

  delete img;
}



// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
