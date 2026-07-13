/*
 * Entry: 0048554c
 * Name: ConstructionRig::Load
 * Namespace: ConstructionRig
 * Signature: bool Load(ConstructionRig * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ConstructionRig::Load(ConstructionRig *this,_iobuf *param_1)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  int iVar3;
  float *pfVar4;
  MAT_3D *pMVar5;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  this->dropClass = (GameObjectClass *)0x0;
  local_5 = '\x01';
  if (version < 0x407) {
    pfVar4 = (float *)(this->_padding_ + 0x20);
    pMVar5 = &this->dropMat;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar5->right_x = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
  }
  else {
    local_14 = 0;
    local_10 = 0;
    bVar1 = ::in(param_1,&this->dropMat,0x40);
    if (bVar1) {
      bVar1 = ::in(param_1,(long64 *)&local_14,8);
      local_5 = '\x01';
      if (!bVar1) goto LAB_004855a8;
    }
    else {
LAB_004855a8:
      local_5 = '\0';
    }
    if (local_14 != 0 || local_10 != 0) {
      pGVar2 = GameObjectClass::Find(CONCAT44(local_10,local_14));
      this->dropClass = pGVar2;
    }
    if (1999 < version) {
      if ((local_5 != '\0') && (bVar1 = ::in(param_1,&local_c,4), bVar1)) goto LAB_00485612;
      local_5 = '\0';
    }
  }
  if (local_5 == '\0') {
    return false;
  }
LAB_00485612:
  bVar1 = Producer::Load((Producer *)this,param_1);
  if (!bVar1) {
    return false;
  }
  return true;
}
