
undefined4 __fastcall FUN_007f4b70(undefined4 param_1)

{
  char cVar1;
  
  while( true ) {
    cVar1 = FUN_007f4a70(param_1);
    if (cVar1 != '\0') {
      return 0;
    }
    cVar1 = Copy(param_1);
    if (cVar1 == '\0') break;
    cVar1 = FUN_007f4a70();
    if (cVar1 == '\0') {
      FUN_007f5a50();
    }
  }
  return 1;
}

