
void FUN_0083574a(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 8);
  iVar2 = FUN_0082d490(uVar1,3);
  if (2 < iVar2) {
    if (iVar2 < 5) {
      FUN_008356a9(param_1,param_2,param_3,param_4);
      return;
    }
    if (iVar2 == 5) {
      FUN_00836056(param_1,0,param_3,param_4);
      FUN_0082c8d1(uVar1,3);
    }
    else if (iVar2 == 6) {
      FUN_0082cdd2(uVar1,3);
      uVar3 = FUN_0083600d(param_1,param_3,param_4);
      FUN_0082c585(uVar1,uVar3,1);
    }
  }
  iVar2 = FUN_0082d2e8(uVar1,0xffffffff);
  if (iVar2 == 0) {
    FUN_0082d226(uVar1,0xfffffffe);
    FUN_0082cd08(uVar1,param_3,param_4 - param_3);
  }
  else {
    iVar2 = FUN_0082c9f5(uVar1,0xffffffff);
    if (iVar2 == 0) {
      uVar3 = FUN_0082d490(uVar1,0xffffffff);
      uVar3 = FUN_0082d4b1(uVar1,uVar3);
      FUN_0082bc39(uVar1,"invalid replacement value (a %s)",uVar3);
    }
  }
  FUN_0082b87b(param_2);
  return;
}

