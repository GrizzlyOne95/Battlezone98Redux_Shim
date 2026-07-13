/*
 * Entry: 004039c4
 * Name: AiPath::AiPath
 * Namespace: AiPath
 * Signature: AiPath * AiPath(AiPath * this, char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __thiscall AiPath::AiPath(AiPath *this,char *param_1,int param_2)

{
  char cVar1;
  _Const_iterator<1> _Var2;
  char *pcVar3;
  VECTOR_2D *pVVar4;
  int iVar5;
  _Iterator<1> _Var6;
  undefined1 local_14 [8];
  _Const_iterator<1> local_c;
  
  *(undefined4 *)&this->me = 0;
  *(undefined4 *)&(this->me).field_0x4 = 0;
  if (param_1 == (char *)0x0) {
    this->label = (char *)0x0;
  }
  else {
    pcVar3 = param_1;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pcVar3 = operator_new__((uint)(pcVar3 + (1 - (int)(param_1 + 1))));
    this->label = pcVar3;
    do {
      cVar1 = *param_1;
      param_1 = param_1 + 1;
      *pcVar3 = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
  }
  this->pointCount = param_2;
  pVVar4 = operator_new__(-(uint)((int)((ulonglong)(uint)param_2 * 8 >> 0x20) != 0) |
                          (uint)((ulonglong)(uint)param_2 * 8));
  this->points = pVVar4;
  iVar5 = 0;
  if (0 < this->pointCount) {
    do {
      this->points[iVar5].x = 0.0;
      this->points[iVar5].z = 0.0;
      iVar5 = iVar5 + 1;
    } while (iVar5 < this->pointCount);
  }
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_c,pathList._Myhead,&pathList);
  _Var2._Ptr = (_Node *)local_c._padding_;
  _Var2._padding_ = (int)local_14;
  _Var6 = std::list<AiPath_*,std::allocator<AiPath_*>_>::insert
                    (&pathList,_Var2,(AiPath **)local_c._Ptr);
  *(undefined4 *)&this->me = *_Var6._0_4_;
  *(undefined4 *)&(this->me).field_0x4 = _Var6._0_4_[1];
  this->bDontSave = false;
  this->pathType = ONE_WAY_PATH;
  return this;
}
