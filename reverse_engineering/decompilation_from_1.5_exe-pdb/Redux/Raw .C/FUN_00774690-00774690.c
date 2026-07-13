
int __thiscall
FUN_00774690(int param_1,uint param_2,uint param_3,int param_4,uint param_5,uint param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 <= *(uint *)(param_1 + 0x10)) {
    uVar1 = FUN_004170c0();
    if (param_5 <= uVar1) goto LAB_007746b9;
  }
  FUN_00417440();
LAB_007746b9:
  if (*(int *)(param_1 + 0x10) - param_2 < param_3) {
    param_3 = *(int *)(param_1 + 0x10) - param_2;
  }
  iVar2 = FUN_004170c0();
  if (iVar2 - param_5 < param_6) {
    param_6 = iVar2 - param_5;
  }
  if (-param_6 - 1 <= *(int *)(param_1 + 0x10) - param_3) {
    FUN_00417420();
  }
  iVar2 = (*(int *)(param_1 + 0x10) - param_3) - param_2;
  uVar1 = (*(int *)(param_1 + 0x10) + param_6) - param_3;
  if (*(uint *)(param_1 + 0x10) < uVar1) {
    FID_conflict__Grow(uVar1,0);
  }
  if (param_1 == param_4) {
    if (param_3 < param_6) {
      if (param_2 < param_5) {
        if (param_5 < param_2 + param_3) {
          iVar3 = Myptr(param_3);
          iVar3 = Myptr(iVar3 + param_5 * 2);
          move(iVar3 + param_2 * 2);
          iVar2 = Myptr(iVar2);
          iVar2 = Myptr(iVar2 + param_2 * 2 + param_3 * 2);
          move(iVar2 + param_2 * 2 + param_6 * 2);
          iVar2 = Myptr(param_6 - param_3);
          iVar2 = Myptr(iVar2 + param_5 * 2 + param_6 * 2);
          move(iVar2 + param_2 * 2 + param_3 * 2);
        }
        else {
          iVar2 = Myptr(iVar2);
          iVar2 = Myptr(iVar2 + param_2 * 2 + param_3 * 2);
          move(iVar2 + param_2 * 2 + param_6 * 2);
          iVar2 = Myptr(param_6);
          iVar2 = Myptr(iVar2 + ((param_5 + param_6) - param_3) * 2);
          move(iVar2 + param_2 * 2);
        }
      }
      else {
        iVar2 = Myptr(iVar2);
        iVar2 = Myptr(iVar2 + param_2 * 2 + param_3 * 2);
        move(iVar2 + param_2 * 2 + param_6 * 2);
        iVar2 = Myptr(param_6);
        iVar2 = Myptr(iVar2 + param_5 * 2);
        move(iVar2 + param_2 * 2);
      }
    }
    else {
      iVar3 = Myptr(param_6);
      iVar3 = Myptr(iVar3 + param_5 * 2);
      move(iVar3 + param_2 * 2);
      iVar2 = Myptr(iVar2);
      iVar2 = Myptr(iVar2 + param_2 * 2 + param_3 * 2);
      move(iVar2 + param_2 * 2 + param_6 * 2);
    }
  }
  else {
    iVar2 = Myptr(iVar2);
    iVar2 = Myptr(iVar2 + param_2 * 2 + param_3 * 2);
    move(iVar2 + param_2 * 2 + param_6 * 2);
    iVar2 = Myptr(param_6);
    iVar2 = Myptr(iVar2 + param_5 * 2);
    copy(iVar2 + param_2 * 2);
  }
  FID_conflict__Eos(uVar1);
  return param_1;
}

