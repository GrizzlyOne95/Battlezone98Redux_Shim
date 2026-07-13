/*
 * Entry: 00491d34
 * Name: std::_Push_heap<GameFeature_*_*,int,GameFeature_*,GFPreLoadPri>
 * Namespace: std
 * Signature: void _Push_heap<GameFeature_*_*,int,GameFeature_*,GFPreLoadPri>(GameFeature * * param_1, int param_2, int param_3, GameFeature * param_4, GFPreLoadPri param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Push_heap<GameFeature_*_*,int,GameFeature_*,GFPreLoadPri>
          (GameFeature **param_1,int param_2,int param_3,GameFeature *param_4,GFPreLoadPri param_5)

{
  int iVar1;
  
  while (param_3 < param_2) {
    iVar1 = (param_2 + -1) / 2;
    if (param_1[iVar1]->preLoadPriority <= param_4->preLoadPriority) break;
    param_1[param_2] = param_1[iVar1];
    param_2 = iVar1;
  }
  param_1[param_2] = param_4;
  return;
}
