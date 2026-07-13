/*
 * Entry: 0045fb0b
 * Name: IsBusy
 * Namespace: Global
 * Signature: bool IsBusy(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsBusy(int param_1)

{
  bool bVar1;
  Producer *this;
  int iVar2;
  
  this = (Producer *)GameObjectHandle::GetObj(param_1);
  if (this != (Producer *)0x0) {
    iVar2 = (**(code **)this->_padding_)();
    iVar2 = *(int *)(iVar2 + 0x20);
    if ((((iVar2 == 0x52435943) || (iVar2 == 0x46414354)) || (iVar2 == 0x41524d52)) ||
       (iVar2 == 0x434e5354)) {
      bVar1 = Producer::IsBusy(this);
      return bVar1;
    }
  }
  return false;
}
