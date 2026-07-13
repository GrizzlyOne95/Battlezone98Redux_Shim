
void FUN_008381c0(undefined4 param_1)

{
  DWORD dwMessageId;
  DWORD DVar1;
  CHAR local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  dwMessageId = GetLastError();
  DVar1 = FormatMessageA(0x1200,(LPCVOID)0x0,dwMessageId,0,local_88,0x80,(va_list *)0x0);
  if (DVar1 == 0) {
    FUN_0082cc9e(param_1,"system error %d\n",dwMessageId);
  }
  else {
    FUN_0082cd77(param_1,local_88);
  }
  FUN_0083e885();
  return;
}

