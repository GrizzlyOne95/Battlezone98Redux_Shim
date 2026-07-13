
void FUN_0082f536(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x28);
  if (param_2 + 1U < 0xaaaaaab) {
    iVar2 = FUN_00838869(param_1,iVar1,*(int *)(param_1 + 0x30) * 0x18,param_2 * 0x18);
  }
  else {
    iVar2 = FUN_008388ab(param_1);
  }
  *(int *)(param_1 + 0x30) = param_2;
  *(int *)(param_1 + 0x28) = iVar2;
  *(int *)(param_1 + 0x14) = ((*(int *)(param_1 + 0x14) - iVar1) / 0x18) * 0x18 + iVar2;
  *(int *)(param_1 + 0x24) = param_2 * 0x18 + -0x18 + iVar2;
  return;
}

