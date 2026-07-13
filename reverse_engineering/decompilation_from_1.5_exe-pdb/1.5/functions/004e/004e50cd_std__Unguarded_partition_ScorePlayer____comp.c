/*
 * Entry: 004e50cd
 * Name: std::_Unguarded_partition<ScorePlayer_*_*,comp>
 * Namespace: std
 * Signature: pair<ScorePlayer_*_*,ScorePlayer_*_*> _Unguarded_partition<ScorePlayer_*_*,comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<ScorePlayer_*_*,ScorePlayer_*_*> __cdecl
std::_Unguarded_partition<ScorePlayer_*_*,comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,comp param_3)

{
  ScorePlayer *pSVar1;
  ScorePlayer *pSVar2;
  ScorePlayer *pSVar3;
  ScorePlayer *pSVar4;
  ScorePlayer *extraout_EDX;
  ScorePlayer *extraout_EDX_00;
  ScorePlayer *extraout_EDX_01;
  ScorePlayer *extraout_EDX_02;
  ScorePlayer *pSVar5;
  ScorePlayer *pSVar6;
  pair<ScorePlayer_*_*,ScorePlayer_*_*> pVar7;
  undefined3 in_stack_0000000d;
  comp in_stack_00000010;
  ScorePlayer *local_10;
  ScorePlayer *local_c;
  ScorePlayer *local_8;
  
  pSVar3 = (ScorePlayer *)
           (param_2 +
           (((int)_param_3 - (int)param_2 >> 2) - ((int)_param_3 - (int)param_2 >> 0x1f) >> 1));
  _Median<ScorePlayer_*_*,comp>
            (param_2,(ScorePlayer **)pSVar3,(ScorePlayer **)(_param_3[-1].caName + 0x18),
             in_stack_00000010);
  pSVar4 = (ScorePlayer *)&pSVar3->iTeam;
  while (local_10 = pSVar3, param_2 < local_10) {
    pSVar5 = *(ScorePlayer **)local_10;
    pSVar6 = *(ScorePlayer **)(local_10[-1].caName + 0x18);
    if ((pSVar5->iKills - pSVar5->iDeaths < pSVar6->iKills - pSVar6->iDeaths) ||
       (pSVar3 = (ScorePlayer *)(local_10[-1].caName + 0x18),
       pSVar6->iKills - pSVar6->iDeaths < pSVar5->iKills - pSVar5->iDeaths)) break;
  }
  pSVar3 = pSVar4;
  local_8 = pSVar4;
  pSVar5 = local_10;
  if (pSVar4 < _param_3) {
    pSVar6 = *(ScorePlayer **)local_10;
    do {
      pSVar1 = *(ScorePlayer **)pSVar4;
      pSVar3 = pSVar4;
      local_8 = pSVar4;
      if ((pSVar6->iKills - pSVar6->iDeaths < pSVar1->iKills - pSVar1->iDeaths) ||
         (pSVar1->iKills - pSVar1->iDeaths < pSVar6->iKills - pSVar6->iDeaths)) break;
      pSVar4 = (ScorePlayer *)&pSVar4->iTeam;
      pSVar3 = pSVar4;
      local_8 = pSVar4;
    } while (pSVar4 < _param_3);
  }
joined_r0x004e5179:
  do {
    pSVar6 = local_10;
    if (_param_3 <= local_8) {
LAB_004e51f8:
      while (local_10 = pSVar6, param_2 < local_10) {
        pSVar1 = *(ScorePlayer **)pSVar5;
        pSVar6 = (ScorePlayer *)(local_10[-1].caName + 0x18);
        pSVar2 = *(ScorePlayer **)pSVar6;
        pSVar4 = (ScorePlayer *)(pSVar2->iKills - pSVar2->iDeaths);
        if ((int)pSVar4 <= pSVar1->iKills - pSVar1->iDeaths) {
          pSVar4 = (ScorePlayer *)(pSVar1->iKills - pSVar1->iDeaths);
          if (pSVar2->iKills - pSVar2->iDeaths < (int)pSVar4) break;
          pSVar5 = (ScorePlayer *)(pSVar5[-1].caName + 0x18);
          swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)pSVar6);
          pSVar4 = extraout_EDX_00;
        }
      }
      if (local_10 == (ScorePlayer *)param_2) {
        if (local_8 == _param_3) {
          *param_1 = pSVar5;
          param_1[1] = pSVar3;
          pVar7.second = (ScorePlayer **)pSVar4;
          pVar7.first = param_1;
          return pVar7;
        }
        if (pSVar3 != local_8) {
          swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)pSVar3);
        }
        pSVar6 = (ScorePlayer *)&pSVar5->iTeam;
        pSVar4 = local_8;
        local_c = (ScorePlayer *)&pSVar3->iTeam;
        local_8 = (ScorePlayer *)&local_8->iTeam;
      }
      else {
        local_10 = (ScorePlayer *)(local_10[-1].caName + 0x18);
        if (local_8 != _param_3) {
          swap<ScorePlayer_*>((ScorePlayer **)local_8,(ScorePlayer **)local_10);
          pSVar4 = extraout_EDX_02;
          local_8 = (ScorePlayer *)&local_8->iTeam;
          goto joined_r0x004e5179;
        }
        pSVar6 = (ScorePlayer *)(pSVar5[-1].caName + 0x18);
        if (local_10 != pSVar6) {
          swap<ScorePlayer_*>((ScorePlayer **)local_10,(ScorePlayer **)pSVar6);
        }
        pSVar4 = (ScorePlayer *)(pSVar3[-1].caName + 0x18);
        pSVar5 = pSVar6;
        local_c = pSVar4;
      }
      swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)pSVar4);
      pSVar4 = extraout_EDX_01;
      pSVar3 = local_c;
      pSVar5 = pSVar6;
      goto joined_r0x004e5179;
    }
    pSVar1 = *(ScorePlayer **)local_8;
    pSVar2 = *(ScorePlayer **)pSVar5;
    pSVar4 = (ScorePlayer *)(pSVar2->iKills - pSVar2->iDeaths);
    local_c = pSVar3;
    if ((int)pSVar4 <= pSVar1->iKills - pSVar1->iDeaths) {
      pSVar4 = (ScorePlayer *)(pSVar1->iKills - pSVar1->iDeaths);
      if (pSVar2->iKills - pSVar2->iDeaths < (int)pSVar4) goto LAB_004e51f8;
      local_c = (ScorePlayer *)&pSVar3->iTeam;
      swap<ScorePlayer_*>((ScorePlayer **)pSVar3,(ScorePlayer **)local_8);
      pSVar4 = extraout_EDX;
    }
    pSVar3 = local_c;
    local_8 = (ScorePlayer *)&local_8->iTeam;
  } while( true );
}
