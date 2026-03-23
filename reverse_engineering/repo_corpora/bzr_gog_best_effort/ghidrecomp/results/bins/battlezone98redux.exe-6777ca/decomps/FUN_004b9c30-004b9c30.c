
void __fastcall FUN_004b9c30(int param_1)

{
  int *piVar1;
  
  *(undefined1 *)(param_1 + 0x68) = 2;
  *(int *)(param_1 + 100) = DAT_008e80b4;
  DAT_008e80b4 = DAT_008e80b4 + 1;
  piVar1 = (int *)FUN_004bad10(param_1 + 100);
  *piVar1 = param_1;
  return;
}

