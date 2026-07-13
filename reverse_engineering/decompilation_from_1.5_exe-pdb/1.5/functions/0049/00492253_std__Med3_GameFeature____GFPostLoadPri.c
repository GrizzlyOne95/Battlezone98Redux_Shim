/*
 * Entry: 00492253
 * Name: std::_Med3<GameFeature_*_*,GFPostLoadPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFPostLoadPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFPostLoadPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFPostLoadPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFPostLoadPri param_4)

{
  if ((*param_1)->postLoadPriority < (*param_2)->postLoadPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->postLoadPriority < (*param_3)->postLoadPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->postLoadPriority < (*param_2)->postLoadPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
