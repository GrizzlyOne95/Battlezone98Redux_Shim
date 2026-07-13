/*
 * Entry: 00537951
 * Name: RemoteDetonator::Detonate
 * Namespace: RemoteDetonator
 * Signature: void Detonate(RemoteDetonator * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall RemoteDetonator::Detonate(RemoteDetonator *this)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  Ordnance **ppOVar6;
  ushort uVar7;
  undefined2 *puVar8;
  int local_10c;
  undefined2 local_108;
  ushort local_106 [61];
  undefined1 local_8c [132];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_8c;
  local_108 = 0x7878;
  puVar4 = local_106;
  ppOVar6 = this->ordnance;
  local_10c = 4;
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
    local_10c = local_10c + -1;
  } while (local_10c != 0);
  iVar3 = Net_IsNetGame();
  if ((iVar3 != 0) && (this->_padding_ != 0)) {
    bVar1 = DistributedObject::IsLocal((DistributedObject *)(this->_padding_ + 0x20));
    if ((bVar1) && (local_106 < puVar4)) {
      puVar8 = &local_108;
      uVar5 = (int)puVar4 - (int)puVar8;
      iVar3 = 1;
      uVar7 = 0;
      uVar2 = Net_GetMyPlayerID();
      Net::Send(Net::dp,uVar2,uVar7,iVar3,puVar8,uVar5);
    }
  }
  return;
}
