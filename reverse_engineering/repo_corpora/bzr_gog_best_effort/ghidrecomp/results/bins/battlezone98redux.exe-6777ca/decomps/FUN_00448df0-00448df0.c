
HANDLE __fastcall FUN_00448df0(int param_1)

{
  HANDLE hObject;
  HANDLE pvVar1;
  
  hObject = (HANDLE)FUN_00448b70(param_1 + 4);
  if (hObject == (HANDLE)0x0) {
    hObject = (HANDLE)FUN_00448ab0(0,0);
    LOCK();
    pvVar1 = *(HANDLE *)(param_1 + 4);
    if (pvVar1 == (HANDLE)0x0) {
      *(HANDLE *)(param_1 + 4) = hObject;
      pvVar1 = (HANDLE)0x0;
    }
    UNLOCK();
    if (pvVar1 != (HANDLE)0x0) {
      CloseHandle(hObject);
      hObject = pvVar1;
    }
  }
  return hObject;
}

