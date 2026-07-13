
void FUN_0083426a(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082d490(param_1,1);
  if (iVar1 == 6) {
    FUN_0082cdd2(param_1,1);
  }
  else {
    if (param_2 == 0) {
      iVar1 = FUN_0082ba1c(param_1,1);
    }
    else {
      iVar1 = FUN_0082c1fd(param_1,1);
    }
    if (iVar1 < 0) {
      FUN_0082b8e4(param_1,1,"level must be non-negative");
    }
    iVar2 = FUN_0082e171(param_1,iVar1,local_6c);
    if (iVar2 == 0) {
      FUN_0082b8e4(param_1,1,"invalid level");
    }
    FUN_0082e08b(param_1,&DAT_0087d188,local_6c);
    iVar2 = FUN_0082d490(param_1,0xffffffff);
    if (iVar2 == 0) {
      FUN_0082bc39(param_1,"no function environment for tail call at level %d",iVar1);
    }
  }
  FUN_0083e885();
  return;
}

