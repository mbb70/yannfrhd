class Layer {
  unsigned int mrand() {
    seed = (1103515245*seed + 12345) % 4294967295;
    return seed;
  }

  float rnd() {
    return 2.0*((float) mrand())/4294967295 - 1.0;
  }

  public:
  int seed;
  int size;
  int in_size;
  int out_size;
  float *W, *dW, *mW, *B, *dB, *mB, *act, *sig, *delta;
  Layer(int in, int out, int s) {
    in_size = in;
    out_size = out;
    size = in * out;
    seed = s;

    W = new float[size];
    dW = new float[size];
    mW = new float[size];
    for (int i = 0; i < size; ++i) {
      W[i] = rnd()/1000;
      dW[i] = 0;
      mW[i] = W[i];
    }

    B = new float[out_size];
    dB = new float[out_size];
    mB = new float[out_size];
    for (int i = 0; i < out_size; ++i) {
      B[i] = rnd()/1000;
      dB[i] = 0;
      mB[i] = B[i];
    }

    delta = new float[out_size];
    sig = new float[out_size];
    act = new float[out_size];
  }
  ~Layer();
};
