/*
 * Entry: 004b2c00
 * Name: Texture_Select
 * Namespace: Global
 * Signature: int Texture_Select(_OBJ76 * param_1, char * param_2, long param_3, long param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Texture_Select(_OBJ76 *param_1,char *param_2,long param_3,long param_4,int param_5)

{
  uint uVar1;
  TEX_INFO *unaff_EBX;
  TEX_INFO *unaff_EDI;
  
  if (param_3 == 0) {
    param_3 = *(ushort *)((int)&(param_1->tex_info).selectNum + 2) + 1;
  }
  uVar1 = param_3 * 0x10000 - 0x10000U | param_4;
  if (uVar1 != (param_1->tex_info).selectNum) {
    if ((param_1->tex_info).selectTex != (TEXTURE *)0x0) {
      ReleaseSelection(unaff_EDI);
    }
    (param_1->tex_info).selectNum = uVar1;
    if (param_5 != 0) {
      LoadSelection(unaff_EBX);
    }
  }
  return 1;
}
