/*
 * MIT License
 *
 * Copyright (c) 2019-2026 Evgenii Sopov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

// original source-code: https://github.com/wsjcpp/wsjcpp-core

#include <vector>
#include <iostream>
#include <wsjcpp_diff_text.h>

int main() {
  int found_errors = 0;

  struct LTest {
    LTest(
        std::string txt1,
        std::string txt2,
        std::string txt3,
        unsigned int n
    ) : txt1(txt1), txt2(txt2), txt3(txt3), n(n) {
        //
    }
    std::string txt1;
    std::string txt2;
    std::string txt3;
    unsigned int n;
  };

  std::vector<LTest *> tests1;
  std::vector<wsjcpp::diff_text_row> arr1, arr2;

  //empty (Test №1)
  tests1.push_back(new LTest("", "", "", 0));
  //without any difference (Test №2)
  tests1.push_back(new LTest("I\ngot\nMike", "I\ngot\nMike", "I\ngot\nMike", 0));
  //with a difference in the ending (Tests №3-6)
  tests1.push_back(new LTest("I\ngot\nMike", "I\ngot\nMike", "I\ngot\nNike", 1));
  tests1.push_back(new LTest("I\ngot\nNike", "I\ngot\nMike", "I\ngot\nMike", 1));
  tests1.push_back(new LTest("I\ngot\nNike", "I\ngot\nMike", "I\ngot\nNike", 1));
  tests1.push_back(new LTest("I\ngot\nBike", "I\ngot\nMike", "I\ngot\nNike", 1));
  //with a difference in the beginning (Tests №7-10)
  tests1.push_back(new LTest("I\ngot\nMike", "I\ngot\nMike", "You\ngot\nMike", 1));
  tests1.push_back(new LTest("You\ngot\nMike", "I\ngot\nMike", "I\ngot\nMike", 1));
  tests1.push_back(new LTest("You\ngot\nMike", "I\ngot\nMike", "You\ngot\nMike", 1));
  tests1.push_back(new LTest("We\ngot\nMike", "I\ngot\nMike", "You\ngot\nMike", 1));
  //with a difference in the middle of the row (Tests №11-15)
  tests1.push_back(new LTest("I\nhave\ncute\ncats", "I\nhave\ncute\ncats", "I\nhave\nhuge\ncats", 1));
  tests1.push_back(new LTest("I\nhave\nhuge\ncats", "I\nhave\ncute\ncats", "I\nhave\ncute\ncats", 1));
  tests1.push_back(new LTest("I\nhave\nhuge\ncats", "I\nhave\ncute\ncats", "I\nhave\nhuge\ncats", 1));
  tests1.push_back(new LTest("I\nhave\ndifference\ncats", "I\nhave\ncute\ncats", "I\nhave\nhuge\ncats", 1));
  tests1.push_back(new LTest("I\nbetray\ncats", "I\nhave\ncats", "I\nlove\ncats", 1));
  //delete lines from the end of text (Tests №16-19)
  tests1.push_back(new LTest("Go\nto\nthe\nschool", "Go\nto\nthe\nschool", "Go\nto", 2));
  tests1.push_back(new LTest(
    "Go\nto", "Go\nto\nthe\nschool", "Go\nto\nthe\nschool", 2
  ));
  tests1.push_back(new LTest("Go\nto\nthe", "Go\nto\nthe\nschool", "Go\nto", 2));
  tests1.push_back(new LTest("Go\nto", "Go\nto\nthe\nschool", "Go\nto\nthe", 2));
  //add lines in the end of text (Tests №20-23)
  tests1.push_back(new LTest("Go\nto", "Go\nto", "Go\nto\nthe\nschool", 2));
  tests1.push_back(new LTest("Go\nto\nthe\nschool", "Go\nto", "Go\nto", 2));
  tests1.push_back(new LTest("Go\nto\nthe", "Go\nto", "Go\nto\nthe\nschool", 2));
  tests1.push_back(new LTest("Go\nto\nthe\nschool", "Go\nto", "Go\nto\nthe", 2));
  //delete rows from the beginning and the middle of text (Tests №24-27)
  tests1.push_back(new LTest("Go\nto\nthe\nschool", "Go\nto\nthe\nschool", "the\nschool", 2));
  tests1.push_back(new LTest("the\nschool", "Go\nto\nthe\nschool", "Go\nto\nthe\nschool", 2));
  tests1.push_back(new LTest("Go\nto\nthe\nschool", "Go\nto\nthe\nschool", "Go\nto\nschool", 1));
  tests1.push_back(new LTest("Go\nto\nschool", "Go\nto\nthe\nschool", "Go\nto\nthe\nschool", 1));
  //add rows to the beginning and the middle of text (Tests №28-31)
  tests1.push_back(new LTest("the\nschool", "the\nschool", "Go\nto\nthe\nschool", 2));
  tests1.push_back(new LTest("Go\nto\nthe\nschool", "the\nschool", "the\nschool", 2));
  tests1.push_back(new LTest("Go\nthe\nschool", "the\nschool", "the\nschool", 1));
  tests1.push_back(new LTest("the\nschool", "the\nschool", "Go\nthe\nschool", 1));
  //complex (Tests №32-33)
  tests1.push_back(new LTest("You\nare\ngot\nand\ngood", "I\ngot\nMike\nand\nthis is\ngood\nboy", "I\ncure\ndamn\nill\ncancer", 8));
  tests1.push_back(new LTest("We\nspent\nthe rest\nof our life\non\nthis\ncourse\nwork", "We\nspent\na lot of\ntime\non\nthis\ncourse\nwork", "We\ngonna\nspend\na lot of\nfunky\ntime\non\ncourse\nwork", 6));

  for (unsigned int i = 0; i < tests1.size(); i++) {
    std::string txt1 = tests1[i]->txt1;
    std::string txt2 = tests1[i]->txt2;
    std::string txt3 = tests1[i]->txt3;
    wsjcpp::diff_text_merge(txt1, txt2, txt3, arr1, arr2);
    unsigned int n = tests1[i]->n;

    if (arr1.size() != n) {
      found_errors++;
      std::cerr << "In the test #" << (i + 1) << " the length of the vector is expected: "
              << n << ", but got: " << arr1.size() << std::endl;
    }
    arr1.clear();
    arr2.clear();
  }

  //sort module test
  struct LTest2 {
    LTest2(
      std::string txt1,
      std::string txt2,
      std::string txt3,
      std::vector<wsjcpp::diff_text_row> arr1,
      std::vector<wsjcpp::diff_text_row> arr2,
      std::vector<wsjcpp::diff_text_row> arr3
    ) : txt1(txt1), txt2(txt2), txt3(txt3), arr1(arr1), arr2(arr2), arr3(arr3) {
    }

    std::string txt1;
    std::string txt2;
    std::string txt3;
    std::vector<wsjcpp::diff_text_row> arr1;
    std::vector<wsjcpp::diff_text_row> arr2;
    std::vector<wsjcpp::diff_text_row> arr3;
  };

  std::vector<LTest2 *> tests2;
  std::vector<wsjcpp::diff_text_row> arr3;
  int id[8] = {0,1,1,2,3,4,5,6};
  std::vector<std::string> skey;
  skey.push_back("I");
  skey.push_back("got");
  skey.push_back("!add");
  skey.push_back("Mike");
  skey.push_back("and");
  skey.push_back("this is");
  skey.push_back("!del");
  skey.push_back("!del");

  std::vector<std::string> sline;
  sline.push_back("You");
  sline.push_back("cure");
  sline.push_back("are");
  sline.push_back("damn");
  sline.push_back("ill");
  sline.push_back("cancer");
  sline.push_back("good");
  sline.push_back("boy");

  for (int i = 0; i < skey.size(); ++i) {
    arr3.push_back(wsjcpp::diff_text_row(id[i], skey.at(i), sline.at(i)));
  }

  tests2.push_back(new LTest2(
    "You\nare\ngot\nand\ngood",
    "I\ngot\nMike\nand\nthis is\ngood\nboy",
    "I\ncure\ndamn\nill\ncancer",
    arr1, arr2, arr3));

  std::string txt1 = tests2[0]->txt1;
  std::string txt2 = tests2[0]->txt2;
  std::string txt3 = tests2[0]->txt3;
  wsjcpp::diff_text_merge(txt1, txt2, txt3, arr1, arr2);

  for (int i = 0; i < 8; ++i) {
    int id1 = arr1[i].getNumberOfLine();
    int id2 = arr3[i].getNumberOfLine();
    std::string key1 = arr1[i].getKey();
    std::string key2 = arr3[i].getKey();
    std::string line1 = arr1[i].line();
    std::string line2 = arr3[i].line();
    if (id1 != id2) {
      found_errors++;
      std::cerr << "In the sort test in the element #" << std::to_string(i + 1) << ": id1 != id2" << std::endl;
    }

    if (key1 != key2) {
      found_errors++;
      std::cerr << "In the sort test in the element #" << std::to_string(i + 1) << ": key1 != key2" << std::endl;
    }
    if (line1 != line2) {
      found_errors++;
      std::cerr << "In the sort test in the element #" << std::to_string(i + 1) << ": line1 != line2" << std::endl;
    }
  }


  if (found_errors > 0) {
    return 1;
  }

  std::cout << "ok" << std::endl;
  return 0;
}
