/*
 * Entry: 004b246e
 * Name: remove_animation
 * Namespace: Global
 * Signature: int remove_animation(texanim * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl remove_animation(texanim *param_1)

{
  texanim *ptVar1;
  void *unaff_ESI;
  
  ptVar1 = *(texanim **)((int)unaff_ESI + 0x20);
  if (*(texanim **)((int)unaff_ESI + 0x1c) == (texanim *)0x0) {
    texanim_list = ptVar1;
    if (*(int *)((int)unaff_ESI + 0x20) != 0) {
      *(undefined4 *)(*(int *)((int)unaff_ESI + 0x20) + 0x1c) = 0;
    }
  }
  else {
    if (ptVar1 != (texanim *)0x0) {
      ptVar1->prev = *(texanim **)((int)unaff_ESI + 0x1c);
    }
    *(undefined4 *)(*(int *)((int)unaff_ESI + 0x1c) + 0x20) = *(undefined4 *)((int)unaff_ESI + 0x20)
    ;
  }
  if (*(code **)((int)unaff_ESI + 0x14) == loopanim_cb) {
    operator_delete(*(void **)((int)unaff_ESI + 0x18));
  }
  operator_delete(unaff_ESI);
  return 1;
}
