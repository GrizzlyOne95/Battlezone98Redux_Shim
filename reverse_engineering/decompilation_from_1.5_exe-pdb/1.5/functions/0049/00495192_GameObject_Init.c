/*
 * Entry: 00495192
 * Name: GameObject::Init
 * Namespace: GameObject
 * Signature: GameObject * Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GameObject::Init(_OBJ76 *param_1)

{
  AiMission *pAVar1;
  Person *pPVar2;
  
  pPVar2 = (Person *)0x0;
  switch(param_1->class_id) {
  case CLASS_ID_HELICOPTER:
  case CLASS_ID_VEHICLE:
    pPVar2 = (Person *)Craft::Init(param_1);
    break;
  case CLASS_ID_STRUCTURE1:
  case CLASS_ID_SIGN:
  case CLASS_ID_SCRAP:
  case CLASS_ID_STRUCTURE2:
    pPVar2 = (Person *)Building::Init(param_1);
    break;
  case CLASS_ID_POWERUP:
    pPVar2 = (Person *)PowerUp::Init(param_1);
    break;
  case CLASS_ID_PERSON:
    pPVar2 = Person::Init(param_1);
    break;
  default:
    goto switchD_004951ac_caseD_8;
  }
  if ((pPVar2 != (Person *)0x0) && (pAVar1 = AiMission::GetCurrent(), pAVar1 != (AiMission *)0x0)) {
    (**(code **)(pAVar1->_padding_ + 0x14))(pPVar2);
  }
switchD_004951ac_caseD_8:
  return (GameObject *)pPVar2;
}
