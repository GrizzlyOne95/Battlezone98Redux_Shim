
undefined4 __fastcall FUN_00438080(int param_1)

{
  undefined4 *puVar1;
  
  FUN_0043aaa0(*(undefined4 *)(param_1 + 0x38));
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  puVar1 = (undefined4 *)FUN_00438b60();
  operator_delete((void *)*puVar1);
  FUN_00438bb0();
  *(undefined1 *)(param_1 + 0x34) = 0;
  return 0;
}

