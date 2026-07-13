/*
 * Entry: 004b2f02
 * Name: Texture_Get
 * Namespace: Global
 * Signature: TEXTURE * Texture_Get(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl Texture_Get(_OBJ76 *param_1,char *param_2)

{
  TEXTURE *pTVar1;
  TEX_INFO *unaff_EBX;
  
  pTVar1 = (param_1->tex_info).selectTex;
  if (pTVar1 == (TEXTURE *)0x0) {
    if ((param_1->tex_info).textab == (textab *)0x0) {
      Texture_AddGroup(param_1,param_2);
    }
    if ((param_1->tex_info).selectTex == (TEXTURE *)0x0) {
      LoadSelection(unaff_EBX);
    }
    pTVar1 = (param_1->tex_info).selectTex;
  }
  return pTVar1;
}
