/*
 * Entry: 0055a5f2
 * Name: SyncTimer
 * Namespace: Global
 * Signature: void SyncTimer(int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SyncTimer(int *param_1)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  undefined1 *puVar4;
  Chat *this;
  Chat *this_00;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 uVar9;
  undefined1 local_534 [4];
  undefined4 local_530;
  uint local_52c;
  int local_528;
  ushort local_524;
  float local_522;
  short local_51c;
  void *local_51a;
  undefined1 local_4b8 [916];
  char local_124 [2];
  char acStack_122 [19];
  undefined1 local_10f;
  undefined1 local_10e;
  undefined1 local_10d [4];
  undefined1 local_109 [229];
  char local_24 [4];
  undefined2 local_20;
  undefined1 local_1e;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_4b8;
  local_528 = 0;
  do {
    local_52c = 0x400;
    iVar3 = dpReceive(Net::dp,&local_530,local_534,0,&local_524,&local_52c);
    if (iVar3 == 0) {
      local_528 = 0;
LAB_0055a67f:
      if (iVar3 == 0) {
        uVar2 = (ushort)local_530;
        if (uVar2 == 0) {
          if (local_524 == 0x3164) {
            uVar2 = Net_GetMyPlayerID();
            if (local_522._0_2_ != uVar2) {
              uVar2 = Net_GetMyPlayerID();
              bVar1 = PlayerList::IsHost((PlayerList *)&playersInSyncGame,uVar2);
              if (bVar1) {
                iVar3 = SyncGamePlayerList::GetTeam(&playersInSyncGame,SUB42(local_522,0));
                local_1e = (undefined1)iVar3;
                local_20 = 0x4154;
                Net::Send(Net::dp,Net::myPlayerID,SUB42(local_522,0),1,&local_20,3);
              }
            }
          }
          else if (local_524 != 0x3264) {
            if (local_524 == 0x3764) {
LAB_0055a6c2:
              bSessionDisconnected = true;
            }
            else if (local_524 == 0x3864) {
              if (local_51c == 0xc) {
                Net::HandleGameInfoData(Net::dp,Net::myPlayerID,(uint)local_522,local_51a);
              }
            }
            else if (local_524 == 0x3964) goto LAB_0055a6c2;
          }
        }
        else if (((char)local_524 == '_') || ((char)local_524 == '*')) {
LAB_0055a7be:
          gameclock = local_522;
          SyncGamePlayerList::InGame(&playersInSyncGame,uVar2);
        }
        else if (local_524 < 0x5342) {
          if (local_524 == 0x5341) {
            if (system_on != 0) {
              pcVar8 = "Host auto-kicked player %s";
              pcVar7 = local_124;
              for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
                *(undefined4 *)pcVar7 = *(undefined4 *)pcVar8;
                pcVar8 = pcVar8 + 4;
                pcVar7 = pcVar7 + 4;
              }
              *(undefined2 *)pcVar7 = *(undefined2 *)pcVar8;
              pcVar7[2] = pcVar8[2];
              memset(local_109,0,0xe5);
              pcVar8 = "host_autokicked";
LAB_0055aa0c:
              read_text_label("multi_message",pcVar8,local_124);
              dpGetPlayerName(Net::dp,local_522,local_24,0x19);
              Chat::Append(this_00,(char *)&chatGame);
            }
          }
          else if (local_524 == 0x4154) {
            bVar1 = PlayerList::IsHost((PlayerList *)&playersInSyncGame,uVar2);
            if (bVar1) {
              Net::Team = (int)local_522._0_1_ & 0xf;
            }
          }
          else if (local_524 == 0x4350) {
            bVar1 = PlayerList::IsMuted((PlayerList *)&playersInSyncGame,uVar2);
            if (!bVar1) {
              dpGetPlayerName(Net::dp,local_530,local_24,0x19);
              Chat::AppendMessage((Chat *)&chatGame,local_24,local_52c,(char *)&local_522);
            }
          }
          else if (local_524 == 0x4b41) {
            *param_1 = 2;
          }
          else if (local_524 == 0x4b4b) {
            *param_1 = 1;
          }
          else if (local_524 == 0x4c4e) {
            SyncGamePlayerList::Launch(&playersInSyncGame,uVar2);
          }
          else if (local_524 == 0x4c53) {
            Net_CRC = (ulong)local_522;
            SyncGamePlayerList::HostLaunch(&playersInSyncGame,uVar2);
          }
          else if (local_524 == 0x4f50) goto LAB_0055a7be;
        }
        else if (local_524 == 0x5347) {
          bSessionEnded = true;
        }
        else if (local_524 == 0x534b) {
          if (system_on != 0) {
            pcVar8 = "Host kicked player %s";
            pcVar7 = local_124;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)pcVar7 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar7 = pcVar7 + 4;
            }
            *(undefined2 *)pcVar7 = *(undefined2 *)pcVar8;
            memset(&local_10e,0,0xea);
            pcVar8 = "host_kicked";
            goto LAB_0055aa0c;
          }
        }
        else if (local_524 == 0x534c) {
          if (system_on != 0) {
            pcVar8 = "Host locked the game";
            pcVar7 = local_124;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)pcVar7 = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              pcVar7 = pcVar7 + 4;
            }
            uVar9 = 0xeb;
            puVar4 = &local_10f;
LAB_0055a996:
            *pcVar7 = *pcVar8;
            memset(puVar4,0,uVar9);
            read_text_label("multi_message","host_locked",local_124);
            Chat::Append(this,(char *)&chatGame);
          }
        }
        else if (local_524 == 0x5355) {
          if (system_on != 0) {
            pcVar5 = "Host unlocked the game";
            pcVar6 = local_124;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
              pcVar5 = pcVar5 + 4;
              pcVar6 = pcVar6 + 4;
            }
            pcVar7 = pcVar6 + 2;
            pcVar8 = pcVar5 + 2;
            *(undefined2 *)pcVar6 = *(undefined2 *)pcVar5;
            uVar9 = 0xe9;
            puVar4 = local_10d;
            goto LAB_0055a996;
          }
        }
        else if (local_524 == 0x5370) {
          bVar1 = PlayerList::IsMuted((PlayerList *)&playersInSyncGame,uVar2);
          if (!bVar1) {
            dpGetPlayerName(Net::dp,local_530,local_24,0x19);
            Chat::AppendWhisper((Chat *)&chatGame,local_24,local_52c,(char *)&local_522);
          }
        }
        else if (local_524 == 0x6e6e) {
          SyncGamePlayerList::NoLaunch(&playersInSyncGame,uVar2);
        }
      }
    }
    else {
      if (iVar3 != 2) {
        if (iVar3 == 0xc) {
          bModemNoResponse = true;
          return;
        }
        if (iVar3 == 0x10) {
          bHostNotResponding = true;
          return;
        }
        goto LAB_0055a67f;
      }
      local_528 = local_528 + 1;
    }
    if (2 < local_528) {
      return;
    }
  } while( true );
}
