
int __thiscall FUN_007744d0(int param_1,uint param_2,uint param_3,int param_4,uint param_5)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  cVar1 = FID_conflict__Inside(param_4);
  if (cVar1 == '\0') {
    if (*(uint *)(param_1 + 0x10) < param_2) {
      FUN_00417440();
    }
    if (*(int *)(param_1 + 0x10) - param_2 < param_3) {
      param_3 = *(int *)(param_1 + 0x10) - param_2;
    }
    if (-param_5 - 1 <= *(int *)(param_1 + 0x10) - param_3) {
      FUN_00417420();
    }
    iVar2 = (*(int *)(param_1 + 0x10) - param_3) - param_2;
    if (param_5 < param_3) {
      iVar3 = Myptr(iVar2);
      iVar3 = Myptr(iVar3 + param_2 * 2 + param_3 * 2);
      move(iVar3 + param_2 * 2 + param_5 * 2);
    }
    if ((param_5 != 0) || (param_3 != 0)) {
      iVar3 = (*(int *)(param_1 + 0x10) + param_5) - param_3;
      cVar1 = FID_conflict__Grow(iVar3,0);
      if (cVar1 != '\0') {
        if (param_3 < param_5) {
          iVar2 = Myptr(iVar2);
          iVar2 = Myptr(iVar2 + param_2 * 2 + param_3 * 2);
          move(iVar2 + param_2 * 2 + param_5 * 2);
        }
        iVar2 = Myptr(param_4,param_5);
        copy(iVar2 + param_2 * 2);
        FID_conflict__Eos(iVar3);
      }
    }
  }
  else {
    iVar2 = Myptr(param_5);
    param_1 = FUN_00774690(param_2,param_3,param_1,param_4 - iVar2 >> 1,param_5);
  }
  return param_1;
}

