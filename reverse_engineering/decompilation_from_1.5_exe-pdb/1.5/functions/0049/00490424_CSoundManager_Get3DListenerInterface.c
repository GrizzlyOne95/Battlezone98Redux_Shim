/*
 * Entry: 00490424
 * Name: CSoundManager::Get3DListenerInterface
 * Namespace: CSoundManager
 * Signature: T_HRESULT Get3DListenerInterface(CSoundManager * this, IDirectSound3DListener * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall
CSoundManager::Get3DListenerInterface(CSoundManager *this,IDirectSound3DListener **param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int *local_30;
  undefined4 local_2c [9];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_30 = (int *)0x0;
  if (param_1 == (IDirectSound3DListener **)0x0) {
    uVar1 = 0x80070057;
  }
  else if (this->m_pDS == (IDirectSound8 *)0x0) {
    uVar1 = 0x800401f0;
  }
  else {
    *param_1 = (IDirectSound3DListener *)0x0;
    puVar3 = local_2c;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_2c[0] = 0x24;
    local_2c[1] = 0x11;
    iVar2 = (**(code **)((int)*this->m_pDS + 0xc))(this->m_pDS,local_2c,&local_30,0);
    if (-1 < iVar2) {
      iVar2 = (**(code **)*local_30)(local_30,&IID_IDirectSound3DListener,param_1);
      if (-1 < iVar2) {
        if (local_30 != (int *)0x0) {
          (**(code **)(*local_30 + 8))(local_30);
        }
        return 0;
      }
      if (local_30 != (int *)0x0) {
        (**(code **)(*local_30 + 8))(local_30);
      }
    }
    uVar1 = 0x80004005;
  }
  return uVar1;
}
