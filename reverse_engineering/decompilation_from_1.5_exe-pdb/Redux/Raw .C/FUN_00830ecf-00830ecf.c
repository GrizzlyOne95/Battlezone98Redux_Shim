
undefined * FUN_00830ecf(int param_1,int param_2)

{
  undefined *puVar1;
  double dVar2;
  
  if (param_2 - 1U < *(uint *)(param_1 + 0x1c)) {
    return (undefined *)(*(int *)(param_1 + 0xc) + -0x10 + param_2 * 0x10);
  }
  dVar2 = (double)param_2;
  puVar1 = (undefined *)FUN_00830d4e(param_1,dVar2);
  while ((*(int *)(puVar1 + 0x18) != 3 || (*(double *)(puVar1 + 0x10) != dVar2))) {
    puVar1 = *(undefined **)(puVar1 + 0x1c);
    if (puVar1 == (undefined *)0x0) {
      return &DAT_0086ed18;
    }
  }
  return puVar1;
}

