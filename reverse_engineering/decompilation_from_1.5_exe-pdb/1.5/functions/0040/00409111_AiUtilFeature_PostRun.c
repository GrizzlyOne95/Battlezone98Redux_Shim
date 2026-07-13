/*
 * Entry: 00409111
 * Name: AiUtilFeature::PostRun
 * Namespace: AiUtilFeature
 * Signature: void PostRun(AiUtilFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiUtilFeature::PostRun(AiUtilFeature *this)

{
  CleanPathing();
  BlockedCellClean();
  return;
}
