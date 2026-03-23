
void FUN_0083975c(int param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x30);
  param_2 = param_2 - param_3;
  if ((*param_4 == 0xd) || (*param_4 == 0xe)) {
    iVar3 = param_2 + 1;
    if (param_2 + 1 < 0) {
      iVar3 = 0;
    }
    FUN_0083ce76(iVar1,param_4,iVar3);
    if (1 < iVar3) {
      FUN_0083cd31(iVar1,iVar3 + -1);
    }
  }
  else {
    if (*param_4 != 0) {
      FUN_0083c800(iVar1,param_4);
    }
    if (0 < param_2) {
      uVar2 = *(undefined4 *)(iVar1 + 0x24);
      FUN_0083cd31(iVar1,param_2);
      FUN_0083c9f3(iVar1,uVar2,param_2);
    }
  }
  return;
}

