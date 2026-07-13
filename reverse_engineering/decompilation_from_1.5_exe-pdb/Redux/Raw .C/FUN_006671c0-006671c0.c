
void __fastcall FUN_006671c0(int param_1)

{
  HANDLE hObject;
  
  LOCK();
  hObject = *(HANDLE *)(param_1 + 4);
  *(undefined4 *)(param_1 + 4) = 0;
  UNLOCK();
  if (hObject != (HANDLE)0x0) {
    CloseHandle(hObject);
  }
  return;
}

