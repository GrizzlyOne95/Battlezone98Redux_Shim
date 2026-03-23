
void FUN_0069ca90(void *param_1)

{
  void *_Memory;
  undefined4 local_c;
  
  FUN_0069c470(*(undefined4 *)((int)param_1 + 0xc));
  FUN_0069c3c0(*(undefined4 *)((int)param_1 + 4));
  local_c = *(int *)((int)param_1 + 0x18);
  while (local_c = local_c + -1, -1 < local_c) {
    _Memory = (void *)FUN_0069d590((int)param_1 + 0x10,local_c);
    free(_Memory);
  }
  FUN_0069d280((int)param_1 + 0x10);
  free(param_1);
  return;
}

