
void FUN_0083cdbd(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = (param_3 + -1) / 0x32 + 1;
  if (param_4 == -1) {
    param_4 = 0;
  }
  if (iVar1 < 0x200) {
    FUN_0083c5d2(param_1,0x22,param_2,param_4,iVar1);
  }
  else {
    FUN_0083c5d2(param_1,0x22,param_2,param_4,0);
    FUN_0083c537(param_1,iVar1,*(undefined4 *)(*(int *)(param_1 + 0xc) + 8));
  }
  *(int *)(param_1 + 0x24) = param_2 + 1;
  return;
}

