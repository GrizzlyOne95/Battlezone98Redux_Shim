
/* WARNING: Removing unreachable block (ram,0x0042a83d) */
/* WARNING: Removing unreachable block (ram,0x0042a87a) */
/* WARNING: Removing unreachable block (ram,0x0042a885) */
/* WARNING: Removing unreachable block (ram,0x0042a87c) */
/* WARNING: Removing unreachable block (ram,0x0042a841) */
/* WARNING: Removing unreachable block (ram,0x0042a852) */
/* WARNING: Removing unreachable block (ram,0x0042a867) */

undefined4 FUN_0042a7f0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined1 local_3c [16];
  void *local_2c;
  int local_20;
  char *local_1c;
  void *local_18;
  char *local_10;
  size_t local_c;
  char local_5;
  
  local_10 = (char *)*param_1;
  local_1c = local_10 + 1;
  do {
    local_5 = *local_10;
    local_10 = local_10 + 1;
  } while (local_5 != '\0');
  local_20 = (int)local_10 - (int)local_1c;
  local_c = local_20 + 1;
  local_2c = (void *)FUN_0083e9fc(local_c,&DAT_00914ce1);
  if (local_2c == (void *)0x0) {
    uVar1 = 0xfffffffe;
  }
  else {
    local_18 = local_2c;
    memcpy(local_2c,(void *)*param_1,local_c);
    FUN_004282e0(local_18,0);
    FUN_0042d880(local_3c);
    *param_1 = local_18;
    uVar1 = 0;
  }
  return uVar1;
}

