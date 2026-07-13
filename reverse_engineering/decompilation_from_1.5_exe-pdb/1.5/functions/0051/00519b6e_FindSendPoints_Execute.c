/*
 * Entry: 00519b6e
 * Name: FindSendPoints::Execute
 * Namespace: FindSendPoints
 * Signature: void Execute(FindSendPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FindSendPoints::Execute(FindSendPoints *this)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  GridPoint *pGVar4;
  uint uVar5;
  VECTOR_3D local_28;
  float local_1c;
  undefined4 local_18;
  float local_14;
  uint *local_10;
  float local_c;
  float local_8;
  
  if (this->row == -1) {
    while (((int)gridPoints._Mylast - (int)gridPoints._Myfirst & 0xfffffff8U) != 0) {
      pGVar4 = std::vector<GridPoint,std::allocator<GridPoint>_>::back(&gridPoints);
      iVar1 = pGVar4->x;
      iVar2 = pGVar4->y;
      if (iVar1 != -1) {
        this->i = 0;
        this->row = iVar2;
        this->col = iVar1;
        goto LAB_00519bbe;
      }
      std::vector<GridPoint,std::allocator<GridPoint>_>::pop_back(&gridPoints);
    }
  }
  else {
LAB_00519bbe:
    iVar1 = this->i;
    local_c = (float)(aiGridX0 + this->col * 8) * 10.0 + layout[iVar1].rx * 80.0;
    local_10 = (uint *)(sendPoints + this->row * grid_columns + this->col);
    local_8 = (float)(aiGridZ0 + this->row * 8) * 10.0 + layout[iVar1].rz * 80.0;
    if (iVar1 == 0) {
      *local_10 = *local_10 & 0x1f;
    }
    bVar3 = OnBlocked(&pathStart);
    if (bVar3) {
      FindPathStart();
    }
    local_1c = local_c;
    local_18 = 0;
    local_14 = local_8;
    local_28.x = local_c;
    local_28.y = 0.0;
    local_28.z = local_8;
    bVar3 = OnBlocked(&local_28);
    if ((bVar3) || (bVar3 = PlanExists(pathStart.x,pathStart.z,local_c,local_8), !bVar3)) {
      *local_10 = *local_10 & ~(this->i << ((byte)this->i & 0x1f));
    }
    else {
      *local_10 = *local_10 | 1 << ((byte)this->i & 0x1f);
    }
    this->i = this->i + 1;
    if (this->i == 5) {
      uVar5 = (int)gridPoints._Mylast - (int)gridPoints._Myfirst >> 3;
      do {
        if ((int)uVar5 < 1) goto LAB_00519cfb;
        uVar5 = uVar5 - 1;
        pGVar4 = std::vector<GridPoint,std::allocator<GridPoint>_>::operator[](&gridPoints,uVar5);
      } while ((pGVar4->x != this->col) || (pGVar4->y != this->row));
      pGVar4->x = -1;
      pGVar4->y = -1;
LAB_00519cfb:
      this->row = -1;
      this->col = -1;
      this->i = 0;
    }
  }
  return;
}
