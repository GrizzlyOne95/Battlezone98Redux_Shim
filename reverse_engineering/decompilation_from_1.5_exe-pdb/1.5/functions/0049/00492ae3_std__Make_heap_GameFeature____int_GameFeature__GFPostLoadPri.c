/*
 * Entry: 00492ae3
 * Name: std::_Make_heap<GameFeature_*_*,int,GameFeature_*,GFPostLoadPri>
 * Namespace: std
 * Signature: void _Make_heap<GameFeature_*_*,int,GameFeature_*,GFPostLoadPri>(GameFeature * * param_1, GameFeature * * param_2, GFPostLoadPri param_3, int * param_4, GameFeature * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Make_heap<GameFeature_*_*,int,GameFeature_*,GFPostLoadPri>
          (GameFeature **param_1,GameFeature **param_2,GFPostLoadPri param_3,int *param_4,
          GameFeature **param_5)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (int)param_2 - (int)param_1 >> 2;
  iVar1 = iVar2 - ((int)param_2 - (int)param_1 >> 0x1f) >> 1;
  while (0 < iVar1) {
    iVar1 = iVar1 + -1;
    _Adjust_heap<GameFeature_*_*,int,GameFeature_*,GFPostLoadPri>
              (param_1,iVar1,iVar2,param_1[iVar1],param_3);
  }
  return;
}
