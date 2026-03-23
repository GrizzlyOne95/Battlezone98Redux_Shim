
void FUN_007d62a0(void)

{
  _CONSOLE_SCREEN_BUFFER_INFO local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  GetConsoleScreenBufferInfo(DAT_008f1694,&local_20);
  FUN_0083e885();
  return;
}

