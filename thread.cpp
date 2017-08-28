class Thread {
  pthread_t thread;
  public:
  Network *networks[NUM_MEMBERS];
  Thread(int i) {
    for (int j = 0; j < NUM_MEMBERS; ++j) {
      networks[j] = new Network(i * NUM_THREADS + j);
    }
  }
  ~Thread();

  static void *thread_helper(void *t) {
    Thread *th = (Thread *) t;
    for (int i = 0; i < NUM_MEMBERS; ++i) {
      th->networks[i]->train_network();
    }
    pthread_exit(0);
  }

  void begin_threaded_training() {
    pthread_create(&thread, NULL, thread_helper, this);
  }

  void collect_threads() {
    pthread_join(thread, NULL);
  }
};
