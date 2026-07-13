/*
 * Entry: 00564e09
 * Name: RoomDlgProc
 * Namespace: Global
 * Signature: int RoomDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl RoomDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND pHVar1;
  ShellBitmap *pSVar2;
  TextLabel *pTVar3;
  ShellButton *pSVar4;
  HDC pHVar5;
  HGDIOBJ pvVar6;
  Chat *this;
  Chat *this_00;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  CHAR *pCVar12;
  int iVar13;
  tagPOINT *lpPoint;
  BOOL BVar14;
  tagPOINT local_24c;
  tagRECT local_244;
  HWND__ *local_234;
  undefined1 local_230 [13];
  ushort local_223;
  undefined2 local_21f;
  undefined2 local_21b;
  char local_219 [5];
  tagPAINTSTRUCT local_214;
  char local_1d0 [28];
  undefined1 local_1b4 [228];
  CHAR local_d0 [100];
  char local_6c [100];
  uint local_8;
  
  pcVar7 = local_6c;
  local_8 = __security_cookie ^ (uint)pcVar7;
  local_234 = param_1;
  if (param_2 < 0x134) {
    if (param_2 != 0x133) {
      if (param_2 != 2) {
        if (param_2 == 0xf) {
          pHVar5 = BeginPaint((HWND)param_1,&local_214);
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar5);
          TextLabel::DrawLabelText(nameLabel,(HDC__ *)pHVar5,(char *)0x0,1);
          TextLabel::DrawLabelText(passwordLabel,(HDC__ *)pHVar5,(char *)0x0,1);
          ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar5);
          ShellButton::UpdateButton(okButton,(HDC__ *)pHVar5);
          EndPaint((HWND)param_1,&local_214);
          return 0;
        }
        if (param_2 != 0x14) {
          if (param_2 == 0x20) {
            set_cursor(0);
            SetWindowLongA((HWND)param_1,0,1);
          }
          else if (param_2 == 0x110) {
            SetFontRecursive(param_1);
            GetClientRect((HWND)shell_hwnd,&local_244);
            local_24c.x = local_244.left + 0xca;
            local_24c.y = local_244.top + 0xc1;
            lpPoint = &local_24c;
            pHVar1 = GetWindow((HWND)param_1,4);
            ClientToScreen(pHVar1,lpPoint);
            local_244.left = local_244.left + local_24c.x;
            local_244.right = local_244.right + local_24c.x;
            local_244.top = local_244.top + local_24c.y;
            local_244.bottom = local_244.bottom + local_24c.y;
            MoveWindow((HWND)param_1,local_244.left,local_244.top,0xed,0x5e,1);
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
              nameLabel = TextLabel::TextLabel(pTVar3,param_1,"Room Name",4,4,0x71,0x1a,0);
            }
            pTVar3 = operator_new(0x128);
            if (pTVar3 == (TextLabel *)0x0) {
              passwordLabel = (TextLabel *)0x0;
            }
            else {
              passwordLabel = TextLabel::TextLabel(pTVar3,param_1,"Password",4,0x21,0x71,0x1a,0);
            }
            BVar14 = 1;
            iVar11 = 0x10;
            iVar10 = 0x72;
            iVar9 = 9;
            iVar13 = 0x78;
            pHVar1 = GetDlgItem((HWND)param_1,0x7e0);
            MoveWindow(pHVar1,iVar13,iVar9,iVar10,iVar11,BVar14);
            BVar14 = 1;
            iVar11 = 0x10;
            iVar10 = 0x72;
            iVar9 = 0x25;
            iVar13 = 0x78;
            pHVar1 = GetDlgItem((HWND)local_234,0x7f8);
            MoveWindow(pHVar1,iVar13,iVar9,iVar10,iVar11,BVar14);
            SendDlgItemMessageA((HWND)local_234,0x7f8,0xc5,10,0);
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              okButton = (ShellButton *)0x0;
            }
            else {
              okButton = ShellButton::ShellButton
                                   (pSVar4,local_234,shell_hInstance,0x836,0x837,0x835,1,0x40,0x75,
                                    0x1e,1,"Ok");
            }
            pSVar4 = operator_new(0x110);
            if (pSVar4 == (ShellButton *)0x0) {
              cancelButton = (ShellButton *)0x0;
            }
            else {
              cancelButton = ShellButton::ShellButton
                                       (pSVar4,local_234,shell_hInstance,0x839,0x83a,0x838,0x76,0x40
                                        ,0x75,0x1e,1,"Cancel");
            }
            read_text_label("multi_popup","ok_button",okButton->labelText);
            read_text_label("multi_popup","cancel_button",cancelButton->labelText);
            read_text_label("multi_popup","room_name",nameLabel->textData);
            read_text_label("multi_popup","password",passwordLabel->textData);
          }
          else {
            if (param_2 != 0x111) {
              return 0;
            }
            if ((param_3 & 0xffff) == 1) {
              iVar13 = 100;
              local_6c[0] = '\0';
              local_d0[0] = '\0';
              pcVar8 = pcVar7;
              pHVar1 = GetDlgItem((HWND)param_1,0x7e0);
              GetWindowTextA(pHVar1,pcVar8,iVar13);
              iVar13 = 100;
              pCVar12 = local_d0;
              pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
              GetWindowTextA(pHVar1,pCVar12,iVar13);
              if (local_6c[0] == '\0') {
                pcVar7 = "You must enter a room name.";
                pcVar8 = local_1d0;
                for (iVar13 = 7; iVar13 != 0; iVar13 = iVar13 + -1) {
                  *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
                  pcVar7 = pcVar7 + 4;
                  pcVar8 = pcVar8 + 4;
                }
                memset(local_1b4,0,0xe4);
                read_text_label("multi_message","enter_room_name",local_1d0);
                Chat::Append(this,(char *)&chatRoom);
              }
              else {
                Net::Close();
                memset(local_230,0,0x5f);
                local_21b = 0x51;
                local_223 = Net::session_type;
                pcVar8 = local_219;
                local_230[0] = 0x5f;
                strncpy(pcVar8,pcVar7,0x20);
                encrypt_password(local_219,pcVar8,pcVar7);
                local_214.rgbReserved[0x13] = '\0';
                local_214.rgbReserved[0x14] = '\0';
                local_214.rgbReserved[0x15] = '\0';
                local_214.rgbReserved[0x16] = '\0';
                local_21f = 0x1e;
                chat_state = 5;
                dp_result = dpOpen(Net::dp,local_230,dpCreateRoomOpenCallback,&roomList);
              }
              iVar13 = 1;
            }
            else {
              if ((param_3 & 0xffff) != 2) {
                return 0;
              }
              iVar13 = 0;
            }
            Shell_EndDialog(param_1,iVar13);
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
    if (param_2 == 0x136) goto LAB_00565589;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar10 = 1;
        iVar9 = 1;
        iVar13 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        ShellButton::SetButtonMode(okButton,iVar13,iVar9,iVar10);
        iVar10 = 1;
        iVar9 = 1;
        iVar13 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        pSVar4 = cancelButton;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar13 == 0) {
            iVar13 = ShellButton::CheckRollOver
                               (cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
            if (iVar13 == 0) {
              return 0;
            }
            iVar13 = 0;
          }
          else {
            iVar13 = 100;
            local_6c[0] = '\0';
            local_d0[0] = '\0';
            pcVar8 = pcVar7;
            pHVar1 = GetDlgItem((HWND)param_1,0x7e0);
            GetWindowTextA(pHVar1,pcVar8,iVar13);
            iVar13 = 100;
            pCVar12 = local_d0;
            pHVar1 = GetDlgItem((HWND)param_1,0x7f8);
            GetWindowTextA(pHVar1,pCVar12,iVar13);
            if (local_6c[0] == '\0') {
              pcVar7 = "You must enter a room name.";
              pcVar8 = local_1d0;
              for (iVar13 = 7; iVar13 != 0; iVar13 = iVar13 + -1) {
                *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
                pcVar7 = pcVar7 + 4;
                pcVar8 = pcVar8 + 4;
              }
              memset(local_1b4,0,0xe4);
              read_text_label("multi_message","enter_room_name",local_1d0);
              Chat::Append(this_00,(char *)&chatRoom);
            }
            else {
              Net::Close();
              memset(local_230,0,0x5f);
              local_21b = 0x51;
              local_223 = Net::session_type;
              pcVar8 = local_219;
              local_230[0] = 0x5f;
              strncpy(pcVar8,pcVar7,0x20);
              encrypt_password(local_219,pcVar8,pcVar7);
              local_214.rgbReserved[0x13] = '\0';
              local_214.rgbReserved[0x14] = '\0';
              local_214.rgbReserved[0x15] = '\0';
              local_214.rgbReserved[0x16] = '\0';
              local_21f = 0x1e;
              chat_state = 5;
              dp_result = dpOpen(Net::dp,local_230,dpCreateRoomOpenCallback,&roomList);
            }
            iVar13 = 1;
          }
          Shell_EndDialog(param_1,iVar13);
          return 0;
        }
        iVar13 = ShellButton::CheckRollOver(okButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
        if (iVar13 == 0) {
          iVar13 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar13 == 0) {
            return 0;
          }
          iVar10 = 1;
          iVar9 = 1;
          iVar13 = 2;
          pSVar4 = cancelButton;
        }
        else {
          iVar10 = 1;
          iVar9 = 1;
          iVar13 = 2;
          pSVar4 = okButton;
        }
      }
      ShellButton::SetButtonMode(pSVar4,iVar13,iVar9,iVar10);
      return 0;
    }
    SetTextColor((HDC)param_3,0xff00);
  }
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_00565589:
  pvVar6 = GetStockObject(4);
  return (int)pvVar6;
}
