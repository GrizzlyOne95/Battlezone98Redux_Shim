
int FUN_0083347b(int param_1,byte param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00830f2e(param_1,param_3);
  if (*(int *)(iVar1 + 8) == 0) {
    *(byte *)(param_1 + 6) = *(byte *)(param_1 + 6) | '\x01' << (param_2 & 0x1f);
    iVar1 = 0;
  }
  return iVar1;
}

