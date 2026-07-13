/*
 * Entry: 0047a6ca
 * Name: Exit_Edit_View
 * Namespace: Global
 * Signature: void Exit_Edit_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Exit_Edit_View(tagENTITY *param_1)

{
  (*Last_View.fntc)(param_1);
  EditTerrain_Exit();
  return;
}
