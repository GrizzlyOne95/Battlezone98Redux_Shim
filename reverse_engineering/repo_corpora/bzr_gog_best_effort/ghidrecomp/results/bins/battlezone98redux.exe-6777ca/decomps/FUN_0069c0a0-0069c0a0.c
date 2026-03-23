
void FUN_0069c0a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  void *local_60;
  int local_5c;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_5c = 0;
  local_60 = malloc(1);
  uVar1 = FUN_0069bfb0(param_5,local_58,&local_60);
  local_5c = FUN_00699f10(param_1,param_2,param_3,uVar1);
  if (local_5c == 0) {
    local_5c = FUN_0069bc80(param_1,param_2,param_3,param_4,param_5,param_6,&local_60,local_60);
  }
  free(local_60);
  FUN_0083e885();
  return;
}

