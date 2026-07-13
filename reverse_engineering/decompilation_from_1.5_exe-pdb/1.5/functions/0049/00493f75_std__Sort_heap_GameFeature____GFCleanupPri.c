/*
 * Entry: 00493f75
 * Name: std::_Sort_heap<GameFeature_*_*,GFCleanupPri>
 * Namespace: std
 * Signature: void _Sort_heap<GameFeature_*_*,GFCleanupPri>(GameFeature * * param_1, GameFeature * * param_2, GFCleanupPri param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Sort_heap<GameFeature_*_*,GFCleanupPri>
          (GameFeature **param_1,GameFeature **param_2,GFCleanupPri param_3)

{
  uint uVar1;
  
  for (uVar1 = (int)param_2 - (int)param_1; 4 < (int)(uVar1 & 0xfffffffc); uVar1 = uVar1 - 4) {
    pop_heap<GameFeature_*_*,GFCleanupPri>(param_1,param_2,param_3);
    param_2 = param_2 + -1;
  }
  return;
}
