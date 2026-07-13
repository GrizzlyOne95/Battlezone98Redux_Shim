/*
 * Entry: 00451350
 * Name: std::_Insertion_sort1<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*),Strip_*>
 * Namespace: std
 * Signature: void _Insertion_sort1<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*),Strip_*>(Strip * * param_1, Strip * * param_2, _func___cdecl_bool_Strip_ptr_Strip_ptr * param_3, Strip * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Insertion_sort1<Strip_*_*,bool_(__cdecl*)(Strip_*,Strip_*),Strip_*>
          (Strip **param_1,Strip **param_2,_func___cdecl_bool_Strip_ptr_Strip_ptr *param_3,
          Strip **param_4)

{
  Strip *pSVar1;
  bool bVar2;
  int iVar3;
  Strip **ppSVar4;
  Strip **ppSVar5;
  Strip **ppSVar6;
  
  if ((param_1 != param_2) && (ppSVar4 = param_1 + 1, ppSVar4 != param_2)) {
    do {
      pSVar1 = *ppSVar4;
      bVar2 = (*param_3)(pSVar1,*param_1);
      if (bVar2) {
        iVar3 = (int)ppSVar4 - (int)param_1 >> 2;
        if (0 < iVar3) {
          memmove_s(ppSVar4 + (1 - iVar3),iVar3 * 4,param_1,iVar3 * 4);
        }
        *param_1 = pSVar1;
      }
      else {
        bVar2 = (*param_3)(pSVar1,ppSVar4[-1]);
        ppSVar5 = ppSVar4;
        ppSVar6 = ppSVar4;
        if (bVar2) {
          do {
            ppSVar6 = ppSVar5 + -1;
            *ppSVar5 = *ppSVar6;
            bVar2 = (*param_3)(pSVar1,ppSVar5[-2]);
            ppSVar5 = ppSVar6;
          } while (bVar2);
        }
        *ppSVar6 = pSVar1;
      }
      ppSVar4 = ppSVar4 + 1;
    } while (ppSVar4 != param_2);
  }
  return;
}
