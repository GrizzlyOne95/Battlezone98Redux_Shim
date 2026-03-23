
void __fastcall FUN_005856a0(int param_1)

{
  undefined4 *puVar1;
  undefined1 local_70 [12];
  undefined1 local_64 [12];
  undefined1 local_58 [12];
  undefined1 local_4c [12];
  int local_40;
  undefined4 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = param_1;
  if (0.0001 < *(float *)(param_1 + 0x20) || *(float *)(param_1 + 0x20) == 0.0001) {
    local_3c = (undefined4 *)(*(int *)(param_1 + 0x14) + 0x20);
    puVar1 = (undefined4 *)FUN_004621a0(local_64,param_1 + 0x30);
    local_38 = *puVar1;
    local_34 = puVar1[1];
    local_30 = puVar1[2];
    local_3c[6] = local_38;
    local_3c[7] = local_34;
    local_3c[8] = local_30;
    puVar1 = (undefined4 *)FUN_004440d0(local_4c,local_3c + 3,local_3c + 6);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    *local_3c = local_2c;
    local_3c[1] = local_28;
    local_3c[2] = local_24;
    puVar1 = (undefined4 *)FUN_004621a0(local_58,local_3c);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *local_3c = local_14;
    local_3c[1] = local_10;
    local_3c[2] = local_c;
    puVar1 = (undefined4 *)FUN_004440d0(local_70,local_3c + 6,local_3c);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    local_3c[3] = local_20;
    local_3c[4] = local_1c;
    local_3c[5] = local_18;
  }
  FUN_0083e885();
  return;
}

