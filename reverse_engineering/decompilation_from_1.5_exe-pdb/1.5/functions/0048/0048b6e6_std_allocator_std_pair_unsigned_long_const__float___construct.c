/*
 * Entry: 0048b6e6
 * Name: std::allocator<std::pair<unsigned_long_const_,float>_>::construct
 * Namespace: std::allocator<std::pair<unsigned_long_const_,float>_>
 * Signature: void construct(allocator<std::pair<unsigned_long_const_,float>_> * this, pair<unsigned_long_const_,float> * param_1, pair<unsigned_long_const_,float> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::pair<unsigned_long_const_,float>_>::construct
          (allocator<std::pair<unsigned_long_const_,float>_> *this,
          pair<unsigned_long_const_,float> *param_1,pair<unsigned_long_const_,float> *param_2)

{
  _Construct<std::pair<unsigned_long_const_,float>,std::pair<unsigned_long_const_,float>_>
            (param_1,param_2);
  return;
}
