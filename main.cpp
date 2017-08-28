#include "header.h"
#include "load_data.cpp"
#include "layer.cpp"
#include "wobbler.cpp"
#include "network.cpp"
#include "thread.cpp"
#include "committee.cpp"

int main() {
  load_testing_data();
  load_training_data();

  Committee* com = new Committee();
  com->read_network_weights();
  for (int i = 1; i <= EPOCHS; ++i) {
    com->train_committee();
    com->test_committee(i);
    com->write_network_weights();
    com->drop_learning_rate();
  }
  return 0;
}
