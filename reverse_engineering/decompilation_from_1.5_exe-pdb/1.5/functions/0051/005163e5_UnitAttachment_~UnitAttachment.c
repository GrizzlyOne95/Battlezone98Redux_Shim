/*
 * Entry: 005163e5
 * Name: UnitAttachment::~UnitAttachment
 * Namespace: UnitAttachment
 * Signature: void ~UnitAttachment(UnitAttachment * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitAttachment::~UnitAttachment(UnitAttachment *this)

{
  this->_padding_ = (int)&_vftable_;
  if (AI_map != (tag_strategy_map *)0x0) {
    PREREQ_Remove((((this->unit).type)->prereq).prereqtype,(this->unit).team);
    if ((this->unit).special == '\0') {
      AI_UnitRemove(&this->unit);
    }
    teamdata[(this->unit).team].unitcount = teamdata[(this->unit).team].unitcount + -1;
  }
  Attachment::~Attachment((Attachment *)this);
  return;
}
