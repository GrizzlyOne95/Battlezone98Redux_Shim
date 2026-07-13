
undefined1 FUN_006d53e0(void)

{
  int iVar1;
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  int *local_8;
  
  FUN_006ce130(local_10);
  iVar1 = get();
  if (*local_8 != iVar1) {
    FUN_006ce110(local_14);
    iVar1 = get();
    if (*local_8 != iVar1) {
      return 0;
    }
  }
  return 1;
}

