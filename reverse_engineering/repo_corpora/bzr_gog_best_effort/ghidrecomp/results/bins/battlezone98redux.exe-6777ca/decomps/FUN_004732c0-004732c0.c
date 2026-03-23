
undefined4 __fastcall FUN_004732c0(int param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00417f60(0);
  FUN_00581eb0(param_1 + 0x37c);
  FUN_00581ed0(*(undefined4 *)(param_1 + 0x300));
  (**(code **)(*piVar1 + 8))();
  FUN_004723b0(0);
  *(undefined4 *)(param_1 + 0x300) = 0;
  return 0;
}

