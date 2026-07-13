/*
 * Entry: 004e5da3
 * Name: Scores_UpdateScores
 * Namespace: Global
 * Signature: void Scores_UpdateScores(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scores_UpdateScores(void)

{
  ScorePlayer *pSVar1;
  int iVar2;
  bool bVar3;
  ushort uVar4;
  ScorePlayer **ppSVar5;
  Team *pTVar6;
  ulong uVar7;
  char (*_Dest) [80];
  long lVar8;
  char *pcVar9;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_24;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_1c;
  NetPlayer *local_14;
  Team *local_10;
  ulong local_c;
  ulong local_8;
  
  TotalKills = 0;
  dpEnumPlayers(Net::dp,0,dpEnumPlayersCallback,0,0);
  ScorePlayer::Sort();
  score_count = 0;
  score_has_ping = 0;
  local_10 = GameObject::userTeamList;
  std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            (&local_24,ScorePlayer::playerV._Myfirst,(_Container_base_aux *)&ScorePlayer::playerV);
  local_1c._padding_ = local_24._padding_;
  local_1c._Myptr = local_24._Myptr;
  std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            (&local_24,ScorePlayer::playerV._Mylast,(_Container_base_aux *)&ScorePlayer::playerV);
  bVar3 = std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator==
                    (&local_1c,&local_24);
  do {
    if (bVar3) {
      ScorePlayer::Cleanup();
      return;
    }
    ppSVar5 = std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator*
                        (&local_1c);
    pSVar1 = *ppSVar5;
    if (pSVar1 != (ScorePlayer *)0x0) {
      if (TotalKills < pSVar1->iKills) {
        TotalKills = pSVar1->iKills;
      }
      if ((((score_count == 0) &&
           (1 < (uint)((int)ScorePlayer::playerV._Mylast - (int)ScorePlayer::playerV._Myfirst >> 2))
           ) && (stratgy_game != 0)) && (pTVar6 = Team::GetTeam(pSVar1->iTeam), local_10 == pTVar6))
      {
        iYouWonStratgy = 1;
      }
      local_8 = 0;
      local_c = 0;
      local_14 = NetPlayer::Find(pSVar1->dpid);
      if ((local_14 != (NetPlayer *)0x0) && (uVar4 = Net_GetMyPlayerID(), pSVar1->dpid != uVar4)) {
        uVar7 = NetPlayer::GetAveragePingTime(local_14);
        local_8 = 9999;
        if ((int)uVar7 < 10000) {
          local_8 = uVar7;
        }
        local_c = NetPlayer::GetAverageLoss(local_14);
        score_has_ping = 1;
      }
      lVar8 = DisplayInterface::colorGrey;
      if (((local_10 != (Team *)0x0) &&
          (pTVar6 = Team::GetTeam(pSVar1->iTeam), lVar8 = DisplayInterface::colorGreen,
          local_10 != pTVar6)) &&
         (bVar3 = Team::FriendP(local_10,pSVar1->iTeam), lVar8 = DisplayInterface::colorBlue, !bVar3
         )) {
        lVar8 = DisplayInterface::colorRed;
      }
      iVar2 = score_count;
      score_color[score_count] = lVar8;
      _Dest = score_text + iVar2;
      if (king_of_the_hill_game == 0) {
        if (stratgy_game != 0) {
          pcVar9 = pSVar1->caLives;
          goto LAB_004e5f3e;
        }
        if (local_8 == 0) {
          sprintf(*_Dest,"%s\t%s\t%s\t%s",pSVar1->caTeam,pSVar1->caName,pSVar1->caDeaths,
                  pSVar1->caKills);
        }
        else {
          sprintf(*_Dest,"%s\t%s\t%s\t%s\t%lu\t%lu",pSVar1->caTeam,pSVar1->caName,pSVar1->caDeaths,
                  pSVar1->caKills,local_8,local_c);
        }
      }
      else {
        pcVar9 = pSVar1->caTimeInZone;
LAB_004e5f3e:
        if (local_8 == 0) {
          sprintf(*_Dest,"%s\t%s\t%s\t%s\t%s",pSVar1->caTeam,pSVar1->caName,pSVar1->caDeaths,
                  pSVar1->caKills,pcVar9);
        }
        else {
          sprintf(*_Dest,"%s\t%s\t%s\t%s\t%s\t%lu\t%lu",pSVar1->caTeam,pSVar1->caName,
                  pSVar1->caDeaths,pSVar1->caKills,pcVar9,local_8,local_c);
        }
      }
      score_count = score_count + 1;
    }
    std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++(&local_1c)
    ;
    std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
    _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
              (&local_24,ScorePlayer::playerV._Mylast,(_Container_base_aux *)&ScorePlayer::playerV);
    bVar3 = std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator==
                      (&local_1c,&local_24);
  } while( true );
}
