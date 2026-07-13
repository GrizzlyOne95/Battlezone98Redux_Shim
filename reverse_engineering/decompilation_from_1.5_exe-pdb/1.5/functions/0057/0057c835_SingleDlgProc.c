/*
 * Entry: 0057c835
 * Name: SingleDlgProc
 * Namespace: Global
 * Signature: int SingleDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl SingleDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellButton *pSVar1;
  ShellButton *pSVar2;
  TextLabel *pTVar3;
  ShellBitmap *pSVar4;
  ShellButton *pSVar5;
  AnimButton *pAVar6;
  HDC pHVar7;
  HGDIOBJ pvVar8;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  int extraout_EDX_06;
  ShellButton *extraout_EDX_07;
  ShellButton *this;
  ShellButton *this_00;
  AnimButton *this_01;
  AnimButton *this_02;
  ShellButton *this_03;
  ShellButton *extraout_EDX_08;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  tagPAINTSTRUCT local_44;
  uint local_4;
  
  pSVar5 = b1Button;
  local_4 = __security_cookie ^ (uint)&local_44;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 == 2) {
        SnapShotBackground();
        CleanCurrentBackground();
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
        pAVar6 = b3Button;
        if (b3Button != (AnimButton *)0x0) {
          AnimButton::~AnimButton(b3Button);
          operator_delete(pAVar6);
          b3Button = (AnimButton *)0x0;
        }
        pAVar6 = b4Button;
        if (b4Button != (AnimButton *)0x0) {
          AnimButton::~AnimButton(b4Button);
          operator_delete(pAVar6);
          b4Button = (AnimButton *)0x0;
        }
        pAVar6 = poster;
        if (poster != (AnimButton *)0x0) {
          AnimButton::~AnimButton(poster);
          operator_delete(pAVar6);
          poster = (AnimButton *)0x0;
        }
        pTVar3 = usaLabel;
        if (usaLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(usaLabel);
          operator_delete(pTVar3);
          usaLabel = (TextLabel *)0x0;
        }
        pTVar3 = ussrLabel;
        if (ussrLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(ussrLabel);
          operator_delete(pTVar3);
          ussrLabel = (TextLabel *)0x0;
        }
        pTVar3 = trnLabel;
        if (trnLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(trnLabel);
          operator_delete(pTVar3);
          trnLabel = (TextLabel *)0x0;
        }
        pTVar3 = loadLabel;
        if (loadLabel == (TextLabel *)0x0) {
          return 0;
        }
        TextLabel::~TextLabel(loadLabel);
        operator_delete(pTVar3);
        loadLabel = (TextLabel *)0x0;
        return 0;
      }
      if (param_2 == 0xf) {
        pHVar7 = BeginPaint((HWND)param_1,&local_44);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(llButton,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(b1Button,(HDC__ *)pHVar7);
        ShellButton::UpdateButton(b2Button,(HDC__ *)pHVar7);
        pAVar6 = b3Button;
        b3Button->nStatusCommand = 1;
        pAVar6->nCommand = 1;
        AnimButton::movie_play(pAVar6,0,0);
        pAVar6 = b4Button;
        b4Button->nStatusCommand = 1;
        pAVar6->nCommand = 1;
        AnimButton::movie_play(pAVar6,0,0);
        TextLabel::DrawLabelText(usaLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(ussrLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(trnLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        TextLabel::DrawLabelText(loadLabel,(HDC__ *)pHVar7,(char *)0x0,0);
        EndPaint((HWND)param_1,&local_44);
        return 0;
      }
      if (param_2 != 0x14) {
        if (param_2 == 0x20) {
          set_cursor(0);
          SetWindowLongA((HWND)param_1,0,1);
        }
        else {
          if (param_2 != 0x110) {
            return 0;
          }
          nPosterMode = 0;
          init_screen_pos(param_1);
          init_bitmap_dc(param_1);
          pTVar3 = operator_new(0x128);
          if (pTVar3 == (TextLabel *)0x0) {
            usaLabel = (TextLabel *)0x0;
          }
          else {
            usaLabel = TextLabel::TextLabel
                                 (pTVar3,param_1,"STARS AND STRIPES",0x29,0x100,0x9d,0x15,0);
          }
          pTVar3 = operator_new(0x128);
          if (pTVar3 == (TextLabel *)0x0) {
            ussrLabel = (TextLabel *)0x0;
          }
          else {
            ussrLabel = TextLabel::TextLabel
                                  (pTVar3,param_1,"THE RED BRIGADE",0x1bc,0x100,0x9d,0x15,0);
          }
          pTVar3 = operator_new(0x128);
          if (pTVar3 == (TextLabel *)0x0) {
            trnLabel = (TextLabel *)0x0;
          }
          else {
            trnLabel = TextLabel::TextLabel
                                 (pTVar3,param_1,"COMBAT EXERCISES",0x46,0x18e,0xd2,0x14,0);
          }
          pTVar3 = operator_new(0x128);
          if (pTVar3 == (TextLabel *)0x0) {
            loadLabel = (TextLabel *)0x0;
          }
          else {
            loadLabel = TextLabel::TextLabel
                                  (pTVar3,param_1,"LOAD SAVED GAME",0x161,0x18e,0xd2,0x14,0);
          }
          pSVar4 = operator_new(0x20);
          if (pSVar4 == (ShellBitmap *)0x0) {
            backGround = (ShellBitmap *)0x0;
          }
          else {
            backGround = ShellBitmap::ShellBitmap(pSVar4,"bitmap\\singlep.bmp",0,0);
          }
          SetCurrentBackground(param_1,backGround);
          pSVar5 = operator_new(0x110);
          if (pSVar5 == (ShellButton *)0x0) {
            ulButton = (ShellButton *)0x0;
          }
          else {
            ulButton = ShellButton::ShellButton
                                 (pSVar5,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                                  "BACK");
          }
          pSVar5 = operator_new(0x110);
          if (pSVar5 == (ShellButton *)0x0) {
            llButton = (ShellButton *)0x0;
          }
          else {
            llButton = ShellButton::ShellButton
                                 (pSVar5,param_1,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                                  "OPTIONS");
          }
          ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
          ShellButton::SetLabelPos(llButton,0x2f,0x1c4,0x58,0x17);
          pSVar5 = operator_new(0x110);
          if (pSVar5 == (ShellButton *)0x0) {
            b1Button = (ShellButton *)0x0;
          }
          else {
            b1Button = ShellButton::ShellButton
                                 (pSVar5,param_1,shell_hInstance,0,0xfe,0x100,0x3e,0x39,0x75,0xc6,0,
                                  (char *)0x0);
          }
          pSVar5 = operator_new(0x110);
          if (pSVar5 == (ShellButton *)0x0) {
            b2Button = (ShellButton *)0x0;
          }
          else {
            b2Button = ShellButton::ShellButton
                                 (pSVar5,param_1,shell_hInstance,0,0xfd,0xff,0x1d0,0x39,0x75,0xc6,0,
                                  (char *)0x0);
          }
          ShellButton::SetSoundFile(b1Button,"shmroll.wav","shmclick.wav");
          ShellButton::SetSoundFile(b2Button,"shmroll.wav","shmclick.wav");
          pAVar6 = operator_new(0x14c);
          if (pAVar6 == (AnimButton *)0x0) {
            pAVar6 = (AnimButton *)0x0;
          }
          else {
            pAVar6 = AnimButton::AnimButton
                               (pAVar6,param_1,"anims\\posters.avi",0x3c,0xfc,0x25,0x8b,0xd3,4);
          }
          poster = pAVar6;
          pAVar6->nStatusCommand = 1;
          pAVar6->nCommand = 1;
          AnimButton::movie_play(pAVar6,0,0);
          pAVar6 = operator_new(0x14c);
          if (pAVar6 == (AnimButton *)0x0) {
            b3Button = (AnimButton *)0x0;
          }
          else {
            b3Button = AnimButton::AnimButton
                                 (pAVar6,param_1,"anims\\training.avi",0x1e,0x2a,0x121,0x8c,0x6e,2);
          }
          pAVar6 = operator_new(0x14c);
          if (pAVar6 == (AnimButton *)0x0) {
            b4Button = (AnimButton *)0x0;
          }
          else {
            b4Button = AnimButton::AnimButton
                                 (pAVar6,param_1,"anims\\loadgme.avi",0x1e,0x1e3,0x121,0x6e,0x6e,2);
          }
          read_text_label("single","back",ulButton->labelText);
          read_text_label("single","usa",usaLabel->textData);
          read_text_label("single","ussr",ussrLabel->textData);
          read_text_label("single","training",trnLabel->textData);
          read_text_label("single","load_saved_game",loadLabel->textData);
          read_text_label("single","options",llButton->labelText);
        }
        return 1;
      }
      return 1;
    }
    iVar12 = 4;
LAB_0057d286:
    pvVar8 = GetStockObject(iVar12);
    return (int)pvVar8;
  }
  if (param_2 == 0x138) {
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar12 = 5;
    goto LAB_0057d286;
  }
  if (param_2 == 0x200) {
    uVar9 = param_4 & 0xffff;
    iVar13 = 0;
    iVar11 = 1;
    uVar10 = (uint)param_4 >> 0x10;
    iVar12 = ShellButton::CheckRollOver(b1Button,uVar9,uVar10);
    ShellButton::SetButtonMode(this,iVar12,iVar11,iVar13);
    iVar13 = 0;
    iVar11 = 1;
    iVar12 = ShellButton::CheckRollOver(b2Button,uVar9,uVar10);
    ShellButton::SetButtonMode(this_00,iVar12,iVar11,iVar13);
    if (b1Button->nButtonMode == 0) {
      if (b2Button->nButtonMode == 0) {
        AnimButton::SetButtonMode(poster,0);
        nPosterMode = 0;
      }
      else if (nPosterMode != 2) {
        AnimButton::SetButtonMode(poster,0);
        pAVar6 = poster;
        poster->nStart = 0x1e;
        pAVar6->nEnd = 0x3b;
        AnimButton::SetButtonMode(pAVar6,1);
        nPosterMode = 2;
      }
    }
    else if (nPosterMode != 1) {
      AnimButton::SetButtonMode(poster,0);
      pAVar6 = poster;
      poster->nStart = 0;
      pAVar6->nEnd = 0x1d;
      AnimButton::SetButtonMode(pAVar6,1);
      nPosterMode = 1;
    }
    iVar12 = AnimButton::CheckRollOver(b3Button,uVar9,uVar10);
    iVar12 = AnimButton::SetButtonMode(this_01,iVar12);
    if (iVar12 != 0) {
      ShellPlaySound("shmroll.wav",100,0,-1);
    }
    iVar12 = AnimButton::CheckRollOver(b4Button,uVar9,uVar10);
    iVar12 = AnimButton::SetButtonMode(this_02,iVar12);
    if (iVar12 != 0) {
      ShellPlaySound("shmroll.wav",100,0,-1);
    }
    iVar13 = 0;
    iVar11 = 1;
    iVar12 = ShellButton::CheckRollOver(ulButton,uVar9,uVar10);
    ShellButton::SetButtonMode(this_03,iVar12,iVar11,iVar13);
    iVar13 = 0;
    iVar11 = 1;
    iVar12 = ShellButton::CheckRollOver(llButton,uVar9,uVar10);
    pSVar5 = extraout_EDX_08;
LAB_0057d266:
    ShellButton::SetButtonMode(pSVar5,iVar12,iVar11,iVar13);
    return 0;
  }
  if (param_2 == 0x201) {
    uVar9 = param_4 & 0xffff;
    iVar12 = ShellButton::CheckRollOver(b1Button,uVar9,(uint)param_4 >> 0x10);
    pSVar1 = b2Button;
    if (((iVar12 == 0) &&
        (iVar12 = ShellButton::CheckRollOver(b2Button,uVar9,extraout_EDX_04), pSVar2 = ulButton,
        pSVar5 = pSVar1, iVar12 == 0)) &&
       (iVar12 = ShellButton::CheckRollOver(ulButton,uVar9,extraout_EDX_05), pSVar5 = pSVar2,
       iVar12 == 0)) {
      iVar12 = ShellButton::CheckRollOver(llButton,uVar9,extraout_EDX_06);
      if (iVar12 == 0) {
        return 0;
      }
      iVar13 = 0;
      iVar11 = 1;
      iVar12 = 2;
      pSVar5 = extraout_EDX_07;
    }
    else {
      iVar13 = 0;
      iVar11 = 1;
      iVar12 = 2;
    }
    goto LAB_0057d266;
  }
  if (param_2 != 0x202) {
    if (param_2 != 0x3b9) {
      return 0;
    }
    if (b3Button != (AnimButton *)0x0) {
      AnimButton::movie_check(b3Button,param_3,param_4);
    }
    if (b4Button != (AnimButton *)0x0) {
      AnimButton::movie_check(b4Button,param_3,param_4);
    }
    AnimButton::movie_check(poster,param_3,param_4);
    return 0;
  }
  uVar9 = param_4 & 0xffff;
  iVar12 = ShellButton::CheckRollOver(b1Button,uVar9,(uint)param_4 >> 0x10);
  if (iVar12 == 0) {
    iVar12 = ShellButton::CheckRollOver(b2Button,uVar9,extraout_EDX);
    if (iVar12 == 0) {
      iVar12 = AnimButton::CheckRollOver(b3Button,uVar9,extraout_EDX_00);
      if (iVar12 != 0) {
        ShellPlaySound("shmclick.wav",100,0,-1);
        nMissionCurrentIndex = 0;
        nShellMode = 9;
LAB_0057d004:
        Shell_EndDialog(param_1,1);
        return 0;
      }
      iVar12 = AnimButton::CheckRollOver(b4Button,uVar9,extraout_EDX_01);
      if (iVar12 != 0) {
        ShellPlaySound("shmclick.wav",100,0,-1);
        nReplayIntro = 0;
        nPlayCredits = 0;
        nShellMode = 0x12;
        goto LAB_0057d004;
      }
      iVar12 = ShellButton::CheckRollOver(ulButton,uVar9,extraout_EDX_02);
      if (iVar12 == 0) {
        iVar12 = ShellButton::CheckRollOver(llButton,uVar9,extraout_EDX_03);
        if (iVar12 == 0) {
          return 0;
        }
        ShowWindow((HWND)param_1,0);
        EnableWindow((HWND)param_1,0);
        do_options(0);
        SetCurrentBackground(param_1,backGround);
        Shell_EndDialog(param_1,1);
        return 0;
      }
      nShellMode = 1;
      goto LAB_0057d02f;
    }
    if (nDemoFlag != 0) {
      TextLabel::DrawLabelText(ussrLabel,"NOT IN DEMO",0);
      return 0;
    }
    nShellMode = 8;
  }
  else {
    nShellMode = 7;
  }
  nMissionCurrentIndex = 0;
LAB_0057d02f:
  Shell_EndDialog(param_1,1);
  return 0;
}
