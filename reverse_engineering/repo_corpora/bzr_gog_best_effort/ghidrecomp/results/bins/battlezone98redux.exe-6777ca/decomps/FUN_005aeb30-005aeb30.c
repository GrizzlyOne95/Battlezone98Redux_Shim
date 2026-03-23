
undefined4 __thiscall FUN_005aeb30(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar2 = FUN_0046fc10();
  if (iVar2 != 0) {
    if (iVar2 == 1) {
      if (param_2 == param_1) {
        return 0;
      }
      iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
      if (*(int *)(iVar2 + 0x14) == 0x53435250) {
        return 0;
      }
      iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
      if (*(int *)(iVar2 + 0x14) == 0x4745495a) {
        if (*(char *)(param_2 + 0x239) != '\0') {
          return 0;
        }
        return 3;
      }
      iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
      if (*(int *)(iVar2 + 0x1c) == 3) {
        return 3;
      }
      iVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
      if ((iVar2 == 0) && (cVar1 = FUN_0046fbf0(), cVar1 == '\0')) {
        return 0;
      }
      cVar1 = FUN_004db5b0(param_2);
      if (cVar1 != '\0') {
        return 0;
      }
      iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
      if ((*(int *)(iVar2 + 0x1c) != 1) &&
         (iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))(), *(int *)(iVar2 + 0x1c) != 6)) {
        iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
        if (*(int *)(iVar2 + 0x1c) == 5) {
          return 0;
        }
        return 3;
      }
      return 5;
    }
    if (iVar2 != 9) {
      return 0;
    }
  }
  return 0;
}

