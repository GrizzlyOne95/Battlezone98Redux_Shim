/*
 * Entry: 004e4d7b
 * Name: std::_Unguarded_partition<ScorePlayer_*_*,king_comp>
 * Namespace: std
 * Signature: pair<ScorePlayer_*_*,ScorePlayer_*_*> _Unguarded_partition<ScorePlayer_*_*,king_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, king_comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<ScorePlayer_*_*,ScorePlayer_*_*> __cdecl
std::_Unguarded_partition<ScorePlayer_*_*,king_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,king_comp param_3)

{
  bool bVar1;
  ScorePlayer **extraout_EDX;
  ScorePlayer **extraout_EDX_00;
  ScorePlayer **extraout_EDX_01;
  ScorePlayer **extraout_EDX_02;
  ScorePlayer **extraout_EDX_03;
  ScorePlayer **extraout_EDX_04;
  ScorePlayer **extraout_EDX_05;
  ScorePlayer **extraout_EDX_06;
  ScorePlayer **extraout_EDX_07;
  ScorePlayer **extraout_EDX_08;
  ScorePlayer **extraout_EDX_09;
  ScorePlayer **ppSVar2;
  ScorePlayer **extraout_EDX_10;
  ScorePlayer *pSVar3;
  ScorePlayer *pSVar4;
  ScorePlayer *pSVar5;
  ScorePlayer *pSVar6;
  pair<ScorePlayer_*_*,ScorePlayer_*_*> pVar7;
  undefined3 in_stack_0000000d;
  king_comp in_stack_00000010;
  ScorePlayer *pSVar8;
  ScorePlayer *pSVar9;
  ScorePlayer *local_c;
  ScorePlayer *local_8;
  
  pSVar3 = (ScorePlayer *)
           (param_2 +
           (((int)_param_3 - (int)param_2 >> 2) - ((int)_param_3 - (int)param_2 >> 0x1f) >> 1));
  _Median<ScorePlayer_*_*,king_comp>
            (param_2,(ScorePlayer **)pSVar3,(ScorePlayer **)(_param_3[-1].caName + 0x18),
             in_stack_00000010);
  local_8 = (ScorePlayer *)&pSVar3->iTeam;
  ppSVar2 = extraout_EDX;
  while (pSVar6 = pSVar3, param_2 < pSVar6) {
    pSVar3 = (ScorePlayer *)(pSVar6[-1].caName + 0x18);
    bVar1 = king_comp::operator()(&stack0x00000010,*(ScorePlayer **)pSVar3,*(ScorePlayer **)pSVar6);
    ppSVar2 = extraout_EDX_00;
    if ((bVar1) ||
       (bVar1 = king_comp::operator()
                          (&stack0x00000010,*(ScorePlayer **)pSVar6,*(ScorePlayer **)pSVar3),
       ppSVar2 = extraout_EDX_01, bVar1)) break;
  }
  do {
    pSVar3 = local_8;
    local_c = pSVar6;
    if (_param_3 <= local_8) break;
    pSVar5 = *(ScorePlayer **)local_8;
    bVar1 = king_comp::operator()(&stack0x00000010,pSVar5,*(ScorePlayer **)pSVar6);
    ppSVar2 = extraout_EDX_02;
    if ((bVar1) ||
       (bVar1 = king_comp::operator()(&stack0x00000010,*(ScorePlayer **)pSVar6,pSVar5),
       ppSVar2 = extraout_EDX_03, bVar1)) break;
    local_8 = (ScorePlayer *)&local_8->iTeam;
  } while( true );
LAB_004e4e49:
  pSVar5 = pSVar6;
  if (_param_3 <= pSVar3) {
joined_r0x004e4e54:
    while (pSVar8 = local_c, param_2 < pSVar8) {
      local_c = (ScorePlayer *)(pSVar8[-1].caName + 0x18);
      bVar1 = king_comp::operator()
                        (&stack0x00000010,*(ScorePlayer **)local_c,*(ScorePlayer **)pSVar5);
      ppSVar2 = extraout_EDX_07;
      if (!bVar1) {
        bVar1 = king_comp::operator()
                          (&stack0x00000010,*(ScorePlayer **)pSVar5,*(ScorePlayer **)local_c);
        ppSVar2 = extraout_EDX_08;
        if (bVar1) break;
        pSVar5 = (ScorePlayer *)(pSVar5[-1].caName + 0x18);
        swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)local_c);
        ppSVar2 = extraout_EDX_09;
      }
    }
    if (pSVar8 == (ScorePlayer *)param_2) {
      if (pSVar3 == _param_3) {
        *param_1 = pSVar5;
        param_1[1] = local_8;
        pVar7.second = ppSVar2;
        pVar7.first = param_1;
        return pVar7;
      }
      if (local_8 != pSVar3) {
        swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)local_8);
      }
      pSVar6 = (ScorePlayer *)&pSVar5->iTeam;
      pSVar4 = (ScorePlayer *)&pSVar3->iTeam;
      pSVar9 = pSVar3;
      local_c = pSVar8;
      local_8 = (ScorePlayer *)&local_8->iTeam;
    }
    else {
      pSVar8 = (ScorePlayer *)(pSVar8[-1].caName + 0x18);
      pSVar6 = pSVar3;
      local_c = pSVar8;
      if (pSVar3 != _param_3) goto LAB_004e4e3f;
      pSVar6 = (ScorePlayer *)(pSVar5[-1].caName + 0x18);
      if (pSVar8 != pSVar6) {
        swap<ScorePlayer_*>((ScorePlayer **)pSVar8,(ScorePlayer **)pSVar6);
      }
      pSVar9 = (ScorePlayer *)(local_8[-1].caName + 0x18);
      pSVar4 = pSVar3;
      pSVar5 = pSVar6;
      local_8 = pSVar9;
    }
    swap<ScorePlayer_*>((ScorePlayer **)pSVar5,(ScorePlayer **)pSVar9);
    ppSVar2 = extraout_EDX_10;
    pSVar3 = pSVar4;
    goto LAB_004e4e49;
  }
  pSVar8 = *(ScorePlayer **)pSVar3;
  bVar1 = king_comp::operator()(&stack0x00000010,*(ScorePlayer **)pSVar6,pSVar8);
  ppSVar2 = extraout_EDX_04;
  if (!bVar1) {
    bVar1 = king_comp::operator()(&stack0x00000010,pSVar8,*(ScorePlayer **)pSVar6);
    ppSVar2 = extraout_EDX_05;
    if (bVar1) goto joined_r0x004e4e54;
    pSVar6 = local_8;
    pSVar8 = pSVar3;
    local_8 = (ScorePlayer *)&local_8->iTeam;
LAB_004e4e3f:
    swap<ScorePlayer_*>((ScorePlayer **)pSVar6,(ScorePlayer **)pSVar8);
    ppSVar2 = extraout_EDX_06;
    pSVar6 = pSVar5;
  }
  pSVar3 = (ScorePlayer *)&pSVar3->iTeam;
  goto LAB_004e4e49;
}
