/*
 * Entry: 004e408a
 * Name: std::_Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>
 * Namespace: std
 * Signature: void _Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>(ScorePlayer * * param_1, int param_2, int param_3, ScorePlayer * param_4, comp param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>
          (ScorePlayer **param_1,int param_2,int param_3,ScorePlayer *param_4,comp param_5)

{
  ScorePlayer *pSVar1;
  int iVar2;
  
  while (param_3 < param_2) {
    iVar2 = (param_2 + -1) / 2;
    pSVar1 = param_1[iVar2];
    if (pSVar1->iKills - pSVar1->iDeaths <= param_4->iKills - param_4->iDeaths) break;
    param_1[param_2] = pSVar1;
    param_2 = iVar2;
  }
  param_1[param_2] = param_4;
  return;
}
