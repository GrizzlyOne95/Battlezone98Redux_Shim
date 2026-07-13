/*
 * Entry: 0048bce5
 * Name: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>::load_factor
 * Namespace: stdext::_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
 * Signature: float load_factor(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall
stdext::
_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
::load_factor(_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
              *this)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)(int)(this->_List)._Mysize;
  if ((int)(this->_List)._Mysize < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  fVar2 = (float)(int)this->_Maxidx;
  if ((int)this->_Maxidx < 0) {
    fVar2 = fVar2 + 4.2949673e+09;
  }
  return fVar1 / fVar2;
}
