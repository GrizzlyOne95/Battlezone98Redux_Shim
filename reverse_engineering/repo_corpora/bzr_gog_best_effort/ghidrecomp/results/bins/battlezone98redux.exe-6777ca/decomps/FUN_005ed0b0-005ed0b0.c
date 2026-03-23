
undefined4 __thiscall FUN_005ed0b0(int *param_1,int *param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (param_2 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    iVar3 = (**(code **)param_2[6])();
    iVar5 = *(int *)(iVar3 + 0x14);
    iVar3 = *(int *)(iVar3 + 0x1c);
    iVar4 = FUN_0046fc10();
    if (iVar4 == 1) {
      if (param_2 == param_1) {
        uVar2 = 0;
      }
      else if (iVar5 == 0x53435250) {
        uVar2 = 0;
      }
      else if (iVar5 == 0x4745495a) {
        uVar2 = 0;
      }
      else if (iVar3 == 3) {
        uVar2 = 3;
      }
      else if ((iVar3 == 2) || (iVar3 == 5)) {
        if ((param_1[0xc0] == 0) && (iVar5 = (**(code **)(*param_2 + 0x28))(), iVar5 != 0)) {
          return 7;
        }
        uVar2 = 0;
      }
      else {
        if ((param_1[0xc0] == 0) &&
           (((iVar3 == 6 || (iVar3 == 1)) && (iVar5 = FUN_0045bdf0(), iVar5 == 0)))) {
          return 7;
        }
        cVar1 = FUN_004db510(param_2);
        if (cVar1 == '\0') {
          uVar2 = 0;
        }
        else {
          uVar2 = 5;
        }
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

