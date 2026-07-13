/*
 * Entry: 0047487b
 * Name: InitCollisionType
 * Namespace: Global
 * Signature: void InitCollisionType(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitCollisionType(tagENTITY *param_1)

{
  tagENTITY *in_ECX;
  
  switch(in_ECX->obj76->class_id) {
  case CLASS_ID_HELICOPTER:
  case CLASS_ID_POWERUP:
  case CLASS_ID_PERSON:
    SetCarSphere(in_ECX);
    return;
  case CLASS_ID_STRUCTURE1:
  case CLASS_ID_VEHICLE:
  case CLASS_ID_BRIDGE:
  case CLASS_ID_STRUCTURE2:
    CurrentDefaultCollision = 0x3000;
    break;
  case CLASS_ID_SIGN:
  case CLASS_ID_SCRAP:
  case CLASS_ID_SPINNER:
    CurrentDefaultCollision = 0x2000;
    break;
  default:
    goto switchD_00474890_caseD_9;
  }
  in_ECX->cType = CLSN_TYPE_CHILDREN;
  SetObjCollision(in_ECX->obj76,&Identity_Matrix);
switchD_00474890_caseD_9:
  return;
}
