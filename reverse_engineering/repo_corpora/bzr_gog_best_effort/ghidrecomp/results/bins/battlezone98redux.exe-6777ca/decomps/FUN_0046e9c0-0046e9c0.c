
undefined4 *
FUN_0046e9c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_0042eee0(param_3,param_4);
  uVar1 = FUN_0042eee0(param_2,uVar1);
  uVar1 = _Find_unchecked<>(uVar1);
  puVar2 = (undefined4 *)FUN_0046ea70(&param_2,uVar1);
  *param_1 = *puVar2;
  return param_1;
}

