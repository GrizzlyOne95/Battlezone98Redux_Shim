/*
 * Entry: 0046fe51
 * Name: UserProcess::Init
 * Namespace: UserProcess
 * Signature: void Init(UserProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall UserProcess::Init(UserProcess *this)

{
  int (*paiVar1) [5];
  Weapon *pWVar2;
  Weapon *pWVar3;
  ulong (*pauVar4) [5];
  GameObjectClass *pGVar5;
  int iVar6;
  ulong (*pauVar7) [5];
  ulong *puVar8;
  uint uVar9;
  undefined4 local_34;
  UserProcess *local_30;
  uint local_2c;
  uint local_28;
  Carrier *local_24;
  int local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (this->_padding_ == 0) {
    local_24 = (Carrier *)0x0;
  }
  else {
    local_24 = *(Carrier **)(this->_padding_ + 0x198);
  }
  paiVar1 = this->selectNext;
  iVar6 = 5;
  do {
    (*(ulong (*) [5])(paiVar1 + -2))[0] = 0;
    (*paiVar1)[0] = 0;
    (*(ulong (*) [5])(paiVar1 + -1))[0] = 0;
    paiVar1[1][0] = 0;
    paiVar1 = (int (*) [5])(*paiVar1 + 1);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  local_30 = this;
  if (local_24 != (Carrier *)0x0) {
    local_2c = local_24->existant;
    local_20 = 0;
    pauVar4 = this->selectList;
    do {
      uVar9 = 1 << ((byte)local_20 & 0x1f);
      if ((local_2c & uVar9) != 0) {
        pWVar2 = Carrier::GetWeapon(local_24,local_20);
        (*pauVar4)[0] = (*pauVar4)[0] | uVar9;
        pauVar4[1][0] = pauVar4[1][0] | uVar9;
        local_1c = local_20 + 1;
        if (local_1c < 5) {
          puVar8 = pauVar4[1];
          do {
            puVar8 = puVar8 + 1;
            local_28 = 1 << ((byte)local_1c & 0x1f);
            if ((local_28 & local_2c) != 0) {
              pWVar3 = Carrier::GetWeapon(local_24,local_1c);
              if (pWVar2->weaponClass == pWVar3->weaponClass) {
                (*pauVar4)[0] = (*pauVar4)[0] | local_28;
                puVar8[-5] = puVar8[-5] | uVar9;
              }
              if (pWVar2->hard->class_id == pWVar3->hard->class_id) {
                pauVar4[1][0] = pauVar4[1][0] | local_28;
                *puVar8 = *puVar8 | uVar9;
              }
            }
            local_1c = local_1c + 1;
            this = local_30;
          } while (local_1c < 5);
        }
      }
      local_20 = local_20 + 1;
      pauVar4 = (ulong (*) [5])(*pauVar4 + 1);
    } while (local_20 < 5);
  }
  pauVar4 = this->selectList;
  iVar6 = 0;
  do {
    local_2c = iVar6 + 1;
    local_20 = iVar6;
    if ((int)local_2c < 5) {
      pauVar7 = pauVar4;
      local_1c = local_2c;
      do {
        pauVar7 = (ulong (*) [5])(*pauVar7 + 1);
        if (((*pauVar7)[0] != (*pauVar4)[0]) && ((*pauVar7)[0] != 0)) {
          local_20 = local_1c;
          if (local_1c != iVar6) goto LAB_0046ffb0;
          break;
        }
        local_1c = local_1c + 1;
      } while (local_1c < 5);
    }
    local_1c = 0;
    if (0 < iVar6) {
      pauVar7 = this->selectList;
      do {
        if (((*pauVar7)[0] != (*pauVar4)[0]) && ((*pauVar7)[0] != 0)) {
          local_20 = local_1c;
          break;
        }
        local_1c = local_1c + 1;
        pauVar7 = (ulong (*) [5])(*pauVar7 + 1);
      } while (local_1c < iVar6);
    }
LAB_0046ffb0:
    (*(int (*) [5])(pauVar4 + 2))[0] = local_20;
    local_20 = iVar6;
    if ((int)local_2c < 5) {
      puVar8 = pauVar4[1];
      local_1c = local_2c;
      do {
        puVar8 = puVar8 + 1;
        if ((*puVar8 != pauVar4[1][0]) && (*puVar8 != 0)) {
          local_20 = local_1c;
          if (local_1c != iVar6) goto LAB_00470017;
          break;
        }
        local_1c = local_1c + 1;
      } while (local_1c < 5);
    }
    local_1c = 0;
    if (0 < iVar6) {
      pauVar7 = this->selectList + 1;
      do {
        if (((*pauVar7)[0] != pauVar4[1][0]) && ((*pauVar7)[0] != 0)) {
          local_20 = local_1c;
          break;
        }
        local_1c = local_1c + 1;
        pauVar7 = (ulong (*) [5])(*pauVar7 + 1);
      } while (local_1c < iVar6);
    }
LAB_00470017:
    (*(int (*) [5])(pauVar4 + 3))[0] = local_20;
    pauVar4 = (ulong (*) [5])(*pauVar4 + 1);
    iVar6 = local_2c;
    if (4 < (int)local_2c) {
      if (local_24 != (Carrier *)0x0) {
        if (this->selectList[this->linked][this->cycle] == 0) {
          this->cycle = this->selectNext[this->linked][this->cycle];
        }
        Carrier::SetSelected(local_24,0);
        Carrier::SetSelected(local_24,this->selectList[this->linked][this->cycle]);
      }
      local_34 = 0x6163702a;
      local_30 = (UserProcess *)0x726d;
      iVar6 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))();
      local_34 = CONCAT31(local_34._1_3_,*(undefined1 *)(iVar6 + 0xd4));
      sprintf(local_18,"%.8s.odf",&local_34);
      iVar6 = ItemExists(local_18);
      if (iVar6 == 0) {
        iVar6 = (*(code *)**(undefined4 **)(this->_padding_ + 0x20))();
        local_34 = CONCAT31(local_34._1_3_,((*(char *)(iVar6 + 0xd4) != 'c') - 1U & 0x12) + 0x61);
      }
      pGVar5 = GameObjectClass::Find(CONCAT44(local_30,local_34));
      this->nav = pGVar5;
      return;
    }
  } while( true );
}
