/*
 * Entry: 004b9639
 * Name: WingmanClass::WingmanClass
 * Namespace: WingmanClass
 * Signature: WingmanClass * WingmanClass(WingmanClass * this, WingmanClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WingmanClass * __thiscall
WingmanClass::WingmanClass(WingmanClass *this,WingmanClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
