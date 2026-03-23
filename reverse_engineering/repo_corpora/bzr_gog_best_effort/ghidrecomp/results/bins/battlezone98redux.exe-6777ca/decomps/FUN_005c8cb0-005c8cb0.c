
void FUN_005c8cb0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = FUN_00462630(param_1);
  if ((iVar2 != 0) && (cVar1 = FUN_005c8220(local_14,param_2,param_3), cVar1 != '\0')) {
    FUN_005873a0(local_14);
  }
  FUN_0083e885();
  return;
}

