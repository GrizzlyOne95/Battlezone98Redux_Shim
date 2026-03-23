
undefined4 FUN_005c8560(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
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
      iVar3 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
      if ((*(int *)(iVar3 + 0x84) == 1) || (*(int *)(iVar3 + 0x84) == 6)) {
        iVar3 = FUN_0045bdf0();
        if (iVar3 == 0) {
          *param_1 = 0;
          uVar1 = 0;
        }
        else if (*(int *)(iVar2 + 0xec) == 0) {
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

