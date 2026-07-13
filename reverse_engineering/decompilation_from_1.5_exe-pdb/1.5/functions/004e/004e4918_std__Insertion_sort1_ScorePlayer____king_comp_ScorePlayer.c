/*
 * Entry: 004e4918
 * Name: std::_Insertion_sort1<ScorePlayer_*_*,king_comp,ScorePlayer_*>
 * Namespace: std
 * Signature: void _Insertion_sort1<ScorePlayer_*_*,king_comp,ScorePlayer_*>(ScorePlayer * * param_1, ScorePlayer * * param_2, king_comp param_3, ScorePlayer * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Insertion_sort1<ScorePlayer_*_*,king_comp,ScorePlayer_*>
          (ScorePlayer **param_1,ScorePlayer **param_2,king_comp param_3,ScorePlayer **param_4)

{
  ScorePlayer *pSVar1;
  ScorePlayer **ppSVar2;
  ScorePlayer **ppSVar3;
  bool bVar4;
  ScorePlayer **ppSVar5;
  ScorePlayer *pSVar6;
  ScorePlayer **local_8;
  
  ppSVar2 = param_1;
  if (param_1 != param_2) {
    while (ppSVar2 = ppSVar2 + 1, ppSVar2 != param_2) {
      pSVar1 = *ppSVar2;
      bVar4 = king_comp::operator()(&param_3,pSVar1,*param_1);
      if (bVar4) {
        stdext::unchecked_copy_backward<ScorePlayer_*_*,ScorePlayer_*_*>
                  (param_1,ppSVar2,ppSVar2 + 1);
        *param_1 = pSVar1;
      }
      else {
        pSVar6 = ppSVar2[-1];
        ppSVar3 = ppSVar2 + -1;
        local_8 = ppSVar2;
        while (ppSVar5 = ppSVar3, bVar4 = king_comp::operator()(&param_3,pSVar1,pSVar6), bVar4) {
          *local_8 = *ppSVar5;
          pSVar6 = ppSVar5[-1];
          ppSVar3 = ppSVar5 + -1;
          local_8 = ppSVar5;
        }
        *local_8 = pSVar1;
      }
    }
  }
  return;
}
