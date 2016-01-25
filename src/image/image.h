#ifndef image_h
#define image_h

unsigned int max_index(unsigned int count, int *values){
  unsigned int index = 0;
  for(unsigned int i = 1; i < count; ++i){
    if(values[i] > values[index]){
      index = i;
    }
  }
  return index;
}

unsigned int min_index(unsigned int count, int *values){
  unsigned int index = 0;
  for(unsigned int i = 1; i < count; ++i){
    if(values[i] < values[index]){
      index = i;
    }
  }
  return index;
}
#endif
