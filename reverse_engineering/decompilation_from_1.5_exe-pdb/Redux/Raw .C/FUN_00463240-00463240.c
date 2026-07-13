
void FUN_00463240(int param_1,float *param_2)

{
  char cVar1;
  float *pfVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_104 [44];
  undefined1 local_d8 [12];
  undefined1 local_cc [12];
  undefined1 local_c0 [12];
  float local_b4;
  int local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  undefined4 *local_a0;
  float local_9c;
  float local_98;
  int local_94;
  int local_90;
  float local_8c;
  int local_88;
  float local_84;
  int local_80;
  int local_7c;
  int local_78;
  float local_74;
  float local_70;
  float local_6c;
  int local_68;
  float local_64;
  int local_60;
  float local_5c;
  float local_58;
  float local_54;
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
  pfVar2 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_5c = *pfVar2;
  local_58 = pfVar2[1];
  local_54 = pfVar2[2];
  local_78 = 0;
  local_74 = *param_2;
  local_88 = 0;
  local_70 = *param_2;
  local_68 = 0;
  local_64 = *param_2;
  uVar3 = FUN_00462530();
  local_90 = FUN_00462630(uVar3);
  fVar7 = (float10)FUN_00417910(*param_2);
  local_a8 = (float)fVar7;
  FUN_005b28e0((double)local_5c,(double)local_54,(double)local_a8,local_104);
LAB_00463320:
  do {
    do {
      do {
        cVar1 = FUN_00462710(&local_a0);
        if (cVar1 == '\0') {
          if (local_78 == 0) {
            if (local_68 == 0) {
              *param_2 = local_70;
            }
            else {
              *param_2 = local_64;
            }
          }
          else {
            *param_2 = local_74;
          }
          FUN_0083e885();
          return;
        }
        local_60 = FUN_00462630(*local_a0);
      } while (local_60 == 0);
      uVar3 = (**(code **)(*(int *)(local_60 + 0x18) + 4))();
      cVar1 = FUN_004db600(uVar3);
    } while (cVar1 == '\0');
    uVar3 = FUN_004625b0();
    cVar1 = FUN_004db600(uVar3);
  } while (cVar1 == '\0');
  iVar4 = FUN_004625b0();
  iVar5 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
  if (iVar4 != iVar5) goto code_r0x004633b5;
  goto LAB_004633d2;
code_r0x004633b5:
  uVar3 = FUN_004625b0();
  cVar1 = FUN_004db600(uVar3);
  if (cVar1 == '\0') goto LAB_00463320;
LAB_004633d2:
  fVar7 = (float10)FUN_004624f0();
  local_ac = (float)fVar7;
  if ((local_ac == 0.0) || (*(char *)(local_60 + 0x9c) != '\0')) goto LAB_00463320;
  cVar1 = FUN_004631d0(local_60);
  if (cVar1 != '\0') {
    if (local_60 == local_90) {
      puVar6 = (undefined4 *)
               (**(code **)(*(int *)(local_60 + 0x18) + 0xc))(local_5c,local_58,local_54);
      puVar6 = (undefined4 *)FUN_004401a0(local_c0,*puVar6,puVar6[1]);
      local_44 = *puVar6;
      local_40 = puVar6[1];
      local_3c = puVar6[2];
      local_20 = local_44;
      local_1c = local_40;
      local_18 = local_3c;
      fVar7 = (float10)FUN_00462070(&local_44);
      local_8c = (float)fVar7;
      if (local_8c < local_64) {
        local_68 = local_60;
        local_64 = local_8c;
      }
    }
    goto LAB_00463320;
  }
  local_7c = (**(code **)(*(int *)(local_60 + 0x18) + 0x30))();
  iVar4 = FUN_00417e20(local_7c);
  if (iVar4 != 0) {
    local_94 = local_60;
    cVar1 = FUN_00462670();
    if (cVar1 == '\0') {
      puVar6 = (undefined4 *)
               (**(code **)(*(int *)(local_60 + 0x18) + 0xc))(local_5c,local_58,local_54);
      puVar6 = (undefined4 *)FUN_004401a0(local_d8,*puVar6,puVar6[1]);
      local_50 = *puVar6;
      local_4c = puVar6[1];
      local_48 = puVar6[2];
      local_2c = local_50;
      local_28 = local_4c;
      local_24 = local_48;
      fVar7 = (float10)FUN_00462070(&local_50);
      local_6c = (float)fVar7;
      iVar4 = FUN_0045bdf0();
      if (iVar4 == 0) {
        if (local_6c < local_70) {
          local_70 = local_6c;
          local_88 = local_60;
        }
      }
      else if (local_6c < local_74) {
        local_74 = local_6c;
        local_78 = local_60;
      }
    }
    goto LAB_00463320;
  }
  iVar4 = FUN_00462340(local_7c);
  if (iVar4 == 0) goto LAB_00463320;
  puVar6 = (undefined4 *)(**(code **)(*(int *)(local_60 + 0x18) + 0xc))(local_5c,local_58,local_54);
  puVar6 = (undefined4 *)FUN_004401a0(local_cc,*puVar6,puVar6[1]);
  local_38 = *puVar6;
  local_34 = puVar6[1];
  local_30 = puVar6[2];
  local_14 = local_38;
  local_10 = local_34;
  local_c = local_30;
  fVar7 = (float10)FUN_00462070(&local_38);
  local_84 = (float)fVar7;
  if (local_60 != local_90) {
    uVar3 = FUN_00462550();
    local_80 = FUN_00462630(uVar3);
    if (local_80 != 0) {
      fVar7 = (float10)FUN_00822d80();
      local_b4 = (float)fVar7;
      local_98 = local_b4;
      fVar7 = (float10)FUN_00462570();
      local_9c = (float)fVar7;
      if (local_98 - local_9c <= 10.0) {
        uVar3 = (**(code **)(*(int *)(local_80 + 0x18) + 4))();
        cVar1 = FUN_004db560(uVar3);
        if (cVar1 != '\0') goto LAB_00463773;
      }
    }
    if (4900.0 < local_84) goto LAB_00463320;
    FUN_00462490();
    fVar7 = (float10)FUN_004428b0();
    local_a4 = (float)fVar7;
    if ((local_a4 < 0.0) ||
       (local_b0 = *(int *)(local_7c + 0x88), (*(uint *)(local_b0 + 0x114) & 0x80) == 0))
    goto LAB_00463320;
  }
LAB_00463773:
  if (local_84 < local_64) {
    local_64 = local_84;
    local_68 = local_60;
  }
  goto LAB_00463320;
}

