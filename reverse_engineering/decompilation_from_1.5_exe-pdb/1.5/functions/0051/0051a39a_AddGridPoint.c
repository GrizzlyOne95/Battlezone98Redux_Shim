/*
 * Entry: 0051a39a
 * Name: AddGridPoint
 * Namespace: Global
 * Signature: void AddGridPoint(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddGridPoint(int param_1,int param_2)

{
  int iVar1;
  GridPoint *pGVar2;
  int iVar3;
  GridPoint local_c;
  
  iVar1 = param_1;
  if (sendPoints[grid_columns * param_2 + param_1] < 0) {
    param_1 = 0;
    iVar3 = (int)gridPoints._Mylast - (int)gridPoints._Myfirst >> 3;
    if (0 < iVar3) {
      do {
        pGVar2 = std::vector<GridPoint,std::allocator<GridPoint>_>::operator[](&gridPoints,param_1);
        if ((iVar1 == pGVar2->x) && (pGVar2->y == param_2)) {
          return;
        }
        param_1 = param_1 + 1;
      } while (param_1 < iVar3);
    }
    local_c.y = param_2;
    local_c.x = iVar1;
    std::vector<GridPoint,std::allocator<GridPoint>_>::push_back(&gridPoints,&local_c);
  }
  return;
}
