/*
 * Entry: 004a111e
 * Name: stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>::operator()
 * Namespace: stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>
 * Signature: bool operator()(hash_compare<unsigned_int,std::less<unsigned_int>_> * this, uint * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
stdext::hash_compare<unsigned_int,std::less<unsigned_int>_>::operator()
          (hash_compare<unsigned_int,std::less<unsigned_int>_> *this,uint *param_1,uint *param_2)

{
  return *param_1 < *param_2;
}
