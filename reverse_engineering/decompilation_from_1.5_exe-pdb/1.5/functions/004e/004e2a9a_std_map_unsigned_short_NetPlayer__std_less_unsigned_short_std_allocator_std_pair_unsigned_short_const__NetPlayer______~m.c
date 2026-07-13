/*
 * Entry: 004e2a9a
 * Name: std::map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>::~map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
 * Namespace: std::map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
 * Signature: void ~map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>(map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
::
~map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
          (map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
           *this)

{
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
           *)this);
  operator_delete(*(void **)this);
  return;
}
