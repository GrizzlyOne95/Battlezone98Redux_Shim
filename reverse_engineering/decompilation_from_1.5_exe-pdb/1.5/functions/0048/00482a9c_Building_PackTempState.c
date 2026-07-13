/*
 * Entry: 00482a9c
 * Name: Building::PackTempState
 * Namespace: Building
 * Signature: void PackTempState(Building * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Building::PackTempState(Building *this,void *param_1,uint *param_2)

{
  *param_2 = *param_2 + 4;
  *(int *)param_1 = this->_padding_;
  this->_padding_ = this->_padding_;
  return;
}
