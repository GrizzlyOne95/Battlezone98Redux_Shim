
void __thiscall FUN_005d1fe0(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float fVar3;
  undefined8 uVar4;
  undefined1 local_8c [4];
  undefined1 local_88 [4];
  undefined1 local_84 [4];
  undefined1 local_80 [4];
  undefined8 local_7c;
  undefined4 local_74;
  undefined4 local_70;
  int local_6c;
  int local_68;
  undefined8 local_64;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  float local_44;
  float local_40;
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
  local_74 = DAT_00920ef4;
  local_5c = param_1;
  for (local_54 = 0; local_54 < *(int *)(local_5c + 0x4b0); local_54 = local_54 + 1) {
    local_4c = local_5c + 0x30 + local_54 * 0x24;
    FUN_00820180(&local_44,local_4c,1,param_2 + 0x40);
    iVar1 = FUN_006895d0(param_2,&local_44,*(undefined4 *)(local_4c + 0xc));
    if (iVar1 < 1) {
      DAT_00920ef4 = local_3c;
      FUN_0049bf10(*(undefined4 *)(local_4c + 0x20));
      local_70 = FUN_0083f040();
      FUN_0068f0f0(local_70,local_80,local_88,local_8c,local_84);
      uVar4 = local_7c;
      for (local_48 = 0; local_7c = uVar4, local_48 < 0x18; local_48 = local_48 + 1) {
        uVar4 = FUN_008205a0(((float)local_48 * 6.2831855) / 24.0);
        fVar3 = (float)((ulonglong)uVar4 >> 0x20);
        local_50 = local_48 * 2;
        *(float *)(DAT_02cecf70 + local_48 * 0x18) = fVar3 * *(float *)(local_4c + 0xc) + local_44;
        *(float *)(DAT_02cecf70 + 4 + local_48 * 0x18) =
             (float)uVar4 * *(float *)(local_4c + 0xc) + local_40;
        *(undefined4 *)(DAT_02cecf70 + 8 + local_48 * 0x18) = local_3c;
        *(float *)(DAT_02cecf70 + (local_50 + 1) * 0xc) =
             fVar3 * *(float *)(local_4c + 0x10) + local_44;
        *(float *)(DAT_02cecf70 + 4 + (local_50 + 1) * 0xc) =
             (float)uVar4 * *(float *)(local_4c + 0x10) + local_40;
        *(undefined4 *)(DAT_02cecf70 + 8 + (local_50 + 1) * 0xc) = local_3c;
        local_64 = uVar4;
      }
      for (local_48 = 0; local_48 < 0x18; local_48 = local_48 + 1) {
        local_58 = local_48 * 2;
        if (local_58 == 0) {
          local_68 = 0x2e;
        }
        else {
          local_68 = local_58 + -2;
        }
        local_6c = local_68;
        puVar2 = (undefined4 *)(local_48 * 0x18 + DAT_02cecf70);
        local_38 = *puVar2;
        local_34 = puVar2[1];
        local_30 = puVar2[2];
        puVar2 = (undefined4 *)(local_68 * 0xc + DAT_02cecf70);
        local_2c = *puVar2;
        local_28 = puVar2[1];
        local_24 = puVar2[2];
        puVar2 = (undefined4 *)((local_68 + 1) * 0xc + DAT_02cecf70);
        local_20 = *puVar2;
        local_1c = puVar2[1];
        local_18 = puVar2[2];
        puVar2 = (undefined4 *)((local_58 + 1) * 0xc + DAT_02cecf70);
        local_14 = *puVar2;
        local_10 = puVar2[1];
        local_c = puVar2[2];
        FUN_0068d2f0(param_2,(int)*(float *)(local_4c + 0x20),&local_38,4);
      }
    }
  }
  DAT_00920ef4 = local_74;
  FUN_0083e885();
  return;
}

