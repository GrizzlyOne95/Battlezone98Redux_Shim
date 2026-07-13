/*
 * Entry: 0045efdb
 * Name: SetPilotClass
 * Namespace: Global
 * Signature: void SetPilotClass(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPilotClass(int param_1,char *param_2)

{
  GameObject *pGVar1;
  GameObjectClass *pGVar2;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    pGVar2 = GameObjectClass::Find(param_2);
    pGVar1->curPilot = pGVar2;
  }
  return;
}
