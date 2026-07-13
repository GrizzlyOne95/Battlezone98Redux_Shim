
void FUN_0081fa10(undefined4 *param_1,float *param_2,float *param_3)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  double local_74;
  undefined4 local_6c [4];
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  float local_50;
  float local_4c;
  double local_44;
  double local_3c;
  double local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_44 = (double)*param_2;
  local_3c = (double)param_2[1];
  local_34 = (double)param_2[2];
  local_14 = *param_3;
  local_10 = param_3[1];
  local_c = param_3[2];
  pfVar1 = (float *)FUN_004621a0(local_80,&local_14);
  local_14 = *pfVar1;
  local_10 = pfVar1[1];
  local_c = pfVar1[2];
  local_74 = (double)(local_14 * local_14 + local_c * local_c);
  if (0.02 <= local_74) {
    local_2c = 0;
    local_28 = 0x3f800000;
    local_24 = 0;
    puVar2 = (undefined4 *)FUN_004440d0(local_a4,&local_2c,&local_14);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
    puVar2 = (undefined4 *)FUN_004621a0(local_98,&local_20);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    local_18 = puVar2[2];
  }
  else {
    local_20 = 0x3f800000;
    local_1c = 0;
    local_18 = 0;
  }
  puVar2 = (undefined4 *)FUN_004440d0(local_8c,&local_14,&local_20);
  local_2c = *puVar2;
  local_28 = puVar2[1];
  local_24 = puVar2[2];
  local_6c[0] = local_20;
  local_6c[1] = local_1c;
  local_6c[2] = local_18;
  local_6c[3] = *puVar2;
  local_5c = puVar2[1];
  local_58 = puVar2[2];
  local_54 = local_14;
  local_50 = local_10;
  local_4c = local_c;
  puVar2 = local_6c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

