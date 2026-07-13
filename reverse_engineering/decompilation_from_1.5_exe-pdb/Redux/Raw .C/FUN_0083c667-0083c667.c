
void FUN_0083c667(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (iVar1 == 6) {
    *param_2 = 0xc;
  }
  else {
    if (iVar1 == 7) {
      iVar1 = FUN_0083c5d2(param_1,4,0,param_2[2],0);
    }
    else if (iVar1 == 8) {
      iVar1 = FUN_0083c5ff(param_1,5,0,param_2[2]);
    }
    else {
      if (iVar1 != 9) {
        if (1 < iVar1 - 0xdU) {
          return;
        }
        FUN_0083ce20(param_1,param_2);
        return;
      }
      FUN_0083c3cb(param_1,param_2[3]);
      FUN_0083c3cb(param_1,param_2[2]);
      iVar1 = FUN_0083c5d2(param_1,6,0,param_2[2],param_2[3]);
    }
    param_2[2] = iVar1;
    *param_2 = 0xb;
  }
  return;
}

