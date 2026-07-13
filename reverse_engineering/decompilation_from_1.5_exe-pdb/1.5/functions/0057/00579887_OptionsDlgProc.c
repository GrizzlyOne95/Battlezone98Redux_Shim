/*
 * Entry: 00579887
 * Name: OptionsDlgProc
 * Namespace: Global
 * Signature: int OptionsDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl OptionsDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellButton *pSVar1;
  ShellButton *pSVar2;
  ShellBitmap *pSVar3;
  ShellButton *pSVar4;
  HDC pHVar5;
  HGDIOBJ pvVar6;
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
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *extraout_EDX_08;
  code *pcVar7;
  uint uVar8;
  code *pcVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  pSVar4 = b1Button;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x137) {
    if (param_2 != 0x136) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar5 = BeginPaint((HWND)param_1,&local_48);
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(b1Button,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(b2Button,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(b3Button,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(b4Button,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar5);
          EndPaint((HWND)param_1,&local_48);
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
            init_screen_pos(param_1);
            init_bitmap_dc(param_1);
            nCallMode = param_4;
            pSVar3 = operator_new(0x20);
            if (pSVar3 == (ShellBitmap *)0x0) {
              backGround = (ShellBitmap *)0x0;
            }
            else {
              backGround = ShellBitmap::ShellBitmap(pSVar3,"bitmap\\esc.bmp",0,0);
            }
            SetCurrentBackground(param_1,backGround);
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              ulButton = (ShellButton *)0x0;
            }
            else {
              ulButton = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1
                                    ,"BACK");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              b1Button = (ShellButton *)0x0;
            }
            else {
              b1Button = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0x5c,0xbc,0x3a
                                    ,1,"PLAY OPTIONS");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              b2Button = (ShellButton *)0x0;
            }
            else {
              b2Button = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0xab,0xbc,0x3a
                                    ,1,"GRAPHIC OPTIONS");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              b3Button = (ShellButton *)0x0;
            }
            else {
              b3Button = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0xfa,0xbc,0x3a
                                    ,1,"AUDIO OPTIONS");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              b4Button = (ShellButton *)0x0;
            }
            else {
              b4Button = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0,0x10c,0x10d,0xe2,0x149,0xbc,
                                    0x3a,1,"INPUT CONFIGURATION");
            }
            ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
            read_text_label("options","play_options",b1Button->labelText);
            read_text_label("options","graphic_options",b2Button->labelText);
            read_text_label("options","audio_options",b3Button->labelText);
            read_text_label("options","input_config",b4Button->labelText);
            read_text_label("options","back",ulButton->labelText);
          }
        }
        return 1;
      }
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
      pSVar4 = b1Button;
      if (b1Button != (ShellButton *)0x0) {
        ShellButton::~ShellButton(b1Button);
        operator_delete(pSVar4);
        b1Button = (ShellButton *)0x0;
      }
      pSVar4 = b2Button;
      if (b2Button != (ShellButton *)0x0) {
        ShellButton::~ShellButton(b2Button);
        operator_delete(pSVar4);
        b2Button = (ShellButton *)0x0;
      }
      pSVar4 = b3Button;
      if (b3Button != (ShellButton *)0x0) {
        ShellButton::~ShellButton(b3Button);
        operator_delete(pSVar4);
        b3Button = (ShellButton *)0x0;
      }
      pSVar4 = b4Button;
      if (b4Button == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(b4Button);
      operator_delete(pSVar4);
      b4Button = (ShellButton *)0x0;
      return 0;
    }
    iVar12 = 4;
  }
  else {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar8 = param_4 & 0xffff;
        iVar13 = 0;
        iVar11 = 1;
        uVar10 = (uint)param_4 >> 0x10;
        iVar12 = ShellButton::CheckRollOver(b1Button,uVar8,uVar10);
        ShellButton::SetButtonMode(this,iVar12,iVar11,iVar13);
        iVar13 = 0;
        iVar11 = 1;
        iVar12 = ShellButton::CheckRollOver(b2Button,uVar8,uVar10);
        ShellButton::SetButtonMode(this_00,iVar12,iVar11,iVar13);
        iVar13 = 0;
        iVar11 = 1;
        iVar12 = ShellButton::CheckRollOver(b3Button,uVar8,uVar10);
        ShellButton::SetButtonMode(this_01,iVar12,iVar11,iVar13);
        iVar13 = 0;
        iVar11 = 1;
        iVar12 = ShellButton::CheckRollOver(b4Button,uVar8,uVar10);
        ShellButton::SetButtonMode(this_02,iVar12,iVar11,iVar13);
        iVar13 = 0;
        iVar11 = 1;
        iVar12 = ShellButton::CheckRollOver(ulButton,uVar8,uVar10);
        pSVar4 = extraout_EDX_08;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          uVar8 = param_4 & 0xffff;
          iVar12 = ShellButton::CheckRollOver(b1Button,uVar8,(uint)param_4 >> 0x10);
          pcVar7 = ShowWindow_exref;
          if (iVar12 == 0) {
            iVar12 = ShellButton::CheckRollOver(b2Button,uVar8,extraout_EDX);
            pcVar7 = ShowWindow_exref;
            if (iVar12 == 0) {
              iVar12 = ShellButton::CheckRollOver(b3Button,uVar8,extraout_EDX_00);
              pcVar7 = ShowWindow_exref;
              if (iVar12 == 0) {
                iVar12 = ShellButton::CheckRollOver(b4Button,uVar8,extraout_EDX_01);
                if (iVar12 != 0) {
                  ShowWindow((HWND)param_1,0);
                  EnableWindow((HWND)param_1,0);
                  if (nCallMode != 0) {
                    LastInputs();
                  }
                  do_input_config();
                  SetCurrentBackground(param_1,backGround);
                  UnlockMouse();
                  if (nCallMode != 0) {
                    FirstInputs();
                    UnlockMouse();
                  }
                  EnableWindow((HWND)param_1,1);
                  ShowWindow((HWND)param_1,5);
                  return 1;
                }
                iVar12 = ShellButton::CheckRollOver(ulButton,uVar8,extraout_EDX_02);
                if (iVar12 == 0) {
                  return 0;
                }
                Shell_EndDialog(param_1,1);
                return 0;
              }
              ShowWindow((HWND)param_1,0);
              pcVar9 = EnableWindow_exref;
              EnableWindow((HWND)param_1,0);
              do_audio_options();
            }
            else {
              ShowWindow((HWND)param_1,0);
              pcVar9 = EnableWindow_exref;
              EnableWindow((HWND)param_1,0);
              do_graphic_options();
            }
            SetCurrentBackground(param_1,backGround);
          }
          else {
            ShowWindow((HWND)param_1,0);
            pcVar9 = EnableWindow_exref;
            EnableWindow((HWND)param_1,0);
            do_play_options(nCallMode);
            SetCurrentBackground(param_1,backGround);
          }
          (*pcVar9)(param_1,1);
          (*pcVar7)(param_1,5);
          return 0;
        }
        uVar8 = param_4 & 0xffff;
        iVar12 = ShellButton::CheckRollOver(b1Button,uVar8,(uint)param_4 >> 0x10);
        pSVar1 = b2Button;
        if ((((iVar12 == 0) &&
             (iVar12 = ShellButton::CheckRollOver(b2Button,uVar8,extraout_EDX_03), pSVar2 = b3Button
             , pSVar4 = pSVar1, iVar12 == 0)) &&
            (iVar12 = ShellButton::CheckRollOver(b3Button,uVar8,extraout_EDX_04), pSVar1 = b4Button,
            pSVar4 = pSVar2, iVar12 == 0)) &&
           (iVar12 = ShellButton::CheckRollOver(b4Button,uVar8,extraout_EDX_05), pSVar4 = pSVar1,
           iVar12 == 0)) {
          iVar12 = ShellButton::CheckRollOver(ulButton,uVar8,extraout_EDX_06);
          if (iVar12 == 0) {
            return 0;
          }
          iVar13 = 0;
          iVar11 = 1;
          iVar12 = 2;
          pSVar4 = extraout_EDX_07;
        }
        else {
          iVar13 = 0;
          iVar11 = 1;
          iVar12 = 2;
        }
      }
      ShellButton::SetButtonMode(pSVar4,iVar12,iVar11,iVar13);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar12 = 5;
  }
  pvVar6 = GetStockObject(iVar12);
  return (int)pvVar6;
}
