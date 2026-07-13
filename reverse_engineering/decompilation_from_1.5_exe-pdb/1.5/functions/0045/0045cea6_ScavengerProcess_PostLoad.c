/*
 * Entry: 0045cea6
 * Name: ScavengerProcess::PostLoad
 * Namespace: ScavengerProcess
 * Signature: bool PostLoad(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavengerProcess::PostLoad(ScavengerProcess *this)

{
  bool bVar1;
  int iVar2;
  float fVar3;
  
  iVar2 = ConvertHandle(this->whoHandle);
  this->whoHandle = iVar2;
  bVar1 = SObject::PostLoad((SObject *)this);
  Init_Escorts(this);
  if (this->curState == RECYCLE) {
    fVar3 = Get_Time();
    this->wait_time = fVar3 + 10.0;
  }
  return bVar1;
}
