/*
 * Entry: 00489f50
 * Name: Crater::UnPackPermState
 * Namespace: Crater
 * Signature: void UnPackPermState(Crater * this, void * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Crater::UnPackPermState(Crater *this,void *param_1,uint param_2)

{
  float fVar1;
  
  this->fx = *(float *)param_1;
  this->fz = *(float *)((int)param_1 + 4);
  fVar1 = *(float *)((int)param_1 + 8);
  this->dy = fVar1;
  if (this->dug == false) {
    MakeCrater(this->fx,this->fz,fVar1);
  }
  this->dug = true;
  DistributedObject::UnPackPermState
            ((DistributedObject *)this,(void *)((int)param_1 + 0xc),param_2 - 0xc);
  return;
}
