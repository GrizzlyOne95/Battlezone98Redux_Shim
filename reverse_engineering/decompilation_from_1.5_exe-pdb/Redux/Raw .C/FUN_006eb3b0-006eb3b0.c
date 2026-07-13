
undefined4 * __thiscall
FUN_006eb3b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  uVar2 = FUN_00417780(param_4);
  uVar3 = FUN_00417780(param_3,uVar2);
  FUN_006f9ce0(uVar3,uVar2);
  return param_1;
}

