/*
 * Entry: 00492686
 * Name: std::_Pop_heap<GameFeature_*_*,int,GameFeature_*,GFPostRunPri>
 * Namespace: std
 * Signature: void _Pop_heap<GameFeature_*_*,int,GameFeature_*,GFPostRunPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GameFeature * param_4, GFPostRunPri param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap<GameFeature_*_*,int,GameFeature_*,GFPostRunPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GameFeature *param_4,
          GFPostRunPri param_5,int *param_6)

{
  *param_3 = *param_1;
  _Adjust_heap<GameFeature_*_*,int,GameFeature_*,GFPostRunPri>
            (param_1,0,(int)param_2 - (int)param_1 >> 2,param_4,param_5);
  return;
}
