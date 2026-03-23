
undefined4 FUN_0043e4c0(int param_1)

{
  DWORD DVar1;
  
  while (*(char *)(param_1 + 0x38) != '\0') {
    DVar1 = MsgWaitForMultipleObjects(1,(HANDLE *)(param_1 + 0x28),0,0xffffffff,0);
    if (DVar1 == 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
      if (*(char *)(param_1 + 0x38) != '\0') {
        FUN_0043e100();
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
    }
  }
  *(undefined1 *)(param_1 + 0x39) = 1;
  SetEvent(*(HANDLE *)(param_1 + 0x2c));
  return 0;
}

