/*
 * Entry: 00452b10
 * Name: std::_Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>
 * Namespace: std
 * Signature: void _Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>(Strip * * param_1, Strip * * param_2, int param_3, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>
          (Strip **param_1,Strip **param_2,int param_3,
          _func___cdecl_bool_Strip_ptr_Strip_ptr *param_4)

{
  int iVar1;
  Strip *local_8;
  Strip **local_4;
  
  iVar1 = (int)param_2 - (int)param_1;
  do {
    iVar1 = iVar1 >> 2;
    if (iVar1 < 0x21) {
LAB_00452b9c:
      if (1 < iVar1) {
        _Insertion_sort1<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*),Strip_*>
                  (param_1,param_2,param_4,(Strip **)0x0);
      }
      return;
    }
    if (param_3 < 1) {
      if (0x20 < iVar1) {
        if (4 < (int)((int)param_2 - (int)param_1 & 0xfffffffcU)) {
          _Make_heap<Strip_*_*,int,Strip_*,bool_(__cdecl*)(Strip_*,Strip_*)>
                    (param_1,param_2,param_4,(int *)0x0,(Strip **)0x0);
        }
        _Sort_heap<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>(param_1,param_2,param_4);
        return;
      }
      goto LAB_00452b9c;
    }
    _Unguarded_partition<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*)>
              (&local_8,param_1,(_func___cdecl_bool_Strip_ptr_Strip_ptr *)param_2);
    param_3 = param_3 / 2 + (param_3 / 2) / 2;
    if ((int)((int)local_8 - (int)param_1 & 0xfffffffcU) <
        (int)((int)param_2 - (int)local_4 & 0xfffffffcU)) {
      _Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>
                (param_1,(Strip **)local_8,param_3,param_4);
      param_1 = local_4;
    }
    else {
      _Sort<Strip_*_*,int,bool_(__cdecl*)(Strip_*,Strip_*)>(local_4,param_2,param_3,param_4);
      param_2 = (Strip **)local_8;
    }
    iVar1 = (int)param_2 - (int)param_1;
  } while( true );
}
