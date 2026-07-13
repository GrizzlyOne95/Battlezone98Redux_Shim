/*
 * Entry: 004923af
 * Name: std::_Med3<GameFeature_*_*,GFPreDestroyPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFPreDestroyPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFPreDestroyPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFPreDestroyPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFPreDestroyPri param_4
          )

{
  if ((*param_1)->preDestroyPriority < (*param_2)->preDestroyPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->preDestroyPriority < (*param_3)->preDestroyPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->preDestroyPriority < (*param_2)->preDestroyPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
