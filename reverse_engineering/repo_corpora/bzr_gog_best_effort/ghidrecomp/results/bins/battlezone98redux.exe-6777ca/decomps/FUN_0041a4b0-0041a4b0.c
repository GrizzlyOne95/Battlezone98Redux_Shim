
void __thiscall
FUN_0041a4b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844b94;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00418d40(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = TouchInputAnalog::vftable;
  FUN_004186f0();
  local_8._0_1_ = 1;
  FUN_004186f0();
  local_8 = CONCAT31(local_8._1_3_,2);
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x23] = 0;
  FUN_00418890(param_2,param_3,param_4);
  FUN_00418890(param_2,param_5,param_6);
  uVar1 = FUN_0068bed0("button_analog_cam");
  param_1[0x1b] = uVar1;
  uVar1 = FUN_0068bed0("button_analog_base");
  param_1[0x1f] = uVar1;
  *(undefined1 *)(param_1 + 0xf) = 1;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

