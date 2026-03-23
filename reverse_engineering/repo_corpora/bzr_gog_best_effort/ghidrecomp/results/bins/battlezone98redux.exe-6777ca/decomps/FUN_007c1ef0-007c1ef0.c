
undefined4 * __thiscall
FUN_007c1ef0(undefined4 *param_1,undefined4 param_2,float param_3,float param_4,float param_5,
            float param_6,undefined4 param_7,undefined4 param_8)

{
  void *pvVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  undefined4 local_30;
  undefined4 local_28;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861d90;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  local_8 = 0;
  *param_1 = cUI_Alert::vftable;
  param_1[0x51] = 0;
  param_1[0x52] = 0;
  param_1[0x53] = 0;
  param_1[0x54] = 0;
  param_1[0x55] = 0;
  *(undefined1 *)(param_1 + 0x56) = 1;
  DAT_009455e4 = param_1;
  FUN_007d3f20(8);
  if ((param_1[5] & 0x200) == 0) {
    FUN_007c1a50(param_3,param_4,param_5,param_6,param_8);
    pvVar1 = operator_new(0x294c);
    local_8._0_1_ = 2;
    if (pvVar1 == (void *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = FUN_007ccb70("AlertText",param_3 + 33.5,param_6 / 4.0 + param_4,param_5 - 67.0,
                              param_6 - 100.0,0,param_8);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x51] = local_30;
    FUN_007cce50(0x3f800000);
    uVar2 = FUN_007c19b0();
    FUN_007d3f20((uVar2 & 0xff) + 1);
    FUN_007d2110(param_1[0x51],0);
  }
  else {
    fVar3 = 720.0 - param_5 / 2.0;
    fVar4 = 540.0 - param_6 / 2.0;
    FUN_007c1a50(fVar3,fVar4,param_5,param_6,param_8);
    FUN_007d3650(fVar3,fVar4,0);
    pvVar1 = operator_new(0x294c);
    local_8._0_1_ = 1;
    if (pvVar1 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_007ccb70("AlertText",720.0 - (param_5 - 67.0) / 2.0,param_6 / 4.0 + fVar4,
                              param_5 - 67.0,param_6 - 100.0,0,param_8);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x51] = local_28;
    FUN_007cce50(0x3f800000);
    uVar2 = FUN_007c19b0();
    FUN_007d3f20((uVar2 & 0xff) + 1);
    FUN_007d2110(param_1[0x51],0);
  }
  ExceptionList = local_10;
  return param_1;
}

