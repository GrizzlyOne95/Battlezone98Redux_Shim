
undefined4 FUN_0070bb20(void)

{
  char cVar1;
  undefined4 uVar2;
  
  while( true ) {
    cVar1 = FUN_00420f10(&stack0x00000008);
    if (cVar1 == '\0') {
      return 1;
    }
    uVar2 = FUN_004237d0();
    uVar2 = FUN_004237d0(uVar2);
    cVar1 = operator==<>(uVar2);
    if (cVar1 == '\0') break;
    FUN_004238b0();
    FUN_004238b0();
  }
  return 0;
}

