/*
 * Entry: 004920cf
 * Name: std::_Med3<GameFeature_*_*,GFInitPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFInitPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFInitPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFInitPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFInitPri param_4)

{
  if ((*param_1)->initPriority < (*param_2)->initPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->initPriority < (*param_3)->initPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->initPriority < (*param_2)->initPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
