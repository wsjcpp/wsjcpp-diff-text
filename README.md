# wsjcpp-diff-text

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-diff-text.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-diff-text) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-diff-text.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-diff-text) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-diff-text.svg)](https://github.com/wsjcpp/wsjcpp-diff-text) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-diff-text.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-diff-text/network/members) [![Total alerts](https://img.shields.io/lgtm/alerts/g/wsjcpp/wsjcpp-diff-text.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-diff-text/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wsjcpp/wsjcpp-diff-text.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wsjcpp/wsjcpp-diff-text/context:cpp)

Algorithm for like a diff texts


## Integrate to your project

```
wsjcpp install "https://github.com/wsjcpp/wsjcpp-diff-text:master"
```

Or copy files to project:

* src.wsjcpp/wsjcpp_core/wsjcpp_core.h
* src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
* src/wsjcpp_diff_text.h
* src/wsjcpp_diff_text.cpp

## Examples

```cpp
#include <wsjcpp_core.h>
#include <wsjcpp_diff_text.h>

std::string sFileContent1;
std::string sFileContent2;
WsjcppCore::readTextFile("data/file1.txt", sFileContent1);
WsjcppCore::readTextFile("data/file1.txt", sFileContent2);

std::vector<wsjcpp::diff_text_row> result;
WsjcppDiffText::compare(sFileContent1, sFileContent2, result);
for (int i = 0; i < result.size(); i++) {
    std::cout
        << result[i].key() << " => line (" << result[i].number_of_line() << "): "
        << result[i].line() << std::endl;
}
```

example output:
```
!del => line (1): 22222
!add => line (6): 71111
!add => line (10): 11111
```




