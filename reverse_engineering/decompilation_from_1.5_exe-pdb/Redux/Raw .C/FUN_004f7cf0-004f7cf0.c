
undefined4 * __thiscall FUN_004f7cf0(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  float10 fVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847938;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00611300(param_2,param_3);
  local_8 = 0;
  *param_1 = Launcher::vftable;
  param_1[0x2c] = *(undefined4 *)(param_3 + 0x34);
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  param_1[0x32] = *(float *)(param_3 + 0x88) / (float)*(int *)(param_3 + 0xb8);
  param_1[0x34] = 0;
  fVar3 = (float10)FUN_004178f0(*(undefined4 *)(param_3 + 0x8c),uVar1);
  param_1[0x33] = (float)fVar3;
  param_1[0x33] = (float)param_1[0x33] * (float)param_1[0x33];
  param_1[0x35] = 0;
  uVar2 = FUN_00479f30(param_1[6]);
  param_1[0x36] = uVar2;
  param_1[0x37] = 0;
  param_1[0x39] = 0;
  *(undefined1 *)(param_1 + 0x38) = 0;
  *(undefined1 *)((int)param_1 + 0xe1) = 0;
  ExceptionList = local_10;
  return param_1;
}

