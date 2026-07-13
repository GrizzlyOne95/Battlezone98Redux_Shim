/*
 * Entry: 004d3658
 * Name: OverView_SetObject
 * Namespace: Global
 * Signature: void OverView_SetObject(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OverView_SetObject(_OBJ76 *param_1)

{
  GameObject *pGVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pGVar1 = (GameObject *)0x0;
  }
  else {
    pGVar1 = param_1->gameObj;
  }
  OverView::SetObject((OverView *)&overView,pGVar1);
  return;
}
