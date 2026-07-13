/*
 * Entry: 00492ca8
 * Name: std::_Median<GameFeature_*_*,GFPreDestroyPri>
 * Namespace: std
 * Signature: void _Median<GameFeature_*_*,GFPreDestroyPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFPreDestroyPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Median<GameFeature_*_*,GFPreDestroyPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFPreDestroyPri param_4
          )

{
  int iVar1;
  
  iVar1 = (int)param_3 - (int)param_1 >> 2;
  if (iVar1 < 0x29) {
    _Med3<GameFeature_*_*,GFPreDestroyPri>(param_1,param_2,param_3,param_4);
  }
  else {
    iVar1 = iVar1 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    _Med3<GameFeature_*_*,GFPreDestroyPri>(param_1,param_1 + iVar1,param_1 + iVar1 * 2,param_4);
    _Med3<GameFeature_*_*,GFPreDestroyPri>(param_2 + -iVar1,param_2,param_2 + iVar1,param_4);
    _Med3<GameFeature_*_*,GFPreDestroyPri>(param_3 + iVar1 * -2,param_3 + -iVar1,param_3,param_4);
    _Med3<GameFeature_*_*,GFPreDestroyPri>(param_1 + iVar1,param_2,param_3 + -iVar1,param_4);
  }
  return;
}
