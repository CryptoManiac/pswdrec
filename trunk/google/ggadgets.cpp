#include "ggadgets.h"

#include <QDebug>


int Compute(char salt1, char salt2, const char *input, size_t input_size, std::string *output) {
    int x = salt1 * 30103 + salt2 * 70607;
    for (size_t i = 0; i < input_size; i++) {
      output->append(1, static_cast<char>(input[i] ^ (x >> 16)));
      x = x * 275604541 + 15485863;
    }
    return x;
  }

bool Decrypt(const std::string &input, std::string *output) {
    output->clear();

 if (input.size() < 3)

      return false;

    int x = Compute(input[0], input[1], input.c_str() + 2, input.size() - 3, output);
    if (input[input.size() - 1] != static_cast<char>(x)) {
      output->clear();
      return false;
    }

    return true;
  }


std::string UnescapeValue(const std::string &input) {
    std::string result;
    result.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++) {
      char c = input[i];
      if (c == '=' && i < input.size() - 2) {
        unsigned int t;
        sscanf(input.c_str() + i + 1, "%02X", &t);
        c = static_cast<char>(t);
        i += 2;
      }
      result.append(1, c);
    }
    return result;
  }

ggadgets::ggadgets()
{
    std::string value_str = UnescapeValue("=00=AF=8A.L{!=A8=C8=8C=92=1F=83");
    std::string temp(value_str);
    Decrypt(temp, &value_str);
    qDebug() << value_str.data();
}
