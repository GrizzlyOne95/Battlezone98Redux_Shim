/*
 * Entry: 00552e90
 * Name: write_score
 * Namespace: Global
 * Signature: void write_score(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl write_score(char *param_1)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *local_710;
  char local_708 [120];
  undefined1 local_690 [136];
  char local_608 [256];
  char local_508 [256];
  char local_408 [256];
  char local_308 [256];
  char local_208 [256];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_690;
  builtin_strncpy(local_508,"Team",5);
  memset(local_508 + 5,0,0xfb);
  builtin_strncpy(local_308,"Player",7);
  memset(local_308 + 7,0,0xf9);
  builtin_strncpy(local_108,"Deaths",7);
  memset(local_108 + 7,0,0xf9);
  builtin_strncpy(local_208,"Kills",6);
  memset(local_208 + 6,0,0xfa);
  builtin_strncpy(local_708,"TimeInZone",0xb);
  memset(local_708 + 0xb,0,0xf5);
  builtin_strncpy(local_408,"Ping",5);
  memset(local_408 + 5,0,0xfb);
  builtin_strncpy(local_608,"Lives",6);
  memset(local_608 + 6,0,0xfa);
  read_text_label("multi_common","team",local_508);
  read_text_label("multi_common","player",local_308);
  read_text_label("multi_common","deaths",local_108);
  read_text_label("multi_common","kills",local_208);
  read_text_label("multi_common","time_in_zone",local_708);
  read_text_label("escape","ping_score",local_408);
  read_text_label("multi_common","lives",local_608);
  Scores_UpdateScores();
  if ((stratgy_game != 0) && (iNetEscapeSetMessage == 0)) {
    if ((iYouWonStratgy == 1) && ((bVar2 = NetPlayer::IWon(), bVar2 && (Net::bSyncJoin != false))))
    {
      iNetEscapeEndMessage = 1;
    }
    else {
      if (0 < Net::iLivesLeft) goto LAB_0055306d;
      iNetEscapeEndMessage = -1;
    }
    iNetEscapeSetMessage = 1;
  }
LAB_0055306d:
  if (king_of_the_hill_game == 0) {
    if (stratgy_game == 0) {
      sprintf(param_1,"%s\t%s\t%s\t%s\t%s\n\n",local_508,local_308,local_108,local_208,local_408);
      goto LAB_005530ec;
    }
    pcVar3 = local_608;
  }
  else {
    pcVar3 = local_708;
  }
  sprintf(param_1,"%s\t%s\t%s\t%s\t%s\t%s\n\n",local_508,local_308,local_108,local_208,pcVar3);
LAB_005530ec:
  iVar6 = 0;
  if (0 < score_count) {
    local_710 = score_text[0];
    pcVar3 = local_710;
    do {
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      uVar4 = (int)pcVar3 - (int)local_710;
      pcVar3 = param_1 + -1;
      do {
        pcVar7 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar7 != '\0');
      pcVar7 = local_710;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar3 = pcVar3 + 1;
      }
      pcVar7 = param_1 + -1;
      do {
        pcVar3 = pcVar7 + 1;
        pcVar7 = pcVar7 + 1;
      } while (*pcVar3 != '\0');
      pcVar3 = local_710 + 0x50;
      iVar6 = iVar6 + 1;
      *(char (*) [2])pcVar7 = (char  [2])0xa;
      local_710 = pcVar3;
    } while (iVar6 < score_count);
  }
  return;
}
