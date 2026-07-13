/*
 * Entry: 00493d49
 * Name: std::pop_heap<GameFeature_*_*,GFPostRunPri>
 * Namespace: std
 * Signature: void pop_heap<GameFeature_*_*,GFPostRunPri>(GameFeature * * param_1, GameFeature * * param_2, GFPostRunPri param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::pop_heap<GameFeature_*_*,GFPostRunPri>
          (GameFeature **param_1,GameFeature **param_2,GFPostRunPri param_3)

{
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    _Pop_heap_0<GameFeature_*_*,GameFeature_*,GFPostRunPri>
              (param_1,param_2,param_3,(GameFeature **)0x0);
  }
  return;
}
