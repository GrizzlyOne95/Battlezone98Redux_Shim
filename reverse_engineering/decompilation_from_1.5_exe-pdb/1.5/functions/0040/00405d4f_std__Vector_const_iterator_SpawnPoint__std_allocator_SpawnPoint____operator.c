/*
 * Entry: 00405d4f
 * Name: std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: SpawnPoint * * operator*(_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __thiscall
std::_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::operator*
          (_Vector_const_iterator<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00405d6d;
    }
  }
  iVar2 = *piVar1;
LAB_00405d6d:
  if (*(SpawnPoint ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
