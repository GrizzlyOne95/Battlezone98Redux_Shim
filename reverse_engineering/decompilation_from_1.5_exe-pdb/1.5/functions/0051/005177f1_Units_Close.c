/*
 * Entry: 005177f1
 * Name: Units_Close
 * Namespace: Global
 * Signature: void Units_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Units_Close(void)

{
  ObjectClassInfo **ppOVar1;
  Attachment **ppAVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (0 < NRUNITTYPES) {
    do {
      ppOVar1 = std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
                          (&vehicleClassList,uVar3);
      ppAVar2 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                          ((vector<Attachment_*,std::allocator<Attachment_*>_> *)
                           &(*ppOVar1)->objClass->_padding_,attachIndex);
      if (*ppAVar2 != (Attachment *)0x0) {
        (**(code **)**ppAVar2)(1);
        *ppAVar2 = (Attachment *)0x0;
      }
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < NRUNITTYPES);
  }
  return;
}
