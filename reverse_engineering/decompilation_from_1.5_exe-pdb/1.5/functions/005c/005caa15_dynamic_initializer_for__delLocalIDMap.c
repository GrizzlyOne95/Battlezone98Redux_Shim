/*
 * Entry: 005caa15
 * Name: `dynamic_initializer_for_'delLocalIDMap''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'delLocalIDMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__delLocalIDMap__(void)

{
  stdext::
  hash_map<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
  ::
  hash_map<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
            (&delLocalIDMap);
  atexit(_dynamic_atexit_destructor_for__delLocalIDMap__);
  return;
}
