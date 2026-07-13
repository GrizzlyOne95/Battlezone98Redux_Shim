
void __fastcall FUN_004f2210(int param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  char cVar9;
  undefined4 *puVar10;
  uint uVar11;
  float *pfVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined1 local_1bc [64];
  undefined1 local_17c [44];
  undefined4 *local_150;
  int local_14c;
  int local_148;
  float local_144;
  float local_140;
  int local_13c;
  undefined4 local_138 [16];
  undefined4 local_f8 [16];
  undefined4 local_b8 [16];
  undefined4 local_78 [6];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_148 = param_1;
  puVar10 = (undefined4 *)FUN_0081fe60(local_1bc,*(int *)(param_1 + 0x10) + 0x20,param_1 + 0x28);
  puVar14 = local_138;
  for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
    *puVar14 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar14 = puVar14 + 1;
  }
  puVar10 = local_138;
  puVar14 = local_78;
  for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
    *puVar14 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar14 = puVar14 + 1;
  }
  local_38 = local_50;
  uVar2 = local_38;
  local_30 = local_48;
  uVar5 = local_30;
  local_28 = local_40;
  uVar7 = local_28;
  local_20 = local_60;
  local_1c = local_5c;
  local_18 = local_58;
  local_140 = *(float *)(*(int *)(local_148 + 8) + 0x80);
  local_38._0_4_ = (undefined4)local_50;
  uVar1 = (undefined4)local_38;
  local_38._4_4_ = (undefined4)((ulonglong)local_50 >> 0x20);
  uVar3 = local_38._4_4_;
  local_30._0_4_ = (undefined4)local_48;
  uVar4 = (undefined4)local_30;
  local_30._4_4_ = (undefined4)((ulonglong)local_48 >> 0x20);
  uVar6 = local_30._4_4_;
  local_28._4_4_ = (undefined4)((ulonglong)local_40 >> 0x20);
  uVar8 = local_28._4_4_;
  local_38 = uVar2;
  local_30 = uVar5;
  local_28 = uVar7;
  FUN_00784620(uVar1,uVar3,uVar4,uVar6,(int)local_40,uVar8,local_60,local_5c,local_58,&local_140,0);
  local_14c = 0;
  puVar10 = (undefined4 *)FUN_008203f0();
  puVar14 = local_f8;
  for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
    *puVar14 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar14 = puVar14 + 1;
  }
  puVar10 = local_f8;
  puVar14 = local_b8;
  for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
    *puVar14 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar14 = puVar14 + 1;
  }
  FUN_005b28e0(local_38,local_28,(double)local_140,local_17c);
  while (cVar9 = FUN_00462710(&local_150), cVar9 != '\0') {
    local_13c = FUN_004da060(*local_150);
    if (((local_13c != 0) && (local_13c != *(int *)(local_148 + 0xd8))) &&
       (uVar11 = FUN_0045c4b0(), (uVar11 & 0x400) == 0)) {
      pfVar12 = (float *)(**(code **)(*(int *)(local_13c + 0x18) + 0xc))();
      local_14 = *pfVar12;
      local_10 = pfVar12[1];
      local_c = pfVar12[2];
      FUN_00820180();
      if ((0.0 <= local_c) && (local_c <= local_140)) {
        iVar13 = FUN_00462400();
        local_144 = *(float *)(iVar13 + 0xc) * 0.75;
        local_144 = local_144 * local_144;
        if (local_14 * local_14 + local_10 * local_10 <= local_144) {
          local_140 = local_c;
          local_14c = local_13c;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

