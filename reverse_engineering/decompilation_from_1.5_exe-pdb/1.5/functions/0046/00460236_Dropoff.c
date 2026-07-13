/*
 * Entry: 00460236
 * Name: Dropoff
 * Namespace: Global
 * Signature: void Dropoff(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Dropoff(int param_1,char *param_2,int param_3)

{
  GameObject *pGVar1;
  AiPath *pAVar2;
  int unaff_EBX;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if ((pGVar1 != (GameObject *)0x0) &&
     ((param_2 == (char *)0x0 || (pAVar2 = AiPath::Find(param_2), pAVar2 != (AiPath *)0x0)))) {
    Dropoff(pGVar1,(AiPath *)param_3,unaff_EBX);
  }
  return;
}
