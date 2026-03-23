
void FUN_0083c95a(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (-1 < param_2) {
    if (param_2 < 6) {
      iVar1 = FUN_0083c468(param_3);
      if (iVar1 != 0) {
        return;
      }
    }
    else {
      if (param_2 == 6) {
        FUN_0083c800(param_1,param_3);
        return;
      }
      if (param_2 == 0xd) {
        FUN_0083c8d6(param_1,param_3);
        return;
      }
      if (param_2 == 0xe) {
        FUN_0083c87c(param_1,param_3);
        return;
      }
    }
  }
  FUN_0083c706(param_1,param_3);
  return;
}

