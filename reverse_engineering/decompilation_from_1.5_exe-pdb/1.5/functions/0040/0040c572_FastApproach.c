/*
 * Entry: 0040c572
 * Name: FastApproach
 * Namespace: Global
 * Signature: void FastApproach(ActionInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FastApproach(ActionInfo *param_1)

{
  OBJECT_CLASS_T OVar1;
  float fVar2;
  _OBJ76 *p_Var3;
  
  p_Var3 = param_1->me;
  OVar1 = p_Var3->class_id;
  if ((OVar1 == CLASS_ID_HELICOPTER) || (OVar1 == CLASS_ID_VEHICLE)) {
    Craft_ControlSpeed(p_Var3,1000.0);
    fVar2 = GetApproachAim(param_1->me,p_Var3);
    Craft_ControlHeading(param_1->me,fVar2);
  }
  else if (OVar1 == CLASS_ID_PERSON) {
    Person_ControlSpeed(p_Var3,1000.0);
    fVar2 = GetApproachAim(param_1->me,p_Var3);
    Person_ControlHeading(param_1->me,fVar2);
  }
  return;
}
