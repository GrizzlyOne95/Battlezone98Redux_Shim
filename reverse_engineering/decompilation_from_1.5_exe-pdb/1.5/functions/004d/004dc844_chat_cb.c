/*
 * Entry: 004dc844
 * Name: chat_cb
 * Namespace: Global
 * Signature: int chat_cb(void * * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl chat_cb(void **param_1,char *param_2)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  dp_s *pdVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  undefined2 *puVar8;
  undefined2 local_114;
  char local_112 [6];
  char local_10c [8];
  undefined4 uStack_104;
  char local_100 [9];
  undefined1 local_f7 [2];
  undefined1 local_f5 [2];
  undefined1 local_f3 [95];
  undefined1 local_94 [140];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_94;
  TextInput_ShowRegion(chat_entry,0);
  TextInput_AllowInput(chat_entry,0);
  Scroll_SetFlags(chat_display,1,1);
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    return 0;
  }
  pdVar4 = Net_GetDP();
  if (pdVar4 != (dp_s *)0x0) {
    iVar5 = _stricmp(param_2,"/help");
    if (iVar5 == 0) {
      Scroll_AddString(chat_display,"/mute <player> - mute the specified player");
      Scroll_AddString(chat_display,"/unmute <player> - unmute the specified player");
      Scroll_AddString(chat_display,"/kick <player> - kick out the specified player");
      Scroll_AddString(chat_display,"/lock - prevent new players from joining");
      Scroll_AddString(chat_display,"/unlock - allow new players to join");
    }
    else {
      iVar5 = _stricmp(param_2,"/kick");
      if (iVar5 == 0) {
        iVar5 = Net_IsHosting();
        if (iVar5 != 0) {
          if (destinations[cur_dest].dpid == 0) {
            return 1;
          }
          NetPlayer_GetPlayerName(destinations[cur_dest].dpid);
          builtin_strncpy(local_10c,"Kicked %",8);
          uStack_104 = CONCAT22(uStack_104._2_2_,0x73);
          memset((int)&uStack_104 + 2,0,0xf6);
          read_text_label("multi_message","kicked",local_10c);
          DMessage(local_10c);
          Net_KickPlayer(destinations[cur_dest].dpid);
          return 1;
        }
        pcVar7 = "Only the host can kick";
        pcVar6 = local_10c;
        for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
          *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar6 = pcVar6 + 4;
        }
        *(undefined2 *)pcVar6 = *(undefined2 *)pcVar7;
        pcVar6[2] = pcVar7[2];
        memset(local_f5,0,0xe9);
        pcVar7 = "only_host_kick";
      }
      else {
        iVar5 = _stricmp(param_2,"/mute");
        if (iVar5 == 0) {
          if (destinations[cur_dest].dpid == 0) {
            return 1;
          }
          NetPlayer_GetPlayerName(destinations[cur_dest].dpid);
          builtin_strncpy(local_10c,"Muted %s",8);
          uStack_104 = uStack_104 & 0xffffff00;
          memset((int)&uStack_104 + 1,0,0xf7);
          read_text_label("multi_message","muted",local_10c);
          DMessage(local_10c);
          Net_MutePlayer(destinations[cur_dest].dpid);
          return 1;
        }
        iVar5 = _stricmp(param_2,"/unmute");
        if (iVar5 == 0) {
          if (destinations[cur_dest].dpid == 0) {
            return 1;
          }
          NetPlayer_GetPlayerName(destinations[cur_dest].dpid);
          builtin_strncpy(local_10c,"Un-muted",8);
          uStack_104._0_1_ = ' ';
          uStack_104._1_1_ = '%';
          uStack_104._2_1_ = 's';
          uStack_104._3_1_ = '\0';
          memset(local_100,0,0xf4);
          read_text_label("multi_message","unmuted",local_10c);
          DMessage(local_10c);
          Net_UnmutePlayer(destinations[cur_dest].dpid);
          return 1;
        }
        iVar5 = _stricmp(param_2,"/system");
        if ((iVar5 == 0) || (iVar5 = _stricmp(param_2,"/system on"), iVar5 == 0)) {
          pcVar7 = "Show system messages";
          pcVar6 = local_10c;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar6 = pcVar6 + 4;
          }
          *pcVar6 = *pcVar7;
          memset(local_f7,0,0xeb);
          read_text_label("multi_message","system_on",local_10c);
          DMessage(local_10c);
          system_on = 1;
          return 1;
        }
        iVar5 = _stricmp(param_2,"/nosystem");
        if ((iVar5 == 0) || (iVar5 = _stricmp(param_2,"/system off"), iVar5 == 0)) {
          pcVar7 = "Hide system messages";
          pcVar6 = local_10c;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar6 = pcVar6 + 4;
          }
          *pcVar6 = *pcVar7;
          memset(local_f7,0,0xeb);
          read_text_label("multi_message","system_off",local_10c);
          DMessage(local_10c);
          system_on = 0;
          return 1;
        }
        iVar5 = _stricmp(param_2,"/lock");
        if (iVar5 == 0) {
          iVar5 = Net_IsHosting();
          if (iVar5 != 0) {
            builtin_strncpy(local_10c,"Game loc",8);
            uStack_104._0_1_ = 'k';
            uStack_104._1_1_ = 'e';
            uStack_104._2_1_ = 'd';
            uStack_104._3_1_ = '\0';
            memset(local_100,0,0xf4);
            read_text_label("multi_message","locked",local_10c);
            DMessage(local_10c);
            Net_LockGame();
            return 1;
          }
          pcVar7 = "Only the host can lock";
          pcVar6 = local_10c;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar6 = pcVar6 + 4;
          }
          *(undefined2 *)pcVar6 = *(undefined2 *)pcVar7;
          pcVar6[2] = pcVar7[2];
          memset(local_f5,0,0xe9);
          pcVar7 = "only_host_lock";
        }
        else {
          iVar5 = _stricmp(param_2,"/unlock");
          if (iVar5 == 0) {
            iVar5 = Net_IsHosting();
            if (iVar5 != 0) {
              builtin_strncpy(local_10c,"Game unl",8);
              uStack_104._0_1_ = 'o';
              uStack_104._1_1_ = 'c';
              uStack_104._2_1_ = 'k';
              uStack_104._3_1_ = 'e';
              local_100[0] = 'd';
              local_100[1] = '\0';
              memset(local_100 + 2,0,0xf2);
              read_text_label("multi_message","unlocked",local_10c);
              DMessage(local_10c);
              Net_UnlockGame();
              return 1;
            }
            pcVar7 = "Only the host can unlock";
            pcVar6 = local_10c;
            for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
              *(undefined4 *)pcVar6 = *(undefined4 *)pcVar7;
              pcVar7 = pcVar7 + 4;
              pcVar6 = pcVar6 + 4;
            }
            *pcVar6 = *pcVar7;
            memset(local_f3,0,0xe7);
            pcVar7 = "only_host_unlock";
          }
          else {
            if (*param_2 != '/') {
              uVar2 = destinations[cur_dest].dpid;
              if (uVar2 == 0) {
                uVar2 = Net_GetMyPlayerID();
                pcVar7 = NetPlayer_GetPlayerName(uVar2);
                if (pcVar7 != (char *)0x0) {
                  DMessage("<%s> %s");
                }
                local_114 = 0x4350;
              }
              else {
                if (uVar2 == 1) {
                  DMessage("<%s> %s");
                }
                else {
                  pcVar7 = NetPlayer_GetPlayerName(uVar2);
                  if (pcVar7 != (char *)0x0) {
                    DMessage("<%s %s> %s");
                  }
                }
                local_114 = 0x5370;
              }
              pcVar7 = param_2;
              do {
                cVar1 = *pcVar7;
                pcVar7[(int)(local_112 + -(int)param_2)] = cVar1;
                pcVar7 = pcVar7 + 1;
              } while (cVar1 != '\0');
              uVar2 = destinations[cur_dest].dpid;
              if (uVar2 == 1) {
                uVar2 = NetPlayer_GetFirstPlayer
                                  ((char **)0x0,(ulong *)0x0,(ulong *)0x0,(ulong *)0x0);
                while (uVar2 != 0xfa01) {
                  iVar5 = NetPlayer_IsPlayerAlly(uVar2);
                  if (iVar5 != 0) {
                    pcVar7 = param_2;
                    do {
                      cVar1 = *pcVar7;
                      pcVar7 = pcVar7 + 1;
                    } while (cVar1 != '\0');
                    pcVar7 = pcVar7 + (3 - (int)(param_2 + 1));
                    puVar8 = &local_114;
                    iVar5 = 1;
                    uVar3 = Net_GetMyPlayerID();
                    pdVar4 = Net_GetDP();
                    Net_Send(pdVar4,uVar3,uVar2,iVar5,puVar8,(uint)pcVar7);
                  }
                  uVar2 = NetPlayer_GetNextPlayer
                                    ((char **)0x0,(ulong *)0x0,(ulong *)0x0,(ulong *)0x0);
                }
                return 1;
              }
              pcVar7 = param_2 + 1;
              do {
                cVar1 = *param_2;
                param_2 = param_2 + 1;
              } while (cVar1 != '\0');
              pcVar7 = param_2 + (3 - (int)pcVar7);
              puVar8 = &local_114;
              iVar5 = 1;
              uVar3 = Net_GetMyPlayerID();
              pdVar4 = Net_GetDP();
              Net_Send(pdVar4,uVar3,uVar2,iVar5,puVar8,(uint)pcVar7);
              return 1;
            }
            iVar5 = Net_ChatCommand(param_2 + 1);
            if (iVar5 != 0) {
              return 1;
            }
            builtin_strncpy(local_10c,"Unknown ",8);
            uStack_104._0_1_ = 'c';
            uStack_104._1_1_ = 'o';
            uStack_104._2_1_ = 'm';
            uStack_104._3_1_ = 'm';
            builtin_strncpy(local_100,"and",4);
            memset(local_100 + 4,0,0xf0);
            pcVar7 = "unknown_command";
          }
        }
      }
      read_text_label("multi_message",pcVar7,local_10c);
      DMessage(local_10c);
    }
  }
  return 1;
}
