
int FUN_0083c3e8(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = -1;
  iVar2 = (*(uint *)(*(int *)(*param_1 + 0xc) + param_2 * 4) >> 0xe) - 0x1ffff;
  if (iVar2 != -1) {
    iVar1 = param_2 + 1 + iVar2;
  }
  return iVar1;
}

