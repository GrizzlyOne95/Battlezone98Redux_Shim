
void __fastcall FUN_005e1ea0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 local_1ac [64];
  undefined1 local_16c [44];
  float local_140;
  undefined4 *local_13c;
  float local_138;
  int local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  int local_120;
  int local_11c;
  float local_118;
  undefined4 local_114 [16];
  undefined4 local_d4 [16];
  undefined4 local_94 [16];
  undefined4 local_54 [10];
  undefined8 local_2c;
  undefined8 local_1c;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_120 = param_1;
  puVar2 = (undefined4 *)FUN_0081fe60(local_1ac,*(int *)(param_1 + 0x10) + 0x20,param_1 + 0x28);
  puVar6 = local_d4;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar2 = local_d4;
  puVar6 = local_54;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar2 = (undefined4 *)FUN_008203f0();
  puVar6 = local_94;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar2 = local_94;
  puVar6 = local_114;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar6 = puVar6 + 1;
  }
  local_128 = *(float *)(*(int *)(local_120 + 8) + 0x80);
  local_140 = local_128 * local_128;
  local_134 = 0;
  local_138 = 0.0;
  FUN_005b28e0(local_2c,local_1c,(double)local_128,local_16c);
  while (cVar1 = FUN_00462710(&local_13c), cVar1 != '\0') {
    local_11c = FUN_004da060(*local_13c);
    if (((local_11c != 0) && (local_11c != *(int *)(local_120 + 0xd8))) &&
       (uVar3 = FUN_0045c4b0(), (uVar3 & 0x400) == 0)) {
      pfVar4 = (float *)(**(code **)(*(int *)(local_11c + 0x18) + 0xc))();
      local_14 = *pfVar4;
      local_10 = pfVar4[1];
      local_c = pfVar4[2];
      FUN_00820180();
      if ((0.0 <= local_c) && (local_c <= local_128)) {
        iVar5 = FUN_00462400();
        local_12c = *(float *)(iVar5 + 0xc) * 0.75;
        local_12c = local_12c * local_12c;
        local_124 = local_14 * local_14 + local_10 * local_10;
        local_130 = local_c * local_c + local_124;
        if ((local_124 <= local_12c) || (local_124 <= local_130 * *(float *)(local_120 + 0xcc))) {
          local_118 = 1.0 - local_124 / local_130;
          local_118 = local_118 * local_118;
          local_118 = local_118 * local_118;
          local_118 = local_118 * local_118;
          local_118 = local_118 * local_118;
          local_118 = local_118 * local_118;
          iVar5 = (*(code *)**(undefined4 **)(local_11c + 0x18))();
          local_118 = ((*(float *)(iVar5 + 0xe0) * local_140) / local_130) * local_118;
          if (local_138 < local_118) {
            local_134 = local_11c;
            local_138 = local_118;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

