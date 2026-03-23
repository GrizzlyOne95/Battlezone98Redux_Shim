
undefined * Catch_00435e0c(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x9c) + 4))();
  *(undefined4 *)(unaff_EBP + -0x98) = uVar1;
  FUN_007d6a70("Could not load GL Renderer: %s\n",*(undefined4 *)(unaff_EBP + -0x98));
  return &DAT_00435e59;
}

