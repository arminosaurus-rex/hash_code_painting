#include <iostream>
#include <vector>
#include <string>

using namespace std;

static const int penalty = 10;
int r, c;

enum CommandType {
  Square = 0,
  Line = 1,
  Delete = 2,
};

struct Command {
  CommandType type;
  int arg1;
  int arg2;
  int arg3;
  int arg4;
};

vector<Command> all_commands;

int max_d(int x, int y) {
  return min(min(min(x, y), r-x-1), c-y-1);
}

void fill_commands() {
  for (int x = 0; x < r; ++x) {
    for (int y = 0; y < c; ++y) {
      for (int d = 0; d < max_d(x, y); ++d) {
	all_commands.push_back({CommandType::Square, x, y, d, 0});
      }
    }
  }

  for (int xmin = 0; xmin < r; ++xmin) {
    for (int xmax = xmin + 1; xmax < r; ++xmax) {
      for (int y = 0; y < c; ++y) {
	all_commands.push_back({CommandType::Line, xmin, y, xmax, y});
      }
    }
  }

  for (int x = 0; x < r; ++x) {
    for (int ymin = 0; ymin < c; ++ymin) {
      for (int ymax = ymin + 1; ymax < c; ++ymax) {
	all_commands.push_back({CommandType::Line, x, ymin, x, ymax});
      }
    }
  }

  for (int x = 0; x < r; ++x) {
    for (int y = 0; y < c; ++y) {
      all_commands.push_back({CommandType::Delete, x, y, 0, 0});
    }
  }
}

typedef vector<vector<bool> > Picture;

int Diff(const Picture& src, const Picture& target) {
  int delta = 0;
  for (int x = 0; x < r; ++x) {
    for (int y = 0; y < c; ++y) {
      if (src[x][y] == false && target[x][y] == true)
	delta += 1;
      else if (src[x][y] == true && target[x][y] == false)
	delta += penalty;
    }
  }
  return delta;
}

Picture Apply(const Picture& in, Command cmd) {
  Picture out = in;
  switch (cmd.type) {
  case CommandType::Square:
    for (int x = cmd.arg1 - cmd.arg3; x <= cmd.arg1 + cmd.arg3; ++x) {
      for (int y = cmd.arg2 - cmd.arg3; y <= cmd.arg2 + cmd.arg3; ++y) {
	out[x][y] = true;
      }
    }
    break;
  case CommandType::Line:
    for (int x = cmd.arg1; x <= cmd.arg3; ++x) {
      for (int y = cmd.arg2; y <= cmd.arg4; ++y) {
	out[x][y] = true;
      }
    }
    break;
  case CommandType::Delete:
    out[cmd.arg1][cmd.arg2] = false;
  }
  return out;
}

Picture Empty() {
  Picture picture;
  picture.resize(r);
  for (int i = 0; i < r; ++i) {
    picture[i].resize(c, false);
  }
  return picture;
}

vector<Command> Greedy(const Picture& target) {
  vector<Command> stack;
  Picture cur = Empty();
  while (Diff(cur, target) > 0) {
    Command best_try = all_commands[0];
    int lowest_delta = 1 << 28;

    //    cout << "New iteration. Delta = " << Diff(cur, target) << endl;

    for (int i = 0; i < all_commands.size(); ++i) {
      int delta = Diff(Apply(cur, all_commands[i]), target);
      if (delta < lowest_delta) {
	lowest_delta = delta;
	best_try = all_commands[i];
      }
    }
    cur = Apply(cur, best_try);
    stack.push_back(best_try);
  }
  return stack;
}

void print_output(const vector<Command>& cmds) {
  cout << cmds.size() << endl;
  for (int i = 0; i < cmds.size(); ++i) {
    Command cmd = all_commands[i];
    switch (cmd.type) {
    case CommandType::Square:
      cout << "PAINT_SQUARE "
	   << cmd.arg1 << " " << cmd.arg2 << " " << cmd.arg3 << endl;
      break;
    case CommandType::Line:
      cout << "PAINT_LINE "
	   << cmd.arg1 << " " << cmd.arg2 << " " << cmd.arg3 << " " << cmd.arg4
	   << endl;
      break;
    case CommandType::Delete:
      cout << "ERASE_CELL "
	   << cmd.arg1 << " " << cmd.arg2 << endl;
      break;
    }
  }
}

int main() {
  cin >> r >> c;
  Picture picture = Empty();
  for (int i = 0; i < r; ++i) {
    string row;
    cin >> row;
    for (int j = 0; j < c; ++j) {
      picture[i][j] = (row[j] == '#');
    }
  }

  fill_commands();
  vector<Command> commands = Greedy(picture);
  print_output(commands);
  return 0;
}
