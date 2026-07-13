/*
 * Entry: 004b0a7e
 * Name: SObject::IsKindOf
 * Namespace: SObject
 * Signature: bool IsKindOf(SObject * this, RtimeClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SObject::IsKindOf(SObject *this,RtimeClass *param_1)

{
  RtimeClass *pRVar1;
  
  pRVar1 = (RtimeClass *)(**(code **)(this->_padding_ + 0x10))();
  while( true ) {
    if (pRVar1 == (RtimeClass *)0x0) {
      return false;
    }
    if (param_1 == pRVar1) break;
    pRVar1 = pRVar1->base_class;
  }
  return true;
}
