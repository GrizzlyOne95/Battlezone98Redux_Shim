/*
 * Entry: 00569627
 * Name: STransportDlgProc
 * Namespace: Global
 * Signature: int STransportDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl STransportDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  char cVar1;
  HDC pHVar2;
  HWND pHVar3;
  HBRUSH pHVar4;
  char *pcVar5;
  PortData **ppPVar6;
  int iVar7;
  undefined1 auVar8 [4];
  LRESULT LVar9;
  int *piVar10;
  RECT *pRVar11;
  uint uVar12;
  HWND pHVar13;
  WPARAM WVar14;
  ServerList *pSVar15;
  ServerList *pSVar16;
  FlagList *pFVar17;
  ShellBitmap *pSVar18;
  ShellButton *pSVar19;
  TextLabel *pTVar20;
  OptionBox *pOVar21;
  HWND pHVar22;
  HWND pHVar23;
  char *pcVar24;
  char *pcVar25;
  PlayerInfo *this;
  HGDIOBJ pvVar26;
  char *pcVar27;
  short sVar28;
  int unaff_EBX;
  ServerList *pSVar29;
  int iVar30;
  char **ppcVar31;
  code *pcVar32;
  sTransport *psVar33;
  comm_driverInfo_t *pcVar34;
  uint uVar35;
  code *pcVar36;
  int iVar37;
  comm_driverInfo_t *pcVar38;
  byte *pbVar39;
  bool bVar40;
  bool bVar41;
  _Vector_iterator<PortData_*,std::allocator<PortData_*>_> _Var42;
  HWND__ *pHVar43;
  WPARAM WVar44;
  UINT UVar45;
  LPARAM LVar46;
  int iVar47;
  dp_s *pdVar48;
  COLORREF color;
  BOOL BVar49;
  undefined4 uVar50;
  net_defaults_s *lParam;
  LPARAM lParam_00;
  undefined1 local_2a4 [4];
  undefined1 local_2a0 [8];
  undefined1 local_298 [12];
  RECT local_28c;
  _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> local_27c;
  RECT local_274;
  undefined1 auStack_260 [8];
  undefined1 local_258 [4];
  undefined1 auStack_254 [8];
  undefined1 auStack_24c [8];
  tagPAINTSTRUCT local_244;
  char local_204 [22];
  undefined1 local_1ee [2];
  undefined1 local_1ec;
  undefined1 local_1eb [9];
  undefined1 local_1e2 [222];
  char local_104 [38];
  undefined1 local_de [218];
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)local_2a4;
  if (0x113 < param_2) {
    if (param_2 == 0x133) {
      SetTextColor((HDC)param_3,0xff00);
LAB_0056d710:
      SetBkMode((HDC)param_3,2);
      SetBkColor((HDC)param_3,0);
LAB_0056d720:
      pvVar26 = GetStockObject(4);
      return (int)pvVar26;
    }
    if (param_2 == 0x134) {
      SetTextColor((HDC)param_3,0xff00);
      SetBkMode((HDC)param_3,1);
      goto LAB_0056d720;
    }
    if (param_2 == 0x136) goto LAB_0056d720;
    if (param_2 == 0x138) {
      SetTextColor((HDC)param_3,0xff00);
      goto LAB_0056d710;
    }
    if (param_2 == 0x200) {
      iVar37 = 0;
      iVar7 = 1;
      uVar35 = (uint)param_4 >> 0x10;
      uVar12 = param_4 & 0xffff;
      iVar30 = ShellButton::CheckRollOver(newCharButton,uVar12,uVar35);
      ShellButton::SetButtonMode(newCharButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(delCharButton,uVar12,uVar35);
      ShellButton::SetButtonMode(delCharButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(ulButton,uVar12,uVar35);
      ShellButton::SetButtonMode(ulButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(urButton,uVar12,uVar35);
      ShellButton::SetButtonMode(urButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(llButton,uVar12,uVar35);
      ShellButton::SetButtonMode(llButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(comPortButton,uVar12,uVar35);
      ShellButton::SetButtonMode(comPortButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(nmComPortButton,uVar12,uVar35);
      ShellButton::SetButtonMode(nmComPortButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(baudRateButton,uVar12,uVar35);
      ShellButton::SetButtonMode(baudRateButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(newPhoneButton,uVar12,uVar35);
      ShellButton::SetButtonMode(newPhoneButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(editPhoneButton,uVar12,uVar35);
      ShellButton::SetButtonMode(editPhoneButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(delPhoneButton,uVar12,uVar35);
      ShellButton::SetButtonMode(delPhoneButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(dialButton,uVar12,uVar35);
      ShellButton::SetButtonMode(dialButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(answerButton,uVar12,uVar35);
      ShellButton::SetButtonMode(answerButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(flagLeftButton,uVar12,uVar35);
      ShellButton::SetButtonMode(flagLeftButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(flagRightButton,uVar12,uVar35);
      ShellButton::SetButtonMode(flagRightButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(charUpButton,uVar12,uVar35);
      ShellButton::SetButtonMode(charUpButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(charDownButton,uVar12,uVar35);
      ShellButton::SetButtonMode(charDownButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(phoneUpButton,uVar12,uVar35);
      ShellButton::SetButtonMode(phoneUpButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(phoneDownButton,uVar12,uVar35);
      ShellButton::SetButtonMode(phoneDownButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(serverUpButton,uVar12,uVar35);
      ShellButton::SetButtonMode(serverUpButton,iVar30,iVar7,iVar37);
      iVar37 = 0;
      iVar7 = 1;
      iVar30 = ShellButton::CheckRollOver(serverDownButton,uVar12,uVar35);
      ShellButton::SetButtonMode(serverDownButton,iVar30,iVar7,iVar37);
      return 0;
    }
    if (param_2 == 0x201) {
      uVar12 = (uint)param_4 >> 0x10;
      uVar35 = param_4 & 0xffff;
      iVar30 = ShellButton::CheckRollOver(newCharButton,uVar35,uVar12);
      pSVar19 = newCharButton;
      if (((((((iVar30 == 0) &&
              (iVar30 = ShellButton::CheckRollOver(delCharButton,uVar35,uVar12),
              pSVar19 = delCharButton, iVar30 == 0)) &&
             (iVar30 = ShellButton::CheckRollOver(newPhoneButton,uVar35,uVar12),
             pSVar19 = newPhoneButton, iVar30 == 0)) &&
            ((iVar30 = ShellButton::CheckRollOver(editPhoneButton,uVar35,uVar12),
             pSVar19 = editPhoneButton, iVar30 == 0 &&
             (iVar30 = ShellButton::CheckRollOver(delPhoneButton,uVar35,uVar12),
             pSVar19 = delPhoneButton, iVar30 == 0)))) &&
           ((iVar30 = ShellButton::CheckRollOver(dialButton,uVar35,uVar12), pSVar19 = dialButton,
            iVar30 == 0 &&
            ((iVar30 = ShellButton::CheckRollOver(answerButton,uVar35,uVar12),
             pSVar19 = answerButton, iVar30 == 0 &&
             (iVar30 = ShellButton::CheckRollOver(ulButton,uVar35,uVar12), pSVar19 = ulButton,
             iVar30 == 0)))))) &&
          ((iVar30 = ShellButton::CheckRollOver(urButton,uVar35,uVar12), pSVar19 = urButton,
           iVar30 == 0 &&
           (((((iVar30 = ShellButton::CheckRollOver(llButton,uVar35,uVar12), pSVar19 = llButton,
               iVar30 == 0 &&
               (iVar30 = ShellButton::CheckRollOver(comPortButton,uVar35,uVar12),
               pSVar19 = comPortButton, iVar30 == 0)) &&
              (iVar30 = ShellButton::CheckRollOver(nmComPortButton,uVar35,uVar12),
              pSVar19 = nmComPortButton, iVar30 == 0)) &&
             (((iVar30 = ShellButton::CheckRollOver(baudRateButton,uVar35,uVar12),
               pSVar19 = baudRateButton, iVar30 == 0 &&
               (iVar30 = ShellButton::CheckRollOver(flagLeftButton,uVar35,uVar12),
               pSVar19 = flagLeftButton, iVar30 == 0)) &&
              ((iVar30 = ShellButton::CheckRollOver(flagRightButton,uVar35,uVar12),
               pSVar19 = flagRightButton, iVar30 == 0 &&
               ((iVar30 = ShellButton::CheckRollOver(charUpButton,uVar35,uVar12),
                pSVar19 = charUpButton, iVar30 == 0 &&
                (iVar30 = ShellButton::CheckRollOver(charDownButton,uVar35,uVar12),
                pSVar19 = charDownButton, iVar30 == 0)))))))) &&
            (iVar30 = ShellButton::CheckRollOver(phoneUpButton,uVar35,uVar12),
            pSVar19 = phoneUpButton, iVar30 == 0)))))) &&
         (((iVar30 = ShellButton::CheckRollOver(phoneDownButton,uVar35,uVar12),
           pSVar19 = phoneDownButton, iVar30 == 0 &&
           (iVar30 = ShellButton::CheckRollOver(serverUpButton,uVar35,uVar12),
           pSVar19 = serverUpButton, iVar30 == 0)) &&
          (iVar30 = ShellButton::CheckRollOver(serverDownButton,uVar35,uVar12),
          pSVar19 = serverDownButton, iVar30 == 0)))) {
        return 1;
      }
      ShellButton::SetButtonMode(pSVar19,2,1,0);
      return 1;
    }
    if (param_2 != 0x202) {
      return 0;
    }
    uVar12 = (uint)param_4 >> 0x10;
    uVar35 = param_4 & 0xffff;
    iVar30 = ShellButton::CheckRollOver(newCharButton,uVar35,uVar12);
    pcVar36 = EnableWindow_exref;
    if (iVar30 == 0) {
      iVar30 = ShellButton::CheckRollOver(delCharButton,uVar35,uVar12);
      pcVar36 = EnableWindow_exref;
      if (iVar30 == 0) {
        iVar30 = ShellButton::CheckRollOver(newPhoneButton,uVar35,uVar12);
        pcVar36 = EnableWindow_exref;
        if (iVar30 == 0) {
          iVar30 = ShellButton::CheckRollOver(delPhoneButton,uVar35,uVar12);
          pcVar36 = EnableWindow_exref;
          if (iVar30 != 0) {
            EnableWindow((HWND)param_1,0);
            PhoneNumberList::Delete(&phoneNumberList);
            PhoneNumberList::Save(&phoneNumberList,"netpho.txt");
            goto LAB_0056c5b3;
          }
          iVar30 = ShellButton::CheckRollOver(editPhoneButton,uVar35,uVar12);
          pcVar36 = EnableWindow_exref;
          if (iVar30 == 0) {
            iVar30 = ShellButton::CheckRollOver(nmComPortButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(nmComPortButton,1,0,0);
              pOVar21 = nmComPortBox;
LAB_0056c636:
              OptionBox::ToggleOptionBox(pOVar21);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(comPortButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(comPortButton,1,0,0);
              pOVar21 = comPortBox;
              goto LAB_0056c636;
            }
            iVar30 = ShellButton::CheckRollOver(baudRateButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(baudRateButton,1,0,0);
              pOVar21 = baudRateBox;
              goto LAB_0056c636;
            }
            iVar30 = ShellButton::CheckRollOver(flagLeftButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(flagLeftButton,1,0,0);
              FlagList::SelectionDown(flagList);
LAB_0056c69c:
              pcVar5 = FlagList::GetSelection(flagList);
              PlayerNameList::ChangeFlag(&playerNameList,pcVar5);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(flagRightButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(flagRightButton,1,0,0);
              FlagList::SelectionUp(flagList);
              goto LAB_0056c69c;
            }
            iVar30 = ShellButton::CheckRollOver(charUpButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(charUpButton,1,0,0);
              PlayerNameList::SelectionUp(&playerNameList);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(charDownButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(charDownButton,1,0,0);
              PlayerNameList::SelectionDown(&playerNameList);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(phoneUpButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(phoneUpButton,1,0,0);
              PhoneNumberList::SelectionUp(&phoneNumberList);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(phoneDownButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(phoneDownButton,1,0,0);
              PhoneNumberList::SelectionDown(&phoneNumberList);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(serverUpButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(serverUpButton,1,0,0);
              if (serverList == (ServerList *)0x0) {
                return 1;
              }
              ServerList::SelectionUp(serverList);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(serverDownButton,uVar35,uVar12);
            if (iVar30 != 0) {
              ShellButton::SetButtonMode(serverDownButton,1,0,0);
              if (serverList == (ServerList *)0x0) {
                return 1;
              }
              ServerList::SelectionDown(serverList);
              return 1;
            }
            iVar30 = ShellButton::CheckRollOver(dialButton,uVar35,uVar12);
            if (iVar30 == 0) {
              iVar30 = ShellButton::CheckRollOver(answerButton,uVar35,uVar12);
              if (iVar30 == 0) {
                iVar30 = ShellButton::CheckRollOver(ulButton,uVar35,uVar12);
                if (iVar30 != 0) {
                  EnableWindow((HWND)param_1,0);
                  if (serverList != (ServerList *)0x0) {
                    (**(code **)serverList->_padding_)(1);
                  }
                  serverList = (ServerList *)0x0;
                  if (Net::dp != (dp_s *)0x0) {
                    Net::Close();
                    dpDestroy(Net::dp,0);
                    Net::dp = (dp_s *)0x0;
                  }
                  pcVar5 = PlayerNameList::GetName(&playerNameList);
                  pcVar27 = player_name;
                  do {
                    cVar1 = *pcVar5;
                    pcVar5 = pcVar5 + 1;
                    *pcVar27 = cVar1;
                    pcVar27 = pcVar27 + 1;
                  } while (cVar1 != '\0');
                  iVar30 = 0;
                  do {
                    cVar1 = player_name[iVar30];
                    net_defaults.playername[iVar30] = cVar1;
                    iVar30 = iVar30 + 1;
                  } while (cVar1 != '\0');
                  SaveDefaults();
                  EnableWindow((HWND)param_1,1);
                  Net::DoNetworking(false);
                  nShellMode = 1;
                  Shell_EndDialog(param_1,0);
                  return 1;
                }
                iVar30 = ShellButton::CheckRollOver(llButton,uVar35,uVar12);
                pcVar36 = ShowWindow_exref;
                if (iVar30 != 0) {
                  ShowWindow((HWND)param_1,0);
                  EnableWindow((HWND)param_1,0);
                  do_options(0);
                  pSVar18 = backGround;
                  if (((nTransportMode != 4) && (nTransportMode != 5)) &&
                     ((pSVar18 = backGroundC, nTransportMode != 3 &&
                      (pSVar18 = backGroundB, nTransportMode == 2)))) {
                    pSVar18 = backGroundA;
                  }
                  SetCurrentBackground(param_1,pSVar18);
                  EnableWindow((HWND)param_1,1);
                  uVar50 = 5;
                  goto LAB_0056ce42;
                }
                iVar30 = ShellButton::CheckRollOver(urButton,uVar35,uVar12);
                if (iVar30 == 0) {
                  return 1;
                }
                pcVar5 = PlayerNameList::GetName(&playerNameList);
                if (*pcVar5 == '\0') {
                  EnableWindow((HWND)param_1,0);
                  pcVar5 = "No character selected";
                  pcVar27 = local_204;
                  for (iVar30 = 5; iVar30 != 0; iVar30 = iVar30 + -1) {
                    *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
                    pcVar5 = pcVar5 + 4;
                    pcVar27 = pcVar27 + 4;
                  }
                  *(undefined2 *)pcVar27 = *(undefined2 *)pcVar5;
                  memset(local_1ee,0,0xea);
                  pcVar5 = "no_character";
                }
                else {
                  pcVar27 = pcVar5;
                  do {
                    cVar1 = *pcVar27;
                    pcVar27[(int)player_name - (int)pcVar5] = cVar1;
                    pcVar27 = pcVar27 + 1;
                  } while (cVar1 != '\0');
                  if (*pcVar5 != '\0') {
                    Net_SetPlayerName(pcVar5);
                  }
                  iVar30 = 0;
                  do {
                    cVar1 = player_name[iVar30];
                    net_defaults.playername[iVar30] = cVar1;
                    pSVar29 = serverList;
                    iVar30 = iVar30 + 1;
                  } while (cVar1 != '\0');
                  if (serverList != (ServerList *)0x0) {
                    serverList->bStop = true;
                  }
                  if (nTransportMode == 3) {
                    if ((pSVar29 == (ServerList *)0x0) ||
                       (bVar40 = ServerList::ServerSelected(pSVar29), !bVar40)) {
                      EnableWindow((HWND)param_1,0);
                      builtin_strncpy(local_204,"No server selected",0x13);
                      memset(local_204 + 0x13,0,0xed);
                      pcVar5 = "no_server";
                      goto LAB_0056ceaa;
                    }
                    iVar30 = ServerList::SetSelected(serverList);
                    if (iVar30 == 0) goto LAB_0056cece;
                  }
                  LVar46 = 0;
                  WVar14 = 0;
                  UVar45 = 0x188;
                  pHVar13 = GetDlgItem((HWND)param_1,0x41f);
                  WVar14 = SendMessageA(pHVar13,UVar45,WVar14,LVar46);
                  LVar46 = 0;
                  if (WVar14 != 0xffffffff) {
                    UVar45 = 0x199;
                    WVar44 = WVar14;
                    pHVar13 = GetDlgItem((HWND)param_1,0x41f);
                    LVar9 = SendMessageA(pHVar13,UVar45,WVar44,LVar46);
                    if (LVar9 == -1) goto LAB_0056cece;
                    iVar30 = 0x20;
                    psVar33 = Transport + LVar9;
                    pcVar5 = dp_transport.fname;
                    net_defaults.TransportIndex = WVar14;
                    for (; iVar30 != 0; iVar30 = iVar30 + -1) {
                      *(undefined4 *)pcVar5 = *(undefined4 *)(psVar33->dp_transport).fname;
                      psVar33 = (sTransport *)((psVar33->dp_transport).fname + 4);
                      pcVar5 = pcVar5 + 4;
                    }
                    pcVar34 = &Transport[LVar9].comm_driverInfo;
                    pcVar38 = &comm_driverInfo;
                    for (iVar30 = 0xc; iVar30 != 0; iVar30 = iVar30 + -1) {
                      *(undefined4 *)pcVar38->signature = *(undefined4 *)pcVar34->signature;
                      pcVar34 = (comm_driverInfo_t *)(pcVar34->signature + 4);
                      pcVar38 = (comm_driverInfo_t *)(pcVar38->signature + 4);
                    }
                    *(undefined2 *)pcVar38->signature = *(undefined2 *)pcVar34->signature;
                    Net_SetTransport(dp_transport.fname);
                    this = operator_new(0x14);
                    if (this == (PlayerInfo *)0x0) {
                      playerInfo = (PlayerInfo *)0x0;
                    }
                    else {
                      pcVar5 = PlayerNameList::GetDescription(&playerNameList);
                      pcVar27 = PlayerNameList::GetURL(&playerNameList);
                      pcVar24 = PlayerNameList::GetEmail(&playerNameList);
                      playerInfo = PlayerInfo::PlayerInfo(this,pcVar24,pcVar27,pcVar5);
                    }
                    memset(&params,0,0x2c);
                    params.reqLen = 0x2c;
                    if (((byte)comm_driverInfo.needs & 2) != 0) {
                      params.sessionId = Get_TimeNow();
                    }
                    if (((byte)comm_driverInfo.needs & 8) != 0) {
                      params.baud = 0xe100;
                    }
                    if (((byte)comm_driverInfo.needs & 4) == 0) {
                      if (nTransportMode == 3) {
                        pcVar5 = "ConnectPortInternet";
                      }
                      else {
                        if (nTransportMode != 5) goto LAB_0056d114;
                        pcVar5 = "ConnectPortLAN";
                      }
                      params.portnum =
                           GetPrivateProfileIntA("Net",pcVar5,params.portnum,".\\net.ini");
                    }
                    else {
                      params.portnum = OptionBox::GetCurrentValue(nmComPortBox);
                      net_defaults.serialcomport = params.portnum;
                    }
LAB_0056d114:
                    Net_SetParams(&params);
                    if ((nTransportMode == 3) ||
                       (iVar30 = dpCreate(&Net::dp,&dp_transport,&params,0), iVar30 == 0)) {
                      if (serverList != (ServerList *)0x0) {
                        (**(code **)serverList->_padding_)(1);
                      }
                      serverList = (ServerList *)0x0;
                      if ((nTransportMode == 4) || (nTransportMode == 5)) {
                        Net_SetIPX();
                      }
                      else if ((nTransportMode == 1) || (nTransportMode == 2)) {
                        Net_SetInternet();
                      }
                      if (nTransportMode == 3) {
                        Net_SetInternet();
                      }
                      SaveDefaults();
                      nShellMode = 0xe;
LAB_0056d20e:
                      Shell_EndDialog(param_1,1);
                      return 1;
                    }
                    pcVar5 = "Error opening transport";
                    pcVar27 = local_204;
                    for (iVar30 = 6; iVar30 != 0; iVar30 = iVar30 + -1) {
                      *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
                      pcVar5 = pcVar5 + 4;
                      pcVar27 = pcVar27 + 4;
                    }
                    memset(&local_1ec,0,0xe8);
                    read_text_label("multi_error","error_open_transport",local_204);
                    do_error(param_1,local_204);
                    pSVar18 = backGround;
                    if ((((nTransportMode != 4) && (nTransportMode != 5)) &&
                        (pSVar18 = backGroundC, nTransportMode != 3)) &&
                       (pSVar18 = backGroundB, nTransportMode == 2)) {
                      pSVar18 = backGroundA;
                    }
                    SetCurrentBackground(param_1,pSVar18);
                    goto LAB_0056cece;
                  }
                  EnableWindow((HWND)param_1,0);
                  pcVar5 = "No transport selected";
                  pcVar27 = local_204;
                  for (iVar30 = 5; iVar30 != 0; iVar30 = iVar30 + -1) {
                    *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
                    pcVar5 = pcVar5 + 4;
                    pcVar27 = pcVar27 + 4;
                  }
                  *(undefined2 *)pcVar27 = *(undefined2 *)pcVar5;
                  memset(local_1ee,0,0xea);
                  pcVar5 = "no_transport";
                }
LAB_0056ceaa:
                read_text_label("multi_error",pcVar5,local_204);
                do_error(param_1,local_204);
                EnableWindow((HWND)param_1,1);
LAB_0056cece:
                if (serverList == (ServerList *)0x0) {
                  return 1;
                }
                serverList->bStop = false;
                return 1;
              }
              EnableWindow((HWND)param_1,0);
              LVar46 = 0;
              WVar14 = 0;
              UVar45 = 0x188;
              pHVar13 = GetDlgItem((HWND)param_1,0x41f);
              WVar14 = SendMessageA(pHVar13,UVar45,WVar14,LVar46);
              if (WVar14 == 0xffffffff) goto LAB_0056c831;
              LVar46 = 0;
              UVar45 = 0x199;
              WVar44 = WVar14;
              pHVar13 = GetDlgItem((HWND)param_1,0x41f);
              LVar9 = SendMessageA(pHVar13,UVar45,WVar44,LVar46);
              if (LVar9 == -1) goto LAB_0056c882;
              iVar30 = 0x20;
              psVar33 = Transport + LVar9;
              pcVar5 = dp_transport.fname;
              net_defaults.TransportIndex = WVar14;
              for (; iVar30 != 0; iVar30 = iVar30 + -1) {
                *(undefined4 *)pcVar5 = *(undefined4 *)(psVar33->dp_transport).fname;
                psVar33 = (sTransport *)((psVar33->dp_transport).fname + 4);
                pcVar5 = pcVar5 + 4;
              }
              pcVar34 = &Transport[LVar9].comm_driverInfo;
              pcVar38 = &comm_driverInfo;
              for (iVar30 = 0xc; iVar30 != 0; iVar30 = iVar30 + -1) {
                *(undefined4 *)pcVar38->signature = *(undefined4 *)pcVar34->signature;
                pcVar34 = (comm_driverInfo_t *)(pcVar34->signature + 4);
                pcVar38 = (comm_driverInfo_t *)(pcVar38->signature + 4);
              }
              *(undefined2 *)pcVar38->signature = *(undefined2 *)pcVar34->signature;
              Net_SetTransport(dp_transport.fname);
              pcVar5 = PlayerNameList::GetName(&playerNameList);
              if (*pcVar5 != '\0') {
                local_2a0._0_4_ = operator_new(0x14);
                if ((PlayerInfo *)local_2a0._0_4_ == (PlayerInfo *)0x0) {
                  playerInfo = (PlayerInfo *)0x0;
                }
                else {
                  pcVar27 = PlayerNameList::GetDescription(&playerNameList);
                  pcVar24 = PlayerNameList::GetURL(&playerNameList);
                  pcVar25 = PlayerNameList::GetEmail(&playerNameList);
                  playerInfo = PlayerInfo::PlayerInfo
                                         ((PlayerInfo *)local_2a0._0_4_,pcVar25,pcVar24,pcVar27);
                }
                pcVar27 = pcVar5;
                do {
                  cVar1 = *pcVar27;
                  pcVar27[(int)player_name - (int)pcVar5] = cVar1;
                  pcVar27 = pcVar27 + 1;
                } while (cVar1 != '\0');
                if (*pcVar5 != '\0') {
                  Net_SetPlayerName(pcVar5);
                }
                iVar30 = 0;
                do {
                  cVar1 = player_name[iVar30];
                  net_defaults.playername[iVar30] = cVar1;
                  iVar30 = iVar30 + 1;
                } while (cVar1 != '\0');
                memset(&params,0,0x2c);
                params.reqLen = 0x2c;
                params.sessionId = Get_TimeNow();
                params.baud = OptionBox::GetCurrentValue(baudRateBox);
                phonenum[0] = '\0';
                params.phonenum = phonenum;
                net_defaults.baud = params.baud;
                params.portnum = OptionBox::GetCurrentValue(comPortBox);
                net_defaults.modemcomport = params.portnum;
                Net_SetParams(&params);
                GetDlgItemTextA((HWND)param_1,0x7d1,pcVar5,4);
                pcVar27 = pcVar5;
                do {
                  cVar1 = *pcVar27;
                  pcVar27[(int)modeministr - (int)pcVar5] = cVar1;
                  pcVar27 = pcVar27 + 1;
                } while (cVar1 != '\0');
                params.modeministr = modeministr;
                iVar30 = 0xc6f7ac - (int)pcVar5;
                do {
                  cVar1 = *pcVar5;
                  pcVar5[iVar30] = cVar1;
                  pcVar5 = pcVar5 + 1;
                } while (cVar1 != '\0');
                SaveDefaults();
                params.dialing_method = 1;
                params.hwirq = 0x3039;
                params.swint = (long)&stopit;
                stopit = 0;
                dpCreateDone = 0;
                h = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,MyThreadFunc,(LPVOID)0x0,0,&dwId);
                Sleep(2000);
                bAnswer = true;
LAB_0056cad0:
                iVar30 = Shell_DialogBoxParam(shell_hInstance,(char *)0x84,shell_hwnd,Modem,0);
                if (iVar30 == 0) goto LAB_0056c882;
                goto LAB_0056d20e;
              }
LAB_0056c902:
              pcVar5 = "No character selected";
              pcVar27 = local_204;
              for (iVar30 = 5; iVar30 != 0; iVar30 = iVar30 + -1) {
                *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
                pcVar5 = pcVar5 + 4;
                pcVar27 = pcVar27 + 4;
              }
              *(undefined2 *)pcVar27 = *(undefined2 *)pcVar5;
              memset(local_1ee,0,0xea);
              pcVar5 = "no_character";
            }
            else {
              EnableWindow((HWND)param_1,0);
              LVar46 = 0;
              WVar14 = 0;
              UVar45 = 0x188;
              pHVar13 = GetDlgItem((HWND)param_1,0x41f);
              WVar14 = SendMessageA(pHVar13,UVar45,WVar14,LVar46);
              if (WVar14 == 0xffffffff) {
LAB_0056c831:
                pcVar5 = "No transport selected";
                pcVar27 = local_204;
                for (iVar30 = 5; iVar30 != 0; iVar30 = iVar30 + -1) {
                  *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
                  pcVar5 = pcVar5 + 4;
                  pcVar27 = pcVar27 + 4;
                }
                *(undefined2 *)pcVar27 = *(undefined2 *)pcVar5;
                memset(local_1ee,0,0xea);
                pcVar5 = "no_transport";
              }
              else {
                LVar46 = 0;
                UVar45 = 0x199;
                WVar44 = WVar14;
                pHVar13 = GetDlgItem((HWND)param_1,0x41f);
                LVar9 = SendMessageA(pHVar13,UVar45,WVar44,LVar46);
                if (LVar9 == -1) goto LAB_0056c882;
                iVar30 = 0x20;
                psVar33 = Transport + LVar9;
                pcVar5 = dp_transport.fname;
                net_defaults.TransportIndex = WVar14;
                for (; iVar30 != 0; iVar30 = iVar30 + -1) {
                  *(undefined4 *)pcVar5 = *(undefined4 *)(psVar33->dp_transport).fname;
                  psVar33 = (sTransport *)((psVar33->dp_transport).fname + 4);
                  pcVar5 = pcVar5 + 4;
                }
                pcVar34 = &Transport[LVar9].comm_driverInfo;
                pcVar38 = &comm_driverInfo;
                for (iVar30 = 0xc; iVar30 != 0; iVar30 = iVar30 + -1) {
                  *(undefined4 *)pcVar38->signature = *(undefined4 *)pcVar34->signature;
                  pcVar34 = (comm_driverInfo_t *)(pcVar34->signature + 4);
                  pcVar38 = (comm_driverInfo_t *)(pcVar38->signature + 4);
                }
                *(undefined2 *)pcVar38->signature = *(undefined2 *)pcVar34->signature;
                Net_SetTransport(dp_transport.fname);
                pcVar5 = PlayerNameList::GetName(&playerNameList);
                pcVar27 = player_name;
                do {
                  cVar1 = *pcVar5;
                  pcVar5 = pcVar5 + 1;
                  *pcVar27 = cVar1;
                  pcVar27 = pcVar27 + 1;
                } while (cVar1 != '\0');
                if (player_name[0] == '\0') goto LAB_0056c902;
                local_2a0._0_4_ = operator_new(0x14);
                if ((PlayerInfo *)local_2a0._0_4_ == (PlayerInfo *)0x0) {
                  playerInfo = (PlayerInfo *)0x0;
                }
                else {
                  pcVar5 = PlayerNameList::GetDescription(&playerNameList);
                  pcVar27 = PlayerNameList::GetURL(&playerNameList);
                  pcVar24 = PlayerNameList::GetEmail(&playerNameList);
                  playerInfo = PlayerInfo::PlayerInfo
                                         ((PlayerInfo *)local_2a0._0_4_,pcVar24,pcVar27,pcVar5);
                }
                Net_SetPlayerName(player_name);
                iVar30 = 0;
                do {
                  cVar1 = player_name[iVar30];
                  net_defaults.playername[iVar30] = cVar1;
                  iVar30 = iVar30 + 1;
                } while (cVar1 != '\0');
                memset(&params,0,0x2c);
                params.reqLen = 0x2c;
                params.sessionId = Get_TimeNow();
                params.baud = OptionBox::GetCurrentValue(baudRateBox);
                net_defaults.baud = params.baud;
                pcVar5 = PhoneNumberList::GetNumber(&phoneNumberList);
                pcVar27 = phonenum;
                do {
                  cVar1 = *pcVar5;
                  pcVar5 = pcVar5 + 1;
                  *pcVar27 = cVar1;
                  pcVar27 = pcVar27 + 1;
                } while (cVar1 != '\0');
                params.phonenum = phonenum;
                if (phonenum[0] != '\0') {
                  params.portnum = OptionBox::GetCurrentValue(comPortBox);
                  net_defaults.modemcomport = params.portnum;
                  Net_SetParams(&params);
                  GetDlgItemTextA((HWND)param_1,0x7d1,modeministr,100);
                  params.modeministr = modeministr;
                  iVar30 = 0;
                  do {
                    cVar1 = modeministr[iVar30];
                    net_defaults.modeminitstring[iVar30] = cVar1;
                    iVar30 = iVar30 + 1;
                  } while (cVar1 != '\0');
                  SaveDefaults();
                  params.dialing_method = 1;
                  params.hwirq = 0x3039;
                  params.swint = (long)&stopit;
                  stopit = 0;
                  dpCreateDone = 0;
                  h = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,MyThreadFunc,(LPVOID)0x0,0,&dwId);
                  Sleep(2000);
                  bAnswer = false;
                  goto LAB_0056cad0;
                }
                pcVar5 = "No phone number selected";
                pcVar27 = local_204;
                for (iVar30 = 6; iVar30 != 0; iVar30 = iVar30 + -1) {
                  *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
                  pcVar5 = pcVar5 + 4;
                  pcVar27 = pcVar27 + 4;
                }
                *pcVar27 = *pcVar5;
                memset(local_1eb,0,0xe7);
                pcVar5 = "no_phone";
              }
            }
            read_text_label("multi_error",pcVar5,local_204);
            do_error(param_1,local_204);
LAB_0056c882:
            EnableWindow((HWND)param_1,1);
            return 1;
          }
          EnableWindow((HWND)param_1,0);
          phoneNumberList.edit = true;
        }
        else {
          EnableWindow((HWND)param_1,0);
          phoneNumberList.edit = false;
        }
        do_phone();
        goto LAB_0056c4a1;
      }
      EnableWindow((HWND)param_1,0);
      PlayerNameList::Delete(&playerNameList);
      PlayerNameList::Save(&playerNameList,"netnam2.txt");
    }
    else {
      EnableWindow((HWND)param_1,0);
      Shell_DialogBoxParam(shell_hInstance,(char *)0x96,shell_hwnd,NameDlgProc,0);
LAB_0056c4a1:
      pSVar18 = backGround;
      if (((nTransportMode != 4) && (nTransportMode != 5)) &&
         ((pSVar18 = backGroundC, nTransportMode != 3 &&
          (pSVar18 = backGroundB, nTransportMode == 2)))) {
        pSVar18 = backGroundA;
      }
      SetCurrentBackground(param_1,pSVar18);
    }
LAB_0056c5b3:
    uVar50 = 1;
LAB_0056ce42:
    (*pcVar36)(param_1,uVar50);
    return 1;
  }
  if (param_2 == 0x113) {
    if (serverList == (ServerList *)0x0) {
      return 1;
    }
    ServerList::Timer(serverList);
    return 1;
  }
  if (param_2 < 0x2c) {
    if (param_2 != 0x2b) {
      if (param_2 == 2) {
        if (serverList != (ServerList *)0x0) {
          (**(code **)serverList->_padding_)(1);
        }
        serverList = (ServerList *)0x0;
        SnapShotBackground();
        CleanCurrentBackground();
        pSVar19 = ulButton;
        if (ulButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(ulButton);
          operator_delete(pSVar19);
        }
        pSVar19 = urButton;
        if (urButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(urButton);
          operator_delete(pSVar19);
        }
        pSVar19 = llButton;
        if (llButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(llButton);
          operator_delete(pSVar19);
        }
        pSVar19 = newCharButton;
        if (newCharButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(newCharButton);
          operator_delete(pSVar19);
        }
        pSVar19 = delCharButton;
        if (delCharButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(delCharButton);
          operator_delete(pSVar19);
        }
        pSVar18 = backGround;
        if (backGround != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGround);
          operator_delete(pSVar18);
        }
        pSVar18 = backGroundA;
        if (backGroundA != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGroundA);
          operator_delete(pSVar18);
        }
        pSVar18 = backGroundB;
        if (backGroundB != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGroundB);
          operator_delete(pSVar18);
        }
        pSVar18 = backGroundC;
        if (backGroundC != (ShellBitmap *)0x0) {
          ShellBitmap::~ShellBitmap(backGroundC);
          operator_delete(pSVar18);
        }
        pTVar20 = charLabel;
        if (charLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(charLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = flagLabel;
        if (flagLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(flagLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = descLabel;
        if (descLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(descLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = mailLabel;
        if (mailLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(mailLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = urlLabel;
        if (urlLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(urlLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = conLabel;
        if (conLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(conLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = phoneLabel;
        if (phoneLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(phoneLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = snLabel;
        if (snLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(snLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = plLabel;
        if (plLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(plLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = msLabel;
        if (msLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(msLabel);
          operator_delete(pTVar20);
        }
        pTVar20 = modemStringLabel;
        if (modemStringLabel != (TextLabel *)0x0) {
          TextLabel::~TextLabel(modemStringLabel);
          operator_delete(pTVar20);
        }
        pSVar19 = newPhoneButton;
        if (newPhoneButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(newPhoneButton);
          operator_delete(pSVar19);
        }
        pSVar19 = editPhoneButton;
        if (editPhoneButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(editPhoneButton);
          operator_delete(pSVar19);
        }
        pSVar19 = delPhoneButton;
        if (delPhoneButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(delPhoneButton);
          operator_delete(pSVar19);
        }
        pSVar19 = dialButton;
        if (dialButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(dialButton);
          operator_delete(pSVar19);
        }
        pSVar19 = answerButton;
        if (answerButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(answerButton);
          operator_delete(pSVar19);
        }
        pSVar19 = flagLeftButton;
        if (flagLeftButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(flagLeftButton);
          operator_delete(pSVar19);
        }
        pSVar19 = flagRightButton;
        if (flagRightButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(flagRightButton);
          operator_delete(pSVar19);
        }
        pSVar19 = charUpButton;
        if (charUpButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(charUpButton);
          operator_delete(pSVar19);
        }
        pSVar19 = charDownButton;
        if (charDownButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(charDownButton);
          operator_delete(pSVar19);
        }
        pSVar19 = phoneUpButton;
        if (phoneUpButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(phoneUpButton);
          operator_delete(pSVar19);
        }
        pSVar19 = phoneDownButton;
        if (phoneDownButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(phoneDownButton);
          operator_delete(pSVar19);
        }
        pSVar19 = serverUpButton;
        if (serverUpButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(serverUpButton);
          operator_delete(pSVar19);
        }
        pSVar19 = serverDownButton;
        if (serverDownButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(serverDownButton);
          operator_delete(pSVar19);
        }
        pSVar19 = comPortButton;
        if (comPortButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(comPortButton);
          operator_delete(pSVar19);
        }
        pSVar19 = baudRateButton;
        if (baudRateButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(baudRateButton);
          operator_delete(pSVar19);
        }
        pOVar21 = comPortBox;
        if (comPortBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(comPortBox);
          operator_delete(pOVar21);
        }
        pOVar21 = baudRateBox;
        if (baudRateBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(baudRateBox);
          operator_delete(pOVar21);
        }
        pSVar19 = nmComPortButton;
        if (nmComPortButton != (ShellButton *)0x0) {
          ShellButton::~ShellButton(nmComPortButton);
          operator_delete(pSVar19);
        }
        pOVar21 = nmComPortBox;
        if (nmComPortBox != (OptionBox *)0x0) {
          OptionBox::~OptionBox(nmComPortBox);
          operator_delete(pOVar21);
        }
        pFVar17 = flagList;
        if (flagList != (FlagList *)0x0) {
          FlagList::~FlagList(flagList);
          operator_delete(pFVar17);
        }
      }
      else {
        if (param_2 != 0xf) {
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
        pHVar2 = BeginPaint((HWND)param_1,&local_244);
        pSVar18 = backGround;
        if (((nTransportMode != 4) && (nTransportMode != 5)) &&
           ((pSVar18 = backGroundC, nTransportMode != 3 &&
            (pSVar18 = backGroundB, nTransportMode == 2)))) {
          pSVar18 = backGroundA;
        }
        ShellBitmap::BltBitmap(pSVar18,(HDC__ *)pHVar2);
        if (flagList->shellBitmap != (ShellBitmap *)0x0) {
          ShellBitmap::BltBitmap(flagList->shellBitmap,(HDC__ *)pHVar2);
        }
        pSVar18 = backGround;
        if (((nTransportMode != 4) && (nTransportMode != 5)) &&
           ((pSVar18 = backGroundC, nTransportMode != 3 &&
            (pSVar18 = backGroundB, nTransportMode == 2)))) {
          pSVar18 = backGroundA;
        }
        SetCurrentBackground(param_1,pSVar18);
        ShellButton::UpdateButton(ulButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(urButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(llButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(newCharButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(delCharButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(comPortButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(baudRateButton,(HDC__ *)pHVar2);
        OptionBox::UpdateOptionBox(comPortBox,(HDC__ *)pHVar2);
        OptionBox::UpdateOptionBox(baudRateBox,(HDC__ *)pHVar2);
        OptionBox::UpdateOptionBox(nmComPortBox,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(nmComPortButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(newPhoneButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(editPhoneButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(delPhoneButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(dialButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(answerButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(flagLeftButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(flagRightButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(charUpButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(charDownButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(phoneUpButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(phoneDownButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(serverUpButton,(HDC__ *)pHVar2);
        ShellButton::UpdateButton(serverDownButton,(HDC__ *)pHVar2);
        TextLabel::DrawLabelText(charLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(flagLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(descLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(mailLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(urlLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(conLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(phoneLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(snLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(plLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(msLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        TextLabel::DrawLabelText(modemStringLabel,(HDC__ *)pHVar2,(char *)0x0,0);
        EndPaint((HWND)param_1,&local_244);
      }
      return 0;
    }
    if (*(int *)(param_4 + 8) == -1) {
      return 0;
    }
    if (1 < *(int *)(param_4 + 0xc) - 1U) {
      return 1;
    }
    pHVar13 = *(HWND *)(param_4 + 0x14);
    pHVar3 = GetDlgItem((HWND)param_1,0x820);
    if (pHVar13 != pHVar3) {
      pHVar13 = *(HWND *)(param_4 + 0x14);
      pHVar3 = GetDlgItem((HWND)param_1,0x7e7);
      if (pHVar13 == pHVar3) {
        LVar9 = SendMessageA(pHVar13,0x199,*(WPARAM *)(param_4 + 8),0);
        local_27c._padding_ = (int)PhoneNumberList::GetNumber(&phoneNumberList,LVar9);
        local_298._4_4_ = PhoneNumberList::GetName(&phoneNumberList,LVar9);
        GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)&local_244);
        local_28c.top = *(int *)(param_4 + 0x20);
        local_28c.bottom = *(int *)(param_4 + 0x28);
        local_28c.left = *(LONG *)(param_4 + 0x1c);
        local_28c.right = *(LONG *)(param_4 + 0x24);
        iVar37 = ((local_28c.top - (int)local_244.hdc) + local_28c.bottom) / 2;
        if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
          local_2a0._4_4_ = (PortData **)0x0;
        }
        else {
          DrawFocusRect(*(HDC *)(param_4 + 0x18),&local_28c);
          local_2a0._4_4_ = (PortData **)0x6400;
        }
        local_2a0._0_4_ = (PortData **)0x0;
        local_298._0_4_ = 0;
        pHVar4 = CreateBrushIndirect((LOGBRUSH *)local_2a0);
        FillRect(*(HDC *)(param_4 + 0x18),&local_28c,pHVar4);
        if (pHVar4 != (HBRUSH)0x0) {
          DeleteObject(pHVar4);
        }
        local_274.top = *(int *)(param_4 + 0x20);
        local_274.bottom = *(int *)(param_4 + 0x28);
        local_274.left = 5;
        local_274.right = 0x73;
        piVar10 = (int *)local_298._4_4_;
        do {
          iVar30 = *piVar10;
          piVar10 = (int *)((int)piVar10 + 1);
        } while ((byte)iVar30 != 0);
        ExtTextOutA(*(HDC *)(param_4 + 0x18),5,iVar37,4,&local_274,(LPCSTR)local_298._4_4_,
                    (int)piVar10 - (int)(local_298._4_4_ + 1),(INT *)0x0);
        pcVar5 = (char *)local_27c._padding_;
        do {
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        iVar30 = (int)pcVar5 - (int)(local_27c._padding_ + 1);
        iVar7 = 0x78;
        pcVar5 = (char *)local_27c._padding_;
      }
      else {
        pHVar13 = *(HWND *)(param_4 + 0x14);
        pHVar3 = GetDlgItem((HWND)param_1,0x7d9);
        if (pHVar13 == pHVar3) {
          SendMessageA(pHVar13,0x189,*(WPARAM *)(param_4 + 8),(LPARAM)local_104);
          GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)&local_244);
          iVar30 = *(int *)(param_4 + 0x20);
          iVar7 = *(int *)(param_4 + 0x28);
          iVar37 = (iVar30 - (int)local_244.hdc) + iVar7;
          if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
            local_274.right = *(LONG *)(param_4 + 0x24);
            local_2a0._0_4_ = (PortData **)0x0;
            local_2a0._4_4_ = (PortData **)0x0;
            local_298._0_4_ = 0;
            local_274.left = *(LONG *)(param_4 + 0x1c);
            local_274.top = iVar30;
            local_274.bottom = iVar7;
            pHVar4 = CreateBrushIndirect((LOGBRUSH *)local_2a0);
            pRVar11 = &local_274;
          }
          else {
            local_28c.right = *(LONG *)(param_4 + 0x24);
            local_28c.left = *(LONG *)(param_4 + 0x1c);
            local_28c.top = iVar30;
            local_28c.bottom = iVar7;
            DrawFocusRect(*(HDC *)(param_4 + 0x18),&local_28c);
            local_2a0._0_4_ = (PortData **)0x0;
            local_2a0._4_4_ = (PortData **)0x6400;
            local_298._0_4_ = 0;
            pHVar4 = CreateBrushIndirect((LOGBRUSH *)local_2a0);
            pRVar11 = &local_28c;
          }
          FillRect(*(HDC *)(param_4 + 0x18),pRVar11,pHVar4);
          if (pHVar4 != (HBRUSH)0x0) {
            DeleteObject(pHVar4);
          }
          pcVar5 = local_104;
          do {
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar1 != '\0');
        }
        else {
          pHVar13 = *(HWND *)(param_4 + 0x14);
          pHVar3 = GetDlgItem((HWND)param_1,0x41f);
          if (pHVar13 != pHVar3) {
            return 1;
          }
          SendMessageA(pHVar13,0x189,*(WPARAM *)(param_4 + 8),(LPARAM)local_104);
          GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)&local_244);
          iVar30 = *(int *)(param_4 + 0x20);
          iVar7 = *(int *)(param_4 + 0x28);
          iVar37 = (iVar30 - (int)local_244.hdc) + iVar7;
          if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
            local_274.right = *(LONG *)(param_4 + 0x24);
            local_2a0._0_4_ = (PortData **)0x0;
            local_2a0._4_4_ = (PortData **)0x0;
            local_298._0_4_ = 0;
            local_274.left = *(LONG *)(param_4 + 0x1c);
            local_274.top = iVar30;
            local_274.bottom = iVar7;
            pHVar4 = CreateBrushIndirect((LOGBRUSH *)local_2a0);
            pRVar11 = &local_274;
          }
          else {
            local_28c.right = *(LONG *)(param_4 + 0x24);
            local_28c.left = *(LONG *)(param_4 + 0x1c);
            local_28c.top = iVar30;
            local_28c.bottom = iVar7;
            DrawFocusRect(*(HDC *)(param_4 + 0x18),&local_28c);
            local_2a0._0_4_ = (PortData **)0x0;
            local_2a0._4_4_ = (PortData **)0x6400;
            local_298._0_4_ = 0;
            pHVar4 = CreateBrushIndirect((LOGBRUSH *)local_2a0);
            pRVar11 = &local_28c;
          }
          FillRect(*(HDC *)(param_4 + 0x18),pRVar11,pHVar4);
          if (pHVar4 != (HBRUSH)0x0) {
            DeleteObject(pHVar4);
          }
          pcVar5 = local_104;
          do {
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar1 != '\0');
        }
        iVar37 = iVar37 / 2;
        iVar30 = (int)pcVar5 - (int)(local_104 + 1);
        pcVar5 = local_104;
        iVar7 = 5;
      }
      TextOutA(*(HDC *)(param_4 + 0x18),iVar7,iVar37,pcVar5,iVar30);
      return 1;
    }
    SendMessageA(pHVar13,0x189,*(WPARAM *)(param_4 + 8),(LPARAM)local_104);
    local_27c._padding_ = (int)strtok(local_104," ");
    if (serverList == (ServerList *)0x0) {
      local_2a4 = (undefined1  [4])strtok((char *)0x0," ");
      local_298._4_4_ = strtok((char *)0x0," ");
    }
    else {
      local_2a4 = (undefined1  [4])ServerList::GetMS(serverList,(char *)local_27c._padding_);
      local_298._4_4_ = ServerList::GetNP(serverList,(char *)local_27c._padding_);
    }
    if ((char *)local_27c._padding_ == (char *)0x0) {
      return 1;
    }
    if (local_2a4 == (undefined1  [4])0x0) {
      return 1;
    }
    if ((PortData **)local_298._4_4_ == (PortData **)0x0) {
      return 1;
    }
    GetTextMetricsA(*(HDC *)(param_4 + 0x18),(LPTEXTMETRICA)&local_244);
    local_28c.top = *(int *)(param_4 + 0x20);
    local_28c.bottom = *(int *)(param_4 + 0x28);
    local_28c.left = *(LONG *)(param_4 + 0x1c);
    local_28c.right = *(LONG *)(param_4 + 0x24);
    iVar30 = ((local_28c.top - (int)local_244.hdc) + local_28c.bottom) / 2;
    if ((*(byte *)(param_4 + 0x10) & 1) == 0) {
      local_2a0._4_4_ = (PortData **)0x0;
    }
    else {
      DrawFocusRect(*(HDC *)(param_4 + 0x18),&local_28c);
      local_2a0._4_4_ = (PortData **)0x6400;
    }
    local_2a0._0_4_ = (PortData **)0x0;
    local_298._0_4_ = 0;
    pHVar4 = CreateBrushIndirect((LOGBRUSH *)local_2a0);
    FillRect(*(HDC *)(param_4 + 0x18),&local_28c,pHVar4);
    if (pHVar4 != (HBRUSH)0x0) {
      DeleteObject(pHVar4);
    }
    local_2a0._0_4_ = GetTextColor(*(HDC *)(param_4 + 0x18));
    pcVar5 = (char *)local_27c._padding_;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    TextOutA(*(HDC *)(param_4 + 0x18),5,iVar30,(LPCSTR)local_27c._padding_,
             (int)pcVar5 - (int)(local_27c._padding_ + 1));
    ppPVar6 = (PortData **)local_298._4_4_;
    do {
      cVar1 = *(char *)ppPVar6;
      ppPVar6 = (PortData **)((int)ppPVar6 + 1);
    } while (cVar1 != '\0');
    TextOutA(*(HDC *)(param_4 + 0x18),0xaf,iVar30,(LPCSTR)local_298._4_4_,
             (int)ppPVar6 - (int)(local_298._4_4_ + 1));
    iVar7 = atoi((char *)local_2a4);
    if (iVar7 < 0x3e9) {
      if (iVar7 < 0x1f5) goto LAB_00569eca;
      color = 0xffff;
    }
    else {
      color = 0xff;
    }
    SetTextColor(*(HDC *)(param_4 + 0x18),color);
LAB_00569eca:
    auVar8 = local_2a4;
    do {
      cVar1 = *(char *)auVar8;
      auVar8 = (undefined1  [4])((int)auVar8 + 1);
    } while (cVar1 != '\0');
    TextOutA(*(HDC *)(param_4 + 0x18),200,iVar30,(LPCSTR)local_2a4,
             (int)auVar8 - (int)((int)local_2a4 + 1));
    SetTextColor(*(HDC *)(param_4 + 0x18),local_2a0._0_4_);
    return 1;
  }
  if (param_2 == 0x2c) {
    *(undefined4 *)(param_4 + 0x10) = 0x10;
    return 1;
  }
  if (param_2 == 0x110) {
    SetFontRecursive(param_1);
    Net::bBroadcastOptimize = false;
    serverList = (ServerList *)0x0;
    init_screen_pos(param_1);
    init_bitmap_dc(param_1);
    nTransportMode = 5;
    pFVar17 = operator_new(0x2c);
    if (pFVar17 == (FlagList *)0x0) {
      flagList = (FlagList *)0x0;
    }
    else {
      flagList = FlagList::FlagList(pFVar17,param_1,0x34,0x47);
    }
    pcVar36 = GetDlgItem_exref;
    BVar49 = 1;
    iVar47 = 0x9c;
    iVar37 = 0x8d;
    iVar7 = 0x41;
    iVar30 = 0x91;
    pHVar13 = GetDlgItem((HWND)param_1,0x7d9);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0xf;
    iVar37 = 0x8f;
    iVar7 = 0x18d;
    iVar30 = 0xa4;
    pHVar13 = GetDlgItem((HWND)param_1,0x7e1);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0xf;
    iVar37 = 0x8f;
    iVar7 = 0x1a2;
    iVar30 = 0xa4;
    pHVar13 = GetDlgItem((HWND)param_1,0x7df);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0x5d;
    iVar37 = 0x105;
    iVar7 = 299;
    iVar30 = 0x2e;
    pHVar13 = GetDlgItem((HWND)param_1,0x429);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0x48;
    iVar37 = 0x102;
    iVar7 = 0x41;
    iVar30 = 0x14e;
    pHVar13 = GetDlgItem((HWND)param_1,0x41f);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0x48;
    iVar37 = 0xed;
    iVar7 = 0xb3;
    iVar30 = 0x14e;
    pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0xe2;
    iVar37 = 0xed;
    iVar7 = 0xc9;
    iVar30 = 0x14e;
    pHVar13 = GetDlgItem((HWND)param_1,0x820);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    BVar49 = 1;
    iVar47 = 0xf;
    iVar37 = 0x79;
    iVar7 = 0x178;
    iVar30 = 0x1d6;
    pHVar13 = GetDlgItem((HWND)param_1,0x7d1);
    MoveWindow(pHVar13,iVar30,iVar7,iVar37,iVar47,BVar49);
    pSVar18 = operator_new(0x20);
    if (pSVar18 == (ShellBitmap *)0x0) {
      backGround = (ShellBitmap *)0x0;
    }
    else {
      backGround = ShellBitmap::ShellBitmap(pSVar18,"bitmap\\multip1.bmp",0,0);
    }
    pSVar18 = operator_new(0x20);
    if (pSVar18 == (ShellBitmap *)0x0) {
      backGroundA = (ShellBitmap *)0x0;
    }
    else {
      backGroundA = ShellBitmap::ShellBitmap(pSVar18,"bitmap\\multip1a.bmp",0,0);
    }
    pSVar18 = operator_new(0x20);
    if (pSVar18 == (ShellBitmap *)0x0) {
      backGroundB = (ShellBitmap *)0x0;
    }
    else {
      backGroundB = ShellBitmap::ShellBitmap(pSVar18,"bitmap\\multip1b.bmp",0,0);
    }
    pSVar18 = operator_new(0x20);
    if (pSVar18 == (ShellBitmap *)0x0) {
      backGroundC = (ShellBitmap *)0x0;
    }
    else {
      backGroundC = ShellBitmap::ShellBitmap(pSVar18,"bitmap\\multip1c.bmp",0,0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      ulButton = (ShellButton *)0x0;
    }
    else {
      ulButton = ShellButton::ShellButton
                           (pSVar19,param_1,shell_hInstance,0x103,0x102,0x104,1,0,0x98,0x22,1,"BACK"
                           );
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      llButton = (ShellButton *)0x0;
    }
    else {
      llButton = ShellButton::ShellButton
                           (pSVar19,param_1,shell_hInstance,199,0xc6,200,1,0x1bd,199,0x22,1,
                            "OPTIONS");
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      urButton = (ShellButton *)0x0;
    }
    else {
      urButton = ShellButton::ShellButton
                           (pSVar19,param_1,shell_hInstance,0xca,0xc9,0xcb,0x1e8,0,0x98,0x22,1,
                            "NEXT");
    }
    ShellButton::SetLabelPos(ulButton,0x2f,4,0x58,0x17);
    ShellButton::SetLabelPos(llButton,0x2f,0x1c6,0x58,0x17);
    ShellButton::SetLabelPos(urButton,0x1fb,4,0x58,0x17);
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      newCharButton = (ShellButton *)0x0;
    }
    else {
      newCharButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0x8e,0xe5,0x52,0x1a,1,"New");
    }
    ShellButton::SetSoundFile(newCharButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      delCharButton = (ShellButton *)0x0;
    }
    else {
      delCharButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0xe3,0xe5,0x52,0x1a,1,"Delete");
    }
    ShellButton::SetSoundFile(delCharButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      newPhoneButton = (ShellButton *)0x0;
    }
    else {
      newPhoneButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0x14b,0x105,0x52,0x1a,1,"New");
    }
    ShellButton::SetSoundFile(newPhoneButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      editPhoneButton = (ShellButton *)0x0;
    }
    else {
      editPhoneButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0x1a5,0x105,0x52,0x1a,1,"Edit");
    }
    ShellButton::SetSoundFile(editPhoneButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      delPhoneButton = (ShellButton *)0x0;
    }
    else {
      delPhoneButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0x200,0x105,0x52,0x1a,1,"Delete"
                     );
    }
    ShellButton::SetSoundFile(delPhoneButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      dialButton = (ShellButton *)0x0;
    }
    else {
      dialButton = ShellButton::ShellButton
                             (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0x164,0x19a,0x52,0x1a,1,
                              "Dial");
    }
    ShellButton::SetSoundFile(dialButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      answerButton = (ShellButton *)0x0;
    }
    else {
      answerButton = ShellButton::ShellButton
                               (pSVar19,param_1,shell_hInstance,0,0x813,0x812,0x1e0,0x19a,0x52,0x1a,
                                1,"Answer");
    }
    ShellButton::SetSoundFile(answerButton,"multion.wav","multiclk.wav");
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      charUpButton = (ShellButton *)0x0;
    }
    else {
      charUpButton = ShellButton::ShellButton
                               (pSVar19,param_1,shell_hInstance,0,0x819,0x7ff,0x121,0xbc,0x13,0x12,0
                                ,(char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      charDownButton = (ShellButton *)0x0;
    }
    else {
      charDownButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x818,0x800,0x121,0xce,0x13,0x12,0,
                      (char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      phoneUpButton = (ShellButton *)0x0;
    }
    else {
      phoneUpButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x819,0x7ff,0x23e,0xda,0x13,0x12,0,
                      (char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      phoneDownButton = (ShellButton *)0x0;
    }
    else {
      phoneDownButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x818,0x800,0x23e,0xec,0x13,0x12,0,
                      (char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      serverUpButton = (ShellButton *)0x0;
    }
    else {
      serverUpButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x819,0x7ff,0x23e,0x189,0x13,0x12,0,
                      (char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      serverDownButton = (ShellButton *)0x0;
    }
    else {
      serverDownButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x818,0x800,0x23e,0x19b,0x13,0x12,0,
                      (char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      flagLeftButton = (ShellButton *)0x0;
    }
    else {
      flagLeftButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x817,0x801,0x5a,0x72,0x12,0x13,0,
                      (char *)0x0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      flagRightButton = (ShellButton *)0x0;
    }
    else {
      flagRightButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x816,0x802,0x6c,0x72,0x12,0x13,0,
                      (char *)0x0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      charLabel = (TextLabel *)0x0;
    }
    else {
      charLabel = TextLabel::TextLabel(pTVar20,param_1,"Characters",0x9d,0x2d,0x89,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      flagLabel = (TextLabel *)0x0;
    }
    else {
      flagLabel = TextLabel::TextLabel(pTVar20,param_1,"Flags",0x39,0x2e,0x36,0xd,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      descLabel = (TextLabel *)0x0;
    }
    else {
      descLabel = TextLabel::TextLabel(pTVar20,param_1,"Player Information",0x3a,0x117,0xec,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      mailLabel = (TextLabel *)0x0;
    }
    else {
      mailLabel = TextLabel::TextLabel(pTVar20,param_1,"E-Mail",0x2e,0x18d,0x71,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      urlLabel = (TextLabel *)0x0;
    }
    else {
      urlLabel = TextLabel::TextLabel(pTVar20,param_1,"Web Page",0x2e,0x1a2,0x71,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      conLabel = (TextLabel *)0x0;
    }
    else {
      conLabel = TextLabel::TextLabel(pTVar20,param_1,"Connection",0x15a,0x2d,0xe8,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      phoneLabel = (TextLabel *)0x0;
    }
    else {
      phoneLabel = TextLabel::TextLabel(pTVar20,param_1,"Phone List",0x15a,0x9f,0xe8,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      snLabel = (TextLabel *)0x0;
    }
    else {
      snLabel = TextLabel::TextLabel(pTVar20,param_1,"Server",0x154,0xb1,0xa0,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      plLabel = (TextLabel *)0x0;
    }
    else {
      plLabel = TextLabel::TextLabel(pTVar20,param_1,"pl",500,0xb1,0x14,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      msLabel = (TextLabel *)0x0;
    }
    else {
      msLabel = TextLabel::TextLabel(pTVar20,param_1,"ms",0x208,0xb1,0x28,0xf,0);
    }
    pTVar20 = operator_new(0x128);
    if (pTVar20 == (TextLabel *)0x0) {
      modemStringLabel = (TextLabel *)0x0;
    }
    else {
      modemStringLabel =
           TextLabel::TextLabel(pTVar20,param_1,"Modem Init String",0x14f,0x178,0x83,0xf,0);
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      comPortButton = (ShellButton *)0x0;
    }
    else {
      comPortButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x811,0x815,0x14c,0x133,0x89,0x15,1,
                      "Comm Port");
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      baudRateButton = (ShellButton *)0x0;
    }
    else {
      baudRateButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x811,0x815,0x14c,0x154,0x89,0x15,1,
                      "Baud Rate");
    }
    pSVar19 = operator_new(0x110);
    if (pSVar19 == (ShellButton *)0x0) {
      nmComPortButton = (ShellButton *)0x0;
    }
    else {
      nmComPortButton =
           ShellButton::ShellButton
                     (pSVar19,param_1,shell_hInstance,0,0x811,0x815,0x14c,0xbb,0x89,0x15,1,
                      "Comm Port");
    }
    pOVar21 = operator_new(0x32ec);
    if (pOVar21 == (OptionBox *)0x0) {
      baudRateBox = (OptionBox *)0x0;
    }
    else {
      baudRateBox = OptionBox::OptionBox(pOVar21,param_1,3,0x1d6,0x156,0x79,0x11);
    }
    OptionBox::LoadItemList(baudRateBox,0,"19200",0x4b00);
    OptionBox::LoadItemList(baudRateBox,1,"38400",0x9600);
    OptionBox::LoadItemList(baudRateBox,2,"57600",0xe100);
    pFVar17 = flagList;
    pHVar13 = GetDlgItem((HWND)param_1,0x429);
    pHVar3 = GetDlgItem((HWND)param_1,0x7df);
    pHVar22 = GetDlgItem((HWND)param_1,0x7e1);
    pHVar23 = GetDlgItem((HWND)param_1,0x7d9);
    PlayerNameList::Load
              (&playerNameList,(HWND__ *)pHVar23,(HWND__ *)pHVar22,(HWND__ *)pHVar3,
               (HWND__ *)pHVar13,pFVar17);
    iVar30 = 1;
    pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
    ShowWindow(pHVar13,iVar30);
    phoneNumberList.hwnd = (HWND__ *)GetDlgItem((HWND)param_1,0x7e7);
    PhoneNumberList::Load(&phoneNumberList,"netpho.txt");
    read_text_label("multi_common","back",ulButton->labelText);
    read_text_label("multi_common","next",urButton->labelText);
    read_text_label("multi_common","options",llButton->labelText);
    read_text_label("multi_common","new",newCharButton->labelText);
    read_text_label("multi_common","delete",delCharButton->labelText);
    read_text_label("multi_common","new",newPhoneButton->labelText);
    read_text_label("multi_common","edit",editPhoneButton->labelText);
    read_text_label("multi_common","delete",delPhoneButton->labelText);
    read_text_label("multi_one","dial",dialButton->labelText);
    read_text_label("multi_one","answer",answerButton->labelText);
    read_text_label("multi_one","description",descLabel->textData);
    read_text_label("multi_one","characters",charLabel->textData);
    read_text_label("multi_one","mail",mailLabel->textData);
    read_text_label("multi_one","url",urlLabel->textData);
    read_text_label("multi_one","connection",conLabel->textData);
    read_text_label("multi_one","phone_list",phoneLabel->textData);
    read_text_label("multi_one","flags",flagLabel->textData);
    read_text_label("multi_one","modem_init",modemStringLabel->textData);
    read_text_label("multi_one","comm_port",comPortButton->labelText);
    read_text_label("multi_one","baud_rate",baudRateButton->labelText);
    read_text_label("multi_one","comm_port",nmComPortButton->labelText);
    read_text_label("multi_one","sn",snLabel->textData);
    read_text_label("multi_one","pl",plLabel->textData);
    read_text_label("multi_one","ms",msLabel->textData);
    LoadDefaults();
    pcVar5 = Net::hostname;
    do {
      pcVar27 = pcVar5;
      pcVar5 = pcVar27 + 1;
    } while (*pcVar27 != '\0');
    iVar30 = 0;
    if (pcVar27 == Net::hostname) {
      do {
        cVar1 = net_defaults.server[iVar30];
        Net::hostname[iVar30] = cVar1;
        iVar30 = iVar30 + 1;
      } while (cVar1 != '\0');
    }
    OptionBox::SetCurrentValue(baudRateBox,net_defaults.baud);
    pcVar5 = net_defaults.modeminitstring;
    pHVar13 = GetDlgItem((HWND)param_1,0x7d1);
    SetWindowTextA(pHVar13,pcVar5);
    lParam = &net_defaults;
    WVar14 = 0xffffffff;
    UVar45 = 0x18c;
    pHVar13 = GetDlgItem((HWND)param_1,0x7d9);
    SendMessageA(pHVar13,UVar45,WVar14,(LPARAM)lParam);
    PlayerNameList::SelectionChanged(&playerNameList);
    Net::Team = 1;
    builtin_strncpy(local_104,"dll",4);
    iTransportCount = 0;
    pHVar13 = GetDlgItem((HWND)param_1,0x41f);
    dpEnumTransports(local_104,dpEnumTransportCallback,pHVar13);
    if ((int)modem_portlist._Mylast - (int)modem_portlist._Myfirst >> 2 == 0) {
      pOVar21 = operator_new(0x32ec);
      if (pOVar21 == (OptionBox *)0x0) {
        comPortBox = (OptionBox *)0x0;
      }
      else {
        comPortBox = OptionBox::OptionBox(pOVar21,param_1,4,0x1d6,0x135,0x79,0x11);
      }
      OptionBox::LoadItemList(comPortBox,0,"COM1",0);
      OptionBox::LoadItemList(comPortBox,1,"COM2",1);
      OptionBox::LoadItemList(comPortBox,2,"COM3",2);
      OptionBox::LoadItemList(comPortBox,3,"COM4",3);
    }
    else {
      pOVar21 = operator_new(0x32ec);
      if (pOVar21 == (OptionBox *)0x0) {
        comPortBox = (OptionBox *)0x0;
      }
      else {
        comPortBox = OptionBox::OptionBox
                               (pOVar21,param_1,
                                (int)modem_portlist._Mylast - (int)modem_portlist._Myfirst >> 2,
                                0x1d6,0x135,0x79,0x11);
      }
      local_2a4 = (undefined1  [4])0x0;
      std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
      _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)(local_298 + 4),
                 modem_portlist._Mylast,(_Container_base_aux *)&modem_portlist);
      std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
      _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)local_2a0,
                 modem_portlist._Myfirst,(_Container_base_aux *)&modem_portlist);
      while( true ) {
        _Var42 = std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator+
                           ((_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *)
                            (local_2a0 + 4),(int)auStack_260);
        bVar40 = std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator==
                           (_Var42._0_4_,
                            (_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)
                            (local_298 + 4));
        if (bVar40) break;
        std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
        _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                  (&local_27c,modem_portlist._Myfirst,(_Container_base_aux *)&modem_portlist);
        _Var42 = std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator+
                           ((_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *)&local_27c,
                            (int)auStack_254);
        ppPVar6 = std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator*
                            (_Var42._0_4_);
        OptionBox::LoadItemList(comPortBox,unaff_EBX,(*ppPVar6)->name,(*ppPVar6)->comport);
        unaff_EBX = unaff_EBX + 1;
        std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
        _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                  ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)local_298,
                   modem_portlist._Mylast,(_Container_base_aux *)&modem_portlist);
        std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
        _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                  ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)local_2a4,
                   modem_portlist._Myfirst,(_Container_base_aux *)&modem_portlist);
      }
    }
    if ((uint)net_defaults.modemcomport <
        (uint)((int)modem_portlist._Mylast - (int)modem_portlist._Myfirst >> 2)) {
      OptionBox::SetCurrentValue(comPortBox,net_defaults.modemcomport);
    }
    while (((int)modem_portlist._Mylast - (int)modem_portlist._Myfirst & 0xfffffffcU) != 0) {
      ppPVar6 = std::vector<PortData_*,std::allocator<PortData_*>_>::back(&modem_portlist);
      if (*ppPVar6 != (PortData *)0x0) {
        PortData::_scalar_deleting_destructor_(*ppPVar6,1);
      }
      std::vector<PortData_*,std::allocator<PortData_*>_>::pop_back(&modem_portlist);
    }
    if ((int)nullmodem_portlist._Mylast - (int)nullmodem_portlist._Myfirst >> 2 == 0) {
      pOVar21 = operator_new(0x32ec);
      if (pOVar21 == (OptionBox *)0x0) {
        nmComPortBox = (OptionBox *)0x0;
      }
      else {
        nmComPortBox = OptionBox::OptionBox(pOVar21,param_1,4,0x1d6,0xbd,0x79,0x11);
      }
      OptionBox::LoadItemList(nmComPortBox,0,"COM1",0);
      OptionBox::LoadItemList(nmComPortBox,1,"COM2",1);
      OptionBox::LoadItemList(nmComPortBox,2,"COM3",2);
      OptionBox::LoadItemList(nmComPortBox,3,"COM4",3);
    }
    else {
      pOVar21 = operator_new(0x32ec);
      if (pOVar21 == (OptionBox *)0x0) {
        nmComPortBox = (OptionBox *)0x0;
      }
      else {
        nmComPortBox = OptionBox::OptionBox
                                 (pOVar21,param_1,
                                  (int)nullmodem_portlist._Mylast - (int)nullmodem_portlist._Myfirst
                                  >> 2,0x1d6,0xbd,0x79,0x11);
      }
      local_2a4 = (undefined1  [4])0x0;
      std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
      _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)(local_298 + 4),
                 nullmodem_portlist._Mylast,(_Container_base_aux *)&nullmodem_portlist);
      std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
      _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)local_2a0,
                 nullmodem_portlist._Myfirst,(_Container_base_aux *)&nullmodem_portlist);
      while( true ) {
        _Var42 = std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator+
                           ((_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *)
                            (local_2a0 + 4),(int)local_258);
        bVar40 = std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator==
                           (_Var42._0_4_,
                            (_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)
                            (local_298 + 4));
        if (bVar40) break;
        std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
        _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                  (&local_27c,nullmodem_portlist._Myfirst,(_Container_base_aux *)&nullmodem_portlist
                  );
        _Var42 = std::_Vector_iterator<PortData_*,std::allocator<PortData_*>_>::operator+
                           ((_Vector_iterator<PortData_*,std::allocator<PortData_*>_> *)&local_27c,
                            (int)auStack_24c);
        ppPVar6 = std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::operator*
                            (_Var42._0_4_);
        OptionBox::LoadItemList(nmComPortBox,unaff_EBX,(*ppPVar6)->name,(*ppPVar6)->comport);
        unaff_EBX = unaff_EBX + 1;
        std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
        _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                  ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)local_298,
                   nullmodem_portlist._Mylast,(_Container_base_aux *)&nullmodem_portlist);
        std::_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>::
        _Vector_const_iterator<PortData_*,std::allocator<PortData_*>_>
                  ((_Vector_const_iterator<PortData_*,std::allocator<PortData_*>_> *)local_2a4,
                   nullmodem_portlist._Myfirst,(_Container_base_aux *)&nullmodem_portlist);
      }
    }
    if ((uint)net_defaults.serialcomport <
        (uint)((int)nullmodem_portlist._Mylast - (int)nullmodem_portlist._Myfirst >> 2)) {
      OptionBox::SetCurrentValue(nmComPortBox,net_defaults.serialcomport);
    }
    while (((int)nullmodem_portlist._Mylast - (int)nullmodem_portlist._Myfirst & 0xfffffffcU) != 0)
    {
      ppPVar6 = std::vector<PortData_*,std::allocator<PortData_*>_>::back(&nullmodem_portlist);
      if (*ppPVar6 != (PortData *)0x0) {
        PortData::_scalar_deleting_destructor_(*ppPVar6,1);
      }
      std::vector<PortData_*,std::allocator<PortData_*>_>::pop_back(&nullmodem_portlist);
    }
    while( true ) {
      lParam_00 = 0;
      LVar46 = 0x186;
      WVar44 = 0x41f;
      pHVar43 = param_1;
      WVar14 = net_defaults.TransportIndex;
      pHVar13 = (HWND)(*pcVar36)();
      SendMessageA(pHVar13,(UINT)pHVar43,WVar44,LVar46);
      UVar45 = 0;
      pHVar13 = (HWND)(*pcVar36)(param_1,0x41f,0x199,net_defaults.TransportIndex);
      local_298._4_4_ = SendMessageA(pHVar13,UVar45,WVar14,lParam_00);
      if ((int *)local_298._4_4_ == (int *)0xffffffff) break;
      ShellButton::HideButton(serverUpButton,0);
      ShellButton::HideButton(serverDownButton,0);
      iVar30 = 6;
      bVar40 = false;
      iVar7 = 0;
      bVar41 = true;
      pcVar5 = Transport[local_298._4_4_].comm_driverInfo.name;
      pbVar39 = (byte *)"Modem";
      do {
        if (iVar30 == 0) break;
        iVar30 = iVar30 + -1;
        bVar40 = (byte)*pcVar5 < *pbVar39;
        bVar41 = *pcVar5 == *pbVar39;
        pcVar5 = pcVar5 + 1;
        pbVar39 = pbVar39 + 1;
      } while (bVar41);
      if (!bVar41) {
        iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
      }
      if (iVar7 == 0) {
        nTransportMode = 1;
        ShellButton::HideButton(urButton,0);
        ShellButton::HideButton(nmComPortButton,0);
        OptionBox::HideBox(nmComPortBox,0);
        TextLabel::HideLabelText(snLabel,1);
        TextLabel::HideLabelText(plLabel,1);
        TextLabel::HideLabelText(msLabel,1);
        SetCurrentBackground(param_1,backGroundB);
        iVar30 = 0;
        pHVar13 = GetDlgItem((HWND)param_1,0x820);
        ShowWindow(pHVar13,iVar30);
        break;
      }
      iVar30 = 0xb;
      bVar40 = false;
      iVar7 = 0;
      bVar41 = true;
      pcVar5 = Transport[local_298._4_4_].comm_driverInfo.name;
      pbVar39 = (byte *)"Null Modem";
      do {
        if (iVar30 == 0) break;
        iVar30 = iVar30 + -1;
        bVar40 = (byte)*pcVar5 < *pbVar39;
        bVar41 = *pcVar5 == *pbVar39;
        pcVar5 = pcVar5 + 1;
        pbVar39 = pbVar39 + 1;
      } while (bVar41);
      if (!bVar41) {
        iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
      }
      if (iVar7 == 0) {
        nTransportMode = 2;
        TextLabel::HideLabelText(phoneLabel,1);
        iVar30 = 0;
        pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
        ShowWindow(pHVar13,iVar30);
        iVar30 = 0;
        pHVar13 = GetDlgItem((HWND)param_1,0x820);
        ShowWindow(pHVar13,iVar30);
        ShellButton::HideButton(newPhoneButton,0);
        ShellButton::HideButton(editPhoneButton,0);
        ShellButton::HideButton(delPhoneButton,0);
        TextLabel::HideLabelText(modemStringLabel,1);
        TextLabel::HideLabelText(snLabel,1);
        TextLabel::HideLabelText(plLabel,1);
        TextLabel::HideLabelText(msLabel,1);
        iVar30 = 0;
        pHVar13 = GetDlgItem((HWND)param_1,0x7d1);
        ShowWindow(pHVar13,iVar30);
        ShellButton::HideButton(dialButton,0);
        ShellButton::HideButton(answerButton,0);
        ShellButton::HideButton(phoneUpButton,0);
        ShellButton::HideButton(phoneDownButton,0);
        ShellButton::HideButton(comPortButton,0);
        ShellButton::HideButton(baudRateButton,0);
        OptionBox::HideBox(comPortBox,0);
        OptionBox::HideBox(baudRateBox,0);
        SetCurrentBackground(param_1,backGroundA);
        ShellButton::ShowButton(nmComPortButton,0);
        OptionBox::ShowBox(nmComPortBox,0);
        break;
      }
      iVar30 = 9;
      bVar40 = false;
      iVar7 = 0;
      bVar41 = true;
      pcVar5 = Transport[local_298._4_4_].comm_driverInfo.name;
      pbVar39 = (byte *)"Internet";
      do {
        if (iVar30 == 0) break;
        iVar30 = iVar30 + -1;
        bVar40 = (byte)*pcVar5 < *pbVar39;
        bVar41 = *pcVar5 == *pbVar39;
        pcVar5 = pcVar5 + 1;
        pbVar39 = pbVar39 + 1;
      } while (bVar41);
      if (!bVar41) {
        iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
      }
      if (iVar7 != 0) {
        pcVar5 = Transport[local_298._4_4_].comm_driverInfo.name;
        iVar30 = 4;
        bVar40 = false;
        iVar7 = 0;
        bVar41 = true;
        pcVar27 = pcVar5;
        pbVar39 = &s_IPX;
        goto code_r0x0056c264;
      }
      iVar30 = 0x20;
      psVar33 = Transport + local_298._4_4_;
      pcVar5 = dp_transport.fname;
      for (; iVar30 != 0; iVar30 = iVar30 + -1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)(psVar33->dp_transport).fname;
        psVar33 = (sTransport *)((psVar33->dp_transport).fname + 4);
        pcVar5 = pcVar5 + 4;
      }
      pcVar34 = &Transport[local_298._4_4_].comm_driverInfo;
      pcVar38 = &comm_driverInfo;
      for (iVar30 = 0xc; iVar30 != 0; iVar30 = iVar30 + -1) {
        *(undefined4 *)pcVar38->signature = *(undefined4 *)pcVar34->signature;
        pcVar34 = (comm_driverInfo_t *)(pcVar34->signature + 4);
        pcVar38 = (comm_driverInfo_t *)(pcVar38->signature + 4);
      }
      *(undefined2 *)pcVar38->signature = *(undefined2 *)pcVar34->signature;
      Net_SetTransport(dp_transport.fname);
      PreInternetDpCreate();
      iVar30 = dpCreate(&Net::dp,&dp_transport,&params,0);
      PostInternetDpCreate();
      if (iVar30 == 0) {
        pSVar29 = operator_new(100);
        if (pSVar29 == (ServerList *)0x0) {
          serverList = (ServerList *)0x0;
        }
        else {
          pdVar48 = Net::dp;
          pHVar43 = param_1;
          pHVar13 = GetDlgItem((HWND)param_1,0x820);
          serverList = ServerList::ServerList(pSVar29,(HWND__ *)pHVar13,pdVar48,pHVar43);
        }
        nTransportMode = 3;
        TextLabel::SetLabelText(phoneLabel,"Servers");
        read_text_label("multi_one","server_list",phoneLabel->textData);
        TextLabel::ShowLabelText(phoneLabel,1);
        TextLabel::ShowLabelText(snLabel,1);
        TextLabel::ShowLabelText(plLabel,1);
        TextLabel::ShowLabelText(msLabel,1);
        iVar30 = 0;
        pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
        ShowWindow(pHVar13,iVar30);
        ShellButton::HideButton(newPhoneButton,0);
        ShellButton::HideButton(editPhoneButton,0);
        ShellButton::HideButton(delPhoneButton,0);
        TextLabel::HideLabelText(modemStringLabel,1);
        iVar30 = 0;
        pHVar13 = GetDlgItem((HWND)param_1,0x7d1);
        ShowWindow(pHVar13,iVar30);
        iVar30 = 1;
        pHVar13 = GetDlgItem((HWND)param_1,0x820);
        ShowWindow(pHVar13,iVar30);
        ShellButton::HideButton(dialButton,0);
        ShellButton::HideButton(answerButton,0);
        OptionBox::HideBox(comPortBox,0);
        OptionBox::HideBox(baudRateBox,0);
        ShellButton::HideButton(comPortButton,0);
        ShellButton::HideButton(baudRateButton,0);
        ShellButton::HideButton(phoneUpButton,0);
        ShellButton::HideButton(phoneDownButton,0);
        ShellButton::ShowButton(serverUpButton,0);
        ShellButton::ShowButton(serverDownButton,0);
        ShellButton::HideButton(nmComPortButton,0);
        OptionBox::HideBox(nmComPortBox,0);
        pSVar18 = backGroundC;
        goto LAB_0056c3b6;
      }
      pcVar5 = "Could not open internet transport";
      pcVar27 = local_204;
      for (iVar30 = 8; iVar30 != 0; iVar30 = iVar30 + -1) {
        *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar27 = pcVar27 + 4;
      }
      *(undefined2 *)pcVar27 = *(undefined2 *)pcVar5;
      memset(local_1e2,0,0xde);
      read_text_label("multi_error","cannot_open_internet",local_204);
      do_error(param_1,local_204);
      net_defaults.TransportIndex = (int)(net_defaults.TransportIndex == 0);
      Net::dp = (dp_s *)0x0;
      pcVar36 = GetDlgItem_exref;
    }
    goto LAB_0056c3be;
  }
  if (param_2 != 0x111) {
    return 0;
  }
  uVar12 = param_3 & 0xffff;
  if (uVar12 != 0x41f) {
    sVar28 = (short)(param_3 >> 0x10);
    if (uVar12 == 0x429) {
      if (sVar28 != 0x300) {
        return 1;
      }
      iVar30 = 2;
LAB_0056a2c8:
      PlayerNameList::Changed(&playerNameList,iVar30);
      return 1;
    }
    if (uVar12 == 0x7d9) {
      if (param_3 >> 0x10 != 1) {
        return 1;
      }
      PlayerNameList::SelectionChanged(&playerNameList);
      return 1;
    }
    if (uVar12 == 0x7df) {
      if (sVar28 != 0x300) {
        return 1;
      }
      iVar30 = 1;
      goto LAB_0056a2c8;
    }
    if (uVar12 == 0x7e1) {
      if (sVar28 != 0x300) {
        return 1;
      }
      iVar30 = 0;
      goto LAB_0056a2c8;
    }
    if (uVar12 != 0x7e7) {
      if (uVar12 != 0x820) {
        return 0;
      }
      if (serverList == (ServerList *)0x0) {
        return 0;
      }
      ServerList::Redraw(serverList);
      return 0;
    }
    if (param_3 >> 0x10 != 1) {
      return 1;
    }
    BVar49 = 1;
    pRVar11 = (RECT *)0x0;
    param_1 = phoneNumberList.hwnd;
    goto LAB_0056a2aa;
  }
  pSVar29 = (ServerList *)((param_3 >> 0x10) - 1);
  if (pSVar29 != (ServerList *)0x0) {
    return 1;
  }
  BVar49 = 1;
  pSVar16 = pSVar29;
  pHVar13 = GetDlgItem((HWND)param_1,0x41f);
  InvalidateRect(pHVar13,(RECT *)pSVar16,BVar49);
  UVar45 = 0x188;
  pSVar16 = pSVar29;
  pSVar15 = pSVar29;
  pHVar13 = GetDlgItem((HWND)param_1,0x41f);
  WVar14 = SendMessageA(pHVar13,UVar45,(WPARAM)pSVar16,(LPARAM)pSVar15);
  if (WVar14 == 0xffffffff) {
    return 1;
  }
  UVar45 = 0x199;
  pSVar16 = pSVar29;
  pHVar13 = GetDlgItem((HWND)param_1,0x41f);
  LVar9 = SendMessageA(pHVar13,UVar45,WVar14,(LPARAM)pSVar16);
  if (LVar9 == -1) {
    return 1;
  }
  ShellButton::HideButton(serverUpButton,0);
  ShellButton::HideButton(serverDownButton,0);
  local_2a0._0_4_ = LVar9 * 0xb2;
  local_298._4_4_ = &((PlayerInfo *)(local_2a0._0_4_ + 0xc6e6fc))->itype;
  iVar30 = 9;
  bVar40 = false;
  iVar7 = 0;
  bVar41 = true;
  piVar10 = (int *)local_298._4_4_;
  pbVar39 = (byte *)"Internet";
  do {
    if (iVar30 == 0) break;
    iVar30 = iVar30 + -1;
    bVar40 = (byte)*piVar10 < *pbVar39;
    bVar41 = (byte)*piVar10 == *pbVar39;
    piVar10 = (int *)((int)piVar10 + 1);
    pbVar39 = pbVar39 + 1;
  } while (bVar41);
  if (!bVar41) {
    iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
  }
  if (iVar7 == 0) {
    ShellButton::ShowButton(urButton,0);
    InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
    InvalidateRect((HWND)param_1,(RECT *)&urButton->labelRect,0);
    pSVar16 = serverList;
    if (Net::dp == (dp_s *)0x0) {
      iVar30 = 0x20;
      piVar10 = &((PlayerInfo *)(local_2a0._0_4_ + 0xc6e670))->itype;
      pcVar5 = dp_transport.fname;
      for (; iVar30 != 0; iVar30 = iVar30 + -1) {
        *(int *)pcVar5 = *piVar10;
        piVar10 = piVar10 + 1;
        pcVar5 = pcVar5 + 4;
      }
      ppcVar31 = &((PlayerInfo *)(local_2a0._0_4_ + 0xc6e6fc))->email;
      pcVar34 = &comm_driverInfo;
      for (iVar30 = 0xc; iVar30 != 0; iVar30 = iVar30 + -1) {
        *(char **)pcVar34->signature = *ppcVar31;
        ppcVar31 = ppcVar31 + 1;
        pcVar34 = (comm_driverInfo_t *)(pcVar34->signature + 4);
      }
      *(undefined2 *)pcVar34->signature = *(undefined2 *)ppcVar31;
      Net_SetTransport(dp_transport.fname);
      memset(&params,0,0x2c);
      params.reqLen = 0x2c;
      params.portnum =
           GetPrivateProfileIntA("Net","ConnectPortInternet",params.portnum,".\\net.ini");
      Net_SetParams(&params);
      PreInternetDpCreate();
      iVar30 = dpCreate(&Net::dp,&dp_transport,&params,0);
      PostInternetDpCreate();
      if (iVar30 == 0) {
        if (serverList != (ServerList *)0x0) {
          (**(code **)serverList->_padding_)(1);
        }
        pSVar15 = operator_new(100);
        pSVar16 = pSVar29;
        if (pSVar15 != (ServerList *)0x0) {
          pdVar48 = Net::dp;
          pHVar43 = param_1;
          pHVar13 = GetDlgItem((HWND)param_1,0x820);
          pSVar16 = ServerList::ServerList(pSVar15,(HWND__ *)pHVar13,pdVar48,pHVar43);
        }
      }
      else {
        pcVar5 = "You are not connected to the internet";
        pcVar27 = local_104;
        for (iVar30 = 9; iVar30 != 0; iVar30 = iVar30 + -1) {
          *(undefined4 *)pcVar27 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          pcVar27 = pcVar27 + 4;
        }
        *(undefined2 *)pcVar27 = *(undefined2 *)pcVar5;
        memset(local_de,0,0xda);
        read_text_label("multi_error","no_internet",local_104);
        do_error(param_1,local_104);
        Net::dp = (dp_s *)0x0;
        pSVar16 = serverList;
      }
    }
    serverList = pSVar16;
    nTransportMode = 3;
    SetCurrentBackground(param_1,backGroundC);
    TextLabel::SetLabelText(phoneLabel,"Servers");
    read_text_label("multi_one","server_list",phoneLabel->textData);
    TextLabel::ShowLabelText(phoneLabel,0);
    TextLabel::ShowLabelText(snLabel,0);
    TextLabel::ShowLabelText(plLabel,0);
    TextLabel::ShowLabelText(msLabel,0);
    ShellButton::HideButton(newPhoneButton,0);
    ShellButton::HideButton(editPhoneButton,0);
    ShellButton::HideButton(delPhoneButton,0);
    TextLabel::HideLabelText(modemStringLabel,0);
    ShellButton::HideButton(dialButton,0);
    ShellButton::HideButton(answerButton,0);
    OptionBox::HideBox(comPortBox,0);
    OptionBox::HideBox(baudRateBox,0);
    ShellButton::HideButton(comPortButton,0);
    ShellButton::HideButton(baudRateButton,0);
    ShellButton::HideButton(phoneUpButton,0);
    ShellButton::HideButton(phoneDownButton,0);
    ShellButton::ShowButton(serverUpButton,0);
    ShellButton::ShowButton(serverDownButton,0);
    ShellButton::HideButton(nmComPortButton,0);
    OptionBox::HideBox(nmComPortBox,0);
    ShellButton::ShowButton(urButton,0);
    InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
    pcVar36 = GetDlgItem_exref;
    pSVar16 = pSVar29;
    pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
    pcVar32 = ShowWindow_exref;
    ShowWindow(pHVar13,(int)pSVar16);
    pHVar13 = GetDlgItem((HWND)param_1,0x7d1);
    ShowWindow(pHVar13,(int)pSVar29);
    uVar50 = 1;
LAB_0056abb3:
    uVar50 = (*pcVar36)(param_1,0x820,uVar50);
    (*pcVar32)(uVar50);
  }
  else {
    if (serverList != (ServerList *)0x0) {
      (**(code **)serverList->_padding_)(1);
    }
    serverList = pSVar29;
    if (Net::dp != (dp_s *)0x0) {
      Net::Close();
      dpDestroy(Net::dp,0);
      Net::dp = (dp_s *)0x0;
    }
    iVar30 = 6;
    bVar40 = false;
    iVar7 = 0;
    bVar41 = true;
    piVar10 = (int *)local_298._4_4_;
    pbVar39 = (byte *)"Modem";
    do {
      if (iVar30 == 0) break;
      iVar30 = iVar30 + -1;
      bVar40 = (byte)*piVar10 < *pbVar39;
      bVar41 = (byte)*piVar10 == *pbVar39;
      piVar10 = (int *)((int)piVar10 + 1);
      pbVar39 = pbVar39 + 1;
    } while (bVar41);
    if (!bVar41) {
      iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
    }
    if (iVar7 == 0) {
      ShellButton::HideButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->labelRect,0);
      nTransportMode = 1;
      SetCurrentBackground(param_1,backGroundB);
      TextLabel::SetLabelText(phoneLabel,"Phone List");
      read_text_label("multi_one","phone_list",phoneLabel->textData);
      TextLabel::ShowLabelText(phoneLabel,0);
      TextLabel::HideLabelText(snLabel,0);
      TextLabel::HideLabelText(plLabel,0);
      TextLabel::HideLabelText(msLabel,0);
      ShellButton::ShowButton(newPhoneButton,0);
      ShellButton::ShowButton(editPhoneButton,0);
      ShellButton::ShowButton(delPhoneButton,0);
      TextLabel::ShowLabelText(modemStringLabel,0);
      ShellButton::ShowButton(dialButton,0);
      ShellButton::ShowButton(answerButton,0);
      OptionBox::ShowBox(comPortBox,0);
      OptionBox::ShowBox(baudRateBox,0);
      ShellButton::ShowButton(comPortButton,0);
      ShellButton::ShowButton(baudRateButton,0);
      ShellButton::ShowButton(phoneUpButton,0);
      ShellButton::ShowButton(phoneDownButton,0);
      ShellButton::HideButton(nmComPortButton,0);
      OptionBox::HideBox(nmComPortBox,0);
      ShellButton::HideButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      pcVar36 = GetDlgItem_exref;
      iVar30 = 1;
      pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
      pcVar32 = ShowWindow_exref;
      ShowWindow(pHVar13,iVar30);
      uVar50 = 1;
LAB_0056aba7:
      uVar50 = (*pcVar36)(param_1,0x7d1,uVar50);
      (*pcVar32)(uVar50);
      uVar50 = 0;
      goto LAB_0056abb3;
    }
    iVar30 = 0xb;
    bVar40 = false;
    iVar7 = 0;
    bVar41 = true;
    piVar10 = (int *)local_298._4_4_;
    pbVar39 = (byte *)"Null Modem";
    do {
      if (iVar30 == 0) break;
      iVar30 = iVar30 + -1;
      bVar40 = (byte)*piVar10 < *pbVar39;
      bVar41 = (byte)*piVar10 == *pbVar39;
      piVar10 = (int *)((int)piVar10 + 1);
      pbVar39 = pbVar39 + 1;
    } while (bVar41);
    if (!bVar41) {
      iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
    }
    if (iVar7 == 0) {
      ShellButton::ShowButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->labelRect,0);
      nTransportMode = 2;
      SetCurrentBackground(param_1,backGroundA);
      TextLabel::HideLabelText(phoneLabel,0);
      TextLabel::HideLabelText(snLabel,0);
      TextLabel::HideLabelText(plLabel,0);
      TextLabel::HideLabelText(msLabel,0);
      ShellButton::HideButton(newPhoneButton,0);
      ShellButton::HideButton(editPhoneButton,0);
      ShellButton::HideButton(delPhoneButton,0);
      TextLabel::HideLabelText(modemStringLabel,0);
      ShellButton::HideButton(dialButton,0);
      ShellButton::HideButton(answerButton,0);
      OptionBox::HideBox(comPortBox,0);
      OptionBox::HideBox(baudRateBox,0);
      ShellButton::HideButton(comPortButton,0);
      ShellButton::HideButton(baudRateButton,0);
      ShellButton::HideButton(phoneUpButton,0);
      ShellButton::HideButton(phoneDownButton,0);
      ShellButton::ShowButton(nmComPortButton,0);
      OptionBox::ShowBox(nmComPortBox,0);
      ShellButton::ShowButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      pcVar36 = GetDlgItem_exref;
      pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
      pcVar32 = ShowWindow_exref;
LAB_0056aba3:
      (*pcVar32)(pHVar13,pSVar29);
      uVar50 = 0;
      goto LAB_0056aba7;
    }
    iVar30 = 4;
    bVar40 = false;
    iVar7 = 0;
    bVar41 = true;
    piVar10 = (int *)local_298._4_4_;
    pbVar39 = &s_IPX;
    do {
      if (iVar30 == 0) break;
      iVar30 = iVar30 + -1;
      bVar40 = (byte)*piVar10 < *pbVar39;
      bVar41 = (byte)*piVar10 == *pbVar39;
      piVar10 = (int *)((int)piVar10 + 1);
      pbVar39 = pbVar39 + 1;
    } while (bVar41);
    if (!bVar41) {
      iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
    }
    if (iVar7 == 0) {
      ShellButton::ShowButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->labelRect,0);
      nTransportMode = 4;
LAB_0056aa7f:
      SetCurrentBackground(param_1,backGround);
      TextLabel::HideLabelText(phoneLabel,0);
      TextLabel::HideLabelText(snLabel,0);
      TextLabel::HideLabelText(plLabel,0);
      TextLabel::HideLabelText(msLabel,0);
      pcVar36 = GetDlgItem_exref;
      pSVar16 = pSVar29;
      pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
      pcVar32 = ShowWindow_exref;
      ShowWindow(pHVar13,(int)pSVar16);
      ShellButton::HideButton(newPhoneButton,0);
      ShellButton::HideButton(editPhoneButton,0);
      ShellButton::HideButton(delPhoneButton,0);
      TextLabel::HideLabelText(modemStringLabel,0);
      ShellButton::HideButton(dialButton,0);
      ShellButton::HideButton(answerButton,0);
      OptionBox::HideBox(comPortBox,0);
      OptionBox::HideBox(baudRateBox,0);
      ShellButton::HideButton(comPortButton,0);
      ShellButton::HideButton(baudRateButton,0);
      ShellButton::HideButton(phoneUpButton,0);
      ShellButton::HideButton(phoneDownButton,0);
      ShellButton::HideButton(nmComPortButton,0);
      OptionBox::HideBox(nmComPortBox,0);
      ShellButton::ShowButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
      goto LAB_0056aba3;
    }
    iVar30 = 0xb;
    bVar40 = false;
    iVar7 = 0;
    bVar41 = true;
    piVar10 = (int *)local_298._4_4_;
    pbVar39 = (byte *)"TCP/IP LAN";
    do {
      if (iVar30 == 0) break;
      iVar30 = iVar30 + -1;
      bVar40 = (byte)*piVar10 < *pbVar39;
      bVar41 = (byte)*piVar10 == *pbVar39;
      piVar10 = (int *)((int)piVar10 + 1);
      pbVar39 = pbVar39 + 1;
    } while (bVar41);
    if (!bVar41) {
      iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
    }
    if (iVar7 == 0) {
      ShellButton::ShowButton(urButton,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->buttonRect,0);
      InvalidateRect((HWND)param_1,(RECT *)&urButton->labelRect,0);
      nTransportMode = 5;
      goto LAB_0056aa7f;
    }
  }
  pRVar11 = &local_274;
  local_274.left = 0x140;
  local_274.right = 0x25e;
  local_274.top = 0x91;
  local_274.bottom = 0x1b8;
  BVar49 = 0;
LAB_0056a2aa:
  InvalidateRect((HWND)param_1,pRVar11,BVar49);
  return 1;
  while( true ) {
    iVar30 = iVar30 + -1;
    bVar40 = (byte)*pcVar27 < *pbVar39;
    bVar41 = *pcVar27 == *pbVar39;
    pcVar27 = pcVar27 + 1;
    pbVar39 = pbVar39 + 1;
    if (!bVar41) break;
code_r0x0056c264:
    if (iVar30 == 0) break;
  }
  if (!bVar41) {
    iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
  }
  if (iVar7 == 0) {
    nTransportMode = 4;
  }
  else {
    iVar30 = 0xb;
    bVar40 = false;
    iVar7 = 0;
    bVar41 = true;
    pbVar39 = (byte *)"TCP/IP LAN";
    do {
      if (iVar30 == 0) break;
      iVar30 = iVar30 + -1;
      bVar40 = (byte)*pcVar5 < *pbVar39;
      bVar41 = *pcVar5 == *pbVar39;
      pcVar5 = pcVar5 + 1;
      pbVar39 = pbVar39 + 1;
    } while (bVar41);
    if (!bVar41) {
      iVar7 = (1 - (uint)bVar40) - (uint)(bVar40 != 0);
    }
    if (iVar7 != 0) goto LAB_0056c3be;
    nTransportMode = 5;
  }
  TextLabel::HideLabelText(phoneLabel,1);
  TextLabel::HideLabelText(snLabel,1);
  TextLabel::HideLabelText(plLabel,1);
  TextLabel::HideLabelText(msLabel,1);
  iVar30 = 0;
  pHVar13 = GetDlgItem((HWND)param_1,0x7e7);
  ShowWindow(pHVar13,iVar30);
  iVar30 = 0;
  pHVar13 = GetDlgItem((HWND)param_1,0x820);
  ShowWindow(pHVar13,iVar30);
  ShellButton::HideButton(newPhoneButton,0);
  ShellButton::HideButton(editPhoneButton,0);
  ShellButton::HideButton(delPhoneButton,0);
  TextLabel::HideLabelText(modemStringLabel,1);
  iVar30 = 0;
  pHVar13 = GetDlgItem((HWND)param_1,0x7d1);
  ShowWindow(pHVar13,iVar30);
  ShellButton::HideButton(dialButton,0);
  ShellButton::HideButton(answerButton,0);
  OptionBox::HideBox(comPortBox,0);
  OptionBox::HideBox(baudRateBox,0);
  ShellButton::HideButton(comPortButton,0);
  ShellButton::HideButton(baudRateButton,0);
  ShellButton::HideButton(phoneUpButton,0);
  ShellButton::HideButton(phoneDownButton,0);
  ShellButton::HideButton(nmComPortButton,0);
  OptionBox::HideBox(nmComPortBox,0);
  pSVar18 = backGround;
LAB_0056c3b6:
  SetCurrentBackground(param_1,pSVar18);
LAB_0056c3be:
  pSVar18 = backGround;
  if ((((nTransportMode != 4) && (nTransportMode != 5)) &&
      (pSVar18 = backGroundC, nTransportMode != 3)) && (pSVar18 = backGroundB, nTransportMode == 2))
  {
    pSVar18 = backGroundA;
  }
  SetCurrentBackground(param_1,pSVar18);
  return 1;
}
