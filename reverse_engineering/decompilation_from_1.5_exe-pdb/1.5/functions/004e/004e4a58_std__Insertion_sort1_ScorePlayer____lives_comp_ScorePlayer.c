/*
 * Entry: 004e4a58
 * Name: std::_Insertion_sort1<ScorePlayer_*_*,lives_comp,ScorePlayer_*>
 * Namespace: std
 * Signature: void _Insertion_sort1<ScorePlayer_*_*,lives_comp,ScorePlayer_*>(ScorePlayer * * param_1, ScorePlayer * * param_2, lives_comp param_3, ScorePlayer * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Insertion_sort1<ScorePlayer_*_*,lives_comp,ScorePlayer_*>
          (ScorePlayer **param_1,ScorePlayer **param_2,lives_comp param_3,ScorePlayer **param_4)

{
  ScorePlayer *pSVar1;
  ScorePlayer *pSVar2;
  ScorePlayer **ppSVar3;
  int iVar4;
  ScorePlayer **ppSVar5;
  
  ppSVar3 = param_1;
  if (param_1 != param_2) {
    while (ppSVar3 = ppSVar3 + 1, ppSVar3 != param_2) {
      pSVar1 = *ppSVar3;
      iVar4 = pSVar1->iLives;
      ppSVar5 = ppSVar3;
      if ((*param_1)->iLives < iVar4) {
        stdext::unchecked_copy_backward<ScorePlayer_*_*,ScorePlayer_*_*>
                  (param_1,ppSVar3,ppSVar3 + 1);
        *param_1 = pSVar1;
      }
      else {
        while( true ) {
          pSVar2 = ppSVar5[-1];
          if (iVar4 <= pSVar2->iLives) break;
          *ppSVar5 = pSVar2;
          iVar4 = pSVar1->iLives;
          ppSVar5 = ppSVar5 + -1;
        }
        *ppSVar5 = pSVar1;
      }
    }
  }
  return;
}
