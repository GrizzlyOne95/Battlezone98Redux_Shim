
void FUN_006a1960(void)

{
  char cVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  FUN_0068f7b0();
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    for (local_c = 0; local_c < 0x10; local_c = local_c + 1) {
      iVar2 = local_c;
      FUN_005e0bc0(local_8,local_c);
      cVar1 = FUN_005e1310(iVar2);
      if (cVar1 == '\0') {
        iVar2 = local_c;
        FUN_005e0bc0(local_8,local_c);
        cVar1 = FUN_005e1350(iVar2);
        if (cVar1 == '\0') {
          FUN_006a9040(local_8,local_c,2);
        }
        else {
          FUN_006a9040(local_8,local_c,1);
        }
      }
      else {
        FUN_006a9040(local_8,local_c,4);
      }
    }
    FUN_0068fa20(local_8);
  }
  return;
}

