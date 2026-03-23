
void FUN_008300aa(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(byte *)(iVar1 + 0x15) < 2) {
    *(undefined1 *)(iVar1 + 0x15) = 2;
    *(undefined4 *)(iVar1 + 0x18) = 0;
    *(int *)(iVar1 + 0x20) = iVar1 + 0x1c;
    *(undefined4 *)(iVar1 + 0x24) = 0;
    *(undefined4 *)(iVar1 + 0x28) = 0;
    *(undefined4 *)(iVar1 + 0x2c) = 0;
  }
  while( true ) {
    if (*(char *)(iVar1 + 0x15) == '\x04') break;
    FUN_008304dc(param_1);
  }
  FUN_008302c4();
  while (*(char *)(iVar1 + 0x15) != '\0') {
    FUN_008304dc(param_1);
  }
  *(uint *)(iVar1 + 0x40) = (*(uint *)(iVar1 + 0x48) / 100) * *(int *)(iVar1 + 0x50);
  return;
}

