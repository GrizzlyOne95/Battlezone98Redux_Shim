
int FUN_004d8e00(void *param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = param_2 - (int)param_1 >> 2;
  memmove((void *)(param_3 + iVar1 * -4),param_1,iVar1 << 2);
  return param_3 + iVar1 * -4;
}

