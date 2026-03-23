
void FUN_00784180(int param_1,int param_2,double param_3,double param_4,double param_5,float param_6
                 ,float param_7,float param_8,float *param_9,undefined4 *param_10)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_5c [12];
  undefined1 local_50 [12];
  float local_44;
  float local_40;
  int local_3c;
  int local_38;
  int local_34;
  float local_30;
  int local_2c;
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
  local_2c = FUN_00784100(param_1,param_2);
  local_34 = FUN_00784100(param_1 + 1,param_2);
  local_3c = FUN_00784100(param_1,param_2 + 1);
  local_38 = FUN_00784100(param_1 + 1,param_2 + 1);
  local_24 = DAT_02cc50e4 * 0.1;
  local_10 = 1.0;
  local_14 = (float)(local_2c - local_34) * local_24;
  local_c = (float)(local_34 - local_38) * local_24;
  local_28 = param_6 * local_14 + param_7 * 1.0 + param_8 * local_c;
  if (local_28 < 0.0) {
    local_1c = (float)(param_3 - (double)param_1);
    local_30 = (float)(param_4 - (double)((float)local_2c * local_24));
    local_20 = (float)(param_5 - (double)param_2);
    local_18 = local_1c * local_14 + local_30 * 1.0 + local_20 * local_c;
    if (local_18 < 0.0) {
      fVar2 = (float10)FUN_00417910(local_14 * local_14 + 1.0 + local_c * local_c);
      local_44 = (float)fVar2;
      if (local_18 <= local_44 * -0.1) goto LAB_00784407;
    }
    local_18 = local_18 / -local_28;
    if (local_18 < *param_9) {
      local_1c = local_18 * param_6 + local_1c;
      local_20 = local_18 * param_8 + local_20;
      if (((local_20 <= local_1c) && (0.0 <= local_20)) && (local_1c <= 1.0)) {
        if (param_9 != (float *)0x0) {
          *param_9 = local_18;
        }
        if (param_10 != (undefined4 *)0x0) {
          puVar1 = (undefined4 *)FUN_004621a0(local_50,&local_14);
          *param_10 = *puVar1;
          param_10[1] = puVar1[1];
          param_10[2] = puVar1[2];
        }
        goto LAB_00784603;
      }
    }
  }
LAB_00784407:
  local_14 = (float)(local_3c - local_38) * local_24;
  local_c = (float)(local_2c - local_3c) * local_24;
  local_28 = param_6 * local_14 + param_7 * local_10 + param_8 * local_c;
  if (local_28 < 0.0) {
    local_1c = (float)(param_3 - (double)param_1);
    local_30 = (float)(param_4 - (double)((float)local_2c * local_24));
    local_20 = (float)(param_5 - (double)param_2);
    local_18 = local_1c * local_14 + local_30 * local_10 + local_20 * local_c;
    if (local_18 < 0.0) {
      fVar2 = (float10)FUN_00417910(local_14 * local_14 + local_10 * local_10 + local_c * local_c);
      local_40 = (float)fVar2;
      if (local_18 <= local_40 * -0.1) goto LAB_00784603;
    }
    local_18 = local_18 / -local_28;
    if (local_18 < *param_9) {
      local_1c = local_18 * param_6 + local_1c;
      local_20 = local_18 * param_8 + local_20;
      if (((local_1c <= local_20) && (0.0 <= local_1c)) && (local_20 <= 1.0)) {
        if (param_9 != (float *)0x0) {
          *param_9 = local_18;
        }
        if (param_10 != (undefined4 *)0x0) {
          puVar1 = (undefined4 *)FUN_004621a0(local_5c,&local_14);
          *param_10 = *puVar1;
          param_10[1] = puVar1[1];
          param_10[2] = puVar1[2];
        }
      }
    }
  }
LAB_00784603:
  FUN_0083e885();
  return;
}

