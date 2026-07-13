/*
 * Entry: 00473b91
 * Name: ClearCollision
 * Namespace: Global
 * Signature: void ClearCollision(CLSN_INFO * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearCollision(CLSN_INFO *param_1)

{
  param_1->collided = 0;
  param_1->obj = (_OBJ76 *)0x0;
  (param_1->normal).x = 0.0;
  (param_1->normal).y = 0.0;
  (param_1->normal).z = 0.0;
  InitEuler(&param_1->euler);
  return;
}
