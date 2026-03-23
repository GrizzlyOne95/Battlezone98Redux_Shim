
void FUN_00481550(undefined4 *param_1,int param_2)

{
  undefined4 *local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    local_8 = &DAT_0091739c;
  }
  else {
    local_8 = param_1;
  }
  if (*(int *)(param_2 + 0x20) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0x20) + 0x24) = *(undefined4 *)(param_2 + 0x24);
  }
  if (*(int *)(param_2 + 0x24) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0x24) + 0x20) = *(undefined4 *)(param_2 + 0x20);
  }
  if (param_2 == local_8[3]) {
    local_8[3] = *(undefined4 *)(param_2 + 0x20);
  }
  if (param_2 == local_8[4]) {
    local_8[4] = *(undefined4 *)(param_2 + 0x24);
  }
  *(undefined4 *)(param_2 + 0x20) = 0;
  *(undefined4 *)(param_2 + 0x24) = 0;
  return;
}

