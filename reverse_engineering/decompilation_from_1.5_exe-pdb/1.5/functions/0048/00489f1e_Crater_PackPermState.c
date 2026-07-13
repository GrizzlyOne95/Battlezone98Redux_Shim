/*
 * Entry: 00489f1e
 * Name: Crater::PackPermState
 * Namespace: Crater
 * Signature: void PackPermState(Crater * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Crater::PackPermState(Crater *this,void *param_1,uint *param_2)

{
  *param_2 = *param_2 + 0xc;
  *(float *)param_1 = this->fx;
  *(float *)((int)param_1 + 4) = this->fz;
  *(float *)((int)param_1 + 8) = this->dy;
  DistributedObject::PackPermState((DistributedObject *)this,(void *)((int)param_1 + 0xc),param_2);
  return;
}
