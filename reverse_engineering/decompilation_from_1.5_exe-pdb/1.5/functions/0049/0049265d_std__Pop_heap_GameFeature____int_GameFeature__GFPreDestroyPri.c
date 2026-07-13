/*
 * Entry: 0049265d
 * Name: std::_Pop_heap<GameFeature_*_*,int,GameFeature_*,GFPreDestroyPri>
 * Namespace: std
 * Signature: void _Pop_heap<GameFeature_*_*,int,GameFeature_*,GFPreDestroyPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GameFeature * param_4, GFPreDestroyPri param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap<GameFeature_*_*,int,GameFeature_*,GFPreDestroyPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GameFeature *param_4,
          GFPreDestroyPri param_5,int *param_6)

{
  *param_3 = *param_1;
  _Adjust_heap<GameFeature_*_*,int,GameFeature_*,GFPreDestroyPri>
            (param_1,0,(int)param_2 - (int)param_1 >> 2,param_4,param_5);
  return;
}
