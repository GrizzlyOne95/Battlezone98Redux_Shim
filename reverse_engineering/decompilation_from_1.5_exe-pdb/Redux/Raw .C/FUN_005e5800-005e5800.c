
void __fastcall FUN_005e5800(int param_1)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_a8 [44];
  undefined1 local_7c [12];
  undefined4 *local_70;
  float local_6c;
  int local_68;
  float local_64;
  float local_60;
  float *local_5c;
  float local_58;
  uint *local_54;
  float *local_50;
  float local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
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
  local_3c = param_1;
  pfVar2 = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0xc) + 0x18) + 0xc))();
  local_14 = *pfVar2;
  local_10 = pfVar2[1];
  local_c = pfVar2[2];
  iVar3 = FUN_0045c490();
  local_60 = *(float *)(iVar3 + 8);
  if ((((100.0 < local_60) || (local_14 - DAT_02cd912c < 20.0)) || (DAT_02cd9124 - local_14 < 20.0))
     || ((local_c - DAT_02cd9130 < 20.0 || (DAT_02cd9128 - local_c < 20.0)))) {
    iVar3 = (**(code **)(*(int *)(*(int *)(local_3c + 0xc) + 0x18) + 0x30))();
    local_54 = (uint *)(iVar3 + 0x14);
    *local_54 = *local_54 | 0x200;
  }
  else {
    local_50 = (float *)(*(int *)(*(int *)(local_3c + 0xc) + 0x228) + 0xc4);
    local_5c = (float *)FUN_0045c4d0();
    local_68 = FUN_0045c490();
    local_68 = local_68 + 0x24;
    local_44 = FUN_00462610();
    if (local_44 == 0) {
      *local_50 = 0.0;
      local_48 = 0;
      local_4c = DAT_008fe6c4 * DAT_008fe6c4;
      FUN_005b28e0((double)local_14,(double)local_c,(double)DAT_008fe6c4,local_a8);
      while (cVar1 = FUN_00462710(&local_70), cVar1 != '\0') {
        local_40 = FUN_00462630(*local_70);
        if (((local_40 != 0) && (uVar4 = FUN_0045c4b0(), (uVar4 & 1) == 0)) &&
           (iVar3 = (**(code **)(*(int *)(local_40 + 0x18) + 4))(), iVar3 != 0)) {
          uVar5 = (**(code **)(*(int *)(local_40 + 0x18) + 4))();
          cVar1 = FUN_004db560(uVar5);
          if (cVar1 == '\0') {
            uVar5 = FUN_004625b0();
            cVar1 = FUN_004db560(uVar5);
            if (cVar1 == '\0') {
              puVar6 = (undefined4 *)(**(code **)(*(int *)(local_40 + 0x18) + 0xc))();
              local_38 = *puVar6;
              local_34 = puVar6[1];
              local_30 = puVar6[2];
              fVar7 = (float10)FUN_004620b0();
              local_58 = (float)fVar7;
              if (local_58 < local_4c) {
                local_48 = local_40;
                local_4c = local_58;
              }
            }
          }
        }
      }
      FUN_0049f450(local_48);
    }
    else {
      puVar6 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_3c + 0xc) + 0x18) + 0xc))();
      puVar6 = (undefined4 *)
               (**(code **)(*(int *)(local_44 + 0x18) + 0xc))(*puVar6,puVar6[1],puVar6[2]);
      pfVar2 = (float *)FUN_004401a0(local_7c,*puVar6,puVar6[1],puVar6[2]);
      local_2c = *pfVar2;
      local_28 = pfVar2[1];
      local_24 = pfVar2[2];
      local_6c = local_2c * *local_5c + local_24 * local_5c[2];
      local_20 = local_2c;
      local_1c = local_28;
      local_18 = local_24;
      fVar7 = (float10)FUN_00820570((double)(local_2c * local_2c + local_24 * local_24 + 0.0001));
      local_64 = (float)fVar7;
      fVar7 = (float10)FUN_00447ed0(local_6c * -5.0 * local_64 - *(float *)(local_68 + 4),0xbf800000
                                    ,0x3f800000);
      *local_50 = (float)fVar7;
    }
  }
  FUN_0083e885();
  return;
}

