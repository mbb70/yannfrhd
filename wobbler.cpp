class Wobbler {
  int seed;
  int w;

  unsigned int mrand() {
    seed = (1103515245*seed + 12345) % 4294967295;
    return seed;
  }

  float rnd() {
    return 2.0*((float) mrand())/4294967295 - 1.0;
  }

  void rotate(float* x) {
    float theta = rnd()/1000;
    float c = cos(theta);
    float s = sin(theta);
    float rx[PIXELS];
    for (int i = 0; i < PIXELS; ++i) rx[i] = x[i];
    for (int i = 0; i < NUM_COL; ++i) {
      int tx = i - 14;
      for (int j = 0; j < NUM_COL; ++j) {
        int ty = j - 14;
        int nx = (tx)*c - (ty)*s + 14;
        int ny = (tx)*s + (ty)*c + 14;
        if (NUM_COL*nx + ny >= PIXELS) continue;
        x[NUM_COL*nx + ny] = rx[NUM_COL*i + j];
      }
    }
  }

  void translate(float* x) {
    int horz = roundf(2*rnd());
    int vert = roundf(2*rnd());
    float tx[PIXELS];
    for (int i = 0; i < PIXELS; ++i) tx[i] = x[i];
    for (int i = 0; i < NUM_COL; ++i) {
      int ni = i + horz;
      for (int j = 0; j < NUM_COL; ++j) {
        int nj = j + vert;
        if (ni >= NUM_COL || ni <= 0 || nj >= NUM_COL || nj <= 0) {
          x[NUM_COL*i + j] = 0;
        } else {
          x[NUM_COL*i + j] = tx[NUM_COL*ni + nj];
        }
      }
    }
  }

  public:
  Wobbler(int nseed) {
    seed = nseed;
    w = 3;
  }
  ~Wobbler();

  void wobble(float* x) {
    --w;
    if (w == 0) {
      rotate(x);
      translate(x);
      w = 3;
    }
  }
};
