
undefined4 FUN_006d34b0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  uVar2 = FUN_006d3430(param_1,param_3);
  uVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  puVar3 = (undefined4 *)FUN_004fbb60();
  uVar1 = puVar3[1];
  *param_3 = *puVar3;
  param_3[1] = uVar1;
  return uVar2;
}

