/*
 * Entry: 00460104
 * Name: Dropoff
 * Namespace: Global
 * Signature: void Dropoff(int param_1, VECTOR_3D * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Dropoff(int param_1,VECTOR_3D *param_2,int param_3)

{
  GameObject *pGVar1;
  AiPath *this;
  VECTOR_3D *pVVar2;
  int unaff_EDI;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    this = operator_new(0x1c);
    if (this != (AiPath *)0x0) {
      pVVar2 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
      AiPath::AiPath(this,pVVar2,param_2);
    }
    Dropoff(pGVar1,(AiPath *)param_3,unaff_EDI);
  }
  return;
}
