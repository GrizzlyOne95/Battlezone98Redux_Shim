
undefined4 * __thiscall FUN_005e2730(undefined4 *param_1,undefined4 param_2,int param_3)

{
  float10 fVar1;
  float10 fVar2;
  
  FUN_0056a380(param_2,param_3);
  *param_1 = ThermalMissile::vftable;
  fVar1 = (float10)FUN_004178b0(*(undefined4 *)(param_3 + 0xd8));
  fVar2 = (float10)FUN_004178b0(*(undefined4 *)(param_3 + 0xd8));
  param_1[0x3e] = (float)fVar1 * (float)fVar2;
  return param_1;
}

