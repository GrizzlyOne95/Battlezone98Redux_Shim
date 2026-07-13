/*
 * Entry: 0057ebeb
 * Name: UssrMissionsDlgProc
 * Namespace: Global
 * Signature: int UssrMissionsDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl UssrMissionsDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  ShellButton *pSVar5;
  ShellButton *pSVar6;
  HDC pHVar7;
  HWND pHVar8;
  int iVar9;
  char *pcVar10;
  HWND pHVar11;
  AnimButton *pAVar12;
  ShellBitmap *pSVar13;
  ShellButton *pSVar14;
  TextWindow *pTVar15;
  UINT UVar16;
  HGDIOBJ pvVar17;
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
  uint uVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int nHeight;
  BOOL BVar22;
  LOGBRUSH LStack_1f670;
  RECT RStack_1f664;
  _USSRMission *p_Stack_1f654;
  HBRUSH pHStack_1f650;
  HWND__ *pHStack_1f64c;
  undefined1 auStack_1f648 [64];
  char acStack_1f608 [24];
  undefined1 auStack_1f5f0 [127976];
  char local_208 [256];
  char local_108 [256];
  uint local_8;
  
  pSVar14 = urButton;
  local_8 = __security_cookie ^ (uint)auStack_1f5f0;
  pHStack_1f64c = param_1;
  if (0x111 < param_2) {
    if (param_2 == 0x134) {
      SetTextColor((HDC)param_3,0x200ff00);
      SetBkMode((HDC)param_3,1);
    }
    else if (param_2 != 0x136) {
      if (param_2 != 0x138) {
        if (param_2 == 0x200) {
          iVar21 = 0;
          iVar20 = 1;
          uVar19 = (uint)param_4 >> 0x10;
          uVar18 = param_4 & 0xffff;
          iVar9 = ShellButton::CheckRollOver(ulButton,uVar18,uVar19);
          ShellButton::SetButtonMode(this,iVar9,iVar20,iVar21);
          iVar21 = 0;
          iVar20 = 1;
          iVar9 = ShellButton::CheckRollOver(llButton,uVar18,uVar19);
          ShellButton::SetButtonMode(this_00,iVar9,iVar20,iVar21);
          iVar21 = 0;
          iVar20 = 1;
          iVar9 = ShellButton::CheckRollOver(urButton,uVar18,uVar19);
          ShellButton::SetButtonMode(this_01,iVar9,iVar20,iVar21);
          iVar21 = 0;
          iVar20 = 1;
          iVar9 = ShellButton::CheckRollOver(lrButton,uVar18,uVar19);
          ShellButton::SetButtonMode(this_02,iVar9,iVar20,iVar21);
          iVar21 = 0;
          iVar20 = 1;
          iVar9 = ShellButton::CheckRollOver(mainButton,uVar18,uVar19);
          ShellButton::SetButtonMode(this_03,iVar9,iVar20,iVar21);
          iVar21 = 0;
          iVar20 = 1;
          iVar9 = ShellButton::CheckRollOver(scrollUp,uVar18,uVar19);
          ShellButton::SetButtonMode(this_04,iVar9,iVar20,iVar21);
          iVar21 = 0;
          iVar20 = 1;
          iVar9 = ShellButton::CheckRollOver(scrollDown,uVar18,uVar19);
          pSVar14 = extraout_EDX_12;
        }
        else {
          if (param_2 != 0x201) {
            if (param_2 != 0x202) {
              if (param_2 != 0x3b9) {
                return 0;
              }
              if (animWindow == (AnimButton *)0x0) {
                return 0;
              }
              AnimButton::movie_check(animWindow,param_3,param_4);
              return 0;
            }
            uVar18 = param_4 & 0xffff;
            iVar9 = ShellButton::CheckRollOver(urButton,uVar18,(uint)param_4 >> 0x10);
            if (iVar9 != 0) {
              pHStack_1f650 = (HBRUSH)SendDlgItemMessageA((HWND)param_1,0x45e,0x188,0,0);
              SendDlgItemMessageA((HWND)pHStack_1f64c,0x45e,0x189,(WPARAM)pHStack_1f650,
                                  (LPARAM)local_108);
              nMissionCurrentIndex = (int)pHStack_1f650;
              iVar9 = 0;
              do {
                cVar1 = local_108[iVar9];
                (&msn_filename)[iVar9] = cVar1;
                iVar9 = iVar9 + 1;
              } while (cVar1 != '\0');
              SetRunning(5);
              nReplayIntro = 0;
              nPlayCredits = 0;
              nShellMode = 0;
              Shell_EndDialog(pHStack_1f64c,1);
              return 0;
            }
            iVar9 = ShellButton::CheckRollOver(llButton,uVar18,extraout_EDX);
            if (iVar9 != 0) {
              stop_anim_sound();
              ShowWindow((HWND)param_1,0);
              EnableWindow((HWND)param_1,0);
              do_options(0);
              SetCurrentBackground(pHStack_1f64c,backGround);
              EnableWindow((HWND)pHStack_1f64c,1);
              ShowWindow((HWND)pHStack_1f64c,5);
              return 0;
            }
            iVar9 = ShellButton::CheckRollOver(ulButton,uVar18,extraout_EDX_00);
            if (iVar9 == 0) {
              iVar9 = ShellButton::CheckRollOver(lrButton,uVar18,extraout_EDX_01);
              if (iVar9 == 0) {
                iVar9 = ShellButton::CheckRollOver(mainButton,uVar18,extraout_EDX_02);
                if (iVar9 == 0) {
                  iVar9 = ShellButton::CheckRollOver(scrollUp,uVar18,extraout_EDX_03);
                  if (iVar9 == 0) {
                    iVar9 = ShellButton::CheckRollOver(scrollDown,uVar18,extraout_EDX_04);
                    if (iVar9 == 0) {
                      return 0;
                    }
                    iVar9 = descText->nFontHeight;
                  }
                  else {
                    iVar9 = -descText->nFontHeight;
                  }
                  (**(code **)(descText->_padding_ + 4))(iVar9);
                  return 0;
                }
                nShellMode = 1;
              }
              else {
                nShellMode = 0xc;
              }
            }
            else {
              nShellMode = 2;
            }
            goto LAB_0057eff0;
          }
          uVar18 = param_4 & 0xffff;
          iVar9 = ShellButton::CheckRollOver(urButton,uVar18,(uint)param_4 >> 0x10);
          pSVar5 = llButton;
          if ((((iVar9 == 0) &&
               (iVar9 = ShellButton::CheckRollOver(llButton,uVar18,extraout_EDX_05),
               pSVar6 = ulButton, pSVar14 = pSVar5, iVar9 == 0)) &&
              (iVar9 = ShellButton::CheckRollOver(ulButton,uVar18,extraout_EDX_06),
              pSVar5 = lrButton, pSVar14 = pSVar6, iVar9 == 0)) &&
             (((iVar9 = ShellButton::CheckRollOver(lrButton,uVar18,extraout_EDX_07),
               pSVar6 = mainButton, pSVar14 = pSVar5, iVar9 == 0 &&
               (iVar9 = ShellButton::CheckRollOver(mainButton,uVar18,extraout_EDX_08),
               pSVar5 = scrollUp, pSVar14 = pSVar6, iVar9 == 0)) &&
              (iVar9 = ShellButton::CheckRollOver(scrollUp,uVar18,extraout_EDX_09), pSVar14 = pSVar5
              , iVar9 == 0)))) {
            iVar9 = ShellButton::CheckRollOver(scrollDown,uVar18,extraout_EDX_10);
            if (iVar9 == 0) {
              return 0;
            }
            iVar21 = 0;
            iVar20 = 1;
            iVar9 = 2;
            pSVar14 = extraout_EDX_11;
          }
          else {
            iVar21 = 0;
            iVar20 = 1;
            iVar9 = 2;
          }
        }
        ShellButton::SetButtonMode(pSVar14,iVar9,iVar20,iVar21);
        return 0;
      }
      SetTextColor((HDC)param_3,0x200ff00);
      SetBkMode((HDC)param_3,1);
      iVar9 = 5;
      goto LAB_0057fb8b;
    }
    iVar9 = 4;
LAB_0057fb8b:
    pvVar17 = GetStockObject(iVar9);
    return (int)pvVar17;
  }
  if (param_2 == 0x111) {
    if ((short)param_3 == 0x45e) {
      if ((short)(param_3 >> 0x10) == 1) {
        pHStack_1f650 = (HBRUSH)SendDlgItemMessageA((HWND)param_1,0x45e,0x188,0,0);
        SendDlgItemMessageA((HWND)pHStack_1f64c,0x45e,0x189,(WPARAM)pHStack_1f650,(LPARAM)local_108)
        ;
        nMissionCurrentIndex = (int)pHStack_1f650;
        GetMissionDesc(local_108,acStack_1f608);
        pTVar15 = descText;
        TextWindow::SetWindowTextA(descText,acStack_1f608);
        (**(code **)(pTVar15->_padding_ + 4))(0);
      }
      return 1;
    }
    return 0;
  }
  if (param_2 < 0x2c) {
    if (param_2 == 0x2b) {
      if (*(int *)(param_4 + 8) == -1) {
        return 0;
      }
      if (1 < *(int *)(param_4 + 0xc) - 1U) {
        return 1;
      }
      pHVar11 = *(HWND *)(param_4 + 0x14);
      pHVar8 = GetDlgItem((HWND)param_1,0x45e);
      if (pHVar11 != pHVar8) {
        return 1;
      }
      SendMessageA(pHVar11,0x189,*(WPARAM *)(param_4 + 8),(LPARAM)local_208);
      GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)(auStack_1f648 + 8));
      RStack_1f664.top = *(int *)(param_4 + 0x20);
      RStack_1f664.bottom = *(int *)(param_4 + 0x28);
      iVar9 = (RStack_1f664.top - auStack_1f648._8_4_) + RStack_1f664.bottom;
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
      pHStack_1f650 = CreateBrushIndirect(&LStack_1f670);
      FillRect(*(HDC *)(param_4 + 0x18),&RStack_1f664,pHStack_1f650);
      if (pHStack_1f650 != (HBRUSH)0x0) {
        DeleteObject(pHStack_1f650);
      }
      pcVar10 = local_208;
      do {
        cVar1 = *pcVar10;
        pcVar10 = pcVar10 + 1;
      } while (cVar1 != '\0');
      TextOutA(*(HDC *)(param_4 + 0x18),5,iVar9 / 2,local_208,(int)pcVar10 - (int)(local_208 + 1));
      return 1;
    }
    if (param_2 == 2) {
      stop_anim_sound();
      SnapShotBackground();
      if (backGround != (ShellBitmap *)0x0) {
        CleanCurrentBackground();
      }
      pAVar12 = animWindow;
      if (animWindow != (AnimButton *)0x0) {
        AnimButton::~AnimButton(animWindow);
        operator_delete(pAVar12);
        animWindow = (AnimButton *)0x0;
      }
      pSVar13 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar13);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar14 = ulButton;
      if (ulButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(ulButton);
        operator_delete(pSVar14);
        ulButton = (ShellButton *)0x0;
      }
      pSVar14 = llButton;
      if (llButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(llButton);
        operator_delete(pSVar14);
        llButton = (ShellButton *)0x0;
      }
      pSVar14 = urButton;
      if (urButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(urButton);
        operator_delete(pSVar14);
        urButton = (ShellButton *)0x0;
      }
      pSVar14 = lrButton;
      if (lrButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(lrButton);
        operator_delete(pSVar14);
        lrButton = (ShellButton *)0x0;
      }
      pTVar15 = descText;
      if (descText != (TextWindow *)0x0) {
        TextWindow::~TextWindow(descText);
        operator_delete(pTVar15);
        descText = (TextWindow *)0x0;
      }
      pTVar15 = planetText;
      if (planetText != (TextWindow *)0x0) {
        TextWindow::~TextWindow(planetText);
        operator_delete(pTVar15);
        planetText = (TextWindow *)0x0;
      }
      pSVar14 = mainButton;
      if (mainButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(mainButton);
        operator_delete(pSVar14);
        mainButton = (ShellButton *)0x0;
      }
      pSVar14 = scrollUp;
      if (scrollUp != (ShellButton *)0x0) {
        ShellButton::~ShellButton(scrollUp);
        operator_delete(pSVar14);
        scrollUp = (ShellButton *)0x0;
      }
      pSVar14 = scrollDown;
      if (scrollDown == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(scrollDown);
      operator_delete(pSVar14);
      scrollDown = (ShellButton *)0x0;
      return 0;
    }
    if (param_2 == 0xf) {
      pHVar7 = BeginPaint((HWND)param_1,(LPPAINTSTRUCT)auStack_1f648);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar7);
      ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar7);
      ShellButton::UpdateButton(llButton,(HDC__ *)pHVar7);
      ShellButton::UpdateButton(urButton,(HDC__ *)pHVar7);
      ShellButton::UpdateButton(lrButton,(HDC__ *)pHVar7);
      (**(code **)descText->_padding_)(pHVar7,0);
      (**(code **)planetText->_padding_)(pHVar7,0);
      ShellButton::UpdateButton(mainButton,(HDC__ *)pHVar7);
      ShellButton::UpdateButton(scrollUp,(HDC__ *)pHVar7);
      ShellButton::UpdateButton(scrollDown,(HDC__ *)pHVar7);
      EndPaint((HWND)param_1,(PAINTSTRUCT *)auStack_1f648);
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
    return 0;
  }
  if (param_2 == 0x2c) {
    *(undefined4 *)(param_4 + 0x10) = 0xc;
    return 1;
  }
  if (param_2 == 0x100) {
    uVar2._3_1_ = testStr[4];
    uVar2._0_1_ = testStr[1];
    uVar2._1_1_ = testStr[2];
    uVar2._2_1_ = testStr[3];
    uVar3._3_1_ = testStr[8];
    uVar3._0_1_ = testStr[5];
    uVar3._1_1_ = testStr[6];
    uVar3._2_1_ = testStr[7];
    uVar4._3_1_ = testStr[0xc];
    uVar4._0_1_ = testStr[9];
    uVar4._1_1_ = testStr[10];
    uVar4._2_1_ = testStr[0xb];
    testStr[0xc] = testStr[0xd];
    testStr[0xd] = testStr[0xe];
    testStr[0xe] = testStr[0xf];
    testStr._0_4_ = uVar2;
    testStr._4_4_ = uVar3;
    testStr._8_4_ = uVar4;
    UVar16 = MapVirtualKeyA(param_3,2);
    testStr[0xf] = (char)UVar16;
    iVar9 = strncmp(testStr,skipCode,0xf);
    if (iVar9 != 0) {
      return 0;
    }
    builtin_strncpy(testStr,"                ",0x10);
    AnimButton::movie_stop(animWindow);
    iVar9 = 1;
    pHVar11 = GetDlgItem((HWND)pHStack_1f64c,0x45e);
    ShowWindow(pHVar11,iVar9);
    BVar22 = 1;
    pHVar11 = GetDlgItem((HWND)pHStack_1f64c,0x45e);
    EnableWindow(pHVar11,BVar22);
    return 0;
  }
  if (param_2 != 0x110) {
    return 0;
  }
  if (nDemoFlag != 0) {
    BVar22 = 0;
    pHVar11 = GetDlgItem((HWND)param_1,0x522);
    EnableWindow(pHVar11,BVar22);
    iVar9 = 0;
    pHVar11 = GetDlgItem((HWND)pHStack_1f64c,0x522);
    ShowWindow(pHVar11,iVar9);
  }
  nCheatStatus = 0;
  nPlayerSide = 2;
  nMissionStatus = 1;
  if (7 < nUssrMissionIndex) {
    nShellMode = 0xc;
    param_1 = pHStack_1f64c;
LAB_0057eff0:
    Shell_EndDialog(param_1,1);
    return 0;
  }
  init_screen_pos(pHStack_1f64c);
  init_bitmap_dc(pHStack_1f64c);
  iVar9 = USSRMissionList[nUssrMissionIndex].nPlanet;
  if (iVar9 == 3) {
    if (nUssrMissionIndex != 0) {
      pAVar12 = operator_new(0x14c);
      if (pAVar12 == (AnimButton *)0x0) {
        pAVar12 = (AnimButton *)0x0;
      }
      else {
        pAVar12 = AnimButton::AnimButton
                            (pAVar12,pHStack_1f64c,"anims\\vnspin.avi",0x85,0x29,0x25,0x140,0xf0,4);
      }
      iVar9 = 0x4c;
LAB_0057f227:
      pAVar12->nStart = iVar9;
      pAVar12->nSpecialFrame = iVar9;
      animWindow = pAVar12;
      pAVar12->nStatusCommand = 3;
      AnimButton::SetButtonMode(pAVar12,1);
      goto LAB_0057f24b;
    }
    pAVar12 = operator_new(0x14c);
    if (pAVar12 == (AnimButton *)0x0) {
      pAVar12 = (AnimButton *)0x0;
    }
    else {
      pAVar12 = AnimButton::AnimButton
                          (pAVar12,pHStack_1f64c,"anims\\vnspin.avi",0x85,0x29,0x25,0x140,0xf0,1);
    }
    animWindow = pAVar12;
    pAVar12->nSpecialFrame = 0x4c;
    pAVar12->nStatusCommand = 1;
    AnimButton::SetButtonMode(pAVar12,1);
    pcVar10 = "mspin.wav";
  }
  else {
    if (iVar9 == 4) {
      if (nUssrMissionIndex != 2) {
        pAVar12 = operator_new(0x14c);
        if (pAVar12 != (AnimButton *)0x0) {
          iVar9 = 4;
          pcVar10 = "anims\\jispin.avi";
          goto LAB_0057f11e;
        }
LAB_0057f12a:
        pAVar12 = (AnimButton *)0x0;
LAB_0057f12c:
        iVar9 = 0x60;
        goto LAB_0057f227;
      }
      pAVar12 = operator_new(0x14c);
      if (pAVar12 != (AnimButton *)0x0) {
        pcVar10 = "anims\\jispin.avi";
        goto LAB_0057f0c6;
      }
LAB_0057f0d2:
      pAVar12 = (AnimButton *)0x0;
    }
    else {
      if (iVar9 != 6) {
        pAVar12 = operator_new(0x14c);
        if (pAVar12 == (AnimButton *)0x0) {
          pAVar12 = (AnimButton *)0x0;
        }
        else {
          pAVar12 = AnimButton::AnimButton
                              (pAVar12,pHStack_1f64c,"anims\\vnspin.avi",0x85,0x29,0x25,0x140,0xf0,1
                              );
        }
        animWindow = pAVar12;
        pAVar12->nSpecialFrame = 0x4c;
        pAVar12->nStatusCommand = 1;
        AnimButton::SetButtonMode(pAVar12,1);
        animWindow->nStatusCommand = 3;
        goto LAB_0057f24b;
      }
      if (nUssrMissionIndex != 4) {
        pAVar12 = operator_new(0x14c);
        if (pAVar12 == (AnimButton *)0x0) goto LAB_0057f12a;
        iVar9 = 1;
        pcVar10 = "anims\\stspin.avi";
LAB_0057f11e:
        pAVar12 = AnimButton::AnimButton
                            (pAVar12,pHStack_1f64c,pcVar10,0x9a,0x29,0x25,0x140,0xf0,iVar9);
        goto LAB_0057f12c;
      }
      pAVar12 = operator_new(0x14c);
      if (pAVar12 == (AnimButton *)0x0) goto LAB_0057f0d2;
      pcVar10 = "anims\\stspin.avi";
LAB_0057f0c6:
      pAVar12 = AnimButton::AnimButton(pAVar12,pHStack_1f64c,pcVar10,0x9a,0x29,0x25,0x140,0xf0,1);
    }
    pAVar12->nSpecialFrame = 0x60;
    animWindow = pAVar12;
    pAVar12->nStatusCommand = 1;
    AnimButton::SetButtonMode(pAVar12,1);
    pcVar10 = "emspin.wav";
  }
  animWindow->nStatusCommand = 3;
  play_anim_sound(pcVar10);
LAB_0057f24b:
  pSVar13 = operator_new(0x20);
  if (pSVar13 == (ShellBitmap *)0x0) {
    backGround = (ShellBitmap *)0x0;
  }
  else {
    backGround = ShellBitmap::ShellBitmap(pSVar13,"bitmap\\missbrf2.bmp",0,0);
  }
  SetCurrentBackground(pHStack_1f64c,backGround);
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    ulButton = (ShellButton *)0x0;
  }
  else {
    ulButton = ShellButton::ShellButton
                         (pSVar14,pHStack_1f64c,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                          "BACK");
  }
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    llButton = (ShellButton *)0x0;
  }
  else {
    llButton = ShellButton::ShellButton
                         (pSVar14,pHStack_1f64c,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                          "OPTIONS");
  }
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    urButton = (ShellButton *)0x0;
  }
  else {
    urButton = ShellButton::ShellButton
                         (pSVar14,pHStack_1f64c,shell_hInstance,0xca,0xc9,0xcb,0x1e8,0,0x98,0x22,1,
                          "LAUNCH");
  }
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    lrButton = (ShellButton *)0x0;
  }
  else {
    lrButton = ShellButton::ShellButton
                         (pSVar14,pHStack_1f64c,shell_hInstance,0xc4,0xc3,0xc5,0x1b9,0x1bd,199,0x22,
                          1,"MISSION ARCHIVE");
  }
  ShellButton::SetLabelPos(lrButton,0x1fb,0x1c4,0x58,0x17);
  ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
  ShellButton::SetLabelPos(llButton,0x2f,0x1c6,0x58,0x17);
  ShellButton::SetLabelPos(urButton,0x1fb,4,0x58,0x17);
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    mainButton = (ShellButton *)0x0;
  }
  else {
    mainButton = ShellButton::ShellButton
                           (pSVar14,pHStack_1f64c,shell_hInstance,0x119,0x118,0x11a,0xef,0,0xa4,0x1e
                            ,1,"To Main Menu");
  }
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    scrollUp = (ShellButton *)0x0;
  }
  else {
    scrollUp = ShellButton::ShellButton
                         (pSVar14,pHStack_1f64c,shell_hInstance,0x82c,0x819,0x7ff,0x178,0x114,0x13,
                          0x12,0,(char *)0x0);
  }
  pSVar14 = operator_new(0x110);
  if (pSVar14 == (ShellButton *)0x0) {
    scrollDown = (ShellButton *)0x0;
  }
  else {
    scrollDown = ShellButton::ShellButton
                           (pSVar14,pHStack_1f64c,shell_hInstance,0x82d,0x818,0x800,0x178,0x126,0x13
                            ,0x12,0,(char *)0x0);
  }
  pHStack_1f650 = (HBRUSH)0x0;
  p_Stack_1f654 = USSRMissionList;
  do {
    sprintf(local_108,"%s",p_Stack_1f654);
    SendDlgItemMessageA((HWND)pHStack_1f64c,0x45e,0x181,(WPARAM)pHStack_1f650,(LPARAM)local_108);
    p_Stack_1f654 = p_Stack_1f654 + 1;
    pHStack_1f650 = (HBRUSH)((int)pHStack_1f650 + 1);
  } while ((int)p_Stack_1f654 < 0x63a3f0);
  SendDlgItemMessageA((HWND)pHStack_1f64c,0x45e,0x186,nUssrMissionIndex,0);
  GetMissionDesc(USSRMissionList[nUssrMissionIndex].cMissionName,acStack_1f608);
  BVar22 = 1;
  nHeight = 0xf0;
  iVar21 = 0x140;
  iVar20 = 0x25;
  iVar9 = 0x29;
  pHVar11 = GetDlgItem((HWND)pHStack_1f64c,0x45e);
  MoveWindow(pHVar11,iVar9,iVar20,iVar21,nHeight,BVar22);
  iVar9 = 0;
  pHVar11 = GetDlgItem((HWND)pHStack_1f64c,0x45e);
  ShowWindow(pHVar11,iVar9);
  BVar22 = 0;
  pHVar11 = GetDlgItem((HWND)pHStack_1f64c,0x45e);
  EnableWindow(pHVar11,BVar22);
  pTVar15 = operator_new(0x1f438);
  if (pTVar15 == (TextWindow *)0x0) {
    descText = (TextWindow *)0x0;
  }
  else {
    descText = TextWindow::TextWindow(pTVar15,pHStack_1f64c,acStack_1f608,0x192,0x35,0xcd,0x174,0);
  }
  TextWindow::SetTextFont(descText,defaultFont,defaultFontSize2);
  TextWindow::SetWindowTextColor(descText,0xff,1);
  iVar9 = TextWindow::CheckTextSize(descText);
  if (iVar9 == 0) {
    ShellButton::HideButton(scrollUp,0);
    ShellButton::HideButton(scrollDown,0);
  }
  GetPlanetDesc(2,nUssrMissionIndex,local_108);
  GetMissionDesc(local_108,acStack_1f608);
  pTVar15 = operator_new(0x1f438);
  if (pTVar15 == (TextWindow *)0x0) {
    planetText = (TextWindow *)0x0;
  }
  else {
    planetText = TextWindow::TextWindow(pTVar15,pHStack_1f64c,acStack_1f608,0x34,300,0x11a,100,0);
  }
  TextWindow::SetTextFont(planetText,defaultFont,defaultFontSize2);
  read_text_label("missions","back",ulButton->labelText);
  read_text_label("missions","options",llButton->labelText);
  read_text_label("missions","launch",urButton->labelText);
  read_text_label("missions","main_menu",mainButton->labelText);
  read_text_label("missions","archives",lrButton->labelText);
  if (nUssrMissionIndex == 0) {
    ShellButton::HideButton(lrButton,0);
  }
  SetFocus((HWND)pHStack_1f64c);
  return 0;
}
