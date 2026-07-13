/*
 * Entry: 004921a5
 * Name: std::_Med3<GameFeature_*_*,GFPreLoadPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFPreLoadPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFPreLoadPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFPreLoadPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFPreLoadPri param_4)

{
  if ((*param_1)->preLoadPriority < (*param_2)->preLoadPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->preLoadPriority < (*param_3)->preLoadPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->preLoadPriority < (*param_2)->preLoadPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
