/*
 * Entry: 00474519
 * Name: ClearObjCollision
 * Namespace: Global
 * Signature: void ClearObjCollision(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearObjCollision(_OBJ76 *param_1)

{
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    if ((param_1->flags & 0xf000) == 0x3000) {
      Cgeom_Delete(param_1);
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      ClearObjCollision(param_1->child);
    }
  }
  return;
}
