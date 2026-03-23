
void FUN_004fec66(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  int iVar2;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + 0xc) != 0) {
    uVar1 = Myptr(*(undefined4 *)(unaff_EBP + 0xc));
    copy(*(undefined4 *)(unaff_EBP + -0x20),uVar1);
  }
  FID_conflict__Tidy(1,0);
  iVar2 = unaff_EBP + -0x20;
  uVar1 = *(undefined4 *)(unaff_EBP + -0x18);
  Getal(unaff_EBP + -0x13);
  construct<>(uVar1,iVar2);
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 0x14) = *(undefined4 *)(unaff_EBP + -0x1c);
  FID_conflict__Eos(*(undefined4 *)(unaff_EBP + 0xc));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

