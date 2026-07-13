/*
 * Entry: 005373fb
 * Name: RadarDamper::~RadarDamper
 * Namespace: RadarDamper
 * Signature: void ~RadarDamper(RadarDamper * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RadarDamper::~RadarDamper(RadarDamper *this)

{
  uint *puVar1;
  
  *(undefined ***)this = &_vftable_;
  if ((*(byte *)(*(int *)&this->field_0x18 + 0x14) & 1) != 0) {
    puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  SpecialItem::~SpecialItem((SpecialItem *)this);
  return;
}
