/*
 * Entry: 0045cc64
 * Name: ScavengerProcess::GetScrapPosition
 * Namespace: ScavengerProcess
 * Signature: VECTOR_3D * GetScrapPosition(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall ScavengerProcess::GetScrapPosition(ScavengerProcess *this)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D local_c;
  
  if ((this->curState == RECYCLE) && (this->task != (AiTask *)0x0)) {
    pVVar1 = RecycleTask_GetScrapPos(&local_c,this->task);
    (this->lastScrap).x = pVVar1->x;
    (this->lastScrap).y = pVVar1->y;
    (this->lastScrap).z = pVVar1->z;
  }
  else {
    (this->lastScrap).y = -1.0;
  }
  return &this->lastScrap;
}
