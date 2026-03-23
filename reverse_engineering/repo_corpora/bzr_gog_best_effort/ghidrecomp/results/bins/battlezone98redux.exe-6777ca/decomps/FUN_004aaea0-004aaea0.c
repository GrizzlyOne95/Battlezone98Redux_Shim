
void FUN_004aaea0(float param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  float fVar4;
  undefined1 local_80 [12];
  float local_74;
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  float local_40;
  uint local_3c;
  int local_38;
  float local_34;
  int local_30;
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
  if ((*(uint *)(DAT_0094672c + 0x30) & 1) == 0) {
    local_28 = FUN_0077d680();
    FUN_0049bf10();
    local_2c = FUN_0083f040();
    FUN_0049bf10();
    local_30 = FUN_0083f040();
    iVar1 = FUN_0077d660(local_2c,local_30);
    if (iVar1 == local_28) {
      iVar1 = FUN_0077d660(local_2c + -1,local_30 + -1);
      local_50 = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c,local_30 + -1);
      local_5c = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c + 1,local_30 + -1);
      local_58 = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c + -1,local_30);
      local_48 = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c + 1,local_30);
      local_3c = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c + -1,local_30 + 1);
      local_4c = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c,local_30 + 1);
      local_54 = (uint)(iVar1 == local_28);
      iVar1 = FUN_0077d660(local_2c + 1,local_30 + 1);
      local_44 = (uint)(iVar1 == local_28);
      local_38 = (int)(local_50 + local_5c + local_58 + local_48 + local_3c + local_4c + local_54 +
                      local_44) / 2;
      local_70 = (float)*(double *)(*(int *)(local_24 + 0xf4) + 0x50);
      fVar3 = (float10)FUN_007855e0(*(undefined8 *)(*(int *)(local_24 + 0xf4) + 0x48),
                                    *(undefined8 *)(*(int *)(local_24 + 0xf4) + 0x58));
      local_74 = (float)fVar3;
      fVar4 = local_70 - local_74;
      if (fVar4 <= 1.0) {
        if (fVar4 <= 0.0) {
          local_34 = 2.0;
        }
        else {
          local_34 = 2.0 - fVar4 * 1.0;
        }
      }
      else {
        local_34 = 1.25 - fVar4 * 0.25;
      }
      local_40 = (float)local_38 * 40.0 * local_34 * param_1;
      if (0.0 < local_40) {
        local_6c = 0;
        local_68 = 0;
        local_64 = 4;
        local_60 = local_40;
        puVar2 = (undefined4 *)
                 FUN_00785430(local_80,(double)*(float *)(local_24 + 0x108),
                              (double)*(float *)(local_24 + 0x110));
        local_20 = *puVar2;
        local_1c = puVar2[1];
        local_18 = puVar2[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        (**(code **)(*(int *)(local_24 + 0x18) + 0x38))(&local_6c,&local_20);
        if (local_24 == DAT_00917afc) {
          FUN_0049b430((float)local_38 * 0.01,0x40a00000,0xff,0x40,0);
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

