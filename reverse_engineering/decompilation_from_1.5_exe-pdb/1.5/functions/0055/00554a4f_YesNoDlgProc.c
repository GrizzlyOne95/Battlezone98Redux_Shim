/*
 * Entry: 00554a4f
 * Name: YesNoDlgProc
 * Namespace: Global
 * Signature: int YesNoDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl YesNoDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND hWnd;
  ShellBitmap *pSVar1;
  TextLabel *pTVar2;
  ShellButton *pSVar3;
  HDC pHVar4;
  HGDIOBJ pvVar5;
  int iVar6;
  int iVar7;
  tagPOINT *lpPoint;
  int iVar8;
  tagPOINT local_60;
  tagRECT local_58;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar4 = BeginPaint((HWND)param_1,&local_48);
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar4);
          TextLabel::DrawLabelText(messageLabel,(HDC__ *)pHVar4,(char *)0x0,1);
          ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar4);
          ShellButton::UpdateButton(okButton,(HDC__ *)pHVar4);
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
            hWnd = GetWindow((HWND)param_1,4);
            ClientToScreen(hWnd,lpPoint);
            local_58.left = local_58.left + local_60.x;
            local_58.right = local_58.right + local_60.x;
            local_58.top = local_58.top + local_60.y;
            local_58.bottom = local_58.bottom + local_60.y;
            MoveWindow((HWND)param_1,local_58.left,local_58.top,0xed,0x5e,1);
            pSVar1 = operator_new(0x20);
            if (pSVar1 == (ShellBitmap *)0x0) {
              backGround = (ShellBitmap *)0x0;
            }
            else {
              backGround = ShellBitmap::ShellBitmap(pSVar1,"bitmap\\popup5.bmp",0,0);
            }
            pTVar2 = operator_new(0x128);
            if (pTVar2 == (TextLabel *)0x0) {
              messageLabel = (TextLabel *)0x0;
            }
            else {
              messageLabel = TextLabel::TextLabel(pTVar2,param_1,YesNoMessage,9,0xb,0xdb,0x28,0);
            }
            pSVar3 = operator_new(0x110);
            if (pSVar3 == (ShellButton *)0x0) {
              okButton = (ShellButton *)0x0;
            }
            else {
              okButton = ShellButton::ShellButton
                                   (pSVar3,param_1,shell_hInstance,0x836,0x837,0x835,1,0x40,0x75,
                                    0x1e,1,"Yes");
            }
            pSVar3 = operator_new(0x110);
            if (pSVar3 == (ShellButton *)0x0) {
              cancelButton = (ShellButton *)0x0;
            }
            else {
              cancelButton = ShellButton::ShellButton
                                       (pSVar3,param_1,shell_hInstance,0x839,0x83a,0x838,0x76,0x40,
                                        0x75,0x1e,1,"No");
            }
            read_text_label("multi_popup","ok_button",okButton->labelText);
            read_text_label("multi_popup","cancel_button",cancelButton->labelText);
          }
          else {
            if (param_2 != 0x111) {
              return 0;
            }
            if ((param_3 & 0xffff) == 1) {
              iVar7 = 1;
            }
            else {
              if ((param_3 & 0xffff) != 2) {
                return 0;
              }
              iVar7 = 0;
            }
            Shell_EndDialog(param_1,iVar7);
          }
        }
        return 1;
      }
      ReleaseCapture();
      pSVar1 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar1);
      }
      pTVar2 = messageLabel;
      if (messageLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(messageLabel);
        operator_delete(pTVar2);
      }
      pSVar3 = cancelButton;
      if (cancelButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(cancelButton);
        operator_delete(pSVar3);
      }
      pSVar3 = okButton;
      if (okButton == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(okButton);
      operator_delete(pSVar3);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  else {
    if (param_2 == 0x136) goto LAB_00554e5f;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar8 = 1;
        iVar6 = 1;
        iVar7 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        ShellButton::SetButtonMode(okButton,iVar7,iVar6,iVar8);
        iVar8 = 1;
        iVar6 = 1;
        iVar7 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        pSVar3 = cancelButton;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar7 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar7 == 0) {
            iVar7 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10)
            ;
            if (iVar7 == 0) {
              return 0;
            }
            iVar7 = 0;
          }
          else {
            iVar7 = 1;
          }
          Shell_EndDialog(param_1,iVar7);
          return 0;
        }
        iVar7 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        if (iVar7 == 0) {
          iVar7 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar7 == 0) {
            return 0;
          }
          iVar8 = 1;
          iVar6 = 1;
          iVar7 = 2;
          pSVar3 = cancelButton;
        }
        else {
          iVar8 = 1;
          iVar6 = 1;
          iVar7 = 2;
          pSVar3 = okButton;
        }
      }
      ShellButton::SetButtonMode(pSVar3,iVar7,iVar6,iVar8);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_00554e5f:
  pvVar5 = GetStockObject(4);
  return (int)pvVar5;
}
