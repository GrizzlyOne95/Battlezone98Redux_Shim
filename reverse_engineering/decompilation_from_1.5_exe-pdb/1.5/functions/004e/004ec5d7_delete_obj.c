/*
 * Entry: 004ec5d7
 * Name: delete_obj
 * Namespace: Global
 * Signature: void delete_obj(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl delete_obj(_OBJ76 *param_1)

{
  _OBJ76 **pp_Var1;
  _OBJ76 *p_Var2;
  _OBJ76 *p_Var3;
  _OBJ76 *unaff_ESI;
  
  if (unaff_ESI != (_OBJ76 *)0x0) {
    if (unaff_ESI->parent != (_OBJ76 *)0x0) {
      pp_Var1 = &unaff_ESI->parent->child;
      p_Var2 = *pp_Var1;
      if (p_Var2 == unaff_ESI) {
        *pp_Var1 = unaff_ESI->sibling;
      }
      else {
        do {
          p_Var3 = p_Var2;
          if (p_Var3 == (_OBJ76 *)0x0) goto LAB_004ec61d;
          p_Var2 = p_Var3->sibling;
        } while (p_Var3->sibling != unaff_ESI);
        p_Var3->sibling = unaff_ESI->sibling;
      }
    }
LAB_004ec61d:
    if (unaff_ESI->child != (_OBJ76 *)0x0) {
      unaff_ESI->child->parent = (_OBJ76 *)0x0;
    }
    ZapClass(unaff_ESI->class_id,unaff_ESI->class_ptr);
    unaff_ESI->class_id = CLASS_ID_NONE;
    unaff_ESI->class_ptr = (void *)0x0;
    GeoCache_Delete(unaff_ESI);
    Texture_Delete(unaff_ESI);
    if ((unaff_ESI->flags & 0x800) != 0) {
      Remove_Light_Source(unaff_ESI);
    }
    (unaff_ESI->objHandle).handle = 0;
    unaff_ESI->sibling = free_head;
    free_head = unaff_ESI;
  }
  return;
}
