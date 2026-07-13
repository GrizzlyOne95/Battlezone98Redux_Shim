/*
 * Entry: 0046f892
 * Name: GameObject_GetFromObj
 * Namespace: Global
 * Signature: GameObject * GameObject_GetFromObj(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GameObject_GetFromObj(_OBJ76 *param_1)

{
  if (param_1 != (_OBJ76 *)0x0) {
    return param_1->gameObj;
  }
  return (GameObject *)0x0;
}
