/*
 * Entry: 00556f33
 * Name: JoinGameSession
 * Namespace: Global
 * Signature: int JoinGameSession(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl JoinGameSession(HWND__ *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  char *pcVar5;
  char *pcVar6;
  char local_118 [20];
  undefined1 local_104;
  undefined1 local_103 [103];
  undefined1 local_9c [131];
  undefined4 uStack_19;
  undefined1 auStack_14 [6];
  undefined1 local_e;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_9c;
  Creator = false;
  if (bGameSetup == 0) {
    Net::myPlayerID = 0xfa01;
    iVar3 = 0;
    do {
      *(byte *)((int)&uStack_19 + iVar3 + 1) = dp_session_game.szUserField[iVar3] & 0x7f;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 10);
    local_e = 0;
    puVar2 = &uStack_19;
    do {
      puVar4 = puVar2;
      puVar2 = (undefined4 *)((int)puVar4 + 1);
    } while (*(char *)((int)puVar4 + 1) != '\0');
    *(undefined4 *)((int)puVar4 + 1) = 0x6e7a622e;
    *(undefined1 *)((int)puVar4 + 5) = 0;
    iVar3 = ItemExists((char *)((int)&uStack_19 + 1));
    uVar1 = local_118._8_4_;
    if (iVar3 == 0) {
      pcVar6 = "Mission %s not found";
      pcVar5 = local_118;
      for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar5 = pcVar5 + 4;
      }
      *pcVar5 = *pcVar6;
      memset(local_103,0,0xeb);
      read_text_label("multi_error","missing_map",local_118);
      do_error(param_1,local_118);
    }
    else {
      if ((dp_session_game.field7_0x15.flags._0_1_ & 4) == 0) {
        builtin_strncpy(local_118,"Game Locked",0xc);
        memset(local_118 + 0xc,0,0xf4);
        pcVar6 = "game_locked";
      }
      else if (dp_session_game.field6_0x13.currentPlayers < dp_session_game.field5_0x11.maxPlayers)
      {
        dp_result = dpOpen(Net::dp,&dp_session_game,dpJoinGameOpenCallback,param_1);
        if (dp_result == 0) goto LAB_005570d5;
        pcVar6 = "Unable to join game";
        pcVar5 = local_118;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined4 *)pcVar5 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar5 = pcVar5 + 4;
        }
        memset(&local_104,0,0xec);
        pcVar6 = "fail_join_game";
      }
      else {
        builtin_strncpy(local_118,"Game Full",10);
        local_118._10_2_ = SUB42(uVar1,2);
        memset(local_118 + 10,0,0xf6);
        pcVar6 = "game_full";
      }
      read_text_label("multi_error",pcVar6,local_118);
      do_error(param_1,local_118);
    }
    iVar3 = 0;
  }
  else {
LAB_005570d5:
    iVar3 = 1;
  }
  return iVar3;
}
