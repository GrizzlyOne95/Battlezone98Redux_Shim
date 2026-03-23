
undefined4 FUN_00503bb0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0082ba1c(param_1,1);
  uVar2 = FUN_0082c1fd(param_1,2,0x80000000,uVar1);
  uVar3 = FUN_0082c1fd(param_1,3,0x80000000,uVar1,uVar2);
  FUN_004f6ae0(uVar1,uVar2,uVar3);
  return 0;
}

