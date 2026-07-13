
undefined4 FUN_00837254(undefined4 param_1)

{
  int iVar1;
  
  FUN_0082bbb2(param_1,2,5);
  FUN_0082d226(param_1,2);
  iVar1 = FUN_0082d08e(param_1,1);
  if (iVar1 == 0) {
    FUN_0082bc39(param_1,"\'setfenv\' cannot change environment of given object");
  }
  return 1;
}

