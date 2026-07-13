/*
 * Entry: 0051424e
 * Name: Mapgrid_Goal::Is_Satisfied
 * Namespace: Mapgrid_Goal
 * Signature: int Is_Satisfied(Mapgrid_Goal * this, int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Mapgrid_Goal::Is_Satisfied(Mapgrid_Goal *this,int *param_1)

{
  int iVar1;
  
  if ((this->_padding_ == 0) || (iVar1 = *(int *)(this->_padding_ + 0x34), iVar1 < this->_padding_))
  {
    iVar1 = 0;
  }
  else {
    *param_1 = iVar1 - this->_padding_;
    iVar1 = 1;
  }
  return iVar1;
}
