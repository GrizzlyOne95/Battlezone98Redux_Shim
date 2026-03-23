
undefined4 * __thiscall
FUN_00459750(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846fa6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0044dcd0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = TwirlTrailRender::vftable;
  FUN_0045b7b0(uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_0044b810(param_4,param_1 + 0x20,param_1 + 0x2a);
  param_1[0x1c] = param_1[0x20];
  param_1[0x1d] = param_1[0x21];
  param_1[0x1e] = param_1[0x22];
  param_1[0x1f] = param_1[0x23];
  param_1[0x24] = param_1[0x2a];
  param_1[0x25] = param_1[0x2b];
  param_1[0x26] = param_1[0x2c];
  param_1[0x27] = param_1[0x2d];
  param_1[0x28] = param_1[0x2e];
  param_1[0x29] = param_1[0x2f];
  FUN_0045ba50(0x40);
  ExceptionList = local_10;
  return param_1;
}

