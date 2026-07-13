/*
 * Entry: 004acd0e
 * Name: SetEditMode
 * Namespace: Global
 * Signature: void SetEditMode(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetEditMode(int param_1)

{
  editMode = (uint)(param_1 == 1);
  return;
}
