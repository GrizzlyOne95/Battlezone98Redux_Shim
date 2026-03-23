
void FUN_0068d570(uint *param_1,uint *param_2,int param_3,int param_4)

{
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  
  local_c = 0xff;
  local_10 = 0;
  for (; 0 < param_4; param_4 = param_4 + -1) {
    local_14 = (uint)(*(float *)(param_3 + 0xc) <= 0.0 && *(float *)(param_3 + 0xc) != 0.0);
    local_18 = (uint)(1.0 < *(float *)(param_3 + 0xc));
    local_1c = (uint)(*(float *)(param_3 + 0x10) <= 0.0 && *(float *)(param_3 + 0x10) != 0.0);
    local_20 = (uint)(1.0 < *(float *)(param_3 + 0x10));
    local_20 = ((local_14 * 2 + local_18) * 2 + local_1c) * 2 + local_20;
    local_c = local_c & local_20;
    local_10 = local_10 | local_20;
    param_3 = param_3 + 0x18;
  }
  *param_1 = local_c;
  *param_2 = local_10;
  return;
}

