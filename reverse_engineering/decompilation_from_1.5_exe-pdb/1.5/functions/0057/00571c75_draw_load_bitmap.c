/*
 * Entry: 00571c75
 * Name: draw_load_bitmap
 * Namespace: Global
 * Signature: int draw_load_bitmap(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl draw_load_bitmap(void)

{
  char cVar1;
  HDC hDC;
  int iVar2;
  int iVar3;
  _LoadScreenItem *p_Var4;
  ShellBitmap *pSVar5;
  char *pcVar6;
  int *piVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  char local_108 [124];
  undefined1 local_8c [132];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_8c;
  InvalidateRect((HWND)shell_hwnd,(RECT *)0x0,0);
  hDC = GetDC((HWND)shell_hwnd);
  if (nLoadStarted == 0) {
    if (nOldMissionMode == 0) {
      iVar2 = 0;
      piVar7 = &LoadScreenList[0].nMissionIndex;
LAB_00571d33:
      if ((piVar7[-1] != nPlayerSide) || (*piVar7 != nMissionCurrentIndex)) goto LAB_00571d42;
      p_Var4 = LoadScreenList + iVar2;
      iVar2 = -(int)p_Var4;
      do {
        cVar1 = p_Var4->cBitmapName[0];
        (local_108 + iVar2)[(int)p_Var4->cBitmapName] = cVar1;
        p_Var4 = (_LoadScreenItem *)(p_Var4->cBitmapName + 1);
      } while (cVar1 != '\0');
      goto LAB_00571d95;
    }
    if (nPlayerSide == 1) {
      iVar2 = 0;
      do {
        cVar1 = LoadScreenList[1].cBitmapName[iVar2];
        local_108[iVar2] = cVar1;
        iVar2 = iVar2 + 1;
      } while (cVar1 != '\0');
    }
    else if (nPlayerSide == 2) {
      iVar2 = 0;
      do {
        cVar1 = LoadScreenList[2].cBitmapName[iVar2];
        local_108[iVar2] = cVar1;
        iVar2 = iVar2 + 1;
      } while (cVar1 != '\0');
    }
    else {
      iVar2 = 0;
      do {
        cVar1 = LoadScreenList[1].cBitmapName[iVar2];
        local_108[iVar2] = cVar1;
        iVar2 = iVar2 + 1;
      } while (cVar1 != '\0');
    }
  }
  else {
    iVar2 = 0;
    do {
      cVar1 = LoadScreenList[0].cBitmapName[iVar2];
      local_108[iVar2] = cVar1;
      iVar2 = iVar2 + 1;
    } while (cVar1 != '\0');
  }
LAB_00571d95:
  pSVar5 = operator_new(0x20);
  if (pSVar5 == (ShellBitmap *)0x0) {
    myBitmap = (ShellBitmap *)0x0;
  }
  else {
    myBitmap = ShellBitmap::ShellBitmap(pSVar5,local_108,0,0);
  }
  ShellBitmap::BltBitmap(myBitmap,(HDC__ *)hDC);
  pSVar5 = myBitmap;
  if (myBitmap != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(myBitmap);
    operator_delete(pSVar5);
    myBitmap = (ShellBitmap *)0x0;
  }
  ReleaseDC((HWND)shell_hwnd,hDC);
  if ((((nPlayerSide == 1) && (nOldMissionMode == 0)) && (nLoadStarted == 0)) &&
     (iVar2 = Net_IsNetGame(), iVar2 == 0)) {
    pcVar6 = USAMissionList[nMissionCurrentIndex].cMissionVoice;
    iVar2 = 5;
    bVar10 = true;
    pcVar8 = pcVar6;
    pcVar9 = "NULL";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + 1;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (!bVar10) {
      iVar2 = -(int)pcVar6;
      do {
        cVar1 = *pcVar6;
        pcVar6[(int)(local_108 + iVar2)] = cVar1;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      loadVoice = ShellPlaySound(local_108,100,0,-1);
    }
  }
  nLoadStarted = 0;
  return 1;
LAB_00571d42:
  iVar3 = 0;
  if (nPlayerSide == 3) {
    do {
      cVar1 = LoadScreenList[1].cBitmapName[iVar3];
      local_108[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
    } while (cVar1 != '\0');
  }
  else {
    do {
      cVar1 = LoadScreenList[0].cBitmapName[iVar3];
      local_108[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
    } while (cVar1 != '\0');
  }
  piVar7 = piVar7 + 0x42;
  iVar2 = iVar2 + 1;
  if (0x63d5d3 < (int)piVar7) goto LAB_00571d95;
  goto LAB_00571d33;
}
