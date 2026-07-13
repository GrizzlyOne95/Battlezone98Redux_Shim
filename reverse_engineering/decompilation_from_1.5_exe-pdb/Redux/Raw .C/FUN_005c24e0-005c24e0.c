
void FUN_005c24e0(int param_1)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_74 [56];
  undefined4 *local_3c;
  float local_38;
  int local_34;
  float local_30;
  float local_2c;
  int local_28;
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0045c4d0();
  pfVar2 = (float *)FUN_00439de0();
  local_20 = *pfVar2;
  local_1c = pfVar2[1];
  local_18 = pfVar2[2];
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  iVar3 = FUN_00417c70();
  if (param_1 == iVar3) {
    local_34 = 0;
    local_2c = 25.0;
    FUN_005b28e0((double)local_14,(double)local_c,0x4034000000000000,local_74);
    while (cVar1 = FUN_00462710(&local_3c), cVar1 != '\0') {
      local_24 = FUN_004da060(*local_3c);
      if ((local_24 != 0) &&
         (iVar3 = (**(code **)(*(int *)(local_24 + 0x18) + 0x30))(),
         (*(uint *)(iVar3 + 0x14) & 0x200) == 0)) {
        (**(code **)(*(int *)(local_24 + 0x18) + 0xc))();
        fVar4 = (float10)FUN_00462010();
        local_30 = (float)fVar4;
        if (local_30 < local_2c) {
          local_34 = local_24;
          local_2c = local_30;
        }
      }
    }
  }
  else {
    local_28 = FUN_00462610();
    if (local_28 != 0) {
      (**(code **)(*(int *)(local_28 + 0x18) + 0xc))();
      fVar4 = (float10)FUN_00462010();
      local_38 = (float)fVar4;
    }
  }
  FUN_0083e885();
  return;
}

