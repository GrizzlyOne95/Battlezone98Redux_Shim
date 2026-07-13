/*
 * Entry: 0057d2a1
 * Name: EscapeDlgProc
 * Namespace: Global
 * Signature: int EscapeDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl EscapeDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  ShellButton *pSVar4;
  ShellButton *pSVar5;
  ShellBitmap *pSVar6;
  ShellButton *pSVar7;
  UINT UVar8;
  int iVar9;
  HDC pHVar10;
  HGDIOBJ pvVar11;
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
  char *pcVar12;
  uint uVar13;
  code *pcVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  tagPAINTSTRUCT local_44;
  uint local_4;
  
  pSVar7 = b1Button;
  local_4 = __security_cookie ^ (uint)&local_44;
  if (param_2 < 0x114) {
    if (param_2 == 0x113) {
      iVar9 = Net_IsNetGame();
      if (iVar9 == 0) {
        return 0;
      }
      Net_Execute();
      return 0;
    }
    if (param_2 == 2) {
      KillTimer((HWND)param_1,iTimerID);
      CleanCurrentBackground();
      pSVar6 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar6);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar7 = ulButton;
      if (ulButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(ulButton);
        operator_delete(pSVar7);
        ulButton = (ShellButton *)0x0;
      }
      pSVar7 = llButton;
      if (llButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(llButton);
        operator_delete(pSVar7);
        llButton = (ShellButton *)0x0;
      }
      pSVar7 = b1Button;
      if (b1Button != (ShellButton *)0x0) {
        ShellButton::~ShellButton(b1Button);
        operator_delete(pSVar7);
        b1Button = (ShellButton *)0x0;
      }
      pSVar7 = b2Button;
      if (b2Button != (ShellButton *)0x0) {
        ShellButton::~ShellButton(b2Button);
        operator_delete(pSVar7);
        b2Button = (ShellButton *)0x0;
      }
      pSVar7 = b3Button;
      if (b3Button != (ShellButton *)0x0) {
        ShellButton::~ShellButton(b3Button);
        operator_delete(pSVar7);
        b3Button = (ShellButton *)0x0;
      }
      pSVar7 = b4Button;
      if (b4Button == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(b4Button);
      operator_delete(pSVar7);
      b4Button = (ShellButton *)0x0;
      return 0;
    }
    if (param_2 == 0xf) {
      pHVar10 = BeginPaint((HWND)param_1,&local_44);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar10);
      ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar10);
      ShellButton::UpdateButton(llButton,(HDC__ *)pHVar10);
      ShellButton::UpdateButton(b1Button,(HDC__ *)pHVar10);
      ShellButton::UpdateButton(b2Button,(HDC__ *)pHVar10);
      ShellButton::UpdateButton(b3Button,(HDC__ *)pHVar10);
      ShellButton::UpdateButton(b4Button,(HDC__ *)pHVar10);
      EndPaint((HWND)param_1,&local_44);
      return 0;
    }
    if (param_2 != 0x14) {
      if (param_2 != 0x20) {
        if (param_2 != 0x100) {
          if (param_2 != 0x110) {
            return 0;
          }
          iTimerID = SetTimer((HWND)param_1,1,100,(TIMERPROC)0x0);
          init_screen_pos(param_1);
          init_bitmap_dc(param_1);
          pSVar6 = operator_new(0x20);
          if (pSVar6 == (ShellBitmap *)0x0) {
            backGround = (ShellBitmap *)0x0;
          }
          else {
            backGround = ShellBitmap::ShellBitmap(pSVar6,"bitmap\\esc.bmp",0,0);
          }
          SetCurrentBackground(param_1,backGround);
          pSVar7 = operator_new(0x110);
          if (pSVar7 == (ShellButton *)0x0) {
            ulButton = (ShellButton *)0x0;
          }
          else {
            ulButton = ShellButton::ShellButton
                                 (pSVar7,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                                  "RETURN TO GAME");
          }
          pSVar7 = operator_new(0x110);
          if (pSVar7 == (ShellButton *)0x0) {
            llButton = (ShellButton *)0x0;
          }
          else {
            llButton = ShellButton::ShellButton
                                 (pSVar7,param_1,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                                  "OPTIONS");
          }
          pSVar7 = operator_new(0x110);
          if (pSVar7 == (ShellButton *)0x0) {
            b1Button = (ShellButton *)0x0;
          }
          else {
            b1Button = ShellButton::ShellButton
                                 (pSVar7,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0x5c,0xbc,0x3a,1
                                  ,"SAVE GAME");
          }
          pSVar7 = operator_new(0x110);
          if (pSVar7 == (ShellButton *)0x0) {
            b2Button = (ShellButton *)0x0;
          }
          else {
            b2Button = ShellButton::ShellButton
                                 (pSVar7,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0xab,0xbc,0x3a,1
                                  ,"LOAD GAME");
          }
          pSVar7 = operator_new(0x110);
          if (pSVar7 == (ShellButton *)0x0) {
            b3Button = (ShellButton *)0x0;
          }
          else {
            b3Button = ShellButton::ShellButton
                                 (pSVar7,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0xfa,0xbc,0x3a,1
                                  ,"RESTART MISSION");
          }
          pSVar7 = operator_new(0x110);
          if (pSVar7 == (ShellButton *)0x0) {
            b4Button = (ShellButton *)0x0;
          }
          else {
            b4Button = ShellButton::ShellButton
                                 (pSVar7,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0x149,0xbc,0x3a,
                                  1,"ABORT MISSION");
          }
          ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
          ShellButton::SetLabelPos(llButton,0x2f,0x1c4,0x58,0x17);
          read_text_label("escape","return_to_game",ulButton->labelText);
          read_text_label("escape","save_game",b1Button->labelText);
          read_text_label("escape","load_game",b2Button->labelText);
          read_text_label("escape","restart_mission",b3Button->labelText);
          read_text_label("escape","abort_mission",b4Button->labelText);
          read_text_label("escape","options",llButton->labelText);
          SetFocus((HWND)param_1);
          return 0;
        }
        uVar1._3_1_ = testStr[4];
        uVar1._0_1_ = testStr[1];
        uVar1._1_1_ = testStr[2];
        uVar1._2_1_ = testStr[3];
        uVar2._3_1_ = testStr[8];
        uVar2._0_1_ = testStr[5];
        uVar2._1_1_ = testStr[6];
        uVar2._2_1_ = testStr[7];
        uVar3._3_1_ = testStr[0xc];
        uVar3._0_1_ = testStr[9];
        uVar3._1_1_ = testStr[10];
        uVar3._2_1_ = testStr[0xb];
        testStr[0xc] = testStr[0xd];
        testStr._0_4_ = uVar1;
        testStr._4_4_ = uVar2;
        testStr._8_4_ = uVar3;
        UVar8 = MapVirtualKeyA(param_3,2);
        if (UVar8 != 0x20) {
          testStr[0xd] = (char)UVar8;
          return 0;
        }
        testStr[0xd] = '\0';
        pcVar12 = testStr + 0xc;
        do {
          iVar9 = isalnum((int)*pcVar12);
          if ((iVar9 == 0) && (*pcVar12 != '.')) break;
          pcVar12 = pcVar12 + -1;
        } while (testStr + 7 < pcVar12);
        iVar9 = ItemExists(pcVar12 + 1);
        if (iVar9 != 0) {
          InfoDisplay::ClearObjectives(&infoDisplay);
          AddObjective(pcVar12 + 1,DisplayInterface::colorWhite,8.0);
        }
        builtin_strncpy(testStr,"______________",0xe);
        return 0;
      }
      set_cursor(0);
      SetWindowLongA((HWND)param_1,0,1);
    }
    return 1;
  }
  if (param_2 == 0x136) {
    iVar9 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar15 = param_4 & 0xffff;
        iVar17 = 0;
        iVar16 = 1;
        uVar13 = (uint)param_4 >> 0x10;
        iVar9 = ShellButton::CheckRollOver(b1Button,uVar15,uVar13);
        ShellButton::SetButtonMode(this,iVar9,iVar16,iVar17);
        iVar17 = 0;
        iVar16 = 1;
        iVar9 = ShellButton::CheckRollOver(b2Button,uVar15,uVar13);
        ShellButton::SetButtonMode(this_00,iVar9,iVar16,iVar17);
        iVar17 = 0;
        iVar16 = 1;
        iVar9 = ShellButton::CheckRollOver(b3Button,uVar15,uVar13);
        ShellButton::SetButtonMode(this_01,iVar9,iVar16,iVar17);
        iVar17 = 0;
        iVar16 = 1;
        iVar9 = ShellButton::CheckRollOver(b4Button,uVar15,uVar13);
        ShellButton::SetButtonMode(this_02,iVar9,iVar16,iVar17);
        iVar17 = 0;
        iVar16 = 1;
        iVar9 = ShellButton::CheckRollOver(ulButton,uVar15,uVar13);
        ShellButton::SetButtonMode(this_03,iVar9,iVar16,iVar17);
        iVar17 = 0;
        iVar16 = 1;
        iVar9 = ShellButton::CheckRollOver(llButton,uVar15,uVar13);
        pSVar7 = extraout_EDX_10;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          uVar13 = param_4 & 0xffff;
          iVar9 = ShellButton::CheckRollOver(b1Button,uVar13,(uint)param_4 >> 0x10);
          pcVar14 = ShowWindow_exref;
          if (iVar9 != 0) {
            ShowWindow((HWND)param_1,0);
            EnableWindow((HWND)param_1,0);
            do_savegame(0);
            SetCurrentBackground(param_1,backGround);
            EnableWindow((HWND)param_1,1);
LAB_0057d92d:
            (*pcVar14)(param_1,5);
            return 0;
          }
          iVar9 = ShellButton::CheckRollOver(b2Button,uVar13,extraout_EDX);
          if (iVar9 != 0) {
            nReplayIntro = 0;
            nPlayCredits = 0;
            nShellMode = 0x12;
LAB_0057d8d8:
            Shell_EndDialog(param_1,1);
            return 0;
          }
          iVar9 = ShellButton::CheckRollOver(b3Button,uVar13,extraout_EDX_00);
          if (iVar9 == 0) {
            iVar9 = ShellButton::CheckRollOver(b4Button,uVar13,extraout_EDX_01);
            if (iVar9 == 0) {
              iVar9 = ShellButton::CheckRollOver(ulButton,uVar13,extraout_EDX_02);
              if (iVar9 == 0) {
                iVar9 = ShellButton::CheckRollOver(llButton,uVar13,extraout_EDX_03);
                pcVar14 = ShowWindow_exref;
                if (iVar9 == 0) {
                  return 0;
                }
                ShowWindow((HWND)param_1,0);
                EnableWindow((HWND)param_1,0);
                do_options(1);
                SetCurrentBackground(param_1,backGround);
                EnableWindow((HWND)param_1,1);
                goto LAB_0057d92d;
              }
              nShellMode = 0;
              goto LAB_0057d8d8;
            }
            iVar9 = 2;
          }
          else {
            iVar9 = 7;
          }
          SetRunning(iVar9);
          nShellMode = 0;
          Shell_EndDialog(param_1,1);
          return 0;
        }
        uVar13 = param_4 & 0xffff;
        iVar9 = ShellButton::CheckRollOver(b1Button,uVar13,(uint)param_4 >> 0x10);
        pSVar4 = b2Button;
        if ((((iVar9 == 0) &&
             (iVar9 = ShellButton::CheckRollOver(b2Button,uVar13,extraout_EDX_04), pSVar5 = b3Button
             , pSVar7 = pSVar4, iVar9 == 0)) &&
            (iVar9 = ShellButton::CheckRollOver(b3Button,uVar13,extraout_EDX_05), pSVar4 = b4Button,
            pSVar7 = pSVar5, iVar9 == 0)) &&
           ((iVar9 = ShellButton::CheckRollOver(b4Button,uVar13,extraout_EDX_06), pSVar5 = ulButton,
            pSVar7 = pSVar4, iVar9 == 0 &&
            (iVar9 = ShellButton::CheckRollOver(ulButton,uVar13,extraout_EDX_07), pSVar7 = pSVar5,
            iVar9 == 0)))) {
          iVar9 = ShellButton::CheckRollOver(llButton,uVar13,extraout_EDX_08);
          if (iVar9 == 0) {
            return 0;
          }
          iVar17 = 0;
          iVar16 = 1;
          iVar9 = 2;
          pSVar7 = extraout_EDX_09;
        }
        else {
          iVar17 = 0;
          iVar16 = 1;
          iVar9 = 2;
        }
      }
      ShellButton::SetButtonMode(pSVar7,iVar9,iVar16,iVar17);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar9 = 5;
  }
  pvVar11 = GetStockObject(iVar9);
  return (int)pvVar11;
}
