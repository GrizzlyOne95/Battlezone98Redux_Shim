
void FUN_0075a0f0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_78 [28];
  undefined1 local_5c [28];
  undefined1 local_40 [28];
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = FUN_006b3750(local_40);
  uVar3 = FUN_006b3750(local_24);
  cVar1 = FUN_0075a090(uVar3,uVar2);
  if (cVar1 == '\0') {
    uVar2 = FUN_006b3750(local_78);
    uVar3 = FUN_006b3750(local_5c);
    cVar1 = operator!=<>(uVar3,uVar2);
    if (cVar1 == '\0') {
      FUN_006b36c0();
      FUN_006b36c0();
    }
  }
  FUN_0083e885();
  return;
}

