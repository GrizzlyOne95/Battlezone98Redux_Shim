/*
 * Entry: 004e12df
 * Name: std::_Distance2<std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator,unsigned_int>
 * Namespace: std
 * Signature: void _Distance2<std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator,unsigned_int>(iterator param_1, iterator param_2, uint * param_3, bidirectional_iterator_tag param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Distance2<std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::iterator,unsigned_int>
          (iterator param_1,iterator param_2,uint *param_3,bidirectional_iterator_tag param_4)

{
  bool bVar1;
  
  bVar1 = _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          ::const_iterator::operator==((const_iterator *)&param_1,(const_iterator *)&param_2);
  while (!bVar1) {
    *param_3 = *param_3 + 1;
    _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
    ::const_iterator::_Inc((const_iterator *)&param_1);
    bVar1 = _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
            ::const_iterator::operator==((const_iterator *)&param_1,(const_iterator *)&param_2);
  }
  return;
}
