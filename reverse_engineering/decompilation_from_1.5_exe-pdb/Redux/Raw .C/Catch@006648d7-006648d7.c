
undefined * Catch_006648d7(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  
  uVar1 = (**(code **)(**(int **)(unaff_EBP + -0x4dc) + 4))();
  FUN_007d6a70("Failed to restore graphics configuration with error: %s\n",uVar1);
  *(undefined1 *)(unaff_EBP + -0x439) = 0;
  return &DAT_0066490e;
}

