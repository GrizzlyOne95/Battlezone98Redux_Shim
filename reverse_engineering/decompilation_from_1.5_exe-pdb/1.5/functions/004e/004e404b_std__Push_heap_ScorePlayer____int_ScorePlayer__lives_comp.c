/*
 * Entry: 004e404b
 * Name: std::_Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
 * Namespace: std
 * Signature: void _Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>(ScorePlayer * * param_1, int param_2, int param_3, ScorePlayer * param_4, lives_comp param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
          (ScorePlayer **param_1,int param_2,int param_3,ScorePlayer *param_4,lives_comp param_5)

{
  int iVar1;
  
  while (param_3 < param_2) {
    iVar1 = (param_2 + -1) / 2;
    if (param_1[iVar1]->iLives <= param_4->iLives) break;
    param_1[param_2] = param_1[iVar1];
    param_2 = iVar1;
  }
  param_1[param_2] = param_4;
  return;
}
