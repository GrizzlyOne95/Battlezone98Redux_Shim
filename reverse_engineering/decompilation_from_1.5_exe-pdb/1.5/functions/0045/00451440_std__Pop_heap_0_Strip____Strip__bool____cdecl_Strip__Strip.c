/*
 * Entry: 00451440
 * Name: std::_Pop_heap_0<Strip_*_*,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Pop_heap_0<Strip_*_*,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3, Strip * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Pop_heap_0<Strip_*_*,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3,
          Strip **param_4)

{
  Strip *pSVar1;
  
  pSVar1 = param_2[-1];
  param_2[-1] = *param_1;
  _Adjust_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
            (param_1,0,(int)param_2 + (-4 - (int)param_1) >> 2,pSVar1,param_3);
  return;
}
