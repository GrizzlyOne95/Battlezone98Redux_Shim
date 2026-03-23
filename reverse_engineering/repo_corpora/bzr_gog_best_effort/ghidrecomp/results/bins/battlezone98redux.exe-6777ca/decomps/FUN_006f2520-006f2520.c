
uint * __thiscall FUN_006f2520(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *param_1;
  uVar2 = *param_2;
  uVar3 = param_2[1];
  *param_1 = uVar1 - *param_2;
  param_1[1] = (param_1[1] - uVar3) - (uint)(uVar1 < uVar2);
  return param_1;
}

