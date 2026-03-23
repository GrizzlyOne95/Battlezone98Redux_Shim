
undefined4 FUN_00684ca0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  cVar1 = (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x88))();
  if ((cVar1 != '\0') && (iVar2 = FUN_004346a0(), iVar2 == 0)) {
    uVar3 = FUN_00684ce0(param_1);
    return uVar3;
  }
  return 0;
}

