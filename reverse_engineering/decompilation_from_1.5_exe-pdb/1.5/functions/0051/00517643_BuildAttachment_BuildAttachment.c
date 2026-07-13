/*
 * Entry: 00517643
 * Name: BuildAttachment::BuildAttachment
 * Namespace: BuildAttachment
 * Signature: BuildAttachment * BuildAttachment(BuildAttachment * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BuildAttachment * __thiscall
BuildAttachment::BuildAttachment(BuildAttachment *this,GameObject *param_1)

{
  tagBUILDINGTYPE *ptVar1;
  int iVar2;
  tagBUILDINGTYPE *unaff_ESI;
  GameObjectClass *unaff_EDI;
  
  this->_padding_ = (int)&_vftable_;
  memset(&this->build,0,0x38);
  (this->build).id = (int)param_1;
  (**(code **)param_1->_padding_)();
  ptVar1 = Class2BuildingType(unaff_EDI,unaff_ESI);
  (this->build).buildingtype = ptVar1;
  iVar2 = (**(code **)(param_1->_padding_ + 4))();
  (this->build).order = 0;
  (this->build).team = iVar2;
  (this->build).seeingrange = '\n';
  PREREQ_Add(((this->build).buildingtype)->prereqtype,(char)iVar2);
  return this;
}
