
void FUN_005ce330(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = FUN_00460fc0(param_1);
  if (iVar2 == 0) {
    FUN_007d6a70("Path %s not found",param_1);
  }
  else {
    cVar1 = FUN_005c8220(local_14,param_1,0);
    if (cVar1 != '\0') {
      FUN_005ce280(local_14,param_2);
    }
  }
  FUN_0083e885();
  return;
}

