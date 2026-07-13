/*
 * Entry: 004716cb
 * Name: SetCBState
 * Namespace: Global
 * Signature: void SetCBState(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetCBState(int param_1)

{
  NoMoreCB = (uint)(param_1 == 0);
  return;
}
