/*
 * Entry: 004e29fa
 * Name: std::map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>::operator[]
 * Namespace: std::map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
 * Signature: NetPlayer * * operator[](map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_> * this, ushort * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NetPlayer ** __thiscall
std::
map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
::operator[](map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
             *this,ushort *param_1)

{
  const_iterator cVar1;
  bool bVar2;
  pair<unsigned_short_const_,NetPlayer_*> *ppVar3;
  iterator iVar4;
  undefined1 local_1c [8];
  const_iterator local_14;
  const_iterator local_c;
  
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::lower_bound((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                 *)this,(ushort *)&local_c);
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_14,*(_Node **)&this->field_0x18,
             (_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
              *)this);
  bVar2 = _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==(&local_c,&local_14);
  if ((bVar2) || (*param_1 < ((local_c._Ptr)->_Myval).first)) {
    local_14._padding_._0_2_ = *param_1;
    local_14._Ptr = (_Node *)0x0;
    cVar1._Ptr = (_Node *)local_c._padding_;
    cVar1._padding_ = (int)local_1c;
    iVar4 = _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::insert((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
                      *)this,cVar1,(pair<unsigned_short_const_,NetPlayer_*> *)local_c._Ptr);
    local_c._padding_ = *iVar4._0_4_;
    local_c._Ptr = (_Node *)iVar4._0_4_[1];
  }
  ppVar3 = _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
           ::const_iterator::operator*(&local_c);
  return &ppVar3->second;
}
