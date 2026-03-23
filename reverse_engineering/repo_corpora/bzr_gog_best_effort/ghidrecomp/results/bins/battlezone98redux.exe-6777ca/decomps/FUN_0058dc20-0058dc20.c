
int FUN_0058dc20(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  float10 fVar1;
  undefined4 local_8;
  
  if (*(char *)(param_4 + 0x21) == '\0') {
    fVar1 = (float10)FUN_0058bec0(*(undefined4 *)(param_4 + 0x10));
    if ((float)fVar1 == 99999.0) {
      local_8 = 0;
    }
    else {
      local_8 = FUN_0058d8a0(param_1,param_2,param_3,param_4);
    }
  }
  else if (*(char *)(param_4 + 0x1f) == *(char *)(param_3 + 0x1f)) {
    local_8 = FUN_0058d950(param_1,param_2,param_3,param_4);
  }
  else {
    local_8 = FUN_0058dab0(param_1,param_2,param_3,param_4);
  }
  if (local_8 != 0) {
    FUN_0058d3c0(param_3,local_8);
  }
  return local_8;
}

