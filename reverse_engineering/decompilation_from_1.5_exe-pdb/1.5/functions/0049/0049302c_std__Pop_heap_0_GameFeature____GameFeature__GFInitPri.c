/*
 * Entry: 0049302c
 * Name: std::_Pop_heap_0<GameFeature_*_*,GameFeature_*,GFInitPri>
 * Namespace: std
 * Signature: void _Pop_heap_0<GameFeature_*_*,GameFeature_*,GFInitPri>(GameFeature * * param_1, GameFeature * * param_2, GFInitPri param_3, GameFeature * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap_0<GameFeature_*_*,GameFeature_*,GFInitPri>
          (GameFeature **param_1,GameFeature **param_2,GFInitPri param_3,GameFeature **param_4)

{
  GameFeature **ppGVar1;
  
  ppGVar1 = param_2 + -1;
  _Pop_heap<GameFeature_*_*,int,GameFeature_*,GFInitPri>
            (param_1,ppGVar1,ppGVar1,*ppGVar1,param_3,(int *)0x0);
  return;
}
