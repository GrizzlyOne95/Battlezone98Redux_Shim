
undefined4 FUN_0083bc1d(undefined4 *param_1)

{
  undefined4 uVar1;
  int local_8;
  
  FUN_0083b798(param_1,&local_8,4);
  if (local_8 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_0082ecad(*param_1,param_1[2],local_8);
    FUN_0083b798(param_1,uVar1,local_8);
    uVar1 = FUN_008309f4(*param_1,uVar1,local_8 + -1);
  }
  return uVar1;
}

