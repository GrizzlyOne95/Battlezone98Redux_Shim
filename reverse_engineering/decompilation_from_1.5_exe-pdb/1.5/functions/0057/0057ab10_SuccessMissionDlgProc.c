/*
 * Entry: 0057ab10
 * Name: SuccessMissionDlgProc
 * Namespace: Global
 * Signature: int SuccessMissionDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl SuccessMissionDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  ShellButton *pSVar4;
  ShellButton *pSVar5;
  UINT UVar6;
  int iVar7;
  ShellBitmap *pSVar8;
  HDC pHVar9;
  ShellButton *pSVar10;
  TextLabel *pTVar11;
  TextWindow *pTVar12;
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
  ShellButton *extraout_EDX_09;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *this_03;
  ShellButton *extraout_EDX_10;
  char *pcVar14;
  uint uVar15;
  char *pcVar16;
  uint uVar17;
  bool bVar18;
  int iVar19;
  char *pcVar20;
  int iVar21;
  char *pcStack_1f550;
  tagPAINTSTRUCT tStack_1f548;
  char acStack_1f508 [56];
  undefined1 auStack_1f4d0 [127944];
  char local_108 [256];
  uint local_8;
  
  pSVar10 = urButton;
  local_8 = __security_cookie ^ (uint)auStack_1f4d0;
  if (0x110 < param_2) {
    if (param_2 == 0x136) {
      iVar7 = 4;
    }
    else {
      if (param_2 != 0x138) {
        if (param_2 == 0x200) {
          uVar17 = param_4 & 0xffff;
          iVar21 = 0;
          iVar19 = 1;
          uVar15 = (uint)param_4 >> 0x10;
          iVar7 = ShellButton::CheckRollOver(urButton,uVar17,uVar15);
          ShellButton::SetButtonMode(this,iVar7,iVar19,iVar21);
          iVar21 = 0;
          iVar19 = 1;
          iVar7 = ShellButton::CheckRollOver(lrButton,uVar17,uVar15);
          ShellButton::SetButtonMode(this_00,iVar7,iVar19,iVar21);
          iVar21 = 0;
          iVar19 = 1;
          iVar7 = ShellButton::CheckRollOver(llButton,uVar17,uVar15);
          ShellButton::SetButtonMode(this_01,iVar7,iVar19,iVar21);
          iVar21 = 0;
          iVar19 = 1;
          iVar7 = ShellButton::CheckRollOver(mainButton,uVar17,uVar15);
          ShellButton::SetButtonMode(this_02,iVar7,iVar19,iVar21);
          iVar21 = 0;
          iVar19 = 1;
          iVar7 = ShellButton::CheckRollOver(scrollUp,uVar17,uVar15);
          ShellButton::SetButtonMode(this_03,iVar7,iVar19,iVar21);
          iVar21 = 0;
          iVar19 = 1;
          iVar7 = ShellButton::CheckRollOver(scrollDown,uVar17,uVar15);
          pSVar10 = extraout_EDX_10;
        }
        else {
          if (param_2 != 0x201) {
            if (param_2 != 0x202) {
              return 0;
            }
            uVar15 = param_4 & 0xffff;
            iVar7 = ShellButton::CheckRollOver(urButton,uVar15,(uint)param_4 >> 0x10);
            if (iVar7 == 0) {
              iVar7 = ShellButton::CheckRollOver(mainButton,uVar15,extraout_EDX);
              if (iVar7 == 0) {
                iVar7 = ShellButton::CheckRollOver(llButton,uVar15,extraout_EDX_00);
                if (iVar7 != 0) {
                  ShowWindow((HWND)param_1,0);
                  EnableWindow((HWND)param_1,0);
                  do_savegame(1);
                  pSVar8 = backGround;
                  if (giftBackground != (ShellBitmap *)0x0) {
                    pSVar8 = giftBackground;
                  }
                  SetCurrentBackground(param_1,pSVar8);
                  EnableWindow((HWND)param_1,1);
                  ShowWindow((HWND)param_1,5);
                  return 0;
                }
                iVar7 = ShellButton::CheckRollOver(lrButton,uVar15,extraout_EDX_01);
                if (iVar7 != 0) {
                  SetCurrentBackground(param_1,backGround);
                  iVar7 = TextWindow::CheckTextSize(result);
                  if (iVar7 != 0) {
                    ShellButton::ShowButton(scrollUp,0);
                    ShellButton::ShowButton(scrollDown,0);
                  }
                  ShellButton::HideButton(lrButton,0);
                  ShellButton::ShowButton(urButton,0);
                  ShellButton::ShowButton(llButton,0);
                  ShellButton::ShowButton(mainButton,0);
                  TextLabel::ShowLabelText(message,0);
                  TextWindow::ShowWindowText(result,0);
                  pHVar9 = GetDC((HWND)param_1);
                  ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar9);
                  ShellButton::UpdateButton(urButton);
                  ShellButton::UpdateButton(llButton);
                  ShellButton::UpdateButton(mainButton);
                  ShellButton::UpdateButton(scrollUp);
                  ShellButton::UpdateButton(scrollDown);
                  TextLabel::DrawLabelText(message,(char *)0x0,0);
                  (**(code **)(result->_padding_ + 4))(0);
                  ReleaseDC((HWND)param_1,pHVar9);
                  pSVar8 = giftBackground;
                  if (giftBackground == (ShellBitmap *)0x0) {
                    return 0;
                  }
                  ShellBitmap::~ShellBitmap(giftBackground);
                  operator_delete(pSVar8);
                  giftBackground = (ShellBitmap *)0x0;
                  return 0;
                }
                iVar7 = ShellButton::CheckRollOver(scrollUp,uVar15,extraout_EDX_02);
                if (iVar7 == 0) {
                  iVar7 = ShellButton::CheckRollOver(scrollDown,uVar15,extraout_EDX_03);
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
            }
            else {
              SetRunning(2);
            }
            Shell_EndDialog(param_1,1);
            return 0;
          }
          uVar15 = param_4 & 0xffff;
          iVar7 = ShellButton::CheckRollOver(urButton,uVar15,(uint)param_4 >> 0x10);
          pSVar4 = lrButton;
          if ((((iVar7 == 0) &&
               (iVar7 = ShellButton::CheckRollOver(lrButton,uVar15,extraout_EDX_04),
               pSVar5 = llButton, pSVar10 = pSVar4, iVar7 == 0)) &&
              (iVar7 = ShellButton::CheckRollOver(llButton,uVar15,extraout_EDX_05),
              pSVar4 = mainButton, pSVar10 = pSVar5, iVar7 == 0)) &&
             ((iVar7 = ShellButton::CheckRollOver(mainButton,uVar15,extraout_EDX_06),
              pSVar5 = scrollUp, pSVar10 = pSVar4, iVar7 == 0 &&
              (iVar7 = ShellButton::CheckRollOver(scrollUp,uVar15,extraout_EDX_07), pSVar10 = pSVar5
              , iVar7 == 0)))) {
            iVar7 = ShellButton::CheckRollOver(scrollDown,uVar15,extraout_EDX_08);
            if (iVar7 == 0) {
              return 0;
            }
            iVar21 = 0;
            iVar19 = 1;
            iVar7 = 2;
            pSVar10 = extraout_EDX_09;
          }
          else {
            iVar21 = 0;
            iVar19 = 1;
            iVar7 = 2;
          }
        }
        ShellButton::SetButtonMode(pSVar10,iVar7,iVar19,iVar21);
        return 0;
      }
      SetTextColor((HDC)param_3,0x200ff00);
      SetBkMode((HDC)param_3,1);
      iVar7 = 5;
    }
    pvVar13 = GetStockObject(iVar7);
    return (int)pvVar13;
  }
  if (param_2 != 0x110) {
    if (param_2 == 2) {
      CleanCurrentBackground();
      pSVar8 = eeBackground;
      if (eeBackground != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(eeBackground);
        operator_delete(pSVar8);
        eeBackground = (ShellBitmap *)0x0;
      }
      pSVar8 = giftBackground;
      if (giftBackground != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(giftBackground);
        operator_delete(pSVar8);
        giftBackground = (ShellBitmap *)0x0;
      }
      pSVar8 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar8);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar10 = urButton;
      if (urButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(urButton);
        operator_delete(pSVar10);
        urButton = (ShellButton *)0x0;
      }
      pSVar10 = llButton;
      if (llButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(llButton);
        operator_delete(pSVar10);
        llButton = (ShellButton *)0x0;
      }
      pSVar10 = lrButton;
      if (lrButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(lrButton);
        operator_delete(pSVar10);
        lrButton = (ShellButton *)0x0;
      }
      pTVar11 = message;
      if (message != (TextLabel *)0x0) {
        TextLabel::~TextLabel(message);
        operator_delete(pTVar11);
        message = (TextLabel *)0x0;
      }
      pTVar12 = result;
      if (result != (TextWindow *)0x0) {
        TextWindow::~TextWindow(result);
        operator_delete(pTVar12);
        result = (TextWindow *)0x0;
      }
      pSVar10 = mainButton;
      if (mainButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(mainButton);
        operator_delete(pSVar10);
        mainButton = (ShellButton *)0x0;
      }
      pSVar10 = scrollUp;
      if (scrollUp != (ShellButton *)0x0) {
        ShellButton::~ShellButton(scrollUp);
        operator_delete(pSVar10);
        scrollUp = (ShellButton *)0x0;
      }
      pSVar10 = scrollDown;
      if (scrollDown == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(scrollDown);
      operator_delete(pSVar10);
      scrollDown = (ShellButton *)0x0;
      return 0;
    }
    if (param_2 == 0xf) {
      pHVar9 = BeginPaint((HWND)param_1,&tStack_1f548);
      if (giftBackground == (ShellBitmap *)0x0) {
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar9);
      }
      else {
        ShellBitmap::LineBlt(giftBackground,(HDC__ *)pHVar9);
      }
      if (eeBackground != (ShellBitmap *)0x0) {
        ShellBitmap::BltBitmap(eeBackground,(HDC__ *)pHVar9);
      }
      pSVar8 = backGround;
      if (giftBackground != (ShellBitmap *)0x0) {
        pSVar8 = giftBackground;
      }
      SetCurrentBackground(param_1,pSVar8);
      ShellButton::UpdateButton(urButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(lrButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(llButton,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(mainButton,(HDC__ *)pHVar9);
      TextLabel::DrawLabelText(message,(HDC__ *)pHVar9,(char *)0x0,0);
      (**(code **)result->_padding_)(pHVar9,0);
      ShellButton::UpdateButton(scrollUp,(HDC__ *)pHVar9);
      ShellButton::UpdateButton(scrollDown,(HDC__ *)pHVar9);
      EndPaint((HWND)param_1,&tStack_1f548);
      return 0;
    }
    if (param_2 == 0x14) {
      return 1;
    }
    if (param_2 == 0x20) {
      set_cursor(0);
      SetWindowLongA((HWND)param_1,0,1);
      return 1;
    }
    if (param_2 != 0x100) {
      return 0;
    }
    uVar2._3_1_ = testStr[4];
    uVar2._0_1_ = testStr[1];
    uVar2._1_1_ = testStr[2];
    uVar2._2_1_ = testStr[3];
    uVar3._3_1_ = testStr[8];
    uVar3._0_1_ = testStr[5];
    uVar3._1_1_ = testStr[6];
    uVar3._2_1_ = testStr[7];
    testStr._0_4_ = uVar2;
    testStr._4_4_ = uVar3;
    UVar6 = MapVirtualKeyA(param_3,2);
    testStr[8] = (char)UVar6;
    iVar7 = strncmp(testStr,"WESLEY",6);
    if (iVar7 == 0) {
      pcStack_1f550 = "ee012397.bmp";
      TextWindow::HideWindowText(result,1);
      TextLabel::HideLabelText(message,1);
      GetMissionDesc("bradp.des",acStack_1f508);
      pTVar12 = result;
      TextWindow::SetWindowTextA(result,acStack_1f508);
      pcVar20 = "Pickering, you\'re a Marvel!";
LAB_0057ac15:
      TextLabel::SetLabelText(message,pcVar20);
      TextWindow::ShowWindowText(pTVar12,1);
      TextLabel::ShowLabelText(message,1);
      ShellButton::ShowButton(scrollUp,1);
      ShellButton::ShowButton(scrollDown,1);
      pSVar8 = eeBackground;
      builtin_strncpy(testStr,"         ",9);
      if (eeBackground != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(eeBackground);
        operator_delete(pSVar8);
        eeBackground = (ShellBitmap *)0x0;
      }
      iVar7 = ItemExists(pcStack_1f550);
      if (iVar7 != 0) {
        pSVar8 = operator_new(0x20);
        if (pSVar8 == (ShellBitmap *)0x0) {
          eeBackground = (ShellBitmap *)0x0;
        }
        else {
          eeBackground = ShellBitmap::ShellBitmap(pSVar8,pcStack_1f550,10,10);
        }
      }
      RedrawWindow((HWND)param_1,(RECT *)0x0,(HRGN)0x0,0x101);
      return 0;
    }
    iVar7 = strncmp(testStr,linusCode,8);
    if (iVar7 == 0) {
      ShellPlaySound("ping.wav",100,0,-1);
      TextWindow::HideWindowText(result,1);
      TextLabel::HideLabelText(message,1);
      GetMissionDesc("linus.des",acStack_1f508);
      pTVar12 = result;
      TextWindow::SetWindowTextA(result,acStack_1f508);
      pcVar20 = "Notes from Newt";
    }
    else {
      iVar7 = strncmp(testStr,matthewCode,8);
      if (iVar7 == 0) {
        ShellPlaySound("ping.wav",100,0,-1);
        TextWindow::HideWindowText(result,1);
        TextLabel::HideLabelText(message,1);
        GetMissionDesc("matthew.des",acStack_1f508);
        pTVar12 = result;
        TextWindow::SetWindowTextA(result,acStack_1f508);
        pcVar20 = "Notes from Monolith";
      }
      else {
        iVar7 = strncmp(testStr,careyCode,8);
        if (iVar7 == 0) {
          ShellPlaySound("ping.wav",100,0,-1);
          TextWindow::HideWindowText(result,1);
          TextLabel::HideLabelText(message,1);
          GetMissionDesc("carey.des",acStack_1f508);
          pTVar12 = result;
          TextWindow::SetWindowTextA(result,acStack_1f508);
          pcVar20 = "Notes from Damien";
        }
        else {
          iVar7 = strncmp(testStr,gSuttyCode,8);
          if (iVar7 == 0) {
            pcStack_1f550 = "gs123.bmp";
            ShellPlaySound("pissed.wav",100,0,-1);
            TextWindow::HideWindowText(result,1);
            TextLabel::HideLabelText(message,1);
            GetMissionDesc("george.des",acStack_1f508);
            pTVar12 = result;
            TextWindow::SetWindowTextA(result,acStack_1f508);
            pcVar20 = "Welcome to Graphics Software Labs";
            goto LAB_0057ac15;
          }
          iVar7 = strncmp(testStr,gCollinsCode,8);
          if (iVar7 == 0) {
            ShellPlaySound("ping.wav",100,0,-1);
            TextWindow::HideWindowText(result,1);
            TextLabel::HideLabelText(message,1);
            GetMissionDesc("georgec.des",acStack_1f508);
            pTVar12 = result;
            TextWindow::SetWindowTextA(result,acStack_1f508);
            pcVar20 = "Notes from GMoney";
          }
          else {
            iVar7 = strncmp(testStr,jerryCode,8);
            if (iVar7 == 0) {
              ShellPlaySound("ping.wav",100,0,-1);
              TextWindow::HideWindowText(result,1);
              TextLabel::HideLabelText(message,1);
              GetMissionDesc("jerry.des",acStack_1f508);
              pTVar12 = result;
              TextWindow::SetWindowTextA(result,acStack_1f508);
              pcVar20 = "Notes from Jerry";
            }
            else {
              iVar7 = strncmp(testStr,manoxCode,8);
              if (iVar7 == 0) {
                ShellPlaySound("ping.wav",100,0,-1);
                TextWindow::HideWindowText(result,1);
                TextLabel::HideLabelText(message,1);
                GetMissionDesc("wils.des",acStack_1f508);
                pTVar12 = result;
                TextWindow::SetWindowTextA(result,acStack_1f508);
                pcVar20 = "YOU MUST FEAR THE MANOX";
              }
              else {
                iVar7 = strncmp(testStr,andrewCode,8);
                if (iVar7 == 0) {
                  ShellPlaySound("ping.wav",100,0,-1);
                  TextWindow::HideWindowText(result,1);
                  TextLabel::HideLabelText(message,1);
                  GetMissionDesc("andrewg.des",acStack_1f508);
                  pTVar12 = result;
                  TextWindow::SetWindowTextA(result,acStack_1f508);
                  pcVar20 = "Notes from Roadkill";
                }
                else {
                  iVar7 = strncmp(testStr,willCode,8);
                  if (iVar7 == 0) {
                    ShellPlaySound("ping.wav",100,0,-1);
                    TextWindow::HideWindowText(result,1);
                    TextLabel::HideLabelText(message,1);
                    GetMissionDesc("wilr.des",acStack_1f508);
                    pTVar12 = result;
                    TextWindow::SetWindowTextA(result,acStack_1f508);
                    pcVar20 = "Notes from Will";
                  }
                  else {
                    iVar7 = strncmp(testStr,arkinCode,8);
                    if (iVar7 == 0) {
                      ShellPlaySound("ping.wav",100,0,-1);
                      TextWindow::HideWindowText(result,1);
                      TextLabel::HideLabelText(message,1);
                      GetMissionDesc("mikea.des",acStack_1f508);
                      pTVar12 = result;
                      TextWindow::SetWindowTextA(result,acStack_1f508);
                      pcVar20 = "Notes from Arkin";
                    }
                    else {
                      iVar7 = strncmp(testStr,kenCode,8);
                      if (iVar7 == 0) {
                        ShellPlaySound("ping.wav",100,0,-1);
                        TextWindow::HideWindowText(result,1);
                        TextLabel::HideLabelText(message,1);
                        GetMissionDesc("ken.des",acStack_1f508);
                        pTVar12 = result;
                        TextWindow::SetWindowTextA(result,acStack_1f508);
                        pcVar20 = "Notes from the Code Elf";
                      }
                      else {
                        iVar7 = strncmp(testStr,jensCode,8);
                        if (iVar7 == 0) {
                          ShellPlaySound("ping.wav",100,0,-1);
                          TextWindow::HideWindowText(result,1);
                          TextLabel::HideLabelText(message,1);
                          GetMissionDesc("jens.des",acStack_1f508);
                          pTVar12 = result;
                          TextWindow::SetWindowTextA(result,acStack_1f508);
                          pcVar20 = "Thanks from Jens";
                        }
                        else {
                          iVar7 = strncmp(testStr,brianCode,8);
                          if (iVar7 != 0) {
                            return 0;
                          }
                          ShellPlaySound("ping.wav",100,0,-1);
                          TextWindow::HideWindowText(result,1);
                          TextLabel::HideLabelText(message,1);
                          GetMissionDesc("briand.des",acStack_1f508);
                          pTVar12 = result;
                          TextWindow::SetWindowTextA(result,acStack_1f508);
                          pcVar20 = "Thanks from Brian";
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    TextLabel::SetLabelText(message,pcVar20);
    TextWindow::ShowWindowText(pTVar12,1);
    TextLabel::ShowLabelText(message,1);
    ShellButton::ShowButton(scrollUp,1);
    ShellButton::ShowButton(scrollDown,1);
    return 0;
  }
  nLastMission = 0;
  nLastUSAMission = 0;
  nMissionCurrentIndex = CheckMissionIndex();
  giftBackground = (ShellBitmap *)0x0;
  if (nPlayerSide == 1) {
    if (nOldMissionMode == 0) {
      pcVar20 = USAMissionList[nMissionCurrentIndex].cMissionGift;
      iVar7 = 5;
      bVar18 = true;
      pcVar14 = pcVar20;
      pcVar16 = "NULL";
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar18 = *pcVar14 == *pcVar16;
        pcVar14 = pcVar14 + 1;
        pcVar16 = pcVar16 + 1;
      } while (bVar18);
      if (!bVar18) {
        iVar7 = -(int)pcVar20;
        do {
          cVar1 = *pcVar20;
          pcVar20[(int)(local_108 + iVar7)] = cVar1;
          pcVar20 = pcVar20 + 1;
        } while (cVar1 != '\0');
        goto LAB_0057b576;
      }
    }
  }
  else if (nPlayerSide == 2) {
    if (nOldMissionMode == 0) {
      pcVar20 = USSRMissionList[nMissionCurrentIndex].cMissionGift;
      iVar7 = 5;
      bVar18 = true;
      pcVar14 = pcVar20;
      pcVar16 = "NULL";
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar18 = *pcVar14 == *pcVar16;
        pcVar14 = pcVar14 + 1;
        pcVar16 = pcVar16 + 1;
      } while (bVar18);
      if (!bVar18) {
        iVar7 = -(int)pcVar20;
        do {
          cVar1 = *pcVar20;
          pcVar20[(int)(local_108 + iVar7)] = cVar1;
          pcVar20 = pcVar20 + 1;
        } while (cVar1 != '\0');
LAB_0057b576:
        pSVar8 = operator_new(0x20);
        if (pSVar8 == (ShellBitmap *)0x0) {
          giftBackground = (ShellBitmap *)0x0;
        }
        else {
          giftBackground = ShellBitmap::ShellBitmap(pSVar8,local_108,0,0);
        }
      }
    }
  }
  else if ((nPlayerSide == 3) && (nOldMissionMode == 0)) {
    pcVar20 = TrnMissionList[nMissionCurrentIndex].cMissionGift;
    iVar7 = 5;
    bVar18 = true;
    pcVar14 = pcVar20;
    pcVar16 = "NULL";
    do {
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      bVar18 = *pcVar14 == *pcVar16;
      pcVar14 = pcVar14 + 1;
      pcVar16 = pcVar16 + 1;
    } while (bVar18);
    if (!bVar18) {
      iVar7 = -(int)pcVar20;
      do {
        cVar1 = *pcVar20;
        pcVar20[(int)(local_108 + iVar7)] = cVar1;
        pcVar20 = pcVar20 + 1;
      } while (cVar1 != '\0');
      goto LAB_0057b576;
    }
  }
  nMissionStatus = 2;
  init_screen_pos(param_1);
  init_bitmap_dc(param_1);
  if ((nPlayerSide == 1) || (nPlayerSide != 2)) {
    pSVar8 = operator_new(0x20);
    if (pSVar8 != (ShellBitmap *)0x0) {
      pcVar20 = "bitmap\\win.bmp";
      goto LAB_0057b5f0;
    }
LAB_0057b5fe:
    backGround = (ShellBitmap *)0x0;
  }
  else {
    pSVar8 = operator_new(0x20);
    if (pSVar8 == (ShellBitmap *)0x0) goto LAB_0057b5fe;
    pcVar20 = "bitmap\\svtwin.bmp";
LAB_0057b5f0:
    backGround = ShellBitmap::ShellBitmap(pSVar8,pcVar20,0,0);
  }
  pSVar10 = operator_new(0x110);
  if (pSVar10 == (ShellButton *)0x0) {
    urButton = (ShellButton *)0x0;
  }
  else {
    urButton = ShellButton::ShellButton
                         (pSVar10,param_1,shell_hInstance,0xca,0xc9,0xcb,0x1e8,0,0x98,0x22,1,
                          "NEXT MISSION");
  }
  pSVar10 = operator_new(0x110);
  if (pSVar10 == (ShellButton *)0x0) {
    lrButton = (ShellButton *)0x0;
  }
  else {
    lrButton = ShellButton::ShellButton
                         (pSVar10,param_1,shell_hInstance,0xc4,0xc3,0xc5,0x1b9,0x1bd,199,0x22,1,
                          "Mission Result");
  }
  pSVar10 = operator_new(0x110);
  if (pSVar10 == (ShellButton *)0x0) {
    llButton = (ShellButton *)0x0;
  }
  else {
    llButton = ShellButton::ShellButton
                         (pSVar10,param_1,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                          "SAVE GAME");
  }
  ShellButton::SetLabelPos(llButton,0x2f,0x1c6,0x58,0x17);
  ShellButton::SetLabelPos(lrButton,0x1fb,0x1c4,0x58,0x17);
  ShellButton::SetLabelPos(urButton,0x1fb,4,0x58,0x17);
  read_text_label("win_mission","save_game",llButton->labelText);
  pSVar10 = operator_new(0x110);
  if (pSVar10 == (ShellButton *)0x0) {
    scrollUp = (ShellButton *)0x0;
  }
  else {
    scrollUp = ShellButton::ShellButton
                         (pSVar10,param_1,shell_hInstance,0x82c,0x819,0x7ff,0x24e,0x176,0x13,0x12,0,
                          (char *)0x0);
  }
  pSVar10 = operator_new(0x110);
  if (pSVar10 == (ShellButton *)0x0) {
    scrollDown = (ShellButton *)0x0;
  }
  else {
    scrollDown = ShellButton::ShellButton
                           (pSVar10,param_1,shell_hInstance,0x82d,0x818,0x800,0x24e,0x188,0x13,0x12,
                            0,(char *)0x0);
  }
  pSVar10 = operator_new(0x110);
  if (pSVar10 == (ShellButton *)0x0) {
    mainButton = (ShellButton *)0x0;
  }
  else {
    mainButton = ShellButton::ShellButton
                           (pSVar10,param_1,shell_hInstance,0x119,0x118,0x11a,0xef,0,0xa4,0x1e,1,
                            "To Main Menu");
  }
  read_text_label("win_mission","next_mission",urButton->labelText);
  read_text_label("win_mission","mission_result",lrButton->labelText);
  read_text_label("missions","main_menu",mainButton->labelText);
  pSVar10 = urButton;
  if (nPlayerSide == 1) {
    if (nMissionCurrentIndex != 0x10) goto LAB_0057b896;
    nLastUSAMission = 1;
  }
  else {
    if (nPlayerSide == 2) {
      bVar18 = nMissionCurrentIndex == 7;
    }
    else {
      if (nPlayerSide != 3) goto LAB_0057b896;
      bVar18 = nMissionCurrentIndex == 3;
    }
    if (!bVar18) goto LAB_0057b896;
  }
  nLastMission = 1;
LAB_0057b896:
  if (nOldMissionMode != 0) {
    nLastMission = 1;
  }
  if (nLastMission != 0) {
    ShellButton::SetLabelText(urButton,"END MISSION");
    read_text_label("win_mission","end_mission",pSVar10->labelText);
    nLastMission = 0;
  }
  GetMissionDesc(cMissionResult,acStack_1f508);
  pTVar11 = operator_new(0x128);
  if (pTVar11 == (TextLabel *)0x0) {
    message = (TextLabel *)0x0;
  }
  else {
    message = TextLabel::TextLabel(pTVar11,param_1,"MISSION COMPLETED",0xbf,0x6b,0x102,0x1c,0);
  }
  read_text_label("win_mission","message",message->textData);
  pTVar12 = operator_new(0x1f438);
  if (pTVar12 == (TextWindow *)0x0) {
    result = (TextWindow *)0x0;
  }
  else {
    result = TextWindow::TextWindow(pTVar12,param_1,acStack_1f508,0x3f,0x91,0x202,300,0);
  }
  iVar7 = TextWindow::CheckTextSize(result);
  if (iVar7 == 0) {
    ShellButton::HideButton(scrollUp,0);
    ShellButton::HideButton(scrollDown,0);
  }
  if (nLastUSAMission == 0) {
    pSVar10 = lrButton;
    if (giftBackground != (ShellBitmap *)0x0) {
      ShellButton::HideButton(urButton,0);
      ShellButton::HideButton(llButton,0);
      TextLabel::HideLabelText(message,1);
      TextWindow::HideWindowText(result,1);
      ShellButton::HideButton(mainButton,0);
      ShellButton::HideButton(scrollUp,0);
      pSVar10 = scrollDown;
    }
  }
  else {
    nLastUSAMission = 0;
    ShellButton::HideButton(lrButton,0);
    TextLabel::HideLabelText(message,1);
    TextWindow::HideWindowText(result,1);
    pSVar10 = mainButton;
  }
  ShellButton::HideButton(pSVar10,0);
  eeBackground = (ShellBitmap *)0x0;
  SetFocus((HWND)param_1);
  return 0;
}
