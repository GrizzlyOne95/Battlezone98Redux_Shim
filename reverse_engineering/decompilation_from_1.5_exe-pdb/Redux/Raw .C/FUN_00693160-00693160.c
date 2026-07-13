
void * FUN_00693160(void)

{
  void *pvVar1;
  undefined4 local_8;
  
  pvVar1 = malloc(0x80);
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    *(undefined4 *)((int)pvVar1 + local_8 * 4) = 0;
  }
  return pvVar1;
}

