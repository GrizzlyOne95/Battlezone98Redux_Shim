
void FUN_00834f76(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_218;
  undefined1 local_214 [524];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_0082ba59(param_1,1,&local_218);
  iVar2 = FUN_0082ba1c(param_1,2);
  FUN_0082b98a(param_1,local_214);
  for (; 0 < iVar2; iVar2 = iVar2 + -1) {
    FUN_0082b81b(local_214,uVar1,local_218);
  }
  FUN_0082c2cb(local_214);
  FUN_0083e885();
  return;
}

