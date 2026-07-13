/*
 * Entry: 004e4564
 * Name: std::_Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
 * Namespace: std
 * Signature: void _Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>(ScorePlayer * * param_1, int param_2, int param_3, ScorePlayer * param_4, lives_comp param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>
          (ScorePlayer **param_1,int param_2,int param_3,ScorePlayer *param_4,lives_comp param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_2;
  while( true ) {
    iVar1 = iVar3 * 2;
    iVar2 = iVar1 + 2;
    if (param_3 <= iVar2) break;
    if (param_1[iVar1 + 1]->iLives < param_1[iVar2]->iLives) {
      iVar2 = iVar1 + 1;
    }
    param_1[iVar3] = param_1[iVar2];
    iVar3 = iVar2;
  }
  if (iVar2 == param_3) {
    param_1[iVar3] = param_1[param_3 + -1];
    iVar3 = param_3 + -1;
  }
  _Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,lives_comp>(param_1,iVar3,param_2,param_4,param_5);
  return;
}
