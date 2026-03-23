
undefined4 * __thiscall FUN_00459a40(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847020;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00458ad0(param_2,param_3);
  local_8 = 0;
  *param_1 = TwirlTrailRenderClass::vftable;
  if (param_2 == 0) {
    param_1[0x61] = 0x7f7fffff;
    param_1[0x62] = 0;
    param_1[99] = 0;
    param_1[100] = 0;
    param_1[0x65] = 0;
    param_1[0x66] = 0;
    param_1[0x67] = 0;
    param_1[0x68] = 0;
    param_1[0x69] = 0;
    param_1[0x6a] = 0;
    param_1[0x6b] = 0;
    param_1[0x6c] = 0x3f800000;
    param_1[0x6d] = 0x43c80000;
    param_1[0x6e] = 0xc1200000;
  }
  else {
    uVar2 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar1);
    FUN_00589430(param_1 + 0x25);
    local_8._0_1_ = 1;
    FUN_00589800(uVar2,0x73965b8d,param_1 + 0x61,*(undefined4 *)(param_2 + 0x184));
    FUN_00589800(uVar2,0xf92c3036,param_1 + 0x62,*(undefined4 *)(param_2 + 0x188));
    FUN_00589ca0(uVar2,0x2cb72e51,param_1 + 99,*(undefined4 *)(param_2 + 0x18c),
                 *(undefined4 *)(param_2 + 400),*(undefined4 *)(param_2 + 0x194));
    FUN_00589ca0(uVar2,0xf45716fd,param_1 + 0x66,*(undefined4 *)(param_2 + 0x198),
                 *(undefined4 *)(param_2 + 0x19c),*(undefined4 *)(param_2 + 0x1a0));
    FUN_00589ca0(uVar2,0x55d04c01,param_1 + 0x69,*(undefined4 *)(param_2 + 0x1a4),
                 *(undefined4 *)(param_2 + 0x1a8),*(undefined4 *)(param_2 + 0x1ac));
    FUN_00589800(uVar2,&DAT_017e7e20,param_1 + 0x6c,*(undefined4 *)(param_2 + 0x1b0));
    FUN_00589800(uVar2,0x39f85b7d,param_1 + 0x6d,*(undefined4 *)(param_2 + 0x1b4));
    FUN_00589800(uVar2,0xfddec52,param_1 + 0x6e,*(undefined4 *)(param_2 + 0x1b8));
    param_1[0x70] = (float)param_1[0x61] * 4.0;
    param_1[0x71] = (float)param_1[0x61] * 2.0;
    param_1[0x72] = (float)param_1[0x61] * 1.0;
    param_1[0x73] = (float)param_1[0x62] * 4.0;
    param_1[0x74] = (float)param_1[0x62] * 2.0;
    param_1[0x75] = (float)param_1[0x62] * 1.0;
    param_1[0x76] = (float)param_1[0x6d] * 0.6;
    param_1[0x77] = (float)param_1[0x6d] * 0.8;
    param_1[0x78] = (float)param_1[0x6d] * 1.0;
    FUN_0045b760(2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00589530();
  }
  ExceptionList = local_10;
  return param_1;
}

