
int __thiscall FUN_00705a80(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)_Min_value<>(param_1 + 0x18,&stack0x00000008);
  iVar1 = *piVar2;
  FUN_006da2a0(param_2,param_2 + iVar1,param_1 + 0x4c + *(int *)(param_1 + 0x1c));
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + iVar1;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) - iVar1;
  return iVar1;
}

