/*
 * Entry: 004571ff
 * Name: PersonGetIn::~PersonGetIn
 * Namespace: PersonGetIn
 * Signature: void ~PersonGetIn(PersonGetIn * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonGetIn::~PersonGetIn(PersonGetIn *this)

{
  *(undefined ***)this = &GotoTask::_vftable_;
  GotoTask::CleanState((GotoTask *)this);
  *(undefined4 *)&this->field_0xc = 0xd;
  if ((this->field_0x140 != '\0') && (*(AiPath **)&this->field_0x138 != (AiPath *)0x0)) {
    AiPath::Release(*(AiPath **)&this->field_0x138);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
