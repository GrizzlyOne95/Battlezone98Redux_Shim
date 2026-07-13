/*
 * Entry: 0049a91b
 * Name: stdext::unchecked_fill_n<Geizer_*_*,unsigned_int,Geizer_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<Geizer_*_*,unsigned_int,Geizer_*>(Geizer * * param_1, uint param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<Geizer_*_*,unsigned_int,Geizer_*>
          (Geizer **param_1,uint param_2,Geizer **param_3)

{
  std::_Fill_n<Geizer_*_*,unsigned_int,Geizer_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
