
void FUN_006adc80(void)

{
  DWORDLONG dwlConditionMask;
  _OSVERSIONINFOEXA local_a4;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  memset(&local_a4,0,0x9c);
  local_a4.dwOSVersionInfoSize = 0x9c;
  local_a4.dwMajorVersion = 6;
  dwlConditionMask = (DWORDLONG)VerSetConditionMask(0,0,2,3);
  VerifyVersionInfoA(&local_a4,2,dwlConditionMask);
  FUN_0083e885();
  return;
}

