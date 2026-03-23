
undefined4 FUN_0043e8a0(HANDLE *param_1)

{
  bool bVar1;
  DWORD DVar2;
  int iVar3;
  
  bVar1 = false;
  FUN_0043e6d0(0xffffffff,"OggDecoder");
  while (!bVar1) {
    DVar2 = MsgWaitForMultipleObjects(2,param_1,0,0xffffffff,0);
    if (DVar2 == 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xbd));
      if (param_1[7] == (HANDLE)0x0) {
        bVar1 = true;
      }
      else {
        iVar3 = FUN_00416aa0(*(undefined1 *)(param_1 + 4));
        if (iVar3 < 0) {
          bVar1 = true;
        }
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xbd));
    }
    else if (DVar2 == 1) {
      bVar1 = true;
    }
  }
  *(undefined1 *)(param_1 + 0xc3) = 1;
  SetEvent(DAT_00915648);
  return 0;
}

