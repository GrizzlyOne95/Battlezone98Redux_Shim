
void __thiscall FUN_00588a40(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  undefined8 uVar6;
  float local_48 [4];
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar1 = *(float *)(param_1 + 0x50);
  fVar2 = *(float *)(param_1 + 0x58);
  uVar6 = FUN_008205a0(0x3f5f66f3);
  local_38 = (float)((ulonglong)uVar6 >> 0x20);
  fVar3 = (float)uVar6;
  local_48[0] = fVar2;
  local_48[1] = 0.0;
  local_48[2] = -fVar1;
  local_48[3] = fVar1 * fVar3;
  local_34 = fVar2 * fVar3;
  local_30 = fVar1 * local_38;
  local_2c = -fVar3;
  local_28 = fVar2 * local_38;
  local_20 = (double)(*(float *)(param_1 + 0x44) - fVar1 * local_38 * 500.0);
  local_18 = (double)(*(float *)(param_1 + 0x48) - -fVar3 * 500.0);
  local_10 = (double)(*(float *)(param_1 + 0x4c) - fVar2 * local_38 * 500.0);
  pfVar5 = local_48;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *param_2 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    param_2 = param_2 + 1;
  }
  FUN_0083e885();
  return;
}

