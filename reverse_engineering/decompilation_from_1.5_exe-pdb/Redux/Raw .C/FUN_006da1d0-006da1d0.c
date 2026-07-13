
undefined4 FUN_006da1d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0042eee0(param_4);
  uVar1 = FUN_0042eee0(param_3,uVar1);
  uVar1 = FUN_0042eee0(param_2,uVar1);
  uVar1 = _Move<>(uVar1);
  FUN_006e8130(param_1,&param_4,uVar1);
  return param_1;
}

