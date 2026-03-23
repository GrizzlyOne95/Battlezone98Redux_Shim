
undefined4 FUN_006a3ad0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = (**(code **)(*(int *)(param_1 + 0x18) + 0x30))();
  iVar3 = FUN_00417e20(uVar2);
  if (iVar3 == 0) {
    uVar2 = 0;
  }
  else {
    iVar3 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
    cVar1 = FUN_006a07e0(*(undefined4 *)(iVar3 + 0x14));
    if (cVar1 == '\0') {
      iVar3 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
      if (*(int *)(iVar3 + 0x14) == 0x54555252) {
        uVar2 = 0;
      }
      else {
        iVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 0x2c))();
        if (iVar3 == 0) {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

