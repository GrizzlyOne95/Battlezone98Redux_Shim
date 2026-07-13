/*
 * Entry: 0057376d
 * Name: JoystickDlgProc
 * Namespace: Global
 * Signature: int JoystickDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl JoystickDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char cVar1;
  ShellBitmap *pSVar2;
  ShellButton *pSVar3;
  ShellScrollBar *pSVar4;
  TextLabel *pTVar5;
  _JoystickListItem *p_Var6;
  HWND pHVar7;
  HWND pHVar8;
  HDC hdc;
  LRESULT LVar9;
  HGDIOBJ pvVar10;
  char *pcVar11;
  int extraout_EDX;
  ShellButton *extraout_EDX_00;
  ShellButton *extraout_EDX_01;
  _JoystickListItem *p_Var12;
  int iVar13;
  int iVar14;
  int iVar15;
  int nHeight;
  BOOL bRepaint;
  LOGBRUSH local_270;
  RECT local_264;
  int local_254;
  HWND__ *local_250;
  HBRUSH local_24c;
  undefined1 local_248 [64];
  char local_208 [24];
  undefined1 local_1f0 [232];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1f0;
  local_250 = param_1;
  if (param_2 < 0x112) {
    if (param_2 == 0x111) {
      if ((short)param_3 != 0x429) {
        return 0;
      }
      if ((short)(param_3 >> 0x10) != 1) {
        return 1;
      }
      LVar9 = SendDlgItemMessageA((HWND)param_1,0x429,0x188,0,0);
      (UserProfilePtr->config).jIndex = LVar9;
      p_Var6 = JoystickList + LVar9;
      iVar13 = (int)&currentJoystickMap - (int)p_Var6;
      do {
        cVar1 = p_Var6->fileName[0];
        *(char *)((int)p_Var6 + iVar13) = cVar1;
        p_Var6 = (_JoystickListItem *)(p_Var6->fileName + 1);
      } while (cVar1 != '\0');
      return 1;
    }
    if (param_2 == 2) {
      SnapShotBackground();
      CleanCurrentBackground();
      pSVar2 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar2);
        backGround = (ShellBitmap *)0x0;
      }
      pSVar3 = ulButton;
      if (ulButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(ulButton);
        operator_delete(pSVar3);
        ulButton = (ShellButton *)0x0;
      }
      pSVar4 = joyScroll;
      if (joyScroll != (ShellScrollBar *)0x0) {
        ShellScrollBar::~ShellScrollBar(joyScroll);
        operator_delete(pSVar4);
        joyScroll = (ShellScrollBar *)0x0;
      }
      pTVar5 = joyLabel;
      if (joyLabel != (TextLabel *)0x0) {
        TextLabel::~TextLabel(joyLabel);
        operator_delete(pTVar5);
        joyLabel = (TextLabel *)0x0;
      }
      pTVar5 = message;
      if (message == (TextLabel *)0x0) {
        return 0;
      }
      TextLabel::~TextLabel(message);
      operator_delete(pTVar5);
      message = (TextLabel *)0x0;
      return 0;
    }
    if (param_2 == 0xf) {
      hdc = BeginPaint((HWND)param_1,(LPPAINTSTRUCT)local_248);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)hdc);
      PatBlt(hdc,0x82,0x157,0x17a,0x1e,0x42);
      ShellButton::UpdateButton(ulButton,(HDC__ *)hdc);
      ShellScrollBar::UpdateScroll(joyScroll,(HDC__ *)hdc);
      TextLabel::DrawLabelText(message,(HDC__ *)hdc,(char *)0x0,0);
      TextLabel::DrawLabelText(joyLabel,(HDC__ *)hdc,(char *)0x0,0);
      EndPaint((HWND)param_1,(PAINTSTRUCT *)local_248);
    }
    else if (param_2 != 0x14) {
      if (param_2 != 0x20) {
        if (param_2 == 0x2b) {
          if (*(int *)(param_4 + 8) == -1) {
            return 0;
          }
          if (1 < *(int *)(param_4 + 0xc) - 1U) {
            return 1;
          }
          pHVar7 = *(HWND *)(param_4 + 0x14);
          pHVar8 = GetDlgItem((HWND)param_1,0x429);
          if (pHVar7 != pHVar8) {
            return 1;
          }
          SendMessageA(pHVar7,0x189,*(WPARAM *)(param_4 + 8),(LPARAM)local_108);
          GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)(local_248 + 8));
          local_264.top = *(int *)(param_4 + 0x20);
          local_264.bottom = *(int *)(param_4 + 0x28);
          iVar13 = (local_264.top - local_248._8_4_) + local_264.bottom;
          local_264.left = *(LONG *)(param_4 + 0x1c);
          local_264.right = *(LONG *)(param_4 + 0x24);
          if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
            local_270.lbColor = 0;
          }
          else {
            DrawFocusRect(*(HDC *)(param_4 + 0x18),&local_264);
            local_270.lbColor = 0x6400;
          }
          local_270.lbStyle = 0;
          local_270.lbHatch = 0;
          local_24c = CreateBrushIndirect(&local_270);
          FillRect(*(HDC *)(param_4 + 0x18),&local_264,local_24c);
          if (local_24c != (HBRUSH)0x0) {
            DeleteObject(local_24c);
          }
          pcVar11 = local_108;
          do {
            cVar1 = *pcVar11;
            pcVar11 = pcVar11 + 1;
          } while (cVar1 != '\0');
          TextOutA(*(HDC *)(param_4 + 0x18),5,iVar13 / 2,local_108,
                   (int)pcVar11 - (int)(local_108 + 1));
          return 1;
        }
        if (param_2 == 0x2c) {
          *(undefined4 *)(param_4 + 0x10) = 0x10;
          return 1;
        }
        if (param_2 != 0x110) {
          return 0;
        }
        init_screen_pos(param_1);
        init_bitmap_dc(param_1);
        pSVar2 = operator_new(0x20);
        if (pSVar2 == (ShellBitmap *)0x0) {
          backGround = (ShellBitmap *)0x0;
        }
        else {
          backGround = ShellBitmap::ShellBitmap(pSVar2,"bitmap\\poptions.bmp",0,0);
        }
        SetCurrentBackground(param_1,backGround);
        pSVar3 = operator_new(0x110);
        if (pSVar3 == (ShellButton *)0x0) {
          ulButton = (ShellButton *)0x0;
        }
        else {
          ulButton = ShellButton::ShellButton
                               (pSVar3,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                                "BACK");
        }
        ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
        pSVar4 = operator_new(0x58);
        if (pSVar4 == (ShellScrollBar *)0x0) {
          joyScroll = (ShellScrollBar *)0x0;
        }
        else {
          joyScroll = ShellScrollBar::ShellScrollBar
                                (pSVar4,param_1,shell_hInstance,0x10e,0x120,299,0xd6,0x26,0x1b,0);
        }
        joyScroll->nCurrentPos = (UserProfilePtr->config).jSensitivity;
        pTVar5 = operator_new(0x128);
        if (pTVar5 == (TextLabel *)0x0) {
          joyLabel = (TextLabel *)0x0;
        }
        else {
          joyLabel = TextLabel::TextLabel
                               (pTVar5,param_1,"JOYSTICK SENSITIVITY",0x87,0x136,0x96,0x13,0x126);
        }
        pTVar5 = operator_new(0x128);
        if (pTVar5 == (TextLabel *)0x0) {
          message = (TextLabel *)0x0;
        }
        else {
          message = TextLabel::TextLabel
                              (pTVar5,param_1,"Select Joystick Map file",0xc3,0x37,0xfa,0x1e,0);
        }
        p_Var12 = JoystickList;
        p_Var6 = JoystickList + (UserProfilePtr->config).jIndex;
        pcVar11 = &currentJoystickMap;
        do {
          cVar1 = p_Var6->fileName[0];
          p_Var6 = (_JoystickListItem *)(p_Var6->fileName + 1);
          *pcVar11 = cVar1;
          pcVar11 = pcVar11 + 1;
        } while (cVar1 != '\0');
        do {
          read_text_label("joystick",p_Var12->fileName,p_Var12->displayName);
          p_Var12 = p_Var12 + 1;
        } while ((int)p_Var12 < 0x6408f0);
        pHVar7 = GetDlgItem((HWND)local_250,0x429);
        SetNetworkFont((HWND__ *)pHVar7);
        local_24c = (HBRUSH)0x0;
        local_254 = 0x63fa30;
        do {
          sprintf(local_208,"%s",local_254);
          SendDlgItemMessageA((HWND)local_250,0x429,0x181,(WPARAM)local_24c,(LPARAM)local_208);
          local_254 = local_254 + 0x140;
          local_24c = (HBRUSH)((int)local_24c + 1);
        } while (local_254 < 0x640930);
        SendDlgItemMessageA((HWND)local_250,0x429,0x186,(UserProfilePtr->config).jIndex,0);
        bRepaint = 1;
        nHeight = 200;
        iVar15 = 0x118;
        iVar14 = 100;
        iVar13 = 0xb4;
        pHVar7 = GetDlgItem((HWND)local_250,0x429);
        MoveWindow(pHVar7,iVar13,iVar14,iVar15,nHeight,bRepaint);
        read_text_label("missions","back",ulButton->labelText);
        read_text_label("joystick","select",message->textData);
        read_text_label("joystick","sensitivity",joyLabel->textData);
        SetFocus((HWND)local_250);
        return 0;
      }
      set_cursor(0);
      SetWindowLongA((HWND)param_1,0,1);
    }
    return 1;
  }
  if (param_2 != 0x134) {
    if (param_2 == 0x136) goto LAB_00573df4;
    if (param_2 != 0x138) {
      if (param_2 == 0x200) {
        iVar15 = 0;
        iVar14 = 1;
        iVar13 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
        pSVar3 = extraout_EDX_01;
      }
      else {
        if (param_2 != 0x201) {
          if (param_2 != 0x202) {
            return 0;
          }
          iVar13 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffffU,(uint)param_4 >> 0x10);
          if (iVar13 != 0) {
            SaveUserProfile();
            Shell_EndDialog(param_1,1);
            return 0;
          }
          iVar13 = ShellScrollBar::CheckButtons(joyScroll,param_4 & 0xffffU,extraout_EDX);
          if (iVar13 < 0) {
            return 0;
          }
          (UserProfilePtr->config).jSensitivity = joyScroll->nCurrentPos;
          return 0;
        }
        iVar13 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
        if (iVar13 == 0) {
          return 0;
        }
        iVar15 = 0;
        iVar14 = 1;
        iVar13 = 2;
        pSVar3 = extraout_EDX_00;
      }
      ShellButton::SetButtonMode(pSVar3,iVar13,iVar14,iVar15);
      return 0;
    }
  }
  SetTextColor((HDC)param_3,0x200ff00);
  SetBkMode((HDC)param_3,1);
LAB_00573df4:
  pvVar10 = GetStockObject(4);
  return (int)pvVar10;
}
