
void FUN_00830000(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) & 0xfb;
  *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(iVar1 + 0x28);
  *(int *)(iVar1 + 0x28) = param_2;
  return;
}

