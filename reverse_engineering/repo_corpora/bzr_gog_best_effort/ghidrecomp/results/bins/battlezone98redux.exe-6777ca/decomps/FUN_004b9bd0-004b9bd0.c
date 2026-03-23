
void __fastcall FUN_004b9bd0(int param_1)

{
  int *piVar1;
  
  if ((*(char *)(param_1 + 0x68) != '\x01') && (*(char *)(param_1 + 0x68) != '\x02')) {
    *(undefined1 *)(param_1 + 0x68) = 1;
    *(int *)(param_1 + 100) = DAT_008e80b4;
    DAT_008e80b4 = DAT_008e80b4 + 1;
    piVar1 = (int *)FUN_004bad10(param_1 + 100);
    *piVar1 = param_1;
  }
  return;
}

