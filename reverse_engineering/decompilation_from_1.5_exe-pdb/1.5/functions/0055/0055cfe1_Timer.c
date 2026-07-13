/*
 * Entry: 0055cfe1
 * Name: Timer
 * Namespace: Global
 * Signature: void Timer(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Timer(HWND__ *param_1)

{
  bool bVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  undefined1 *puVar5;
  dp_session_t *pdVar6;
  DWORD DVar7;
  Chat *this;
  Chat *extraout_ECX;
  Chat *extraout_ECX_00;
  Chat *this_00;
  Chat *this_01;
  Chat *this_02;
  Chat *this_03;
  Chat *this_04;
  Chat *this_05;
  Chat *this_06;
  char *pcVar8;
  PlayerList *this_07;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 uVar12;
  undefined1 local_72c [4];
  HWND__ *local_728;
  ulong local_724;
  int local_720;
  int local_71c;
  undefined4 local_718;
  char *local_714;
  undefined1 local_710 [13];
  ushort local_703;
  undefined1 local_6b0 [4];
  undefined1 local_6ac [9];
  ushort local_6a3;
  undefined2 local_69f;
  undefined2 local_69b;
  char local_699 [56];
  undefined4 local_661;
  ushort local_650;
  undefined4 local_64e;
  char local_64a [1018];
  undefined1 local_250 [2];
  char local_24e [42];
  char local_224 [4];
  undefined4 uStack_220;
  char acStack_21c [22];
  undefined1 local_206 [226];
  char local_124 [4];
  undefined4 uStack_120;
  char acStack_11c [13];
  undefined1 local_10f;
  undefined1 local_10e;
  undefined1 local_10d [2];
  undefined1 local_10b [2];
  undefined1 local_109 [10];
  undefined1 local_ff [3];
  undefined1 local_fc [216];
  char local_24 [28];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_6ac;
  local_728 = param_1;
  local_71c = 0;
  do {
    local_720 = 0x400;
    iVar2 = dpReceive(Net::dp,&local_718,local_72c,0,&local_650,&local_720);
    if (iVar2 == 0) {
      local_71c = 0;
LAB_0055d06b:
      if (iVar2 == 0) {
        if ((short)local_718 == 0) {
          if (local_650 == 0x3164) {
            if (system_on != 0) {
              builtin_strncpy(local_224,"<sys",4);
              uStack_220._0_1_ = 't';
              uStack_220._1_1_ = 'e';
              uStack_220._2_1_ = 'm';
              uStack_220._3_1_ = '>';
              acStack_21c[0] = ' ';
              acStack_21c[1] = '\0';
              memset(acStack_21c + 2,0,0xf6);
              builtin_strncpy(local_124,"ente",4);
              uStack_120._0_3_ = 0x7372;
              memset((int)&uStack_120 + 3,0,0xf9);
              read_text_label("multi_message","player_named",local_224);
              read_text_label("multi_message","entered_room",local_124);
              this_00 = extraout_ECX_00;
LAB_0055d210:
              Chat::Append(this_00,(char *)&chatRoom);
            }
          }
          else if (local_650 == 0x3264) {
            if (system_on != 0) {
              builtin_strncpy(local_124,"<sys",4);
              uStack_120._0_1_ = 't';
              uStack_120._1_1_ = 'e';
              uStack_120._2_1_ = 'm';
              uStack_120._3_1_ = '>';
              acStack_11c[0] = ' ';
              acStack_11c[1] = '\0';
              memset(acStack_11c + 2,0,0xf6);
              builtin_strncpy(local_224,"leav",4);
              uStack_220._0_3_ = 0x7365;
              memset((int)&uStack_220 + 3,0,0xf9);
              read_text_label("multi_message","player_named",local_124);
              read_text_label("multi_message","left_room",local_224);
              this_00 = extraout_ECX;
              goto LAB_0055d210;
            }
          }
          else if (local_650 == 0x3764) {
            pcVar11 = "<system> You are now the host";
            pcVar9 = local_224;
            for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
              pcVar11 = pcVar11 + 4;
              pcVar9 = pcVar9 + 4;
            }
            *(undefined2 *)pcVar9 = *(undefined2 *)pcVar11;
            memset(local_206,0,0xe2);
            read_text_label("multi_message","you_are_host",local_224);
            Chat::Append(this,(char *)&chatRoom);
          }
          else if (local_650 == 0x3964) {
            bSessionLost = true;
            return;
          }
        }
        else if (local_650 < 0x5348) {
          if (local_650 == 0x5347) {
            bSessionEnded = true;
LAB_0055d35b:
            Net::Close();
          }
          else {
            if (local_650 == 0x4350) {
              dpGetPlayerName(Net::dp,local_718,local_24,0x19);
              iVar2 = strncmp("#_)(",(char *)&local_64e,4);
              if (iVar2 == 0) {
                local_714 = strtok(local_64a," ");
                pcVar11 = strtok((char *)0x0," ");
                if ((local_714 != (char *)0x0) && (pcVar11 != (char *)0x0)) {
                  local_724 = crc32zix(local_714,0);
                  uVar3 = atol(pcVar11);
                  if (local_724 != uVar3) {
                    pcVar11 = "file differs with player";
                    pcVar9 = local_124;
                    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
                      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
                      pcVar11 = pcVar11 + 4;
                      pcVar9 = pcVar9 + 4;
                    }
                    *pcVar9 = *pcVar11;
                    memset(local_10b,0,0xe7);
                    read_text_label("multi_message","file_differs",local_124);
                    Chat::Append(this_03,(char *)&chatRoom);
                  }
                  sprintf(local_24e,"__)(%s %ld ",local_714,local_724);
                  Net::Send(Net::dp,Net::myPlayerID,0,1,local_250,0x2a);
                }
              }
              else {
                iVar2 = strncmp("__)(",(char *)&local_64e,4);
                if (iVar2 == 0) {
                  local_714 = strtok(local_64a," ");
                  pcVar11 = strtok((char *)0x0," ");
                  if ((local_714 != (char *)0x0) && (pcVar11 != (char *)0x0)) {
                    uVar3 = crc32zix(local_714,0);
                    uVar4 = atol(pcVar11);
                    if (uVar3 != uVar4) {
                      pcVar11 = "file differs with player";
                      pcVar9 = local_124;
                      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
                        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
                        pcVar11 = pcVar11 + 4;
                        pcVar9 = pcVar9 + 4;
                      }
                      *pcVar9 = *pcVar11;
                      memset(local_10b,0,0xe7);
                      read_text_label("multi_message","file_differs",local_124);
                      Chat::Append(this_04,(char *)&chatRoom);
                    }
                  }
                }
                else {
                  bVar1 = PlayerList::IsMuted(&playersInRoom,(ushort)local_718);
                  if (!bVar1) {
                    Chat::AppendMessage((Chat *)&chatRoom,local_24,local_720 - 2,(char *)&local_64e)
                    ;
                  }
                }
              }
              goto LAB_0055d6f3;
            }
            if (local_650 == 0x4b41) {
              pcVar11 = "You have been auto-kicked from the room";
              pcVar9 = local_124;
              for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
                *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
                pcVar11 = pcVar11 + 4;
                pcVar9 = pcVar9 + 4;
              }
              memset(local_fc,0,0xd8);
              read_text_label("multi_message","autokick_room",local_124);
              Chat::Append(this_02,(char *)&chatRoom);
              goto LAB_0055d35b;
            }
            if (local_650 != 0x4b4b) {
              if ((local_650 == 0x5341) && (system_on != 0)) {
                pcVar11 = "Host auto-kicked player %s";
                pcVar9 = local_124;
                for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
                  *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
                  pcVar11 = pcVar11 + 4;
                  pcVar9 = pcVar9 + 4;
                }
                *(undefined2 *)pcVar9 = *(undefined2 *)pcVar11;
                pcVar9[2] = pcVar11[2];
                memset(local_109,0,0xe5);
                pcVar11 = "host_autokicked";
                goto LAB_0055d6bb;
              }
              goto LAB_0055d6f3;
            }
            pcVar11 = "You have been kicked out of the room";
            pcVar9 = local_124;
            for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
              pcVar11 = pcVar11 + 4;
              pcVar9 = pcVar9 + 4;
            }
            *pcVar9 = *pcVar11;
            memset(local_ff,0,0xdb);
            read_text_label("multi_message","kick_room",local_124);
            Chat::Append(this_01,(char *)&chatRoom);
            SessionList::Banned(&roomList);
            Net::Close();
          }
          SessionList::JoinLobby(&roomList);
        }
        else if (local_650 == 0x534b) {
          if (system_on != 0) {
            pcVar11 = "Host kicked player %s";
            pcVar9 = local_124;
            for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
              pcVar11 = pcVar11 + 4;
              pcVar9 = pcVar9 + 4;
            }
            *(undefined2 *)pcVar9 = *(undefined2 *)pcVar11;
            memset(&local_10e,0,0xea);
            pcVar11 = "host_kicked";
LAB_0055d6bb:
            read_text_label("multi_message",pcVar11,local_124);
            dpGetPlayerName(Net::dp,local_64e,local_24,0x19);
            Chat::Append(this_06,(char *)&chatRoom);
          }
        }
        else if (local_650 == 0x534c) {
          if (system_on != 0) {
            pcVar11 = "Host locked the game";
            pcVar9 = local_124;
            for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
              pcVar11 = pcVar11 + 4;
              pcVar9 = pcVar9 + 4;
            }
            uVar12 = 0xeb;
            puVar5 = &local_10f;
LAB_0055d64c:
            *pcVar9 = *pcVar11;
            memset(puVar5,0,uVar12);
            read_text_label("multi_message","host_locked",local_124);
            Chat::Append(this_05,(char *)&chatRoom);
          }
        }
        else if (local_650 == 0x5355) {
          if (system_on != 0) {
            pcVar8 = "Host unlocked the game";
            pcVar10 = local_124;
            for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
              *(undefined4 *)pcVar10 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar10 = pcVar10 + 4;
            }
            pcVar9 = pcVar10 + 2;
            pcVar11 = pcVar8 + 2;
            *(undefined2 *)pcVar10 = *(undefined2 *)pcVar8;
            uVar12 = 0xe9;
            puVar5 = local_10d;
            goto LAB_0055d64c;
          }
        }
        else if (local_650 == 0x5370) {
          dpGetPlayerName(Net::dp,local_718,local_24,0x19);
          bVar1 = PlayerList::IsMuted(&playersInRoom,(ushort)local_718);
          if (!bVar1) {
            Chat::AppendWhisper((Chat *)&chatRoom,local_24,local_720 - 2,(char *)&local_64e);
          }
        }
      }
    }
    else {
      if (iVar2 != 2) {
        if (iVar2 == 0xc) {
          bModemNoResponse = true;
          return;
        }
        if (iVar2 == 0x10) {
          bHostNotResponding = true;
          return;
        }
        goto LAB_0055d06b;
      }
      local_71c = local_71c + 1;
    }
LAB_0055d6f3:
  } while (local_71c < 3);
  if (people_state == 2) {
    pdVar6 = SessionList::GetCurrent((SessionList *)&gameList);
    if (pdVar6 == (dp_session_t *)0x0) {
      people_state = 4;
      this_07 = (PlayerList *)&playersInGame;
    }
    else {
      people_state = 3;
      PlayerList::StartEnum((PlayerList *)&playersInGame);
      dp_result = dpEnumPlayersEx(Net::dp,pdVar6,dpEnumPlayersCallback,0,0);
      if (dp_result == 0) goto LAB_0055d7ed;
      people_state = 4;
      this_07 = (PlayerList *)&playersInGame;
LAB_0055d762:
      PlayerList::EndEnum(this_07);
    }
  }
  else {
    if (people_state != 4) goto LAB_0055d7ed;
    pdVar6 = SessionList::GetCurrent(&roomList);
    if (pdVar6 != (dp_session_t *)0x0) {
      this_07 = &playersInRoom;
      people_state = 1;
      PlayerList::StartEnum(&playersInRoom);
      dp_result = dpEnumPlayersEx(Net::dp,pdVar6,dpEnumPlayersCallback,0,0);
      if (dp_result == 0) goto LAB_0055d7ed;
      people_state = 2;
      goto LAB_0055d762;
    }
    people_state = 2;
    this_07 = &playersInRoom;
  }
  PlayerList::Clear(this_07);
LAB_0055d7ed:
  if (state == 0xc9) {
    if (createRoom != false) {
      Net::Close();
      DVar7 = Get_TimeNow();
      dwCreateRoomTimeout = DVar7 + 10000;
      chat_state = 5;
      if (nTransportMode == 3) {
        dp_result = dpSetGameServerEx(Net::dp,Net::hostname,Net::session_type);
        if (dp_result == 0) {
          dp_result = dpOpen(Net::dp,0,dpCreateRoomOpenCallback,&roomList);
        }
        else {
          pcVar11 = "Cannot connect to server";
          pcVar9 = local_124;
          for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar9 = pcVar9 + 4;
          }
          *pcVar9 = *pcVar11;
          memset(local_10b,0,0xe7);
          read_text_label("multi_error","cannot_connect_server",local_124);
          do_error(local_728,local_124);
        }
      }
      else {
        memset(local_6b0,0,0x5f);
        local_69b = 0x51;
        local_6a3 = Net::session_type;
        local_69f = 0x1e;
        local_6b0[0] = 0x5f;
        local_661 = 2;
        strncpy(local_699,"Battle Zone",0x20);
        dp_result = dpOpen(Net::dp,local_6b0,dpCreateRoomOpenCallback,&roomList);
      }
      if (dp_result != 0) {
        SessionList::JoinLobby(&roomList);
      }
      createRoom = false;
    }
    memset(local_710,0,0x5f);
    local_710[0] = 0x5f;
    local_703 = Net::session_type;
    state = 200;
    SessionList::StartEnum((SessionList *)&gameList);
    SessionList::StartEnum(&roomList);
    dp_result = dpEnumSessions(Net::dp,local_710,0,0,dpEnumGamesCallback,0);
  }
  if (chat_state == 6) {
    chat_state = 7;
    dp_result = dpCreatePlayer(Net::dp,dpCreatePlayerCallback,0,player_name);
    if (dp_result != 0) {
      SessionList::JoinLobby(&roomList);
    }
  }
  else if (chat_state == 8) {
    chat_state = 0;
  }
  return;
}
