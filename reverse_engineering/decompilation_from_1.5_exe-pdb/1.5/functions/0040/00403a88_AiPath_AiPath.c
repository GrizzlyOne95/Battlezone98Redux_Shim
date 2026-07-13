/*
 * Entry: 00403a88
 * Name: AiPath::AiPath
 * Namespace: AiPath
 * Signature: AiPath * AiPath(AiPath * this, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __thiscall AiPath::AiPath(AiPath *this,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  _Const_iterator<1> _Var1;
  VECTOR_2D *pVVar2;
  _Iterator<1> _Var3;
  undefined1 local_14 [8];
  _Const_iterator<1> local_c;
  
  *(undefined4 *)&this->me = 0;
  *(undefined4 *)&(this->me).field_0x4 = 0;
  this->label = (char *)0x0;
  this->pointCount = 2;
  pVVar2 = operator_new__(0x10);
  this->points = pVVar2;
  pVVar2->x = param_1->x;
  this->points->z = param_1->z;
  this->points[1].x = param_2->x;
  this->points[1].z = param_2->z;
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,pathList._Myhead,&pathList);
  _Var1._Ptr = (_Node *)local_c._padding_;
  _Var1._padding_ = (int)local_14;
  _Var3 = std::list<AiPath_*,std::allocator<AiPath_*>_>::insert
                    (&pathList,_Var1,(AiPath **)local_c._Ptr);
  *(undefined4 *)&this->me = *_Var3._0_4_;
  *(undefined4 *)&(this->me).field_0x4 = _Var3._0_4_[1];
  this->bDontSave = false;
  this->pathType = ONE_WAY_PATH;
  return this;
}
