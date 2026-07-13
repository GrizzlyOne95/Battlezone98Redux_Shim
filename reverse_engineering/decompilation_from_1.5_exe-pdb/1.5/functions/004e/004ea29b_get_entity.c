/*
 * Entry: 004ea29b
 * Name: get_entity
 * Namespace: Global
 * Signature: tagENTITY * get_entity(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl get_entity(void)

{
  tagENTITY *ptVar1;
  
  if (current_entity_ptr < world_count) {
    ptVar1 = world + current_entity_ptr;
    do {
      current_entity_ptr = current_entity_ptr + 1;
      if (ptVar1->obj76 != (_OBJ76 *)0x0) {
        return ptVar1;
      }
      ptVar1 = ptVar1 + 1;
    } while (current_entity_ptr < world_count);
  }
  return (tagENTITY *)0x0;
}
