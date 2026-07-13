/*
 * Entry: 00493cd7
 * Name: std::pop_heap<GameFeature_*_*,GFPostLoadPri>
 * Namespace: std
 * Signature: void pop_heap<GameFeature_*_*,GFPostLoadPri>(GameFeature * * param_1, GameFeature * * param_2, GFPostLoadPri param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::pop_heap<GameFeature_*_*,GFPostLoadPri>
          (GameFeature **param_1,GameFeature **param_2,GFPostLoadPri param_3)

{
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    _Pop_heap_0<GameFeature_*_*,GameFeature_*,GFPostLoadPri>
              (param_1,param_2,param_3,(GameFeature **)0x0);
  }
  return;
}
