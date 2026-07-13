
int FUN_0083c410(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(*param_1 + 0xc) + param_2 * 4;
  if ((param_2 < 1) ||
     (iVar2 = iVar1 + -4, ((&DAT_00870638)[*(uint *)(iVar1 + -4) & 0x3f] & 0x80) == 0)) {
    iVar2 = iVar1;
  }
  return iVar2;
}

