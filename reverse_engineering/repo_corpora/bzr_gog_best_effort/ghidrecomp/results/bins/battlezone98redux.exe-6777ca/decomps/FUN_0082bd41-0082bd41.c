
bool FUN_0082bd41(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = FUN_0082c882(param_1,param_2);
  bVar2 = false;
  if (iVar1 != 0) {
    FUN_0082cd77(param_1,param_3);
    FUN_0082ce65(param_1,0xfffffffe);
    iVar1 = FUN_0082d490(param_1,0xffffffff);
    bVar2 = iVar1 != 0;
    if (bVar2) {
      FUN_0082cf99(param_1,0xfffffffe);
    }
    else {
      FUN_0082d226(param_1,0xfffffffd);
    }
  }
  return bVar2;
}

