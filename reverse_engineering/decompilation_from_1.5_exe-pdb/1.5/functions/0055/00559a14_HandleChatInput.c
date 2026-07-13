/*
 * Entry: 00559a14
 * Name: HandleChatInput
 * Namespace: Global
 * Signature: void HandleChatInput(HWND__ * param_1, dp_s * param_2, ushort param_3, char * param_4, Chat * param_5, PlayerList * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
HandleChatInput(HWND__ *param_1,dp_s *param_2,ushort param_3,char *param_4,Chat *param_5,
               PlayerList *param_6)

{
  bool bVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  uint uVar6;
  Player *pPVar7;
  uint uVar8;
  char *pcVar9;
  Player **ppPVar10;
  HWND in_ECX;
  Chat *this;
  Chat *extraout_ECX;
  Chat *extraout_ECX_00;
  Chat *extraout_ECX_01;
  Chat *extraout_ECX_02;
  Chat *pCVar11;
  Chat *extraout_ECX_03;
  Chat *this_00;
  Chat *extraout_ECX_04;
  Chat *in_EDX;
  ChatColor *pCVar12;
  vector<Player_*,std::allocator<Player_*>_> *this_01;
  char *unaff_EDI;
  char *pcVar13;
  undefined2 in_stack_0000000e;
  char *pcVar14;
  char *local_26c;
  dp_s *local_268;
  char *local_264;
  vector<Player_*,std::allocator<Player_*>_> *local_260;
  PlayerList *local_25c;
  Chat *local_258;
  char local_254 [32];
  undefined2 local_234;
  char local_232 [5];
  char local_22d;
  char local_22c [2];
  char local_22a [62];
  undefined1 local_1ec [228];
  char local_108 [8];
  undefined4 uStack_100;
  char local_fc [9];
  undefined1 local_f3;
  undefined1 local_f2;
  undefined1 local_f1 [2];
  undefined1 local_ef [19];
  undefined1 local_dc [212];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1ec;
  local_268 = (dp_s *)param_1;
  local_26c = _param_3;
  local_234 = 0x4350;
  local_25c = (PlayerList *)param_4;
  local_258 = in_EDX;
  GetWindowTextA(in_ECX,local_232,0x122);
  SetWindowTextA(in_ECX,"");
  if (local_232[0] == '\0') {
    return;
  }
  pcVar14 = "/help";
  iVar5 = _stricmp(local_232,"/help");
  if (iVar5 == 0) {
LAB_00559b1a:
    Chat::Append((Chat *)pcVar14,(char *)in_EDX);
    return;
  }
  iVar5 = _strnicmp(local_232,"/help ",6);
  if (iVar5 == 0) {
    iVar5 = sscanf(local_232,"/help %32s",local_254);
    if (iVar5 != 1) {
      return;
    }
    pcVar14 = (char *)0x811c9dc5;
    uVar6 = Hash(local_254,0x811c9dc5);
    in_EDX = local_258;
    if (((uVar6 != 0x3d7e6258) && (uVar6 != 0x491e0a9c)) && (uVar6 != 0x5d68eeb5)) {
      return;
    }
    goto LAB_00559b1a;
  }
  iVar5 = _stricmp(local_232,"/system");
  if ((iVar5 == 0) || (iVar5 = _stricmp(local_232,"/system on"), iVar5 == 0)) {
    system_on = 1;
    WritePrivateProfileStringA("Config","System","1",shellCfgName);
    pcVar14 = "Show system messages";
    pcVar9 = local_108;
    for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar14;
      pcVar14 = pcVar14 + 4;
      pcVar9 = pcVar9 + 4;
    }
    *pcVar9 = *pcVar14;
    memset(&local_f3,0,0xeb);
    pcVar14 = local_108;
    pcVar9 = "system_on";
  }
  else {
    iVar5 = _stricmp(local_232,"/nosystem");
    if ((iVar5 == 0) || (iVar5 = _stricmp(local_232,"/system off"), iVar5 == 0)) {
      system_on = 0;
      WritePrivateProfileStringA("Config","System","0",shellCfgName);
      pcVar14 = "Hide system messages";
      pcVar9 = local_108;
      for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar14;
        pcVar14 = pcVar14 + 4;
        pcVar9 = pcVar9 + 4;
      }
      *pcVar9 = *pcVar14;
      memset(&local_f3,0,0xeb);
      pcVar14 = local_108;
      pcVar9 = "system_off";
    }
    else {
      iVar5 = _stricmp(local_232,"/players");
      if (iVar5 == 0) {
        uVar6 = 0;
        if ((int)(*(int *)(param_4 + 0x24) - *(int *)(param_4 + 0x20) & 0xfffffffcU) < 1) {
          return;
        }
        do {
          std::vector<Player_*,std::allocator<Player_*>_>::operator[]
                    ((vector<Player_*,std::allocator<Player_*>_> *)(param_4 + 0x14),uVar6);
          Chat::Append(this,(char *)local_258);
          uVar6 = uVar6 + 1;
        } while ((int)uVar6 < *(int *)(param_4 + 0x24) - *(int *)(param_4 + 0x20) >> 2);
        return;
      }
      iVar5 = _strnicmp(local_232,"/msg ",5);
      pcVar14 = local_232;
      if (iVar5 == 0) {
        do {
          cVar2 = *pcVar14;
          pcVar14 = pcVar14 + 1;
        } while (cVar2 != '\0');
        if ((uint)((int)pcVar14 - (int)(local_232 + 1)) < 6) {
          return;
        }
        uVar3 = PlayerList::FindPlayerID((PlayerList *)param_4,&local_22d,(char **)&local_260);
        if (uVar3 == 0xfa01) {
          return;
        }
        if (local_260 == (vector<Player_*,std::allocator<Player_*>_> *)0x0) {
          return;
        }
        if ((char)local_260->_padding_ == '\0') {
          return;
        }
        send_private_message(param_2,uVar3,(ushort)local_260,unaff_EDI);
        pPVar7 = PlayerList::FindPlayer(local_25c,uVar3);
        Chat::AppendWhisperSent(local_258,pPVar7->caName,(char *)local_260);
        return;
      }
      iVar5 = _stricmp(pcVar14,"/times");
      if ((iVar5 == 0) || (iVar5 = _stricmp(local_232,"/times on"), iVar5 == 0)) {
        times_on = 1;
        WritePrivateProfileStringA("Config","Times","1",shellCfgName);
        builtin_strncpy(local_108,"Show mes",8);
        uStack_100._0_1_ = 's';
        uStack_100._1_1_ = 'a';
        uStack_100._2_1_ = 'g';
        uStack_100._3_1_ = 'e';
        builtin_strncpy(local_fc," times",7);
        memset(local_fc + 7,0,0xed);
        pcVar14 = local_108;
        pcVar9 = "times_on";
      }
      else {
        iVar5 = _stricmp(local_232,"/notimes");
        if ((iVar5 == 0) || (iVar5 = _stricmp(local_232,"/times off"), iVar5 == 0)) {
          times_on = 0;
          WritePrivateProfileStringA("Config","Times","0",shellCfgName);
          builtin_strncpy(local_108,"Hide mes",8);
          uStack_100._0_1_ = 's';
          uStack_100._1_1_ = 'a';
          uStack_100._2_1_ = 'g';
          uStack_100._3_1_ = 'e';
          builtin_strncpy(local_fc," times",7);
          memset(local_fc + 7,0,0xed);
          pcVar14 = local_108;
          pcVar9 = "times_off";
        }
        else {
          iVar5 = _stricmp(local_232,"/colors");
          if ((iVar5 == 0) || (iVar5 = _stricmp(local_232,"/colors on"), iVar5 == 0)) {
            colors_on = 1;
            WritePrivateProfileStringA("Config","Colors","1",shellCfgName);
            pcVar14 = "Enable message colors";
            pcVar9 = local_108;
            for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar14;
              pcVar14 = pcVar14 + 4;
              pcVar9 = pcVar9 + 4;
            }
            *(undefined2 *)pcVar9 = *(undefined2 *)pcVar14;
            memset(&local_f2,0,0xea);
            pcVar14 = local_108;
            pcVar9 = "colors_on";
          }
          else {
            iVar5 = _stricmp(local_232,"/color");
            if (iVar5 == 0) {
              pCVar12 = ChatColor;
              do {
                Chat::Append((Chat *)((uint)pCVar12->Value & 0xff),(ulong)local_258,
                             (char *)pCVar12->Value);
                pCVar12 = pCVar12 + 1;
              } while ((int)pCVar12 < 0x633c18);
              return;
            }
            iVar5 = _strnicmp(local_232,"/color ",7);
            if (iVar5 == 0) {
              iVar5 = _stricmp(local_232,"/color save");
              if (iVar5 == 0) {
                SaveChatColors();
                pcVar14 = (char *)extraout_ECX;
                in_EDX = local_258;
              }
              else {
                iVar5 = _stricmp(local_232,"/color load");
                if (iVar5 != 0) {
                  local_260 = (vector<Player_*,std::allocator<Player_*>_> *)
                              sscanf(local_232,"/color %32s %d %d %d",local_254,&local_25c,
                                     &local_264,&local_268);
                  uVar6 = Hash(local_254,0x811c9dc5);
                  iVar5 = 0;
                  do {
                    uVar8 = Hash(ChatColor[iVar5].Name,0x811c9dc5);
                    if (uVar6 == uVar8) {
                      if (local_260 == (vector<Player_*,std::allocator<Player_*>_> *)0x4) {
                        ChatColor[iVar5].Value =
                             (uint)CONCAT21(CONCAT11(local_268._0_1_,local_264._0_1_),
                                            local_25c._0_1_);
                      }
                      Chat::Append((Chat *)ChatColor[iVar5].Value,(ulong)local_258,
                                   (char *)ChatColor[iVar5].Value);
                      return;
                    }
                    iVar5 = iVar5 + 1;
                  } while (iVar5 < 0xd);
                  return;
                }
                LoadChatColors();
                pcVar14 = (char *)extraout_ECX_00;
                in_EDX = local_258;
              }
              goto LAB_00559b1a;
            }
            iVar5 = _stricmp(local_232,"/nocolors");
            if ((iVar5 != 0) && (iVar5 = _stricmp(local_232,"/colors off"), iVar5 != 0)) {
              iVar5 = _strnicmp(local_232,"/mute ",6);
              pcVar14 = local_232;
              if (iVar5 == 0) {
                do {
                  cVar2 = *pcVar14;
                  pcVar14 = pcVar14 + 1;
                } while (cVar2 != '\0');
                if ((uint)((int)pcVar14 - (int)(local_232 + 1)) < 6) {
                  return;
                }
                uVar3 = PlayerList::FindPlayerID((PlayerList *)param_4,local_22c,(char **)0x0);
                if (uVar3 == 0xfa01) {
                  return;
                }
                uVar4 = Net_GetMyPlayerID();
                if (uVar4 == uVar3) {
                  return;
                }
                bVar1 = PlayerList::Mute((PlayerList *)param_4,uVar3);
                if (!bVar1) {
                  return;
                }
                PlayerList::FindPlayer((PlayerList *)param_4,uVar3);
                builtin_strncpy(local_108,"Muted %s",8);
                pcVar14 = (char *)((int)&uStack_100 + 1);
                uStack_100 = uStack_100 & 0xffffff00;
                memset(pcVar14,0,0xf7);
                pcVar9 = local_108;
              }
              else {
                iVar5 = _strnicmp(pcVar14,"/unmute ",8);
                pcVar9 = local_232;
                if (iVar5 == 0) {
                  do {
                    cVar2 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                  } while (cVar2 != '\0');
                  if ((uint)((int)pcVar9 - (int)(local_232 + 1)) < 8) {
                    return;
                  }
                  uVar3 = PlayerList::FindPlayerID((PlayerList *)param_4,local_22a,(char **)0x0);
                  if (uVar3 == 0xfa01) {
                    return;
                  }
                  uVar4 = Net_GetMyPlayerID();
                  if (uVar4 == uVar3) {
                    return;
                  }
                  bVar1 = PlayerList::UnMute((PlayerList *)param_4,uVar3);
                  if (!bVar1) {
                    return;
                  }
                  PlayerList::FindPlayer((PlayerList *)param_4,uVar3);
                  builtin_strncpy(local_108,"Un-muted",8);
                  pcVar14 = local_fc;
                  uStack_100._0_1_ = ' ';
                  uStack_100._1_1_ = '%';
                  uStack_100._2_1_ = 's';
                  uStack_100._3_1_ = '\0';
                  memset(pcVar14,0,0xf4);
                  pcVar9 = local_108;
                }
                else {
                  pcVar14 = (char *)0x559fd6;
                  iVar5 = _strnicmp(pcVar9,"/kick ",6);
                  if (iVar5 != 0) {
                    pcVar9 = "/version";
                    iVar5 = _stricmp(local_232,"/version");
                    if (iVar5 == 0) {
                      Chat::Append((Chat *)pcVar9,(char *)local_258);
                      crc32openlog("crc32game.log");
                      crc32game(0);
                      crc32closelog();
                      pCVar11 = extraout_ECX_03;
                      goto LAB_0055a5cf;
                    }
                    iVar5 = _stricmp(local_232,"/lock");
                    if (iVar5 == 0) {
                      cVar2 = (**(code **)(*(int *)param_4 + 0x14))(Net::myPlayerID);
                      if (cVar2 == '\0') {
                        pcVar9 = "Only the host can lock";
                        pcVar13 = local_108;
                        for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
                          *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                          pcVar9 = pcVar9 + 4;
                          pcVar13 = pcVar13 + 4;
                        }
                        *(undefined2 *)pcVar13 = *(undefined2 *)pcVar9;
                        pcVar13[2] = pcVar9[2];
                        memset(local_f1,0,0xe9);
                        pcVar9 = "only_host_lock";
                      }
                      else {
                        if (Net::bStopGame != false) {
                          return;
                        }
                        Net_LockGame();
                        builtin_strncpy(local_108,"Game loc",8);
                        uStack_100._0_1_ = 'k';
                        uStack_100._1_1_ = 'e';
                        uStack_100._2_1_ = 'd';
                        uStack_100._3_1_ = '\0';
                        memset(local_fc,0,0xf4);
                        pcVar9 = "locked";
                      }
                    }
                    else {
                      iVar5 = _stricmp(local_232,"/unlock");
                      if (iVar5 == 0) {
                        cVar2 = (**(code **)(*(int *)param_4 + 0x14))(Net::myPlayerID);
                        if (cVar2 == '\0') {
                          pcVar9 = "Only the host can unlock";
                          pcVar13 = local_108;
                          for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
                            *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                            pcVar9 = pcVar9 + 4;
                            pcVar13 = pcVar13 + 4;
                          }
                          *pcVar13 = *pcVar9;
                          memset(local_ef,0,0xe7);
                          pcVar9 = "only_host_unlock";
                        }
                        else {
                          if (Net::bStopGame != false) {
                            return;
                          }
                          Net_UnlockGame();
                          builtin_strncpy(local_108,"Game unl",8);
                          uStack_100._0_1_ = 'o';
                          uStack_100._1_1_ = 'c';
                          uStack_100._2_1_ = 'k';
                          uStack_100._3_1_ = 'e';
                          local_fc[0] = 'd';
                          local_fc[1] = '\0';
                          memset(local_fc + 2,0,0xf2);
                          pcVar9 = "unlocked";
                        }
                      }
                      else {
                        if (local_232[0] != '/') {
                          local_264 = local_232;
                          do {
                            cVar2 = *local_264;
                            local_264 = local_264 + 1;
                          } while (cVar2 != '\0');
                          local_264 = local_264 + (3 - (int)(local_232 + 1));
                          if ((char *)0xf4 < local_264) {
                            local_264 = (char *)0xf4;
                          }
                          local_25c = (PlayerList *)0x0;
                          this_01 = (vector<Player_*,std::allocator<Player_*>_> *)(param_4 + 0x14);
                          local_260 = this_01;
                          if (0 < (int)(*(int *)(param_4 + 0x24) - *(int *)(param_4 + 0x20) &
                                       0xfffffffcU)) {
                            do {
                              ppPVar10 = std::vector<Player_*,std::allocator<Player_*>_>::operator[]
                                                   (this_01,(uint)local_25c);
                              pPVar7 = *ppPVar10;
                              dp_result = Net::Send(local_268,(ushort)param_2,pPVar7->id,1,
                                                    &local_234,(uint)local_264);
                              if ((dp_result == 3) && (pPVar7->sendresult != '\x03')) {
                                pcVar14 = "<error> Send buffer full, message not sent.";
                                pcVar9 = local_108;
                                for (iVar5 = 0xb; iVar5 != 0; iVar5 = iVar5 + -1) {
                                  *(undefined4 *)pcVar9 = *(undefined4 *)pcVar14;
                                  pcVar14 = pcVar14 + 4;
                                  pcVar9 = pcVar9 + 4;
                                }
                                memset(local_dc,0,0xd4);
                                read_text_label("multi_message","send_buffer_full",local_108);
                                Chat::Append(this_00,(char *)local_258);
                                this_01 = local_260;
                              }
                              local_25c = (PlayerList *)((int)&local_25c->_padding_ + 1);
                              pPVar7->sendresult = (uchar)dp_result;
                            } while ((int)local_25c <
                                     (int)this_01->_Mylast - (int)this_01->_Myfirst >> 2);
                          }
                          Chat::AppendMessageSent(local_258,local_26c,local_232);
                          return;
                        }
                        iVar5 = Net_ChatCommand(local_232 + 1);
                        if (iVar5 != 0) {
                          return;
                        }
                        builtin_strncpy(local_108,"Unknown ",8);
                        uStack_100._0_1_ = 'c';
                        uStack_100._1_1_ = 'o';
                        uStack_100._2_1_ = 'm';
                        uStack_100._3_1_ = 'm';
                        builtin_strncpy(local_fc,"and",4);
                        memset(local_fc + 4,0,0xf0);
                        pcVar14 = local_108;
                        pcVar9 = "unknown_command";
                      }
                    }
                    goto LAB_0055a5be;
                  }
                  cVar2 = (**(code **)(*(int *)param_4 + 0x14))(Net::myPlayerID);
                  if (cVar2 == '\0') {
                    pcVar14 = "Only the host can kick";
                    pcVar9 = local_108;
                    for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
                      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar14;
                      pcVar14 = pcVar14 + 4;
                      pcVar9 = pcVar9 + 4;
                    }
                    *(undefined2 *)pcVar9 = *(undefined2 *)pcVar14;
                    pcVar9[2] = pcVar14[2];
                    memset(local_f1,0,0xe9);
                    read_text_label("multi_message","only_host_kick",local_108);
                    pCVar11 = extraout_ECX_02;
                    goto LAB_0055a0ca;
                  }
                  pcVar14 = local_232;
                  do {
                    cVar2 = *pcVar14;
                    pcVar14 = pcVar14 + 1;
                  } while (cVar2 != '\0');
                  if ((uint)((int)pcVar14 - (int)(local_232 + 1)) < 7) {
                    return;
                  }
                  uVar3 = PlayerList::FindPlayerID((PlayerList *)param_4,local_22c,&local_26c);
                  if (uVar3 == 0xfa01) {
                    return;
                  }
                  uVar4 = Net_GetMyPlayerID();
                  if (uVar4 == uVar3) {
                    return;
                  }
                  Net_KickPlayer(uVar3);
                  PlayerList::FindPlayer((PlayerList *)param_4,uVar3);
                  builtin_strncpy(local_108,"Kicked %",8);
                  uStack_100 = CONCAT22(uStack_100._2_2_,0x73);
                  memset((int)&uStack_100 + 2,0,0xf6);
                  pcVar14 = local_108;
                  pcVar9 = "kicked";
                }
              }
              read_text_label("multi_message",pcVar9,pcVar14);
              pCVar11 = extraout_ECX_01;
LAB_0055a0ca:
              Chat::Append(pCVar11,(char *)local_258);
              return;
            }
            colors_on = 0;
            WritePrivateProfileStringA("Config","Colors","0",shellCfgName);
            pcVar14 = "Disable message colors";
            pcVar9 = local_108;
            for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
              *(undefined4 *)pcVar9 = *(undefined4 *)pcVar14;
              pcVar14 = pcVar14 + 4;
              pcVar9 = pcVar9 + 4;
            }
            *(undefined2 *)pcVar9 = *(undefined2 *)pcVar14;
            pcVar9[2] = pcVar14[2];
            memset(local_f1,0,0xe9);
            pcVar14 = local_108;
            pcVar9 = "colors_off";
          }
        }
      }
    }
  }
LAB_0055a5be:
  read_text_label("multi_message",pcVar9,pcVar14);
  pCVar11 = extraout_ECX_04;
LAB_0055a5cf:
  Chat::Append(pCVar11,(char *)local_258);
  return;
}
