/*
 * Entry: 0049250b
 * Name: std::_Med3<GameFeature_*_*,GFCleanupPri>
 * Namespace: std
 * Signature: void _Med3<GameFeature_*_*,GFCleanupPri>(GameFeature * * param_1, GameFeature * * param_2, GameFeature * * param_3, GFCleanupPri param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Med3<GameFeature_*_*,GFCleanupPri>
          (GameFeature **param_1,GameFeature **param_2,GameFeature **param_3,GFCleanupPri param_4)

{
  if ((*param_1)->cleanupPriority < (*param_2)->cleanupPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  if ((*param_2)->cleanupPriority < (*param_3)->cleanupPriority) {
    swap<GameFeature_*>(param_3,param_2);
  }
  if ((*param_1)->cleanupPriority < (*param_2)->cleanupPriority) {
    swap<GameFeature_*>(param_2,param_1);
  }
  return;
}
