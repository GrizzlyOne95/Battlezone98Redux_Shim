
undefined4 FUN_00672da0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_00417780(param_3,param_4);
  uVar1 = FUN_00417780(param_2,uVar1);
  uVar1 = FUN_00417780(param_1,uVar1);
  uVar1 = _Uninitialized_move<>(uVar1);
  puVar2 = (undefined4 *)FUN_0042ef30(&param_3,uVar1);
  return *puVar2;
}

