
void FUN_0061a370(undefined4 *param_1,float *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float10 fVar5;
  undefined1 local_70 [16];
  double local_60;
  float local_58;
  float local_54 [6];
  float local_3c;
  float local_34;
  float local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar3 = (float *)&DAT_008fe1e0;
  pfVar4 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar4 = pfVar4 + 1;
  }
  local_14 = param_2[8];
  local_10 = 0;
  local_c = param_2[6];
  local_58 = local_14 * local_14 + local_c * local_c;
  if (0.001 <= local_58) {
    fVar5 = (float10)FUN_00417910(local_58);
    local_60 = (double)fVar5;
    local_58 = (float)(1.0 / local_60);
    local_14 = local_14 * local_58;
    local_c = local_c * local_58;
  }
  else {
    local_14 = *param_2;
    local_10 = 0;
    local_c = param_2[2];
  }
  local_54[0] = local_14;
  local_54[2] = -local_c;
  local_3c = local_c;
  local_34 = local_14;
  puVar1 = (undefined4 *)FUN_0081f1e0(local_70,local_54);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  param_1[3] = puVar1[3];
  FUN_0083e885();
  return;
}

