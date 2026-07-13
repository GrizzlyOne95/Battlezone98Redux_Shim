
void FUN_0081ee70(float *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  undefined8 uVar9;
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
  uVar9 = FUN_008205a0(param_4);
  fVar5 = (float)((ulonglong)uVar9 >> 0x20);
  fVar1 = (float)uVar9;
  uVar9 = FUN_008205a0(param_2);
  fVar6 = (float)((ulonglong)uVar9 >> 0x20);
  fVar2 = (float)uVar9;
  uVar9 = FUN_008205a0(param_3);
  fVar7 = (float)((ulonglong)uVar9 >> 0x20);
  fVar3 = (float)uVar9;
  local_48[0] = fVar1 * fVar3 * fVar2 + fVar5 * fVar7;
  local_48[1] = fVar1 * fVar6;
  local_48[2] = fVar1 * fVar7 * fVar2 - fVar5 * fVar3;
  local_48[3] = fVar5 * fVar3 * fVar2 - fVar1 * fVar7;
  local_38 = fVar5 * fVar6;
  local_34 = fVar5 * fVar7 * fVar2 + fVar1 * fVar3;
  local_30 = fVar3 * fVar6;
  local_2c = -fVar2;
  local_28 = fVar7 * fVar6;
  local_20 = param_5;
  local_18 = param_6;
  local_10 = param_7;
  pfVar8 = local_48;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *param_1 = *pfVar8;
    pfVar8 = pfVar8 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

