/*
 * Entry: 00553f12
 * Name: GameDlgProc
 * Namespace: Global
 * Signature: int GameDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GameDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND pHVar1;
  ShellBitmap *pSVar2;
  TextLabel *pTVar3;
  ShellButton *pSVar4;
  HDC pHVar5;
  HGDIOBJ pvVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  tagPOINT *lpPoint;
  BOOL BVar12;
  tagPOINT local_64;
  tagRECT local_5c;
  HWND__ *local_4c;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_4c = param_1;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar5 = BeginPaint((HWND)param_1,&local_48);
          if (backGround != (ShellBitmap *)0x0) {
            ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar5);
          }
          if (nameLabel != (TextLabel *)0x0) {
            TextLabel::DrawLabelText(nameLabel,(HDC__ *)pHVar5,(char *)0x0,1);
          }
          if (passwordLabel != (TextLabel *)0x0) {
            TextLabel::DrawLabelText(passwordLabel,(HDC__ *)pHVar5,(char *)0x0,1);
          }
          if (cancelButton != (ShellButton *)0x0) {
            ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar5);
          }
          if (okButton != (ShellButton *)0x0) {
            ShellButton::UpdateButton(okButton,(HDC__ *)pHVar5);
          }
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
            GetClientRect((HWND)shell_hwnd,&local_5c);
            local_64.x = local_5c.left + 0xca;
            local_64.y = local_5c.top + 0xc1;
            lpPoint = &local_64;
            pHVar1 = GetWindow((HWND)param_1,4);
            ClientToScreen(pHVar1,lpPoint);
            local_5c.left = local_5c.left + local_64.x;
            local_5c.right = local_5c.right + local_64.x;
            local_5c.top = local_5c.top + local_64.y;
            local_5c.bottom = local_5c.bottom + local_64.y;
            MoveWindow((HWND)param_1,local_5c.left,local_5c.top,0xed,0x5e,1);
            pSVar2 = operator_new(0x20);
            if (pSVar2 == (ShellBitmap *)0x0) {
              backGround = (ShellBitmap *)0x0;
            }
            else {
              backGround = ShellBitmap::ShellBitmap(pSVar2,"bitmap\\popup.bmp",0,0);
            }
            pTVar3 = operator_new(0x128);
            if (pTVar3 == (TextLabel *)0x0) {
              nameLabel = (TextLabel *)0x0;
            }
            else {
              nameLabel = TextLabel::TextLabel(pTVar3,param_1,"Game Name",4,4,0x71,0x1a,0);
            }
            pTVar3 = operator_new(0x128);
            if (pTVar3 == (TextLabel *)0x0) {
              passwordLabel = (TextLabel *)0x0;
            }
            else {
              passwordLabel = TextLabel::TextLabel(pTVar3,param_1,"Password",4,0x21,0x71,0x1a,0);
            }
            BVar12 = 1;
            iVar9 = 0x10;
            iVar8 = 0x72;
            iVar7 = 9;
            iVar11 = 0x78;
            pHVar1 = GetDlgItem((HWND)param_1,0x7e0);
            MoveWindow(pHVar1,iVar11,iVar7,iVar8,iVar9,BVar12);
            BVar12 = 1;
            iVar9 = 0x10;
            iVar8 = 0x72;
            iVar7 = 0x25;
            iVar11 = 0x78;
            pHVar1 = GetDlgItem((HWND)local_4c,0x7f8);
            MoveWindow(pHVar1,iVar11,iVar7,iVar8,iVar9,BVar12);
            SendDlgItemMessageA((HWND)local_4c,0x7f8,0xc5,10,0);
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              okButton = (ShellButton *)0x0;
            }
            else {
              okButton = ShellButton::ShellButton
                                   (pSVar4,local_4c,shell_hInstance,0x836,0x837,0x835,1,0x40,0x75,
                                    0x1e,1,"Ok");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              cancelButton = (ShellButton *)0x0;
            }
            else {
              cancelButton = ShellButton::ShellButton
                                       (pSVar4,local_4c,shell_hInstance,0x839,0x83a,0x838,0x76,0x40,
                                        0x75,0x1e,1,"Cancel");
            }
            pcVar10 = net_defaults.gamename;
            pHVar1 = GetDlgItem((HWND)local_4c,0x7e0);
            SetWindowTextA(pHVar1,pcVar10);
            pcVar10 = net_defaults.password;
            pHVar1 = GetDlgItem((HWND)local_4c,0x7f8);
            SetWindowTextA(pHVar1,pcVar10);
            read_text_label("multi_popup","ok_button",okButton->labelText);
            read_text_label("multi_popup","cancel_button",cancelButton->labelText);
            read_text_label("multi_popup","game_name",nameLabel->textData);
            read_text_label("multi_popup","password",passwordLabel->textData);
          }
          else {
            if (param_2 != 0x111) {
              return 0;
            }
            if ((param_3 & 0xffff) == 1) {
              iVar11 = 0x20;
              pcVar10 = net_defaults.gamename;
              net_defaults.gamename[0] = '\0';
              net_defaults.password[0] = '\0';
              pHVar1 = GetDlgItem((HWND)param_1,0x7e0);
              GetWindowTextA(pHVar1,pcVar10,iVar11);
              iVar11 = 0xb;
              pcVar10 = net_defaults.password;
              pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
              GetWindowTextA(pHVar1,pcVar10,iVar11);
              iVar11 = 1;
            }
            else {
              if ((param_3 & 0xffff) != 2) {
                return 0;
              }
              iVar11 = 0;
            }
            Shell_EndDialog(param_1,iVar11);
          }
        }
        return 1;
      }
      ReleaseCapture();
      pSVar2 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar2);
        backGround = (ShellBitmap *)0x0;
      }
      pTVar3 = nameLabel;
      if (nameLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(nameLabel);
        operator_delete(pTVar3);
        nameLabel = (TextLabel *)0x0;
      }
      pTVar3 = passwordLabel;
      if (passwordLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(passwordLabel);
        operator_delete(pTVar3);
        passwordLabel = (TextLabel *)0x0;
      }
      pSVar4 = cancelButton;
      if (cancelButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(cancelButton);
        operator_delete(pSVar4);
        cancelButton = (ShellButton *)0x0;
      }
      pSVar4 = okButton;
      if (okButton == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(okButton);
      operator_delete(pSVar4);
      okButton = (ShellButton *)0x0;
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  else {
    if (param_2 == 0x136) goto LAB_005544cb;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar8 = 1;
        iVar7 = 1;
        iVar11 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        ShellButton::SetButtonMode(okButton,iVar11,iVar7,iVar8);
        iVar8 = 1;
        iVar7 = 1;
        iVar11 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        pSVar4 = cancelButton;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar11 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar11 == 0) {
            iVar11 = ShellButton::CheckRollOver
                               (cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
            if (iVar11 == 0) {
              return 0;
            }
            iVar11 = 0;
          }
          else {
            iVar11 = 0x20;
            pcVar10 = net_defaults.gamename;
            net_defaults.gamename[0] = '\0';
            net_defaults.password[0] = '\0';
            pHVar1 = GetDlgItem((HWND)param_1,0x7e0);
            GetWindowTextA(pHVar1,pcVar10,iVar11);
            iVar11 = 0xb;
            pcVar10 = net_defaults.password;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
            GetWindowTextA(pHVar1,pcVar10,iVar11);
            iVar11 = 1;
          }
          Shell_EndDialog(param_1,iVar11);
          return 0;
        }
        iVar11 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        if (iVar11 == 0) {
          iVar11 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar11 == 0) {
            return 0;
          }
          iVar8 = 1;
          iVar7 = 1;
          iVar11 = 2;
          pSVar4 = cancelButton;
        }
        else {
          iVar8 = 1;
          iVar7 = 1;
          iVar11 = 2;
          pSVar4 = okButton;
        }
      }
      ShellButton::SetButtonMode(pSVar4,iVar11,iVar7,iVar8);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_005544cb:
  pvVar6 = GetStockObject(4);
  return (int)pvVar6;
}
