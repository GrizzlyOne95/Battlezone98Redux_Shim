/*
 * Entry: 0048b6ae
 * Name: std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>::construct
 * Namespace: std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>
 * Signature: void construct(allocator<std::pair<unsigned_long_const_,unsigned_long>_> * this, pair<unsigned_long_const_,unsigned_long> * param_1, pair<unsigned_long_const_,unsigned_long> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>::construct
          (allocator<std::pair<unsigned_long_const_,unsigned_long>_> *this,
          pair<unsigned_long_const_,unsigned_long> *param_1,
          pair<unsigned_long_const_,unsigned_long> *param_2)

{
  _Construct<std::pair<unsigned_long_const_,unsigned_long>,std::pair<unsigned_long_const_,unsigned_long>_>
            (param_1,param_2);
  return;
}
