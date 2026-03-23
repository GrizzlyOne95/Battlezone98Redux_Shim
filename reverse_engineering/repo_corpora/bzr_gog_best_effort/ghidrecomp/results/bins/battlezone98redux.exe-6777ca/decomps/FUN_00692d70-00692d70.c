
void FUN_00692d70(undefined4 *param_1,int param_2,int param_3)

{
  int local_c;
  int local_8;
  
  for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
    param_1[local_8 + 0x4f] = *(undefined4 *)(param_2 + local_8 * 4);
    param_1[local_8 + 0x70] = *(undefined4 *)(param_3 + local_8 * 4);
  }
  local_c = 0;
  for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
    local_c = local_c + param_1[local_8 + 0x4f];
  }
  param_1[0x6f] = (float)local_c;
  if (local_c == 0) {
    param_1[0x90] = 0;
    for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
      param_1[local_8 + 0x2f] = 0;
    }
  }
  else {
    param_1[0x90] = 1;
  }
  FUN_00692990(*param_1);
  return;
}

