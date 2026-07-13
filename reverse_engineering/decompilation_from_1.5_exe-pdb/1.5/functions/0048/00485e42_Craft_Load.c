/*
 * Entry: 00485e42
 * Name: Craft::Load
 * Namespace: Craft
 * Signature: bool Load(Craft * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::Load(Craft *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  VECTOR_3D local_54 [6];
  float local_c;
  float local_8;
  
  p_Var1 = param_1;
  if ((0x3fa < version) ||
     ((((bVar2 = ::in(param_1,(int *)&param_1,4), bVar2 &&
        (bVar2 = ::in(p_Var1,(int *)&param_1,4), bVar2)) &&
       (bVar2 = ::in(p_Var1,(int *)&param_1,4), bVar2)) &&
      (((bVar2 = ::in(p_Var1,(int *)&param_1,4), bVar2 &&
        (bVar2 = ::in(p_Var1,(int *)&param_1,4), bVar2)) &&
       ((bVar2 = ::in(p_Var1,(int *)&param_1,4), bVar2 &&
        (bVar2 = ::in(p_Var1,local_54,0x48), bVar2)))))))) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (version < 0x404) {
    this->abandoned = 0;
  }
  else if ((bVar2) && (bVar2 = ::in(p_Var1,&this->abandoned,4), bVar2)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (version < 2000) {
LAB_00485f68:
    bVar3 = false;
    if (!bVar2) goto LAB_00485f76;
  }
  else if ((((!bVar2) || (bVar2 = ::in(p_Var1,&param_1,4), !bVar2)) ||
           (bVar2 = ::in(p_Var1,&local_8,4), !bVar2)) || (bVar2 = ::in(p_Var1,&local_c,4), !bVar2))
  {
    bVar2 = false;
    goto LAB_00485f68;
  }
  bVar3 = GameObject::Load((GameObject *)this,p_Var1);
LAB_00485f76:
  if (this->_padding_ == 0) {
    if (this->_padding_ == 0) {
      iVar4 = (**(code **)(this->_padding_ + 0x30))();
      this->_padding_ = iVar4;
    }
  }
  else if ((this->_padding_ != 0) && (*(int *)(this->_padding_ + 0x20) != 0x54554700)) {
    this->_padding_ = 0;
  }
  return bVar3;
}
