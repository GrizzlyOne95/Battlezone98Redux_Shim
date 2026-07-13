/*
 * Entry: 00452f00
 * Name: std::sort<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void sort<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::sort<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3)

{
  _Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>
            (param_1,param_2,(int)param_2 - (int)param_1 >> 2,param_3);
  return;
}
