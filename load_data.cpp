void load_testing_data(){
  FILE *data, *labels;
  data = fopen("t10k-images.idx3-ubyte", "r");
  labels = fopen("t10k-labels.idx1-ubyte", "r");
  for (int i = 0; i < 16; ++i) fgetc(data);
  for (int i = 0; i < 8; ++i) fgetc(labels);
  for (int i = 0; i < TOT_TES; ++i){
    rlabels[i] = (int) fgetc(labels);
    for (int r = 0; r < PIXELS; ++r) {
      rdata[i][r] = ((float) fgetc(data))/255.0;
    }
  }
  fclose(data);
  fclose(labels);
}

void load_training_data(){
  FILE *data, *labels;
  data = fopen("train-images.idx3-ubyte", "r");
  labels = fopen("train-labels.idx1-ubyte", "r");
  for (int i = 0; i < 16; ++i) fgetc(data);
  for (int i = 0; i < 8; ++i) fgetc(labels);
  for (int i = 0; i < TOT_NUM; ++i) {
    tlabels[i] = (int) fgetc(labels);
    for (int r = 0; r < PIXELS; ++r) {
      tdata[i][r] = ((float) fgetc(data))/255.0;
    }
  }
  for (int i = 0; i < TOT_VAL; ++i) {
    vlabels[i] = (int) fgetc(labels);
    for (int r = 0; r < PIXELS; ++r) {
      vdata[i][r] = ((float) fgetc(data))/255.0;
    }
  }
  fclose(data);
  fclose(labels);
}

