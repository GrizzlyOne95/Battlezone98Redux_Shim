/*
 * Entry: 0047013f
 * Name: SetupUserProcess
 * Namespace: Global
 * Signature: void SetupUserProcess(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetupUserProcess(_OBJ76 *param_1)

{
  AiMission *pAVar1;
  UserProcess *this;
  GameObject *pGVar2;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pGVar2 = (GameObject *)0x0;
  }
  else {
    pGVar2 = param_1->gameObj;
  }
  pAVar1 = AiMission::GetCurrent();
  this = operator_new(0x70);
  if (this != (UserProcess *)0x0) {
    UserProcess::UserProcess(this,pAVar1,pGVar2);
  }
  return;
}
