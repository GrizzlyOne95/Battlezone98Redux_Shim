
void FUN_00839df0(int param_1)

{
  int local_20 [6];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0083b5a6(param_1,local_20,0);
  if (local_20[0] == 1) {
    local_20[0] = 3;
  }
  FUN_0083c8d6(*(undefined4 *)(param_1 + 0x30),local_20);
  FUN_0083e885();
  return;
}

