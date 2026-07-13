/*
 * Entry: 004e6594
 * Name: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Buy
 * Namespace: std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>
 * Signature: bool _Buy(vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_>::_Buy
          (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *this,uint param_1)

{
  bool bVar1;
  SpawnPoint **ppSVar2;
  
  this->_Myfirst = (SpawnPoint **)0x0;
  this->_Mylast = (SpawnPoint **)0x0;
  this->_Myend = (SpawnPoint **)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x40000000) {
      ppSVar2 = _Allocate<SpawnPoint_*>(param_1,(SpawnPoint **)0x0);
      this->_Myfirst = ppSVar2;
      this->_Mylast = ppSVar2;
      this->_Myend = ppSVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
