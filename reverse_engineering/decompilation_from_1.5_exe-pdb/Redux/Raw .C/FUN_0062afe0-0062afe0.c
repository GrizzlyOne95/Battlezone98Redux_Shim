
void FUN_0062afe0(int param_1,int param_2,int param_3,float param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_60;
  int local_5c;
  undefined4 local_58 [4];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  double local_30;
  double local_28;
  double local_20;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_2 + 0x70) < 1) {
    local_58[0] = *(undefined4 *)(param_2 + 0x3c);
    local_58[1] = *(undefined4 *)(param_2 + 0x40);
    local_58[2] = *(undefined4 *)(param_2 + 0x44);
    local_58[3] = *(undefined4 *)(param_2 + 0x48);
    local_48 = *(undefined4 *)(param_2 + 0x4c);
    local_44 = *(undefined4 *)(param_2 + 0x50);
    local_40 = *(undefined4 *)(param_2 + 0x54);
    local_3c = *(undefined4 *)(param_2 + 0x58);
    local_38 = *(undefined4 *)(param_2 + 0x5c);
  }
  else {
    iVar1 = *(int *)(param_2 + 0x6c) * 0x14 + *(int *)(*(int *)(param_3 + 4) + 0x2c);
    local_5c = -1;
    for (local_60 = 1; local_60 < *(int *)(param_2 + 0x70); local_60 = local_60 + 1) {
      if (((float)*(int *)(iVar1 + (local_60 + -1) * 0x14) <= param_4) &&
         (param_4 <= (float)*(int *)(iVar1 + local_60 * 0x14))) {
        local_5c = local_60 + -1;
        break;
      }
    }
    if (local_5c < 0) {
      local_18 = *(float *)(iVar1 + 4);
      local_14 = *(float *)(iVar1 + 8);
      local_10 = *(float *)(iVar1 + 0xc);
      local_c = *(undefined4 *)(iVar1 + 0x10);
    }
    else {
      FUN_0062a650(&local_18,
                   (param_4 - (float)*(int *)(iVar1 + local_5c * 0x14)) /
                   (float)(*(int *)(iVar1 + (local_5c + 1) * 0x14) -
                          *(int *)(iVar1 + local_5c * 0x14)),iVar1 + 4 + local_5c * 0x14,
                   iVar1 + 4 + (local_5c + 1) * 0x14);
    }
    FUN_0062ad80(local_58,&local_18);
  }
  if (*(int *)(param_2 + 0x80) == 0) {
    local_30 = (double)*(float *)(param_2 + 0x60);
    local_28 = (double)*(float *)(param_2 + 100);
    local_20 = (double)*(float *)(param_2 + 0x68);
  }
  else {
    iVar1 = *(int *)(param_2 + 0x7c) * 0x10 + *(int *)(*(int *)(param_3 + 4) + 0x34);
    local_5c = -1;
    for (local_60 = 1; local_60 < *(int *)(param_2 + 0x80); local_60 = local_60 + 1) {
      if (((float)*(int *)(iVar1 + (local_60 + -1) * 0x10) <= param_4) &&
         (param_4 <= (float)*(int *)(iVar1 + local_60 * 0x10))) {
        local_5c = local_60 + -1;
        break;
      }
    }
    if (local_5c < 0) {
      local_18 = *(float *)(iVar1 + 4);
      local_14 = *(float *)(iVar1 + 8);
      local_10 = *(float *)(iVar1 + 0xc);
    }
    else {
      FUN_0062aca0(&local_18,
                   (param_4 - (float)*(int *)(iVar1 + local_5c * 0x10)) /
                   (float)(*(int *)(iVar1 + (local_5c + 1) * 0x10) -
                          *(int *)(iVar1 + local_5c * 0x10)),iVar1 + 4 + local_5c * 0x10,
                   iVar1 + 4 + (local_5c + 1) * 0x10);
    }
    local_30 = (double)local_18;
    local_28 = (double)local_14;
    local_20 = (double)local_10;
  }
  puVar2 = local_58;
  puVar3 = (undefined4 *)(param_1 + 0x20);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00681a00(param_1,param_1 + 0x20);
  FUN_0083e885();
  return;
}

