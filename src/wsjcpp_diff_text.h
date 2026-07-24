#ifndef WSJCPP_DIFF_TEXT_H
#define WSJCPP_DIFF_TEXT_H


#include <vector>
#include <string>

namespace wsjcpp {

enum class diff_text_row_action {
  NONE,
  INSERT,
  DELETE
};

class diff_text_row {
public:
  diff_text_row(
    int number_of_line,
    const std::string &key,
    const std::string &line
  );
  int number_of_line() const;
  std::string key() const;
  diff_text_row_action action() const;
  bool is_delete() const;
  bool is_insert() const;
  std::string line() const;

private:
  int m_number_of_line;
  std::string m_key;
  std::string m_line;
};

void diff_text_split(
  const std::string &text,
  std::vector<std::string> &output
);

void diff_text_compare(
  const std::string &text_left,
  const std::string &text_right,
  std::vector<diff_text_row> &output_diff
);

void diff_text_merge(
  std::string &curtxt,
  std::string &txt1,
  std::string &txt2,
  std::vector<wsjcpp::diff_text_row> &arr1,
  std::vector<wsjcpp::diff_text_row> &arr2
);

} // namespace wsjcpp

#endif // WSJCPP_DIFF_TEXT_H
