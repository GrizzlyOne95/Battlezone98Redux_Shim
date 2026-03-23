
undefined4 * FUN_006a8590(int param_1)

{
  undefined4 *puVar1;
  void *pvVar2;
  
  puVar1 = malloc(0x10);
  pvVar2 = malloc(param_1 << 2);
  *puVar1 = pvVar2;
  pvVar2 = malloc(param_1 << 3);
  puVar1[1] = pvVar2;
  puVar1[2] = 0;
  puVar1[3] = param_1;
  return puVar1;
}

