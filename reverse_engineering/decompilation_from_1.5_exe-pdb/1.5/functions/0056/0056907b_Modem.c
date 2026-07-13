/*
 * Entry: 0056907b
 * Name: Modem
 * Namespace: Global
 * Signature: int Modem(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

int __cdecl Modem(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  HWND hWnd;
  ShellBitmap *pSVar1;
  TextLabel *pTVar2;
  ShellButton *pSVar3;
  HDC pHVar4;
  int iVar5;
  HGDIOBJ pvVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  tagPOINT *lpPoint;
  tagPOINT local_160;
  tagRECT local_158;
  tagPAINTSTRUCT local_148;
  char local_108 [8];
  undefined4 uStack_100;
  char cStack_fc;
  undefined1 local_e0 [216];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_e0;
  ModemDlg = param_1;
  if (0x113 < param_2) {
    if (param_2 != 0x133) {
      if (param_2 == 0x136) goto LAB_005695a6;
      if (param_2 != 0x138) {
        if (param_2 == 0x201) {
          iVar5 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
          if (iVar5 == 0) {
            return 0;
          }
          ShellButton::SetButtonMode(cancelButton,2,1,1);
          return 0;
        }
        if (param_2 != 0x202) {
          return 0;
        }
        iVar5 = ShellButton::CheckRollOver(cancelButton,param_4 & 0xffff,(uint)param_4 >> 0x10);
        if (iVar5 == 0) {
          return 0;
        }
        stopit = 1;
        Shell_EndDialog(param_1,0);
        return 0;
      }
    }
    SetTextColor((HDC)param_3,0xff00);
    SetBkMode((HDC)param_3,2);
    SetBkColor((HDC)param_3,0);
LAB_005695a6:
    pvVar6 = GetStockObject(4);
    return (int)pvVar6;
  }
  if (param_2 != 0x113) {
    if (param_2 == 2) {
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
      if (cancelButton != (ShellButton *)0x0) {
        ShellButton::~ShellButton(cancelButton);
        operator_delete(pSVar3);
      }
    }
    else {
      if (param_2 != 0xf) {
        if (param_2 == 0x14) {
          return 1;
        }
        if (param_2 == 0x110) {
          SetFontRecursive(param_1);
          GetClientRect((HWND)shell_hwnd,&local_158);
          local_160.x = local_158.left + 0xca;
          local_160.y = local_158.top + 0xc1;
          lpPoint = &local_160;
          hWnd = GetWindow((HWND)param_1,4);
          ClientToScreen(hWnd,lpPoint);
          local_158.left = local_158.left + local_160.x;
          local_158.right = local_158.right + local_160.x;
          local_158.top = local_158.top + local_160.y;
          local_158.bottom = local_158.bottom + local_160.y;
          MoveWindow((HWND)param_1,local_158.left,local_158.top,0xed,0x5e,1);
          pSVar1 = operator_new(0x20);
          if (pSVar1 == (ShellBitmap *)0x0) {
            backGround = (ShellBitmap *)0x0;
          }
          else {
            backGround = ShellBitmap::ShellBitmap(pSVar1,"bitmap\\popup3.bmp",0,0);
          }
          if (bAnswer == false) {
            pTVar2 = operator_new(0x128);
            if (pTVar2 == (TextLabel *)0x0) {
              message = (TextLabel *)0x0;
            }
            else {
              message = TextLabel::TextLabel(pTVar2,param_1,"Dialing...",9,0xb,0xdb,0x28,0);
            }
            pcVar9 = "modem_dial";
          }
          else {
            pTVar2 = operator_new(0x128);
            if (pTVar2 == (TextLabel *)0x0) {
              message = (TextLabel *)0x0;
            }
            else {
              message = TextLabel::TextLabel(pTVar2,param_1,"Waiting for call",9,0xb,0xdb,0x28,0);
            }
            pcVar9 = "modem_abort";
          }
          read_text_label("multi_popup",pcVar9,message->textData);
          pSVar3 = operator_new(0x110);
          if (pSVar3 == (ShellButton *)0x0) {
            cancelButton = (ShellButton *)0x0;
          }
          else {
            cancelButton = ShellButton::ShellButton
                                     (pSVar3,param_1,shell_hInstance,0x836,0x837,0x835,0x3b,0x41,
                                      0x75,0x1e,1,"Abort");
          }
          read_text_label("multi_popup","abort_button",cancelButton->labelText);
          iTimerID2 = SetTimer((HWND)param_1,1,100,(TIMERPROC)0x0);
          return 1;
        }
        if (param_2 != 0x111) {
          return 0;
        }
        if ((param_3 & 0xffff) - 1 < 2) {
          stopit = 1;
          Shell_EndDialog(param_1,0);
          return 1;
        }
        return 1;
      }
      pHVar4 = BeginPaint((HWND)param_1,&local_148);
      ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar4);
      TextLabel::DrawLabelText(message,(HDC__ *)pHVar4,(char *)0x0,1);
      ShellButton::UpdateButton(cancelButton,(HDC__ *)pHVar4);
      EndPaint((HWND)param_1,&local_148);
    }
    return 0;
  }
  if (dpCreateDone == 1) {
    KillTimer((HWND)param_1,iTimerID2);
    daoot(Net::dp);
    iVar5 = do_shell();
    if (iVar5 != 0) {
      SaveDefaults();
    }
    Shell_EndDialog(param_1,1);
    return 1;
  }
  if (dpCreateDone != 2) {
    return 1;
  }
  KillTimer((HWND)param_1,iTimerID2);
  Shell_EndDialog(param_1,0);
  switch(modem_dp_result) {
  case 0:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
    goto switchD_005693a0_caseD_0;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 8:
    builtin_strncpy(local_108,"Modem Er",8);
    uStack_100._0_1_ = 'r';
    uStack_100._1_1_ = 'o';
    uStack_100._2_1_ = 'r';
    uStack_100._3_1_ = '\0';
    goto LAB_005693b2;
  case 6:
    pcVar7 = "Modem Busy";
    pcVar9 = local_108;
    goto LAB_005693c4;
  case 7:
    pcVar9 = local_108 + 4;
    pcVar7 = "ady In Use";
    local_108[0] = 'A';
    local_108[1] = 'l';
    local_108[2] = 'r';
    local_108[3] = 'e';
LAB_005693c4:
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    *(undefined4 *)(pcVar9 + 4) = *(undefined4 *)(pcVar7 + 4);
    *(undefined2 *)(pcVar9 + 8) = *(undefined2 *)(pcVar7 + 8);
    pcVar9[10] = pcVar7[10];
LAB_005693b2:
    pcVar9 = local_108;
    break;
  case 9:
    builtin_strncpy(local_108,"Modem bu",8);
    uStack_100._0_3_ = 0x7973;
    pcVar9 = "modem_busy";
    break;
  case 10:
    builtin_strncpy(local_108,"No Answe",8);
    uStack_100._0_1_ = 'r';
    uStack_100._1_1_ = '\0';
    pcVar9 = "no_answer";
    break;
  case 0xb:
    builtin_strncpy(local_108,"No dial ",8);
    uStack_100._0_1_ = 't';
    uStack_100._1_1_ = 'o';
    uStack_100._2_1_ = 'n';
    uStack_100._3_1_ = 'e';
    cStack_fc = '\0';
    pcVar9 = "no_dial";
    break;
  case 0xc:
    builtin_strncpy(local_108,"No Respo",8);
    uStack_100._0_1_ = 'n';
    uStack_100._1_1_ = 's';
    uStack_100._2_1_ = 'e';
    uStack_100._3_1_ = '\0';
    pcVar9 = "no_response";
    break;
  case 0xd:
    pcVar7 = "Network not present";
    pcVar9 = "no_network";
    goto LAB_005694d1;
  case 0xe:
    pcVar9 = "Bad version of transport driver";
    pcVar7 = local_108;
    for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar7 = pcVar7 + 4;
    }
    read_text_label("multi_error","bad_transport_driver",local_108);
    pcVar9 = "Bad version of transport driver";
    goto LAB_005694e4;
  case 0xf:
    pcVar9 = "Network not responding";
    pcVar7 = local_108;
    for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar7 = pcVar7 + 4;
    }
    *(undefined2 *)pcVar7 = *(undefined2 *)pcVar9;
    pcVar7[2] = pcVar9[2];
    pcVar9 = "no_net_response";
    break;
  case 0x10:
    pcVar7 = "Host not responding";
    pcVar9 = "no_host_response";
    goto LAB_005694d1;
  case 0x16:
    pcVar9 = "Bad initialization string";
    pcVar7 = local_108;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar7 = pcVar7 + 4;
    }
    *(undefined2 *)pcVar7 = *(undefined2 *)pcVar9;
    pcVar9 = "bad_init_string";
    break;
  default:
    pcVar7 = "Unknown modem error";
    pcVar9 = "unknown_error";
LAB_005694d1:
    pcVar8 = local_108;
    for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
  }
  read_text_label("multi_error",pcVar9,local_108);
  pcVar9 = local_108;
LAB_005694e4:
  do_error(param_1,pcVar9);
switchD_005693a0_caseD_0:
  return 1;
}
