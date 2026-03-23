
void FUN_0062cc80(void)

{
  int _Memory;
  
  while (_Memory = DAT_02b3c724, DAT_02b3c724 != 0) {
    DAT_02b3c724 = *(int *)(DAT_02b3c724 + 0x7c);
    free((void *)_Memory);
  }
  return;
}

