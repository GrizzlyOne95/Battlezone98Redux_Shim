
void FUN_0068ad00(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,
                 undefined4 param_6)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  float local_d4;
  int local_d0;
  float local_cc;
  int local_c8 [48];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_5 < 0xc) {
    param_5 = 0xc;
  }
  if (0x18 < param_5) {
    param_5 = 0x18;
  }
  fVar1 = (float10)FUN_004178b0(6.2831855 / (float)param_5);
  fVar2 = (float10)FUN_004178f0(6.2831855 / (float)param_5);
  local_cc = 0.0;
  local_c8[0] = (int)(float)param_4 + param_2;
  local_c8[1] = param_3;
  local_d4 = (float)param_4;
  for (local_d0 = 1; local_d0 < param_5; local_d0 = local_d0 + 1) {
    fVar3 = local_d4 * (float)fVar1 - local_cc * (float)fVar2;
    local_cc = local_d4 * (float)fVar2 + local_cc * (float)fVar1;
    local_c8[local_d0 * 2] = (int)fVar3 + param_2;
    local_c8[local_d0 * 2 + 1] = (int)local_cc + param_3;
    local_d4 = fVar3;
  }
  FUN_00687550(local_c8,param_5,param_6);
  FUN_0083e885();
  return;
}

