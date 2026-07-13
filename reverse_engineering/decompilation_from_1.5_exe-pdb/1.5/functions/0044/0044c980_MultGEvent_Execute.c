/*
 * Entry: 0044c980
 * Name: MultGEvent::Execute
 * Namespace: MultGEvent
 * Signature: void Execute(MultGEvent * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MultGEvent::Execute(MultGEvent *this)

{
  float fVar1;
  bool bVar2;
  AiPath *pAVar3;
  GameObject *pGVar4;
  int iVar5;
  int iVar6;
  MAT_3D *pMVar7;
  MAT_3D *pMVar8;
  char *pcVar9;
  float fVar10;
  char *pcVar11;
  MAT_3D local_60;
  GameObject *local_20;
  char local_1c [8];
  char local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (this->reset != 0) {
    this->reset = 0;
    this->starttimer = 1;
    pGVar4 = GameObject::userObject;
    local_20 = GameObject::userObject;
    if (GameObject::userObject != (GameObject *)0x0) {
      sprintf(local_1c,"team%da");
      pAVar3 = AiPath::Find(local_1c);
      fVar10 = pAVar3->points->x;
      fVar1 = pAVar3->points->z;
      pMVar7 = &pGVar4->obj->transform;
      pMVar8 = &local_60;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        pMVar8->right_x = pMVar7->right_x;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
      }
      local_60.posit_x = (double)fVar10;
      local_60.posit_z = (double)fVar1;
      fVar10 = Terrain_FindFloor((double)fVar10,(double)fVar1);
      local_60.posit_y = (double)fVar10;
      GameObject::SetTransform(local_20,&local_60);
    }
  }
  if (this->starttimer != 0) {
    this->starttimer = 0;
    StartCockpitTimer(0x21c,0x16a,0xb4);
  }
  bVar2 = Net::GetHosting();
  if (bVar2) {
    if (this->state == 0) {
      this->goal1amessage = 1;
      this->goal1bmessage = 1;
      this->goal2amessage = 1;
      this->goal2bmessage = 1;
      this->state = 1;
      pcVar9 = this->pup[0].str;
      local_20 = (GameObject *)0x1e;
      do {
        if (*pcVar9 == 'a') {
          pcVar11 = "apammo";
        }
        else {
          pcVar11 = "aprepa";
        }
        iVar6 = BuildObject(pcVar11,0,pcVar9,0);
        ((prup *)(pcVar9 + -8))->powerup = iVar6;
        pcVar9[0x14] = false;
        pcVar9 = pcVar9 + 0x20;
        local_20 = (GameObject *)((int)local_20 + -1);
      } while (local_20 != (GameObject *)0x0);
      iVar6 = BuildObject("abstor",1,"goal1a",0);
      this->goal1a = iVar6;
      iVar6 = BuildObject("abstor",1,"goal1b",0);
      this->goal1b = iVar6;
      iVar6 = BuildObject("abstor",2,"goal2a",0);
      this->goal2a = iVar6;
      iVar6 = BuildObject("abstor",2,"goal2b",0);
      this->goal2b = iVar6;
    }
    else {
      if (this->goal1amessage != 0) {
        bVar2 = IsAlive(&this->goal1a);
        if (!bVar2) {
          Net_BroadCastMessage("Team 1 has lost flag 1");
          DisplayMessage("Team 1 has lost flag 1");
          this->goal1amessage = 0;
        }
      }
      if (this->goal1bmessage != 0) {
        bVar2 = IsAlive(&this->goal1b);
        if (!bVar2) {
          Net_BroadCastMessage("Team 1 has lost flag 2");
          DisplayMessage("Team 1 has lost flag 2");
          this->goal1bmessage = 0;
        }
      }
      if (this->goal2amessage != 0) {
        bVar2 = IsAlive(&this->goal2a);
        if (!bVar2) {
          Net_BroadCastMessage("Team 2 has lost flag 1");
          DisplayMessage("Team 2 has lost flag 1");
          this->goal2amessage = 0;
        }
      }
      if (this->goal2bmessage != 0) {
        bVar2 = IsAlive(&this->goal2b);
        if (!bVar2) {
          Net_BroadCastMessage("Team 2 has lost flag 2");
          DisplayMessage("Team 2 has lost flag 2");
          this->goal2bmessage = 0;
        }
      }
      if (cockpitTimer.timer < 1) {
        local_14[0] = '#';
        local_14[1] = 0x52;
        local_14[2] = 0;
        local_14[3] = '\0';
        local_14[4] = '\0';
        local_14[5] = '\0';
        local_14[6] = '\0';
        local_14[7] = '\0';
        local_14[8] = '\0';
        local_14[9] = 0;
        Net_BroadCast(local_14,3);
        this->reset = 1;
        Net_BroadCastMessage("Time Has Run Out");
        DisplayMessage("Time Has Run Out");
        refresh_flags(this);
      }
      bVar2 = IsAlive(&this->goal2a);
      if (!bVar2) {
        bVar2 = IsAlive(&this->goal2b);
        if (!bVar2) {
          builtin_strncpy(local_14,"#R\x01",4);
          local_14[4] = '\0';
          local_14[5] = '\0';
          local_14[6] = '\0';
          local_14[7] = '\0';
          local_14[8] = '\0';
          local_14[9] = 0;
          Net_BroadCast(local_14,3);
          this->reset = 1;
          Net_BroadCastMessage("Team 2 has lost its flags, Score 1 for team 1");
          DisplayMessage("Team 2 has lost its flags, Score 1 for team 1");
          refresh_flags(this);
        }
      }
      bVar2 = IsAlive(&this->goal1a);
      if (!bVar2) {
        bVar2 = IsAlive(&this->goal1b);
        if (!bVar2) {
          builtin_strncpy(local_14,"#R\x02",4);
          local_14[4] = '\0';
          local_14[5] = '\0';
          local_14[6] = '\0';
          local_14[7] = '\0';
          local_14[8] = '\0';
          local_14[9] = 0;
          Net_BroadCast(local_14,3);
          this->reset = 1;
          Net_BroadCastMessage("Team 1 has lost its flags, Score 1 for team 2");
          DisplayMessage("Team 1 has lost its flags, Score 1 for team 2");
          refresh_flags(this);
        }
      }
      pcVar9 = this->pup[0].str;
      iVar6 = 0x1e;
      do {
        pGVar4 = GameObjectHandle::GetObj(((prup *)(pcVar9 + -8))->powerup);
        if (pGVar4 == (GameObject *)0x0) {
          if ((bool)pcVar9[0x14] == false) {
            pcVar9[0x14] = true;
            fVar10 = Get_TimeLocal();
            *(float *)(pcVar9 + -4) = fVar10 + 10.0;
            goto LAB_0044cd15;
          }
LAB_0044cd1b:
          fVar10 = Get_TimeLocal();
          if (*(float *)(pcVar9 + -4) < fVar10) {
            if (*pcVar9 == 'a') {
              pcVar11 = "apammo";
            }
            else {
              pcVar11 = "aprepa";
            }
            iVar5 = BuildObject(pcVar11,0,pcVar9,0);
            ((prup *)(pcVar9 + -8))->powerup = iVar5;
            pcVar9[0x14] = false;
          }
        }
        else {
LAB_0044cd15:
          if ((bool)pcVar9[0x14] != false) goto LAB_0044cd1b;
        }
        pcVar9 = pcVar9 + 0x20;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  return;
}
