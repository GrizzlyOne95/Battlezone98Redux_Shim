
undefined4 * __thiscall
FUN_0059c8e0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  FUN_004e54c0(param_2,param_3,1);
  *param_1 = PatrolTask::vftable;
  param_1[0x53] = param_4;
  param_1[0x54] = param_2;
  uVar1 = rand();
  uVar1 = uVar1 & 0x80000007;
  if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffff8) + 1;
  }
  param_1[0x55] = uVar1;
  return param_1;
}

