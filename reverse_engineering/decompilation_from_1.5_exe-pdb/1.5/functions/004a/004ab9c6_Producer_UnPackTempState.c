/*
 * Entry: 004ab9c6
 * Name: Producer::UnPackTempState
 * Namespace: Producer
 * Signature: void UnPackTempState(Producer * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::UnPackTempState(Producer *this,void *param_1,uint *param_2)

{
  Producer *this_00;
  char cVar1;
  
  this_00 = (Producer *)(this[-1].smokeList + 5);
  HasPower(this_00);
  cVar1 = *(char *)param_1;
  if (cVar1 != '\0') {
    if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
      (**(code **)(this_00->_padding_ + 0x5c))();
      goto LAB_004ab9fb;
    }
    if (cVar1 != '\x03') goto LAB_004ab9fb;
  }
  (**(code **)(this_00->_padding_ + 0x60))();
LAB_004ab9fb:
  *param_2 = *param_2 - 1;
  HoverCraft::UnPackTempState((HoverCraft *)this,(void *)((int)param_1 + 1),param_2);
  return;
}
