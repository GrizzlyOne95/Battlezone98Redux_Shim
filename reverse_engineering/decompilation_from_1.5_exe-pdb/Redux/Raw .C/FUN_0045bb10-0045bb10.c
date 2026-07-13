
void __thiscall FUN_0045bb10(uint *param_1,undefined4 *param_2)

{
  uint local_c;
  
  if (param_1[1] <= *param_1) {
    local_c = (*param_1 >> 1) + *param_1;
    if (local_c < 0x40) {
      local_c = 0x40;
    }
    FUN_0045ba50(local_c);
  }
  *(undefined4 *)(param_1[2] + *param_1 * 4) = *param_2;
  *param_1 = *param_1 + 1;
  return;
}

