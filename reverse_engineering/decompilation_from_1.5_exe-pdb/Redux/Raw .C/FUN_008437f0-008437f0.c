
void FUN_008437f0(LPCWSTR param_1,LPCWSTR param_2,undefined4 param_3)

{
  LPCWSTR lpNewFileName;
  BOOL BVar1;
  DWORD DVar2;
  LPCWSTR lpExistingFileName;
  
  lpNewFileName = param_2;
  if (7 < *(uint *)(param_2 + 10)) {
    lpNewFileName = *(LPCWSTR *)param_2;
  }
  lpExistingFileName = param_1;
  if (7 < *(uint *)(param_1 + 10)) {
    lpExistingFileName = *(LPCWSTR *)param_1;
  }
  BVar1 = MoveFileExW(lpExistingFileName,lpNewFileName,3);
  if (BVar1 == 0) {
    DVar2 = GetLastError();
  }
  else {
    DVar2 = 0;
  }
  FUN_00842cb0(DVar2,param_1,param_2,param_3,"boost::filesystem::rename");
  return;
}

