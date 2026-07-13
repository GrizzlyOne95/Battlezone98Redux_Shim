/*
 * Entry: 00405df2
 * Name: IsCraft
 * Namespace: Global
 * Signature: int IsCraft(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsCraft(_OBJ76 *param_1)

{
  if ((param_1->class_id != CLASS_ID_HELICOPTER) && (param_1->class_id != CLASS_ID_VEHICLE)) {
    return 0;
  }
  return 1;
}
