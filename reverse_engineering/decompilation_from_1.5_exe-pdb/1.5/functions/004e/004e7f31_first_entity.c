/*
 * Entry: 004e7f31
 * Name: first_entity
 * Namespace: Global
 * Signature: tagENTITY * first_entity(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl first_entity(void)

{
  tagENTITY *ptVar1;
  
  reset_entity_pointer();
  ptVar1 = get_entity();
  return ptVar1;
}
