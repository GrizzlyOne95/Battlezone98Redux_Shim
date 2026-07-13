/*
 * Entry: 005ca9ff
 * Name: `dynamic_initializer_for_'keyLocalIDMap''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'keyLocalIDMap''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__keyLocalIDMap__(void)

{
  stdext::
  hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
  ::
  hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
            (&keyLocalIDMap);
  atexit(_dynamic_atexit_destructor_for__keyLocalIDMap__);
  return;
}
