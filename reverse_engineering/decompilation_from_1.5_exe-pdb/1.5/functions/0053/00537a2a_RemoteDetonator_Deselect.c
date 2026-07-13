/*
 * Entry: 00537a2a
 * Name: RemoteDetonator::Deselect
 * Namespace: RemoteDetonator
 * Signature: void Deselect(RemoteDetonator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall RemoteDetonator::Deselect(RemoteDetonator *this)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  Ordnance **ppOVar6;
  ushort uVar7;
  undefined2 *puVar8;
  int iStack_10c;
  undefined2 uStack_108;
  ushort auStack_106 [61];
  undefined1 auStack_8c [132];
  uint uStack_8;
  
  uStack_8 = __security_cookie ^ (uint)auStack_8c;
  uStack_108 = 0x7878;
  puVar4 = auStack_106;
  ppOVar6 = this->ordnance;
  iStack_10c = 4;
  do {
    if (*ppOVar6 != (Ordnance *)0x0) {
      (*ppOVar6)->lifeTimer = 0.0;
      iVar3 = Net_IsNetGame();
      if ((iVar3 != 0) && (this->_padding_ != 0)) {
        bVar1 = DistributedObject::IsLocal((DistributedObject *)(this->_padding_ + 0x20));
        if (bVar1) {
          *puVar4 = (*ppOVar6)->ordid;
          puVar4 = puVar4 + 1;
        }
      }
    }
    *ppOVar6 = (Ordnance *)0x0;
    ppOVar6 = ppOVar6 + 1;
    iStack_10c = iStack_10c + -1;
  } while (iStack_10c != 0);
  iVar3 = Net_IsNetGame();
  if ((iVar3 != 0) && (this->_padding_ != 0)) {
    bVar1 = DistributedObject::IsLocal((DistributedObject *)(this->_padding_ + 0x20));
    if ((bVar1) && (auStack_106 < puVar4)) {
      puVar8 = &uStack_108;
      uVar5 = (int)puVar4 - (int)puVar8;
      iVar3 = 1;
      uVar7 = 0;
      uVar2 = Net_GetMyPlayerID();
      Net::Send(Net::dp,uVar2,uVar7,iVar3,puVar8,uVar5);
    }
  }
  return;
}
