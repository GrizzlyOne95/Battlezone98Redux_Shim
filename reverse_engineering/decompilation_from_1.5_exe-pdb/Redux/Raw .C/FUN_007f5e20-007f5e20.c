
undefined4 __fastcall FUN_007f5e20(undefined4 param_1)

{
  char cVar1;
  
  while( true ) {
    cVar1 = FUN_007f5ad0(param_1);
    if (cVar1 != '\0') {
      return 0;
    }
    cVar1 = Copy(param_1);
    if (cVar1 == '\0') break;
    cVar1 = FUN_007f5ad0();
    if (cVar1 == '\0') {
      FUN_007f6320();
    }
  }
  return 1;
}

