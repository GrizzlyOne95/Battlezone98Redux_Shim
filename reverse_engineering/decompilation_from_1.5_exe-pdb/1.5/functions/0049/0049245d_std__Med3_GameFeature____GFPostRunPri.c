/*
 * Entry: 0049245d
 * Name: std::_Med3<GameFeature_*_*,GFPostRunPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFPostRunPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFPostRunPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFPostRunPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFPostRunPri param_4)

{
  if ((*param_1)->postRunPriority < (*param_2)->postRunPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->postRunPriority < (*param_3)->postRunPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->postRunPriority < (*param_2)->postRunPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
