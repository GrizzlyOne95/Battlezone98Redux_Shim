/*
 * Entry: 00579f23
 * Name: FailMissionDlgProc
 * Namespace: Global
 * Signature: int FailMissionDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl FailMissionDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  ShellButton *pSVar4;
  ShellButton *pSVar5;
  HWND__ *hWnd;
  UINT UVar6;
  int iVar7;
  TextWindow *pTVar8;
  HDC pHVar9;
  ShellBitmap *pSVar10;
  ShellButton *pSVar11;
  TextLabel *pTVar12;
  HGDIOBJ pvVar13;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  int extraout_EDX_06;
  int extraout_EDX_07;
  int extraout_EDX_08;
  int extraout_EDX_09;
  int extraout_EDX_10;
  ShellButton *extraout_EDX_11;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *this_03;
  ShellButton *this_04;
  ShellButton *extraout_EDX_12;
  char *pcVar14;
  uint uVar15;
  char *pcVar16;
  uint uVar17;
  bool bVar18;
  int iVar19;
  int iVar20;
  uint uStack_1f550;
  HWND__ *pHStack_1f54c;
  tagPAINTSTRUCT tStack_1f548;
  char acStack_1f508 [56];
  undefined1 auStack_1f4d0 [127944];
  CHAR local_108 [256];
  uint local_8;
  
  pSVar11 = urButton;
  local_8 = __security_cookie ^ (uint)auStack_1f4d0;
  pHStack_1f54c = param_1;
  uStack_1f550 = param_3;
  if (0x110 < param_2) {
    if (param_2 == 0x136) {
      iVar7 = 4;
LAB_0057aaf0:
      pvVar13 = GetStockObject(iVar7);
      return (int)pvVar13;
    }
    if (param_2 == 0x138) {
      SetTextColor((HDC)param_3,0x200ff00);
      SetBkMode((HDC)param_3,1);
      iVar7 = 5;
      goto LAB_0057aaf0;
    }
    if (param_2 == 0x200) {
      uVar17 = param_4 & 0xffff;
      iVar20 = 0;
      iVar19 = 1;
      uVar15 = (uint)param_4 >> 0x10;
      iVar7 = ShellButton::CheckRollOver(ulButton,uVar17,uVar15);
      ShellButton::SetButtonMode(this,iVar7,iVar19,iVar20);
      iVar20 = 0;
      iVar19 = 1;
      iVar7 = ShellButton::CheckRollOver(urButton,uVar17,uVar15);
      ShellButton::SetButtonMode(this_00,iVar7,iVar19,iVar20);
      iVar20 = 0;
      iVar19 = 1;
      iVar7 = ShellButton::CheckRollOver(llButton,uVar17,uVar15);
      ShellButton::SetButtonMode(this_01,iVar7,iVar19,iVar20);
      iVar20 = 0;
      iVar19 = 1;
      iVar7 = ShellButton::CheckRollOver(lrButton,uVar17,uVar15);
      ShellButton::SetButtonMode(this_02,iVar7,iVar19,iVar20);
      iVar20 = 0;
      iVar19 = 1;
      iVar7 = ShellButton::CheckRollOver(mainButton,uVar17,uVar15);
      ShellButton::SetButtonMode(this_03,iVar7,iVar19,iVar20);
      iVar20 = 0;
      iVar19 = 1;
      iVar7 = ShellButton::CheckRollOver(scrollUp,uVar17,uVar15);
      ShellButton::SetButtonMode(this_04,iVar7,iVar19,iVar20);
      iVar20 = 0;
      iVar19 = 1;
      iVar7 = ShellButton::CheckRollOver(scrollDown,uVar17,uVar15);
      pSVar11 = extraout_EDX_12;
LAB_0057aacb:
      ShellButton::SetButtonMode(pSVar11,iVar7,iVar19,iVar20);
      return 0;
    }
    if (param_2 == 0x201) {
      uVar15 = param_4 & 0xffff;
      iVar7 = ShellButton::CheckRollOver(urButton,uVar15,(uint)param_4 >> 0x10);
      pSVar5 = ulButton;
      if (((((iVar7 == 0) &&
            (iVar7 = ShellButton::CheckRollOver(ulButton,uVar15,extraout_EDX_05), pSVar4 = llButton,
            pSVar11 = pSVar5, iVar7 == 0)) &&
           (iVar7 = ShellButton::CheckRollOver(llButton,uVar15,extraout_EDX_06), pSVar5 = lrButton,
           pSVar11 = pSVar4, iVar7 == 0)) &&
          ((iVar7 = ShellButton::CheckRollOver(lrButton,uVar15,extraout_EDX_07), pSVar4 = mainButton
           , pSVar11 = pSVar5, iVar7 == 0 &&
           (iVar7 = ShellButton::CheckRollOver(mainButton,uVar15,extraout_EDX_08), pSVar5 = scrollUp
           , pSVar11 = pSVar4, iVar7 == 0)))) &&
         (iVar7 = ShellButton::CheckRollOver(scrollUp,uVar15,extraout_EDX_09), pSVar11 = pSVar5,
         iVar7 == 0)) {
        iVar7 = ShellButton::CheckRollOver(scrollDown,uVar15,extraout_EDX_10);
        if (iVar7 == 0) {
          return 0;
        }
        iVar20 = 0;
        iVar19 = 1;
        iVar7 = 2;
        pSVar11 = extraout_EDX_11;
      }
      else {
        iVar20 = 0;
        iVar19 = 1;
        iVar7 = 2;
      }
      goto LAB_0057aacb;
    }
    if (param_2 != 0x202) {
      return 0;
    }
    uVar15 = param_4 & 0xffff;
    iVar7 = ShellButton::CheckRollOver(urButton,uVar15,(uint)param_4 >> 0x10);
    if (iVar7 == 0) {
      iVar7 = ShellButton::CheckRollOver(ulButton,uVar15,extraout_EDX);
      if (iVar7 == 0) {
        iVar7 = ShellButton::CheckRollOver(mainButton,uVar15,extraout_EDX_00);
        if (iVar7 == 0) {
          iVar7 = ShellButton::CheckRollOver(llButton,uVar15,extraout_EDX_01);
          hWnd = pHStack_1f54c;
          if (iVar7 != 0) {
            ShowWindow((HWND)pHStack_1f54c,0);
            EnableWindow((HWND)hWnd,0);
            do_savegame(1);
            SetCurrentBackground(hWnd,backGround);
            EnableWindow((HWND)hWnd,1);
            ShowWindow((HWND)hWnd,5);
            return 0;
          }
          iVar7 = ShellButton::CheckRollOver(lrButton,uVar15,extraout_EDX_02);
          if (iVar7 != 0) {
            nReplayIntro = 0;
            nPlayCredits = 0;
            nShellMode = 0x12;
            Shell_EndDialog(pHStack_1f54c,1);
            return 0;
          }
          iVar7 = ShellButton::CheckRollOver(scrollUp,uVar15,extraout_EDX_03);
          if (iVar7 == 0) {
            iVar7 = ShellButton::CheckRollOver(scrollDown,uVar15,extraout_EDX_04);
            if (iVar7 == 0) {
              return 0;
            }
            iVar7 = result->nFontHeight;
          }
          else {
            iVar7 = -result->nFontHeight;
          }
          (**(code **)(result->_padding_ + 4))(iVar7);
          return 0;
        }
        SetRunning(2);
        nMainMenuCalled = 1;
        goto LAB_0057a86c;
      }
      iVar7 = 2;
    }
    else {
      iVar7 = 7;
    }
    SetRunning(iVar7);
LAB_0057a86c:
    nShellMode = 0;
    Shell_EndDialog(param_1,1);
    return 0;
  }
  if (param_2 != 0x110) {
    if (param_2 == 2) {
      CleanCurrentBackground();
      pSVar10 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar10);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar11 = ulButton;
      if (ulButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(ulButton);
        operator_delete(pSVar11);
        ulButton = (ShellButton *)0x0;
      }
      pSVar11 = urButton;
      if (urButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(urButton);
        operator_delete(pSVar11);
        urButton = (ShellButton *)0x0;
      }
      pSVar11 = llButton;
      if (llButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(llButton);
        operator_delete(pSVar11);
        llButton = (ShellButton *)0x0;
      }
      pSVar11 = lrButton;
      if (lrButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(lrButton);
        operator_delete(pSVar11);
        lrButton = (ShellButton *)0x0;
      }
      pTVar12 = message;
      if (message != (TextLabel *)0x0) {
        TextLabel::~TextLabel(message);
        operator_delete(pTVar12);
        message = (TextLabel *)0x0;
      }
      pTVar8 = result;
      if (result != (TextWindow *)0x0) {
        TextWindow::~TextWindow(result);
        operator_delete(pTVar8);
        result = (TextWindow *)0x0;
      }
      pSVar11 = mainButton;
      if (mainButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(mainButton);
        operator_delete(pSVar11);
        mainButton = (ShellButton *)0x0;
      }
      pSVar11 = scrollUp;
      if (scrollUp != (ShellButton *)0x0) {
        ShellButton::~ShellButton(scrollUp);
        operator_delete(pSVar11);
        scrollUp = (ShellButton *)0x0;
      }
      pSVar11 = scrollDown;
      if (scrollDown == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(scrollDown);
      operator_delete(pSVar11);
      scrollDown = (ShellButton *)0x0;
      return 0;
    }
    if (param_2 == 0xf) {
      pHVar9 = BeginPaint((HWND)param_1,&tStack_1f548);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(urButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(llButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(lrButton,(HDC__ *)pHVar9);
      TextLabel::DrawLabelText(message,(HDC__ *)pHVar9,(char *)0x0,0);
      (**(code **)result->_padding_)(pHVar9,0);
      ShellButton::UpdateButton(mainButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(scrollUp,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(scrollDown,(HDC__ *)pHVar9);
      EndPaint((HWND)pHStack_1f54c,&tStack_1f548);
      return 0;
    }
    if (param_2 != 0x14) {
      if (param_2 != 0x20) {
        if (param_2 != 0x100) {
          return 0;
        }
        uVar1._3_1_ = s_aaaabbbb_ccc__0064d284[4];
        uVar1._0_1_ = s_aaaabbbb_ccc__0064d284[1];
        uVar1._1_1_ = s_aaaabbbb_ccc__0064d284[2];
        uVar1._2_1_ = s_aaaabbbb_ccc__0064d284[3];
        uVar2._3_1_ = s_aaaabbbb_ccc__0064d284[8];
        uVar2._0_1_ = s_aaaabbbb_ccc__0064d284[5];
        uVar2._1_1_ = s_aaaabbbb_ccc__0064d284[6];
        uVar2._2_1_ = s_aaaabbbb_ccc__0064d284[7];
        uVar3._3_1_ = s_aaaabbbb_ccc__0064d284[0xc];
        uVar3._0_1_ = s_aaaabbbb_ccc__0064d284[9];
        uVar3._1_1_ = s_aaaabbbb_ccc__0064d284[10];
        uVar3._2_1_ = s_aaaabbbb_ccc__0064d284[0xb];
        s_aaaabbbb_ccc__0064d284[0xc] = s_aaaabbbb_ccc__0064d284[0xd];
        s_aaaabbbb_ccc__0064d284._0_4_ = uVar1;
        s_aaaabbbb_ccc__0064d284._4_4_ = uVar2;
        s_aaaabbbb_ccc__0064d284._8_4_ = uVar3;
        UVar6 = MapVirtualKeyA(param_3,2);
        if (UVar6 != 0x20) {
          s_aaaabbbb_ccc__0064d284[0xd] = (char)UVar6;
          return 0;
        }
        s_aaaabbbb_ccc__0064d284[0xd] = '\0';
        pcVar14 = s_aaaabbbb_ccc__0064d284 + 0xc;
        do {
          iVar7 = isalnum((int)*pcVar14);
          if ((iVar7 == 0) && (*pcVar14 != '.')) break;
          pcVar14 = pcVar14 + -1;
        } while ((char *)((int)&first + 3) < pcVar14);
        iVar7 = ItemExists(pcVar14 + 1);
        pTVar8 = result;
        if (iVar7 != 0) {
          if (result != (TextWindow *)0x0) {
            TextWindow::~TextWindow(result);
            operator_delete(pTVar8);
            result = (TextWindow *)0x0;
          }
          GetMissionDesc(pcVar14 + 1,acStack_1f508);
          pTVar8 = operator_new(0x1f438);
          if (pTVar8 == (TextWindow *)0x0) {
            result = (TextWindow *)0x0;
          }
          else {
            result = TextWindow::TextWindow
                               (pTVar8,pHStack_1f54c,acStack_1f508,0x3f,0xa5,0x202,0xe2,0);
          }
          iVar7 = TextWindow::CheckTextSize(result);
          if (iVar7 == 0) {
            ShellButton::HideButton(scrollUp,0);
            ShellButton::HideButton(scrollDown,0);
          }
          InvalidateRect((HWND)pHStack_1f54c,(RECT *)0x0,0);
        }
        builtin_strncpy(s_aaaabbbb_ccc__0064d284,"______________",0xe);
        return 0;
      }
      set_cursor(0);
      SetWindowLongA((HWND)pHStack_1f54c,0,1);
    }
    return 1;
  }
  GetUserNameA(local_108,&uStack_1f550);
  nMissionStatus = 1;
  nMissionCurrentIndex = CheckMissionIndex();
  init_screen_pos(param_1);
  init_bitmap_dc(param_1);
  if (nPlayerSide == 1) {
    if (GameObject::userObject == (GameObject *)0x0) {
      pSVar10 = operator_new(0x20);
      if (pSVar10 != (ShellBitmap *)0x0) {
        pcVar14 = "bitmap\\death.bmp";
        goto LAB_0057a340;
      }
      goto LAB_0057a34e;
    }
    pSVar10 = operator_new(0x20);
LAB_0057a334:
    if (pSVar10 == (ShellBitmap *)0x0) goto LAB_0057a34e;
    pcVar14 = "bitmap\\failed.bmp";
LAB_0057a340:
    backGround = ShellBitmap::ShellBitmap(pSVar10,pcVar14,0,0);
  }
  else {
    if (nPlayerSide != 2) {
      pSVar10 = operator_new(0x20);
      goto LAB_0057a334;
    }
    if (GameObject::userObject != (GameObject *)0x0) {
      pSVar10 = operator_new(0x20);
      if (pSVar10 == (ShellBitmap *)0x0) goto LAB_0057a34e;
      pcVar14 = "bitmap\\svtlose.bmp";
      goto LAB_0057a340;
    }
    pSVar10 = operator_new(0x20);
    if (pSVar10 != (ShellBitmap *)0x0) {
      pcVar14 = "bitmap\\svtdeath.bmp";
      goto LAB_0057a340;
    }
LAB_0057a34e:
    backGround = (ShellBitmap *)0x0;
  }
  SetCurrentBackground(pHStack_1f54c,backGround);
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    ulButton = (ShellButton *)0x0;
  }
  else {
    ulButton = ShellButton::ShellButton
                         (pSVar11,pHStack_1f54c,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                          "END MISSION");
  }
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    urButton = (ShellButton *)0x0;
  }
  else {
    urButton = ShellButton::ShellButton
                         (pSVar11,pHStack_1f54c,shell_hInstance,0xca,0xc9,0xcb,0x1e8,0,0x98,0x22,1,
                          "REPLAY MISSION");
  }
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    llButton = (ShellButton *)0x0;
  }
  else {
    llButton = ShellButton::ShellButton
                         (pSVar11,pHStack_1f54c,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                          "SAVE GAME");
  }
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    lrButton = (ShellButton *)0x0;
  }
  else {
    lrButton = ShellButton::ShellButton
                         (pSVar11,pHStack_1f54c,shell_hInstance,0xc4,0xc3,0xc5,0x1b9,0x1bd,199,0x22,
                          1,"LOAD GAME");
  }
  ShellButton::SetLabelPos(lrButton,0x1fb,0x1c4,0x58,0x17);
  ShellButton::SetLabelPos(llButton,0x2f,0x1c6,0x58,0x17);
  ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
  ShellButton::SetLabelPos(urButton,0x1fb,4,0x58,0x17);
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    mainButton = (ShellButton *)0x0;
  }
  else {
    mainButton = ShellButton::ShellButton
                           (pSVar11,pHStack_1f54c,shell_hInstance,0x119,0x118,0x11a,0xef,0,0xa4,0x1e
                            ,1,"To Main Menu");
  }
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    scrollUp = (ShellButton *)0x0;
  }
  else {
    scrollUp = ShellButton::ShellButton
                         (pSVar11,pHStack_1f54c,shell_hInstance,0x82c,0x819,0x7ff,0x24e,0x176,0x13,
                          0x12,0,(char *)0x0);
  }
  pSVar11 = operator_new(0x110);
  if (pSVar11 == (ShellButton *)0x0) {
    scrollDown = (ShellButton *)0x0;
  }
  else {
    scrollDown = ShellButton::ShellButton
                           (pSVar11,pHStack_1f54c,shell_hInstance,0x82d,0x818,0x800,0x24e,0x188,0x13
                            ,0x12,0,(char *)0x0);
  }
  GetMissionDesc(cMissionResult,acStack_1f508);
  iVar7 = 0xf;
  bVar18 = true;
  pcVar14 = acStack_1f508;
  pcVar16 = "NO DESCRIPTION";
  do {
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    bVar18 = *pcVar14 == *pcVar16;
    pcVar14 = pcVar14 + 1;
    pcVar16 = pcVar16 + 1;
  } while (bVar18);
  if (bVar18) {
    iVar7 = 6;
    if (GameObject::userObject == (GameObject *)0x0) {
      pcVar14 = "You were killed in action.";
      pcVar16 = acStack_1f508;
      for (; iVar7 != 0; iVar7 = iVar7 + -1) {
        *(undefined4 *)pcVar16 = *(undefined4 *)pcVar14;
        pcVar14 = pcVar14 + 4;
        pcVar16 = pcVar16 + 4;
      }
      *(undefined2 *)pcVar16 = *(undefined2 *)pcVar14;
      pcVar16[2] = pcVar14[2];
      pcVar14 = "killed";
    }
    else {
      pcVar14 = "The Mission was failed!";
      pcVar16 = acStack_1f508;
      for (; iVar7 != 0; iVar7 = iVar7 + -1) {
        *(undefined4 *)pcVar16 = *(undefined4 *)pcVar14;
        pcVar14 = pcVar14 + 4;
        pcVar16 = pcVar16 + 4;
      }
      pcVar14 = "failed";
    }
    read_text_label("fail_mission",pcVar14,acStack_1f508);
  }
  pTVar12 = operator_new(0x128);
  if (pTVar12 == (TextLabel *)0x0) {
    message = (TextLabel *)0x0;
  }
  else {
    message = TextLabel::TextLabel(pTVar12,pHStack_1f54c,"MISSION FAILED",0xbf,0x6b,0x102,0x1c,0);
  }
  pTVar8 = operator_new(0x1f438);
  if (pTVar8 == (TextWindow *)0x0) {
    result = (TextWindow *)0x0;
  }
  else {
    result = TextWindow::TextWindow(pTVar8,pHStack_1f54c,acStack_1f508,0x3f,0xa5,0x202,0xe2,0);
  }
  iVar7 = TextWindow::CheckTextSize(result);
  if (iVar7 == 0) {
    ShellButton::HideButton(scrollUp,0);
    ShellButton::HideButton(scrollDown,0);
  }
  read_text_label("fail_mission","message",message->textData);
  read_text_label("fail_mission","save_game",llButton->labelText);
  read_text_label("fail_mission","load_game",lrButton->labelText);
  read_text_label("fail_mission","end_mission",ulButton->labelText);
  read_text_label("fail_mission","replay_mission",urButton->labelText);
  read_text_label("missions","main_menu",mainButton->labelText);
  iVar7 = 6;
  bVar18 = true;
  pcVar14 = local_108;
  pcVar16 = "lchen";
  do {
    if (iVar7 == 0) break;
    iVar7 = iVar7 + -1;
    bVar18 = *pcVar14 == *pcVar16;
    pcVar14 = pcVar14 + 1;
    pcVar16 = pcVar16 + 1;
  } while (bVar18);
  if (bVar18) {
    pcVar14 = "MISSION WAS A FAILURE";
  }
  else {
    iVar7 = 9;
    bVar18 = true;
    pcVar14 = local_108;
    pcVar16 = "agoldman";
    do {
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      bVar18 = *pcVar14 == *pcVar16;
      pcVar14 = pcVar14 + 1;
      pcVar16 = pcVar16 + 1;
    } while (bVar18);
    if (bVar18) {
      pcVar14 = "YOU DROPPED THE BALL ANDREW";
    }
    else {
      iVar7 = 9;
      bVar18 = true;
      pcVar14 = local_108;
      pcVar16 = "gcollins";
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar18 = *pcVar14 == *pcVar16;
        pcVar14 = pcVar14 + 1;
        pcVar16 = pcVar16 + 1;
      } while (bVar18);
      if (bVar18) {
        pcVar14 = "NICE ONE GEORGE";
      }
      else {
        iVar7 = 10;
        bVar18 = true;
        pcVar14 = local_108;
        pcVar16 = "jandersen";
        do {
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          bVar18 = *pcVar14 == *pcVar16;
          pcVar14 = pcVar14 + 1;
          pcVar16 = pcVar16 + 1;
        } while (bVar18);
        if (bVar18) {
          pcVar14 = "BETTER LUCK NEXT TIME JENS";
        }
        else {
          iVar7 = 7;
          bVar18 = true;
          pcVar14 = local_108;
          pcVar16 = "wstahl";
          do {
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            bVar18 = *pcVar14 == *pcVar16;
            pcVar14 = pcVar14 + 1;
            pcVar16 = pcVar16 + 1;
          } while (bVar18);
          if (bVar18) {
            pcVar14 = "THE MANOX HAS FALLEN";
          }
          else {
            iVar7 = 7;
            bVar18 = true;
            pcVar14 = local_108;
            pcVar16 = "gsutty";
            do {
              if (iVar7 == 0) break;
              iVar7 = iVar7 + -1;
              bVar18 = *pcVar14 == *pcVar16;
              pcVar14 = pcVar14 + 1;
              pcVar16 = pcVar16 + 1;
            } while (bVar18);
            if (!bVar18) goto LAB_0057a7d2;
            pcVar14 = "WELCOME TO GRAPHICS HELPS ALOT";
          }
        }
      }
    }
  }
  TextLabel::SetLabelText(message,pcVar14);
LAB_0057a7d2:
  SetFocus((HWND)pHStack_1f54c);
  return 0;
}
