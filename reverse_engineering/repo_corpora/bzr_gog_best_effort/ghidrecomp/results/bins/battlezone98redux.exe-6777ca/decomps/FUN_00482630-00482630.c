
void FUN_00482630(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  char local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = 0;
  sprintf_s(local_48,0x40,"%d",param_2,0);
  basic_string<>(local_48);
  FUN_0083e885(uVar1 | 1);
  return;
}

