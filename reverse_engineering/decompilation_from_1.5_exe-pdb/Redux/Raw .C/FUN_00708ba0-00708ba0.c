
undefined4 FUN_00708ba0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0042eee0(param_3,param_4);
  uVar1 = FUN_0042eee0(param_2,uVar1);
  uVar1 = _Find_unchecked<>(uVar1);
  FUN_006e8130(param_1,&param_2,uVar1);
  return param_1;
}

