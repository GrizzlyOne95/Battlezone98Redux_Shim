
void __fastcall FUN_004e7ac0(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_68 [12];
  undefined1 local_5c [12];
  float local_50;
  float local_4c;
  undefined4 local_48;
  int local_44;
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
  local_3c = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_40 = param_1;
  local_44 = FUN_0045c490();
  if (0.01 < *(float *)(local_44 + 8) || *(float *)(local_44 + 8) == 0.01) {
    local_48 = FUN_0045c4d0();
    puVar1 = (undefined4 *)FUN_004560b0(local_5c,local_48);
    local_38 = *puVar1;
    local_34 = puVar1[1];
    local_30 = puVar1[2];
    local_20 = local_38;
    local_1c = local_34;
    local_18 = local_30;
    fVar2 = (float10)FUN_004428b0(&local_38,local_44 + 0x18);
    local_50 = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0(-local_50 * 0.2,0xbf800000,0x3f800000);
    local_3c[3] = (float)fVar2;
    puVar1 = (undefined4 *)FUN_00439d80(local_68,local_48);
    local_2c = *puVar1;
    local_28 = puVar1[1];
    local_24 = puVar1[2];
    local_14 = local_2c;
    local_10 = local_28;
    local_c = local_24;
    fVar2 = (float10)FUN_004428b0(&local_2c,local_44 + 0x18);
    local_4c = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0(-local_4c * 0.2,0xbf800000,0x3f800000);
    local_3c[2] = (float)fVar2;
  }
  else {
    local_3c[3] = 0;
    local_3c[2] = 0;
  }
  local_3c[1] = 0;
  *local_3c = 0x3f000000;
  local_3c[4] = 0;
  FUN_0083e885();
  return;
}

