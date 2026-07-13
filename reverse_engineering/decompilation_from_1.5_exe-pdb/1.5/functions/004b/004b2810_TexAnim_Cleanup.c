/*
 * Entry: 004b2810
 * Name: TexAnim_Cleanup
 * Namespace: Global
 * Signature: void TexAnim_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TexAnim_Cleanup(void)

{
  texanim *ptVar1;
  texanim *ptVar2;
  texanim *unaff_EDI;
  
  ptVar2 = texanim_list;
  while (ptVar2 != (texanim *)0x0) {
    ptVar1 = ptVar2->next;
    release_obj(ptVar2->obj,"texanim");
    remove_animation(unaff_EDI);
    ptVar2 = ptVar1;
  }
  texanim_list = (texanim *)0x0;
  return;
}
