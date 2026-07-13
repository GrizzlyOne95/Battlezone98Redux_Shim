/*
 * Entry: 0040ad83
 * Name: std::map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>::~map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
 * Namespace: std::map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
 * Signature: void ~map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>(map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
::
~map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
          (map<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>_>
           *this)

{
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::_Tidy((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *)this);
  operator_delete(*(void **)this);
  return;
}
