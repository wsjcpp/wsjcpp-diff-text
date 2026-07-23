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
        std::string text,
        std::vector<std::string> expected
    ) : text(text), expected(expected) {
    }
    std::string text;
    std::vector<std::string> expected;
  };

  std::vector<LTest> tests;

  tests.push_back(LTest("", {}));
  tests.push_back(LTest("line1\nline2", {"line1", "line2"}));
  tests.push_back(LTest("Str1\n"
    "Str \n"
    "Str\n"
    "Str\n"
    "Str2\n"
    "Str\n"
    "Str3\n"
    "Str\n"
    "Str\n"
    "Str\n", {"Str1", "Str ", "Str", "Str", "Str2", "Str", "Str3", "Str", "Str", "Str"}));



  for (unsigned int i = 0; i < tests.size(); i++) {
    LTest test = tests[i];
    std::vector<std::string> output;
    wsjcpp::diff_text_split(test.text, output);

    if (output.size() != test.expected.size()) {
      found_errors++;
      std::cerr << "In the test #" << (i + 1) << " the length of the vector is expected: "
              << test.expected.size() << ", but got: " << output.size() << std::endl;
    } else {
      for (int l = 0; l < test.expected.size(); l++) {
        if (test.expected[l] != output[l]) {
          found_errors++;
          std::cerr << "In the test #" << (i + 1) << " the line expected(" << l << "): '"
            << test.expected[l] << "', but got '" << output[l] << std::endl;
        }
      }
    }
  }

  if (found_errors > 0) {
    return 1;
  }

  std::cout << "ok" << std::endl;
  return 0;
}