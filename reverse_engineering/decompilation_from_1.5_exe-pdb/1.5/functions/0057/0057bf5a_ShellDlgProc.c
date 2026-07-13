/*
 * Entry: 0057bf5a
 * Name: ShellDlgProc
 * Namespace: Global
 * Signature: int ShellDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl ShellDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  undefined4 uVar1;
  ShellButton *pSVar2;
  AnimButton *pAVar3;
  ShellBitmap *pSVar4;
  ShellButton *pSVar5;
  UINT UVar6;
  int iVar7;
  HDC pHVar8;
  HGDIOBJ pvVar9;
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
  uint uVar10;
  ShellButton *pSVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  pSVar5 = b1Button;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 == 2) {
        SnapShotBackground();
        CleanCurrentBackground();
        pAVar3 = animTitle;
        if (animTitle != (AnimButton *)0x0) {
          AnimButton::~AnimButton(animTitle);
          operator_delete(pAVar3);
          animTitle = (AnimButton *)0x0;
        }
        pSVar4 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar4);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar5 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar5);
          ulButton = (ShellButton *)0x0;
        }
        pSVar5 = llButton;
        if (llButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(llButton);
          operator_delete(pSVar5);
          llButton = (ShellButton *)0x0;
        }
        pSVar5 = b1Button;
        if (b1Button != (ShellButton *)0x0) {
          ShellButton::~ShellButton(b1Button);
          operator_delete(pSVar5);
          b1Button = (ShellButton *)0x0;
        }
        pSVar5 = b2Button;
        if (b2Button != (ShellButton *)0x0) {
          ShellButton::~ShellButton(b2Button);
          operator_delete(pSVar5);
          b2Button = (ShellButton *)0x0;
        }
        pSVar5 = b3Button;
        if (b3Button != (ShellButton *)0x0) {
          ShellButton::~ShellButton(b3Button);
          operator_delete(pSVar5);
          b3Button = (ShellButton *)0x0;
        }
        pSVar5 = b4Button;
        if (b4Button == (ShellButton *)0x0) {
          return 0;
        }
        ShellButton::~ShellButton(b4Button);
        operator_delete(pSVar5);
        b4Button = (ShellButton *)0x0;
        return 0;
      }
      if (param_2 == 0xf) {
        pHVar8 = BeginPaint((HWND)param_1,&local_48);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(llButton,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(b1Button,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(b2Button,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(b3Button,(HDC__ *)pHVar8);
        ShellButton::UpdateButton(b4Button,(HDC__ *)pHVar8);
        EndPaint((HWND)param_1,&local_48);
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
      if (param_2 == 0x100) {
        uVar1._3_1_ = testStr[4];
        uVar1._0_1_ = testStr[1];
        uVar1._1_1_ = testStr[2];
        uVar1._2_1_ = testStr[3];
        testStr[4] = testStr[5];
        testStr[5] = testStr[6];
        testStr[6] = testStr[7];
        testStr._0_4_ = uVar1;
        UVar6 = MapVirtualKeyA(param_3,2);
        testStr[7] = (char)UVar6;
        iVar7 = strncmp(testStr,"PISSED",6);
        if (iVar7 != 0) {
          return 0;
        }
        ShellPlaySound("pissed.wav",100,0,-1);
        return 0;
      }
      if (param_2 != 0x110) {
        return 0;
      }
      nMainMenuCalled = 0;
      init_screen_pos(param_1);
      nReplayIntro = 0;
      nPlayCredits = 0;
      init_bitmap_dc(param_1);
      pAVar3 = operator_new(0x14c);
      if (pAVar3 == (AnimButton *)0x0) {
        animTitle = (AnimButton *)0x0;
      }
      else {
        animTitle = AnimButton::AnimButton
                              (pAVar3,param_1,"anims\\bzone.avi",0xe8,0x2a,0xcb,0x22e,0x4b,2);
      }
      pSVar4 = operator_new(0x20);
      if (pSVar4 == (ShellBitmap *)0x0) {
        backGround = (ShellBitmap *)0x0;
      }
      else {
        backGround = ShellBitmap::ShellBitmap(pSVar4,"bitmap\\main.bmp",0,0);
      }
      SetCurrentBackground(param_1,backGround);
      pSVar5 = operator_new(0x110);
      if (pSVar5 == (ShellButton *)0x0) {
        ulButton = (ShellButton *)0x0;
      }
      else {
        ulButton = ShellButton::ShellButton
                             (pSVar5,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                              "EXIT GAME");
      }
      ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
      pSVar5 = operator_new(0x110);
      if (pSVar5 == (ShellButton *)0x0) {
        llButton = (ShellButton *)0x0;
      }
      else {
        llButton = ShellButton::ShellButton
                             (pSVar5,param_1,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                              "OPTIONS");
      }
      pSVar5 = operator_new(0x110);
      if (pSVar5 == (ShellButton *)0x0) {
        b1Button = (ShellButton *)0x0;
      }
      else {
        b1Button = ShellButton::ShellButton
                             (pSVar5,param_1,shell_hInstance,0,0xd1,0xd0,0x49,0x43,0xc6,0x54,1,
                              "SINGLE PLAYER");
      }
      pSVar5 = operator_new(0x110);
      if (pSVar5 == (ShellButton *)0x0) {
        b2Button = (ShellButton *)0x0;
      }
      else {
        b2Button = ShellButton::ShellButton
                             (pSVar5,param_1,shell_hInstance,0,0xcc,0xd2,0x173,0x43,0xc6,0x54,1,
                              "MULTI PLAYER");
      }
      pSVar5 = operator_new(0x110);
      if (pSVar5 == (ShellButton *)0x0) {
        b3Button = (ShellButton *)0x0;
      }
      else {
        b3Button = ShellButton::ShellButton
                             (pSVar5,param_1,shell_hInstance,0,0xcd,0xd3,0x49,0x148,0xc6,0x54,1,
                              "VIEW CREDITS");
      }
      pSVar5 = operator_new(0x110);
      if (pSVar5 == (ShellButton *)0x0) {
        b4Button = (ShellButton *)0x0;
      }
      else {
        b4Button = ShellButton::ShellButton
                             (pSVar5,param_1,shell_hInstance,0,0xd4,0xce,0x173,0x148,0xc6,0x54,1,
                              "REPLAY INTRO");
      }
      ShellButton::SetSoundFile(b1Button,"shmroll.wav","shmclick.wav");
      ShellButton::SetSoundFile(b2Button,"shmroll.wav","shmclick.wav");
      ShellButton::SetSoundFile(b3Button,"shmroll.wav","shmclick.wav");
      ShellButton::SetSoundFile(b4Button,"shmroll.wav","shmclick.wav");
      read_text_label("main","exit",ulButton->labelText);
      read_text_label("main","single_player",b1Button->labelText);
      read_text_label("main","multi_player",b2Button->labelText);
      read_text_label("main","view_credits",b3Button->labelText);
      read_text_label("main","replay_intro",b4Button->labelText);
      read_text_label("main","options",llButton->labelText);
      ShellButton::SetLabelPos(llButton,0x2f,0x1c4,0x58,0x17);
      pAVar3 = animTitle;
      animTitle->nStatusCommand = 2;
      AnimButton::SetButtonMode(pAVar3,1);
LAB_0057c2f9:
      SetFocus((HWND)param_1);
      return 0;
    }
    iVar7 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        if (nMouseButtonDown != 0) {
          return 0;
        }
        uVar10 = param_4 & 0xffff;
        iVar14 = 0;
        iVar13 = 1;
        uVar12 = (uint)param_4 >> 0x10;
        iVar7 = ShellButton::CheckRollOver(b1Button,uVar10,uVar12);
        ShellButton::SetButtonMode(this,iVar7,iVar13,iVar14);
        iVar14 = 0;
        iVar13 = 1;
        iVar7 = ShellButton::CheckRollOver(b2Button,uVar10,uVar12);
        ShellButton::SetButtonMode(this_00,iVar7,iVar13,iVar14);
        iVar14 = 0;
        iVar13 = 1;
        iVar7 = ShellButton::CheckRollOver(b3Button,uVar10,uVar12);
        ShellButton::SetButtonMode(this_01,iVar7,iVar13,iVar14);
        iVar14 = 0;
        iVar13 = 1;
        iVar7 = ShellButton::CheckRollOver(b4Button,uVar10,uVar12);
        ShellButton::SetButtonMode(this_02,iVar7,iVar13,iVar14);
        iVar14 = 0;
        iVar13 = 1;
        iVar7 = ShellButton::CheckRollOver(ulButton,uVar10,uVar12);
        ShellButton::SetButtonMode(this_03,iVar7,iVar13,iVar14);
        iVar14 = 0;
        iVar13 = 1;
        iVar7 = ShellButton::CheckRollOver(llButton,uVar10,uVar12);
        pSVar5 = extraout_EDX_10;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            if (param_2 != 0x3b9) {
              return 0;
            }
            if (animTitle == (AnimButton *)0x0) {
              return 0;
            }
            AnimButton::movie_check(animTitle,param_3,param_4);
            return 0;
          }
          uVar10 = param_4 & 0xffff;
          nMouseButtonDown = 0;
          iVar7 = ShellButton::CheckRollOver(b1Button,uVar10,(uint)param_4 >> 0x10);
          pSVar5 = b2Button;
          if (iVar7 == 0) {
            iVar7 = ShellButton::CheckRollOver(b2Button,uVar10,extraout_EDX);
            pSVar11 = b3Button;
            if (iVar7 == 0) {
              iVar7 = ShellButton::CheckRollOver(b3Button,uVar10,extraout_EDX_00);
              if (iVar7 == 0) {
                iVar7 = ShellButton::CheckRollOver(b4Button,uVar10,extraout_EDX_01);
                if (iVar7 == 0) {
                  iVar7 = ShellButton::CheckRollOver(ulButton,uVar10,extraout_EDX_02);
                  if (iVar7 != 0) {
                    SetRunning(10);
                    nReplayIntro = 0;
                    nPlayCredits = 0;
                    nShellMode = 0;
                    Shell_EndDialog(param_1,1);
                    return 0;
                  }
                  iVar7 = ShellButton::CheckRollOver(llButton,uVar10,extraout_EDX_03);
                  if (iVar7 == 0) {
                    return 0;
                  }
                  ShowWindow((HWND)param_1,0);
                  EnableWindow((HWND)param_1,0);
                  do_options(0);
                  SetCurrentBackground(param_1,backGround);
                  EnableWindow((HWND)param_1,1);
                  ShowWindow((HWND)param_1,5);
                  goto LAB_0057c2f9;
                }
                nReplayIntro = 1;
                nPlayCredits = 0;
              }
              else {
                if (nDemoFlag != 0) goto LAB_0057c5af;
                nReplayIntro = 0;
                nPlayCredits = 1;
              }
              nMissionStatus = 0;
              nShellMode = 0;
            }
            else {
              pSVar11 = pSVar5;
              if (nDemoFlag != 0) {
LAB_0057c5af:
                ShellButton::SetLabelText(pSVar11,"NOT AVAILABLE IN DEMO");
                ShellButton::UpdateButton(pSVar11);
                return 0;
              }
              nShellMode = 0xd;
            }
          }
          else {
            nShellMode = 2;
          }
          Shell_EndDialog(param_1,1);
          return 0;
        }
        uVar10 = param_4 & 0xffff;
        nMouseButtonDown = 1;
        iVar7 = ShellButton::CheckRollOver(b1Button,uVar10,(uint)param_4 >> 0x10);
        pSVar11 = b2Button;
        if ((((iVar7 == 0) &&
             (iVar7 = ShellButton::CheckRollOver(b2Button,uVar10,extraout_EDX_04), pSVar2 = b3Button
             , pSVar5 = pSVar11, iVar7 == 0)) &&
            (iVar7 = ShellButton::CheckRollOver(b3Button,uVar10,extraout_EDX_05), pSVar11 = b4Button
            , pSVar5 = pSVar2, iVar7 == 0)) &&
           ((iVar7 = ShellButton::CheckRollOver(b4Button,uVar10,extraout_EDX_06), pSVar2 = ulButton,
            pSVar5 = pSVar11, iVar7 == 0 &&
            (iVar7 = ShellButton::CheckRollOver(ulButton,uVar10,extraout_EDX_07), pSVar5 = pSVar2,
            iVar7 == 0)))) {
          iVar7 = ShellButton::CheckRollOver(llButton,uVar10,extraout_EDX_08);
          if (iVar7 == 0) {
            return 0;
          }
          iVar14 = 0;
          iVar13 = 1;
          iVar7 = 2;
          pSVar5 = extraout_EDX_09;
        }
        else {
          iVar14 = 0;
          iVar13 = 1;
          iVar7 = 2;
        }
      }
      ShellButton::SetButtonMode(pSVar5,iVar7,iVar13,iVar14);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar7 = 5;
  }
  pvVar9 = GetStockObject(iVar7);
  return (int)pvVar9;
}
