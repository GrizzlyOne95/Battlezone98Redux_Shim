/*
 * Entry: 004b27b1
 * Name: TexAnim_Unregister
 * Namespace: Global
 * Signature: int TexAnim_Unregister(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl TexAnim_Unregister(_OBJ76 *param_1,char *param_2)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  byte *pbVar4;
  texanim *unaff_ESI;
  texanim *ptVar5;
  bool bVar6;
  
  ptVar5 = texanim_list;
  do {
    if (ptVar5 == (texanim *)0x0) {
      return 0;
    }
    if (ptVar5->obj == param_1) {
      pcVar2 = ptVar5->tex_name;
      pbVar4 = (byte *)param_2;
      do {
        bVar1 = *pcVar2;
        bVar6 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_004b27e7:
          iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_004b27ec;
        }
        if (bVar1 == 0) break;
        bVar1 = pcVar2[1];
        bVar6 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_004b27e7;
        pcVar2 = pcVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_004b27ec:
      if (iVar3 == 0) {
        release_obj(ptVar5->obj,"texanim");
        iVar3 = remove_animation(unaff_ESI);
        return iVar3;
      }
    }
    ptVar5 = ptVar5->next;
  } while( true );
}
