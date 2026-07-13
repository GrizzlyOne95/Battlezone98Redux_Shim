/*
 * Entry: 00553aaf
 * Name: ErrorDlgProc
 * Namespace: Global
 * Signature: int ErrorDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl ErrorDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND hWnd;
  ShellBitmap *pSVar1;
  TextLabel *pTVar2;
  ShellButton *pSVar3;
  NetState NVar4;
  HDC pHVar5;
  AiMission *pAVar6;
  int iVar7;
  HGDIOBJ pvVar8;
  tagPOINT *lpPoint;
  TIMERPROC lpTimerFunc;
  tagPOINT local_60;
  tagRECT local_58;
  tagPAINTSTRUCT local_48;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 < 0x114) {
    if (param_2 == 0x113) {
      if (iTimerID != 0) {
        KillTimer((HWND)param_1,iTimerID);
        iTimerID = 0;
      }
      pAVar6 = AiMission::GetCurrent();
      if (pAVar6 != (AiMission *)0x0) {
        DoNetEscapeFrame();
      }
      lpTimerFunc = (TIMERPROC)0x0;
      iVar7 = GetRunning();
      iTimerID = SetTimer((HWND)param_1,1,(-(uint)(iVar7 != 5) & 0x28) + 10,lpTimerFunc);
      return 0;
    }
    if (param_2 == 2) {
      if (iTimerID != 0) {
        KillTimer((HWND)param_1,iTimerID);
        iTimerID = 0;
      }
      ReleaseCapture();
      pSVar1 = backGround;
      if (backGround != (ShellBitmap *)0x0) {
        ShellBitmap::~ShellBitmap(backGround);
        operator_delete(pSVar1);
      }
      pTVar2 = message;
      if (message != (TextLabel *)0x0) {
        TextLabel::~TextLabel(message);
        operator_delete(pTVar2);
      }
      pSVar3 = cancelButton;
      if (cancelButton == (ShellButton *)0x0) {
        return 0;
      }
      ShellButton::~ShellButton(cancelButton);
      operator_delete(pSVar3);
      return 0;
    }
    if (param_2 == 0xf) {
      pHVar5 = BeginPaint((HWND)param_1,&local_48);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar5);
      TextLabel::DrawLabelText(message,(HDC__ *)pHVar5,(char *)0x0,1);
      ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar5);
      EndPaint((HWND)param_1,&local_48);
      return 0;
    }
    if (param_2 == 0x14) {
      return 1;
    }
    if (param_2 == 0x110) {
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
        backGround = ShellBitmap::ShellBitmap(pSVar1,"bitmap\\popup4.bmp",0,0);
      }
      if (ErrorDlgMessage == (char *)0x0) {
        pTVar2 = operator_new(0x128);
        if (pTVar2 == (TextLabel *)0x0) {
          message = (TextLabel *)0x0;
        }
        else {
          message = TextLabel::TextLabel(pTVar2,param_1,"Error",9,0xb,0xdb,0x28,0);
        }
        read_text_label("multi_error","error",message->textData);
      }
      else {
        pTVar2 = operator_new(0x128);
        if (pTVar2 == (TextLabel *)0x0) {
          message = (TextLabel *)0x0;
        }
        else {
          message = TextLabel::TextLabel(pTVar2,param_1,ErrorDlgMessage,9,0xb,0xdb,0x28,0);
        }
      }
      ErrorDlgMessage = (char *)0x0;
      pSVar3 = operator_new(0x110);
      if (pSVar3 == (ShellButton *)0x0) {
        cancelButton = (ShellButton *)0x0;
      }
      else {
        cancelButton = ShellButton::ShellButton
                                 (pSVar3,param_1,shell_hInstance,0x836,0x837,0x835,0x3b,0x41,0x75,
                                  0x1e,1,"Ok");
      }
      read_text_label("multi_popup","ok_button",cancelButton->labelText);
      if (theNet == (Net *)0x0) {
        return 1;
      }
      NVar4 = Net::GetState(theNet);
      if (NVar4 != NET_IS_RUNNING) {
        return 1;
      }
      iTimerID = SetTimer((HWND)param_1,1,10,(TIMERPROC)0x0);
      return 1;
    }
    if (param_2 != 0x111) {
      return 0;
    }
    if (1 < (param_3 & 0xffff) - 1) {
      return 0;
    }
LAB_00553b14:
    Shell_EndDialog(param_1,1);
    return 1;
  }
  if (param_2 != 0x133) {
    if (param_2 == 0x136) goto LAB_00553e5d;
    if (param_2 != 0x138) {
      if (param_2 == 0x201) {
        iVar7 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
        if (iVar7 == 0) {
          return 0;
        }
        ShellButton::SetButtonMode(cancelButton,2,1,1);
        return 0;
      }
      if (param_2 != 0x202) {
        return 0;
      }
      iVar7 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
      if (iVar7 == 0) {
        return 0;
      }
      goto LAB_00553b14;
    }
  }
  SetTextColor((HDC)param_3,0xff00);
  SetBkMode((HDC)param_3,2);
  SetBkColor((HDC)param_3,0);
LAB_00553e5d:
  pvVar8 = GetStockObject(4);
  return (int)pvVar8;
}
