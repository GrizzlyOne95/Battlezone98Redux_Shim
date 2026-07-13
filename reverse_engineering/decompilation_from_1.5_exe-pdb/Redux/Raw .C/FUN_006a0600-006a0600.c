
undefined4 FUN_006a0600(ushort param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_02ceb7e8 + (uint)param_1 * 0x9c);
  return CONCAT31(cVar1 >> 7,cVar1 == '\0');
}

