
void FUN_00834844(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_21c;
  undefined4 local_218;
  undefined1 local_214 [524];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_218 = FUN_0082c225(param_1,2,&DAT_008a1ad8,&local_21c);
  FUN_0082bbb2(param_1,1,5);
  iVar1 = FUN_0082c1fd(param_1,3,1);
  iVar2 = FUN_0082d490(param_1,4);
  if (iVar2 < 1) {
    iVar2 = FUN_0082cb3b(param_1,1);
  }
  else {
    iVar2 = FUN_0082ba1c(param_1,4);
  }
  FUN_0082b98a(param_1,local_214);
  for (; iVar1 < iVar2; iVar1 = iVar1 + 1) {
    FUN_00834984(param_1,local_214,iVar1);
    FUN_0082b81b(local_214,local_218,local_21c);
  }
  if (iVar1 == iVar2) {
    FUN_00834984(param_1,local_214,iVar1);
  }
  FUN_0082c2cb(local_214);
  FUN_0083e885();
  return;
}

