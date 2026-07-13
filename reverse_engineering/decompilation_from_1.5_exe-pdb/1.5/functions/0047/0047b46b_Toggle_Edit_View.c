/*
 * Entry: 0047b46b
 * Name: Toggle_Edit_View
 * Namespace: Global
 * Signature: void Toggle_Edit_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Toggle_Edit_View(tagENTITY *param_1)

{
  tagENTITY *unaff_EBX;
  
  if (TerrainEdit != 0) {
    if (TerrainEditMode != 0) {
      Exit_Edit_View(param_1);
      return;
    }
    Apply_Edit_View(unaff_EBX);
  }
  return;
}
