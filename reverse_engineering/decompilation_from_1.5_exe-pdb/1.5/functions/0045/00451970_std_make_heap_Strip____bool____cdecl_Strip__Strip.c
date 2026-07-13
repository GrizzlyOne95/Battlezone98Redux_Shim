/*
 * Entry: 00451970
 * Name: std::make_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void make_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::make_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3)

{
  if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
    _Make_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (param_1,param_2,param_3,(int *)0x0,(Strip **)0x0);
  }
  return;
}
