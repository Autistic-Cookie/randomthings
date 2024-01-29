#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

void trim_whitespace(string_view &isvw) {
  while (isvw.size() > 0 && isvw[0] == ' ')
    isvw.remove_prefix(1);
  while (isvw.size() > 0 && isvw[isvw.size() - 1] == ' ')
    isvw.remove_suffix(1);
}

void parse_string_invw(string_view ins, vector<string_view> &outstrs,
                       char delim) {
  int b = 0;
  string_view lsv{};
  for (int x = 0; x < ins.size(); x++) {
    if (ins[x] == delim) {
      lsv = string_view(ins.begin() + b, ins.begin() + x);
      trim_whitespace(lsv);
      outstrs.push_back(lsv);
      b = x + 1;
    }
  }
  if (b < ins.size()) {
    lsv = string_view(ins.begin() + b, ins.end());
    trim_whitespace(lsv);
    outstrs.push_back(lsv);
  }
}

int svwtoi(string_view &words) {
  int li;
  from_chars(words.data(), words.data() + words.size(), li);
  return li;
}

int main() {
  ifstream ifs("aoc2023-4b.txt");
  string str;
  vector<string_view> spl{}, anums{}, wnums{}, onums{};
  map<int, int> mint{};
  vector<int> vint{}, vints{};
  int suma = 0;
  while (getline(ifs, str)) {
    mint.clear();
    parse_string_invw(string_view(str.begin(), str.end()), spl, ':');
    parse_string_invw(spl[1], anums, '|');
    parse_string_invw(anums[0], wnums, ' ');
    parse_string_invw(anums[1], onums, ' ');
    for (auto b : wnums) {
      if (b != "")
        mint[svwtoi(b)]++;
      cout << b << ", ";
    }
    cout << "<>";
    for (auto b : onums) {
      if (b != "")
        mint[svwtoi(b)]++;
      cout << b << ", ";
    }
    cout << "{}";
    spl.clear();
    anums.clear();
    wnums.clear();
    onums.clear();
    int cnt2 = 0;
    for (auto b : mint) {
      cout << "{**" << b.first << " " << b.second << "**}";
      if (b.second == 2)
        cnt2++;
    }
    /// if (cnt2 > 0)
    vint.push_back(cnt2);
    // else
    //   vint.push_back(0);
    vints.push_back(1);
    // mint.clear();
    cout << "[**" << cnt2 << "**]";
    if (cnt2 > 0)
      suma += (1 << (cnt2 - 1));
  }
  cout << "\n" << suma << "\n";
  for (int x = 0; x < vint.size(); x++) {
    int xx = vint[x];
    int xy = vints[x];
    cout << xx << " = ";
    for (int x1 = x + 1; (x1 < x + xx + 1) && (x1 < vint.size()); x1++) {
      vints[x1] += xy;
    }
    for (auto f : vints)
      cout << f << "..";
    cout << "\n";
  }
  int sumb = 0;
  for (auto b : vints) {
    cout << b << " -- ";
    sumb += b;
  }
  cout << "\n" << sumb << "\n";
  return 0;
}