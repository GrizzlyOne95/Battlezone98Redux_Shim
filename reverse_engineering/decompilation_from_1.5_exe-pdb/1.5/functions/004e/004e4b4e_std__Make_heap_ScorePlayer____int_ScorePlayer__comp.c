/*
 * Entry: 004e4b4e
 * Name: std::_Make_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>
 * Namespace: std
 * Signature: void _Make_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, comp param_3, int * param_4, ScorePlayer * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Make_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,comp param_3,int *param_4,
          ScorePlayer **param_5)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (int)param_2 - (int)param_1 >> 2;
  iVar1 = iVar2 - ((int)param_2 - (int)param_1 >> 0x1f) >> 1;
  while (0 < iVar1) {
    iVar1 = iVar1 + -1;
    _Adjust_heap<ScorePlayer_*_*,int,ScorePlayer_*,comp>(param_1,iVar1,iVar2,param_1[iVar1],param_3)
    ;
  }
  return;
}
