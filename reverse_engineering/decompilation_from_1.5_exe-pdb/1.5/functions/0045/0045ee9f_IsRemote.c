/*
 * Entry: 0045ee9f
 * Name: IsRemote
 * Namespace: Global
 * Signature: bool IsRemote(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsRemote(int param_1)

{
  bool bVar1;
  GameObject *pGVar2;
  
  pGVar2 = GameObjectHandle::GetObj(param_1);
  if (pGVar2 == (GameObject *)0x0) {
    return false;
  }
  bVar1 = DistributedObject::IsRemote((DistributedObject *)&pGVar2->_padding_);
  return bVar1;
}
