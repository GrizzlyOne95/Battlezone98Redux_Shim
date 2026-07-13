/*
 * Entry: 00534a78
 * Name: Ordnance::~Ordnance
 * Namespace: Ordnance
 * Signature: void ~Ordnance(Ordnance * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Ordnance::~Ordnance(Ordnance *this)

{
  pair<unsigned_short,unsigned_short> local_8;
  
  this->_padding_ = (int)&_vftable_;
  if (this->source != 0xfa01) {
    local_8.second = this->ordid;
    local_8.first = this->source;
    std::
    _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
    ::erase((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
             *)&netOrdnanceMap,&local_8);
  }
  return;
}
