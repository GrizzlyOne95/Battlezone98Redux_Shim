
void FUN_0080a5c6(void)

{
  char cVar1;
  undefined4 *puVar2;
  int unaff_EBP;
  
  cVar1 = FUN_00420f10(unaff_EBP + 0xc);
  if (cVar1 != '\0') {
    *(undefined4 *)(unaff_EBP + -0x24) = *(undefined4 *)(unaff_EBP + 8);
    puVar2 = (undefined4 *)FUN_0044f2c0();
    FUN_0080a690(*puVar2);
    FUN_0080a5be();
    return;
  }
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}

