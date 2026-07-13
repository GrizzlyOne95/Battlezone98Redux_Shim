
void * FUN_006a8850(void)

{
  void *pvVar1;
  
  pvVar1 = malloc(0x48);
  FUN_0069d210((int)pvVar1 + 0xc);
  *(undefined4 *)((int)pvVar1 + 0x28) = 0;
  *(undefined4 *)((int)pvVar1 + 4) = 0xffffffff;
  *(undefined4 *)((int)pvVar1 + 8) = 0xffffffff;
  *(undefined4 *)((int)pvVar1 + 0x34) = 0;
  *(undefined4 *)((int)pvVar1 + 0x40) = 0;
  *(undefined4 *)((int)pvVar1 + 0x44) = 0;
  return pvVar1;
}

