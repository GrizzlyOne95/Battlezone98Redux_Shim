
undefined4 FUN_005d4280(void)

{
  char cVar1;
  char *local_10;
  char *local_c;
  
  local_10 = &DAT_008e90a0 + *(int *)(DAT_0094672c + 0x34) * 0x140;
  local_c = &DAT_008ead70;
  do {
    cVar1 = *local_10;
    *local_c = cVar1;
    local_10 = local_10 + 1;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  return 0;
}

