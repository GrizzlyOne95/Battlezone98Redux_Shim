/*
 * Entry: 00554505
 * Name: PasswordDlgProc
 * Namespace: Global
 * Signature: int PasswordDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PasswordDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND pHVar1;
  ShellBitmap *pSVar2;
  TextLabel *pTVar3;
  ShellButton *pSVar4;
  HDC pHVar5;
  HGDIOBJ pvVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int nHeight;
  int iVar10;
  tagPOINT *lpPoint;
  BOOL bRepaint;
  tagPOINT local_60;
  tagRECT local_58;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar5 = BeginPaint((HWND)param_1,&local_48);
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar5);
          TextLabel::DrawLabelText(passwordLabel,(HDC__ *)pHVar5,(char *)0x0,1);
          ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(okButton,(HDC__ *)pHVar5);
          EndPaint((HWND)param_1,&local_48);
          return 0;
        }
        if (param_2 != 0x14) {
          if (param_2 == 0x20) {
            set_cursor(0);
            SetWindowLongA((HWND)param_1,0,1);
          }
          else if (param_2 == 0x110) {
            SetFontRecursive(param_1);
            GetClientRect((HWND)shell_hwnd,&local_58);
            local_60.x = local_58.left + 0xca;
            local_60.y = local_58.top + 0xc1;
            lpPoint = &local_60;
            pHVar1 = GetWindow((HWND)param_1,4);
            ClientToScreen(pHVar1,lpPoint);
            local_58.left = local_58.left + local_60.x;
            local_58.right = local_58.right + local_60.x;
            local_58.top = local_58.top + local_60.y;
            local_58.bottom = local_58.bottom + local_60.y;
            MoveWindow((HWND)param_1,local_58.left,local_58.top,0xed,0x5e,1);
            pSVar2 = operator_new(0x20);
            if (pSVar2 == (ShellBitmap *)0x0) {
              backGround = (ShellBitmap *)0x0;
            }
            else {
              backGround = ShellBitmap::ShellBitmap(pSVar2,"bitmap\\popup2.bmp",0,0);
            }
            pTVar3 = operator_new(0x128);
            if (pTVar3 == (TextLabel *)0x0) {
              passwordLabel = (TextLabel *)0x0;
            }
            else {
              passwordLabel = TextLabel::TextLabel(pTVar3,param_1,"Password",0xd,0x12,0x66,0x18,0);
            }
            bRepaint = 1;
            nHeight = 0x10;
            iVar8 = 0x69;
            iVar7 = 0x16;
            iVar10 = 0x78;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
            MoveWindow(pHVar1,iVar10,iVar7,iVar8,nHeight,bRepaint);
            SendDlgItemMessageA((HWND)param_1,0x7f8,0xc5,10,0);
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              okButton = (ShellButton *)0x0;
            }
            else {
              okButton = ShellButton::ShellButton
                                   (pSVar4,param_1,shell_hInstance,0x836,0x837,0x835,1,0x40,0x75,
                                    0x1e,1,"Ok");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              cancelButton = (ShellButton *)0x0;
            }
            else {
              cancelButton = ShellButton::ShellButton
                                       (pSVar4,param_1,shell_hInstance,0x839,0x83a,0x838,0x76,0x40,
                                        0x75,0x1e,1,"Cancel");
            }
            pcVar9 = "";
            pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
            SetWindowTextA(pHVar1,pcVar9);
            read_text_label("multi_popup","ok_button",okButton->labelText);
            read_text_label("multi_popup","cancel_button",cancelButton->labelText);
            read_text_label("multi_popup","password",passwordLabel->textData);
          }
          else {
            if (param_2 != 0x111) {
              return 0;
            }
            if ((param_3 & 0xffff) == 1) {
              iVar10 = 100;
              pcVar9 = do_password_password;
              pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
              GetWindowTextA(pHVar1,pcVar9,iVar10);
              iVar10 = 1;
            }
            else {
              if ((param_3 & 0xffff) != 2) {
                return 0;
              }
              iVar10 = 0;
            }
            Shell_EndDialog(param_1,iVar10);
          }
        }
        return 1;
      }
      ReleaseCapture();
      pSVar2 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar2);
      }
      pTVar3 = passwordLabel;
      if (passwordLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(passwordLabel);
        operator_delete(pTVar3);
      }
      pSVar4 = cancelButton;
      if (cancelButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(cancelButton);
        operator_delete(pSVar4);
      }
      pSVar4 = okButton;
      if (okButton == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(okButton);
      operator_delete(pSVar4);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  else {
    if (param_2 == 0x136) goto LAB_0055499a;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar8 = 1;
        iVar7 = 1;
        iVar10 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        ShellButton::SetButtonMode(okButton,iVar10,iVar7,iVar8);
        iVar8 = 1;
        iVar7 = 1;
        iVar10 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        pSVar4 = cancelButton;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar10 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar10 == 0) {
            iVar10 = ShellButton::CheckRollOver
                               (cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
            if (iVar10 == 0) {
              return 0;
            }
            iVar10 = 0;
          }
          else {
            iVar10 = 100;
            pcVar9 = do_password_password;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
            GetWindowTextA(pHVar1,pcVar9,iVar10);
            iVar10 = 1;
          }
          Shell_EndDialog(param_1,iVar10);
          return 0;
        }
        iVar10 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        if (iVar10 == 0) {
          iVar10 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar10 == 0) {
            return 0;
          }
          iVar8 = 1;
          iVar7 = 1;
          iVar10 = 2;
          pSVar4 = cancelButton;
        }
        else {
          iVar8 = 1;
          iVar7 = 1;
          iVar10 = 2;
          pSVar4 = okButton;
        }
      }
      ShellButton::SetButtonMode(pSVar4,iVar10,iVar7,iVar8);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_0055499a:
  pvVar6 = GetStockObject(4);
  return (int)pvVar6;
}
