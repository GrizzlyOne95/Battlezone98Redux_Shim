/*
 * Entry: 004e4b84
 * Name: std::_Insertion_sort1<ScorePlayer_*_*,comp,ScorePlayer_*>
 * Namespace: std
 * Signature: void _Insertion_sort1<ScorePlayer_*_*,comp,ScorePlayer_*>(ScorePlayer * * param_1, ScorePlayer * * param_2, comp param_3, ScorePlayer * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Insertion_sort1<ScorePlayer_*_*,comp,ScorePlayer_*>
          (ScorePlayer **param_1,ScorePlayer **param_2,comp param_3,ScorePlayer **param_4)

{
  ScorePlayer *pSVar1;
  ScorePlayer **ppSVar2;
  ScorePlayer **ppSVar3;
  int iVar4;
  ScorePlayer *pSVar5;
  ScorePlayer **ppSVar6;
  ScorePlayer **local_8;
  
  ppSVar2 = param_1;
  if (param_1 != param_2) {
    while (ppSVar2 = ppSVar2 + 1, ppSVar2 != param_2) {
      pSVar1 = *ppSVar2;
      iVar4 = pSVar1->iKills - pSVar1->iDeaths;
      if ((*param_1)->iKills - (*param_1)->iDeaths < iVar4) {
        stdext::unchecked_copy_backward<ScorePlayer_*_*,ScorePlayer_*_*>
                  (param_1,ppSVar2,ppSVar2 + 1);
        *param_1 = pSVar1;
      }
      else {
        pSVar5 = ppSVar2[-1];
        ppSVar3 = ppSVar2 + -1;
        local_8 = ppSVar2;
        if (pSVar5->iKills - pSVar5->iDeaths < iVar4) {
          do {
            ppSVar6 = ppSVar3;
            *local_8 = pSVar5;
            pSVar5 = ppSVar6[-1];
            ppSVar3 = ppSVar6 + -1;
            local_8 = ppSVar6;
          } while (pSVar5->iKills - pSVar5->iDeaths < pSVar1->iKills - pSVar1->iDeaths);
        }
        *local_8 = pSVar1;
      }
    }
  }
  return;
}
