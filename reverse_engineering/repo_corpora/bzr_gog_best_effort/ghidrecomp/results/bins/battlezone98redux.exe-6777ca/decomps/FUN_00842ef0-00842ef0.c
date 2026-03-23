
undefined1 FUN_00842ef0(LPCWSTR param_1)

{
  uint uVar1;
  HANDLE hDevice;
  int *lpOutBuffer;
  BOOL BVar2;
  undefined1 uVar3;
  DWORD local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865c30;
  local_c = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffffe0;
  ExceptionList = &local_c;
  if (7 < *(uint *)(param_1 + 10)) {
    param_1 = *(LPCWSTR *)param_1;
  }
  hDevice = CreateFileW(param_1,8,7,(LPSECURITY_ATTRIBUTES)0x0,3,0x2200000,(HANDLE)0x0);
  local_4 = 0;
  if (hDevice == (HANDLE)0xffffffff) {
    uVar3 = 0;
  }
  else {
    lpOutBuffer = (int *)FUN_0083d92c(0x4000,uVar1);
    local_4 = CONCAT31(local_4._1_3_,1);
    BVar2 = DeviceIoControl(hDevice,0x900a8,(LPVOID)0x0,0,lpOutBuffer,0x4000,&local_10,
                            (LPOVERLAPPED)0x0);
    if (BVar2 == 0) {
      uVar3 = 0;
    }
    else if ((*lpOutBuffer == -0x5ffffff4) || (*lpOutBuffer == -0x5ffffffd)) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    operator_delete__(lpOutBuffer);
  }
  local_4 = 0xffffffff;
  if (hDevice != (HANDLE)0xffffffff) {
    CloseHandle(hDevice);
  }
  ExceptionList = local_c;
  return uVar3;
}

