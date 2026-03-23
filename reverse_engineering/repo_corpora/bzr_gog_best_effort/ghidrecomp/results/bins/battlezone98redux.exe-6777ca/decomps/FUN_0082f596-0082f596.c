
void FUN_0082f596(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 0x20);
  if (param_2 + 7U < 0x10000000) {
    iVar2 = FUN_00838869(param_1,uVar1,*(int *)(param_1 + 0x2c) << 4,(param_2 + 6) * 0x10);
  }
  else {
    iVar2 = FUN_008388ab(param_1);
  }
  *(int *)(param_1 + 0x20) = iVar2;
  *(int *)(param_1 + 0x2c) = param_2 + 6;
  *(int *)(param_1 + 0x1c) = param_2 * 0x10 + iVar2;
  FUN_0082eef5(param_1,uVar1);
  return;
}

