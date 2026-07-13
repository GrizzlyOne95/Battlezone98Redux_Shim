/*
 * Entry: 0052cc96
 * Name: ChargeGunClass::~ChargeGunClass
 * Namespace: ChargeGunClass
 * Signature: void ~ChargeGunClass(ChargeGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ChargeGunClass::~ChargeGunClass(ChargeGunClass *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->ordnanceData != (OrdnanceData *)0x0) {
    operator_delete__(this->ordnanceData);
  }
  CannonClass::~CannonClass((CannonClass *)this);
  return;
}
