
undefined4 __fastcall FUN_004dce20(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004cf880(*(undefined4 *)(param_1 + 0xb0));
  *(undefined4 *)(param_1 + 0xb0) = uVar1;
  uVar1 = FUN_004cf880(*(undefined4 *)(param_1 + 0xd0));
  *(undefined4 *)(param_1 + 0xd0) = uVar1;
  return 1;
}

