#include "pad.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

static WINDOW *log_win = nullptr;
static std::vector<std::string> log_lines;

static void redraw_log() {
  int rows, cols;
  getmaxyx(log_win, rows, cols);
  werase(log_win);
  int start = (int)log_lines.size() > rows ? (int)log_lines.size() - rows : 0;
  for (int i = start; i < (int)log_lines.size(); ++i)
    mvwaddnstr(log_win, i - start, 0, log_lines[i].c_str(), cols);
  wrefresh(log_win);
}

static void add_log(const std::string &line) {
  log_lines.push_back(line);
  redraw_log();
}

static void on_result(const char *data, size_t len, void * /*ctx*/) {
  add_log(std::string(data, len));
}

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  log_win = newwin(rows - 2, cols, 0, 0);

  WINDOW *sep_win = newwin(1, cols, rows - 2, 0);
  whline(sep_win, ACS_HLINE, cols);
  wrefresh(sep_win);

  WINDOW *input_win = newwin(1, cols, rows - 1, 0);

  std::string input;

  auto redraw_input = [&]() {
    werase(input_win);
    mvwaddstr(input_win, 0, 0, "> ");
    waddstr(input_win, input.c_str());
    wrefresh(input_win);
  };

  redraw_input();

  while (true) {
    int ch = wgetch(input_win);

    if (ch == '\n' || ch == KEY_ENTER) {
      if (input == "q" || input == "quit" || input == "exit")
        break;
      if (!input.empty()) {
        add_log("> " + input);
        pad_quote(input.c_str(), on_result, nullptr);
        input.clear();
      }
    } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
      if (!input.empty())
        input.pop_back();
    } else if (ch >= 32 && ch < 127) {
      input += static_cast<char>(ch);
    } else if (ch == 3 || ch == 4) {
      break;
    }

    redraw_input();
  }

  endwin();
  return 0;
}
