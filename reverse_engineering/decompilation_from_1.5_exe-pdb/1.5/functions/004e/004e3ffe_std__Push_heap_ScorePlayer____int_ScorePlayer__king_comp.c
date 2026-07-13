/*
 * Entry: 004e3ffe
 * Name: std::_Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>
 * Namespace: std
 * Signature: void _Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>(ScorePlayer * * param_1, int param_2, int param_3, ScorePlayer * param_4, king_comp param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>
          (ScorePlayer **param_1,int param_2,int param_3,ScorePlayer *param_4,king_comp param_5)

{
  bool bVar1;
  int iVar2;
  
  while (iVar2 = (param_2 + -1) / 2, param_3 < param_2) {
    bVar1 = king_comp::operator()(&param_5,param_1[iVar2],param_4);
    if (!bVar1) break;
    param_1[param_2] = param_1[iVar2];
    param_2 = iVar2;
  }
  param_1[param_2] = param_4;
  return;
}
