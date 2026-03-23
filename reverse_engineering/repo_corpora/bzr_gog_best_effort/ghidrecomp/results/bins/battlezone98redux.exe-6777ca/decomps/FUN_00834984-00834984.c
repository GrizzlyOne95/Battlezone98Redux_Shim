
void FUN_00834984(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_0082ce9d(param_1,1,param_3);
  iVar1 = FUN_0082c9f5(param_1,0xffffffff);
  if (iVar1 == 0) {
    uVar2 = FUN_0082d490(param_1,0xffffffff,param_3);
    uVar2 = FUN_0082d4b1(param_1,uVar2);
    FUN_0082bc39(param_1,"invalid value (%s) at index %d in table for \'concat\'",uVar2);
  }
  FUN_0082b87b(param_2);
  return;
}

