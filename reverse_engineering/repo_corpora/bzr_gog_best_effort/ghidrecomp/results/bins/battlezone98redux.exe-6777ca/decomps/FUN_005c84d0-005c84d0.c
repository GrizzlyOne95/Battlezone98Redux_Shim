
undefined4 FUN_005c84d0(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_1 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_00462630(*param_1);
    if (iVar2 == 0) {
      *param_1 = 0;
      uVar1 = 0;
    }
    else {
      iVar2 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
      if ((*(int *)(iVar2 + 0x84) == 1) || (*(int *)(iVar2 + 0x84) == 6)) {
        iVar2 = FUN_0045bdf0();
        if (iVar2 == 0) {
          *param_1 = 0;
          uVar1 = 0;
        }
        else {
          uVar1 = 1;
        }
      }
      else {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

