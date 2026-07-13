/*
 * Entry: 0041d624
 * Name: LayMinesTask::PlanOk
 * Namespace: LayMinesTask
 * Signature: bool PlanOk(LayMinesTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LayMinesTask::PlanOk(LayMinesTask *this)

{
  AiPath *this_00;
  VECTOR_2D *pVVar1;
  VECTOR_2D VVar2;
  float fVar3;
  float fVar4;
  
  this_00 = (AiPath *)this->_padding_;
  if (this_00->pathType != BAD_PATH) {
    pVVar1 = this_00->points;
    VVar2.z = pVVar1[this_00->pointCount + -1].z;
    VVar2.x = pVVar1[this_00->pointCount + -1].x;
    fVar3 = Dist(*pVVar1,VVar2);
    fVar4 = AiPath::GetLength(this_00);
    if (fVar4 <= fVar3 + fVar3) {
      return true;
    }
  }
  return false;
}
