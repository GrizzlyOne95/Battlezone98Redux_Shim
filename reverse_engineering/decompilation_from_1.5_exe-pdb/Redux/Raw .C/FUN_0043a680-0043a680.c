
undefined4 FUN_0043a680(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = FUN_0043c880(param_1,param_2), iVar1 == 0)) {
    FUN_007d6830("Can\'t set DSound primary buffer rate to %d.",param_2);
    return 0;
  }
  return 1;
}

