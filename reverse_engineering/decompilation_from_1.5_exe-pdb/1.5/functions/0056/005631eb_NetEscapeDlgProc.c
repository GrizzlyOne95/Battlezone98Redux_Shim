/*
 * Entry: 005631eb
 * Name: NetEscapeDlgProc
 * Namespace: Global
 * Signature: int NetEscapeDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl NetEscapeDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char cVar1;
  Player *pPVar2;
  bool bVar3;
  HDC pHVar4;
  LRESULT LVar5;
  Player *pPVar6;
  char *pcVar7;
  dp_s *pdVar8;
  ShellBitmap *pSVar9;
  ShellButton *pSVar10;
  TextLabel *pTVar11;
  TabTextWindow *pTVar12;
  uint uVar13;
  HWND pHVar14;
  HWND pHVar15;
  SimpleVehicleList *pSVar16;
  AiMission *pAVar17;
  DWORD DVar18;
  HGDIOBJ pvVar19;
  PlayerList *unaff_ESI;
  Chat *unaff_EDI;
  dp_stat_t *pdVar20;
  char *pcVar21;
  uint uVar22;
  int iVar23;
  dp_s *pdVar24;
  int iVar25;
  int iVar26;
  Chat_conflict *pCVar27;
  ushort uVar28;
  int iVar29;
  code *pcVar30;
  WPARAM wParam;
  COLORREF CVar31;
  SyncGamePlayerList *pSVar32;
  BOOL BVar33;
  HWND__ *pHVar34;
  TIMERPROC lpTimerFunc;
  RECT local_290;
  LOGBRUSH local_280;
  RECT local_274;
  HDC local_264;
  Player *local_260;
  HBRUSH local_25c;
  HWND__ *local_258;
  undefined1 local_254 [64];
  char local_214 [4];
  undefined1 local_210 [21];
  undefined1 local_1fb;
  undefined1 local_1fa [11];
  undefined1 local_1ef [219];
  char local_114 [22];
  undefined1 local_fe [2];
  undefined1 local_fc [232];
  char local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_210;
  local_258 = param_1;
  if (0x113 < param_2) {
    if ((param_2 == 0x133) || (param_2 == 0x134)) {
      SetTextColor((HDC)param_3,0xff00);
      SetBkMode((HDC)param_3,1);
    }
    else if (param_2 != 0x136) {
      if (param_2 != 0x138) {
        if (param_2 == 0x200) {
          if (lrButton == (ShellButton *)0x0) {
            return 0;
          }
          iVar26 = 0;
          iVar25 = 1;
          uVar22 = (uint)param_4 >> 0x10;
          uVar13 = param_4 & 0xffff;
          iVar23 = ShellButton::CheckRollOver(lrButton,uVar13,uVar22);
          ShellButton::SetButtonMode(lrButton,iVar23,iVar25,iVar26);
          if (ulButton != (ShellButton *)0x0) {
            iVar26 = 0;
            iVar25 = 1;
            iVar23 = ShellButton::CheckRollOver(ulButton,uVar13,uVar22);
            ShellButton::SetButtonMode(ulButton,iVar23,iVar25,iVar26);
          }
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(llButton,uVar13,uVar22);
          ShellButton::SetButtonMode(llButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(whisperButton,uVar13,uVar22);
          ShellButton::SetButtonMode(whisperButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(muteButton,uVar13,uVar22);
          ShellButton::SetButtonMode(muteButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(kickButton,uVar13,uVar22);
          ShellButton::SetButtonMode(kickButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(chatUpButton,uVar13,uVar22);
          ShellButton::SetButtonMode(chatUpButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(chatDownButton,uVar13,uVar22);
          ShellButton::SetButtonMode(chatDownButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(statUpButton,uVar13,uVar22);
          ShellButton::SetButtonMode(statUpButton,iVar23,iVar25,iVar26);
          iVar26 = 0;
          iVar25 = 1;
          iVar23 = ShellButton::CheckRollOver(statDownButton,uVar13,uVar22);
          pSVar10 = statDownButton;
        }
        else {
          if (param_2 != 0x201) {
            if (param_2 != 0x202) {
              return 0;
            }
            if ((ulButton != (ShellButton *)0x0) &&
               (iVar23 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10)
               , iVar23 != 0)) {
              if (iTimerID != 0) {
                KillTimer((HWND)local_258,iTimerID);
                iTimerID = 0;
              }
              nShellMode = 0;
              EnableWindow((HWND)local_258,0);
              Shell_EndDialog(local_258,1);
              return 0;
            }
            uVar22 = (uint)param_4 >> 0x10;
            uVar13 = param_4 & 0xffff;
            iVar23 = ShellButton::CheckRollOver(lrButton,uVar13,uVar22);
            if (iVar23 != 0) {
              Scores_ReportScores();
              if (iTimerID != 0) {
                KillTimer((HWND)local_258,iTimerID);
                iTimerID = 0;
              }
              EnableWindow((HWND)local_258,0);
              SetRunning(2);
              nNetMode = 1;
              nShellMode = 0;
              Shell_EndDialog(local_258,1);
              return 0;
            }
            iVar23 = ShellButton::CheckRollOver(llButton,uVar13,uVar22);
            if (iVar23 != 0) {
              ShowWindow((HWND)local_258,0);
              EnableWindow((HWND)local_258,0);
              BEnabled = 0;
              do_options(1);
              SetCurrentBackground(local_258,backGround);
              EnableWindow((HWND)local_258,1);
              ShowWindow((HWND)local_258,5);
              BEnabled = 1;
              return 0;
            }
            iVar23 = ShellButton::CheckRollOver(whisperButton,uVar13,uVar22);
            if (iVar23 != 0) {
              ShellButton::SetButtonMode(whisperButton,1,0,0);
              uVar28 = Net::myPlayerID;
              pHVar14 = GetDlgItem((HWND)local_258,0x825);
              PlayerList::SendMessageToSelectedPlayers
                        ((PlayerList *)&playersInSyncGame,(HWND__ *)pHVar14,uVar28);
              return 0;
            }
            iVar23 = ShellButton::CheckRollOver(muteButton,uVar13,uVar22);
            if (iVar23 != 0) {
              ShellButton::SetButtonMode(muteButton,1,0,0);
              PlayerList::ToggleMute((PlayerList *)&playersInSyncGame);
              return 0;
            }
            iVar23 = ShellButton::CheckRollOver(kickButton,uVar13,uVar22);
            if (iVar23 != 0) {
              ShellButton::SetButtonMode(kickButton,1,0,0);
              PlayerList::KickSelectedPlayers((PlayerList *)&playersInSyncGame);
              return 0;
            }
            iVar23 = ShellButton::CheckRollOver(chatUpButton,uVar13,uVar22);
            if (iVar23 == 0) {
              iVar23 = ShellButton::CheckRollOver(chatDownButton,uVar13,uVar22);
              if (iVar23 == 0) {
                iVar23 = ShellButton::CheckRollOver(statUpButton,uVar13,uVar22);
                if (iVar23 == 0) {
                  iVar23 = ShellButton::CheckRollOver(statDownButton,uVar13,uVar22);
                  if (iVar23 == 0) {
                    return 0;
                  }
                  iVar26 = 0;
                  iVar25 = 0;
                  iVar23 = 1;
                  pSVar10 = statDownButton;
                }
                else {
                  iVar26 = 0;
                  iVar25 = 0;
                  iVar23 = 1;
                  pSVar10 = statUpButton;
                }
                goto LAB_00564d77;
              }
              ShellButton::SetButtonMode(chatDownButton,1,0,0);
              wParam = 1;
            }
            else {
              ShellButton::SetButtonMode(chatUpButton,1,0,0);
              wParam = 0;
            }
            SendDlgItemMessageA((HWND)local_258,0x826,0xb5,wParam,0);
            return 0;
          }
          if ((ulButton == (ShellButton *)0x0) ||
             (iVar23 = ShellButton::CheckRollOver(ulButton,param_4 & 0xffff,(uint)param_4 >> 0x10),
             iVar23 == 0)) {
            uVar22 = (uint)param_4 >> 0x10;
            uVar13 = param_4 & 0xffff;
            iVar23 = ShellButton::CheckRollOver(lrButton,uVar13,uVar22);
            if (iVar23 == 0) {
              iVar23 = ShellButton::CheckRollOver(llButton,uVar13,uVar22);
              if (iVar23 == 0) {
                iVar23 = ShellButton::CheckRollOver(whisperButton,uVar13,uVar22);
                if (iVar23 == 0) {
                  iVar23 = ShellButton::CheckRollOver(muteButton,uVar13,uVar22);
                  if (iVar23 == 0) {
                    iVar23 = ShellButton::CheckRollOver(kickButton,uVar13,uVar22);
                    if (iVar23 == 0) {
                      iVar23 = ShellButton::CheckRollOver(chatUpButton,uVar13,uVar22);
                      if (iVar23 == 0) {
                        iVar23 = ShellButton::CheckRollOver(chatDownButton,uVar13,uVar22);
                        if (iVar23 == 0) {
                          iVar23 = ShellButton::CheckRollOver(statUpButton,uVar13,uVar22);
                          if (iVar23 != 0) {
                            ShellButton::SetButtonMode(statUpButton,2,1,0);
                            PlayerList::SelectionUp((PlayerList *)&playersInSyncGame);
                            return 0;
                          }
                          iVar23 = ShellButton::CheckRollOver(statDownButton,uVar13,uVar22);
                          if (iVar23 == 0) {
                            return 0;
                          }
                          ShellButton::SetButtonMode(statDownButton,2,1,0);
                          PlayerList::SelectionDown((PlayerList *)&playersInSyncGame);
                          return 0;
                        }
                        iVar26 = 0;
                        iVar25 = 1;
                        iVar23 = 2;
                        pSVar10 = chatDownButton;
                      }
                      else {
                        iVar26 = 0;
                        iVar25 = 1;
                        iVar23 = 2;
                        pSVar10 = chatUpButton;
                      }
                    }
                    else {
                      iVar26 = 0;
                      iVar25 = 1;
                      iVar23 = 2;
                      pSVar10 = kickButton;
                    }
                  }
                  else {
                    iVar26 = 0;
                    iVar25 = 1;
                    iVar23 = 2;
                    pSVar10 = muteButton;
                  }
                }
                else {
                  iVar26 = 0;
                  iVar25 = 1;
                  iVar23 = 2;
                  pSVar10 = whisperButton;
                }
              }
              else {
                iVar26 = 0;
                iVar25 = 1;
                iVar23 = 2;
                pSVar10 = llButton;
              }
            }
            else {
              iVar26 = 0;
              iVar25 = 1;
              iVar23 = 2;
              pSVar10 = lrButton;
            }
          }
          else {
            iVar26 = 0;
            iVar25 = 1;
            iVar23 = 2;
            pSVar10 = ulButton;
          }
        }
LAB_00564d77:
        ShellButton::SetButtonMode(pSVar10,iVar23,iVar25,iVar26);
        return 0;
      }
      SetTextColor((HDC)param_3,0x200ff00);
      SetBkMode((HDC)param_3,2);
      SetBkColor((HDC)param_3,0);
    }
    pvVar19 = GetStockObject(4);
    return (int)pvVar19;
  }
  if (param_2 != 0x113) {
    if (param_2 < 0x2c) {
      if (param_2 == 0x2b) {
        if (*(WPARAM *)(param_4 + 8) == 0xffffffff) {
          return 0;
        }
        if (1 < *(int *)(param_4 + 0xc) - 1U) {
          return 1;
        }
        LVar5 = SendMessageA(*(HWND *)(param_4 + 0x14),0x199,*(WPARAM *)(param_4 + 8),0);
        local_260 = PlayerList::FindPlayer((PlayerList *)&playersInSyncGame,(ushort)LVar5);
        if (local_260 == (Player *)0x0) {
          return 1;
        }
        GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)(local_254 + 8));
        local_274.bottom = *(int *)(param_4 + 0x28);
        local_258 = (HWND__ *)
                    (((*(int *)(param_4 + 0x20) - local_254._8_4_) + local_274.bottom) / 2);
        local_274.left = *(LONG *)(param_4 + 0x1c);
        local_274.top = *(LONG *)(param_4 + 0x20);
        local_274.right = *(LONG *)(param_4 + 0x24);
        if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
          local_280.lbColor = 0;
        }
        else {
          DrawFocusRect(*(HDC *)(param_4 + 0x18),&local_274);
          local_280.lbColor = 0x6400;
        }
        local_280.lbStyle = 0;
        local_280.lbHatch = 0;
        local_25c = CreateBrushIndirect(&local_280);
        FillRect(*(HDC *)(param_4 + 0x18),&local_274,local_25c);
        if (local_25c != (HBRUSH)0x0) {
          DeleteObject(local_25c);
        }
        bVar3 = PlayerList::IsHost((PlayerList *)&playersInSyncGame,local_260->id);
        if (bVar3) {
          local_264 = CreateCompatibleDC(*(HDC *)(param_4 + 0x18));
          local_25c = SelectObject(local_264,hbmpHost);
          BitBlt(*(HDC *)(param_4 + 0x18),*(int *)(param_4 + 0x1c),*(int *)(param_4 + 0x20) + 3,
                 *(int *)(param_4 + 0x24) - *(int *)(param_4 + 0x1c),
                 (*(int *)(param_4 + 0x28) - *(int *)(param_4 + 0x20)) + -3,local_264,0,0,0xcc0020);
          SelectObject(local_264,local_25c);
          DeleteDC(local_264);
        }
        bVar3 = PlayerList::IsMuted((PlayerList *)&playersInSyncGame,local_260->id);
        if (bVar3) {
          pHVar4 = CreateCompatibleDC(*(HDC *)(param_4 + 0x18));
          local_25c = SelectObject(pHVar4,hbmpMute);
          BitBlt(*(HDC *)(param_4 + 0x18),*(int *)(param_4 + 0x1c),*(int *)(param_4 + 0x20) + 3,
                 *(int *)(param_4 + 0x24) - *(int *)(param_4 + 0x1c),
                 (*(int *)(param_4 + 0x28) - *(int *)(param_4 + 0x20)) + -3,pHVar4,0,0,0xcc0020);
          SelectObject(pHVar4,local_25c);
          DeleteDC(pHVar4);
        }
        local_25c = (HBRUSH)GetTextColor(*(HDC *)(param_4 + 0x18));
        SetTextColor(*(HDC *)(param_4 + 0x18),0xff00);
        pPVar2 = local_260;
        local_290.top = *(LONG *)(param_4 + 0x20);
        local_290.bottom = *(LONG *)(param_4 + 0x28);
        local_290.left = 0xb;
        local_290.right = 0x74;
        pPVar6 = local_260;
        do {
          pcVar7 = pPVar6->caName;
          pPVar6 = (Player *)(pPVar6->caName + 1);
        } while (*pcVar7 != '\0');
        ExtTextOutA(*(HDC *)(param_4 + 0x18),0xb,(int)local_258,4,&local_290,local_260->caName,
                    (int)pPVar6 - (int)(local_260->caName + 1),(INT *)0x0);
        SetTextColor(*(HDC *)(param_4 + 0x18),(COLORREF)local_25c);
        sprintf(local_14,"%d",(int)pPVar2->blob[0]);
        pcVar7 = local_14;
        do {
          cVar1 = *pcVar7;
          pcVar7 = pcVar7 + 1;
        } while (cVar1 != '\0');
        TextOutA(*(HDC *)(param_4 + 0x18),0x7e,(int)local_258,local_14,
                 (int)pcVar7 - (int)(local_14 + 1));
        local_264 = (HDC)SimpleVehicleList::FindVehicle(simpleVehicleList,pPVar2->blob + 1);
        if (local_264 == (HDC)0x0) {
          TextOutA(*(HDC *)(param_4 + 0x18),0x91,(int)local_258," ",1);
        }
        else {
          local_290.top = *(LONG *)(param_4 + 0x20);
          local_290.bottom = *(LONG *)(param_4 + 0x28);
          local_260 = (Player *)((int)local_264 + 1);
          local_290.left = 0x91;
          local_290.right = 0xe3;
          pcVar7 = (char *)local_264;
          do {
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          ExtTextOutA(*(HDC *)(param_4 + 0x18),0x91,(int)local_258,4,&local_290,(LPCSTR)local_264,
                      (int)pcVar7 - (int)local_260,(INT *)0x0);
        }
        if (pPVar2->id != Net::myPlayerID) {
          local_260 = (Player *)GetTextAlign(*(HDC *)(param_4 + 0x18));
          SetTextAlign(*(HDC *)(param_4 + 0x18),2);
          if (pPVar2->avg_ms < 0x3e9) {
            if (pPVar2->avg_ms < 0x1f5) {
              CVar31 = 0xff00;
            }
            else {
              CVar31 = 0xffff;
            }
          }
          else {
            CVar31 = 0xff;
          }
          SetTextColor(*(HDC *)(param_4 + 0x18),CVar31);
          sprintf(local_14,"%d",pPVar2->avg_ms);
          pcVar7 = local_14;
          do {
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          TextOutA(*(HDC *)(param_4 + 0x18),0xfc,(int)local_258,local_14,
                   (int)pcVar7 - (int)(local_14 + 1));
          if (pPVar2->loss_pct < 0x33) {
            if (pPVar2->loss_pct < 0x1a) {
              CVar31 = 0xff00;
            }
            else {
              CVar31 = 0xffff;
            }
          }
          else {
            CVar31 = 0xff;
          }
          SetTextColor(*(HDC *)(param_4 + 0x18),CVar31);
          sprintf(local_14,"%d",pPVar2->loss_pct);
          pcVar7 = local_14;
          do {
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          TextOutA(*(HDC *)(param_4 + 0x18),0x119,(int)local_258,local_14,
                   (int)pcVar7 - (int)(local_14 + 1));
          SetTextAlign(*(HDC *)(param_4 + 0x18),(UINT)local_260);
        }
        SetTextColor(*(HDC *)(param_4 + 0x18),(COLORREF)local_25c);
        return 1;
      }
      if (param_2 == 2) {
        if (iTimerID != 0) {
          KillTimer((HWND)param_1,iTimerID);
          iTimerID = 0;
        }
        BEnabled = 0;
        iNetEscapeSetMessage = 0;
        iNetEscapeEndMessage = 0;
        PlayerList::Init((PlayerList *)&playersInSyncGame,(HWND__ *)0x0,Net::dp,(HWND__ *)0x0,
                         (Chat *)0x0,GamePingHandler);
        playersInSyncGame.hLaunchButton = (HWND__ *)0x0;
        playersInSyncGame.dwConnectStateSendTime = Get_TimeNow();
        pSVar16 = simpleVehicleList;
        Net::CHAT_PACKET_ID_CALLBACK = (_func___cdecl_void_ushort_char_ptr_char_ptr_uint *)0x0;
        Net::WHISPER_PACKET_ID_CALLBACK = (_func___cdecl_void_ushort_char_ptr_char_ptr_uint *)0x0;
        Net::KICKED_PACKET_ID_CALLBACK = (_func___cdecl_void *)0x0;
        Net::AUTOKICKED_PACKET_ID_CALLBACK = (_func___cdecl_void *)0x0;
        if (simpleVehicleList != (SimpleVehicleList *)0x0) {
          SimpleVehicleList::~SimpleVehicleList(simpleVehicleList);
          operator_delete(pSVar16);
          simpleVehicleList = (SimpleVehicleList *)0x0;
        }
        CleanCurrentBackground();
        pSVar9 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar9);
          backGround = (ShellBitmap *)0x0;
        }
        pSVar10 = lrButton;
        if (lrButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(lrButton);
          operator_delete(pSVar10);
          lrButton = (ShellButton *)0x0;
        }
        pSVar10 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar10);
          ulButton = (ShellButton *)0x0;
        }
        pSVar10 = llButton;
        if (llButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(llButton);
          operator_delete(pSVar10);
          llButton = (ShellButton *)0x0;
        }
        pSVar10 = whisperButton;
        if (whisperButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(whisperButton);
          operator_delete(pSVar10);
          whisperButton = (ShellButton *)0x0;
        }
        pSVar10 = muteButton;
        if (muteButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(muteButton);
          operator_delete(pSVar10);
          muteButton = (ShellButton *)0x0;
        }
        pSVar10 = kickButton;
        if (kickButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(kickButton);
          operator_delete(pSVar10);
          kickButton = (ShellButton *)0x0;
        }
        pSVar10 = chatUpButton;
        if (chatUpButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(chatUpButton);
          operator_delete(pSVar10);
          chatUpButton = (ShellButton *)0x0;
        }
        pSVar10 = chatDownButton;
        if (chatDownButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(chatDownButton);
          operator_delete(pSVar10);
          chatDownButton = (ShellButton *)0x0;
        }
        pSVar10 = statUpButton;
        if (statUpButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(statUpButton);
          operator_delete(pSVar10);
          statUpButton = (ShellButton *)0x0;
        }
        pSVar10 = statDownButton;
        if (statDownButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(statDownButton);
          operator_delete(pSVar10);
          statDownButton = (ShellButton *)0x0;
        }
        pTVar11 = statsLabel;
        if (statsLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(statsLabel);
          operator_delete(pTVar11);
          statsLabel = (TextLabel *)0x0;
        }
        pTVar11 = pstatLabel;
        if (pstatLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(pstatLabel);
          operator_delete(pTVar11);
          pstatLabel = (TextLabel *)0x0;
        }
        pTVar11 = playerLabel;
        if (playerLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(playerLabel);
          operator_delete(pTVar11);
          playerLabel = (TextLabel *)0x0;
        }
        pTVar11 = chatLabel;
        if (chatLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(chatLabel);
          operator_delete(pTVar11);
          chatLabel = (TextLabel *)0x0;
        }
        pTVar12 = statsDesc;
        if (statsDesc != (TabTextWindow *)0x0) {
          TabTextWindow::~TabTextWindow(statsDesc);
          operator_delete(pTVar12);
          statsDesc = (TabTextWindow *)0x0;
        }
        pTVar11 = pLabel;
        if (pLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(pLabel);
          operator_delete(pTVar11);
          pLabel = (TextLabel *)0x0;
        }
        pTVar11 = tLabel;
        if (tLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(tLabel);
          operator_delete(pTVar11);
          tLabel = (TextLabel *)0x0;
        }
        pTVar11 = vLabel;
        if (vLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(vLabel);
          operator_delete(pTVar11);
          vLabel = (TextLabel *)0x0;
        }
        pTVar11 = pgLabel;
        if (pgLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(pgLabel);
          operator_delete(pTVar11);
          pgLabel = (TextLabel *)0x0;
        }
        pTVar11 = lLabel;
        if (lLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(lLabel);
          operator_delete(pTVar11);
          lLabel = (TextLabel *)0x0;
        }
        pTVar11 = helpLabel;
        if (helpLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(helpLabel);
          operator_delete(pTVar11);
          helpLabel = (TextLabel *)0x0;
        }
        DeleteObject(hbmpHost);
        DeleteObject(hbmpMute);
        DeleteObject(hbmpReady);
        DeleteObject(hbmpWaiting);
        return 0;
      }
      if (param_2 == 0xf) {
        pHVar4 = BeginPaint((HWND)param_1,(LPPAINTSTRUCT)local_254);
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::BltBitmap(backGround,(HDC__ *)pHVar4);
        }
        if (lrButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(lrButton,(HDC__ *)pHVar4);
        }
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar4);
        }
        if (llButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(llButton,(HDC__ *)pHVar4);
        }
        if (whisperButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(whisperButton,(HDC__ *)pHVar4);
        }
        if (muteButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(muteButton,(HDC__ *)pHVar4);
        }
        if (kickButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(kickButton,(HDC__ *)pHVar4);
        }
        if (chatUpButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(chatUpButton,(HDC__ *)pHVar4);
        }
        if (chatDownButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(chatDownButton,(HDC__ *)pHVar4);
        }
        if (statUpButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(statUpButton,(HDC__ *)pHVar4);
        }
        if (statDownButton != (ShellButton *)0x0) {
          ShellButton::UpdateButton(statDownButton,(HDC__ *)pHVar4);
        }
        if (statsLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(statsLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (pstatLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(pstatLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (playerLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(playerLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (chatLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(chatLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (pLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(pLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (tLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(tLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (vLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(vLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (pgLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(pgLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (lLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(lLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (helpLabel != (TextLabel *)0x0) {
          TextLabel::DrawLabelText(helpLabel,(HDC__ *)pHVar4,(char *)0x0,0);
        }
        if (statsDesc != (TabTextWindow *)0x0) {
          (**(code **)statsDesc->_padding_)(pHVar4,0);
        }
        EndPaint((HWND)param_1,(PAINTSTRUCT *)local_254);
        return 0;
      }
      if (param_2 == 0x14) {
        return 1;
      }
      if (param_2 == 0x20) {
        set_cursor(0);
        SetWindowLongA((HWND)param_1,0,1);
        return 1;
      }
      return 0;
    }
    if (param_2 == 0x2c) {
      *(undefined4 *)(param_4 + 0x10) = 0x10;
      return 1;
    }
    if (param_2 != 0x110) {
      if (param_2 != 0x111) {
        return 0;
      }
      if ((param_3 & 0xffff) == 1) {
        pdVar8 = (dp_s *)(uint)Net::myPlayerID;
        pSVar32 = &playersInSyncGame;
        uVar28 = 0xf870;
        pdVar24 = Net::dp;
        GetDlgItem((HWND)param_1,0x825);
        HandleChatInput((HWND__ *)pdVar24,pdVar8,uVar28,(char *)pSVar32,unaff_EDI,unaff_ESI);
        return 1;
      }
      if ((param_3 & 0xffff) != 0x822) {
        return 0;
      }
      if (param_3 >> 0x10 == 1) {
        if (playersInSyncGame._padding_ == 0) {
          return 1;
        }
        InvalidateRect((HWND)playersInSyncGame._padding_,(RECT *)0x0,1);
        return 1;
      }
      return 0;
    }
    SetFontRecursive(param_1);
    iYouWonStratgy = 0;
    BEnabled = 1;
    init_screen_pos(param_1);
    init_bitmap_dc(param_1);
    if (Net::hosting == false) {
      pSVar9 = operator_new(0x20);
      if (pSVar9 != (ShellBitmap *)0x0) {
        pcVar7 = "bitmap\\multipe.bmp";
        goto LAB_00563c04;
      }
    }
    else {
      pSVar9 = operator_new(0x20);
      if (pSVar9 != (ShellBitmap *)0x0) {
        pcVar7 = "bitmap\\multipeh.bmp";
LAB_00563c04:
        backGround = ShellBitmap::ShellBitmap(pSVar9,pcVar7,0,0);
        goto LAB_00563c22;
      }
    }
    backGround = (ShellBitmap *)0x0;
LAB_00563c22:
    SetCurrentBackground(param_1,backGround);
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      lrButton = (ShellButton *)0x0;
    }
    else {
      lrButton = ShellButton::ShellButton
                           (pSVar10,local_258,shell_hInstance,0xc4,0xc3,0xc5,0x1b9,0x1bd,199,0x22,1,
                            "LEAVE GAME");
    }
    ShellButton::SetLabelPos(lrButton,0x1fb,0x1c4,0x58,0x17);
    if ((Net::bStopGame == false) && (mission_stop == 0)) {
      pSVar10 = operator_new(0x110);
      if (pSVar10 == (ShellButton *)0x0) {
        ulButton = (ShellButton *)0x0;
      }
      else {
        ulButton = ShellButton::ShellButton
                             (pSVar10,local_258,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,
                              "RETURN TO GAME");
      }
      ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
      read_text_label("escape","return_to_game",ulButton->labelText);
    }
    else {
      ulButton = (ShellButton *)0x0;
    }
    mission_stop = 0;
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      llButton = (ShellButton *)0x0;
    }
    else {
      llButton = ShellButton::ShellButton
                           (pSVar10,local_258,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                            "OPTIONS");
    }
    ShellButton::SetLabelPos(llButton,0x2f,0x1c6,0x58,0x17);
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      whisperButton = (ShellButton *)0x0;
    }
    else {
      whisperButton =
           ShellButton::ShellButton
                     (pSVar10,local_258,shell_hInstance,0,0x81a,0x7fa,0x24,0x1a7,0x13,0x12,1,"W");
    }
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      muteButton = (ShellButton *)0x0;
    }
    else {
      muteButton = ShellButton::ShellButton
                             (pSVar10,local_258,shell_hInstance,0,0x81a,0x7fa,0x38,0x1a7,0x13,0x12,1
                              ,"M");
    }
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      kickButton = (ShellButton *)0x0;
    }
    else {
      kickButton = ShellButton::ShellButton
                             (pSVar10,local_258,shell_hInstance,0,0x81a,0x7fa,0x4c,0x1a7,0x13,0x12,1
                              ,"K");
    }
    if (Net::hosting == false) {
      ShellButton::HideButton(kickButton,0);
    }
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      chatUpButton = (ShellButton *)0x0;
    }
    else {
      chatUpButton = ShellButton::ShellButton
                               (pSVar10,local_258,shell_hInstance,0,0x819,0x7ff,0x249,0x176,0x13,
                                0x12,0,(char *)0x0);
    }
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      chatDownButton = (ShellButton *)0x0;
    }
    else {
      chatDownButton =
           ShellButton::ShellButton
                     (pSVar10,local_258,shell_hInstance,0,0x818,0x800,0x249,0x188,0x13,0x12,0,
                      (char *)0x0);
    }
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      statUpButton = (ShellButton *)0x0;
    }
    else {
      statUpButton = ShellButton::ShellButton
                               (pSVar10,local_258,shell_hInstance,0,0x819,0x7ff,0x12f,0x196,0x13,
                                0x12,0,(char *)0x0);
    }
    pSVar10 = operator_new(0x110);
    if (pSVar10 == (ShellButton *)0x0) {
      statDownButton = (ShellButton *)0x0;
    }
    else {
      statDownButton =
           ShellButton::ShellButton
                     (pSVar10,local_258,shell_hInstance,0,0x818,0x800,0x12f,0x1a8,0x13,0x12,0,
                      (char *)0x0);
    }
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      statsLabel = (TextLabel *)0x0;
    }
    else {
      statsLabel = TextLabel::TextLabel(pTVar11,local_258,"Game Stats",0x33,0x25,0x217,0xf,0);
    }
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      pLabel = (TextLabel *)0x0;
    }
    else {
      pLabel = TextLabel::TextLabel(pTVar11,local_258,"Player",0x36,0x11c,0x14,0xd,0);
    }
    TextLabel::SetTextFont(pLabel,defaultFont,defaultFontSize2);
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      tLabel = (TextLabel *)0x0;
    }
    else {
      tLabel = TextLabel::TextLabel(pTVar11,local_258,"Team",0x9d,0x11c,0x14,0xd,0);
    }
    TextLabel::SetTextFont(tLabel,defaultFont,defaultFontSize2);
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      vLabel = (TextLabel *)0x0;
    }
    else {
      vLabel = TextLabel::TextLabel(pTVar11,local_258,"Vehicle",0xbb,0x11c,0x14,0xd,0);
    }
    TextLabel::SetTextFont(vLabel,defaultFont,defaultFontSize2);
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      pgLabel = (TextLabel *)0x0;
    }
    else {
      pgLabel = TextLabel::TextLabel(pTVar11,local_258,"Ping",0x10d,0x11c,0x14,0xd,0);
    }
    TextLabel::SetTextFont(pgLabel,defaultFont,defaultFontSize2);
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      lLabel = (TextLabel *)0x0;
    }
    else {
      lLabel = TextLabel::TextLabel(pTVar11,local_258,"Loss",0x129,0x11c,0x14,0xd,0);
    }
    TextLabel::SetTextFont(lLabel,defaultFont,defaultFontSize2);
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      playerLabel = (TextLabel *)0x0;
    }
    else {
      playerLabel = TextLabel::TextLabel(pTVar11,local_258,"Player Status",0x3c,0x108,0x46,0xf,0);
    }
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      chatLabel = (TextLabel *)0x0;
    }
    else {
      chatLabel = TextLabel::TextLabel(pTVar11,local_258,"Chat",0x158,0x108,0x46,0xf,0);
    }
    pTVar12 = operator_new(0x1f488);
    if (pTVar12 == (TabTextWindow *)0x0) {
      statsDesc = (TabTextWindow *)0x0;
    }
    else {
      statsDesc = TabTextWindow::TabTextWindow(pTVar12,local_258,"NULL",0x2b,0x3a,0x22d,0xb9,0);
    }
    pTVar11 = operator_new(0x128);
    if (pTVar11 == (TextLabel *)0x0) {
      helpLabel = (TextLabel *)0x0;
    }
    else {
      helpLabel = TextLabel::TextLabel(pTVar11,local_258,"NULL",0xd8,0x1c2,0xcd,0x11,0);
    }
    TextLabel::HideLabelText(helpLabel,1);
    read_text_label("multi_common","player",pLabel->textData);
    read_text_label("multi_common","team",tLabel->textData);
    read_text_label("multi_common","vehicle",vLabel->textData);
    read_text_label("escape","ping",pgLabel->textData);
    read_text_label("multi_common","loss",lLabel->textData);
    read_text_label("multi_common","options",llButton->labelText);
    read_text_label("multi_common","leave_game",lrButton->labelText);
    read_text_label("multi_common","stats",playerLabel->textData);
    read_text_label("multi_common","chat",chatLabel->textData);
    read_text_label("multi_common","game_stats",statsLabel->textData);
    read_text_label("multi_common","whisper",whisperButton->labelText);
    read_text_label("multi_common","mute",muteButton->labelText);
    read_text_label("multi_common","kick",kickButton->labelText);
    write_score((char *)&statsDesc->_padding_);
    uVar13 = Hash((char *)&statsDesc->_padding_,0x811c9dc5);
    BVar33 = 1;
    iVar29 = 100;
    iVar26 = 0x11c;
    iVar25 = 0x12e;
    iVar23 = 0x25;
    statsDesc->_padding_ = uVar13;
    pHVar14 = GetDlgItem((HWND)local_258,0x822);
    MoveWindow(pHVar14,iVar23,iVar25,iVar26,iVar29,BVar33);
    BVar33 = 1;
    iVar29 = 0x10;
    iVar26 = 0x100;
    iVar25 = 0x1a5;
    iVar23 = 0x154;
    pHVar14 = GetDlgItem((HWND)local_258,0x825);
    MoveWindow(pHVar14,iVar23,iVar25,iVar26,iVar29,BVar33);
    SendDlgItemMessageA((HWND)local_258,0x825,0xc5,0xf1,0);
    BVar33 = 1;
    iVar29 = 0x7a;
    iVar26 = 0xfa;
    iVar25 = 0x11c;
    iVar23 = 0x14c;
    pHVar14 = GetDlgItem((HWND)local_258,0x826);
    MoveWindow(pHVar14,iVar23,iVar25,iVar26,iVar29,BVar33);
    iTimerID = SetTimer((HWND)local_258,1,10,(TIMERPROC)0x0);
    pHVar14 = GetDlgItem((HWND)local_258,0x826);
    Chat::Init((Chat *)&chatGame,(HWND__ *)pHVar14);
    PlayerList::Clear((PlayerList *)&playersInSyncGame);
    SyncGamePlayerList::Timer(&playersInSyncGame);
    pHVar34 = (HWND__ *)0x0;
    pcVar30 = GamePingHandler;
    pCVar27 = &chatGame;
    pHVar14 = GetDlgItem((HWND)local_258,0x825);
    pdVar24 = Net::dp;
    pHVar15 = GetDlgItem((HWND)local_258,0x822);
    SyncGamePlayerList::Init
              (&playersInSyncGame,(HWND__ *)pHVar15,pdVar24,(HWND__ *)pHVar14,(Chat *)pCVar27,
               pcVar30,pHVar34);
    hbmpHost = (HBITMAP__ *)LoadBitmapA((HINSTANCE)shell_hInstance,(LPCSTR)0x820);
    hbmpMute = (HBITMAP__ *)LoadBitmapA((HINSTANCE)shell_hInstance,(LPCSTR)0x821);
    hbmpReady = (HBITMAP__ *)LoadBitmapA((HINSTANCE)shell_hInstance,(LPCSTR)0x822);
    hbmpWaiting = (HBITMAP__ *)LoadBitmapA((HINSTANCE)shell_hInstance,(LPCSTR)0x823);
    Net::CHAT_PACKET_ID_CALLBACK = chat_packet_id_callback;
    Net::WHISPER_PACKET_ID_CALLBACK = whisper_packet_id_callback;
    Net::KICKED_PACKET_ID_CALLBACK = kicked_packet_id_callback;
    Net::AUTOKICKED_PACKET_ID_CALLBACK = autokicked_packet_id_callback;
    pSVar16 = operator_new(8);
    if (pSVar16 == (SimpleVehicleList *)0x0) {
      simpleVehicleList = (SimpleVehicleList *)0x0;
    }
    else {
      simpleVehicleList = SimpleVehicleList::SimpleVehicleList(pSVar16);
    }
    pdVar20 = &prevstats;
    for (iVar23 = 6; iVar23 != 0; iVar23 = iVar23 + -1) {
      pdVar20->in = 0;
      pdVar20 = (dp_stat_t *)&pdVar20->out;
    }
    pHVar14 = GetDlgItem((HWND)local_258,0x825);
    SetFocus(pHVar14);
    return 1;
  }
  if (iTimerID != 0) {
    KillTimer((HWND)param_1,iTimerID);
    iTimerID = 0;
  }
  EnableWindow((HWND)param_1,0);
  pAVar17 = AiMission::GetCurrent();
  if (pAVar17 != (AiMission *)0x0) {
    DoNetEscapeFrame();
  }
  DVar18 = Get_TimeNow();
  if (DVar18 + 3000 < dwNextTimerCall) {
    dwNextTimerCall = DVar18;
  }
  if (dwNextTimerCall < DVar18) {
    SyncGamePlayerList::Timer(&playersInSyncGame);
    dwNextTimerCall = DVar18 + 2000;
  }
  if (statsDesc != (TabTextWindow *)0x0) {
    write_score((char *)&statsDesc->_padding_);
    uVar13 = Hash((char *)&statsDesc->_padding_,0x811c9dc5);
    pTVar12 = statsDesc;
    if (statsDesc->_padding_ != uVar13) {
      statsDesc->_padding_ = uVar13;
      (**(code **)(pTVar12->_padding_ + 4))(0);
    }
  }
  if (ulButton != (ShellButton *)0x0) {
    if ((((iNetEscapeModemNoResponse == 0) && (iNetEscapeSessionLostPacket == 0)) &&
        (iNetEscapeEndMessage == 0)) && (iNetEscapeGotKickedOut == 0)) goto LAB_005647e1;
    if (ulButton->nButtonVisible != 0) {
      ShellButton::HideButton(ulButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&ulButton->buttonRect,0);
    }
    if (ulButton->nButtonEnable != 0) {
      ShellButton::DisableButton(ulButton);
    }
  }
  if (iNetEscapeModemNoResponse == 0) {
    if (iNetEscapeSessionLostPacket == 0) {
      if (iNetEscapeEndMessage == -1) {
        pcVar7 = "You have been eliminated!";
        pcVar21 = local_214;
        for (iVar23 = 6; iVar23 != 0; iVar23 = iVar23 + -1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar21 = pcVar21 + 4;
        }
        iNetEscapeEndMessage = 0;
        *(undefined2 *)pcVar21 = *(undefined2 *)pcVar7;
        memset(local_1fa,0,0xe6);
        read_text_label("multi_message","you_lose",local_214);
        do_error(local_258,local_214);
        param_1 = local_258;
      }
      if (iNetEscapeEndMessage == 1) {
        builtin_strncpy(local_114,"You win",8);
        iNetEscapeEndMessage = 0;
        memset(local_114 + 8,0,0xf8);
        read_text_label("multi_message","you_win",local_114);
        do_error(param_1,local_114);
      }
      if (iNetEscapeGotKickedOut == 0) {
LAB_005647e1:
        UpdatePending(&prevstats,helpLabel);
        if (BEnabled != 0) {
          EnableWindow((HWND)param_1,1);
        }
        lpTimerFunc = (TIMERPROC)0x0;
        iVar23 = GetRunning();
        iTimerID = SetTimer((HWND)param_1,1,(-(uint)(iVar23 != 5) & 0x28) + 10,lpTimerFunc);
        return 0;
      }
      Net::Close();
      SetRunning(2);
      if (iNetEscapeGotKickedOut == 1) {
        pcVar7 = "You have been kicked out";
        pcVar21 = local_214;
        for (iVar23 = 6; iVar23 != 0; iVar23 = iVar23 + -1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar21 = pcVar21 + 4;
        }
        *pcVar21 = *pcVar7;
        memset(&local_1fb,0,0xe7);
        pcVar7 = "player_kick";
LAB_005647b3:
        read_text_label("multi_error",pcVar7,local_214);
        do_error(local_258,local_214);
        param_1 = local_258;
      }
      else if (iNetEscapeGotKickedOut == 2) {
        pcVar7 = "You have been auto-kicked due to lag";
        pcVar21 = local_214;
        for (iVar23 = 9; iVar23 != 0; iVar23 = iVar23 + -1) {
          *(undefined4 *)pcVar21 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar21 = pcVar21 + 4;
        }
        *pcVar21 = *pcVar7;
        memset(local_1ef,0,0xdb);
        pcVar7 = "player_autokick";
        goto LAB_005647b3;
      }
      EnableWindow((HWND)param_1,0);
      goto LAB_0056462c;
    }
    iNetEscapeSessionLostPacket = 0;
    SetRunning(2);
    pcVar7 = "Lost connection to game";
    pcVar21 = local_114;
    for (iVar23 = 6; iVar23 != 0; iVar23 = iVar23 + -1) {
      *(undefined4 *)pcVar21 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar21 = pcVar21 + 4;
    }
    memset(local_fc,0,0xe8);
    pcVar7 = "game_lost";
  }
  else {
    iNetEscapeModemNoResponse = 0;
    SetRunning(2);
    pcVar7 = "Modem lost connection";
    pcVar21 = local_114;
    for (iVar23 = 5; iVar23 != 0; iVar23 = iVar23 + -1) {
      *(undefined4 *)pcVar21 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar21 = pcVar21 + 4;
    }
    *(undefined2 *)pcVar21 = *(undefined2 *)pcVar7;
    memset(local_fe,0,0xea);
    pcVar7 = "modem_lost";
  }
  read_text_label("multi_error",pcVar7,local_114);
  do_error(local_258,local_114);
  Net::Close();
  EnableWindow((HWND)local_258,0);
  param_1 = local_258;
LAB_0056462c:
  nShellMode = 0;
  nNetMode = 1;
  Shell_EndDialog(param_1,1);
  return 1;
}
