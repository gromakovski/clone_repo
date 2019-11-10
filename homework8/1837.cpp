

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

#include <deque>
#include <map>
#include <set>
#include <vector>

using studentsliist = std::vector<std::string>;
using uniquestudents = std::map<std::string, studentsliist>;

//граф в виде списка смежности
uniquestudents students;

//список уникальных студентов для ответа
std::set<std::string> ans;

#define TESTING

int main(int argc, char const* argv[]) {
#ifdef TESTING
  std::istringstream testin(
      "7 "
      "Isenbaev Oparin Toropov "
      "Ayzenshteyn Oparin Samsonov "
      "Ayzenshteyn Chevdar Samsonov "
      "Fominykh Isenbaev Oparin "
      "Dublennykh Fominykh Ivankov "
      "Burmistrov Dublennykh Kurpilyanskiy "
      "Cormen Leiserson Rivest ");

  //  std::istringstream testin(
  //      "1 "
  //      "a b c ");
#endif

  int n;
#ifdef TESTING
  testin >> n;
#else
  std::cin >> n;
#endif

  std::string a, b, c;
  for (long long i = 0; i < n; i++) {
#ifdef TESTING
    testin >> a >> b >> c;
#else
    std::cin >> a >> b >> c;
#endif

    //делаем мап из где key это имя студента
    //а value это vector из имен других студентов
    //котрые когда либо играл с ним в команде
    // A
    students[a].push_back(b);
    students[a].push_back(c);
    // B
    students[b].push_back(a);
    students[b].push_back(c);
    // C
    students[c].push_back(a);
    students[c].push_back(b);

    /// Dobavlenie///
    ans.insert(a);
    ans.insert(b);
    ans.insert(c);
  }
#ifdef TESTING
  for (auto& student : students) {
    std::cout << student.first << " - ";
    for (auto& lstudent : student.second) {
      std::cout << lstudent << " ";
    }
    std::cout << std::endl;
  }
#endif

  std::map<std::string, long long> to,  //мап с глубинами до узлов
      used,  //мап с использованными узлами
      dp;    //мап с глубинами узлов
  dp["Isenbaev"] = 1;
  used["Isenbaev"] = 1;
  std::deque<std::string> dk;
  dk.push_back("Isenbaev");
  while (!dk.empty()) {
    std::string id = dk.front();
    dk.pop_front();
    for (auto st : students[id]) {
      if (used[st] == 0) {
        used[st] = 1;
        to[st] = dp[id];
        dp[st] = dp[id] + 1;
        dk.push_back(st);
      }
    }
  }

  for (auto student : ans) {
    if (student == "Isenbaev" || to[student] != 0)
      std::cout << student << " " << to[student] << std::endl;
    else
      std::cout << student << " "
                << "undefined" << std::endl;
  }

  return 0;
}
