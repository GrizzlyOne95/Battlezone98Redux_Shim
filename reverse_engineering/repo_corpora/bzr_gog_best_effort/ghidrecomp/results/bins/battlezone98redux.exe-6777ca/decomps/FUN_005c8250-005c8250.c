
void FUN_005c8250(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_005c8220(local_14,param_3,param_4);
  if (cVar1 != '\0') {
    FUN_005c8380(param_1,param_2,local_14,param_5);
  }
  FUN_0083e885();
  return;
}

