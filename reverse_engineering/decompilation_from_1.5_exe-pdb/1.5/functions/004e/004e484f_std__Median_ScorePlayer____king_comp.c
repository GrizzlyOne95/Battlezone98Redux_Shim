/*
 * Entry: 004e484f
 * Name: std::_Median<ScorePlayer_*_*,king_comp>
 * Namespace: std
 * Signature: void _Median<ScorePlayer_*_*,king_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, king_comp param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Median<ScorePlayer_*_*,king_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,king_comp param_4)

{
  int iVar1;
  
  iVar1 = (int)param_3 - (int)param_1 >> 2;
  if (iVar1 < 0x29) {
    _Med3<ScorePlayer_*_*,king_comp>(param_1,param_2,param_3,param_4);
  }
  else {
    iVar1 = iVar1 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    _Med3<ScorePlayer_*_*,king_comp>(param_1,param_1 + iVar1,param_1 + iVar1 * 2,param_4);
    _Med3<ScorePlayer_*_*,king_comp>(param_2 + -iVar1,param_2,param_2 + iVar1,param_4);
    _Med3<ScorePlayer_*_*,king_comp>(param_3 + iVar1 * -2,param_3 + -iVar1,param_3,param_4);
    _Med3<ScorePlayer_*_*,king_comp>(param_1 + iVar1,param_2,param_3 + -iVar1,param_4);
  }
  return;
}
