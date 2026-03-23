
void FUN_007b58f0(void)

{
  char cVar1;
  undefined4 uVar2;
  char *local_10;
  char *local_c;
  
  uVar2 = FUN_007cb0a0();
  *(undefined4 *)(DAT_0094672c + 0x34) = uVar2;
  local_10 = &DAT_008e90a0 + *(int *)(DAT_0094672c + 0x34) * 0x140;
  local_c = &DAT_008ead70;
  do {
    cVar1 = *local_10;
    *local_c = cVar1;
    local_10 = local_10 + 1;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  return;
}

