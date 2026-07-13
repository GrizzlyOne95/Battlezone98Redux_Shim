
undefined4 * __thiscall FUN_005b89a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_00462400(0x42200000);
  fVar2 = (float10)FUN_00462470(*(undefined4 *)(iVar1 + 0xc));
  fVar2 = (float10)FUN_0044fb20((float)fVar2);
  fVar2 = (float10)FUN_0044fb20((float)fVar2 + 7.5);
  FUN_004e6bf0(param_2,param_3,(float)fVar2);
  *param_1 = ScavGotoRepair::vftable;
  param_1[0x3f] = 0x40a00000;
  return param_1;
}

