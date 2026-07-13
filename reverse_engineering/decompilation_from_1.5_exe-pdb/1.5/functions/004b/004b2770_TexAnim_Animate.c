/*
 * Entry: 004b2770
 * Name: TexAnim_Animate
 * Namespace: Global
 * Signature: void TexAnim_Animate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TexAnim_Animate(void)

{
  texanim *ptVar1;
  texanim *ptVar2;
  _OBJ76 *p_Var3;
  texanim *unaff_EDI;
  
  ptVar2 = texanim_list;
  while (ptVar2 != (texanim *)0x0) {
    p_Var3 = validate_obj(ptVar2->obj,"texanim");
    ptVar1 = ptVar2->next;
    ptVar2->obj = p_Var3;
    if (p_Var3 == (_OBJ76 *)0x0) {
      remove_animation(unaff_EDI);
      ptVar2 = ptVar1;
    }
    else {
      (*ptVar2->callback)(p_Var3,ptVar2->tex_name,ptVar2->cb_data);
      ptVar2 = ptVar1;
    }
  }
  return;
}
