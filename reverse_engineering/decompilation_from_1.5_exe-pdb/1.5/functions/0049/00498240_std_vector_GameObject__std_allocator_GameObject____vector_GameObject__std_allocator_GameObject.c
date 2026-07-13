/*
 * Entry: 00498240
 * Name: std::vector<GameObject_*,std::allocator<GameObject_*>_>::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Namespace: std::vector<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: vector<GameObject_*,std::allocator<GameObject_*>_> * vector<GameObject_*,std::allocator<GameObject_*>_>(vector<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<GameObject_*,std::allocator<GameObject_*>_> * __thiscall
std::vector<GameObject_*,std::allocator<GameObject_*>_>::
vector<GameObject_*,std::allocator<GameObject_*>_>
          (vector<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  _Vector_val<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_val<GameObject_*,std::allocator<GameObject_*>_>
            ((_Vector_val<GameObject_*,std::allocator<GameObject_*>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
