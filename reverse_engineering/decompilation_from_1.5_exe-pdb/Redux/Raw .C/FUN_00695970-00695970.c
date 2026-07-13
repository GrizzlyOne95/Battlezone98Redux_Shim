
void FUN_00695970(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_64;
  int local_60;
  undefined4 local_5c;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_64 = 0;
  local_5c = 0;
  FUN_006a3c10(local_58);
  while( true ) {
    local_60 = FUN_006a3c70(local_58);
    if (local_60 == 0) break;
    FUN_00695830(param_2,local_60,param_1,&local_5c,&local_64);
  }
  FUN_0083e885();
  return;
}

