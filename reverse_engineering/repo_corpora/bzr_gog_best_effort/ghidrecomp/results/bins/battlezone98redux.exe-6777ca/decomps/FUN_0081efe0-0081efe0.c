
void FUN_0081efe0(float *param_1,float *param_2)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float local_48 [4];
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar3 = *param_2 * 2.0 * *param_2;
  fVar4 = param_2[1] * 2.0 * param_2[1];
  fVar5 = param_2[2] * 2.0 * param_2[2];
  fVar6 = *param_2 * 2.0 * param_2[1];
  fVar7 = *param_2 * 2.0 * param_2[2];
  fVar8 = *param_2 * 2.0 * param_2[3];
  fVar9 = param_2[1] * 2.0 * param_2[2];
  fVar10 = param_2[1] * 2.0 * param_2[3];
  fVar11 = param_2[2] * 2.0 * param_2[3];
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  local_48[0] = (1.0 - fVar4) - fVar5;
  local_48[1] = fVar6 - fVar11;
  local_48[2] = fVar7 + fVar10;
  local_48[3] = fVar6 + fVar11;
  local_38 = (1.0 - fVar3) - fVar5;
  local_34 = fVar9 - fVar8;
  local_30 = fVar7 - fVar10;
  local_2c = fVar9 + fVar8;
  local_28 = (1.0 - fVar3) - fVar4;
  pfVar2 = local_48;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

