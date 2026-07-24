#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_diff_text.h>

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " file1 file2" << std::endl;
    return -1;
  }

  std::string TAG = "MAIN";
  std::string appName = std::string(WSJCPP_APP_NAME);
  std::string appVersion = std::string(WSJCPP_APP_VERSION);
  if (!WsjcppCore::dirExists(".logs")) {
    WsjcppCore::makeDir(".logs");
  }
  WsjcppLog::setPrefixLogFile("wsjcpp-diff-text");
  WsjcppLog::setLogDirectory(".logs");

  std::string sFileName1(argv[1]);
  std::string sFileName2(argv[2]);

  if (!WsjcppCore::fileExists(sFileName1)) {
    WsjcppLog::err(TAG, "file1 not found '" + sFileName1 + "'");
    return -1;
  }

  if (!WsjcppCore::fileExists(sFileName2)) {
    WsjcppLog::err(TAG, "file2 not found '" + sFileName2 + "'");
    return -1;
  }

  std::string file_content1;
  std::string file_content2;
  WsjcppCore::readTextFile(sFileName1, file_content1);
  WsjcppCore::readTextFile(sFileName2, file_content2);

  std::vector<wsjcpp::diff_text_row> result;
  wsjcpp::diff_text_compare(file_content1, file_content2, result);
  for (int i = 0; i < result.size(); i++) {
    std::cout
      << result[i].getKey() << " => line (" << result[i].getNumberOfLine() << "): "
      << result[i].line()
      << std::endl;
  }
  result.clear();
  return 0;
}

