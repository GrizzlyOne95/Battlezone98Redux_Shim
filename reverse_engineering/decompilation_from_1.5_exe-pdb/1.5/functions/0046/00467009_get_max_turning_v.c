/*
 * Entry: 00467009
 * Name: get_max_turning_v
 * Namespace: Global
 * Signature: float get_max_turning_v(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl get_max_turning_v(_OBJ76 *param_1)

{
  int iVar1;
  float fVar2;
  
  iVar1 = IsCraft(param_1);
  if (iVar1 == 0) {
    if (param_1->class_id != CLASS_ID_PERSON) {
      return 0.0;
    }
    fVar2 = Person_MaxTurningSpeed(param_1);
  }
  else {
    fVar2 = Craft_MaxTurningSpeed(param_1);
  }
  return fVar2;
}
