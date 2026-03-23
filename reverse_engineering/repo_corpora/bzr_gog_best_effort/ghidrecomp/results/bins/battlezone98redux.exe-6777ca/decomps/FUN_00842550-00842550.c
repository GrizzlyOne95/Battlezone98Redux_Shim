
void FUN_00842550(DWORD *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  WCHAR WVar1;
  uint uVar2;
  BOOL BVar3;
  DWORD DVar4;
  DWORD DVar5;
  undefined4 uVar6;
  int iVar7;
  WCHAR *pWVar8;
  undefined4 local_27c;
  void *local_278 [4];
  undefined4 local_268;
  uint local_264;
  _WIN32_FIND_DATAW local_260;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865adb;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_27c;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffd74;
  ExceptionList = &local_c;
  local_27c = param_3;
  BVar3 = FindNextFileW((HANDLE)*param_2,&local_260);
  if (BVar3 == 0) {
    DVar4 = GetLastError();
    if ((HANDLE)*param_2 != (HANDLE)0x0) {
      FindClose((HANDLE)*param_2);
      *param_2 = 0;
    }
    DVar5 = FUN_0083e820();
    if (DVar4 == 0x12) {
      DVar4 = 0;
    }
    *param_1 = DVar4;
  }
  else {
    if (local_260.cFileName[0] == L'\0') {
      iVar7 = 0;
    }
    else {
      pWVar8 = local_260.cFileName;
      do {
        WVar1 = *pWVar8;
        pWVar8 = pWVar8 + 1;
      } while (WVar1 != L'\0');
      iVar7 = (int)pWVar8 - (int)(local_260.cFileName + 1) >> 1;
    }
    FUN_0083fdc0(local_260.cFileName,iVar7);
    if ((local_260.dwFileAttributes & 0x400) == 0) {
      if ((local_260.dwFileAttributes & 0x10) == 0) {
        *param_4 = 2;
        *param_5 = 2;
      }
      else {
        *param_4 = 3;
        *param_5 = 3;
      }
      FUN_0083f930(local_260.cFileName);
      local_4 = 0;
      uVar6 = FUN_008430e0(local_278,local_260.dwFileAttributes,uVar2);
      param_4[1] = uVar6;
      local_4 = 0xffffffff;
      if (7 < local_264) {
        operator_delete(local_278[0]);
      }
      local_264 = 7;
      local_278[0] = (void *)((uint)local_278[0] & 0xffff0000);
      local_268 = 0;
      param_5[1] = param_4[1];
    }
    else {
      *param_4 = 0;
      *param_5 = 0;
    }
    *param_1 = 0;
    DVar5 = FUN_0083e820();
  }
  param_1[1] = DVar5;
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

