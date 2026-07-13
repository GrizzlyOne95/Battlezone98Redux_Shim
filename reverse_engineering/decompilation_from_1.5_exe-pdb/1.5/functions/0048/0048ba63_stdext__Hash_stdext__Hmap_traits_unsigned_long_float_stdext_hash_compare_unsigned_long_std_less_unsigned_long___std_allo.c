/*
 * Entry: 0048ba63
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>::_Hashval
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
 * Signature: uint _Hashval(_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_> * this, ulong * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
::_Hashval(_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
           *this,ulong *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = this->_Mask;
  uVar2 = hash_compare<unsigned_long,std::less<unsigned_long>_>::operator()
                    ((hash_compare<unsigned_long,std::less<unsigned_long>_> *)&this->_padding_,
                     param_1);
  uVar2 = uVar2 & uVar1;
  if (this->_Maxidx <= uVar2) {
    uVar2 = uVar2 + (-1 - (uVar1 >> 1));
  }
  return uVar2;
}
