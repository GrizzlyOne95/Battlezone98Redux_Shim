
int * FUN_00693380(int param_1)

{
  int *piVar1;
  void *pvVar2;
  int local_8;
  
  piVar1 = malloc(8);
  *piVar1 = param_1;
  pvVar2 = malloc(param_1 << 4);
  piVar1[1] = (int)pvVar2;
  for (local_8 = 0; local_8 < param_1; local_8 = local_8 + 1) {
    *(undefined4 *)(piVar1[1] + 8 + local_8 * 0x10) = 0;
    *(undefined4 *)(piVar1[1] + 0xc + local_8 * 0x10) = 0;
    *(undefined4 *)(piVar1[1] + local_8 * 0x10) = 0;
    *(undefined4 *)(piVar1[1] + 4 + local_8 * 0x10) = 0;
  }
  return piVar1;
}

