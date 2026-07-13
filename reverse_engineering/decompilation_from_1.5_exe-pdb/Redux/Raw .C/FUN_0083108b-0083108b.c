
void FUN_0083108b(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(undefined **)(param_2 + 0x10) != &DAT_0086eef0) {
    iVar1 = 1 << (*(byte *)(param_2 + 7) & 0x1f);
  }
  FUN_00831491(param_1,param_2,param_3,iVar1);
  return;
}

