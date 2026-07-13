/*
 * Entry: 0048a4c6
 * Name: stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>::operator()
 * Namespace: stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>
 * Signature: bool operator()(hash_compare<unsigned_long,std::less<unsigned_long>_> * this, ulong * param_1, ulong * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>::operator()
          (hash_compare<unsigned_long,std::less<unsigned_long>_> *this,ulong *param_1,ulong *param_2
          )

{
  return *param_1 < *param_2;
}
