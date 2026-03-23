
void FUN_006adef0(void)

{
  int iVar1;
  LARGE_INTEGER local_14;
  int local_c;
  int local_8;
  
  iVar1 = get();
  if (iVar1 != 0) {
    local_c = FUN_006acb90(300000000);
    if (local_c < 300000000) {
      local_14.s.LowPart = -local_c;
      local_14.s.HighPart = (int)local_14.s.LowPart >> 0x1f;
      local_14.QuadPart = (LONGLONG)__allmul(local_14.s.LowPart,local_14.s.HighPart,10,0);
      SetWaitableTimer(*(HANDLE *)(local_8 + 0x30),&local_14,300000,(PTIMERAPCROUTINE)0x0,
                       (LPVOID)0x0,0);
    }
  }
  return;
}

