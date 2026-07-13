/*
 * Entry: 004ea2dc
 * Name: is_user_dead
 * Namespace: Global
 * Signature: int is_user_dead(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl is_user_dead(void)

{
  if (user_entity_ptr != (tagENTITY *)0x0) {
    return *(uint *)((int)user_entity_ptr->obj76->class_ptr + 0x10c) & 0x20;
  }
  return 0;
}
