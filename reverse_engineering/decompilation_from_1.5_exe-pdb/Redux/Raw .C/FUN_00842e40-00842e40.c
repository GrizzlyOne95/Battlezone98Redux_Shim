
void FUN_00842e40(LPCWSTR param_1,undefined4 param_2)

{
  char cVar1;
  LPCWSTR lpFileName;
  BOOL BVar2;
  DWORD DVar3;
  uint local_28 [9];
  uint local_4;
  
  local_4 = DAT_008e7000 ^ (uint)local_28;
  lpFileName = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    lpFileName = *(LPCWSTR *)param_1;
  }
  BVar2 = GetFileAttributesExW(lpFileName,GetFileExInfoStandard,local_28);
  if (BVar2 == 0) {
    DVar3 = GetLastError();
  }
  else {
    DVar3 = 0;
  }
  cVar1 = FUN_00842d80(DVar3,param_1,param_2,"boost::filesystem::file_size");
  if ((cVar1 == '\0') &&
     (cVar1 = FUN_00842d80(-((local_28[0] & 0x10) != 0) & 0x32,param_1,param_2,
                           "boost::filesystem::file_size"), cVar1 == '\0')) {
    FUN_0083e885();
    return;
  }
  FUN_0083e885();
  return;
}

