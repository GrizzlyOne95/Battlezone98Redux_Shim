
uint __thiscall FUN_0060a320(int param_1,undefined4 param_2,float *param_3)

{
  uint3 uVar3;
  int iVar1;
  uint uVar2;
  undefined4 local_20;
  float local_1c;
  uint local_18;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  uVar3 = (uint3)((uint)param_1 >> 8);
  if (*(int *)(param_1 + 0x78) == 0) {
    uVar2 = (uint)uVar3 << 8;
  }
  else if (param_3[2] < *(float *)(param_1 + 0x74) || param_3[2] == *(float *)(param_1 + 0x74)) {
    local_8 = param_1;
    iVar1 = FUN_00462400();
    local_14 = *(float *)(iVar1 + 0xc);
    local_10 = local_14 * 0.8 * local_14 * 0.8;
    local_c = local_14 * 0.6 * local_14 * 0.6;
    local_1c = *param_3 * *param_3 + param_3[1] * param_3[1];
    local_18 = (uint)(local_1c < local_c);
    *(bool *)param_2 = local_1c < local_c;
    if (local_1c <= local_10) {
      local_20 = 0x3f800000;
      uVar2 = FUN_00784620(*(undefined4 *)(local_8 + 0xb0),*(undefined4 *)(local_8 + 0xb4),
                           *(undefined4 *)(local_8 + 0xb8),*(undefined4 *)(local_8 + 0xbc),
                           *(undefined4 *)(local_8 + 0xc0),*(undefined4 *)(local_8 + 0xc4),
                           *(undefined4 *)(local_8 + 0x88),*(undefined4 *)(local_8 + 0x8c),
                           *(undefined4 *)(local_8 + 0x90),&local_20,0);
      if (uVar2 == 0) {
        uVar2 = 1;
      }
      else {
        uVar2 = uVar2 & 0xffffff00;
      }
    }
    else {
      uVar2 = (uint)param_3 & 0xffffff00;
    }
  }
  else {
    uVar2 = (uint)uVar3 << 8;
  }
  return uVar2;
}

