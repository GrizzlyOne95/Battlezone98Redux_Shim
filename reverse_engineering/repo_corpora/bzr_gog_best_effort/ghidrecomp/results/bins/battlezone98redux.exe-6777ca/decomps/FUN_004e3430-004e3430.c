
undefined4 FUN_004e3430(int param_1,int param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int local_10;
  
  *(int *)(param_2 + 0x68) = *(int *)(param_1 + 0x68);
  *(undefined4 *)(param_2 + 0x6c) = *(undefined4 *)(param_1 + 0x6c);
  pvVar1 = malloc(*(int *)(param_1 + 0x6c) << 4);
  *(void **)(param_2 + 0x74) = pvVar1;
  *(undefined4 *)(param_2 + 0x70) = *(undefined4 *)(param_1 + 0x70);
  for (local_10 = 0; local_10 < *(int *)(param_2 + 0x68); local_10 = local_10 + 1) {
    puVar4 = (undefined4 *)(local_10 * 0x10 + *(int *)(param_1 + 0x74));
    puVar3 = (undefined4 *)(local_10 * 0x10 + *(int *)(param_2 + 0x74));
    *puVar3 = *puVar4;
    uVar2 = FUN_004e3810(puVar4[2],puVar4[3]);
    puVar3[1] = uVar2;
    puVar3[2] = puVar4[2];
    puVar3[3] = puVar4[3];
  }
  *(undefined4 *)(param_2 + 100) = *(undefined4 *)(param_1 + 100);
  return 1;
}

