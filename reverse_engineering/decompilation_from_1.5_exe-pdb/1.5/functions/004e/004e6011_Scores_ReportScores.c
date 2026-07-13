/*
 * Entry: 004e6011
 * Name: Scores_ReportScores
 * Namespace: Global
 * Signature: void Scores_ReportScores(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scores_ReportScores(void)

{
  ScorePlayer *pSVar1;
  bool bVar2;
  ScorePlayer **ppSVar3;
  Team *pTVar4;
  undefined4 uVar5;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_1c;
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> local_14;
  Team *local_c;
  int local_8;
  
  dpEnumPlayers(Net::dp,0,dpEnumPlayersCallback,0,0);
  ScorePlayer::Sort();
  local_c = GameObject::userTeamList;
  dax7(Net::dp,0);
  local_8 = 1;
  std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            (&local_1c,ScorePlayer::playerV._Myfirst,(_Container_base_aux *)&ScorePlayer::playerV);
  local_14._padding_ = local_1c._padding_;
  local_14._Myptr = local_1c._Myptr;
  std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
  _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
            (&local_1c,ScorePlayer::playerV._Mylast,(_Container_base_aux *)&ScorePlayer::playerV);
  bVar2 = std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator==
                    (&local_14,&local_1c);
  while (!bVar2) {
    ppSVar3 = std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator*
                        (&local_14);
    pSVar1 = *ppSVar3;
    if (pSVar1 != (ScorePlayer *)0x0) {
      if ((((local_8 == 1) &&
           (1 < (uint)((int)ScorePlayer::playerV._Mylast - (int)ScorePlayer::playerV._Myfirst >> 2))
           ) && (stratgy_game != 0)) && (pTVar4 = Team::GetTeam(pSVar1->iTeam), local_c == pTVar4))
      {
        uVar5 = 1;
      }
      else {
        uVar5 = 0;
      }
      dax8(Net::dp,pSVar1->dpid,0x1106,uVar5);
      dax8(Net::dp,pSVar1->dpid,0x1103,local_8);
      dax8(Net::dp,pSVar1->dpid,0x1104,pSVar1->iKills);
      dax8(Net::dp,pSVar1->dpid,0x1105,pSVar1->iDeaths);
      local_8 = local_8 + 1;
    }
    std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator++(&local_14)
    ;
    std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::
    _Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
              (&local_1c,ScorePlayer::playerV._Mylast,(_Container_base_aux *)&ScorePlayer::playerV);
    bVar2 = std::_Vector_const_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator==
                      (&local_14,&local_1c);
  }
  ScorePlayer::Cleanup();
  dax9(Net::dp);
  return;
}
