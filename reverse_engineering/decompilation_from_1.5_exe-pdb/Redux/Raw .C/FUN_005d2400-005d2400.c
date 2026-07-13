
void FUN_005d2400(void)

{
  char cVar1;
  float10 fVar2;
  int local_1c;
  int *local_18;
  int local_14;
  float local_10;
  float local_c;
  int local_8;
  
  DAT_009182e0 = FUN_005d2bd0(DAT_009182d0,DAT_009182d4);
  DAT_009182ec = FUN_005d2bd0(DAT_009182c8,DAT_009182cc);
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>();
  local_c = 0.0;
  fVar2 = (float10)FUN_005d2850(DAT_009182e0);
  local_10 = (float)fVar2;
  *(float *)(DAT_009182e0 + 0x1c) = local_c;
  FUN_005d3080(DAT_009182e0,local_c,local_10);
  *(undefined1 *)(DAT_009182e0 + 0x19) = 1;
  DAT_009182e8 = 0;
  while ((cVar1 = FUN_005d30c0(), cVar1 == '\0' &&
         (DAT_009182e8 = FUN_005d31c0(), DAT_009182e8 != DAT_009182ec))) {
    FUN_005d2c80(&local_1c,&local_18);
    for (local_14 = 0; local_14 < local_1c; local_14 = local_14 + 1) {
      local_8 = *local_18;
      local_18 = local_18 + 1;
      fVar2 = (float10)FUN_005d2870(DAT_009182e8,local_8);
      local_c = (float)fVar2 + *(float *)(DAT_009182e8 + 0x1c);
      fVar2 = (float10)FUN_005d2850(local_8);
      local_10 = (float)fVar2;
      if (*(char *)(local_8 + 0x19) == '\0') {
        *(undefined1 *)(local_8 + 0x19) = 1;
        *(int *)(local_8 + 0x20) = DAT_009182e8;
        *(float *)(local_8 + 0x1c) = local_c;
        FUN_005d3080(local_8,local_c,local_10);
      }
      else if (local_c < *(float *)(local_8 + 0x1c)) {
        *(int *)(local_8 + 0x20) = DAT_009182e8;
        *(float *)(local_8 + 0x1c) = local_c;
        cVar1 = FUN_005d30f0(local_8);
        if (cVar1 == '\0') {
          FUN_005d3080(local_8,local_c,local_10);
        }
        else {
          FUN_005d3100(local_8,local_c);
        }
      }
    }
    FUN_005d2d10();
  }
  FUN_005d3070();
  return;
}

