/*
 * Entry: 004e4f46
 * Name: std::_Unguarded_partition<ScorePlayer_*_*,lives_comp>
 * Namespace: std
 * Signature: pair<ScorePlayer_*_*,ScorePlayer_*_*> _Unguarded_partition<ScorePlayer_*_*,lives_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, lives_comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<ScorePlayer_*_*,ScorePlayer_*_*> __cdecl
std::_Unguarded_partition<ScorePlayer_*_*,lives_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,lives_comp param_3)

{
  int iVar1;
  ScorePlayer *extraout_EDX;
  ScorePlayer *pSVar2;
  ScorePlayer *extraout_EDX_00;
  ScorePlayer *extraout_EDX_01;
  ScorePlayer *pSVar3;
  ScorePlayer *pSVar4;
  ScorePlayer *pSVar5;
  ScorePlayer *pSVar6;
  pair<ScorePlayer_*_*,ScorePlayer_*_*> pVar7;
  undefined3 in_stack_0000000d;
  lives_comp in_stack_00000010;
  ScorePlayer *pSVar8;
  ScorePlayer *local_c;
  ScorePlayer *local_8;
  
  pSVar3 = (ScorePlayer *)
           (param_2 +
           (((int)_param_3 - (int)param_2 >> 2) - ((int)_param_3 - (int)param_2 >> 0x1f) >> 1));
  _Median<ScorePlayer_*_*,lives_comp>
            (param_2,(ScorePlayer **)pSVar3,(ScorePlayer **)(_param_3[-1].caName + 0x18),
             in_stack_00000010);
  pSVar2 = (ScorePlayer *)&pSVar3->iTeam;
  while (pSVar6 = pSVar3, param_2 < pSVar6) {
    iVar1 = (*(ScorePlayer **)(pSVar6[-1].caName + 0x18))->iLives;
    if (((*(ScorePlayer **)pSVar6)->iLives < iVar1) ||
       (pSVar3 = (ScorePlayer *)(pSVar6[-1].caName + 0x18),
       iVar1 < (*(ScorePlayer **)pSVar6)->iLives)) break;
  }
  pSVar3 = pSVar2;
  local_c = pSVar6;
  local_8 = pSVar2;
  if (pSVar2 < _param_3) {
    do {
      pSVar2 = local_8;
      pSVar3 = local_8;
      if (((*(ScorePlayer **)pSVar6)->iLives < (*(ScorePlayer **)local_8)->iLives) ||
         ((*(ScorePlayer **)local_8)->iLives < (*(ScorePlayer **)pSVar6)->iLives)) break;
      pSVar2 = (ScorePlayer *)&local_8->iTeam;
      pSVar3 = pSVar2;
      local_8 = pSVar2;
    } while (pSVar2 < _param_3);
  }
LAB_004e4fe2:
  do {
    pSVar5 = pSVar6;
    if (_param_3 <= pSVar3) {
joined_r0x004e4fec:
      while (pSVar8 = local_c, param_2 < pSVar8) {
        local_c = (ScorePlayer *)(pSVar8[-1].caName + 0x18);
        if ((*(ScorePlayer **)local_c)->iLives <= (*(ScorePlayer **)pSVar5)->iLives) {
          if ((*(ScorePlayer **)local_c)->iLives < (*(ScorePlayer **)pSVar5)->iLives) break;
          pSVar5 = (ScorePlayer *)(pSVar5[-1].caName + 0x18);
          swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)local_c);
          pSVar2 = extraout_EDX_00;
        }
      }
      if (pSVar8 == (ScorePlayer *)param_2) {
        if (pSVar3 == _param_3) {
          *param_1 = pSVar5;
          param_1[1] = local_8;
          pVar7.second = (ScorePlayer **)pSVar2;
          pVar7.first = param_1;
          return pVar7;
        }
        if (local_8 != pSVar3) {
          swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)local_8);
        }
        pSVar6 = (ScorePlayer *)&pSVar5->iTeam;
        pSVar4 = (ScorePlayer *)&pSVar3->iTeam;
        pSVar2 = pSVar3;
        local_c = pSVar8;
        local_8 = (ScorePlayer *)&local_8->iTeam;
      }
      else {
        pSVar8 = (ScorePlayer *)(pSVar8[-1].caName + 0x18);
        pSVar2 = pSVar3;
        local_c = pSVar8;
        if (pSVar3 != _param_3) goto LAB_004e4fd8;
        pSVar6 = (ScorePlayer *)(pSVar5[-1].caName + 0x18);
        if (pSVar8 != pSVar6) {
          swap<ScorePlayer_*>((ScorePlayer **)pSVar8,(ScorePlayer **)pSVar6);
        }
        pSVar2 = (ScorePlayer *)(local_8[-1].caName + 0x18);
        pSVar4 = pSVar3;
        pSVar5 = pSVar6;
        local_8 = pSVar2;
      }
      swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)pSVar2);
      pSVar2 = extraout_EDX_01;
      pSVar3 = pSVar4;
      goto LAB_004e4fe2;
    }
    if ((*(ScorePlayer **)pSVar6)->iLives <= (*(ScorePlayer **)pSVar3)->iLives) {
      if ((*(ScorePlayer **)pSVar6)->iLives < (*(ScorePlayer **)pSVar3)->iLives)
      goto joined_r0x004e4fec;
      pSVar2 = local_8;
      pSVar8 = pSVar3;
      local_8 = (ScorePlayer *)&local_8->iTeam;
LAB_004e4fd8:
      swap<ScorePlayer_*>((ScorePlayer **)pSVar2,(ScorePlayer **)pSVar8);
      pSVar2 = extraout_EDX;
      pSVar6 = pSVar5;
    }
    pSVar3 = (ScorePlayer *)&pSVar3->iTeam;
  } while( true );
}
