
void __fastcall FUN_0083d6a0(int param_1)

{
  code *pcVar1;
  undefined4 *puVar2;
  
  pcVar1 = _aligned_free_exref;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  if ((*(void **)(param_1 + 0x3c) != (void *)0x0) && (*(char *)(param_1 + 0x40) != '\0')) {
    _aligned_free(*(void **)(param_1 + 0x3c));
    pcVar1 = _aligned_free_exref;
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  puVar2 = *(undefined4 **)(param_1 + 0x48);
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  if (puVar2 != *(undefined4 **)(param_1 + 0x4c)) {
    do {
      (*pcVar1)(*puVar2);
      puVar2 = puVar2 + 1;
      pcVar1 = _aligned_free_exref;
    } while (puVar2 != *(undefined4 **)(param_1 + 0x4c));
  }
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x48);
  if ((uint)(*(int *)(param_1 + 0x50) - *(int *)(param_1 + 0x48) >> 2) < 0x10) {
    FUN_0083d730(0x10);
  }
  return;
}

