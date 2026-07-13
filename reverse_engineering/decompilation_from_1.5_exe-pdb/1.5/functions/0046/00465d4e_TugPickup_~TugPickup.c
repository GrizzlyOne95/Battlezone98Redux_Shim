/*
 * Entry: 00465d4e
 * Name: TugPickup::~TugPickup
 * Namespace: TugPickup
 * Signature: void ~TugPickup(TugPickup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugPickup::~TugPickup(TugPickup *this)

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
