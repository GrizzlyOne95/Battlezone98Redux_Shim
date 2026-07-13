/*
 * Entry: 00534d9d
 * Name: OrdnanceClass::~OrdnanceClass
 * Namespace: OrdnanceClass
 * Signature: void ~OrdnanceClass(OrdnanceClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OrdnanceClass::~OrdnanceClass(OrdnanceClass *this)

{
  this->_padding_ = (int)&_vftable_;
  remove_obj(this->freeOrd,".\\fun3d\\OrdnanceClass.cpp");
  if (this->ord != (_OBJ76 *)0x0) {
    GeoCache_Delete(this->ord);
    remove_obj(this->ord,".\\fun3d\\OrdnanceClass.cpp");
  }
  return;
}
