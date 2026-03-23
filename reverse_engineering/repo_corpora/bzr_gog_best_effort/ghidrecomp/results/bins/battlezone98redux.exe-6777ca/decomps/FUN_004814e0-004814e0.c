
void FUN_004814e0(undefined4 *param_1,int param_2)

{
  undefined4 *local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    local_8 = &DAT_0091739c;
  }
  else {
    local_8 = param_1;
  }
  if (local_8[4] != 0) {
    *(int *)(local_8[4] + 0x20) = param_2;
  }
  *(undefined4 *)(param_2 + 0x24) = local_8[4];
  local_8[4] = param_2;
  *(undefined4 *)(param_2 + 0x20) = 0;
  if (local_8[3] == 0) {
    local_8[3] = param_2;
  }
  return;
}

