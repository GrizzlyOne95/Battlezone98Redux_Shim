
void __thiscall FUN_005aa330(int *param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_dc [24];
  undefined1 local_c4 [12];
  undefined1 local_b8 [12];
  undefined1 local_ac [12];
  undefined1 local_a0 [12];
  float local_94;
  int local_90;
  int local_8c;
  int local_88;
  int *local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
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
  local_84 = param_1;
  if ((param_2 != 0) && ((*(uint *)(param_1[0x37] + 0x14) & 0x200) == 0)) {
    FUN_004dc130(param_2);
    cVar1 = FUN_004b9830();
    if (cVar1 == '\0') {
      fVar3 = (float10)FUN_0047e990(param_2);
      local_94 = (float)fVar3;
      (**(code **)(*local_84 + 0x28))(-local_94);
      local_88 = *(int *)(param_2 + 4);
      if (((local_88 != 0) && (*(int *)(local_88 + 0x84) == 0x33)) &&
         (local_90 = FUN_0047fed0((int)((int)(local_94 - 16.0) +
                                       ((int)(local_94 - 16.0) >> 0x1f & 0x1fU)) >> 5,10),
         0 < local_90)) {
        puVar2 = (undefined4 *)FUN_00447f60(local_dc,local_88 + 0x20);
        local_68 = *puVar2;
        local_64 = puVar2[1];
        local_60 = puVar2[2];
        local_5c = puVar2[3];
        local_58 = puVar2[4];
        local_54 = puVar2[5];
        local_2c = local_68;
        local_28 = local_64;
        local_24 = local_60;
        local_20 = local_5c;
        local_1c = local_58;
        local_18 = local_54;
        puVar2 = (undefined4 *)FUN_00439de0(local_a0,local_88 + 0x20);
        local_80 = *puVar2;
        local_7c = puVar2[1];
        local_78 = puVar2[2];
        puVar2 = (undefined4 *)(**(code **)(*local_84 + 0xc))(local_80,local_7c,local_78);
        puVar2 = (undefined4 *)FUN_004401a0(local_ac,*puVar2,puVar2[1],puVar2[2]);
        local_44 = *puVar2;
        local_40 = puVar2[1];
        local_3c = puVar2[2];
        local_38 = local_44;
        local_34 = local_40;
        local_30 = local_3c;
        puVar2 = (undefined4 *)FUN_004621a0(local_b8,&local_44);
        local_74 = *puVar2;
        local_70 = puVar2[1];
        local_6c = puVar2[2];
        puVar2 = (undefined4 *)
                 FUN_00439d00(local_c4,local_84[0x45],local_84[0x46],local_84[0x47],0xc0a00000,
                              local_74,local_70,local_6c);
        local_50 = *puVar2;
        local_4c = puVar2[1];
        local_48 = puVar2[2];
        local_14 = local_50;
        local_10 = local_4c;
        local_c = local_48;
        for (local_8c = 0; local_8c < local_90; local_8c = local_8c + 1) {
          FUN_004927d0(&local_68,&local_50,0);
        }
      }
      if ((float)local_84[0x7a] <= 0.0 && (float)local_84[0x7a] != 0.0) {
        *(uint *)(local_84[0x37] + 0x14) = *(uint *)(local_84[0x37] + 0x14) | 0x1000000;
      }
    }
  }
  FUN_0083e885();
  return;
}

