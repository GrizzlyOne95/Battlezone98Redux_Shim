
void __fastcall FUN_005efe30(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined4 *puVar5;
  undefined1 local_22c [64];
  undefined1 local_1ec [64];
  undefined1 local_1ac [12];
  undefined1 local_1a0 [12];
  undefined1 local_194 [12];
  undefined1 local_188 [12];
  undefined1 local_17c [12];
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  char local_161;
  int local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144 [16];
  undefined4 local_104 [16];
  undefined4 local_c4 [16];
  undefined4 local_84 [16];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(int *)(*(int *)(param_1 + 0x18) + 0xa0) == 0) ||
     (*(int *)(*(int *)(param_1 + 0x18) + 0xa0) == *(int *)(param_1 + 0x10))) {
    local_168 = 0;
  }
  else {
    local_168 = 1;
  }
  local_161 = (char)local_168;
  local_160 = param_1;
  if (((char)local_168 == '\0') || (*(float *)(param_1 + 0x158) <= 49.0)) {
    iVar2 = (**(code **)(**(int **)(param_1 + 0x18) + 0x28))();
    if (iVar2 == 0) {
      *(undefined4 *)(local_160 + 0xc) = 0xd;
    }
    else {
      local_170 = *(undefined4 *)(*(int *)(local_160 + 0x10) + 0x318);
      local_16c = (**(code **)(**(int **)(local_160 + 0x18) + 0x28))();
      puVar3 = (undefined4 *)FUN_0062e070(local_1ec,local_170,0);
      puVar5 = local_104;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = local_104;
      puVar5 = local_c4;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = (undefined4 *)FUN_0062e070(local_22c,local_16c,0);
      puVar5 = local_144;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = local_144;
      puVar5 = local_84;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = (undefined4 *)FUN_00439de0(local_1ac,local_c4);
      local_15c = *puVar3;
      local_158 = puVar3[1];
      local_154 = puVar3[2];
      puVar3 = (undefined4 *)FUN_00439de0(local_17c,local_84);
      local_150 = *puVar3;
      local_14c = puVar3[1];
      local_148 = puVar3[2];
      pfVar4 = (float *)FUN_004401a0(local_1a0,local_150,local_14c,local_148,local_15c,local_158,
                                     local_154);
      local_20 = *pfVar4;
      local_1c = pfVar4[1];
      local_18 = pfVar4[2];
      local_14 = local_20;
      local_10 = local_1c;
      local_c = local_18;
      if ((local_161 == '\0') && (local_20 * local_20 + local_18 * local_18 < 100.0)) {
        if (*(int *)(*(int *)(local_160 + 0x18) + 0xa0) == *(int *)(local_160 + 0x10)) {
          *(undefined4 *)(local_160 + 0xc) = 0xd;
          goto LAB_005f01bd;
        }
        cVar1 = (**(code **)(**(int **)(local_160 + 0x10) + 0x6c))();
        if (cVar1 != '\0') {
          (**(code **)(**(int **)(local_160 + 0x10) + 0x60))();
        }
      }
      puVar3 = (undefined4 *)FUN_004621a0(local_188,&local_14);
      local_44 = *puVar3;
      local_40 = puVar3[1];
      local_3c = puVar3[2];
      local_38 = local_44;
      local_34 = local_40;
      local_30 = local_3c;
      if (local_161 != '\0') {
        pfVar4 = (float *)FUN_00440000(local_194,0,0,0);
        local_2c = *pfVar4;
        local_28 = pfVar4[1];
        local_24 = pfVar4[2];
        local_14 = local_2c;
        local_10 = local_28;
        local_c = local_24;
      }
      FUN_00607320(&local_44);
      FUN_00606f70(&local_14);
    }
  }
LAB_005f01bd:
  FUN_0083e885();
  return;
}

