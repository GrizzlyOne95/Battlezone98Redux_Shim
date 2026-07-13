/*
 * Entry: 0047dc3f
 * Name: APC::UnPackTempState
 * Namespace: APC
 * Signature: void UnPackTempState(APC * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APC::UnPackTempState(APC *this,void *param_1,uint *param_2)

{
  char cVar1;
  
  cVar1 = *(char *)param_1;
  if (cVar1 != '\0') {
    if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
      (**(code **)(this[-1]._padding_ + 0x5c))();
      goto LAB_0047dc6b;
    }
    if (cVar1 != '\x03') goto LAB_0047dc6b;
  }
  (**(code **)(this[-1]._padding_ + 0x60))();
LAB_0047dc6b:
  *param_2 = *param_2 - 1;
  HoverCraft::UnPackTempState((HoverCraft *)this,(void *)((int)param_1 + 1),param_2);
  return;
}
