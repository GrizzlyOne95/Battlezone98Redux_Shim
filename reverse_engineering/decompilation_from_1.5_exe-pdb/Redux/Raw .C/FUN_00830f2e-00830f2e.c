
undefined * FUN_00830f2e(int param_1,int param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)
           (((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U & *(uint *)(param_2 + 8)) * 0x20 +
           *(int *)(param_1 + 0x10));
  while ((*(int *)(puVar1 + 0x18) != 4 || (*(int *)(puVar1 + 0x10) != param_2))) {
    puVar1 = *(undefined **)(puVar1 + 0x1c);
    if (puVar1 == (undefined *)0x0) {
      return &DAT_0086ed18;
    }
  }
  return puVar1;
}

