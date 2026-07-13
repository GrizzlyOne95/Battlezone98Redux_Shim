/*
 * Entry: 004e9f21
 * Name: Entity_Clear
 * Namespace: Global
 * Signature: void Entity_Clear(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Entity_Clear(tagENTITY *param_1)

{
  memset(param_1,0,0xc4);
  param_1->cType = CLSN_TYPE_NONCOLLIDE;
  return;
}
