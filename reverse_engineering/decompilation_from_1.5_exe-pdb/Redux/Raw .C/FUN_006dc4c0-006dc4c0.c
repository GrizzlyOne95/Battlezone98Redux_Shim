
undefined4 *
FUN_006dc4c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_006eba90(param_4);
  uVar1 = FUN_00417780(param_3,uVar1);
  uVar1 = FUN_00417780(param_2,uVar1);
  uVar1 = _Move<>(uVar1);
  puVar2 = (undefined4 *)FUN_006ebaa0(&param_4,uVar1);
  *param_1 = *puVar2;
  return param_1;
}

