
void __thiscall FUN_00460e90(int param_1,uint param_2)

{
  int iVar1;
  undefined4 local_8;
  
  iVar1 = FUN_0083d92c(-(uint)((int)((ulonglong)param_2 * 8 >> 0x20) != 0) |
                       (uint)((ulonglong)param_2 * 8));
  if ((int)param_2 < *(int *)(param_1 + 4)) {
    *(uint *)(param_1 + 4) = param_2;
  }
  for (local_8 = 0; local_8 < *(int *)(param_1 + 4); local_8 = local_8 + 1) {
    *(undefined4 *)(iVar1 + local_8 * 8) = *(undefined4 *)(*(int *)(param_1 + 8) + local_8 * 8);
    *(undefined4 *)(iVar1 + 4 + local_8 * 8) =
         *(undefined4 *)(*(int *)(param_1 + 8) + 4 + local_8 * 8);
  }
  operator_delete__(*(void **)(param_1 + 8));
  *(int *)(param_1 + 8) = iVar1;
  *(uint *)(param_1 + 4) = param_2;
  for (; local_8 < *(int *)(param_1 + 4); local_8 = local_8 + 1) {
    *(undefined4 *)(*(int *)(param_1 + 8) + local_8 * 8) = 0;
    *(undefined4 *)(*(int *)(param_1 + 8) + 4 + local_8 * 8) = 0;
  }
  return;
}

