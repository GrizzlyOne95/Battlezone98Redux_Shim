/*
 * Entry: 005534a4
 * Name: PhoneDlgProc
 * Namespace: Global
 * Signature: int PhoneDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PhoneDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND pHVar1;
  ShellBitmap *pSVar2;
  TextLabel *pTVar3;
  ShellButton *pSVar4;
  HWND pHVar5;
  HDC pHVar6;
  HGDIOBJ pvVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  tagPOINT *lpPoint;
  BOOL BVar13;
  tagPOINT local_128;
  tagRECT local_120;
  tagPAINTSTRUCT local_110;
  char local_d0 [100];
  char local_6c [100];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_6c;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar6 = BeginPaint((HWND)param_1,&local_110);
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar6);
          TextLabel::DrawLabelText(nameLabel,(HDC__ *)pHVar6,(char *)0x0,1);
          TextLabel::DrawLabelText(numberLabel,(HDC__ *)pHVar6,(char *)0x0,1);
          ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar6);
          ShellButton::UpdateButton(okButton,(HDC__ *)pHVar6);
          EndPaint((HWND)param_1,&local_110);
          return 0;
        }
        if (param_2 != 0x14) {
          if (param_2 == 0x20) {
            set_cursor(0);
            SetWindowLongA((HWND)param_1,0,1);
          }
          else if (param_2 == 0x110) {
            SetFontRecursive(param_1);
            GetClientRect((HWND)shell_hwnd,&local_120);
            local_128.x = local_120.left + 0xca;
            local_128.y = local_120.top + 0xc1;
            lpPoint = &local_128;
            pHVar1 = GetWindow((HWND)param_1,4);
            ClientToScreen(pHVar1,lpPoint);
            local_120.left = local_120.left + local_128.x;
            local_120.right = local_120.right + local_128.x;
            local_120.top = local_120.top + local_128.y;
            local_120.bottom = local_120.bottom + local_128.y;
            MoveWindow((HWND)param_1,local_120.left,local_120.top,0xed,0x5e,1);
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
              nameLabel = TextLabel::TextLabel(pTVar3,param_1,"Player Name",4,4,0x71,0x1a,0);
            }
            pTVar3 = operator_new(0x128);
            if (pTVar3 == (TextLabel *)0x0) {
              numberLabel = (TextLabel *)0x0;
            }
            else {
              numberLabel = TextLabel::TextLabel(pTVar3,param_1,"Phone Number",4,0x21,0x71,0x1a,0);
            }
            BVar13 = 1;
            iVar10 = 0x10;
            iVar9 = 0x72;
            iVar8 = 9;
            iVar12 = 0x78;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f3);
            MoveWindow(pHVar1,iVar12,iVar8,iVar9,iVar10,BVar13);
            BVar13 = 1;
            iVar10 = 0x10;
            iVar9 = 0x72;
            iVar8 = 0x25;
            iVar12 = 0x78;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f4);
            MoveWindow(pHVar1,iVar12,iVar8,iVar9,iVar10,BVar13);
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
            pHVar1 = GetDlgItem((HWND)param_1,0x7f4);
            pHVar5 = GetDlgItem((HWND)param_1,0x7f3);
            PhoneNumberList::Setup(&phoneNumberList,(HWND__ *)pHVar5,(HWND__ *)pHVar1);
            read_text_label("multi_popup","ok_button",okButton->labelText);
            read_text_label("multi_popup","cancel_button",cancelButton->labelText);
            read_text_label("multi_popup","player_name",nameLabel->textData);
            read_text_label("multi_popup","phone_number",numberLabel->textData);
          }
          else {
            if (param_2 != 0x111) {
              return 0;
            }
            if ((param_3 & 0xffff) == 1) {
              iVar12 = 100;
              pcVar11 = local_6c;
              pHVar1 = GetDlgItem((HWND)param_1,0x7f3);
              GetWindowTextA(pHVar1,pcVar11,iVar12);
              iVar12 = 100;
              pcVar11 = local_d0;
              pHVar1 = GetDlgItem((HWND)param_1,0x7f4);
              GetWindowTextA(pHVar1,pcVar11,iVar12);
              if ((local_6c[0] != '\0') && (local_d0[0] != '\0')) {
                PhoneNumberList::Change(&phoneNumberList,local_6c,local_d0);
                PhoneNumberList::Save(&phoneNumberList,"netpho.txt");
              }
              iVar12 = 1;
            }
            else {
              if ((param_3 & 0xffff) != 2) {
                return 0;
              }
              iVar12 = 0;
            }
            Shell_EndDialog(param_1,iVar12);
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
      pTVar3 = nameLabel;
      if (nameLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(nameLabel);
        operator_delete(pTVar3);
      }
      pTVar3 = numberLabel;
      if (numberLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(numberLabel);
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
    if (param_2 == 0x136) goto LAB_00553a72;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar9 = 1;
        iVar8 = 1;
        iVar12 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        ShellButton::SetButtonMode(okButton,iVar12,iVar8,iVar9);
        iVar9 = 1;
        iVar8 = 1;
        iVar12 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        pSVar4 = cancelButton;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar12 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar12 == 0) {
            iVar12 = ShellButton::CheckRollOver
                               (cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
            if (iVar12 == 0) {
              return 0;
            }
            iVar12 = 0;
          }
          else {
            iVar12 = 100;
            pcVar11 = local_6c;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f3);
            GetWindowTextA(pHVar1,pcVar11,iVar12);
            iVar12 = 100;
            pcVar11 = local_d0;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f4);
            GetWindowTextA(pHVar1,pcVar11,iVar12);
            if ((local_6c[0] != '\0') && (local_d0[0] != '\0')) {
              PhoneNumberList::Change(&phoneNumberList,local_6c,local_d0);
              PhoneNumberList::Save(&phoneNumberList,"netpho.txt");
            }
            iVar12 = 1;
          }
          Shell_EndDialog(param_1,iVar12);
          return 0;
        }
        iVar12 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        if (iVar12 == 0) {
          iVar12 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar12 == 0) {
            return 0;
          }
          iVar9 = 1;
          iVar8 = 1;
          iVar12 = 2;
          pSVar4 = cancelButton;
        }
        else {
          iVar9 = 1;
          iVar8 = 1;
          iVar12 = 2;
          pSVar4 = okButton;
        }
      }
      ShellButton::SetButtonMode(pSVar4,iVar12,iVar8,iVar9);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_00553a72:
  pvVar7 = GetStockObject(4);
  return (int)pvVar7;
}
