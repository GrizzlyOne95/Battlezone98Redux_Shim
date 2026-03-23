
DWORD __fastcall FUN_006ac190(LPCRITICAL_SECTION param_1)

{
  BOOL BVar1;
  DWORD DVar2;
  void *local_14;
  code *pcStack_10;
  uint local_c;
  undefined4 local_8;
  
  pcStack_10 = FUN_0083f1c9;
  local_14 = ExceptionList;
  local_c = DAT_008e7000 ^ 0x8c2d10;
  ExceptionList = &local_14;
  local_8 = 0;
  BVar1 = InitializeCriticalSectionAndSpinCount(param_1,0x80000000);
  if (BVar1 == 0) {
    DVar2 = GetLastError();
  }
  else {
    DVar2 = 0;
  }
  ExceptionList = local_14;
  return DVar2;
}

