
void FUN_004fe800(void)

{
  char cVar1;
  undefined1 local_30 [8];
  uint local_28;
  uint local_24;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004fbb60();
  FUN_004fed90(&stack0x00000004,0);
  cVar1 = FUN_004fbc20(local_20,local_30);
  local_24 = (uint)(cVar1 != '\0');
  local_28 = local_24;
  FUN_004180b0();
  FUN_0083e885();
  return;
}

