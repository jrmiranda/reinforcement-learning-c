#include <iostream>
#include <omp.h>
#include <iomanip>
#include "env.cpp"

using namespace std;

int argmax(float vector[4]) {
  int i = 0, max;
  while (i < 4) {
    if (i == 0) max = i;
    else max = vector[i] > vector[i-1] ? i : max;
    i++;
  }
  return max;
}

float max(float vector[4]) {
  int i = 0, max;
  while (i < 4) {
    if (i == 0) max = i;
    else max = vector[i] > vector[i-1] ? i : max;
    i++;
  }
  return vector[max];
}

void print_Q(float Q[16][4]) {
  int i, j, s = 0;
  for (i = 0; i < 16; i++) {
    cout << " " << s << " |\t";
    for (j = 0; j < 4; j++) {
      cout << fixed << setprecision(2) << Q[i][j] << "\t|\t";
    }
    s++;
    cout << "\n-----------------------------------------------------------------\n";
  }
}

void play(Env env, float Q[16][4]) {
  int a, state = env.reset();
  while (!env.done) {
    a = argmax(Q[env.state]);
    env.step(a);
    cout << "State: " << env.state << "\n";
  }
}

int main(int argc, char **argv) {
  float Q[16][4] = { 0 };
  int episodes = 500;
  float lr = 0.9;
  float y = 0.90;
  float eps = 0.5;
  float eps_decay = 0.99;
  float r_eps;
  int e, a, state;
  Env env;

  for (e = 0; e < episodes; e++) {
    state = env.reset();
    eps *= eps_decay;
    while (!env.done) {
      r_eps = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      if (r_eps < eps) {
        a = rand() % 4;
      } else {
        a = argmax(Q[env.state]);
      }
      env.step(a);
      Q[state][a] += lr * (env.reward + y*max(Q[env.state]) - Q[state][a]);
      state = env.state;
    }
  }

  print_Q(Q);
  play(env, Q);
  return 0;
}