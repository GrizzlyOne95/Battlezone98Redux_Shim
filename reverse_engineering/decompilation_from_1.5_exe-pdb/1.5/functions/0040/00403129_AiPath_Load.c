/*
 * Entry: 00403129
 * Name: AiPath::Load
 * Namespace: AiPath
 * Signature: bool Load(AiPath * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiPath::Load(AiPath *this,_iobuf *param_1)

{
  int *piVar1;
  _iobuf *p_Var2;
  bool bVar3;
  bool bVar4;
  OldNew *this_00;
  char *pcVar5;
  VECTOR_2D *pVVar6;
  AiPath *local_8;
  
  p_Var2 = param_1;
  local_8 = this;
  bVar3 = ::in(param_1,"[AiPath]");
  if ((bVar3) && (bVar3 = ::in(p_Var2,&local_8,4), bVar3)) {
    this_00 = operator_new(8);
    if (this_00 != (OldNew *)0x0) {
      OldNew::OldNew(this_00,local_8,this);
    }
    bVar4 = ::in(p_Var2,(int *)&param_1,4);
    bVar3 = false;
    if (bVar4) {
      this->label = (char *)0x0;
      bVar4 = true;
      if (0 < (int)param_1) {
        pcVar5 = operator_new__((uint)((int)&param_1->_ptr + 1));
        this->label = pcVar5;
        bVar4 = ::in(p_Var2,pcVar5,(uint)param_1);
        *(char *)((int)&param_1->_ptr + (int)this->label) = '\0';
      }
      bVar3 = false;
      if (bVar4 != false) {
        piVar1 = &this->pointCount;
        bVar4 = ::in(p_Var2,piVar1,4);
        bVar3 = false;
        if (bVar4) {
          pVVar6 = operator_new__(-(uint)((int)((ulonglong)(uint)*piVar1 * 8 >> 0x20) != 0) |
                                  (uint)((ulonglong)(uint)*piVar1 * 8));
          this->points = pVVar6;
          bVar3 = ::in(p_Var2,pVVar6,*piVar1 << 3);
          if (version < 0x3f6) {
            this->pathType = ONE_WAY_PATH;
          }
          else if (bVar3) {
            bVar3 = ::in(p_Var2,&this->pathType,4);
          }
        }
      }
    }
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}
