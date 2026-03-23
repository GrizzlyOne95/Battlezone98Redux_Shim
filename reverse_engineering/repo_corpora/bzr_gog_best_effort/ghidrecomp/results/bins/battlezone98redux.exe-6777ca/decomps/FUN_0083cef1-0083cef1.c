
void FUN_0083cef1(undefined4 param_1,int *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *param_2;
  if (iVar4 == 6) {
    FUN_0083c3b1(param_1,param_3);
    FUN_0083c26e(param_1,param_3,param_2[2]);
    return;
  }
  if (iVar4 == 7) {
    iVar2 = FUN_0083c7b7(param_1,param_3);
    uVar1 = 0;
    iVar4 = param_2[2];
    uVar3 = 8;
  }
  else {
    if (iVar4 == 8) {
      uVar1 = FUN_0083c7b7(param_1,param_3);
      FUN_0083c5ff(param_1,7,uVar1,param_2[2]);
      goto LAB_0083cf54;
    }
    if (iVar4 != 9) goto LAB_0083cf54;
    uVar1 = FUN_0083c706(param_1,param_3);
    iVar4 = param_2[3];
    iVar2 = param_2[2];
    uVar3 = 9;
  }
  FUN_0083c5d2(param_1,uVar3,iVar2,iVar4,uVar1);
LAB_0083cf54:
  FUN_0083c3b1(param_1,param_3);
  return;
}

