
void FUN_005cc5f0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 != 0) {
    if (param_2 == 0) {
      FUN_005cc2e0(iVar1,0,param_3);
    }
    else {
      iVar2 = FUN_00460fc0(param_2);
      if (iVar2 != 0) {
        FUN_005cc2e0(iVar1,iVar2,param_3);
      }
    }
  }
  return;
}

