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

    std::string sFileContent1;
    std::string sFileContent2;
    WsjcppCore::readTextFile(sFileName1, sFileContent1);
    WsjcppCore::readTextFile(sFileName2, sFileContent2);

    std::vector<WsjcppDiffTextRow> vResult;
    WsjcppDiffText::compare(sFileContent1, sFileContent2, vResult);
    for (int i = 0; i < vResult.size(); i++) {
        std::cout << 
            vResult[i].getKey() << " => line (" << vResult[i].getNumberOfLine() << "): " 
            << vResult[i].getLine() << std::endl;
    }
    vResult.clear();
    return 0;
}

