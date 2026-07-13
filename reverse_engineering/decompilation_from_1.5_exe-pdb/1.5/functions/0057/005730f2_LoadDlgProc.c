/*
 * Entry: 005730f2
 * Name: LoadDlgProc
 * Namespace: Global
 * Signature: int LoadDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl LoadDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  ShellBitmap *pSVar1;
  ShellButton *pSVar2;
  TextLabel *pTVar3;
  int iVar4;
  HWND pHVar5;
  HDC pHVar6;
  HGDIOBJ pvVar7;
  int extraout_EDX;
  ShellButton *extraout_EDX_00;
  ShellButton *extraout_EDX_01;
  ShellButton *extraout_EDX_02;
  ShellButton *this;
  ShellButton *this_00;
  ShellButton *this_01;
  ShellButton *this_02;
  ShellButton *this_03;
  ShellButton **ppSVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int nHeight;
  BOOL bRepaint;
  int local_48;
  tagPAINTSTRUCT local_44;
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)&local_48;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 == 2) {
        CleanCurrentBackground();
        SnapShotBackground();
        pSVar1 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar1);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar2 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar2);
          ulButton = (ShellButton *)0x0;
        }
        pSVar2 = okButton;
        if (okButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(okButton);
          operator_delete(pSVar2);
          okButton = (ShellButton *)0x0;
        }
        pSVar2 = cancelButton;
        if (cancelButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(cancelButton);
          operator_delete(pSVar2);
          cancelButton = (ShellButton *)0x0;
        }
        ppSVar8 = slotArray;
        do {
          pSVar2 = *ppSVar8;
          if (pSVar2 != (ShellButton *)0x0) {
            ShellButton::~ShellButton(pSVar2);
            operator_delete(pSVar2);
            *ppSVar8 = (ShellButton *)0x0;
          }
          pTVar3 = message;
          ppSVar8 = ppSVar8 + 1;
        } while ((int)ppSVar8 < 0xc8fad4);
        if (message != (TextLabel *)0x0) {
          TextLabel::~TextLabel(message);
          operator_delete(pTVar3);
          message = (TextLabel *)0x0;
        }
        return 0;
      }
      if (param_2 == 0xf) {
        pHVar6 = BeginPaint((HWND)param_1,&local_44);
        ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar6);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar6);
        ShellButton::UpdateButton(okButton,(HDC__ *)pHVar6);
        ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar6);
        ppSVar8 = slotArray;
        do {
          ShellButton::UpdateButton(*ppSVar8,(HDC__ *)pHVar6);
          ppSVar8 = ppSVar8 + 1;
        } while ((int)ppSVar8 < 0xc8fad4);
        TextLabel::DrawLabelText(message,(HDC__ *)pHVar6,(char *)0x0,0);
        EndPaint((HWND)param_1,&local_44);
      }
      else if (param_2 != 0x14) {
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
          nType = (int)(param_4 != 0xb);
          nCaller = param_4;
          pSVar1 = operator_new(0x20);
          if (pSVar1 == (ShellBitmap *)0x0) {
            backGround = (ShellBitmap *)0x0;
          }
          else {
            backGround = ShellBitmap::ShellBitmap(pSVar1,"bitmap\\saveload.bmp",0,0);
          }
          SetCurrentBackground(param_1,backGround);
          pSVar2 = operator_new(0x110);
          if (pSVar2 == (ShellButton *)0x0) {
            ulButton = (ShellButton *)0x0;
          }
          else {
            ulButton = ShellButton::ShellButton
                                 (pSVar2,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                                  "BACK");
          }
          ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
          pSVar2 = operator_new(0x110);
          if (pSVar2 == (ShellButton *)0x0) {
            okButton = (ShellButton *)0x0;
          }
          else {
            okButton = ShellButton::ShellButton
                                 (pSVar2,param_1,shell_hInstance,0x831,0x832,0x830,0x17f,0x105,0x62,
                                  0x22,1,"Ok");
          }
          ShellButton::HideButton(okButton,0);
          pSVar2 = operator_new(0x110);
          if (pSVar2 == (ShellButton *)0x0) {
            cancelButton = (ShellButton *)0x0;
          }
          else {
            cancelButton = ShellButton::ShellButton
                                     (pSVar2,param_1,shell_hInstance,0x831,0x832,0x830,0x1ec,0x105,
                                      0x62,0x22,1,"Cancel");
          }
          ShellButton::HideButton(cancelButton,0);
          ppSVar8 = slotArray;
          iVar10 = 0x50;
          do {
            pSVar2 = operator_new(0x110);
            if (pSVar2 == (ShellButton *)0x0) {
              pSVar2 = (ShellButton *)0x0;
            }
            else {
              pSVar2 = ShellButton::ShellButton
                                 (pSVar2,param_1,shell_hInstance,0x834,0x833,0x833,0x3c,iVar10,0x9c,
                                  0x1a,1,"Empty");
            }
            *ppSVar8 = pSVar2;
            iVar10 = iVar10 + 0x1e;
            ppSVar8 = ppSVar8 + 1;
          } while (iVar10 < 0x17c);
          pTVar3 = operator_new(0x128);
          if (pTVar3 == (TextLabel *)0x0) {
            message = (TextLabel *)0x0;
          }
          else {
            message = TextLabel::TextLabel(pTVar3,param_1,"not used",400,0xb4,0xdc,0x14,0);
          }
          TextLabel::HideLabelText(message,0);
          read_text_label("missions","back",ulButton->labelText);
          ppSVar8 = slotArray;
          do {
            read_text_label("multi_error","Empty",(*ppSVar8)->labelText);
            ppSVar8 = ppSVar8 + 1;
          } while ((int)ppSVar8 < 0xc8fad4);
          iVar10 = 0;
          do {
            local_48 = iVar10 + 1;
            iVar4 = GetSaveDesc(local_48,slotArray[iVar10]);
            gameFlag[iVar10] = iVar4;
            iVar10 = local_48;
          } while (local_48 < 10);
          bRepaint = 1;
          nHeight = 0x14;
          iVar12 = 0xdc;
          iVar4 = 0xdc;
          iVar10 = 400;
          pHVar5 = GetDlgItem((HWND)param_1,0x427);
          MoveWindow(pHVar5,iVar10,iVar4,iVar12,nHeight,bRepaint);
          iVar10 = 0;
          pHVar5 = GetDlgItem((HWND)param_1,0x427);
          ShowWindow(pHVar5,iVar10);
        }
      }
      return 1;
    }
    SetTextColor((HDC)param_3,0xff00);
    SetBkMode((HDC)param_3,1);
  }
  else if (param_2 != 0x136) {
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        uVar11 = param_4 & 0xffff;
        iVar12 = 0;
        iVar4 = 1;
        uVar9 = (uint)param_4 >> 0x10;
        iVar10 = ShellButton::CheckRollOver(ulButton,uVar11,uVar9);
        ShellButton::SetButtonMode(this_00,iVar10,iVar4,iVar12);
        iVar12 = 0;
        iVar4 = 1;
        iVar10 = ShellButton::CheckRollOver(okButton,uVar11,uVar9);
        ShellButton::SetButtonMode(this_01,iVar10,iVar4,iVar12);
        iVar12 = 0;
        iVar4 = 1;
        iVar10 = ShellButton::CheckRollOver(cancelButton,uVar11,uVar9);
        ShellButton::SetButtonMode(this_02,iVar10,iVar4,iVar12);
        ppSVar8 = slotArray;
        do {
          iVar12 = 0;
          iVar4 = 1;
          iVar10 = ShellButton::CheckRollOver(*ppSVar8,uVar11,uVar9);
          ShellButton::SetButtonMode(this_03,iVar10,iVar4,iVar12);
          ppSVar8 = ppSVar8 + 1;
        } while ((int)ppSVar8 < 0xc8fad4);
        return 0;
      }
      if (param_2 == 0x201) {
        uVar11 = param_4 & 0xffff;
        uVar9 = (uint)param_4 >> 0x10;
        iVar10 = ShellButton::CheckRollOver(ulButton,uVar11,uVar9);
        pSVar2 = extraout_EDX_00;
        if (((iVar10 == 0) &&
            (iVar10 = ShellButton::CheckRollOver(okButton,uVar11,uVar9), pSVar2 = extraout_EDX_01,
            iVar10 == 0)) &&
           (iVar10 = ShellButton::CheckRollOver(cancelButton,uVar11,uVar9), pSVar2 = extraout_EDX_02
           , iVar10 == 0)) {
          ppSVar8 = slotArray;
          do {
            iVar10 = ShellButton::CheckRollOver(*ppSVar8,uVar11,uVar9);
            if (iVar10 != 0) {
              ShellButton::SetButtonMode(this,2,1,0);
            }
            ppSVar8 = ppSVar8 + 1;
          } while ((int)ppSVar8 < 0xc8fad4);
          return 0;
        }
        ShellButton::SetButtonMode(pSVar2,2,1,0);
        return 0;
      }
      if (param_2 != 0x202) {
        return 0;
      }
      uVar9 = param_4 & 0xffff;
      uVar11 = (uint)param_4 >> 0x10;
      iVar10 = ShellButton::CheckRollOver(ulButton,uVar9,uVar11);
      if (iVar10 != 0) {
        nLoadStarted = 0;
        nShellMode = lastShellMode;
        Shell_EndDialog(param_1,0);
        return 0;
      }
      iVar10 = ShellButton::CheckRollOver(okButton,uVar9,uVar11);
      if (iVar10 != 0) {
        return 0;
      }
      iVar10 = ShellButton::CheckRollOver(cancelButton,uVar9,uVar11);
      if (iVar10 != 0) {
        return 0;
      }
      iVar10 = 0;
      do {
        iVar10 = ShellButton::CheckRollOver(slotArray[iVar10],uVar9,uVar11);
        if (iVar10 != 0) {
          if (gameFlag[extraout_EDX] == 0) {
            return 0;
          }
          nLoadStarted = 1;
          load_bzone_game(extraout_EDX + 1);
          nShellMode = 0;
          Shell_EndDialog(param_1,1);
          return 0;
        }
        iVar10 = extraout_EDX + 1;
      } while (iVar10 < 10);
      return 0;
    }
    SetTextColor((HDC)param_3,0x200ff00);
    SetBkMode((HDC)param_3,1);
    iVar10 = 5;
    goto LAB_00573540;
  }
  iVar10 = 4;
LAB_00573540:
  pvVar7 = GetStockObject(iVar10);
  return (int)pvVar7;
}
