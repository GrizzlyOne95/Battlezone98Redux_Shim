/*
 * Entry: 004b9605
 * Name: WingmanClass::WingmanClass
 * Namespace: WingmanClass
 * Signature: WingmanClass * WingmanClass(WingmanClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WingmanClass * __thiscall WingmanClass::WingmanClass(WingmanClass *this)

{
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x57494e47;
  *(char **)&this->field_0x24 = "wingman";
  *(undefined4 *)&this->field_0x144 = 5;
  *(undefined4 *)&this->field_0x148 = 0xe;
  return this;
}
