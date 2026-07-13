
void __fastcall FUN_00607db0(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined1 local_120 [76];
  undefined8 local_d4;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined8 local_bc;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  undefined4 local_a4;
  undefined4 *local_a0;
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
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
  local_a0 = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0xc4);
  local_9c = param_1;
  fVar3 = (float10)FUN_00822d80();
  local_b0 = (float)fVar3;
  if (local_b0 < *(float *)(local_9c + 0x118) + 10.0) {
    fVar3 = (float10)FUN_00453f80();
    local_a8 = (float)fVar3;
    if (local_a8 < 0.1) {
      fVar3 = (float10)FUN_00453f80();
      local_c0 = (float)fVar3;
      if (local_c0 < 0.1) {
        fVar3 = (float10)FUN_00453f80();
        local_c8 = (float)fVar3;
        if (local_c8 < 0.1) {
          fVar3 = (float10)FUN_00453f80();
          local_ac = (float)fVar3;
          if (local_ac < 0.1) {
            FUN_00602920();
            local_a0[3] = 0;
            *local_a0 = 0;
            local_a0[2] = 0;
            local_a0[1] = 0;
            goto LAB_00608449;
          }
        }
      }
    }
  }
  FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00447f60();
  local_50 = *puVar1;
  local_4c = puVar1[1];
  local_48 = puVar1[2];
  local_44 = puVar1[3];
  local_40 = puVar1[4];
  local_3c = puVar1[5];
  uVar2 = (**(code **)(*(int *)(*(int *)(local_9c + 0x10) + 0x18) + 0x2c))(local_50,local_4c);
  FUN_00444f70(uVar2);
  FUN_00462490();
  fVar3 = (float10)FUN_004428b0();
  local_c4 = (float)fVar3;
  fVar3 = (float10)FUN_00447ed0();
  local_a0[1] = (float)fVar3;
  local_a4 = FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_004560b0();
  local_80 = *puVar1;
  local_7c = puVar1[1];
  local_78 = puVar1[2];
  puVar1 = (undefined4 *)FUN_00439d80();
  local_8c = *puVar1;
  local_88 = puVar1[1];
  local_84 = puVar1[2];
  puVar1 = (undefined4 *)FUN_00459570(local_120,*(undefined4 *)(local_9c + 0x110));
  local_98 = *puVar1;
  local_94 = puVar1[1];
  local_90 = puVar1[2];
  local_5c = local_98;
  local_58 = local_94;
  local_54 = local_90;
  (**(code **)(*(int *)(*(int *)(local_9c + 0x18) + 0x18) + 0xc))();
  puVar1 = (undefined4 *)FUN_00440130();
  local_68 = *puVar1;
  local_64 = puVar1[1];
  local_60 = puVar1[2];
  local_20 = local_68;
  local_1c = local_64;
  local_18 = local_60;
  puVar1 = (undefined4 *)FUN_005fcf00();
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  *(undefined4 *)(local_9c + 0x4c) = local_2c;
  *(undefined4 *)(local_9c + 0x50) = local_28;
  *(undefined4 *)(local_9c + 0x54) = local_24;
  FUN_0045c4d0();
  puVar1 = (undefined4 *)FUN_00440300();
  local_38 = *puVar1;
  local_34 = puVar1[1];
  local_30 = puVar1[2];
  local_14 = local_38;
  local_10 = local_34;
  local_c = local_30;
  fVar3 = (float10)FUN_004624d0();
  local_b4 = (float)fVar3;
  if (5.0 <= local_b4) {
    FUN_004624b0();
    local_bc = FUN_0045c460();
    (**(code **)(**(int **)(local_9c + 0x10) + 0x8c))();
  }
  else {
    FUN_00462490();
    local_d4 = FUN_0045c460();
    (**(code **)(**(int **)(local_9c + 0x10) + 0x8c))();
    fVar3 = (float10)FUN_004428b0();
    local_cc = (float)fVar3;
    if (local_cc < 100.0) {
      FUN_00602920();
      fVar3 = (float10)FUN_00822d80();
      *(float *)(local_9c + 0x118) = (float)fVar3;
    }
  }
  fVar3 = (float10)FUN_00447ed0();
  local_a0[3] = (float)fVar3;
  fVar3 = (float10)FUN_00447ed0();
  local_a0[2] = (float)fVar3;
  if ((float)local_a0[3] == 1.0) {
    local_a0[4] = 1;
  }
  else {
    local_a0[4] = 0;
  }
LAB_00608449:
  FUN_0083e885();
  return;
}

