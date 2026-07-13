
int __thiscall FUN_008287d0(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;
  
  if ((param_2 != 0) && (-1 < *param_3)) {
    while (*param_3 < DAT_009468c0) {
      iVar1 = FUN_008260a0(*param_3 * 0x20 + DAT_009468cc,param_2,param_1);
      if (iVar1 != 0) {
        iVar1 = *param_3 * 0x20 + DAT_009468cc;
        *param_3 = *param_3 + 1;
        return iVar1;
      }
      *param_3 = *param_3 + 1;
    }
  }
  return 0;
}

