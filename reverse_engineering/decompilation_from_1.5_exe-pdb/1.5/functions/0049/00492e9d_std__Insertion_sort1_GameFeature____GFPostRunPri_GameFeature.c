/*
 * Entry: 00492e9d
 * Name: std::_Insertion_sort1<GameFeature_*_*,GFPostRunPri,GameFeature_*>
 * Namespace: std
 * Signature: void _Insertion_sort1<GameFeature_*_*,GFPostRunPri,GameFeature_*>(GameFeature * * param_1, GameFeature * * param_2, GFPostRunPri param_3, GameFeature * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Insertion_sort1<GameFeature_*_*,GFPostRunPri,GameFeature_*>
          (GameFeature **param_1,GameFeature **param_2,GFPostRunPri param_3,GameFeature **param_4)

{
  GameFeature *pGVar1;
  GameFeature *pGVar2;
  GameFeature **ppGVar3;
  int iVar4;
  GameFeature **ppGVar5;
  
  ppGVar3 = param_1;
  if (param_1 != param_2) {
    while (ppGVar3 = ppGVar3 + 1, ppGVar3 != param_2) {
      pGVar1 = *ppGVar3;
      iVar4 = pGVar1->postRunPriority;
      ppGVar5 = ppGVar3;
      if ((*param_1)->postRunPriority < iVar4) {
        stdext::unchecked_copy_backward<GameFeature_*_*,GameFeature_*_*>
                  (param_1,ppGVar3,ppGVar3 + 1);
        *param_1 = pGVar1;
      }
      else {
        while( true ) {
          pGVar2 = ppGVar5[-1];
          if (iVar4 <= pGVar2->postRunPriority) break;
          *ppGVar5 = pGVar2;
          iVar4 = pGVar1->postRunPriority;
          ppGVar5 = ppGVar5 + -1;
        }
        *ppGVar5 = pGVar1;
      }
    }
  }
  return;
}
