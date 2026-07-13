
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_004fbe90(void)

{
  char cVar1;
  char *local_1014;
  char *local_1010;
  allocator<char> local_1009;
  char local_1008 [4096];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  strncpy(local_1008,&DAT_00945708,0x1000);
  std::allocator<char>::allocator<char>(&local_1009);
  DAT_009173b7 = 1;
  cVar1 = FUN_0056ad10(local_1008,1);
  if (cVar1 == '\0') {
    FUN_00417c60();
  }
  else {
    DAT_009173b6 = DAT_008eaab4 != 0;
    FUN_004fd190(local_1008,0);
    DAT_009173b6 = 0;
    local_1014 = local_1008;
    local_1010 = &DAT_00945708;
    do {
      cVar1 = *local_1014;
      *local_1010 = cVar1;
      local_1014 = local_1014 + 1;
      local_1010 = local_1010 + 1;
    } while (cVar1 != '\0');
    FUN_00417c60(&DAT_00945708);
  }
  FUN_0083e885();
  return;
}

