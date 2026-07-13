
int FUN_004d9ca0(int param_1,char *param_2)

{
  int iVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  
  if ((param_1 != 0) && (iVar1 = _strnicmp((char *)(param_1 + 0xd),param_2,3), iVar1 != 0)) {
    uVar2 = extraout_var;
    for (param_1 = *(int *)(param_1 + 0x80); param_1 != 0; param_1 = *(int *)(param_1 + 0x7c)) {
      iVar1 = FUN_004d9ca0(param_1,param_2,uVar2);
      if (iVar1 != 0) {
        return iVar1;
      }
      uVar2 = 0;
    }
    param_1 = 0;
  }
  return param_1;
}

