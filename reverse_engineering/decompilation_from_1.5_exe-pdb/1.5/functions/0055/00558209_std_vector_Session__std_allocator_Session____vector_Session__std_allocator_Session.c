/*
 * Entry: 00558209
 * Name: std::vector<Session_*,std::allocator<Session_*>_>::vector<Session_*,std::allocator<Session_*>_>
 * Namespace: std::vector<Session_*,std::allocator<Session_*>_>
 * Signature: vector<Session_*,std::allocator<Session_*>_> * vector<Session_*,std::allocator<Session_*>_>(vector<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<Session_*,std::allocator<Session_*>_> * __thiscall
std::vector<Session_*,std::allocator<Session_*>_>::vector<Session_*,std::allocator<Session_*>_>
          (vector<Session_*,std::allocator<Session_*>_> *this)

{
  _Vector_val<Session_*,std::allocator<Session_*>_>::
  _Vector_val<Session_*,std::allocator<Session_*>_>
            ((_Vector_val<Session_*,std::allocator<Session_*>_> *)this,SUB41(this,0));
  _Buy(this,0);
  return this;
}
