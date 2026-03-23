
void FUN_00506870(undefined4 param_1)

{
  int iVar1;
  float *pfVar2;
  undefined4 *puVar3;
  undefined1 local_84 [24];
  undefined4 local_6c;
  undefined1 local_68 [4];
  undefined4 local_64;
  undefined4 local_60;
  double local_5c;
  double local_54;
  int local_4c;
  float *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
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
  local_4c = FUN_004ff820(param_1,1);
  if (local_4c == 0) {
    local_48 = (float *)FUN_004ff7a0(param_1,1);
    if (local_48 == (float *)0x0) {
      iVar1 = FUN_0082c9f5(param_1,1);
      if (iVar1 == 0) {
        local_6c = FUN_004ff750(param_1,1);
        pfVar2 = (float *)FUN_005c8b10(local_84,local_6c);
        local_2c = *pfVar2;
        local_28 = pfVar2[1];
        local_24 = pfVar2[2];
        local_54 = (double)local_2c;
        local_5c = (double)local_24;
        local_20 = local_2c;
        local_1c = local_28;
        local_18 = local_24;
      }
      else {
        local_60 = FUN_0082d377();
        local_64 = FUN_0082c1fd();
        pfVar2 = (float *)FUN_005c8bd0();
        local_38 = *pfVar2;
        local_34 = pfVar2[1];
        local_30 = pfVar2[2];
        local_54 = (double)local_38;
        local_5c = (double)local_30;
        local_14 = local_38;
        local_10 = local_34;
        local_c = local_30;
      }
    }
    else {
      local_54 = (double)*local_48;
      local_5c = (double)local_48[2];
    }
  }
  else {
    local_54 = *(double *)(local_4c + 0x28);
    local_5c = *(double *)(local_4c + 0x38);
  }
  FUN_00785730(local_54,local_5c,local_68,&local_44);
  FUN_0082cd58();
  puVar3 = (undefined4 *)FUN_004ff7e0();
  *puVar3 = local_44;
  puVar3[1] = local_40;
  puVar3[2] = local_3c;
  FUN_0083e885();
  return;
}

