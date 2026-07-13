/*
 * Entry: 0049211f
 * Name: std::_Adjust_heap<GameFeature_*_*,int,GameFeature_*,GFInitPri>
 * Namespace: std
 * Signature: void _Adjust_heap<GameFeature_*_*,int,GameFeature_*,GFInitPri>(GameFeature * * param_1, int param_2, int param_3, GameFeature * param_4, GFInitPri param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Adjust_heap<GameFeature_*_*,int,GameFeature_*,GFInitPri>
          (GameFeature **param_1,int param_2,int param_3,GameFeature *param_4,GFInitPri param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_2;
  while( true ) {
    iVar1 = iVar3 * 2;
    iVar2 = iVar1 + 2;
    if (param_3 <= iVar2) break;
    if (param_1[iVar1 + 1]->initPriority < param_1[iVar2]->initPriority) {
      iVar2 = iVar1 + 1;
    }
    param_1[iVar3] = param_1[iVar2];
    iVar3 = iVar2;
  }
  if (iVar2 == param_3) {
    param_1[iVar3] = param_1[param_3 + -1];
    iVar3 = param_3 + -1;
  }
  _Push_heap<GameFeature_*_*,int,GameFeature_*,GFInitPri>(param_1,iVar3,param_2,param_4,param_5);
  return;
}
