/*
 * Entry: 004b2e01
 * Name: Texture_AddGroup
 * Namespace: Global
 * Signature: int Texture_AddGroup(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Texture_AddGroup(_OBJ76 *param_1,char *param_2)

{
  char cVar1;
  float fVar2;
  textab *ptVar3;
  int iVar4;
  char *pcVar5;
  char *unaff_EDI;
  
  ptVar3 = dibs_textable(unaff_EDI);
  if (ptVar3 == (textab *)0x0) {
    iVar4 = 0;
  }
  else {
    (param_1->tex_info).textab = ptVar3;
    pcVar5 = param_2;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)param_1 + (0x78 - (int)param_2)] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    (param_1->tex_info).selectNum = 0;
    (param_1->tex_info).selectTex = (TEXTURE *)0x0;
    *(undefined4 *)&(param_1->tex_info).selectID = 0;
    *(undefined4 *)((int)&(param_1->tex_info).selectID + 4) = 0;
    if ((ptVar3->flags & 1) != 0) {
      fVar2 = 1.0 / ptVar3->FramesPerSec;
      if ((ptVar3->flags & 2) == 0) {
        TexAnim_RegOneShot(param_1,param_2,fVar2,0,ptVar3->size_dims[0],oneshot_cb);
      }
      else {
        TexAnim_RegLoop(param_1,param_2,fVar2,0,ptVar3->size_dims[0],1);
      }
    }
    iVar4 = 1;
  }
  return iVar4;
}
