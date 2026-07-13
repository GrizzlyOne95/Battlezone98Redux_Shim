/*
 * Entry: 00516377
 * Name: AIScheduleFeature::AIScheduleFeature
 * Namespace: AIScheduleFeature
 * Signature: AIScheduleFeature * AIScheduleFeature(AIScheduleFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AIScheduleFeature * __thiscall AIScheduleFeature::AIScheduleFeature(AIScheduleFeature *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x8 = 0x14;
  return this;
}
