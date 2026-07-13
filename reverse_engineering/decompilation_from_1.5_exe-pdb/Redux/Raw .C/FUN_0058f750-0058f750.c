
int FUN_0058f750(float *param_1)

{
  float fVar1;
  float10 fVar2;
  undefined1 local_54 [16];
  int local_44;
  undefined4 local_40;
  float local_3c;
  int local_38;
  float *local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  float *local_20;
  undefined4 *local_1c;
  float *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084be33;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_40 = DAT_00918150;
  FUN_00590eb0(*param_1 - 50.0,param_1[1] - 50.0,*param_1 + 50.0,param_1[1] + 50.0,&local_30,
               &local_1c,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_28 = FUN_0058bca0(0x34);
  local_8 = 0;
  if (local_28 == 0) {
    local_2c = 0;
  }
  else {
    local_2c = FUN_00592010();
  }
  local_38 = local_2c;
  local_8 = 0xffffffff;
  local_14 = local_2c;
  *(undefined4 *)(local_2c + 0x10) = 4;
  *(undefined4 *)(local_2c + 0x14) = 0;
  FUN_00591fc0();
  local_8 = 1;
  FUN_00592230(local_54);
  FUN_00592230(local_54);
  local_20 = (float *)FUN_005111d0(0);
  local_34 = (float *)FUN_005111d0(1);
  fVar1 = param_1[1];
  *local_20 = *param_1;
  local_20[1] = fVar1;
  FUN_0058f710(local_20,local_30,local_1c);
  DAT_00918150 = local_14;
  for (local_24 = 0; local_24 < local_30; local_24 = local_24 + 1) {
    local_18 = (float *)*local_1c;
    local_1c = local_1c + 1;
    if (local_18 != DAT_00918154) {
      fVar2 = (float10)FUN_0058bec0(local_18[4]);
      local_3c = (float)fVar2;
      if (local_3c != 99999.0) {
        fVar2 = (float10)FUN_00447ed0(*local_20,*local_18 * DAT_02cc50e0 + 1.0,
                                      local_18[2] * DAT_02cc50e0 - 1.0);
        *local_34 = (float)fVar2;
        fVar2 = (float10)FUN_00447ed0(local_20[1],local_18[1] * DAT_02cc50e0 + 1.0,
                                      local_18[3] * DAT_02cc50e0 - 1.0);
        local_34[1] = (float)fVar2;
        FUN_005d22e0(local_14);
        if (*(int *)(local_14 + 0x10) == 0) break;
      }
    }
  }
  DAT_00918150 = local_40;
  local_44 = local_14;
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return local_44;
}

