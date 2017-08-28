class Committee {
  public:
  Thread *threads[NUM_THREADS];
  Committee() {
    for (int i = 0; i < NUM_THREADS; ++i) {
      threads[i] = new Thread(i);
    }
  }
  ~Committee();

  void drop_learning_rate() {
    for (int i = 0; i < NUM_THREADS; ++i) {
      for (int j = 0; j < NUM_MEMBERS; ++j) {
        threads[i]->networks[j]->drop_learning_rate();
      }
    }
  }

  int committee_result(float *x) {
    float nums[TOT_RES];
    for (int n = 0; n < TOT_RES; ++n) nums[n] = 0;
    for (int t = 0; t < NUM_THREADS; ++t) {
      for (int m = 0; m < NUM_MEMBERS; ++m) {
        cblas_saxpy(TOT_RES, ALPHA, threads[t]->networks[m]->feedforward(x), INCX, nums, INCY);
      }
    }
    return cblas_isamax(TOT_RES, nums, INCX);
  }

  void test_committee(int epoch) {
    int correct = 0;
    for (int i = 0; i < TOT_VAL; ++i) {
      correct += (committee_result(vdata[i]) == vlabels[i]);
    }
    printf("epoch %d: %d\n", epoch, correct);
  }

  void train_committee() {
    for (int t = 0; t < NUM_THREADS; ++t) {
      threads[t]->begin_threaded_training();
    }
    for (int t = 0; t < NUM_THREADS; ++t) {
      threads[t]->collect_threads();
    }
  }

  void read_network_weights() {
    FILE *data;
    data = fopen("weights.out", "r");
    char line[sizeof(char)*11];
    for (int t = 0; t < NUM_THREADS; ++t) {
      for (int m = 0; m < NUM_MEMBERS; ++m) {
        for (int l = 0; l < NLAYERS; ++l) {
          Layer *layer = threads[t]->networks[m]->l[l];
          for (int i = 0; i < layer->size; ++i) {
            fgets(line, sizeof(line), data);
            layer->W[i] = atof(line);
          }
          for (int i = 0; i < layer->out_size; ++i) {
            fgets(line, sizeof(line), data);
            layer->B[i] = atof(line);
          }
        }
      }
    }
    fclose(data);
  }

  void write_network_weights() {
    FILE *data;
    data = fopen("weights.out", "wb");
    for (int t = 0; t < NUM_THREADS; ++t) {
      for (int m = 0; m < NUM_MEMBERS; ++m) {
        for (int l = 0; l < NLAYERS; ++l) {
          Layer *layer = threads[t]->networks[m]->l[l];
          for (int i = 0; i < layer->size; ++i) {
            fprintf(data, "%f\n", layer->W[i]);
          }
          for (int i = 0; i < layer->out_size; ++i) {
            fprintf(data, "%f\n", layer->B[i]);
          }
        }
      }
    }
    fclose(data);
  }
};
