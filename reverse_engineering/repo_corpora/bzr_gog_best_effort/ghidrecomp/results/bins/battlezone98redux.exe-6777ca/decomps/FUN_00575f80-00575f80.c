
uint __fastcall FUN_00575f80(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x94)) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x94); local_c = local_c + 1) {
      local_8 = local_8 + *(int *)(param_1 + 0x9c + local_c * 0x1c);
    }
    local_8 = local_8 / *(uint *)(param_1 + 0x94);
  }
  return local_8;
}

