/*
 * Entry: 00491b1f
 * Name: GFCleanupPri::operator()
 * Namespace: GFCleanupPri
 * Signature: bool operator()(GFCleanupPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
GFCleanupPri::operator()(GFCleanupPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->cleanupPriority < param_1->cleanupPriority;
}
