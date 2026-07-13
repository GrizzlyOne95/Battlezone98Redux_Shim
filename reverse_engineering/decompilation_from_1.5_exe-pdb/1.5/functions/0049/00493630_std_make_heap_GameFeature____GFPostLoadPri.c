/*
 * Entry: 00493630
 * Name: std::make_heap<GameFeature_*_*,GFPostLoadPri>
 * Namespace: std
 * Signature: void make_heap<GameFeature_*_*,GFPostLoadPri>(GameFeature * * param_1, GameFeature * * param_2, GFPostLoadPri param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::make_heap<GameFeature_*_*,GFPostLoadPri>
          (GameFeature **param_1,GameFeature **param_2,GFPostLoadPri param_3)

{
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    _Make_heap<GameFeature_*_*,int,GameFeature_*,GFPostLoadPri>
              (param_1,param_2,param_3,(int *)0x0,(GameFeature **)0x0);
  }
  return;
}
