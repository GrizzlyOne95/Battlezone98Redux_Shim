
void __fastcall FUN_005cf3f0(int param_1)

{
  ushort *puVar1;
  short *local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  local_1c = *(short **)(param_1 + 0xf4);
  for (local_14 = *(int *)(param_1 + 0xe8); local_14 <= *(int *)(param_1 + 0xf0);
      local_14 = local_14 + 1) {
    for (local_18 = *(int *)(param_1 + 0xe4); local_18 <= *(int *)(param_1 + 0xec);
        local_18 = local_18 + 1) {
      puVar1 = (ushort *)FUN_00492d60(local_18,local_14);
      local_10 = (*puVar1 & 0xfff) - (int)*local_1c;
      local_1c = local_1c + 1;
      if (local_10 < 0) {
        local_10 = 0;
      }
      else if (0xfff < local_10) {
        local_10 = 0xfff;
      }
      *puVar1 = (*puVar1 & 0xf000) + (short)local_10;
    }
  }
  FUN_00777730(*(undefined4 *)(param_1 + 0xe4),*(undefined4 *)(param_1 + 0xe8),
               *(undefined4 *)(param_1 + 0xec),*(undefined4 *)(param_1 + 0xf0));
  return;
}

