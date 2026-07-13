/*
 * Entry: 005185c4
 * Name: Class2UnitType
 * Namespace: Global
 * Signature: tagUNITTYPE * Class2UnitType(GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNITTYPE * __cdecl Class2UnitType(GameObjectClass *param_1)

{
  GameObjectClass *in_EAX;
  Attachment **ppAVar1;
  UnitTypeAttachment *pUVar2;
  
  ppAVar1 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                      ((vector<Attachment_*,std::allocator<Attachment_*>_> *)&in_EAX->_padding_,
                       attachIndex);
  pUVar2 = (UnitTypeAttachment *)*ppAVar1;
  if (pUVar2 == (UnitTypeAttachment *)0x0) {
    pUVar2 = operator_new(0x8c);
    if (pUVar2 == (UnitTypeAttachment *)0x0) {
      pUVar2 = (UnitTypeAttachment *)0x0;
    }
    else {
      pUVar2 = UnitTypeAttachment::UnitTypeAttachment(pUVar2,in_EAX);
    }
    ppAVar1 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                        ((vector<Attachment_*,std::allocator<Attachment_*>_> *)&in_EAX->_padding_,
                         attachIndex);
    *ppAVar1 = (Attachment *)pUVar2;
  }
  return &pUVar2->type;
}
