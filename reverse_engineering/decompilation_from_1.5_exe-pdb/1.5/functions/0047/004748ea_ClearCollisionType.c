/*
 * Entry: 004748ea
 * Name: ClearCollisionType
 * Namespace: Global
 * Signature: void ClearCollisionType(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearCollisionType(tagENTITY *param_1)

{
  undefined4 *in_EAX;
  
  if (in_EAX[9] == 3) {
    ClearObjCollision((_OBJ76 *)*in_EAX);
  }
  return;
}
