/*
 * Entry: 004ed30b
 * Name: Find_Object_Info
 * Namespace: Global
 * Signature: OBJECT_NODE * Find_Object_Info(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OBJECT_NODE * __cdecl Find_Object_Info(_OBJ76 *param_1)

{
  long lVar1;
  _OBJ76 *unaff_ESI;
  
  lVar1 = object_table[((int)unaff_ESI * 0x6cd + 0xaabU) % 0x71];
  while( true ) {
    if (lVar1 == -1) {
      return (OBJECT_NODE *)0x0;
    }
    if (objectdb[lVar1].obj == unaff_ESI) break;
    lVar1 = objectdb[lVar1].next;
  }
  return objectdb + lVar1;
}
