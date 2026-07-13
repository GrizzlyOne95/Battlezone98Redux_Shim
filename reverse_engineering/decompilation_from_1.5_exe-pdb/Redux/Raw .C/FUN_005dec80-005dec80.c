
void FUN_005dec80(void)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_c4 [44];
  undefined1 local_98 [16];
  undefined4 *local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  int local_78;
  float *local_74;
  float local_70;
  int local_6c;
  float local_68;
  float local_64;
  float local_60;
  int local_5c;
  float local_58;
  float local_54;
  undefined *local_50;
  int local_4c;
  float local_48;
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
  local_5c = FUN_00417c70();
  puVar2 = (undefined4 *)(**(code **)(*(int *)(local_5c + 0x18) + 0xc))();
  local_44 = *puVar2;
  local_40 = puVar2[1];
  local_3c = puVar2[2];
  local_74 = (float *)FUN_00492d40();
  if (local_74 != (float *)0x0) {
    local_58 = *local_74;
    local_80 = local_58 * local_58;
    local_50 = &DAT_025ce6f8;
    local_6c = 0;
    local_70 = 0.0;
    FUN_005b28e0((double)(DAT_025ce710 * local_58 * 0.5) + DAT_025ce720,
                 (double)(DAT_025ce718 * local_58 * 0.5) + DAT_025ce730,(double)(local_58 * 0.5),
                 local_c4);
LAB_005ded8e:
    cVar1 = FUN_00462710(&local_88);
    if (cVar1 != '\0') {
      local_4c = FUN_004da060(*local_88);
      if ((((local_4c != 0) && (local_4c != local_5c)) &&
          (uVar3 = FUN_0045c4b0(), (uVar3 & 0x201) == 0)) &&
         (((iVar4 = (*(code *)**(undefined4 **)(local_4c + 0x18))(), *(int *)(iVar4 + 0x1c) == 2 ||
           (iVar4 = (*(code *)**(undefined4 **)(local_4c + 0x18))(), *(int *)(iVar4 + 0x1c) == 1))
          || (iVar4 = (*(code *)**(undefined4 **)(local_4c + 0x18))(), *(int *)(iVar4 + 0x1c) == 6))
         )) {
        puVar2 = (undefined4 *)
                 (**(code **)(*(int *)(local_4c + 0x18) + 0xc))(local_44,local_40,local_3c);
        puVar2 = (undefined4 *)FUN_004401a0(local_98,*puVar2,puVar2[1]);
        local_20 = *puVar2;
        local_1c = puVar2[1];
        local_18 = puVar2[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        cVar1 = FUN_004db5b0(local_4c);
        if (((cVar1 != '\0') && (local_78 = FUN_005c1830(), local_78 != 0)) &&
           (cVar1 = FUN_005c1850(), cVar1 != '\0')) {
          local_7c = 0x3f800000;
          puVar2 = (undefined4 *)FUN_0049c4f0();
          local_38 = *puVar2;
          local_34 = puVar2[1];
          local_30 = puVar2[2];
          local_2c = puVar2[3];
          local_28 = puVar2[4];
          local_24 = puVar2[5];
          iVar4 = FUN_00784620(local_38,local_34,local_30,local_2c,local_28,local_24,local_14,
                               local_10,local_c,&local_7c,0);
          if (iVar4 != 0) goto LAB_005ded8e;
        }
        fVar5 = (float10)FUN_004428b0();
        local_64 = (float)fVar5;
        if (0.0001 <= local_64) {
          fVar5 = (float10)FUN_004428b0();
          local_54 = (float)fVar5;
          if ((0.0001 <= local_54) && (local_54 <= local_80)) {
            local_68 = local_64 * local_64;
            local_84 = local_54 - local_68;
            iVar4 = FUN_00462400();
            local_60 = *(float *)(iVar4 + 0xc) * 0.75;
            local_60 = local_60 * local_60;
            if (((local_84 <= local_60) || (local_54 * 0.5 <= local_68)) &&
               (local_48 = (local_68 / local_54) * (local_68 / local_54),
               local_48 = local_48 * local_48, local_48 = local_48 * local_48,
               local_48 = local_48 * local_48, local_48 = local_48 * local_48, local_70 < local_48))
            {
              local_6c = local_4c;
              local_70 = local_48;
            }
          }
        }
      }
      goto LAB_005ded8e;
    }
  }
  FUN_0083e885();
  return;
}

