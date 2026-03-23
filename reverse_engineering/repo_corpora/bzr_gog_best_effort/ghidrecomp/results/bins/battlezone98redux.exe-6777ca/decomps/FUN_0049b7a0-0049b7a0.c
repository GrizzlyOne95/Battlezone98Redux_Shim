
undefined4 __fastcall FUN_0049b7a0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x1178);
  iVar2 = *(int *)(param_1 + 0x1178) + 1;
  *(int *)(param_1 + 0x1178) = iVar2;
  return CONCAT31((int3)((uint)iVar2 >> 8),iVar1 == 0);
}

