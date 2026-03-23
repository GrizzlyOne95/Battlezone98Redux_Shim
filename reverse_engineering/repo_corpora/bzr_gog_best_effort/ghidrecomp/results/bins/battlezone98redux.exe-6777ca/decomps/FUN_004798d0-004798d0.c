
void FUN_004798d0(undefined4 param_1)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_90 [44];
  undefined1 local_64 [12];
  float local_58;
  float local_54;
  float local_50;
  undefined4 *local_4c;
  float local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  int local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_004b9830();
  if (cVar1 == '\0') {
    fVar6 = (float10)FUN_00822da0();
    local_54 = (float)fVar6;
    if (*(float *)(local_30 + 0x238) <= local_54 && local_54 != *(float *)(local_30 + 0x238)) {
      fVar6 = (float10)FUN_00822da0();
      local_48 = (float)fVar6;
      *(float *)(local_30 + 0x238) = local_48 + 5.0;
      pfVar2 = (float *)(**(code **)(*(int *)(local_30 + 0x18) + 0xc))();
      local_2c = *pfVar2;
      local_28 = pfVar2[1];
      local_24 = pfVar2[2];
      local_44 = 0x42c80000;
      local_58 = 10000.0;
      FUN_005b28e0((double)local_2c,(double)local_24,0x4059000000000000,local_90);
      local_40 = 0;
      local_3c = 0;
LAB_004799bf:
      cVar1 = FUN_00462710(&local_4c);
      if (cVar1 != '\0') {
        local_34 = FUN_00462630(*local_4c);
        if (local_34 != 0) {
          local_38 = (**(code **)(*(int *)(local_34 + 0x18) + 0x30))();
          iVar3 = FUN_00417e20(local_38);
          if ((iVar3 != 0) || (iVar3 = FUN_00462340(local_38), iVar3 != 0)) {
            iVar3 = FUN_00462340(local_38);
            if (iVar3 != 0) {
              iVar3 = (**(code **)(*(int *)(local_34 + 0x18) + 4))();
              iVar4 = (**(code **)(*(int *)(local_30 + 0x18) + 4))();
              if (iVar3 != iVar4) goto LAB_004799bf;
            }
            puVar5 = (undefined4 *)
                     (**(code **)(*(int *)(local_34 + 0x18) + 0xc))(local_2c,local_28,local_24);
            puVar5 = (undefined4 *)FUN_004401a0(local_64,*puVar5,puVar5[1]);
            local_20 = *puVar5;
            local_1c = puVar5[1];
            local_18 = puVar5[2];
            local_14 = local_20;
            local_10 = local_1c;
            local_c = local_18;
            fVar6 = (float10)FUN_00462070(&local_20);
            local_50 = (float)fVar6;
            if (local_50 <= local_58) {
              iVar3 = FUN_0045bdf0();
              if ((iVar3 == 0) && (*(int *)(local_34 + 0xec) == 0)) {
                cVar1 = FUN_00464140();
                if (cVar1 != '\0') {
                  local_3c = local_3c + 1;
                }
              }
              else {
                iVar3 = FUN_00462340(local_38);
                if (iVar3 != 0) {
                  local_40 = local_40 + 1;
                }
              }
            }
          }
        }
        goto LAB_004799bf;
      }
      if ((local_40 < local_3c) && (iVar3 = FUN_005e1220(), 0 < iVar3)) {
        FUN_00479790();
      }
    }
  }
  FUN_0047fcb0(param_1);
  FUN_0083e885();
  return;
}

