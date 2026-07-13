
void FUN_00695db0(int param_1)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = 0;
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      if (*(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_8 * 4) + local_c * 4) + 100)
          <= 0.0) {
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x84) + local_8 * 4) + local_c * 4) = 0;
      }
      else {
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x84) + local_8 * 4) + local_c * 4) = 1;
      }
    }
  }
  FUN_00698cd0(*(undefined4 *)(param_1 + 0x84),*(undefined4 *)(param_1 + 0x88),1,0,0,8,
               *(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x7c));
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      if (local_10 < *(int *)(*(int *)(*(int *)(param_1 + 0x88) + local_8 * 4) + local_c * 4)) {
        local_10 = *(int *)(*(int *)(*(int *)(param_1 + 0x88) + local_8 * 4) + local_c * 4);
      }
    }
  }
  *(int *)(param_1 + 0x8c) = local_10;
  return;
}

