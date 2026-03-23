
undefined4 FUN_006d827d(void)

{
  undefined1 *puVar1;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  puVar1 = (undefined1 *)FUN_00425000(*(undefined4 *)(unaff_EBP + -0x1c));
  *puVar1 = 1;
  puVar1 = (undefined1 *)FUN_004242d0(*(undefined4 *)(unaff_EBP + -0x1c));
  *puVar1 = 1;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + -0x1c);
}

