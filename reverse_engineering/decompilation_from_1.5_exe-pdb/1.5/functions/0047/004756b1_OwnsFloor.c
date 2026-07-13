/*
 * Entry: 004756b1
 * Name: OwnsFloor
 * Namespace: Global
 * Signature: int OwnsFloor(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OwnsFloor(_OBJ76 *param_1)

{
  OBJECT_CLASS_T OVar1;
  
  OVar1 = param_1->class_id;
  if ((OVar1 != CLASS_ID_STRUCTURE1) && (((int)OVar1 < 8 || (10 < (int)OVar1)))) {
    return 0;
  }
  return 1;
}
