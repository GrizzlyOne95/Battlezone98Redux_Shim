/*
 * Entry: 004ecc4a
 * Name: dynamic_object
 * Namespace: Global
 * Signature: int dynamic_object(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl dynamic_object(_OBJ76 *param_1)

{
  OBJECT_CLASS_T OVar1;
  
  OVar1 = param_1->class_id;
  if ((OVar1 != CLASS_ID_HELICOPTER) &&
     (((int)OVar1 < 3 || ((4 < (int)OVar1 && (OVar1 != CLASS_ID_VEHICLE)))))) {
    return 0;
  }
  return 1;
}
