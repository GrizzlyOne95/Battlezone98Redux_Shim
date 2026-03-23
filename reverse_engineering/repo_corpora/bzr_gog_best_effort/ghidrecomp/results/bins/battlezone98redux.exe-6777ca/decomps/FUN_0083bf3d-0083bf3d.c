
void FUN_0083bf3d(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  FUN_0083c667(param_1,param_2);
  iVar2 = *param_2;
  if (5 < iVar2) {
    if (iVar2 == 10) {
      FUN_0083c43c(param_1,param_2);
    }
    else if (iVar2 - 0xbU < 2) {
      FUN_0083c15a(param_1,param_2);
      FUN_0083c3b1(param_1,param_2);
      iVar2 = FUN_0083c5d2(param_1,0x13,0,param_2[2],0);
      param_2[2] = iVar2;
      *param_2 = 0xb;
    }
    goto LAB_0083bfb7;
  }
  if (iVar2 < 4) {
    if (iVar2 != 1) {
      if (iVar2 == 2) goto LAB_0083bf6e;
      if (iVar2 != 3) goto LAB_0083bfb7;
    }
    *param_2 = 2;
  }
  else {
LAB_0083bf6e:
    *param_2 = 3;
  }
LAB_0083bfb7:
  iVar2 = param_2[4];
  iVar1 = param_2[5];
  param_2[5] = iVar2;
  param_2[4] = iVar1;
  FUN_0083d092(param_1,iVar2);
  FUN_0083d092(param_1,param_2[4]);
  return;
}

