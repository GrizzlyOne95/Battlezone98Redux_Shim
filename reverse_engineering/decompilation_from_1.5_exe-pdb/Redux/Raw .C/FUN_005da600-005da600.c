
undefined4 * __thiscall FUN_005da600(undefined4 *param_1,undefined4 param_2,int param_3)

{
  FUN_0047e9c0(param_2,param_3);
  *param_1 = SprayBuilding::vftable;
  param_1[6] = SprayBuilding::vftable;
  param_1[0x8e] = 0;
  *(undefined1 *)(param_1 + 0x8f) = 0;
  *(undefined1 *)((int)param_1 + 0x23d) = 0;
  param_1[0x90] = *(uint *)(param_3 + 0x174) ^ 0x80000000;
  return param_1;
}

