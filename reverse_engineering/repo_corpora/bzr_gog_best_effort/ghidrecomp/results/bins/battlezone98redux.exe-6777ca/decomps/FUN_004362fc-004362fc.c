
void FUN_004362fc(void)

{
  char cVar1;
  undefined4 uVar2;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  cVar1 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x68) + 0xc) + 0x144))();
  if (cVar1 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x98) = 1;
  }
  else {
    *(undefined4 *)(unaff_EBP + -0x98) = 0;
  }
  *(undefined1 *)(*(int *)(unaff_EBP + -0x68) + 0x54) = *(undefined1 *)(unaff_EBP + -0x98);
  uVar2 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x68) + 0xc) + 0x10))();
  *(undefined4 *)(*(int *)(unaff_EBP + -0x68) + 0x50) = uVar2;
  uVar2 = (**(code **)(**(int **)(*(int *)(unaff_EBP + -0x68) + 0xc) + 0xc))();
  *(undefined4 *)(*(int *)(unaff_EBP + -0x68) + 0x4c) = uVar2;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

