/*
 * Entry: 004b2e8a
 * Name: Texture_Clone
 * Namespace: Global
 * Signature: int Texture_Clone(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Texture_Clone(_OBJ76 *param_1,_OBJ76 *param_2)

{
  float fVar1;
  textab *ptVar2;
  int iVar3;
  TEX_INFO *pTVar4;
  TEX_INFO *pTVar5;
  char *unaff_EDI;
  TEX_INFO *pTVar6;
  
  pTVar4 = &param_2->tex_info;
  pTVar5 = &param_1->tex_info;
  pTVar6 = pTVar4;
  for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pTVar6->group = *(undefined4 *)pTVar5->group;
    pTVar5 = (TEX_INFO *)(pTVar5->group + 4);
    pTVar6 = (TEX_INFO *)(pTVar6->group + 4);
  }
  if ((param_2->tex_info).textab != (textab *)0x0) {
    ptVar2 = dibs_textable(unaff_EDI);
    (param_2->tex_info).textab = ptVar2;
    (param_2->tex_info).selectNum = 0;
    (param_2->tex_info).selectTex = (TEXTURE *)0x0;
    if ((ptVar2->flags & 1) != 0) {
      fVar1 = 1.0 / ptVar2->FramesPerSec;
      if ((ptVar2->flags & 2) == 0) {
        TexAnim_RegOneShot(param_2,pTVar4->group,fVar1,0,ptVar2->size_dims[0],oneshot_cb);
      }
      else {
        TexAnim_RegLoop(param_2,pTVar4->group,fVar1,0,ptVar2->size_dims[0],1);
      }
    }
  }
  return 1;
}
