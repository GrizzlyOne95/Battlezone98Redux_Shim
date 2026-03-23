
void Catch_All_004175df(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  *(BADSPACEBASE **)(unaff_EBP + -0x10) = register0x00000010;
  *(undefined4 *)(unaff_EBP + -0x1c) = *(undefined4 *)(unaff_EBP + 8);
  *(undefined1 *)(unaff_EBP + -4) = 2;
  uVar1 = Getal(unaff_EBP + -0x12);
  *(undefined4 *)(unaff_EBP + -0x2c) = uVar1;
  uVar1 = allocate(*(int *)(unaff_EBP + -0x1c) + 1);
  *(undefined4 *)(unaff_EBP + -0x30) = uVar1;
  *(undefined4 *)(unaff_EBP + -0x20) = *(undefined4 *)(unaff_EBP + -0x30);
  FUN_00417630();
  return;
}

