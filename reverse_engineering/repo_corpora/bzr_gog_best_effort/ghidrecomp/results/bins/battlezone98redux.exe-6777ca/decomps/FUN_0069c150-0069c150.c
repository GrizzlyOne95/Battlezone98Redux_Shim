
void FUN_0069c150(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int local_60;
  int local_5c;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_60 = 0;
  local_5c = -2;
  while (((local_5c != -1 && (local_60 == 0)) &&
         (local_5c = FUN_00699ec0(param_1,param_2,param_3,param_4,local_58), local_5c != -1))) {
    local_60 = FUN_0069c0a0(param_1,param_2,param_3,param_4,local_5c,local_58);
  }
  FUN_0083e885();
  return;
}

