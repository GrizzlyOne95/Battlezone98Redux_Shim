/*
 * Entry: 00518615
 * Name: UnitAttachment::UnitAttachment
 * Namespace: UnitAttachment
 * Signature: UnitAttachment * UnitAttachment(UnitAttachment * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnitAttachment * __thiscall UnitAttachment::UnitAttachment(UnitAttachment *this,Craft *param_1)

{
  tagUNIT *ptVar1;
  char cVar2;
  int iVar3;
  tagUNITTYPE *ptVar4;
  GameObjectClass *unaff_EDI;
  
  ptVar1 = &this->unit;
  this->_padding_ = (int)&_vftable_;
  memset(ptVar1,0,0x6c);
  ptVar1->id = (int)param_1;
  if (param_1 == (Craft *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = GameObject::GetHandle((GameObject *)param_1);
  }
  (this->unit).handle = iVar3;
  iVar3 = (**(code **)param_1->_padding_)();
  ptVar4 = Class2UnitType(unaff_EDI);
  (this->unit).type = ptVar4;
  cVar2 = (**(code **)(param_1->_padding_ + 4))();
  (this->unit).team = cVar2;
  (this->unit).movemode = (*(int *)(iVar3 + 0x20) != 0x54554700) + MM_FIXED;
  (this->unit).special = 0 < *(int *)(ptVar1->id + 0xac);
  if (AI_map != (tag_strategy_map *)0x0) {
    teamdata[(this->unit).team].unitcount = teamdata[(this->unit).team].unitcount + 1;
    PREREQ_Add((((this->unit).type)->prereq).prereqtype,(this->unit).team);
    cVar2 = (this->unit).team;
    if ((teamdata[cVar2].aicontrol != '\0') &&
       (number_under_construction[cVar2][(((this->unit).type)->prereq).prereqtype] == 0)) {
      number_under_construction[(this->unit).team][(((this->unit).type)->prereq).prereqtype] =
           number_under_construction[(this->unit).team][(((this->unit).type)->prereq).prereqtype] +
           1;
    }
    if ((this->unit).special == '\0') {
      AI_UnitAdd(ptVar1,(tagBUILDING *)0x0);
    }
  }
  return this;
}
