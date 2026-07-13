/*
 * Entry: 0040a67f
 * Name: std::map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>::operator[]
 * Namespace: std::map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
 * Signature: Area * operator[](map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_> * this, GameObject * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Area * __thiscall
std::
map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
::operator[](map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
             *this,GameObject **param_1)

{
  const_iterator cVar1;
  bool bVar2;
  pair<GameObject_*_const,Area> *ppVar3;
  iterator iVar4;
  const_iterator local_14;
  const_iterator local_c;
  
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::lower_bound((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                 *)this,(GameObject **)&local_c);
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::const_iterator::const_iterator
            (&local_14,*(_Node **)&this->field_0x18,
             (_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
              *)this);
  bVar2 = _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
          ::const_iterator::operator==(&local_c,&local_14);
  if ((bVar2) || (*param_1 < ((local_c._Ptr)->_Myval).first)) {
    local_14._padding_ = 0;
    local_14._Ptr = (_Node *)0x0;
    cVar1._Ptr = (_Node *)local_c._padding_;
    cVar1._padding_ = (int)&local_14;
    iVar4 = _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
            ::insert((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
                      *)this,cVar1,(pair<GameObject_*_const,Area> *)local_c._Ptr);
    local_c._padding_ = *iVar4._0_4_;
    local_c._Ptr = (_Node *)iVar4._0_4_[1];
  }
  ppVar3 = _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           ::const_iterator::operator*(&local_c);
  return &ppVar3->second;
}
