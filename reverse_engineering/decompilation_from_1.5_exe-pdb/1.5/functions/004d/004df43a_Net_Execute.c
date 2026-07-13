/*
 * Entry: 004df43a
 * Name: Net::Execute
 * Namespace: Net
 * Signature: int Execute(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall Net::Execute(Net *this)

{
  ulong *puVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  NetState NVar5;
  PING_PACKET *pPVar6;
  bool bVar7;
  DWORD DVar8;
  int iVar9;
  ulong uVar10;
  int iVar11;
  char *pcVar12;
  uint uVar13;
  _func___cdecl_void *p_Var14;
  _func___cdecl_void_ushort_ushort *p_Var15;
  undefined1 *puVar16;
  Team *pTVar17;
  NetPlayer *pNVar18;
  AiMission *pAVar19;
  ushort uVar20;
  _func___cdecl_void_ushort_char_ptr_char_ptr_uint *p_Var21;
  dp_session_t_u_23 *pdVar22;
  char *pcVar23;
  undefined4 unaff_EDI;
  undefined4 *puVar24;
  uint uVar25;
  char *pcVar26;
  float fVar27;
  char *pcVar28;
  undefined8 uVar29;
  int local_5d0;
  undefined1 local_5cc [4];
  float local_5c8;
  int local_5c4;
  DWORD local_5c0;
  int local_5bc;
  uint local_5b8;
  char local_5b4 [96];
  undefined1 local_554 [928];
  char local_1b4 [44];
  char local_188 [2];
  char acStack_186 [19];
  undefined1 local_173;
  undefined1 local_172;
  undefined1 local_171 [4];
  undefined1 local_16d [229];
  char local_88 [4];
  undefined1 local_84 [17];
  dp_session_t_u_17 local_73;
  undefined4 local_6d [8];
  uint local_4d;
  char acStack_49 [4];
  char acStack_45 [2];
  char local_43 [4];
  char acStack_3f [4];
  char acStack_3b [6];
  long local_35;
  char local_24 [4];
  undefined2 local_20;
  ulong local_1e;
  undefined2 local_18 [8];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_554;
  DVar8 = Get_TimeNow();
  UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffff7;
  UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffffd;
  UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffffb;
  UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffffe;
  StartEdit = 0;
  TerrainEdit = 0;
  iVar11 = 2;
  difficultySetting = iVar11;
  iVar9 = dpNumPlayers();
  if ((1 < iVar9) && (iVar11 = iVar9, 8 < iVar9)) {
    iVar11 = 8;
  }
  Net_MaxOrdnanceSize = (10 - iVar11) * 0x14;
  uVar10 = 0xb4;
  if ((0xb4 < Net_MaxOrdnanceSize) || (uVar10 = 0x28, Net_MaxOrdnanceSize < 0x28)) {
    Net_MaxOrdnanceSize = uVar10;
  }
  if (this->dwNextScoreTime < DVar8) {
    Scores_UpdateScores();
    this->dwNextScoreTime = DVar8 + 1000;
    hosting = IsHost((ushort)unaff_EDI);
    MaxPositionPacketInterval = NextPositionPacketInterval;
  }
  AdjustBandwidth(this);
  local_5c4 = 0;
LAB_004df51d:
  NVar5 = this->state;
  if (NVar5 == INITIAL) {
    Connect(this);
  }
  else if (NVar5 == FINISHED_ENUM_SESSIONS) {
    if (bFoundSession == false) {
      DEBUG_systemError("Failed to join game %s");
                    /* WARNING: Subroutine does not return */
      exit(0x65);
    }
    Join(this);
  }
  else if (NVar5 == FINISHED_CREATE_PLAYER) {
    this->state = (hosting == false) + NET_IS_RUNNING;
  }
  else if (NVar5 == FINISHED_OPEN) {
    CreatePlayer(this);
  }
  else if (NVar5 == WAITING_FOR_SPAWNPOINT) {
    if (this->got_start_location != false) {
      this->state = NET_IS_RUNNING;
    }
  }
  else if (NVar5 == NET_IS_ERROR) {
    Shell_MessageBox_Printf(0,"Network","Could not connect to game");
    return 0;
  }
  pcVar12 = this->buffer;
  local_5bc = 0x400;
  iVar11 = dpReceive(dp,&local_5b8,local_5cc,0);
  local_5c0 = Get_TimeNow();
  if ((iVar11 == 0) && ((ushort)local_5b8 != 0)) {
    if (*(short *)pcVar12 == 0x5050) {
      if (network_loggit != 0) {
        if (fp == (_iobuf *)0x0) {
          fp = (_iobuf *)fopen("j.log","w");
        }
        if (network_loggit != 0) {
          fprintf((FILE *)fp,"Got Ping packet from %d\n");
        }
      }
      DVar8 = local_5c0;
      if (myPlayerID == 0xfa01) {
        if (network_loggit != 0) {
          MessageBeep(0xffffffff);
          fprintf((FILE *)fp,"GOT PING NO PLAYER\n");
        }
      }
      else {
        *this->pingreply_slave_received_time = local_5c0;
        *this->pingreply_master_send_time = *this->ping_master_send_time;
        Send(dp,(ushort)_myPlayerID,(ushort)local_5b8,0,this->pingreply_buffer,10);
        if (network_loggit != 0) {
          fprintf((FILE *)fp,"Send Ping Reply %d -> %d ct = %ld mst = %ld\n",_myPlayerID & 0xffff,
                  local_5b8 & 0xffff,DVar8);
        }
      }
      bVar7 = IsHost((ushort)unaff_EDI);
      if (bVar7) {
        if (network_loggit != 0) {
          fprintf((FILE *)fp,"SET CLOCK OFFSET: %lu, %d, %lu\n",this->ping->offset,
                  this->ping->BAddOffset);
        }
        pPVar6 = this->ping;
        if ((pPVar6->offset != 0) || (pPVar6->BAddOffset != 0)) {
          SetClockOffsetAndStartTime(pPVar6->offset,pPVar6->BAddOffset,pPVar6->host_start_time);
        }
      }
      if (network_loggit != 0) {
        Get_Time();
        DisplayMessage("Got Ping Current Time = %f");
      }
    }
    else {
      if (*(short *)pcVar12 != 0x4147) goto LAB_004df820;
      if (myPlayerID != 0xfa01) {
        *this->pingreply_slave_received_time = local_5c0;
        *this->pingreply_master_send_time = *(ulong *)(this->buffer + 2);
        Send(dp,(ushort)_myPlayerID,(ushort)local_5b8,0,this->pingreply_buffer,10);
      }
      bVar7 = IsHost((ushort)unaff_EDI);
      if (bVar7) {
        bVar2 = this->buffer[10];
        uVar20 = 0;
        if (bVar2 != 0) {
          do {
            if (myPlayerID == *(ushort *)(this->buffer + (uint)uVar20 * 0xc + 0xe)) break;
            uVar20 = uVar20 + 1;
          } while (uVar20 < bVar2);
        }
        if (uVar20 < bVar2) {
          iVar11 = (uint)uVar20 * 0xc;
          if ((*(ulong *)(this->buffer + iVar11 + 0x12) != 0) ||
             (*(int *)(this->buffer + iVar11 + 0x16) != 0)) {
            SetClockOffsetAndStartTime
                      (*(ulong *)(this->buffer + iVar11 + 0x12),
                       *(int *)(this->buffer + iVar11 + 0x16),*(ulong *)(this->buffer + 6));
          }
        }
      }
    }
LAB_004e0579:
    uVar20 = (ushort)unaff_EDI;
    if (local_5c4 < 3) goto LAB_004df51d;
  }
  else {
LAB_004df820:
    if (iVar11 != 0) {
      if (iVar11 == 2) {
        local_5c4 = local_5c4 + 1;
      }
      else {
        if (iVar11 == 0xc) {
          DistributedObject_SetDP((dp_s *)0x0);
          if (bStopGame != false) {
            return 1;
          }
          iNetEscapeModemNoResponse = 1;
          goto LAB_004e07ff;
        }
        if (iVar11 == 0x10) {
          DisplayMessage("Connection to game server lost.");
        }
      }
      goto LAB_004e0579;
    }
    total_bytes_received = total_bytes_received + local_5bc;
    local_5c4 = 0;
    if ((ushort)local_5b8 == 0) {
      uVar20 = *(ushort *)pcVar12;
      if (uVar20 < 0x3565) {
        if (uVar20 != 0x3564) {
          if (uVar20 == 0x3164) {
            SetMyFlag();
            pNVar18 = NetPlayer::Find(*(ushort *)(this->buffer + 2));
            if (pNVar18 == (NetPlayer *)0x0) {
              if (hosting == false) {
                DisplayMessage("%s: id = %ld name = \"%s\"");
                NetPlayer::AddPlayer(*(ushort *)(this->buffer + 2),this->buffer + 0x10,0);
              }
              else {
                local_5c0 = NetPlayer::FindUnusedTeam();
                DisplayMessage("%s: id = %ld name = \"%s\" team = %d");
                NetPlayer::AddPlayer(*(ushort *)(this->buffer + 2),this->buffer + 0x10,local_5c0);
                local_20 = 0x4154;
                local_1e = CONCAT31(local_1e._1_3_,(undefined1)local_5c0);
                Send(dp,(ushort)_myPlayerID,*(ushort *)(this->buffer + 2),1,&local_20,3);
              }
              this->dwLastSpawn = 0;
              this->dwLastPing = 0;
              this->dwNextPing = 300;
            }
            local_20 = 0x4c53;
            local_1e = Net_CRC;
            Send(dp,(ushort)_myPlayerID,*(ushort *)(this->buffer + 2),1,&local_20,6);
          }
          else if (uVar20 == 0x3264) {
            NetPlayer::DelPlayer(*(ushort *)(this->buffer + 2),this->buffer + 0x10);
            DisplayMessage("%s: id = %ld name = %s");
            bVar7 = IsHost((ushort)unaff_EDI);
            if (bVar7) {
              dpidPrevHost = *(ushort *)(this->buffer + 2);
              dpidCurHost = 0xfa01;
            }
            if (*(ushort *)(this->buffer + 2) == myPlayerID) {
              Close(false);
              return 0;
            }
          }
        }
      }
      else if (uVar20 != 0x3664) {
        if (uVar20 == 0x3764) {
          SendGameInfoData(dp,myPlayerID);
          hosting = true;
          this->dwLastSpawn = 0;
          this->dwLastPing = 0;
          pcVar28 = host;
          pcVar12 = "%s";
          this->dwNextPing = 300;
          DisplayMessage("%s");
          dpidCurHost = myPlayerID;
          local_5c0 = 0x5f;
          iVar11 = dpGetSessionDesc(dp,local_84,&local_5c0,pcVar12,pcVar28);
          if (iVar11 == 0) {
            local_73 = sDesc.field5_0x11;
            pdVar22 = &sDesc.field8_0x17;
            puVar24 = local_6d;
            for (iVar11 = 8; iVar11 != 0; iVar11 = iVar11 + -1) {
              *puVar24 = *(undefined4 *)pdVar22;
              pdVar22 = (dp_session_t_u_23 *)((int)pdVar22 + 4);
              puVar24 = puVar24 + 1;
            }
            acStack_49[0] = sDesc.szUserField[4];
            acStack_49[1] = sDesc.szUserField[5];
            acStack_49[2] = sDesc.szUserField[6];
            acStack_49[3] = sDesc.szUserField[7];
            acStack_45[0] = sDesc.szUserField[8];
            acStack_45[1] = sDesc.szUserField[9];
            local_4d = sDesc.szUserField._0_4_ | 0x8000;
            local_43[0] = sDesc.szPassword[0];
            local_43[1] = sDesc.szPassword[1];
            local_43[2] = sDesc.szPassword[2];
            local_43[3] = sDesc.szPassword[3];
            acStack_3f[0] = sDesc.szPassword[4];
            acStack_3f[1] = sDesc.szPassword[5];
            acStack_3f[2] = sDesc.szPassword[6];
            acStack_3f[3] = sDesc.szPassword[7];
            acStack_3b[0] = sDesc.szPassword[8];
            acStack_3b[1] = sDesc.szPassword[9];
            local_35 = sDesc.dwUser1;
            dpSetSessionDesc(dp,local_84);
          }
          if (dpidPrevHost != 0xfa01) {
            DistributedObject::TakeOwnershipFromPlayer(0);
            DistributedObject::TakeOwnershipFromPlayer(dpidPrevHost);
          }
LAB_004dfc99:
          if (this->state == WAITING_FOR_SPAWNPOINT) {
            this->state = FINISHED_CREATE_PLAYER;
          }
        }
        else if (uVar20 == 0x3864) {
          sVar3 = *(short *)(this->buffer + 8);
          if (sVar3 == 0xc) {
            HandleGameInfoData(dp,myPlayerID,*(uint *)(this->buffer + 2),
                               *(void **)(this->buffer + 10));
          }
          else if (sVar3 == 0xd) {
            FlagDisplay::MakeTexture(&flagDisplay);
          }
          else if ((((sVar3 != 0xe) && (sVar3 != 0xf)) && (sVar3 != 0x10)) &&
                  ((sVar3 != 0x11 && (sVar3 != 0x12)))) {
            if (sVar3 == 0x13) {
              if (((*(int *)(this->buffer + 2) == 4) && (**(int **)(this->buffer + 10) == 0)) &&
                 (pcVar12 = NetPlayer_GetPlayerName(*(ushort *)(this->buffer + 6)),
                 pcVar12 != (char *)0x0)) {
                read_text_label("multi_message","defeated",message);
                DisplayMessage("%s %s");
              }
            }
            else if (((sVar3 != 0) && (this->state == NET_IS_RUNNING)) &&
                    (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) {
              DistributedObject_ReadPermState
                        (*(ushort *)(this->buffer + 6),*(uint *)(this->buffer + 2),
                         *(ushort *)(this->buffer + 8),*(void **)(this->buffer + 10));
            }
          }
        }
        else if (uVar20 == 0x3964) {
LAB_004dfa2f:
          DistributedObject_SetDP((dp_s *)0x0);
          if (dp_SESSIONLOST_PACKET_ID_CALLBACK != (_func___cdecl_void *)0x0) {
            (*dp_SESSIONLOST_PACKET_ID_CALLBACK)();
          }
          if (bStopGame != false) {
            return 1;
          }
          iNetEscapeSessionLostPacket = 1;
          goto LAB_004dfa5c;
        }
      }
      goto LAB_004df51d;
    }
    pNVar18 = NetPlayer::Find((ushort)local_5b8);
    uVar20 = (ushort)unaff_EDI;
    if (pNVar18 == (NetPlayer *)0x0) goto LAB_004df51d;
    if (*pcVar12 == '*') {
      if (((ushort)local_5b8 != myPlayerID) && (this->state == NET_IS_RUNNING)) {
        pAVar19 = AiMission::GetCurrent();
        uVar20 = (ushort)unaff_EDI;
        if (pAVar19 == (AiMission *)0x0) goto LAB_004e0583;
        local_5c8 = *(float *)(this->buffer + 2);
        iVar11 = lzo1x_decompress_asm(this->buffer + 6,local_5bc + -6,local_5b4,&local_5d0);
        uVar20 = (ushort)unaff_EDI;
        if (iVar11 == 0) {
          uVar13 = (uint)(byte)this->buffer[1];
          uVar25 = local_5d0 - uVar13;
          pcVar28 = local_5b4 + uVar13;
          if (uVar13 != 0) {
            uVar29 = CONCAT44(local_5b8,uVar13);
            pcVar12 = local_5b4;
LAB_004dfd33:
            Ordnance_Receive(pcVar12,(uint)uVar29,(ushort)((ulonglong)uVar29 >> 0x20));
          }
LAB_004dfd3b:
          NetPlayer::GotMessageFrom((ushort)local_5b8);
          if (0 < (int)uVar25) {
            DistributedObject_NEWReceiveTempState((ushort)local_5b8,pcVar28,uVar25,local_5c8);
          }
          goto LAB_004df51d;
        }
      }
    }
    else {
      if (*pcVar12 != '_') {
        uVar4 = *(ushort *)pcVar12;
        if (uVar4 < 0x4f51) {
          if (uVar4 == 0x4f50) {
            NetPlayer::GotMessageFrom((ushort)local_5b8);
            if ((((ushort)local_5b8 != myPlayerID) && (this->state == NET_IS_RUNNING)) &&
               (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) {
              DistributedObject_ReceiveTempState((ushort)local_5b8,this->buffer + 2,local_5bc - 2);
            }
            goto LAB_004df51d;
          }
          if (0x4752 < uVar4) {
            if (uVar4 < 0x4c4f) {
              p_Var15 = LAUNCH_PACKET_ID_CALLBACK;
              if (uVar4 != 0x4c4e) {
                if (uVar4 == 0x4b41) {
                  p_Var14 = AUTOKICKED_PACKET_ID_CALLBACK;
                  if (AUTOKICKED_PACKET_ID_CALLBACK == (_func___cdecl_void *)0x0) {
                    if ((bStopGame == false) && (bStopGame = true, NetEscapeUp == 0)) {
                      iNetEscapeGotKickedOut = 2;
LAB_004e0072:
                      bStopGame = true;
                      do_escape();
                    }
                    goto LAB_004df51d;
                  }
                }
                else {
                  if (uVar4 != 0x4b4b) {
                    if (uVar4 == 0x4b4d) {
                      RKillMessage((int)this->buffer[2],(int)this->buffer[3],this->buffer[4],
                                   (int)this->buffer[5]);
                    }
                    else {
                      if (uVar4 != 0x4b50) goto LAB_004e04fa;
                      if ((this->state == NET_IS_RUNNING) &&
                         (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) {
                        Increment_Player_Kills();
                      }
                    }
                    goto LAB_004df51d;
                  }
                  p_Var14 = KICKED_PACKET_ID_CALLBACK;
                  if (KICKED_PACKET_ID_CALLBACK == (_func___cdecl_void *)0x0) {
                    if ((bStopGame == false) && (bStopGame = true, NetEscapeUp == 0)) {
                      iNetEscapeGotKickedOut = 1;
                      goto LAB_004e0072;
                    }
                    goto LAB_004df51d;
                  }
                }
                (*p_Var14)();
                goto LAB_004df51d;
              }
            }
            else {
              p_Var15 = HOSTLAUNCH_PACKET_ID_CALLBACK;
              if (uVar4 != 0x4c53) {
                if (uVar4 == 0x4d47) {
                  if ((((ushort)local_5b8 != myPlayerID) && (this->state == NET_IS_RUNNING)) &&
                     (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) {
                    DistributedObject_ReceiveDamage
                              ((ushort)local_5b8,this->buffer + 2,local_5bc - 2);
                  }
                }
                else {
                  if (uVar4 != 0x4f43) goto LAB_004e04fa;
                  if ((((ushort)local_5b8 != myPlayerID) && (this->state == NET_IS_RUNNING)) &&
                     (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) {
                    DistributedObject_ReceiveCommand
                              ((ushort)local_5b8,this->buffer + 2,local_5bc - 2);
                  }
                }
                goto LAB_004df51d;
              }
            }
            if (p_Var15 != (_func___cdecl_void_ushort_ushort *)0x0) {
              (*p_Var15)((ushort)local_5b8,local_5cc._0_2_);
            }
            goto LAB_004df51d;
          }
          if (uVar4 == 0x4752) {
            PowerUp_GiveRemote(this->buffer + 2,local_5bc - 2);
            goto LAB_004df51d;
          }
          if (uVar4 < 0x4251) {
            if (uVar4 == 0x4250) {
              HandleBandwidth(this,(BANDWIDTH_PACKET *)(this->buffer + 2),local_5bc + -2);
              goto LAB_004df51d;
            }
            if (uVar4 == 0x3764) {
              hosting = true;
              this->dwLastSpawn = 0;
              this->dwLastPing = 0;
              this->dwNextPing = 300;
              DisplayMessage("%s");
              goto LAB_004dfc99;
            }
            if (uVar4 == 0x3964) goto LAB_004dfa2f;
            if (uVar4 == 0x414b) {
              NetPlayer::GotSyncPacketAck((ushort)local_5b8);
              goto LAB_004df51d;
            }
            if (uVar4 == 0x4154) {
              bVar7 = IsHost(uVar20);
              if (bVar7) {
                Team = (int)this->buffer[2] & 0xf;
              }
              goto LAB_004df51d;
            }
          }
          else {
            if (uVar4 == 0x4341) {
              if (*(ulong *)(this->buffer + 2) != dwCheaterPacket) {
                pcVar12 = NetPlayer_GetPlayerName((ushort)local_5b8);
                if (pcVar12 == (char *)0x0) {
                  pcVar12 = "%d MAY BE CHEATING";
                }
                else {
                  pcVar12 = "%s MAY BE CHEATING";
                }
                DisplayMessage(pcVar12);
              }
              goto LAB_004df51d;
            }
            if (uVar4 == 0x4343) {
              local_20 = 0x4341;
              local_1e = crc32exe(*(ulong *)(this->buffer + 2));
              Send(dp,(ushort)_myPlayerID,(ushort)local_5b8,0,&local_20,6);
              goto LAB_004df51d;
            }
            if (uVar4 == 0x4350) {
              iVar11 = dpGetPlayerName(dp,local_5b8,local_24);
              p_Var21 = CHAT_PACKET_ID_CALLBACK;
              if (CHAT_PACKET_ID_CALLBACK != (_func___cdecl_void_ushort_char_ptr_char_ptr_uint *)0x0
                 ) goto LAB_004dfec9;
              if (iVar11 == 0) {
                _snprintf(local_1b4,300,"<%s> %.*s",local_24,local_5bc + -2);
                Chat_DisplayMessage((ushort)local_5b8,local_1b4);
              }
              goto LAB_004df51d;
            }
          }
        }
        else {
          if (uVar4 < 0x5356) {
            if (uVar4 == 0x5355) {
              pcVar12 = "Host unlocked the game";
              pcVar28 = local_188;
              for (iVar11 = 5; iVar11 != 0; iVar11 = iVar11 + -1) {
                *(undefined4 *)pcVar28 = *(undefined4 *)pcVar12;
                pcVar12 = pcVar12 + 4;
                pcVar28 = pcVar28 + 4;
              }
              pcVar26 = pcVar28 + 2;
              pcVar23 = pcVar12 + 2;
              *(undefined2 *)pcVar28 = *(undefined2 *)pcVar12;
              uVar13 = 0xe9;
              puVar16 = local_171;
            }
            else {
              if (uVar4 < 0x534c) {
                if (uVar4 == 0x534b) {
                  pcVar12 = "Host kicked player %s";
                  pcVar28 = local_188;
                  for (iVar11 = 5; iVar11 != 0; iVar11 = iVar11 + -1) {
                    *(undefined4 *)pcVar28 = *(undefined4 *)pcVar12;
                    pcVar12 = pcVar12 + 4;
                    pcVar28 = pcVar28 + 4;
                  }
                  *(undefined2 *)pcVar28 = *(undefined2 *)pcVar12;
                  memset(&local_172,0xea00000000);
                  pcVar12 = "host_kicked";
                }
                else {
                  if (uVar4 == 0x4f52) {
                    if ((((ushort)local_5b8 != myPlayerID) && (this->state == NET_IS_RUNNING)) &&
                       (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) {
                      Ordnance_Receive(this->buffer + 2,local_5bc - 2,(ushort)local_5b8);
                    }
                    goto LAB_004df51d;
                  }
                  if (uVar4 == 0x5250) {
                    uVar10 = GetCurrentNetworkTime();
                    HandlePingReply(this,(ushort)local_5b8,(PINGREPLY_PACKET *)(this->buffer + 2),
                                    uVar10);
                    goto LAB_004df51d;
                  }
                  if (uVar4 != 0x5341) {
                    if (uVar4 != 0x5347) goto LAB_004e04fa;
                    if ((bStopGame == false) && (bStopGame = true, NetEscapeUp == 0))
                    goto LAB_004e07ff;
                    goto LAB_004df51d;
                  }
                  pcVar12 = "Host auto-kicked player %s";
                  pcVar28 = local_188;
                  for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
                    *(undefined4 *)pcVar28 = *(undefined4 *)pcVar12;
                    pcVar12 = pcVar12 + 4;
                    pcVar28 = pcVar28 + 4;
                  }
                  *(undefined2 *)pcVar28 = *(undefined2 *)pcVar12;
                  pcVar28[2] = pcVar12[2];
                  memset(local_16d,0xe500000000);
                  pcVar12 = "host_autokicked";
                }
                read_text_label("multi_message",pcVar12,local_188);
                dpGetPlayerName(dp,*(undefined2 *)(this->buffer + 2),local_24,0x19);
                DisplayMessage(local_188);
                goto LAB_004df51d;
              }
              if (uVar4 != 0x534c) {
                if (uVar4 == 0x5350) {
                  HandleSpawnPoint(this,(SPAWNPOINT_PACKET *)(this->buffer + 2));
                }
                else {
                  if (uVar4 != 0x5353) goto LAB_004e04fa;
                  SendSyncAckPacket(this,(ushort)local_5b8);
                  NetPlayer::GotSyncPacket((ushort)local_5b8);
                }
                goto LAB_004df51d;
              }
              pcVar23 = "Host locked the game";
              pcVar26 = local_188;
              for (iVar11 = 5; iVar11 != 0; iVar11 = iVar11 + -1) {
                *(undefined4 *)pcVar26 = *(undefined4 *)pcVar23;
                pcVar23 = pcVar23 + 4;
                pcVar26 = pcVar26 + 4;
              }
              uVar13 = 0xeb;
              puVar16 = &local_173;
            }
            *pcVar26 = *pcVar23;
            memset(puVar16,(ulonglong)uVar13 << 0x20);
            read_text_label("multi_message","host_locked",local_188);
            DisplayMessage("%s");
            goto LAB_004df51d;
          }
          if (uVar4 < 0x6f79) {
            if (uVar4 == 0x6f78) {
              fVar27 = 0.2;
            }
            else {
              if (uVar4 == 0x5370) {
                iVar11 = dpGetPlayerName(dp,local_5b8,local_24);
                p_Var21 = WHISPER_PACKET_ID_CALLBACK;
                if (WHISPER_PACKET_ID_CALLBACK ==
                    (_func___cdecl_void_ushort_char_ptr_char_ptr_uint *)0x0) {
                  if (iVar11 == 0) {
                    sprintf(local_88,"<From: %s> %.*s",local_24,local_5bc + -2);
                    Chat_DisplayMessage((ushort)local_5b8,local_88);
                  }
                }
                else {
LAB_004dfec9:
                  if (iVar11 == 0) {
                    pcVar12 = local_24;
                  }
                  else {
                    pcVar12 = "unknown";
                  }
                  (*p_Var21)((ushort)local_5b8,pcVar12,this->buffer + 2,local_5bc - 2);
                }
                goto LAB_004df51d;
              }
              if (uVar4 == 0x5450) {
                StartCockpitTimer(*(long *)(this->buffer + 2),0x78,0x3c);
                goto LAB_004df51d;
              }
              if (uVar4 == 0x616c) {
                iVar11 = *(int *)(this->buffer + 2);
                if ((((0 < iVar11) && (iVar11 < 0x10)) && (0 < *(int *)(this->buffer + 6))) &&
                   (*(int *)(this->buffer + 6) < 0x10)) {
                  pTVar17 = ::Team::GetTeam(iVar11);
                  ::Team::Ally(pTVar17,*(int *)(this->buffer + 6));
                }
                goto LAB_004df51d;
              }
              if (uVar4 != 0x6f69) goto LAB_004e04fa;
              fVar27 = 0.0;
            }
            Ordnance_ReceiveExpire(this->buffer + 2,local_5bc - 2,(ushort)local_5b8,fVar27);
            goto LAB_004df51d;
          }
          if (uVar4 == 0x736e) {
            HandleSnipe((ushort)local_5b8,(SNIPE_PACKET *)(this->buffer + 2));
            goto LAB_004e0579;
          }
          if (uVar4 == 0x756c) {
            iVar11 = *(int *)(this->buffer + 2);
            if (((0 < iVar11) && (iVar11 < 0x10)) &&
               ((0 < *(int *)(this->buffer + 6) && (*(int *)(this->buffer + 6) < 0x10)))) {
              pTVar17 = ::Team::GetTeam(iVar11);
              ::Team::UnAlly(pTVar17,*(int *)(this->buffer + 6));
            }
            goto LAB_004df51d;
          }
          if (uVar4 == 0x7878) {
            Ordnance_ManualDetonate(this->buffer + 2,local_5bc - 2,(ushort)local_5b8);
            goto LAB_004df51d;
          }
        }
LAB_004e04fa:
        if (MessageHandler != (_func___cdecl_int_ushort_char_ptr_int *)0x0) {
          (*MessageHandler)((ushort)local_5b8,pcVar12,local_5bc);
        }
        goto LAB_004df51d;
      }
      if (((ushort)local_5b8 != myPlayerID) && (this->state == NET_IS_RUNNING)) {
        pAVar19 = AiMission::GetCurrent();
        uVar20 = (ushort)unaff_EDI;
        if (pAVar19 != (AiMission *)0x0) {
          uVar13 = (uint)(byte)this->buffer[1];
          local_5c8 = *(float *)(this->buffer + 2);
          pcVar12 = this->buffer + 6;
          uVar25 = (local_5bc - uVar13) - 6;
          pcVar28 = pcVar12 + uVar13;
          if (uVar13 != 0) {
            uVar29 = CONCAT44(local_5b8,uVar13);
            goto LAB_004dfd33;
          }
          goto LAB_004dfd3b;
        }
      }
    }
  }
LAB_004e0583:
  DVar8 = local_5c0;
  if (dwNextGameInfoTime < local_5c0) {
    dwNextGameInfoTime = local_5c0 + 20000;
    bVar7 = IsHost(uVar20);
    if (bVar7) {
      SendGameInfoData(dp,(ushort)_myPlayerID);
    }
  }
  puVar1 = &this->dwNextSyncSend;
  if (DVar8 + 500 < *puVar1) {
    *puVar1 = DVar8;
  }
  if ((sentsyncs == 0) && (*puVar1 < DVar8)) {
    *puVar1 = DVar8 + 500;
    bVar7 = NetPlayer::SendOutSyncs(dp,(ushort)_myPlayerID);
    if (bVar7) {
      sentsyncs = 1;
    }
  }
  if (((this->bDoNetSync != false) && (this->state == NET_IS_RUNNING)) &&
     (bVar7 = NetPlayer::GotAllSyncs((ushort)_myPlayerID), bVar7)) {
    this->bDoNetSync = false;
  }
  if (((hosting != false) && (2000 < DVar8 - this->dwLastSpawn)) &&
     ((pNVar18 = NetPlayer::Find((ushort)_myPlayerID), pNVar18 != (NetPlayer *)0x0 &&
      (pNVar18->waitingForSpawnPoint == false)))) {
    this->dwLastSpawn = DVar8;
    NetPlayer::SendOutSpawnPoints(dp,(ushort)_myPlayerID);
  }
  if (((this->bDoNetSync == false) && (uVar13 = this->dwNextPing, uVar13 < DVar8 - this->dwLastPing)
      ) && (myPlayerID != 0xfa01)) {
    if (uVar13 < 3000) {
      this->dwNextPing = uVar13 + 10;
    }
    this->dwLastPing = DVar8;
    if ((ushort)_myPlayerID != 0) {
      NetPlayer::SendOutPings(dp,(ushort)_myPlayerID);
    }
    CheckFlags();
    SetMyFlag();
  }
  iVar11 = GetRunning();
  if ((((iVar11 == 5) && (this->state == NET_IS_RUNNING)) &&
      (pAVar19 = AiMission::GetCurrent(), pAVar19 != (AiMission *)0x0)) &&
     (DVar8 = Get_TimeNow(), dwPowerUpCheck < DVar8)) {
    dwPowerUpCheck = DVar8 + 60000;
    LoadPlayerData();
  }
  if (VictoryTime == 0.0) {
    if ((bSyncJoin == false) || (bVar7 = NetPlayer::IWon(), !bVar7)) {
      if (VictoryTime != 0.0) goto LAB_004e081c;
    }
    else {
      dpEnableNewPlayers(dp);
      fVar27 = Get_TimeLocal();
      VictoryTime = fVar27 + 5.0;
    }
  }
  else {
LAB_004e081c:
    fVar27 = Get_TimeLocal();
    if (VictoryTime < fVar27) {
      if (bStopGame != false) goto LAB_004e0766;
LAB_004dfa5c:
      if (NetEscapeUp != 0) {
        bStopGame = true;
        return 1;
      }
LAB_004e07ff:
      bStopGame = true;
      do_escape();
      return 1;
    }
  }
  if (bStopGame == false) {
    return 1;
  }
LAB_004e0766:
  if (hosting == false) {
    return 0;
  }
  iVar11 = GetRunning();
  if (iVar11 != 5) {
    return 0;
  }
  local_18[0] = 0x5347;
  Send(dp,(ushort)_myPlayerID,0,1,local_18,4);
  dpEnableNewPlayers(dp,0);
  return 0;
}
