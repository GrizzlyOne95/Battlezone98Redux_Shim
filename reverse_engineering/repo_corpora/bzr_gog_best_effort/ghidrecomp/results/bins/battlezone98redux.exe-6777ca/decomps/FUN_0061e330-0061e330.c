
int FUN_0061e330(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_var;
  
  iVar1 = isdigit((int)*param_2);
  if (iVar1 == 0) {
    if (param_1 == -1) {
      iVar1 = -1;
    }
    else if (*(int *)(&DAT_0091ff7c + param_1 * 0x74) == 0) {
      FUN_007d6b70("%s line %d: no discrete input channel named \"%s\".",DAT_0091a454,DAT_0091fef8,
                   param_2,extraout_var);
      iVar1 = -1;
    }
    else {
      for (iVar1 = 0; iVar1 < *(int *)(&DAT_0091ff6c + param_1 * 0x74); iVar1 = iVar1 + 1) {
        if ((*(int *)(*(int *)(&DAT_0091ff7c + param_1 * 0x74) + iVar1 * 4) != 0) &&
           (iVar2 = _stricmp(*(char **)(*(int *)(&DAT_0091ff7c + param_1 * 0x74) + iVar1 * 4),
                             param_2), iVar2 == 0)) {
          return iVar1;
        }
      }
      FUN_00621820(0x6f,param_2,&DAT_0091ff1c + param_1 * 0x74);
      iVar1 = -1;
    }
  }
  else {
    iVar1 = atoi(param_2);
  }
  return iVar1;
}

