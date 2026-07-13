
void FUN_00448bd0(void)

{
  char cVar1;
  HANDLE hHandle;
  uint local_10;
  uint *local_c;
  undefined1 local_5;
  
  cVar1 = FUN_00448b90();
  if (cVar1 == '\0') {
    local_10 = *local_c;
    FUN_00448c70(&local_10);
    if ((local_10 & 0x80000000) != 0) {
      local_5 = 0;
      hHandle = (HANDLE)FUN_00448df0();
      do {
        WaitForSingleObjectEx(hHandle,0xffffffff,0);
        FUN_00448d00(&local_10);
        local_5 = (local_10 & 0x80000000) == 0;
      } while (!(bool)local_5);
    }
  }
  return;
}

