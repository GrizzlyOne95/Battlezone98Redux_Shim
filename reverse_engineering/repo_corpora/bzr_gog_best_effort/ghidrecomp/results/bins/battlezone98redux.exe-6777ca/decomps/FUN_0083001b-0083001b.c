
void FUN_0083001b(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(char *)(iVar1 + 0x15) == '\x01') {
    FUN_00830437(iVar1,param_3);
    return;
  }
  *(byte *)(param_2 + 5) = *(byte *)(iVar1 + 0x14) & 3 | *(byte *)(param_2 + 5) & 0xf8;
  return;
}

