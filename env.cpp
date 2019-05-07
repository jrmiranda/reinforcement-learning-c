#include <iostream>
#include <omp.h>

using namespace std;

#define ROWS 4
#define COLS 4
#define START 0
#define END 15
#define FAIL 5

class Env {
  public:
    int states[ROWS * COLS];
    int actions[ROWS * COLS][4];
    int rewards[ROWS * COLS];
    int state = 0;
    int reward = 0;
    bool done = false;

    Env(void) {
      int i, j, k, s;
      int top, right, bottom, left;
      int state_actions[4];
      s = 0;
      for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
          state_actions[0] = i == 0 ? s : s - 4;
          state_actions[1] = j == (COLS-1) ? s : s + 1;
          state_actions[2] = i == (ROWS-1) ? s : s + 4;
          state_actions[3] = j == 0 ? s : s - 1;

          for (k = 0; k < 4; k++) {
            actions[s][k] = state_actions[k];
          }

          rewards[s] = -2;
          s++;
        }
      }
      rewards[5] = -10;
      rewards[7] = 2;
      rewards[12] = -5;
      rewards[13] = -5;
      rewards[15] = 100;
    }

    void debug() {
      int i;
      for (i = 0; i < 16; i++) {
        cout << "State " << actions[i][0] << "\n";
      }
    }

    int reset() {
      state = START;
      reward = 0;
      done = false;
      return state;
    }

    void step(int a) {
      state = actions[state][a];
      reward = rewards[state];
      if (state == END) done = true;
      if (state == FAIL) done = true;
    }
};