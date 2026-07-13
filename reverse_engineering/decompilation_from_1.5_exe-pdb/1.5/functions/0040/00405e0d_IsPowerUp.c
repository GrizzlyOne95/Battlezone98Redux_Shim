/*
 * Entry: 00405e0d
 * Name: IsPowerUp
 * Namespace: Global
 * Signature: int IsPowerUp(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsPowerUp(_OBJ76 *param_1)

{
  return (uint)(param_1->class_id == CLASS_ID_POWERUP);
}
