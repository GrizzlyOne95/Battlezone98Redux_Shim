/*
 * Entry: 004b2bd3
 * Name: Texture_Delete
 * Namespace: Global
 * Signature: int Texture_Delete(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Texture_Delete(_OBJ76 *param_1)

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
  return 1;
}
