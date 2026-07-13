/*
 * Entry: 004ed34c
 * Name: Find_Inter_Object_Info
 * Namespace: Global
 * Signature: INTER_OBJECT_NODE * Find_Inter_Object_Info(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

INTER_OBJECT_NODE * __cdecl Find_Inter_Object_Info(_OBJ76 *param_1,_OBJ76 *param_2)

{
  long lVar1;
  _OBJ76 *unaff_ESI;
  _OBJ76 *unaff_EDI;
  
  lVar1 = inter_object_table[(((uint)unaff_ESI ^ (uint)unaff_EDI) * 0x6cd + 0xaab) % 0x9c7];
  while( true ) {
    if (lVar1 == -1) {
      return (INTER_OBJECT_NODE *)0x0;
    }
    if ((inter_objectdb[lVar1].objA == unaff_ESI) && (inter_objectdb[lVar1].objB == unaff_EDI))
    break;
    lVar1 = inter_objectdb[lVar1].next;
  }
  return inter_objectdb + lVar1;
}
