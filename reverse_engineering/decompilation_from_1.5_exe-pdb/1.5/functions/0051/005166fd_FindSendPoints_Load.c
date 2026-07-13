/*
 * Entry: 005166fd
 * Name: FindSendPoints::Load
 * Namespace: FindSendPoints
 * Signature: bool Load(FindSendPoints * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall FindSendPoints::Load(FindSendPoints *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  FindSendPoints *local_8;
  
  local_8 = this;
  bVar1 = ::in(param_1,&this->row,4);
  if (((bVar1) && (bVar1 = ::in(param_1,&this->col,4), bVar1)) &&
     (bVar1 = ::in(param_1,&this->i,4), bVar1)) {
    bVar2 = ::in(param_1,(int *)&local_8,4);
    bVar1 = true;
    if (bVar2) goto LAB_0051675c;
  }
  bVar1 = false;
LAB_0051675c:
  if (sendPoints != (long *)0x0) {
    operator_delete(sendPoints);
  }
  sendPoints = operator_new__(-(uint)((int)(ZEXT48(local_8) * 4 >> 0x20) != 0) |
                              (uint)(ZEXT48(local_8) * 4));
  if (((bVar1) && (bVar1 = ::in(param_1,sendPoints,(int)local_8 << 2), bVar1)) &&
     (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
