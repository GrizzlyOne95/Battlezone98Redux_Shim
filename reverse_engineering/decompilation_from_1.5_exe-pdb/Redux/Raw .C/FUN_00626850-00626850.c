
undefined4 FUN_00626850(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x44) - *(int *)(param_2 + 0x48);
  return CONCAT31((int3)((uint)iVar1 >> 8),
                  iVar1 < *(int *)(param_1 + 0x44) - *(int *)(param_1 + 0x48));
}

