
undefined4 FUN_008003d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_30 [16];
  undefined1 local_20 [12];
  undefined1 local_14 [16];
  
  uVar1 = FUN_007e1640(param_2,param_3,param_4);
  _Callable_base<>(uVar1);
  puVar3 = local_14;
  uVar1 = param_4;
  uVar2 = FUN_007e31c0(param_2,puVar3,param_4);
  FUN_00800560(local_20,uVar2,puVar3,uVar1);
  puVar3 = local_20;
  uVar1 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_00800590(local_30,uVar1,puVar3,param_4);
  FUN_007fe370(local_30);
  return param_1;
}

