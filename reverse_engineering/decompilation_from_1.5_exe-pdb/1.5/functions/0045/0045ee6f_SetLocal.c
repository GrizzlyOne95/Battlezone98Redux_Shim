/*
 * Entry: 0045ee6f
 * Name: SetLocal
 * Namespace: Global
 * Signature: void SetLocal(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetLocal(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    DistributedObject::SetLocal((DistributedObject *)&pGVar1->_padding_);
    return;
  }
  return;
}
