
void FUN_006c9e70(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_14 [8];
  undefined4 local_c;
  
  cVar1 = FUN_0041fc90();
  if (cVar1 == '\0') {
    FUN_006b2a70(local_14);
    while (cVar1 = FUN_0041fc90(), cVar1 == '\0') {
      uVar2 = FUN_005111d0(0);
      cVar1 = FUN_006b2ad0(local_14,uVar2);
      if (cVar1 != '\0') {
        return;
      }
      iVar3 = FUN_005111d0(0);
      local_c = *(undefined4 *)(iVar3 + 8);
      FUN_006d8a70(local_c);
      FUN_006ce9d0(local_c);
    }
  }
  return;
}

