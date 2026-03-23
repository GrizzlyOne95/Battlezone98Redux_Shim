
undefined4 FUN_00464140(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462370();
  if (iVar1 == param_1) {
    iVar1 = FUN_00462590();
    if ((iVar1 == param_1) && (iVar1 = FUN_0045bba0(), iVar1 != -1)) {
      return 1;
    }
    iVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
    uVar2 = *(undefined4 *)(iVar1 + 0x140);
    iVar1 = (*(code *)**(undefined4 **)(param_2 + 0x18))(uVar2);
    iVar1 = FUN_005e0f90(*(undefined4 *)(iVar1 + 0x13c),uVar2);
    if (iVar1 == -1) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

