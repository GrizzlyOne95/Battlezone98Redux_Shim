
undefined4 FUN_006cd8b0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_10 [8];
  int local_8;
  
  uVar2 = FUN_006cd9f0(local_10);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    while( true ) {
      FUN_0042da60();
      local_8 = get();
      if (local_8 == 0) break;
      cVar1 = FUN_006ae4f0();
      if (cVar1 == '\0') {
        return 1;
      }
      FUN_0042da60();
      FUN_006c8fb0();
      FUN_006c9000(local_8);
    }
    FUN_006cdcc0(param_1);
  }
  return 0;
}

