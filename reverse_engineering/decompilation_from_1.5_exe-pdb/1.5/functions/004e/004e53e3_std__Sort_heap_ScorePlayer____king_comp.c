/*
 * Entry: 004e53e3
 * Name: std::_Sort_heap<ScorePlayer_*_*,king_comp>
 * Namespace: std
 * Signature: void _Sort_heap<ScorePlayer_*_*,king_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, king_comp param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Sort_heap<ScorePlayer_*_*,king_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,king_comp param_3)

{
  uint uVar1;
  
  for (uVar1 = (int)param_2 - (int)param_1; 4 < (int)(uVar1 & 0xfffffffc); uVar1 = uVar1 - 4) {
    pop_heap<ScorePlayer_*_*,king_comp>(param_1,param_2,param_3);
    param_2 = param_2 + -1;
  }
  return;
}
