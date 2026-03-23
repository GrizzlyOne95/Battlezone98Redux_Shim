
undefined4 FUN_0082d9b5(int param_1,uint param_2,int param_3)

{
  int iVar1;
  bool bVar2;
  
  if (param_3 == 0) {
    if (param_2 != 0) {
      return 0;
    }
  }
  else if (param_3 == 2) {
    if ((int)(uint)*(byte *)(param_1 + 0x4b) <= (int)param_2) {
      return 0;
    }
  }
  else if (param_3 == 3) {
    if ((param_2 & 0x100) == 0) {
      bVar2 = SBORROW4(param_2,(uint)*(byte *)(param_1 + 0x4b));
      iVar1 = param_2 - *(byte *)(param_1 + 0x4b);
    }
    else {
      bVar2 = SBORROW4(param_2 & 0xfffffeff,*(int *)(param_1 + 0x28));
      iVar1 = (param_2 & 0xfffffeff) - *(int *)(param_1 + 0x28);
    }
    if (bVar2 == iVar1 < 0) {
      return 0;
    }
  }
  return 1;
}

