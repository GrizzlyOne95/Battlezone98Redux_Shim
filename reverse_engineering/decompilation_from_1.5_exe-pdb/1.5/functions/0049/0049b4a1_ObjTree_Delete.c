/*
 * Entry: 0049b4a1
 * Name: ObjTree_Delete
 * Namespace: Global
 * Signature: int ObjTree_Delete(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjTree_Delete(_OBJ76 *param_1)

{
  if (param_1 == (_OBJ76 *)0x0) {
    return 0;
  }
  GeoCache_Delete(param_1);
  if (bDoSibs == 0) {
    bDoSibs = 1;
    ObjTree_Delete(param_1->child);
    bDoSibs = 0;
  }
  else {
    ObjTree_Delete(param_1->child);
    ObjTree_Delete(param_1->sibling);
  }
  return 1;
}
