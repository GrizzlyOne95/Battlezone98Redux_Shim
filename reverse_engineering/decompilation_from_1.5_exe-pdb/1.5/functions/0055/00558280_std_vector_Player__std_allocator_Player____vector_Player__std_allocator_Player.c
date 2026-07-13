/*
 * Entry: 00558280
 * Name: std::vector<Player_*,std::allocator<Player_*>_>::vector<Player_*,std::allocator<Player_*>_>
 * Namespace: std::vector<Player_*,std::allocator<Player_*>_>
 * Signature: vector<Player_*,std::allocator<Player_*>_> * vector<Player_*,std::allocator<Player_*>_>(vector<Player_*,std::allocator<Player_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<Player_*,std::allocator<Player_*>_> * __thiscall
std::vector<Player_*,std::allocator<Player_*>_>::vector<Player_*,std::allocator<Player_*>_>
          (vector<Player_*,std::allocator<Player_*>_> *this)

{
  _Vector_val<Player_*,std::allocator<Player_*>_>::_Vector_val<Player_*,std::allocator<Player_*>_>
            ((_Vector_val<Player_*,std::allocator<Player_*>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
