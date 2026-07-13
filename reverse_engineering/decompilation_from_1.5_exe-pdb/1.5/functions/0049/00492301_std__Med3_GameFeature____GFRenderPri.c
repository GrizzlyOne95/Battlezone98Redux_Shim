/*
 * Entry: 00492301
 * Name: std::_Med3<GameFeature_*_*,GFRenderPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFRenderPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFRenderPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFRenderPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFRenderPri param_4)

{
  if ((*param_1)->renderPriority < (*param_2)->renderPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->renderPriority < (*param_3)->renderPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->renderPriority < (*param_2)->renderPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
