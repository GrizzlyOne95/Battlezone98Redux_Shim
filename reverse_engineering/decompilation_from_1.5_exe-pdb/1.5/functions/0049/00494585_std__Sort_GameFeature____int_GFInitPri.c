/*
 * Entry: 00494585
 * Name: std::_Sort<GameFeature_*_*,int,GFInitPri>
 * Namespace: std
 * Signature: void _Sort<GameFeature_*_*,int,GFInitPri>(GameFeature * * param_1, GameFeature * * param_2, int param_3, GFInitPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Sort<GameFeature_*_*,int,GFInitPri>
          (GameFeature **param_1,GameFeature **param_2,int param_3,GFInitPri param_4)

{
  int iVar1;
  GameFeature *in_ECX;
  GameFeature *local_c;
  GameFeature *local_8;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  local_c = in_ECX;
  local_8 = in_ECX;
  if (0x20 < iVar1) {
    do {
      if (param_3 < 1) break;
      _Unguarded_partition<GameFeature_*_*,GFInitPri>(&local_c,param_1,SUB41(param_2,0));
      param_3 = param_3 / 2 + (param_3 / 2) / 2;
      if ((int)((int)local_c - (int)param_1 & 0xfffffffcU) <
          (int)((int)param_2 - (int)local_8 & 0xfffffffcU)) {
        _Sort<GameFeature_*_*,int,GFInitPri>(param_1,(GameFeature **)local_c,param_3,param_4);
        param_1 = (GameFeature **)local_8;
      }
      else {
        _Sort<GameFeature_*_*,int,GFInitPri>((GameFeature **)local_8,param_2,param_3,param_4);
        param_2 = (GameFeature **)local_c;
      }
      iVar1 = (int)param_2 - (int)param_1 >> 2;
    } while (0x20 < iVar1);
    if (0x20 < iVar1) {
      make_heap<GameFeature_*_*,GFInitPri>(param_1,param_2,param_4);
      _Sort_heap<GameFeature_*_*,GFInitPri>(param_1,param_2,param_4);
      return;
    }
  }
  if (1 < iVar1) {
    _Insertion_sort<GameFeature_*_*,GFInitPri>(param_1,param_2,param_4);
  }
  return;
}
