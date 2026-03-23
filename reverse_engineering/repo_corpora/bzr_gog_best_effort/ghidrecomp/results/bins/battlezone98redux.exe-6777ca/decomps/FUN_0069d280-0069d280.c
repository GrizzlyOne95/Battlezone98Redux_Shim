
void FUN_0069d280(undefined4 *param_1)

{
  void *_Memory;
  int local_8;
  
  for (local_8 = 0; local_8 < (int)param_1[2]; local_8 = local_8 + 1) {
    if (param_1[3] != 0) {
      _Memory = (void *)param_1[3];
      param_1[3] = *(undefined4 *)(param_1[3] + 4);
      free(_Memory);
    }
  }
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = 0xfffffc19;
  return;
}

