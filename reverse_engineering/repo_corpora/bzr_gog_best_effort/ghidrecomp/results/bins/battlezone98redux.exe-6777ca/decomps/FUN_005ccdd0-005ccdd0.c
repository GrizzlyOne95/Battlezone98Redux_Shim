
void FUN_005ccdd0(undefined4 param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = (int *)FUN_00462630(param_1);
  if (piVar1 != (int *)0x0) {
    uVar2 = (**(code **)(piVar1[6] + 0x30))();
    iVar3 = FUN_00417e20(uVar2);
    if (iVar3 != 0) {
      (**(code **)(*piVar1 + 0x7c))();
    }
  }
  return;
}

