/*
 * Entry: 005178e7
 * Name: Build_Close
 * Namespace: Global
 * Signature: void Build_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Build_Close(void)

{
  ObjectClassInfo **ppOVar1;
  Attachment **ppAVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (0 < maxbuildingtypes) {
    do {
      ppOVar1 = std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
                          (&buildingClassList,uVar3);
      ppAVar2 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                          ((vector<Attachment_*,std::allocator<Attachment_*>_> *)
                           &(*ppOVar1)->objClass->_padding_,attachIndex);
      if (*ppAVar2 != (Attachment *)0x0) {
        (**(code **)**ppAVar2)(1);
        *ppAVar2 = (Attachment *)0x0;
      }
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < maxbuildingtypes);
  }
  maxbuildingtypes = 0;
  if (buildingtypes != (tagBUILDINGTYPE *)0x0) {
    operator_delete__(buildingtypes);
    buildingtypes = (tagBUILDINGTYPE *)0x0;
  }
  return;
}
