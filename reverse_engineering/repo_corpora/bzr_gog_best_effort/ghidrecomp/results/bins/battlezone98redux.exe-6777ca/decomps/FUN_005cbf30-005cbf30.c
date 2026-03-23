
int FUN_005cbf30(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 4) < 3)) {
    iVar1 = 0;
  }
  else {
    local_c = 0;
    for (local_8 = 1; local_8 < *(int *)(param_1 + 4); local_8 = local_8 + 1) {
      iVar1 = FUN_005cbe90(*(int *)(param_1 + 8) + -8 + local_8 * 8,
                           *(int *)(param_1 + 8) + local_8 * 8,param_2);
      local_c = iVar1 + local_c;
    }
    iVar1 = FUN_005cbe90(*(int *)(param_1 + 8) + -8 + *(int *)(param_1 + 4) * 8,
                         *(undefined4 *)(param_1 + 8),param_2);
    iVar1 = iVar1 + local_c;
  }
  return iVar1;
}

