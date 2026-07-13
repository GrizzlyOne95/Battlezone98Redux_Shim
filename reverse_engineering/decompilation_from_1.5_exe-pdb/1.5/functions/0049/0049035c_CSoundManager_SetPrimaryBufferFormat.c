/*
 * Entry: 0049035c
 * Name: CSoundManager::SetPrimaryBufferFormat
 * Namespace: CSoundManager
 * Signature: T_HRESULT SetPrimaryBufferFormat(CSoundManager * this, ulong param_1, ulong param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall
CSoundManager::SetPrimaryBufferFormat(CSoundManager *this,ulong param_1,ulong param_2,ulong param_3)

{
  IDirectSound8 *pIVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined2 local_44;
  short local_42;
  ulong local_40;
  int local_3c;
  undefined4 local_38;
  undefined2 uStack_34;
  int *local_30;
  undefined4 local_2c [4];
  undefined4 local_1c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_30 = (int *)0x0;
  pIVar1 = this->m_pDS;
  if (pIVar1 == (IDirectSound8 *)0x0) {
    uVar3 = 0x800401f0;
  }
  else {
    puVar5 = local_2c;
    for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    local_2c[2] = 0;
    local_1c = 0;
    local_2c[0] = 0x24;
    local_2c[1] = 1;
    iVar4 = (**(code **)((int)*pIVar1 + 0xc))(pIVar1,local_2c,&local_30,0);
    if (-1 < iVar4) {
      uStack_34 = 0;
      uVar2 = ((ushort)param_3 >> 3) * (short)param_1;
      local_38 = CONCAT22((ushort)param_3,uVar2);
      local_3c = uVar2 * param_2;
      local_40 = param_2;
      _local_44 = CONCAT22((short)param_1,1);
      iVar4 = (**(code **)(*local_30 + 0x38))(local_30,&local_44);
      if (-1 < iVar4) {
        if (local_30 != (int *)0x0) {
          (**(code **)(*local_30 + 8))(local_30);
        }
        return 0;
      }
    }
    uVar3 = 0x80004005;
  }
  return uVar3;
}
