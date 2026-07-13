/*
 * Entry: 00460d0c
 * Name: stdext::unchecked_fill_n<Scrap_*_*,unsigned_int,Scrap_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<Scrap_*_*,unsigned_int,Scrap_*>(Scrap * * param_1, uint param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<Scrap_*_*,unsigned_int,Scrap_*>
          (Scrap **param_1,uint param_2,Scrap **param_3)

{
  std::_Fill_n<Scrap_*_*,unsigned_int,Scrap_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
