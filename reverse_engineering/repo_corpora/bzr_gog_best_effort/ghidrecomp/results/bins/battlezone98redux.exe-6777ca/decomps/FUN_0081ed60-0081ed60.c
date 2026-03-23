
void FUN_0081ed60(float *param_1,undefined4 param_2,undefined4 param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  float *pfVar5;
  undefined8 uVar6;
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
  uVar6 = FUN_008205a0(param_3);
  fVar4 = (float)((ulonglong)uVar6 >> 0x20);
  fVar1 = (float)uVar6;
  uVar6 = FUN_008205a0(param_2);
  local_38 = (float)((ulonglong)uVar6 >> 0x20);
  fVar2 = (float)uVar6;
  local_48[0] = fVar4;
  local_48[1] = 0.0;
  local_48[2] = -fVar1;
  local_48[3] = fVar1 * fVar2;
  local_34 = fVar4 * fVar2;
  local_30 = fVar1 * local_38;
  local_2c = -fVar2;
  local_28 = fVar4 * local_38;
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  pfVar5 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

