
undefined4 FUN_008436b0(LPCWSTR param_1)

{
  BOOL BVar1;
  DWORD DVar2;
  
  if (7 < *(uint *)(param_1 + 10)) {
    param_1 = *(LPCWSTR *)param_1;
  }
  BVar1 = RemoveDirectoryW(param_1);
  if (BVar1 == 0) {
    DVar2 = GetLastError();
    if (((((DVar2 != 2) && (DVar2 != 3)) && (DVar2 != 0x7b)) && ((DVar2 != 0xf && (DVar2 != 0x15))))
       && ((DVar2 != 0x57 && ((DVar2 != 0xa1 && (DVar2 != 0x35)))))) {
      return 0;
    }
  }
  return 1;
}

