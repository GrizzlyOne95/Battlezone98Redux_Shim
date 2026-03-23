
void __fastcall FUN_005c0ba0(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_54 [12];
  undefined1 local_48 [12];
  float local_3c;
  int local_38;
  float local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = *(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4;
  local_28 = param_1;
  local_2c = FUN_0045c490();
  local_38 = *(int *)(*(int *)(local_28 + 0x10) + 0x230);
  if (0.01 < *(float *)(local_2c + 8) || *(float *)(local_2c + 8) == 0.01) {
    local_30 = FUN_0045c4d0();
    puVar1 = (undefined4 *)FUN_004560b0(local_48,local_30);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    fVar2 = (float10)FUN_004428b0(&local_20,local_2c + 0x18);
    local_3c = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0(-local_3c * 0.2,0xbf800000,0x3f800000);
    *(float *)(local_24 + 0xc) = (float)fVar2;
    puVar1 = (undefined4 *)FUN_00439d80(local_54,local_30);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    fVar2 = (float10)FUN_004428b0(&local_14,local_2c + 0x18);
    local_34 = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0(-local_34 * 0.2,0xbf800000,0x3f800000);
    *(float *)(local_24 + 8) = (float)fVar2;
  }
  else {
    *(undefined4 *)(local_24 + 0xc) = 0;
    *(undefined4 *)(local_24 + 8) = 0;
  }
  fVar2 = (float10)FUN_00447ed0(*(float *)(local_28 + 0xd8) * -5.0 - *(float *)(local_2c + 0x28),
                                0xbf800000,0x3f800000);
  *(float *)(local_38 + 0xc4) = (float)fVar2;
  *(undefined4 *)(local_24 + 0x10) = 0;
  FUN_0083e885();
  return;
}

