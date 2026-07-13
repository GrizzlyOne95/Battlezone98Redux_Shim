/*
 * Entry: 004ecbd5
 * Name: is_vhcl
 * Namespace: Global
 * Signature: int is_vhcl(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl is_vhcl(_OBJ76 *param_1)

{
  OBJECT_CLASS_T OVar1;
  
  if ((param_1 != (_OBJ76 *)0x0) &&
     ((((OVar1 = param_1->class_id, OVar1 == CLASS_ID_VEHICLE || (OVar1 == CLASS_ID_HELICOPTER)) ||
       (OVar1 == CLASS_ID_PERSON)) || (OVar1 == CLASS_ID_POWERUP)))) {
    return 1;
  }
  return 0;
}
