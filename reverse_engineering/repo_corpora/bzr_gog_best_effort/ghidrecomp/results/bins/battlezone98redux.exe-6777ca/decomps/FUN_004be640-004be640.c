
undefined4 FUN_004be640(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  uVar1 = FUN_00417780(*(undefined4 *)(unaff_EBP + 0x10),*(undefined4 *)(unaff_EBP + 0x14));
  puVar2 = (undefined4 *)FUN_004bf4e0(unaff_EBP + -0x1bc,*(undefined1 *)(unaff_EBP + -0x19),uVar1);
  **(undefined4 **)(unaff_EBP + 8) = *puVar2;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}

