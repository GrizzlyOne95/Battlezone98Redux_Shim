/*
 * Entry: 00450cc0
 * Name: std::_Pop_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Pop_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, Strip * * param_3, Strip * param_4, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,Strip **param_3,Strip *param_4,
          _func___cdecl_bool_Strip_ptr_Strip_ptr *param_5,int *param_6)

{
  *param_3 = *param_1;
  _Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
            (param_1,0,(int)param_2 - (int)param_1 >> 2,param_4,param_5);
  return;
}
