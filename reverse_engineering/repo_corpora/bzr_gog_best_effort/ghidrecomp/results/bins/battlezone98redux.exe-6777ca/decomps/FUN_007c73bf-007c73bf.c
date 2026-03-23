
undefined4 FUN_007c73bf(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar2 = FUN_00684ce0(0);
  if (iVar2 == 0) {
    if (*(char *)(unaff_EBP + 0xc) == '\0') {
      FUN_00822ed0(1);
    }
  }
  else {
    FUN_006854b0();
    iVar2 = FUN_00685520();
    if (iVar2 == 0) {
      FUN_006854d0();
    }
  }
  if (*(char *)(unaff_EBP + 0xc) != '\0') {
    FUN_00822ed0(0x32);
  }
  if ((*(int *)(unaff_EBP + 8) == 0) || (cVar1 = FUN_007c7020(), cVar1 != '\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return uVar3;
}

