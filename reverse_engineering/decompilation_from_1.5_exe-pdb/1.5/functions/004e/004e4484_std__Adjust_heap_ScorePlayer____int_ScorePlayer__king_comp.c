/*
 * Entry: 004e4484
 * Name: std::_Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>
 * Namespace: std
 * Signature: void _Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>(ScorePlayer * * param_1, int param_2, int param_3, ScorePlayer * param_4, king_comp param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>
          (ScorePlayer **param_1,int param_2,int param_3,ScorePlayer *param_4,king_comp param_5)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined3 in_stack_00000015;
  
  iVar3 = param_2;
  while( true ) {
    iVar1 = iVar3 * 2;
    iVar4 = iVar1 + 2;
    if (param_3 <= iVar4) break;
    bVar2 = king_comp::operator()(&param_5,param_1[iVar4],param_1[iVar1 + 1]);
    if (bVar2) {
      iVar4 = iVar1 + 1;
    }
    param_1[iVar3] = param_1[iVar4];
    iVar3 = iVar4;
  }
  if (iVar4 == param_3) {
    param_1[iVar3] = param_1[param_3 + -1];
    iVar3 = param_3 + -1;
  }
  _Push_heap<ScorePlayer_*_*,int,ScorePlayer_*,king_comp>
            (param_1,iVar3,param_2,param_4,SUB41(_param_5,0));
  return;
}
