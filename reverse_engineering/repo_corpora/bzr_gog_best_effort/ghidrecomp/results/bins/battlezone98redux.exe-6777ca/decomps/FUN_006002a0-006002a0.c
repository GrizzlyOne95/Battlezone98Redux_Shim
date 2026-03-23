
void __fastcall FUN_006002a0(int *param_1)

{
  int iVar1;
  int iVar2;
  float local_14;
  float local_10;
  float local_c;
  int *local_8;
  
  if (param_1[2] == 0xd) {
    return;
  }
  local_8 = param_1;
  iVar1 = FUN_00572a70();
  if (iVar1 == 0) {
    iVar1 = (**(code **)(*(int *)(local_8[4] + 0x18) + 4))();
    iVar2 = FUN_00461430();
    if (iVar1 != iVar2) {
      local_14 = (float)DAT_025cfa1c;
      goto LAB_006002ff;
    }
  }
  local_14 = 4.0;
LAB_006002ff:
  local_8[0x26] = (int)local_14;
  iVar1 = FUN_005fed30(local_8[4]);
  if (iVar1 != local_8[0x30]) {
    local_8[0x30] = iVar1;
    FUN_00466be0(local_8[4],&local_c,&local_10,local_8 + 0x29,local_8 + 0x2d);
    iVar1 = FUN_00462400();
    local_c = local_c + *(float *)(iVar1 + 0xc);
    iVar1 = FUN_00462630(local_8[5]);
    if (iVar1 != 0) {
      iVar1 = FUN_00462400();
      local_c = local_c + *(float *)(iVar1 + 0xc);
    }
    local_8[0x2a] = (int)(local_10 / (float)local_8[0x29]);
    local_8[0x2b] = (int)((float)local_8[0x29] / local_10);
    local_8[0x27] = (int)(local_c * local_c);
    local_8[0x28] = (int)(local_10 * local_10);
    local_8[0x43] = 0x3f800000;
    iVar1 = FUN_00605270(local_8 + 0x2e);
    local_8[0x2f] = iVar1;
  }
  if (local_8[3] != -1) {
    (**(code **)(*local_8 + 0x2c))();
    local_8[2] = local_8[3];
    local_8[3] = -1;
    (**(code **)(*local_8 + 0x28))();
    if (local_8[3] != -1) {
      return;
    }
    if (local_8[2] == 0xd) {
      return;
    }
  }
  (**(code **)(*local_8 + 0x30))();
  return;
}

