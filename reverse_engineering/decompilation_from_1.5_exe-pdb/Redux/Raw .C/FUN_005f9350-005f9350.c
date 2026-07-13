
CDC * __fastcall FUN_005f9350(CDC *param_1)

{
  CDC::CDC(param_1);
  *(undefined ***)param_1 = UnitProcess::vftable;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 3;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  param_1[0x40] = (CDC)0x1;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 1;
  param_1[0x48] = (CDC)0x0;
  param_1[0x49] = (CDC)0x1;
  param_1[0x4a] = (CDC)0x0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  return param_1;
}

