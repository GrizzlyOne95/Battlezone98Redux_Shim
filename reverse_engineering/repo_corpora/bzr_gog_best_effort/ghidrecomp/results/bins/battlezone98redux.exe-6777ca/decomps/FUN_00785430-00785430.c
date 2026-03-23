
void FUN_00785430(undefined4 *param_1,double param_2,double param_3)

{
  undefined4 *puVar1;
  double dVar2;
  double dVar3;
  undefined1 local_44 [12];
  float local_38;
  float local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  float local_20;
  int local_1c;
  int local_18;
  float local_14 [3];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  dVar2 = (double)DAT_02cc50e4;
  dVar3 = (double)DAT_02cc50e4;
  local_18 = FUN_0046eaf0(dVar2 * param_2);
  local_1c = FUN_0046eaf0(dVar3 * param_3);
  local_38 = (float)(dVar2 * param_2 - (double)local_18);
  local_34 = (float)(dVar3 * param_3 - (double)local_1c);
  local_20 = DAT_02cc50e4 * 0.1;
  local_2c = FUN_00784100(local_18,local_1c);
  local_28 = FUN_00784100(local_18 + 1,local_1c + 1);
  if (local_34 <= local_38) {
    local_24 = FUN_00784100(local_18 + 1,local_1c);
    local_14[0] = (float)(local_2c - local_24) * local_20;
    local_14[2] = (float)(local_24 - local_28) * local_20;
  }
  else {
    local_30 = FUN_00784100(local_18,local_1c + 1);
    local_14[0] = (float)(local_30 - local_28) * local_20;
    local_14[2] = (float)(local_2c - local_30) * local_20;
  }
  local_14[1] = 1.0;
  puVar1 = (undefined4 *)FUN_004621a0(local_44,local_14);
  *param_1 = *puVar1;
  param_1[1] = puVar1[1];
  param_1[2] = puVar1[2];
  FUN_0083e885();
  return;
}

