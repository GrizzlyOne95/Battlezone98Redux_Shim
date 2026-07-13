/*
 * Entry: 00518c24
 * Name: Obj2Unit
 * Namespace: Global
 * Signature: tagUNIT * Obj2Unit(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNIT * __cdecl Obj2Unit(GameObject *param_1)

{
  float fVar1;
  Attachment **ppAVar2;
  UnitAttachment *pUVar3;
  float *pfVar4;
  int iVar5;
  int extraout_EAX;
  
  ppAVar2 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                      ((vector<Attachment_*,std::allocator<Attachment_*>_> *)&param_1->_padding_,
                       attachIndex);
  pUVar3 = (UnitAttachment *)*ppAVar2;
  if (pUVar3 == (UnitAttachment *)0x0) {
    pUVar3 = operator_new(0x70);
    if (pUVar3 == (UnitAttachment *)0x0) {
      pUVar3 = (UnitAttachment *)0x0;
    }
    else {
      pUVar3 = UnitAttachment::UnitAttachment(pUVar3,(Craft *)param_1);
    }
    ppAVar2 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                        ((vector<Attachment_*,std::allocator<Attachment_*>_> *)&param_1->_padding_,
                         attachIndex);
    *ppAVar2 = (Attachment *)pUVar3;
  }
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar1 = pfVar4[2];
  iVar5 = PosX2POS((double)*pfVar4);
  (pUVar3->unit).tilepos.x = iVar5;
  iVar5 = PosZ2POS((double)fVar1);
  (pUVar3->unit).tilepos.y = iVar5;
  _ftol2_sse();
  (pUVar3->unit).hitpoints = extraout_EAX;
  (pUVar3->unit).perceived_team = (char)param_1->perceivedTeam;
  return &pUVar3->unit;
}
