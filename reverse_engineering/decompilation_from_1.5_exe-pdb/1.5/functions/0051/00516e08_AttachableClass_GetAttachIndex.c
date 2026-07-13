/*
 * Entry: 00516e08
 * Name: AttachableClass::GetAttachIndex
 * Namespace: AttachableClass
 * Signature: int GetAttachIndex(AttachableClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AttachableClass::GetAttachIndex(AttachableClass *this)

{
  int iVar1;
  
  iVar1 = this->attachCount;
  this->attachCount = iVar1 + 1;
  return iVar1;
}
