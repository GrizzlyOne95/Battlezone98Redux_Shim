
undefined4 * __thiscall
FUN_00454020(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_00448f10(param_2,param_3,param_4);
  *param_1 = SphereRender::vftable;
  param_1[0x1c] = *(undefined4 *)(param_2 + 0x18c);
  param_1[0x1d] = *(undefined4 *)(param_2 + 400);
  param_1[0x1e] = *(undefined4 *)(param_2 + 0x194);
  return param_1;
}

