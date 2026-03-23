
CDC * __fastcall FUN_00473960(CDC *param_1)

{
  CDC::CDC(param_1);
  *(undefined ***)param_1 = ArmoryProcess::vftable;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 3;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  param_1[0x41] = (CDC)0x1;
  return param_1;
}

