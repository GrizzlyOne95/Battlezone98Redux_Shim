/*
 * Entry: 00413ffb
 * Name: GotoTask::InitState
 * Namespace: GotoTask
 * Signature: void InitState(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GotoTask::InitState(GotoTask *this)

{
  int iVar1;
  VECTOR_2D *pVVar2;
  float fVar3;
  
  iVar1 = this->_padding_;
  if (iVar1 == 1) {
    this->_padding_ = 2;
    UnitTask::CleanStuck((UnitTask *)this);
    ChoosePathPoint(this);
    pVVar2 = this->path->points;
    fVar3 = pVVar2[this->pathPoint].z;
    this->_padding_ = (int)pVVar2[this->pathPoint].x;
    this->_padding_ = 0;
    this->_padding_ = (int)fVar3;
  }
  else if (iVar1 == 2) {
    UnitTask::InitGoto((UnitTask *)this);
  }
  else if (iVar1 == 3) {
    UnitTask::InitStuck((UnitTask *)this);
  }
  return;
}
