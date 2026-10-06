/*
Stress test for CF2263C1 - Floor of MEX (Easy version)
Usage:  stress_test <your-solution-exe> [rounds]
Windows PowerShell:  .\stress_test.exe .\sol.exe 200
Windows cmd:         stress_test.exe sol.exe 200
Linux / macOS:       ./stress_test ./sol 200
*/

#include <bits/stdc++.h>
using namespace std;

int mexOfFloors(const vector<int>& B, int k) {   // f(B, k) = mex({ floor(y / k) : y in B })
  set<int> s;
  for (int y : B) s.insert(y / k);
  int m = 0;
  while (s.count(m)) ++m;
  return m;
}

void show(const char* name, const vector<int>& v) {
  cout << name << " = [";
  for (size_t i = 0; i < v.size(); ++i) cout << (i ? ", " : "") << v[i];
  cout << "]\n";
}

int main(int argc, char** argv) {
  string exe = argc > 1 ? argv[1] : "sol.exe";
  int rounds = argc > 2 ? atoi(argv[2]) : 200;
  const int T = 50;                               // test cases per round
  mt19937 rng(12345);                             // fixed seed: same tests every run
  const int density[4] = {10, 30, 60, 90};        // chance (%) that y is in the hidden set

  for (int round = 1; round <= rounds; ++round) {
    // 1. write input.txt: pick a random hidden set, compute a by brute force
    vector<vector<int>> A(T);
    {
      ofstream in("input.txt");
      in << T << '\n';
      for (auto& a : A) {
        int n = (int)(rng() % 12) + 1;
        int p = density[rng() % 4];
        vector<int> hidden;
        for (int y = 0; y < n; ++y)
          if ((int)(rng() % 100) < p) hidden.push_back(y);
        a.resize(n);
        for (int k = 1; k <= n; ++k) a[k - 1] = mexOfFloors(hidden, k);
        in << n << '\n';
        for (int x : a) in << x << ' ';
        in << '\n';
      }
    }

    // 2. run your program: input.txt -> output.txt
    string cmd = exe + " < input.txt > output.txt";
    if (system(cmd.c_str()) != 0) {
      cout << "Your program crashed or could not be started.\nCommand tried: " << cmd << '\n';
      return 1;
    }

    // 3. check every answer: it must really produce the array a
    ifstream out("output.txt");
    for (int c = 0; c < T; ++c) {
      int n = (int)A[c].size(), m;
      vector<int> B;
      string why;
      if (!(out >> m) || m < 0 || m > n) why = "the printed size m is missing or out of range";
      else {
        B.resize(m);
        for (int& y : B)
          if (!(out >> y)) { why = "the output ended before all m numbers were printed"; break; }
      }
      if (why.empty()) {
        set<int> seen;
        for (int y : B) {
          if (y < 0 || y >= n) { why = "an element is outside 0 .. n-1"; break; }
          if (!seen.insert(y).second) { why = "an element is printed twice"; break; }
        }
      }
      if (why.empty())
        for (int k = 1; k <= n; ++k)
          if (mexOfFloors(B, k) != A[c][k - 1]) {
            why = "f(B, " + to_string(k) + ") = " + to_string(mexOfFloors(B, k)) + " but a_" + to_string(k) + " = " + to_string(A[c][k - 1]);
            break;
          }
      if (!why.empty()) {
        cout << "FAIL in round " << round << ", test case " << c + 1 << "\nn = " << n << '\n';
        show("a", A[c]); show("your B", B);
        cout << "Reason: " << why << '\n';
        return 1;
      }
    }
  }
  cout << "OK: " << rounds * T << " random cases passed\n";
}