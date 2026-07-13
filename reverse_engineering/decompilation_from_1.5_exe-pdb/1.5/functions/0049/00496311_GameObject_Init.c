/*
 * Entry: 00496311
 * Name: GameObject_Init
 * Namespace: Global
 * Signature: void GameObject_Init(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_Init(_OBJ76 *param_1)

{
  Person *pPVar1;
  AiMission *pAVar2;
  
  switch(param_1->class_id) {
  case CLASS_ID_HELICOPTER:
  case CLASS_ID_VEHICLE:
    pPVar1 = (Person *)Craft::Init(param_1);
    break;
  case CLASS_ID_STRUCTURE1:
  case CLASS_ID_SIGN:
  case CLASS_ID_SCRAP:
  case CLASS_ID_STRUCTURE2:
    pPVar1 = (Person *)Building::Init(param_1);
    break;
  case CLASS_ID_POWERUP:
    pPVar1 = (Person *)PowerUp::Init(param_1);
    break;
  case CLASS_ID_PERSON:
    pPVar1 = Person::Init(param_1);
    break;
  default:
    goto switchD_004951ac_caseD_8;
  }
  if ((pPVar1 != (Person *)0x0) && (pAVar2 = AiMission::GetCurrent(), pAVar2 != (AiMission *)0x0)) {
    (**(code **)(pAVar2->_padding_ + 0x14))(pPVar1);
  }
switchD_004951ac_caseD_8:
  return;
}
