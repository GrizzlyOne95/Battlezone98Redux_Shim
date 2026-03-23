
void __thiscall FUN_0056af20(int param_1,float *param_2,undefined4 *param_3,char param_4)

{
  undefined4 *puVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  uint local_48;
  int local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = *(float *)(*(int *)(param_1 + 0xc) + 0x54);
  local_44 = param_1;
  puVar1 = (undefined4 *)FUN_00439de0(local_74,param_1 + 0x28);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  local_24 = puVar1[2];
  pfVar2 = (float *)FUN_004401a0(local_80,*param_3,param_3[1],param_3[2],local_2c,local_28,local_24)
  ;
  local_20 = *pfVar2;
  local_1c = pfVar2[1];
  local_18 = pfVar2[2];
  local_60 = local_4c * local_4c;
  local_54 = local_20 * local_20;
  local_58 = local_1c * local_1c;
  local_50 = local_18 * local_18;
  local_3c = local_54 + local_50;
  local_30 = local_58 / local_3c + 1.0;
  local_34 = local_60 - local_1c * 9.8;
  local_64 = local_3c * 24.01;
  local_38 = local_34 * local_34 - local_30 * 4.0 * local_64;
  local_14 = local_20;
  local_10 = local_1c;
  local_c = local_18;
  if (local_38 <= 0.0) {
    local_40 = local_34 / (local_30 + local_30);
  }
  else if (param_4 == '\0') {
    fVar3 = (float10)FUN_00417910(local_38);
    local_68 = (float)fVar3;
    local_40 = (local_34 - local_68) / (local_30 + local_30);
  }
  else {
    fVar3 = (float10)FUN_00417910(local_38);
    local_5c = (float)fVar3;
    local_40 = (local_5c + local_34) / (local_30 + local_30);
  }
  *param_2 = local_3c / local_40;
  local_48 = (uint)(0.0 <= local_38);
  FUN_0083e885();
  return;
}

