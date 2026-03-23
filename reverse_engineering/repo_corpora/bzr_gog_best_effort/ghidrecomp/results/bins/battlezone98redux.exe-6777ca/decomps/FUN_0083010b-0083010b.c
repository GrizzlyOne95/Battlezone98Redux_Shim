
void FUN_0083010b(int param_1,undefined4 *param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *param_2 = *(undefined4 *)(iVar1 + 0x1c);
  *(undefined4 **)(iVar1 + 0x1c) = param_2;
  *(byte *)((int)param_2 + 5) = *(byte *)(iVar1 + 0x14) & 3;
  *(undefined1 *)(param_2 + 1) = param_3;
  return;
}

