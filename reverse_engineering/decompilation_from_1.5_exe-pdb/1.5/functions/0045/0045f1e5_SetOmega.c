/*
 * Entry: 0045f1e5
 * Name: SetOmega
 * Namespace: Global
 * Signature: void SetOmega(int param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetOmega(int param_1,VECTOR_3D *param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    (pGVar1->euler).omega.x = param_2->x;
    (pGVar1->euler).omega.y = param_2->y;
    (pGVar1->euler).omega.z = param_2->z;
  }
  return;
}
