/*
 * Entry: 005809a8
 * Name: OldDlgProc
 * Namespace: Global
 * Signature: int OldDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl OldDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char cVar1;
  ShellButton *pSVar2;
  ShellBitmap *pSVar3;
  ShellButton *pSVar4;
  HWND pHVar5;
  TextWindow *pTVar6;
  TextWindow *pTVar7;
  HWND pHVar8;
  HDC pHVar9;
  LRESULT LVar10;
  _USSRMission *p_Var11;
  _TrainingMission *p_Var12;
  HGDIOBJ pvVar13;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  ShellButton *extraout_EDX_03;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *extraout_EDX_04;
  uint uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  char *pcVar18;
  int iVar19;
  int nHeight;
  _USAMission *p_Var20;
  BOOL bRepaint;
  LOGBRUSH LStack_1f670;
  RECT RStack_1f664;
  WPARAM WStack_1f654;
  HWND__ *pHStack_1f650;
  HBRUSH pHStack_1f64c;
  undefined1 auStack_1f648 [64];
  char acStack_1f608 [24];
  undefined1 auStack_1f5f0 [127976];
  char local_208 [256];
  char local_108 [256];
  uint local_8;
  
  pSVar4 = urButton;
  local_8 = __security_cookie ^ (uint)auStack_1f5f0;
  pHStack_1f650 = param_1;
  if (0x111 < param_2) {
    if (param_2 != 0x134) {
      if (param_2 == 0x136) goto LAB_00581474;
      if (param_2 != 0x138) {
        if (param_2 == 0x200) {
          iVar19 = 0;
          iVar17 = 1;
          uVar15 = (uint)param_4 >> 0x10;
          uVar14 = param_4 & 0xffff;
          iVar16 = ShellButton::CheckRollOver(ulButton,uVar14,uVar15);
          ShellButton::SetButtonMode(this,iVar16,iVar17,iVar19);
          iVar19 = 0;
          iVar17 = 1;
          iVar16 = ShellButton::CheckRollOver(llButton,uVar14,uVar15);
          ShellButton::SetButtonMode(this_00,iVar16,iVar17,iVar19);
          iVar19 = 0;
          iVar17 = 1;
          iVar16 = ShellButton::CheckRollOver(urButton,uVar14,uVar15);
          pSVar4 = extraout_EDX_04;
        }
        else {
          if (param_2 != 0x201) {
            if (param_2 != 0x202) {
              return 0;
            }
            uVar14 = param_4 & 0xffff;
            iVar16 = ShellButton::CheckRollOver(urButton,uVar14,(uint)param_4 >> 0x10);
            if (iVar16 != 0) {
              nOldMissionIndex = SendDlgItemMessageA((HWND)param_1,0x429,0x188,0,0);
              nOldMissionMode = 1;
              if (nCaller == 1) {
                p_Var20 = USAMissionList + nOldMissionIndex;
                iVar16 = -(int)p_Var20;
                do {
                  cVar1 = p_Var20->cMissionName[0];
                  (local_108 + iVar16)[(int)p_Var20->cMissionName] = cVar1;
                  p_Var20 = (_USAMission *)(p_Var20->cMissionName + 1);
                } while (cVar1 != '\0');
              }
              else if (nCaller == 2) {
                p_Var11 = USSRMissionList + nOldMissionIndex;
                iVar16 = -(int)p_Var11;
                do {
                  cVar1 = p_Var11->cMissionName[0];
                  (local_108 + iVar16)[(int)p_Var11->cMissionName] = cVar1;
                  p_Var11 = (_USSRMission *)(p_Var11->cMissionName + 1);
                } while (cVar1 != '\0');
              }
              else if (nCaller == 3) {
                p_Var12 = TrnMissionList + nOldMissionIndex;
                iVar16 = -(int)p_Var12;
                do {
                  cVar1 = p_Var12->cMissionName[0];
                  (local_108 + iVar16)[(int)p_Var12->cMissionName] = cVar1;
                  p_Var12 = (_TrainingMission *)(p_Var12->cMissionName + 1);
                } while (cVar1 != '\0');
              }
              iVar16 = 0;
              do {
                cVar1 = local_108[iVar16];
                (&msn_filename)[iVar16] = cVar1;
                iVar16 = iVar16 + 1;
              } while (cVar1 != '\0');
              SetRunning(5);
              nReplayIntro = 0;
              nPlayCredits = 0;
              nShellMode = 0;
              Shell_EndDialog(param_1,1);
              return 0;
            }
            iVar16 = ShellButton::CheckRollOver(llButton,uVar14,extraout_EDX);
            if (iVar16 != 0) {
              ShowWindow((HWND)param_1,0);
              EnableWindow((HWND)param_1,0);
              do_options(0);
              SetCurrentBackground(pHStack_1f650,backGround);
              EnableWindow((HWND)pHStack_1f650,1);
              ShowWindow((HWND)pHStack_1f650,5);
              return 0;
            }
            iVar16 = ShellButton::CheckRollOver(ulButton,uVar14,extraout_EDX_00);
            if (iVar16 == 0) {
              return 0;
            }
            if (nCaller == 1) {
              nShellMode = ((nUsaMissionIndex < 0x11) - 1 & 0xfffffffb) + 7;
            }
            else if (nCaller == 2) {
              nShellMode = ((nUssrMissionIndex < 8) - 1 & 0xfffffffa) + 8;
            }
            else if (nCaller == 3) {
              nShellMode = ((nTrnMissionIndex < 4) - 1 & 0xfffffff9) + 9;
            }
            else {
              nShellMode = 1;
            }
            Shell_EndDialog(param_1,1);
            return 0;
          }
          uVar14 = param_4 & 0xffff;
          iVar16 = ShellButton::CheckRollOver(urButton,uVar14,(uint)param_4 >> 0x10);
          pSVar2 = llButton;
          if ((iVar16 == 0) &&
             (iVar16 = ShellButton::CheckRollOver(llButton,uVar14,extraout_EDX_01), pSVar4 = pSVar2,
             iVar16 == 0)) {
            iVar16 = ShellButton::CheckRollOver(ulButton,uVar14,extraout_EDX_02);
            if (iVar16 == 0) {
              return 0;
            }
            iVar19 = 0;
            iVar17 = 1;
            iVar16 = 2;
            pSVar4 = extraout_EDX_03;
          }
          else {
            iVar19 = 0;
            iVar17 = 1;
            iVar16 = 2;
          }
        }
        ShellButton::SetButtonMode(pSVar4,iVar16,iVar17,iVar19);
        return 0;
      }
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
LAB_00581474:
    pvVar13 = GetStockObject(4);
    return (int)pvVar13;
  }
  if (param_2 == 0x111) {
    if ((short)param_3 != 0x429) {
      return 0;
    }
    if ((short)(param_3 >> 0x10) != 1) {
      return 1;
    }
    LVar10 = SendDlgItemMessageA((HWND)param_1,0x429,0x188,0,0);
    if (nCaller == 1) {
      p_Var20 = USAMissionList + LVar10;
      iVar16 = -(int)p_Var20;
      do {
        cVar1 = p_Var20->cMissionName[0];
        (local_108 + iVar16)[(int)p_Var20->cMissionName] = cVar1;
        p_Var20 = (_USAMission *)(p_Var20->cMissionName + 1);
      } while (cVar1 != '\0');
    }
    else if (nCaller == 2) {
      p_Var11 = USSRMissionList + LVar10;
      iVar16 = -(int)p_Var11;
      do {
        cVar1 = p_Var11->cMissionName[0];
        (local_108 + iVar16)[(int)p_Var11->cMissionName] = cVar1;
        p_Var11 = (_USSRMission *)(p_Var11->cMissionName + 1);
      } while (cVar1 != '\0');
    }
    else if (nCaller == 3) {
      p_Var12 = TrnMissionList + LVar10;
      iVar16 = -(int)p_Var12;
      do {
        cVar1 = p_Var12->cMissionName[0];
        (local_108 + iVar16)[(int)p_Var12->cMissionName] = cVar1;
        p_Var12 = (_TrainingMission *)(p_Var12->cMissionName + 1);
      } while (cVar1 != '\0');
    }
    GetMissionDesc(local_108,acStack_1f608);
    pTVar7 = descText;
    TextWindow::SetWindowTextA(descText,acStack_1f608);
    (**(code **)(pTVar7->_padding_ + 4))(0);
    GetPlanetDesc(nCaller,LVar10,local_108);
    GetMissionDesc(local_108,acStack_1f608);
    pTVar7 = planetText;
    TextWindow::SetWindowTextA(planetText,acStack_1f608);
    (**(code **)(pTVar7->_padding_ + 4))(0);
    return 1;
  }
  if (param_2 == 2) {
    SnapShotBackground();
    CleanCurrentBackground();
    pSVar3 = backGround;
    if (backGround != (ShellBitmap *)0x0) {
      ShellBitmap::~ShellBitmap(backGround);
      operator_delete(pSVar3);
      backGround = (ShellBitmap *)0x0;
    }
    pSVar4 = ulButton;
    if (ulButton != (ShellButton *)0x0) {
      ShellButton::~ShellButton(ulButton);
      operator_delete(pSVar4);
      ulButton = (ShellButton *)0x0;
    }
    pSVar4 = llButton;
    if (llButton != (ShellButton *)0x0) {
      ShellButton::~ShellButton(llButton);
      operator_delete(pSVar4);
      llButton = (ShellButton *)0x0;
    }
    pSVar4 = urButton;
    if (urButton != (ShellButton *)0x0) {
      ShellButton::~ShellButton(urButton);
      operator_delete(pSVar4);
      urButton = (ShellButton *)0x0;
    }
    pTVar7 = planetText;
    if (planetText != (TextWindow *)0x0) {
      TextWindow::~TextWindow(planetText);
      operator_delete(pTVar7);
      planetText = (TextWindow *)0x0;
    }
    pTVar7 = descText;
    if (descText == (TextWindow *)0x0) {
      return 0;
    }
    TextWindow::~TextWindow(descText);
    operator_delete(pTVar7);
    descText = (TextWindow *)0x0;
    return 0;
  }
  if (param_2 == 0xf) {
    pHVar9 = BeginPaint((HWND)param_1,(LPPAINTSTRUCT)auStack_1f648);
    ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar9);
    ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar9);
    ShellButton::UpdateButton(llButton,(HDC__ *)pHVar9);
    ShellButton::UpdateButton(urButton,(HDC__ *)pHVar9);
    (**(code **)planetText->_padding_)(pHVar9,0);
    (**(code **)descText->_padding_)(pHVar9,0);
    EndPaint((HWND)param_1,(PAINTSTRUCT *)auStack_1f648);
    return 1;
  }
  if (param_2 == 0x14) {
    return 1;
  }
  if (param_2 == 0x20) {
    set_cursor(0);
    SetWindowLongA((HWND)param_1,0,1);
    return 1;
  }
  if (param_2 == 0x2b) {
    if (*(int *)(param_4 + 8) == -1) {
      return 0;
    }
    if (1 < *(int *)(param_4 + 0xc) - 1U) {
      return 1;
    }
    pHVar5 = *(HWND *)(param_4 + 0x14);
    pHVar8 = GetDlgItem((HWND)param_1,0x429);
    if (pHVar5 != pHVar8) {
      return 1;
    }
    SendMessageA(pHVar5,0x189,*(WPARAM *)(param_4 + 8),(LPARAM)local_208);
    GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)(auStack_1f648 + 8));
    RStack_1f664.top = *(int *)(param_4 + 0x20);
    RStack_1f664.bottom = *(int *)(param_4 + 0x28);
    iVar16 = (RStack_1f664.top - auStack_1f648._8_4_) + RStack_1f664.bottom;
    RStack_1f664.left = *(LONG *)(param_4 + 0x1c);
    RStack_1f664.right = *(LONG *)(param_4 + 0x24);
    if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
      LStack_1f670.lbColor = 0;
    }
    else {
      DrawFocusRect(*(HDC *)(param_4 + 0x18),&RStack_1f664);
      LStack_1f670.lbColor = 0x6400;
    }
    LStack_1f670.lbStyle = 0;
    LStack_1f670.lbHatch = 0;
    pHStack_1f64c = CreateBrushIndirect(&LStack_1f670);
    FillRect(*(HDC *)(param_4 + 0x18),&RStack_1f664,pHStack_1f64c);
    if (pHStack_1f64c != (HBRUSH)0x0) {
      DeleteObject(pHStack_1f64c);
    }
    pcVar18 = local_208;
    do {
      cVar1 = *pcVar18;
      pcVar18 = pcVar18 + 1;
    } while (cVar1 != '\0');
    TextOutA(*(HDC *)(param_4 + 0x18),5,iVar16 / 2,local_208,(int)pcVar18 - (int)(local_208 + 1));
    return 1;
  }
  if (param_2 == 0x2c) {
    *(undefined4 *)(param_4 + 0x10) = 0xe;
    return 1;
  }
  if (param_2 != 0x110) {
    return 0;
  }
  localize_mission_names();
  nMissionStatus = 1;
  nCaller = param_4;
  init_screen_pos(param_1);
  init_bitmap_dc(param_1);
  if (nPlayerSide == 2) {
    pSVar3 = operator_new(0x20);
    if (pSVar3 == (ShellBitmap *)0x0) goto LAB_00580a97;
    pcVar18 = "bitmap\\missbrf2.bmp";
LAB_00580a79:
    backGround = ShellBitmap::ShellBitmap(pSVar3,pcVar18,0,0);
  }
  else {
    pSVar3 = operator_new(0x20);
    if (pSVar3 != (ShellBitmap *)0x0) {
      pcVar18 = "bitmap\\missbrf.bmp";
      goto LAB_00580a79;
    }
LAB_00580a97:
    backGround = (ShellBitmap *)0x0;
  }
  pTVar7 = (TextWindow *)0x0;
  SetCurrentBackground(param_1,backGround);
  pSVar4 = operator_new(0x110);
  if (pSVar4 == (ShellButton *)0x0) {
    ulButton = (ShellButton *)0x0;
  }
  else {
    ulButton = ShellButton::ShellButton
                         (pSVar4,pHStack_1f650,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                          "BACK");
  }
  pSVar4 = operator_new(0x110);
  if (pSVar4 == (ShellButton *)0x0) {
    llButton = (ShellButton *)0x0;
  }
  else {
    llButton = ShellButton::ShellButton
                         (pSVar4,pHStack_1f650,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                          "OPTIONS");
  }
  pSVar4 = operator_new(0x110);
  if (pSVar4 == (ShellButton *)0x0) {
    urButton = (ShellButton *)0x0;
  }
  else {
    urButton = ShellButton::ShellButton
                         (pSVar4,pHStack_1f650,shell_hInstance,0xca,0xc9,0xcb,0x1e8,0,0x98,0x22,1,
                          "LAUNCH");
  }
  ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
  ShellButton::SetLabelPos(llButton,0x2f,0x1c6,0x58,0x17);
  ShellButton::SetLabelPos(urButton,0x1fb,4,0x58,0x17);
  bRepaint = 0;
  nHeight = 0xf0;
  iVar19 = 0x140;
  iVar17 = 0x25;
  iVar16 = 0x29;
  pHVar5 = GetDlgItem((HWND)pHStack_1f650,0x429);
  MoveWindow(pHVar5,iVar16,iVar17,iVar19,nHeight,bRepaint);
  if (nCaller == 1) {
    WStack_1f654 = 0;
    pHStack_1f64c = (HBRUSH)0x634088;
    while( true ) {
      iVar16 = nUsaMissionIndex;
      if (0x10 < nUsaMissionIndex) {
        iVar16 = 0x11;
      }
      if (iVar16 <= (int)WStack_1f654) break;
      sprintf(local_108,"%s",pHStack_1f64c);
      SendDlgItemMessageA((HWND)pHStack_1f650,0x429,0x181,WStack_1f654,(LPARAM)local_108);
      WStack_1f654 = WStack_1f654 + 1;
      pHStack_1f64c = (HBRUSH)((int)pHStack_1f64c + 0x404);
    }
    SendDlgItemMessageA((HWND)pHStack_1f650,0x429,0x186,0,0);
    p_Var20 = USAMissionList;
  }
  else if (nCaller == 2) {
    WStack_1f654 = 0;
    pHStack_1f64c = (HBRUSH)0x6384d0;
    while( true ) {
      iVar16 = nUssrMissionIndex;
      if (7 < nUssrMissionIndex) {
        iVar16 = 8;
      }
      if (iVar16 <= (int)WStack_1f654) break;
      sprintf(local_108,"%s",pHStack_1f64c);
      SendDlgItemMessageA((HWND)pHStack_1f650,0x429,0x181,WStack_1f654,(LPARAM)local_108);
      WStack_1f654 = WStack_1f654 + 1;
      pHStack_1f64c = (HBRUSH)((int)pHStack_1f64c + 0x404);
    }
    SendDlgItemMessageA((HWND)pHStack_1f650,0x429,0x186,0,0);
    p_Var20 = (_USAMission *)USSRMissionList;
  }
  else {
    if (nCaller != 3) goto LAB_00580d51;
    WStack_1f654 = 0;
    pHStack_1f64c = (HBRUSH)0x63a4f0;
    do {
      sprintf(local_108,"%s",pHStack_1f64c);
      SendDlgItemMessageA((HWND)pHStack_1f650,0x429,0x181,WStack_1f654,(LPARAM)local_108);
      pHStack_1f64c = (HBRUSH)((int)pHStack_1f64c + 0x400);
      WStack_1f654 = WStack_1f654 + 1;
    } while ((int)pHStack_1f64c < 0x63b8f0);
    SendDlgItemMessageA((HWND)pHStack_1f650,0x429,0x186,0,0);
    p_Var20 = (_USAMission *)TrnMissionList;
  }
  GetMissionDesc(p_Var20->cMissionName,acStack_1f608);
LAB_00580d51:
  pTVar6 = operator_new(0x1f438);
  if (pTVar6 == (TextWindow *)0x0) {
    descText = (TextWindow *)0x0;
  }
  else {
    descText = TextWindow::TextWindow(pTVar6,pHStack_1f650,acStack_1f608,0x192,0x35,0xcd,0x174,0);
  }
  TextWindow::SetTextFont(descText,defaultFont,defaultFontSize2);
  GetPlanetDesc(nCaller,0,local_108);
  GetMissionDesc(local_108,acStack_1f608);
  pTVar6 = operator_new(0x1f438);
  if (pTVar6 != (TextWindow *)0x0) {
    pTVar7 = TextWindow::TextWindow(pTVar6,pHStack_1f650,acStack_1f608,0x34,300,0x11a,100,0);
  }
  planetText = pTVar7;
  TextWindow::SetTextFont(pTVar7,defaultFont,defaultFontSize2);
  if (nPlayerSide == 2) {
    TextWindow::SetWindowTextColor(descText,0xff,1);
  }
  read_text_label("missions","back",ulButton->labelText);
  read_text_label("missions","options",llButton->labelText);
  read_text_label("missions","launch",urButton->labelText);
  return 1;
}
