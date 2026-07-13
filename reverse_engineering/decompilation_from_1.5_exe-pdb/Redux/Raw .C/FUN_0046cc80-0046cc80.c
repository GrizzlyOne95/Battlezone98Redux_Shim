
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0046cc80(void)

{
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  char local_40 [40];
  undefined4 local_18;
  undefined4 local_14;
  code *local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_50 = 10;
  local_4c = 300;
  local_48 = 0x1e0;
  local_18 = 0xffff0000;
  builtin_strncpy(local_40,"courier",8);
  local_14 = 0;
  local_10 = FUN_0046ced0;
  local_c = 0;
  DAT_0260d184 = FUN_008231c0(&local_50);
  _DAT_0260d5e8 = 1;
  DAT_0260d5ec = 0;
  FUN_0083e885();
  return;
}

