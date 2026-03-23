
undefined4 FUN_0058ac66(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int unaff_EBP;
  int iVar4;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  uVar3 = *(undefined4 *)(unaff_EBP + 0x10);
  uVar2 = FUN_00417780(*(undefined4 *)(unaff_EBP + 0xc),uVar3);
  FUN_00450660(unaff_EBP + -0x24,uVar2,uVar3);
  *(undefined4 *)(unaff_EBP + -0x2c) = *(undefined4 *)(unaff_EBP + -0x24);
  uVar3 = FUN_0042da80();
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    *(undefined4 *)(unaff_EBP + -100) = *(undefined4 *)(unaff_EBP + -0x2c);
    *(undefined4 *)(unaff_EBP + -0x68) = *(undefined4 *)(unaff_EBP + -0x24);
    *(undefined4 *)(unaff_EBP + -0x6c) = *(undefined4 *)(unaff_EBP + -0x20);
    FUN_00450390(*(undefined4 *)(unaff_EBP + -0x6c),*(undefined4 *)(unaff_EBP + -0x68),
                 *(undefined4 *)(unaff_EBP + -100));
  }
  FUN_00450230(*(undefined4 *)(unaff_EBP + -0x24),*(undefined4 *)(unaff_EBP + -0x20),
               *(undefined4 *)(unaff_EBP + -0x28));
  FUN_0058ada0();
  *(undefined1 *)(unaff_EBP + -0x15) = 1;
  *(undefined4 *)(unaff_EBP + -0x70) = *(undefined4 *)(unaff_EBP + -0x24);
  iVar4 = unaff_EBP + -0x15;
  uVar3 = FUN_0044ec90(unaff_EBP + -0x80,*(undefined4 *)(unaff_EBP + -0x70));
  FUN_0042c980(uVar3,iVar4);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return *(undefined4 *)(unaff_EBP + 8);
}

