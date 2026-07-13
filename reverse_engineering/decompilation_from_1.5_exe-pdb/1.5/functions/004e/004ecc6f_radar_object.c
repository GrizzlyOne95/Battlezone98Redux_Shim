/*
 * Entry: 004ecc6f
 * Name: radar_object
 * Namespace: Global
 * Signature: int radar_object(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl radar_object(_OBJ76 *param_1)

{
  if ((param_1->class_id != CLASS_ID_HELICOPTER) && (param_1->class_id != CLASS_ID_VEHICLE)) {
    return 0;
  }
  return 1;
}
