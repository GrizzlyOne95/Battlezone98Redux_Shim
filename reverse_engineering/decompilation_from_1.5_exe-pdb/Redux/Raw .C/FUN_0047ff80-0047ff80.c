
undefined4 * __thiscall
FUN_0047ff80(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_004e0190();
  *param_1 = BuildingClass::vftable;
  param_1[5] = param_2;
  param_1[6] = param_3;
  param_1[7] = param_4;
  *(undefined1 *)(param_1 + 0x54) = 0;
  return param_1;
}

