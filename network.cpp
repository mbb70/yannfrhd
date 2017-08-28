class Network {
  Wobbler *wobbler;
  int y, seed;
  float eta;
  float x[PIXELS];
  unsigned int mrand() {
    seed = (1103515245*seed + 12345) % 4294967295;
    return seed;
  }

  float rnd() {
    return 2.0*((float) mrand())/4294967295 - 1.0;
  }

  public:
  Layer *l[NLAYERS];
  Network(int i) {
    eta = ETA;
    seed = SEED + i;
    l[0] = new Layer(PIXELS, H_N, seed + 1);
    l[1] = new Layer(H_N, TOT_RES, seed + 2);
    wobbler = new Wobbler(seed + 3);
  }
  ~Network();

  void drop_learning_rate() {
    if (eta > 0.0001) eta *= 0.99;
  }

  float sig_est(float f) {
    if (f < 1.7)
      return (1.5 * f / (1 + f));
    else if (f < 3)
      return (0.935409071 + 0.045881295 * (f - 1.7));
    else
      return 0.995054754f;
  }

  float sigmoid(float f) {
    int sgn = (0 < f) - (f < 0);
    return sgn * sig_est(sgn * f);
  }

  float sigmoid_prime(float f) {
    float sigf = sigmoid(f);
    return 1 - sigf*sigf;
  }

  float rlu(float f) {
    return f * (f > 0);
  }

  float rlu_prime(float f) {
    return f > 0;
  }

  void update_weights() {
    float neta = eta/MINI_BATCH_SIZE;
    float L1_reg = -neta*LAMBDA;
    float L2_reg = 1 + L1_reg;
    for (int i = 0; i < NLAYERS; ++i) {
      float *W = l[i]->W;
      float *dW = l[i]->dW;
      float *mW = l[i]->mW;
      for (int j = 0; j < l[i]->size; ++j) {
        int sgn = (0 < W[j]) - (W[j] < 0);
        mW[j] = BETA*mW[j] + dW[j];
        W[j] = W[j]*L2_reg - L1_reg*sgn - neta*mW[j];
        dW[j] = 0;
      }
      float *B = l[i]->B;
      float *dB = l[i]->dB;
      float *mB = l[i]->mB;
      for (int j = 0; j < l[i]->out_size; ++j) {
        mB[j] = BETA*mB[j] + dB[j];
        B[j] -= neta*mB[j];
        dB[j] = 0;
      }
    }
  }

  void dotmv(enum CBLAS_TRANSPOSE T, int M, int N, float *A, float *X, float *Y) {
    cblas_sgemv(CblasColMajor, T, M, N, ALPHA, A, M, X, INCX, BTA, Y, INCY);
  }

  void dotvv(int M, int N, float *X, float *Y, float *A) {
    cblas_sger(CblasColMajor, M, N, ALPHA, X, INCX, Y, INCY, A, M);
  }

  float *feedforward(float *v) {
    float tot = 0;
    dotmv(CblasNoTrans, l[0]->out_size, l[0]->in_size, l[0]->W, v, l[0]->act);
    for (int i = 0; i < l[0]->out_size; ++i) {
      l[0]->sig[i] = rlu(l[0]->act[i] + l[0]->B[i]);
    }

    dotmv(CblasNoTrans, l[1]->out_size, l[1]->in_size, l[1]->W, l[0]->sig, l[1]->act);

    //softmax
    for (int i = 0; i < l[1]->out_size; ++i) {
      l[1]->sig[i] = expf(l[1]->act[i] + l[1]->B[i]);
      tot += l[1]->sig[i];
    }
    for (int i = 0; i < l[1]->out_size; ++i) {
      l[1]->sig[i] /= tot;
    }
    return l[1]->sig;
  }

  void backprop() {
    l[1]->delta = feedforward(x);
    l[1]->delta[y] -= 1;
    for (int i = 0; i < l[1]->out_size; ++i) {
      l[1]->delta[i] = l[1]->sig[i];
      l[1]->dB[i] += l[1]->delta[i];
    }

    dotvv(l[1]->out_size, l[1]->in_size, l[1]->delta, l[0]->sig, l[1]->dW);
    dotmv(CblasTrans, l[1]->out_size, l[1]->in_size, l[1]->W, l[1]->delta, l[0]->delta);
    for (int i = 0; i < l[0]->out_size; ++i) {
      l[0]->delta[i] *= rlu_prime(l[0]->act[i]);
      l[0]->dB[i] += l[0]->delta[i];
    }
    dotvv(l[0]->out_size, l[0]->in_size, l[0]->delta, x, l[0]->dW);
  }

  void load_random_xy() {
    unsigned int ind = mrand() % TOT_NUM;
    for (int i = 0; i < PIXELS; ++i) {
      x[i] = tdata[ind][i];
    }
    y = tlabels[ind];
  }

  void train_network() {
    int j = 0;
    for (int m = 0; m < TOT_NUM; ++m) {
      load_random_xy();
      wobbler->wobble(x);
      backprop();
      j++;
      if (j == MINI_BATCH_SIZE) {
        j = 0;
        update_weights();
      }
    }
  }
};
