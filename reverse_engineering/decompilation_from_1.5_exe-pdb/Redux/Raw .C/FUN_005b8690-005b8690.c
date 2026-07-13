
void FUN_005b8690(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_9c [12];
  undefined1 local_90 [36];
  float local_6c;
  undefined4 local_68;
  int local_64;
  int local_60;
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
  fVar4 = (float10)FUN_00822da0();
  local_6c = (float)fVar4;
  if (local_6c <= *(float *)(local_60 + 0x154) + 5.0) {
    FUN_0049f450();
    if (*(int *)(*(int *)(local_60 + 0x10) + 0x228) == 0) {
      (**(code **)(**(int **)(local_60 + 0x10) + 0x60))();
    }
    FUN_0045c4d0();
    puVar3 = (undefined4 *)FUN_00439de0();
    local_5c = *puVar3;
    local_58 = puVar3[1];
    local_54 = puVar3[2];
    local_20 = local_5c;
    local_1c = local_58;
    local_18 = local_54;
    puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_60 + 0x18) + 0x18) + 0xc))();
    puVar3 = (undefined4 *)FUN_004401a0(local_90,*puVar3,puVar3[1],puVar3[2]);
    local_50 = *puVar3;
    local_4c = puVar3[1];
    local_48 = puVar3[2];
    local_14 = local_50;
    local_10 = local_4c;
    local_c = local_48;
    puVar3 = (undefined4 *)FUN_004621a0();
    local_44 = *puVar3;
    local_40 = puVar3[1];
    local_3c = puVar3[2];
    local_2c = local_44;
    local_28 = local_40;
    local_24 = local_3c;
    FUN_00607320();
    puVar3 = (undefined4 *)FUN_004462d0(local_9c,0x40a00000);
    local_38 = *puVar3;
    local_34 = puVar3[1];
    local_30 = puVar3[2];
    FUN_00606f70();
    goto LAB_005b88f3;
  }
  local_68 = *(undefined4 *)(local_60 + 0x10);
  local_64 = *(int *)(local_60 + 0x18);
  (*(code *)**(undefined4 **)(local_64 + 0x18))();
  FUN_005b5060();
  iVar2 = FUN_00572a70();
  if (iVar2 == 0) {
LAB_005b8718:
    iVar2 = FUN_00572a70();
    if (iVar2 != 0) {
      cVar1 = FUN_004b9860();
      if (cVar1 == '\0') {
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          cVar1 = FUN_004b9830();
          if (cVar1 != '\0') {
            FUN_004b9940();
          }
        }
        goto LAB_005b876c;
      }
    }
    (**(code **)(*(int *)(local_64 + 0x18) + 0x10))();
  }
  else {
    cVar1 = FUN_004b9860();
    if (cVar1 != '\0') goto LAB_005b8718;
  }
LAB_005b876c:
  *(undefined4 *)(local_60 + 0xc) = 0xd;
LAB_005b88f3:
  FUN_0083e885();
  return;
}

