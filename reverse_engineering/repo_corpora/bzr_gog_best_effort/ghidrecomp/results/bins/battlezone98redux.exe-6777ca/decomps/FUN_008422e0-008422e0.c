
void FUN_008422e0(DWORD *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 *param_5,undefined4 *param_6)

{
  short sVar1;
  WCHAR WVar2;
  LPCWSTR *****ppppppWVar3;
  HANDLE pvVar4;
  DWORD DVar5;
  DWORD DVar6;
  undefined4 uVar7;
  short *psVar8;
  int iVar9;
  WCHAR *pWVar10;
  short *psVar11;
  undefined4 *local_298;
  undefined4 local_294;
  LPCWSTR ****local_290 [4];
  int local_280;
  uint local_27c;
  void *local_278 [5];
  uint local_264;
  _WIN32_FIND_DATAW local_260;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865a96;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_298;
  ExceptionList = &local_c;
  local_294 = param_4;
  local_298 = param_2;
  local_290[0] = (LPCWSTR ****)((uint)local_290[0] & 0xffff0000);
  local_27c = 7;
  local_280 = 0;
  FID_conflict_assign(param_3,0,0xffffffff);
  local_4 = 0;
  if (local_280 == 0) {
LAB_008423c9:
    psVar11 = &DAT_00870df4;
  }
  else {
    ppppppWVar3 = local_290;
    if (7 < local_27c) {
      ppppppWVar3 = (LPCWSTR *****)local_290[0];
    }
    if (*(LPCWSTR)((int)ppppppWVar3 + (local_280 + -1) * 2) != L'\\') {
      ppppppWVar3 = local_290;
      if (7 < local_27c) {
        ppppppWVar3 = (LPCWSTR *****)local_290[0];
      }
      if (*(LPCWSTR)((int)ppppppWVar3 + (local_280 + -1) * 2) != L'/') {
        ppppppWVar3 = local_290;
        if (7 < local_27c) {
          ppppppWVar3 = (LPCWSTR *****)local_290[0];
        }
        if (*(LPCWSTR)((int)ppppppWVar3 + (local_280 + -1) * 2) != L':') goto LAB_008423c9;
      }
    }
    psVar11 = &DAT_00870dfc;
  }
  psVar8 = psVar11;
  do {
    sVar1 = *psVar8;
    psVar8 = psVar8 + 1;
  } while (sVar1 != 0);
  FUN_0083fce0(psVar11,(int)psVar8 - (int)(psVar11 + 1) >> 1);
  ppppppWVar3 = local_290;
  if (7 < local_27c) {
    ppppppWVar3 = (LPCWSTR *****)local_290[0];
  }
  pvVar4 = FindFirstFileW((LPCWSTR)ppppppWVar3,&local_260);
  *local_298 = pvVar4;
  if (pvVar4 == (HANDLE)0xffffffff) {
    *local_298 = 0;
    DVar5 = GetLastError();
    if (DVar5 != 2) {
      DVar5 = GetLastError();
      if (DVar5 != 0x12) {
        DVar6 = GetLastError();
        DVar5 = FUN_0083e820();
        *param_1 = DVar6;
        goto LAB_0084250b;
      }
    }
    DVar5 = FUN_0083e820();
    *param_1 = 0;
  }
  else {
    if (local_260.cFileName[0] == L'\0') {
      iVar9 = 0;
    }
    else {
      pWVar10 = local_260.cFileName;
      do {
        WVar2 = *pWVar10;
        pWVar10 = pWVar10 + 1;
      } while (WVar2 != L'\0');
      iVar9 = (int)pWVar10 - (int)(local_260.cFileName + 1) >> 1;
    }
    FUN_0083fdc0(local_260.cFileName,iVar9);
    if ((local_260.dwFileAttributes & 0x400) == 0) {
      if ((local_260.dwFileAttributes & 0x10) == 0) {
        *param_5 = 2;
        *param_6 = 2;
      }
      else {
        *param_5 = 3;
        *param_6 = 3;
      }
      FUN_0083f930(local_260.cFileName);
      local_4._0_1_ = 1;
      uVar7 = FUN_008430e0(local_278,local_260.dwFileAttributes);
      param_5[1] = uVar7;
      local_4 = (uint)local_4._1_3_ << 8;
      if (7 < local_264) {
        operator_delete(local_278[0]);
      }
      param_6[1] = param_5[1];
    }
    else {
      *param_5 = 0;
      *param_6 = 0;
    }
    *param_1 = 0;
    DVar5 = FUN_0083e820();
  }
LAB_0084250b:
  param_1[1] = DVar5;
  if (7 < local_27c) {
    operator_delete(local_290[0]);
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

