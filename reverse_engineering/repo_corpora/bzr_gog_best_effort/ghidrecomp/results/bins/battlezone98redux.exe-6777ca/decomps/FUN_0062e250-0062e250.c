
int __thiscall FUN_0062e250(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  
  if ((param_2 != 0) && (*(int *)(param_2 + 0x84) != param_3)) {
    for (param_2 = *(int *)(param_2 + 0x80); param_2 != 0; param_2 = *(int *)(param_2 + 0x7c)) {
      iVar1 = FUN_0062e250(param_2,param_3,param_1);
      if (iVar1 != 0) {
        return iVar1;
      }
      param_1 = 0;
    }
    param_2 = 0;
  }
  return param_2;
}

