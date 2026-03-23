
undefined4 FUN_00697700(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00417f90();
  if (iVar1 == 0) {
    iVar1 = (*(code *)**(undefined4 **)(*param_1 + 0x18))();
    if (*(int *)(iVar1 + 0x14) == 0x57494e47) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

