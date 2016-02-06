#include <iostream>
#include <vector>
#include <string>

using namespace std;

int r, c;

int main() {
  cin >> r >> c;
  vector<vector<bool> > picture;
  picture.resize(r);
  for (int i = 0; i < r; ++i) {
    picture[i].resize(c);
    string row;
    cin >> row;
    for (int j = 0; j < c; ++j) {
      picture[i][j] = (row[j] == '#');
    }
  }

  vector<string> commands;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (picture[i][j] == true) {
	string command = "PAINT_SQUARE ";
	command += to_string(i);
	command += " ";
	command += to_string(j);
	command += " 0";
	commands.push_back(command);
      }
    }
  }

  cout << commands.size() << endl;
  for (int i = 0; i < commands.size(); ++i) {
    cout << commands[i] << endl;
  }
  return 0;
}
