/*
 * Entry: 0049b175
 * Name: GeoCache_ClearLOD
 * Namespace: Global
 * Signature: void GeoCache_ClearLOD(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GeoCache_ClearLOD(_OBJ76 *param_1)

{
  long *plVar1;
  TEX_INFO *unaff_ESI;
  
  if ((param_1->tex_info).textab != (textab *)0x0) {
    if ((param_1->tex_info).selectTex != (TEXTURE *)0x0) {
      ReleaseSelection(unaff_ESI);
    }
    plVar1 = &((param_1->tex_info).textab)->usage_count;
    *plVar1 = *plVar1 + -1;
    (param_1->tex_info).textab = (textab *)0x0;
  }
  return;
}
