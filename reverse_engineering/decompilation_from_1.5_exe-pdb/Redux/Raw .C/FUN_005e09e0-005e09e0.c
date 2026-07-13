
void FUN_005e09e0(void)

{
  void *pvVar1;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  undefined4 auStack_30 [10];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = rand();
  local_40 = local_40 % 10;
  if (local_40 < 3) {
    local_40 = 3;
  }
  for (local_38 = 0; local_38 < local_40; local_38 = local_38 + 1) {
    pvVar1 = malloc(0x40);
    auStack_30[local_38] = pvVar1;
  }
  for (local_34 = 0; local_34 < 0x10; local_34 = local_34 + 1) {
    pvVar1 = operator_new(0x184);
    *(void **)(&DAT_00918370 + local_34 * 4) = pvVar1;
    for (local_3c = 0; local_3c < 0x5b; local_3c = local_3c + 1) {
      *(undefined4 *)(*(int *)(&DAT_00918370 + local_34 * 4) + local_3c * 4) = 0;
    }
    FUN_005e10d0(0);
    *(undefined4 *)(*(int *)(&DAT_00918370 + local_34 * 4) + 0x170) = 0;
    *(undefined4 *)(*(int *)(&DAT_00918370 + local_34 * 4) + 0x174) = 0;
    *(undefined4 *)(*(int *)(&DAT_00918370 + local_34 * 4) + 0x178) = 0;
    *(uint *)(*(int *)(&DAT_00918370 + local_34 * 4) + 0x17c) = 1 << ((byte)local_34 & 0x1f) | 1;
    *(int *)(*(int *)(&DAT_00918370 + local_34 * 4) + 0x180) = local_34;
  }
  for (local_38 = 0; local_38 < local_40; local_38 = local_38 + 1) {
    free((void *)auStack_30[local_38]);
  }
  FUN_0083e885();
  return;
}

