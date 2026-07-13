/*
 * Entry: 00482abc
 * Name: Building::PackPermState
 * Namespace: Building
 * Signature: void PackPermState(Building * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Building::PackPermState(Building *this,void *param_1,uint *param_2)

{
  *param_2 = *param_2 + 4;
  *(int *)param_1 = this->_padding_;
  return;
}
