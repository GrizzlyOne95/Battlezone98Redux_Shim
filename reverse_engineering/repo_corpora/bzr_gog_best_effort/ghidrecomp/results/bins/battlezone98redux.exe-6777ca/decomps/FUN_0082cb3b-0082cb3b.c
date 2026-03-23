
undefined4 FUN_0082cb3b(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  iVar3 = piVar1[2];
  if (iVar3 == 3) {
    iVar3 = FUN_00833372(param_1,piVar1);
    if (iVar3 != 0) goto LAB_0082cb71;
  }
  else {
    if (iVar3 == 4) {
LAB_0082cb71:
      return *(undefined4 *)(*piVar1 + 0xc);
    }
    if (iVar3 == 5) {
      uVar2 = FUN_00830e70(*piVar1);
      return uVar2;
    }
    if (iVar3 == 7) {
      return *(undefined4 *)(*piVar1 + 0x10);
    }
  }
  return 0;
}

