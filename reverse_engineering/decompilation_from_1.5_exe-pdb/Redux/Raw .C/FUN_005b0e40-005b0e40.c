
void __thiscall FUN_005b0e40(int param_1,float param_2)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined1 local_c0 [24];
  undefined1 local_a8 [12];
  undefined1 local_9c [8];
  float local_94;
  float local_90;
  float local_8c;
  undefined4 local_88;
  undefined4 local_80;
  int local_7c;
  int local_78;
  int local_74;
  char local_6d;
  int local_6c;
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
  *(float *)(param_1 + 0x240) = *(float *)(param_1 + 0x240) - param_2;
  local_6c = param_1;
  if ((*(float *)(param_1 + 0x240) <= 0.0 && *(float *)(param_1 + 0x240) != 0.0) &&
     ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) == 0)) {
    *(float *)(param_1 + 0x240) =
         *(float *)(param_1 + 0x240) + *(float *)(*(int *)(param_1 + 0xf8) + 0x16c);
    local_6d = '\0';
    local_94 = *(float *)(*(int *)(param_1 + 0xf8) + 0x168) *
               *(float *)(*(int *)(param_1 + 0xf8) + 0x168);
    FID_conflict_begin();
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      FUN_0046b260(local_9c,0);
      piVar2 = (int *)FUN_00421ec0();
      local_74 = *piVar2;
      uVar3 = FUN_0045c4b0();
      if ((uVar3 & 0x200) == 0) {
        uVar6 = *(undefined4 *)(local_6c + 0x108);
        uVar7 = *(undefined8 *)(local_6c + 0x10c);
        puVar4 = (undefined4 *)(**(code **)(*(int *)(local_74 + 0x18) + 0xc))();
        puVar4 = (undefined4 *)FUN_004401a0(local_a8,*puVar4,puVar4[1],puVar4[2],uVar6,uVar7);
        local_20 = *puVar4;
        local_1c = puVar4[1];
        local_18 = puVar4[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        fVar5 = (float10)FUN_004428b0(&local_20);
        local_8c = (float)fVar5;
        if (local_8c <= local_94) {
          cVar1 = FUN_004db510();
          if (cVar1 != '\0') {
            local_6d = '\0';
            break;
          }
          puVar4 = (undefined4 *)FUN_004624b0();
          local_50 = *puVar4;
          local_4c = puVar4[1];
          local_48 = puVar4[2];
          fVar5 = (float10)FUN_004428b0(&local_20);
          local_90 = (float)fVar5;
          if (0.0 < local_90) {
            local_6d = '\x01';
          }
        }
      }
    }
    if (local_6d != '\0') {
      puVar4 = (undefined4 *)FUN_00447f60(local_c0,*(int *)(local_6c + 0xf4) + 0x20);
      local_68 = *puVar4;
      local_64 = puVar4[1];
      local_60 = puVar4[2];
      local_5c = puVar4[3];
      local_58 = puVar4[4];
      local_54 = puVar4[5];
      local_44 = 0;
      local_40 = 0x41700000;
      local_3c = 0;
      local_38 = local_68;
      local_34 = local_64;
      local_30 = local_60;
      local_2c = local_5c;
      local_28 = local_58;
      local_24 = local_54;
      for (local_78 = 0; local_78 < 0x14; local_78 = local_78 + 1) {
        FUN_004927d0();
      }
      FUN_007809d0();
      fVar5 = (float10)FUN_007855e0(*(undefined8 *)(*(int *)(local_6c + 0xf4) + 0x48),
                                    *(undefined8 *)(*(int *)(local_6c + 0xf4) + 0x58));
      *(double *)(*(int *)(local_6c + 0xf4) + 0x50) = (double)fVar5;
      local_7c = FUN_004b0400();
      if (local_7c == 0) {
        local_80 = *(undefined4 *)(local_6c + 0xf4);
      }
      else {
        local_80 = (**(code **)(*(int *)(local_7c + 0x18) + 0x30))();
      }
      local_88 = local_80;
      if (*(int *)(*(int *)(local_6c + 0xf8) + 0x170) != 0) {
        FUN_004cb7b0(*(int *)(local_6c + 0xf4) + 0x20,local_80);
      }
      *(uint *)(*(int *)(local_6c + 0xf4) + 0x14) =
           *(uint *)(*(int *)(local_6c + 0xf4) + 0x14) | 0x280;
      cVar1 = FUN_00571c40();
      if (cVar1 != '\0') {
        FUN_004b8460();
      }
    }
  }
  FUN_00511460();
  FUN_0083e885();
  return;
}

