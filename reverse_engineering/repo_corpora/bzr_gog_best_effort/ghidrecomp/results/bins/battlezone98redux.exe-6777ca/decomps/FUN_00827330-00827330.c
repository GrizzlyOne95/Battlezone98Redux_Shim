
void FUN_00827330(int param_1,char *param_2)

{
  char local_2c [36];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  strncpy(local_2c,param_2,0x10);
  bsearch(local_2c,*(void **)(param_1 + 0x28),*(size_t *)(param_1 + 0x18),0x24,FUN_00827010);
  FUN_0083e885();
  return;
}

