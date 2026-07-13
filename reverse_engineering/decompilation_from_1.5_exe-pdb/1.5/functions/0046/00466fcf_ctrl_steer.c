/*
 * Entry: 00466fcf
 * Name: ctrl_steer
 * Namespace: Global
 * Signature: void ctrl_steer(_OBJ76 * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ctrl_steer(_OBJ76 *param_1,float param_2)

{
  OBJECT_CLASS_T OVar1;
  
  OVar1 = param_1->class_id;
  if ((OVar1 == CLASS_ID_HELICOPTER) || (OVar1 == CLASS_ID_VEHICLE)) {
    Craft_ControlHeading(param_1,param_2);
  }
  else if (OVar1 == CLASS_ID_PERSON) {
    Person_ControlHeading(param_1,param_2);
  }
  return;
}
