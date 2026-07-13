
undefined4 FUN_005053a0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  char cVar3;
  
  iVar1 = *param_1;
  cVar3 = FUN_0082d2e8(param_3,param_4);
  iVar2 = *param_1;
  *(char *)(iVar2 + -1) = *(char *)(iVar1 + -1) + cVar3;
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}

