
undefined4 FUN_0043e810(int param_1,int param_2,undefined4 param_3,int param_4)

{
  if (param_4 == 0) {
    *(int *)(param_1 + 0x2f0) = param_2;
  }
  else if (param_4 == 1) {
    *(int *)(param_1 + 0x2f0) = param_2 + *(int *)(param_1 + 0x2f0);
  }
  else {
    if (param_4 != 2) {
      FUN_007d6a70("Ogg_seek_func has invalid whence %d",param_4);
      return 0xffffffff;
    }
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x18);
  }
  return 0;
}

