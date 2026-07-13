/*
 * Entry: 004e4425
 * Name: std::_Med3<ScorePlayer_*_*,king_comp>
 * Namespace: std
 * Signature: void _Med3<ScorePlayer_*_*,king_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, ScorePlayer * * param_3, king_comp param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<ScorePlayer_*_*,king_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,ScorePlayer **param_3,king_comp param_4)

{
  bool bVar1;
  
  bVar1 = king_comp::operator()(&param_4,*param_2,*param_1);
  if (bVar1) {
    swap<ScorePlayer_*>(param_2,param_1);
  }
  bVar1 = king_comp::operator()(&param_4,*param_3,*param_2);
  if (bVar1) {
    swap<ScorePlayer_*>(param_3,param_2);
  }
  bVar1 = king_comp::operator()(&param_4,*param_2,*param_1);
  if (bVar1) {
    swap<ScorePlayer_*>(param_2,param_1);
  }
  return;
}
