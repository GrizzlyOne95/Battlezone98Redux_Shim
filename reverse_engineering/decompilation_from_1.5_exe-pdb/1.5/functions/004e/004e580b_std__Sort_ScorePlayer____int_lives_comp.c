/*
 * Entry: 004e580b
 * Name: std::_Sort<ScorePlayer_*_*,int,lives_comp>
 * Namespace: std
 * Signature: void _Sort<ScorePlayer_*_*,int,lives_comp>(ScorePlayer * * param_1, ScorePlayer * * param_2, int param_3, lives_comp param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Sort<ScorePlayer_*_*,int,lives_comp>
          (ScorePlayer **param_1,ScorePlayer **param_2,int param_3,lives_comp param_4)

{
  int iVar1;
  ScorePlayer *in_ECX;
  ScorePlayer *local_c;
  ScorePlayer *local_8;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  local_c = in_ECX;
  local_8 = in_ECX;
  if (0x20 < iVar1) {
    do {
      if (param_3 < 1) break;
      _Unguarded_partition<ScorePlayer_*_*,lives_comp>(&local_c,param_1,SUB41(param_2,0));
      param_3 = param_3 / 2 + (param_3 / 2) / 2;
      if ((int)((int)local_c - (int)param_1 & 0xfffffffcU) <
          (int)((int)param_2 - (int)local_8 & 0xfffffffcU)) {
        _Sort<ScorePlayer_*_*,int,lives_comp>(param_1,(ScorePlayer **)local_c,param_3,param_4);
        param_1 = (ScorePlayer **)local_8;
      }
      else {
        _Sort<ScorePlayer_*_*,int,lives_comp>((ScorePlayer **)local_8,param_2,param_3,param_4);
        param_2 = (ScorePlayer **)local_c;
      }
      iVar1 = (int)param_2 - (int)param_1 >> 2;
    } while (0x20 < iVar1);
    if (0x20 < iVar1) {
      make_heap<ScorePlayer_*_*,lives_comp>(param_1,param_2,param_4);
      _Sort_heap<ScorePlayer_*_*,lives_comp>(param_1,param_2,param_4);
      return;
    }
  }
  if (1 < iVar1) {
    _Insertion_sort<ScorePlayer_*_*,lives_comp>(param_1,param_2,param_4);
  }
  return;
}
