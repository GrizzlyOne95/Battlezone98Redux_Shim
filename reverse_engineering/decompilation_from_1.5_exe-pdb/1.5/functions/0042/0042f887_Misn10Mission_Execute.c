/*
 * Entry: 0042f887
 * Name: Misn10Mission::Execute
 * Namespace: Misn10Mission
 * Signature: void Execute(Misn10Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn10Mission::Execute(Misn10Mission *this)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  char *pcVar7;
  
  if ((this->field16_0x40)._s_0.sav_free != false) {
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
    if (bVar3) {
      piVar1 = &(this->field18_0xbc)._s_0.tugger;
      iVar4 = GetTug((this->field18_0xbc)._s_0.sav);
      *piVar1 = iVar4;
      bVar3 = IsAlive(piVar1);
      if (bVar3) {
        iVar4 = GetTeamNum(*piVar1);
        (this->field16_0x40)._s_0.sav_free = false;
        if (iVar4 == 1) {
          (this->field16_0x40)._s_0.sav_secure = true;
        }
        else {
          iVar4 = (this->field18_0xbc)._s_0.ccatug;
          (this->field16_0x40)._s_0.sav_seized = true;
          *piVar1 = iVar4;
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.sav_secure == false) {
LAB_0042f916:
    if ((this->field16_0x40)._s_0.sav_seized != false) goto LAB_0042f91f;
  }
  else {
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.tugger);
    if (bVar3) goto LAB_0042f916;
    if ((this->field16_0x40)._s_0.sav_seized == false) {
      (this->field16_0x40)._s_0.sav_free = true;
      (this->field16_0x40)._s_0.chase_tug = false;
      (this->field16_0x40)._s_0.got_position = false;
      (this->field16_0x40)._s_0.sav_secure = false;
      (this->field16_0x40)._s_0.fighter1_underway = false;
      (this->field16_0x40)._s_0.fighter2_underway = false;
      goto LAB_0042f916;
    }
LAB_0042f91f:
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatug);
    if (!bVar3) {
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank1);
      if (bVar3) {
        piVar1 = &(this->field18_0xbc)._s_0.sav;
        bVar3 = IsAlive(piVar1);
        if (bVar3) {
          Goto((this->field18_0xbc)._s_0.ccatank1,*piVar1,1);
        }
      }
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank2);
      if (bVar3) {
        piVar1 = &(this->field18_0xbc)._s_0.sav;
        bVar3 = IsAlive(piVar1);
        if (bVar3) {
          Goto((this->field18_0xbc)._s_0.ccatank2,*piVar1,1);
        }
      }
      (this->field16_0x40)._s_0.sav_seized = false;
      (this->field16_0x40)._s_0.got_position = false;
      (this->field16_0x40)._s_0.sav_free = true;
    }
  }
  piVar1 = &(this->field18_0xbc)._s_0.ccatug;
  bVar3 = IsAlive(piVar1);
  if (!bVar3) {
    (this->field16_0x40)._s_0.tug_underway1 = false;
    (this->field16_0x40)._s_0.tug_underway2 = false;
    (this->field16_0x40)._s_0.tug_underway3 = false;
    (this->field16_0x40)._s_0.tug_underway4 = false;
    (this->field16_0x40)._s_0.tug_underway5 = false;
    (this->field16_0x40)._s_0.tug_underway6 = false;
    (this->field16_0x40)._s_0.tug_underway7 = false;
    (this->field16_0x40)._s_0.tug_after_sav = false;
    (this->field16_0x40)._s_0.return_to_base = false;
    (this->field16_0x40)._s_0.tug_wait_center = false;
    (this->field16_0x40)._s_0.tug_wait2 = false;
    (this->field16_0x40)._s_0.tug_wait3 = false;
    (this->field16_0x40)._s_0.tug_wait4 = false;
    (this->field16_0x40)._s_0.tug_wait5 = false;
    (this->field16_0x40)._s_0.tug_wait6 = false;
    (this->field16_0x40)._s_0.tug_wait7 = false;
    (this->field16_0x40)._s_0.tug_wait_base = false;
    (this->field16_0x40)._s_0.tug_at_wait_center = false;
    (this->field16_0x40)._s_0.got_position = false;
    (this->field16_0x40)._s_0.sav_warning = false;
  }
  if (((this->field16_0x40)._s_0.sav_seized != false) &&
     ((this->field16_0x40)._s_0.sav_warning == false)) {
    AudioMessage("misn1005.wav");
    (this->field16_0x40)._s_0.sav_warning = true;
  }
  iVar4 = GetPlayerHandle();
  (this->field18_0xbc)._s_0.user = iVar4;
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret1);
  if (!bVar3) {
    (this->field16_0x40)._s_0.turret1_underway = false;
    (this->field16_0x40)._s_0.turret1_stop = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret2);
  if (!bVar3) {
    (this->field16_0x40)._s_0.turret2_underway = false;
    (this->field16_0x40)._s_0.turret2_stop = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil1);
  if (!bVar3) {
    (this->field16_0x40)._s_0.artil1_stop = false;
    (this->field16_0x40)._s_0.artil1_underway = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil2);
  if (!bVar3) {
    (this->field16_0x40)._s_0.artil2_stop = false;
    (this->field16_0x40)._s_0.artil2_underway = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil3);
  if (!bVar3) {
    (this->field16_0x40)._s_0.artil3_stop = false;
    (this->field16_0x40)._s_0.artil3_underway = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccafighter1);
  if (!bVar3) {
    (this->field16_0x40)._s_0.fighter1_underway = false;
    (this->field16_0x40)._s_0.chase_tug = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccafighter2);
  if (!bVar3) {
    (this->field16_0x40)._s_0.fighter2_underway = false;
    (this->field16_0x40)._s_0.chase_tug = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank1);
  if (!bVar3) {
    (this->field16_0x40)._s_0.tank1_follow = false;
    (this->field16_0x40)._s_0.tank1_stop = false;
    (this->field16_0x40)._s_0.chase_tug = false;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank2);
  if (!bVar3) {
    (this->field16_0x40)._s_0.tank2_follow = false;
    (this->field16_0x40)._s_0.tank2_stop = false;
    (this->field16_0x40)._s_0.chase_tug = false;
  }
  bVar3 = IsAlive(piVar1);
  if (((bVar3) && ((this->field16_0x40)._s_0.sav_free != false)) &&
     ((this->field16_0x40)._s_0.got_position == false)) {
    fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
    fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
    if (fVar6 <= fVar5) {
LAB_0042fc4d:
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      if (fVar5 < fVar6) {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        if (fVar6 <= fVar5) goto LAB_0042fd94;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        if (fVar6 <= fVar5) goto LAB_0042fd94;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        if (fVar6 <= fVar5) goto LAB_0042fd94;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        if (fVar6 <= fVar5) goto LAB_0042fd94;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
        if (fVar6 <= fVar5) goto LAB_0042fd94;
        (this->field16_0x40)._s_0.position1 = false;
        (this->field16_0x40)._s_0.position2 = true;
        (this->field16_0x40)._s_0.position7 = false;
        goto LAB_00430419;
      }
LAB_0042fd94:
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      if (fVar5 < fVar6) {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        if (fVar6 <= fVar5) goto LAB_0042fede;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        if (fVar6 <= fVar5) goto LAB_0042fede;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        if (fVar6 <= fVar5) goto LAB_0042fede;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        if (fVar6 <= fVar5) goto LAB_0042fede;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
        if (fVar6 <= fVar5) goto LAB_0042fede;
        (this->field16_0x40)._s_0.position1 = false;
        (this->field16_0x40)._s_0.position2 = false;
        (this->field16_0x40)._s_0.position3 = true;
        (this->field16_0x40)._s_0.position7 = false;
        goto LAB_0043041c;
      }
LAB_0042fede:
      if ((this->field16_0x40)._s_0.sav_seized == false) {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
        if (fVar6 <= fVar5) goto LAB_00430034;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        if (fVar6 <= fVar5) goto LAB_00430034;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        if (fVar6 <= fVar5) goto LAB_00430034;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        if (fVar6 <= fVar5) goto LAB_00430034;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        if (fVar6 <= fVar5) goto LAB_00430034;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
        if (fVar6 <= fVar5) goto LAB_00430034;
        (this->field16_0x40)._s_0.position1 = false;
        (this->field16_0x40)._s_0.position2 = false;
        (this->field16_0x40)._s_0.position3 = false;
        (this->field16_0x40)._s_0.position4 = true;
        (this->field16_0x40)._s_0.position7 = false;
        goto LAB_0043041f;
      }
LAB_00430034:
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      if (fVar5 < fVar6) {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        if (fVar6 <= fVar5) goto LAB_00430184;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        if (fVar6 <= fVar5) goto LAB_00430184;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        if (fVar6 <= fVar5) goto LAB_00430184;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        if (fVar6 <= fVar5) goto LAB_00430184;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
        if (fVar6 <= fVar5) goto LAB_00430184;
        (this->field16_0x40)._s_0.position1 = false;
        (this->field16_0x40)._s_0.position2 = false;
        (this->field16_0x40)._s_0.position3 = false;
        (this->field16_0x40)._s_0.position4 = false;
        (this->field16_0x40)._s_0.position5 = true;
        (this->field16_0x40)._s_0.position7 = false;
        goto LAB_00430422;
      }
LAB_00430184:
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      if (fVar6 <= fVar5) {
LAB_004302d7:
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
          fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
          if (fVar5 < fVar6) {
            fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
            fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
            if (fVar5 < fVar6) {
              fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
              fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
              if (fVar5 < fVar6) {
                fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
                fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
                if (fVar5 < fVar6) {
                  fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7)
                  ;
                  fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6)
                  ;
                  if (fVar5 < fVar6) {
                    (this->field16_0x40)._s_0.position1 = false;
                    (this->field16_0x40)._s_0.position7 = true;
                    goto LAB_00430416;
                  }
                }
              }
            }
          }
        }
      }
      else {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys2);
        if (fVar6 <= fVar5) goto LAB_004302d7;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
        if (fVar6 <= fVar5) goto LAB_004302d7;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
        if (fVar6 <= fVar5) goto LAB_004302d7;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
        if (fVar6 <= fVar5) goto LAB_004302d7;
        fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
        fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
        if (fVar6 <= fVar5) goto LAB_004302d7;
        (this->field16_0x40)._s_0.position1 = false;
        (this->field16_0x40)._s_0.position2 = false;
        (this->field16_0x40)._s_0.position3 = false;
        (this->field16_0x40)._s_0.position4 = false;
        (this->field16_0x40)._s_0.position5 = false;
        (this->field16_0x40)._s_0.position6 = true;
        (this->field16_0x40)._s_0.position7 = false;
      }
    }
    else {
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys3);
      if (fVar6 <= fVar5) goto LAB_0042fc4d;
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys4);
      if (fVar6 <= fVar5) goto LAB_0042fc4d;
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys5);
      if (fVar6 <= fVar5) goto LAB_0042fc4d;
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys6);
      if (fVar6 <= fVar5) goto LAB_0042fc4d;
      fVar5 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys1);
      fVar6 = GetDistance((this->field18_0xbc)._s_0.sav,(this->field18_0xbc)._s_0.geys7);
      if (fVar6 <= fVar5) goto LAB_0042fc4d;
      (this->field16_0x40)._s_0.position1 = true;
      (this->field16_0x40)._s_0.position7 = false;
LAB_00430416:
      (this->field16_0x40)._s_0.position2 = false;
LAB_00430419:
      (this->field16_0x40)._s_0.position3 = false;
LAB_0043041c:
      (this->field16_0x40)._s_0.position4 = false;
LAB_0043041f:
      (this->field16_0x40)._s_0.position5 = false;
LAB_00430422:
      (this->field16_0x40)._s_0.position6 = false;
    }
    (this->field16_0x40)._s_0.got_position = true;
  }
  if ((this->field16_0x40)._s_0.start_done == false) {
    AudioMessage("misn1000.wav");
    InfoDisplay::ClearObjectives(&infoDisplay);
    InfoDisplay::AddObjective(&infoDisplay,"misn1000.otf",DisplayInterface::colorWhite,8.0);
    SetIndependence((this->field18_0xbc)._s_0.svartil1,1);
    SetIndependence((this->field18_0xbc)._s_0.svartil2,1);
    SetScrap(1,0x1e);
    SetPilot(1,10);
    SetScrap(2,0x28);
    SetPilot(2,0x28);
    SetAIP("misn10.aip",2);
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.turret1_check = fVar5 + 19.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.turret2_check = fVar5 + 20.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.artil1_check = fVar5 + 21.0;
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.artil2_check = fVar5 + 22.0;
    fVar5 = Get_Time();
    iVar4 = (this->field18_0xbc)._s_0.nav1;
    (this->field17_0x84)._s_0.artil3_check = fVar5 + 23.0;
    SetObjectiveName(iVar4,"Relic Site");
    SetObjectiveName((this->field18_0xbc)._s_0.nav2,"CCA Base");
    SetObjectiveName((this->field18_0xbc)._s_0.nav3,"Drop Zone");
    SetObjectiveName((this->field18_0xbc)._s_0.sav,"Alien Relic");
    (this->field16_0x40)._s_0.relic_free = true;
    (this->field16_0x40)._s_0.start_done = true;
  }
  fVar5 = GetDistance((this->field18_0xbc)._s_0.user,(this->field18_0xbc)._s_0.sav);
  if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.objective_on == false)) {
    SetObjectiveOn((this->field18_0xbc)._s_0.sav);
    (this->field16_0x40)._s_0.objective_on = true;
  }
  if ((this->field16_0x40)._s_0.relic_free != false) {
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccafighter1);
    if ((bVar3) && ((this->field16_0x40)._s_0.fighter1_underway == false)) {
      Follow((this->field18_0xbc)._s_0.ccafighter1,(this->field18_0xbc)._s_0.sav,1);
      (this->field16_0x40)._s_0.fighter1_underway = true;
    }
    if ((this->field16_0x40)._s_0.relic_free != false) {
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccafighter2);
      if ((bVar3) && ((this->field16_0x40)._s_0.fighter2_underway == false)) {
        Follow((this->field18_0xbc)._s_0.ccafighter2,(this->field18_0xbc)._s_0.sav,1);
        (this->field16_0x40)._s_0.fighter2_underway = true;
      }
    }
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret1);
  if ((bVar3) && ((this->field16_0x40)._s_0.turret1_underway == false)) {
    Goto((this->field18_0xbc)._s_0.ccaturret1,"relic_path1",1);
    (this->field16_0x40)._s_0.turret1_underway = true;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret2);
  if ((bVar3) && ((this->field16_0x40)._s_0.turret2_underway == false)) {
    Goto((this->field18_0xbc)._s_0.ccaturret2,"relic_path1",1);
    (this->field16_0x40)._s_0.turret2_underway = true;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret3);
  if ((bVar3) && ((this->field16_0x40)._s_0.turret3_underway == false)) {
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccarecycle);
    if (bVar3) {
      fVar5 = GetDistance((this->field18_0xbc)._s_0.ccaturret3,(this->field18_0xbc)._s_0.ccarecycle)
      ;
      if (30.0 < fVar5) {
        Defend((this->field18_0xbc)._s_0.ccaturret3,1);
        (this->field16_0x40)._s_0.turret3_underway = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.turret1_underway != false) {
    fVar5 = Get_Time();
    if ((this->field17_0x84)._s_0.turret1_check < fVar5) {
      fVar5 = Get_Time();
      (this->field17_0x84)._s_0.turret1_check = fVar5 + 3.0;
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret1);
      if ((bVar3) && ((this->field16_0x40)._s_0.turret1_stop == false)) {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.ccaturret1,(this->field18_0xbc)._s_0.geys1);
        if (fVar5 < 50.0) {
          Defend((this->field18_0xbc)._s_0.ccaturret1,1);
          (this->field16_0x40)._s_0.turret1_stop = true;
        }
      }
    }
  }
  if ((this->field16_0x40)._s_0.turret2_underway != false) {
    fVar5 = Get_Time();
    if ((this->field17_0x84)._s_0.turret2_check < fVar5) {
      fVar5 = Get_Time();
      (this->field17_0x84)._s_0.turret2_check = fVar5 + 3.0;
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret2);
      if ((bVar3) && ((this->field16_0x40)._s_0.turret2_stop == false)) {
        fVar5 = GetDistance((this->field18_0xbc)._s_0.ccaturret2,(this->field18_0xbc)._s_0.geys2);
        if (fVar5 < 50.0) {
          Deploy((this->field18_0xbc)._s_0.ccaturret2);
          Defend((this->field18_0xbc)._s_0.ccaturret2,1);
          (this->field16_0x40)._s_0.turret2_stop = true;
        }
      }
    }
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccafighter1);
  if (bVar3) {
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccafighter2);
    if (bVar3) {
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret1);
      if (bVar3) {
        bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaturret2);
        if ((bVar3) && ((this->field16_0x40)._s_0.plan_a == false)) {
          iVar4 = GetScrap(2);
          if (0xf < iVar4) {
            SetAIP("misn10a.aip",2);
            (this->field16_0x40)._s_0.plan_a = true;
          }
        }
      }
    }
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil1);
  if ((bVar3) && ((this->field16_0x40)._s_0.artil1_underway == false)) {
    Goto((this->field18_0xbc)._s_0.ccaartil1,"artil1_path",1);
    (this->field16_0x40)._s_0.artil1_underway = true;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil2);
  if ((bVar3) && ((this->field16_0x40)._s_0.artil2_underway == false)) {
    Goto((this->field18_0xbc)._s_0.ccaartil2,"artil2_path",1);
    (this->field16_0x40)._s_0.artil2_underway = true;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil3);
  if ((bVar3) && ((this->field16_0x40)._s_0.artil3_underway == false)) {
    Goto((this->field18_0xbc)._s_0.ccaartil3,"relic_path1",1);
    (this->field16_0x40)._s_0.artil3_underway = true;
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.artil1_check < fVar5) {
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.artil1_check = fVar5 + 3.0;
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil1);
    if ((bVar3) && ((this->field16_0x40)._s_0.artil1_stop == false)) {
      fVar5 = GetDistance((this->field18_0xbc)._s_0.ccaartil1,(this->field18_0xbc)._s_0.post1_geyser
                         );
      if (fVar5 < 20.0) {
        Defend((this->field18_0xbc)._s_0.ccaartil1,1);
        (this->field16_0x40)._s_0.artil1_stop = true;
      }
    }
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.artil2_check < fVar5) {
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.artil2_check = fVar5 + 3.0;
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil2);
    if ((bVar3) && ((this->field16_0x40)._s_0.artil2_stop == false)) {
      fVar5 = GetDistance((this->field18_0xbc)._s_0.ccaartil2,(this->field18_0xbc)._s_0.post3_geyser
                         );
      if (fVar5 < 20.0) {
        Defend((this->field18_0xbc)._s_0.ccaartil2,1);
        (this->field16_0x40)._s_0.artil2_stop = true;
      }
    }
  }
  fVar5 = Get_Time();
  if ((this->field17_0x84)._s_0.artil3_check < fVar5) {
    fVar5 = Get_Time();
    (this->field17_0x84)._s_0.artil3_check = fVar5 + 3.0;
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccaartil3);
    if ((bVar3) && ((this->field16_0x40)._s_0.artil3_stop == false)) {
      fVar5 = GetDistance((this->field18_0xbc)._s_0.ccaartil3,(this->field18_0xbc)._s_0.geys2);
      if (fVar5 < 50.0) {
        Defend((this->field18_0xbc)._s_0.ccaartil3,1);
        (this->field16_0x40)._s_0.artil3_stop = true;
      }
    }
  }
  bVar3 = IsAlive(piVar1);
  if ((bVar3) && ((this->field16_0x40)._s_0.got_position != false)) {
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank1);
    if ((bVar3) && ((this->field16_0x40)._s_0.tank1_follow == false)) {
      Follow((this->field18_0xbc)._s_0.ccatank1,*piVar1,1);
      (this->field16_0x40)._s_0.tank1_follow = true;
    }
    bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank2);
    if ((bVar3) && ((this->field16_0x40)._s_0.tank2_follow == false)) {
      Follow((this->field18_0xbc)._s_0.ccatank2,*piVar1,1);
      (this->field16_0x40)._s_0.tank2_follow = true;
    }
    if ((this->field16_0x40)._s_0.tug_underway1 == false) {
      if ((((this->field16_0x40)._s_0.sav_free != false) &&
          ((this->field16_0x40)._s_0.position1 != false)) &&
         ((this->field16_0x40)._s_0.tug_after_sav == false)) {
        Goto(*piVar1,"relic_path1",1);
        (this->field16_0x40)._s_0.tug_underway1 = true;
      }
      if ((this->field16_0x40)._s_0.tug_underway1 != false) goto LAB_00430a73;
LAB_00430b61:
      if (((this->field16_0x40)._s_0.sav_free == false) ||
         ((this->field16_0x40)._s_0.position2 == false)) goto LAB_00430b8a;
      if ((this->field16_0x40)._s_0.tug_underway2 == false) {
        if ((this->field16_0x40)._s_0.tug_after_sav == false) {
          Goto(*piVar1,"relic_path1",1);
          (this->field16_0x40)._s_0.tug_underway2 = true;
        }
        goto LAB_00430b8a;
      }
LAB_00430b93:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys2);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.tug_underway2 == false) goto LAB_00430c3a;
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys2);
        if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
          Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
          (this->field16_0x40)._s_0.tug_after_sav = true;
        }
        goto LAB_00430c3a;
      }
LAB_00430c63:
      if ((this->field16_0x40)._s_0.tug_underway3 != false) goto LAB_00430c6c;
LAB_00430d13:
      if (((this->field16_0x40)._s_0.sav_free == false) ||
         ((this->field16_0x40)._s_0.position4 == false)) goto LAB_00430d3c;
      if ((this->field16_0x40)._s_0.tug_underway4 == false) {
        if ((this->field16_0x40)._s_0.tug_after_sav == false) {
          Goto(*piVar1,"attack_path_central",1);
          (this->field16_0x40)._s_0.tug_underway4 = true;
        }
        goto LAB_00430d3c;
      }
LAB_00430d45:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys4);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.tug_underway4 == false) goto LAB_00430dec;
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys4);
        if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
          Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
          (this->field16_0x40)._s_0.tug_after_sav = true;
        }
        goto LAB_00430dec;
      }
LAB_00430e15:
      if ((this->field16_0x40)._s_0.tug_underway5 != false) goto LAB_00430e1e;
LAB_00430ec5:
      if (((this->field16_0x40)._s_0.sav_free == false) ||
         ((this->field16_0x40)._s_0.position6 == false)) goto LAB_00430eee;
      if ((this->field16_0x40)._s_0.tug_underway6 == false) {
        if ((this->field16_0x40)._s_0.tug_after_sav == false) {
          Goto(*piVar1,"attack_path_north",1);
          (this->field16_0x40)._s_0.tug_underway6 = true;
        }
        goto LAB_00430eee;
      }
LAB_00430ef7:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys6);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.tug_underway6 == false) goto LAB_00430f9e;
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys6);
        if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
          Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
          (this->field16_0x40)._s_0.tug_after_sav = true;
        }
        goto LAB_00430f9e;
      }
LAB_00430fc7:
      if ((this->field16_0x40)._s_0.tug_underway7 != false) goto LAB_00430fd0;
LAB_00431077:
      if ((this->field16_0x40)._s_0.tug_after_sav == false) goto LAB_004311a7;
    }
    else {
LAB_00430a73:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys1);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank1);
            if (bVar3) {
              Follow((this->field18_0xbc)._s_0.ccatank1,*piVar1,0);
            }
            bVar3 = IsAlive(&(this->field18_0xbc)._s_0.ccatank2);
            if (bVar3) {
              Follow((this->field18_0xbc)._s_0.ccatank2,*piVar1,0);
            }
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.tug_underway1 == false) goto LAB_00430b61;
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys1);
        if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
          Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
          (this->field16_0x40)._s_0.tug_after_sav = true;
        }
        goto LAB_00430b61;
      }
LAB_00430b8a:
      if ((this->field16_0x40)._s_0.tug_underway2 != false) goto LAB_00430b93;
LAB_00430c3a:
      if (((this->field16_0x40)._s_0.sav_free == false) ||
         ((this->field16_0x40)._s_0.position3 == false)) goto LAB_00430c63;
      if ((this->field16_0x40)._s_0.tug_underway3 == false) {
        if ((this->field16_0x40)._s_0.tug_after_sav == false) {
          Goto(*piVar1,"attack_path_central",1);
          (this->field16_0x40)._s_0.tug_underway3 = true;
        }
        goto LAB_00430c63;
      }
LAB_00430c6c:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys3);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.tug_underway3 == false) goto LAB_00430d13;
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys3);
        if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
          Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
          (this->field16_0x40)._s_0.tug_after_sav = true;
        }
        goto LAB_00430d13;
      }
LAB_00430d3c:
      if ((this->field16_0x40)._s_0.tug_underway4 != false) goto LAB_00430d45;
LAB_00430dec:
      if (((this->field16_0x40)._s_0.sav_free == false) ||
         ((this->field16_0x40)._s_0.position5 == false)) goto LAB_00430e15;
      if ((this->field16_0x40)._s_0.tug_underway5 == false) {
        if ((this->field16_0x40)._s_0.tug_after_sav == false) {
          Goto(*piVar1,"attack_path_south",1);
          (this->field16_0x40)._s_0.tug_underway5 = true;
        }
        goto LAB_00430e15;
      }
LAB_00430e1e:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys5);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if ((this->field16_0x40)._s_0.tug_underway5 == false) goto LAB_00430ec5;
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys5);
        if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
          Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
          (this->field16_0x40)._s_0.tug_after_sav = true;
        }
        goto LAB_00430ec5;
      }
LAB_00430eee:
      if ((this->field16_0x40)._s_0.tug_underway6 != false) goto LAB_00430ef7;
LAB_00430f9e:
      if (((this->field16_0x40)._s_0.sav_free == false) ||
         ((this->field16_0x40)._s_0.position7 == false)) goto LAB_00430fc7;
      if ((this->field16_0x40)._s_0.tug_underway7 == false) {
        if ((this->field16_0x40)._s_0.tug_after_sav == false) {
          Goto(*piVar1,"attack_path_south",1);
          (this->field16_0x40)._s_0.tug_underway7 = true;
        }
        goto LAB_00430fc7;
      }
LAB_00430fd0:
      if ((this->field16_0x40)._s_0.sav_free != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
        fVar6 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys7);
        if (fVar5 < fVar6) {
          fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.sav);
          if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.tug_after_sav == false)) {
            Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
            (this->field16_0x40)._s_0.tug_after_sav = true;
          }
        }
      }
      if (((this->field16_0x40)._s_0.tug_underway7 == false) ||
         ((this->field16_0x40)._s_0.sav_free == false)) goto LAB_00431077;
      fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys7);
      if (100.0 <= fVar5) goto LAB_00431077;
      if ((this->field16_0x40)._s_0.tug_after_sav == false) {
        Pickup(*piVar1,(this->field18_0xbc)._s_0.sav,1);
        (this->field16_0x40)._s_0.tug_after_sav = true;
        goto LAB_00431077;
      }
    }
    if ((((this->field16_0x40)._s_0.tug_underway1 != false) &&
        ((this->field16_0x40)._s_0.sav_seized != false)) &&
       ((this->field16_0x40)._s_0.return_to_base == false)) {
      Goto(*piVar1,"main_return_path",1);
      (this->field16_0x40)._s_0.return_to_base = true;
    }
    if ((this->field16_0x40)._s_0.tug_after_sav != false) {
      if ((((this->field16_0x40)._s_0.tug_underway2 != false) &&
          ((this->field16_0x40)._s_0.sav_seized != false)) &&
         ((this->field16_0x40)._s_0.return_to_base == false)) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.ccarecycle,1);
        (this->field16_0x40)._s_0.return_to_base = true;
      }
      if ((this->field16_0x40)._s_0.tug_after_sav != false) {
        if ((((this->field16_0x40)._s_0.tug_underway3 != false) &&
            ((this->field16_0x40)._s_0.sav_seized != false)) &&
           ((this->field16_0x40)._s_0.return_to_base == false)) {
          Goto(*piVar1,"lsouth_return_path",1);
          (this->field16_0x40)._s_0.return_to_base = true;
        }
        if ((this->field16_0x40)._s_0.tug_after_sav != false) {
          if ((((this->field16_0x40)._s_0.tug_underway4 != false) &&
              ((this->field16_0x40)._s_0.sav_seized != false)) &&
             ((this->field16_0x40)._s_0.return_to_base == false)) {
            Goto(*piVar1,"main_return_path",1);
            (this->field16_0x40)._s_0.return_to_base = true;
          }
          if ((this->field16_0x40)._s_0.tug_after_sav != false) {
            if ((((this->field16_0x40)._s_0.tug_underway5 != false) &&
                ((this->field16_0x40)._s_0.sav_seized != false)) &&
               ((this->field16_0x40)._s_0.return_to_base == false)) {
              Goto(*piVar1,"ssouth_return_path",1);
              (this->field16_0x40)._s_0.return_to_base = true;
            }
            if ((this->field16_0x40)._s_0.tug_after_sav != false) {
              if ((((this->field16_0x40)._s_0.tug_underway6 != false) &&
                  ((this->field16_0x40)._s_0.sav_seized != false)) &&
                 ((this->field16_0x40)._s_0.return_to_base == false)) {
                Goto(*piVar1,"main_return_path",1);
                (this->field16_0x40)._s_0.return_to_base = true;
              }
              if (((((this->field16_0x40)._s_0.tug_after_sav != false) &&
                   ((this->field16_0x40)._s_0.tug_underway7 != false)) &&
                  ((this->field16_0x40)._s_0.sav_seized != false)) &&
                 ((this->field16_0x40)._s_0.return_to_base == false)) {
                Goto(*piVar1,"msouth_return_path",1);
                (this->field16_0x40)._s_0.return_to_base = true;
              }
            }
          }
        }
      }
    }
  }
LAB_004311a7:
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
  if ((!bVar3) && (bVar3 = (this->field16_0x40)._s_0.sav_secure, bVar3 != false)) {
    if ((this->field16_0x40)._s_0.tug_underway1 == false) {
      (this->field16_0x40)._s_0.tug_wait_base = true;
    }
    if (bVar3 != false) {
      if ((this->field16_0x40)._s_0.tug_underway1 != false) {
        (this->field16_0x40)._s_0.tug_underway1 = false;
        (this->field16_0x40)._s_0.tug_wait_center = true;
      }
      if ((bVar3 != false) && ((this->field16_0x40)._s_0.tug_underway2 == false)) {
        (this->field16_0x40)._s_0.tug_wait_base = true;
      }
    }
  }
  if ((this->field16_0x40)._s_0.sav_secure != false) {
    if ((this->field16_0x40)._s_0.tug_underway2 != false) {
      fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys2);
      if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.tug_wait2 == false)) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.geys2,1);
        (this->field16_0x40)._s_0.tug_underway2 = false;
        (this->field16_0x40)._s_0.tug_wait2 = true;
      }
    }
    if (((((this->field16_0x40)._s_0.sav_secure != false) &&
         ((this->field16_0x40)._s_0.tug_underway2 != false)) &&
        ((this->field16_0x40)._s_0.tug_after_sav != false)) &&
       ((this->field16_0x40)._s_0.tug_wait2 == false)) {
      Goto(*piVar1,(this->field18_0xbc)._s_0.geys2,1);
      (this->field16_0x40)._s_0.tug_underway2 = false;
      (this->field16_0x40)._s_0.tug_after_sav = false;
      (this->field16_0x40)._s_0.tug_wait2 = true;
    }
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
  if (bVar3) {
LAB_00431278:
    if ((this->field16_0x40)._s_0.sav_secure != false) {
      if ((this->field16_0x40)._s_0.tug_underway3 != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys3);
        if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.tug_wait3 == false)) {
          Goto(*piVar1,(this->field18_0xbc)._s_0.geys3,1);
          (this->field16_0x40)._s_0.tug_underway3 = false;
          (this->field16_0x40)._s_0.tug_wait3 = true;
        }
      }
      if ((((this->field16_0x40)._s_0.sav_secure != false) &&
          ((this->field16_0x40)._s_0.tug_underway3 != false)) &&
         (((this->field16_0x40)._s_0.tug_after_sav != false &&
          ((this->field16_0x40)._s_0.tug_wait3 == false)))) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.geys3,1);
        (this->field16_0x40)._s_0.tug_underway3 = false;
        (this->field16_0x40)._s_0.tug_after_sav = false;
        (this->field16_0x40)._s_0.tug_wait3 = true;
      }
    }
  }
  else if ((this->field16_0x40)._s_0.sav_secure != false) {
    if ((this->field16_0x40)._s_0.tug_underway3 == false) {
      (this->field16_0x40)._s_0.tug_wait_base = true;
    }
    goto LAB_00431278;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
  if (bVar3) {
LAB_0043130b:
    if ((this->field16_0x40)._s_0.sav_secure != false) {
      if ((this->field16_0x40)._s_0.tug_underway4 != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys4);
        if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.tug_wait4 == false)) {
          Goto(*piVar1,(this->field18_0xbc)._s_0.geys4,1);
          (this->field16_0x40)._s_0.tug_underway4 = false;
          (this->field16_0x40)._s_0.tug_wait4 = true;
        }
      }
      if (((((this->field16_0x40)._s_0.sav_secure != false) &&
           ((this->field16_0x40)._s_0.tug_underway4 != false)) &&
          ((this->field16_0x40)._s_0.tug_after_sav != false)) &&
         ((this->field16_0x40)._s_0.tug_wait4 == false)) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.geys4,1);
        (this->field16_0x40)._s_0.tug_underway4 = false;
        (this->field16_0x40)._s_0.tug_after_sav = false;
        (this->field16_0x40)._s_0.tug_wait4 = true;
      }
    }
  }
  else if ((this->field16_0x40)._s_0.sav_secure != false) {
    if ((this->field16_0x40)._s_0.tug_underway4 == false) {
      (this->field16_0x40)._s_0.tug_wait_base = true;
    }
    goto LAB_0043130b;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
  if (bVar3) {
LAB_0043139e:
    if ((this->field16_0x40)._s_0.sav_secure != false) {
      if ((this->field16_0x40)._s_0.tug_underway5 != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys5);
        if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.tug_wait5 == false)) {
          Goto(*piVar1,(this->field18_0xbc)._s_0.geys5,1);
          (this->field16_0x40)._s_0.tug_underway5 = false;
          (this->field16_0x40)._s_0.tug_wait5 = true;
        }
      }
      if ((((this->field16_0x40)._s_0.sav_secure != false) &&
          ((this->field16_0x40)._s_0.tug_underway5 != false)) &&
         (((this->field16_0x40)._s_0.tug_after_sav != false &&
          ((this->field16_0x40)._s_0.tug_wait5 == false)))) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.geys5,1);
        (this->field16_0x40)._s_0.tug_underway5 = false;
        (this->field16_0x40)._s_0.tug_after_sav = false;
        (this->field16_0x40)._s_0.tug_wait5 = true;
      }
    }
  }
  else if ((this->field16_0x40)._s_0.sav_secure != false) {
    if ((this->field16_0x40)._s_0.tug_underway5 == false) {
      (this->field16_0x40)._s_0.tug_wait_base = true;
    }
    goto LAB_0043139e;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
  if (bVar3) {
LAB_00431431:
    if ((this->field16_0x40)._s_0.sav_secure != false) {
      if ((this->field16_0x40)._s_0.tug_underway6 != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys6);
        if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.tug_wait6 == false)) {
          Goto(*piVar1,(this->field18_0xbc)._s_0.geys6,1);
          (this->field16_0x40)._s_0.tug_underway6 = false;
          (this->field16_0x40)._s_0.tug_wait6 = true;
        }
      }
      if (((((this->field16_0x40)._s_0.sav_secure != false) &&
           ((this->field16_0x40)._s_0.tug_underway6 != false)) &&
          ((this->field16_0x40)._s_0.tug_after_sav != false)) &&
         ((this->field16_0x40)._s_0.tug_wait6 == false)) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.geys6,1);
        (this->field16_0x40)._s_0.tug_underway6 = false;
        (this->field16_0x40)._s_0.tug_after_sav = false;
        (this->field16_0x40)._s_0.tug_wait6 = true;
      }
    }
  }
  else if ((this->field16_0x40)._s_0.sav_secure != false) {
    if ((this->field16_0x40)._s_0.tug_underway6 == false) {
      (this->field16_0x40)._s_0.tug_wait_base = true;
    }
    goto LAB_00431431;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.sav);
  if (bVar3) {
LAB_004314cc:
    if ((this->field16_0x40)._s_0.sav_secure != false) {
      if ((this->field16_0x40)._s_0.tug_underway7 != false) {
        fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.geys7);
        if ((fVar5 < 50.0) && ((this->field16_0x40)._s_0.tug_wait7 == false)) {
          Goto(*piVar1,(this->field18_0xbc)._s_0.geys7,1);
          (this->field16_0x40)._s_0.tug_underway7 = false;
          (this->field16_0x40)._s_0.tug_wait7 = true;
        }
      }
      if ((((this->field16_0x40)._s_0.sav_secure != false) &&
          ((this->field16_0x40)._s_0.tug_underway7 != false)) &&
         (((this->field16_0x40)._s_0.tug_after_sav != false &&
          ((this->field16_0x40)._s_0.tug_wait7 == false)))) {
        Goto(*piVar1,(this->field18_0xbc)._s_0.geys7,1);
        (this->field16_0x40)._s_0.tug_underway7 = false;
        (this->field16_0x40)._s_0.tug_after_sav = false;
        (this->field16_0x40)._s_0.tug_wait7 = true;
      }
    }
  }
  else if ((this->field16_0x40)._s_0.sav_secure != false) {
    if ((this->field16_0x40)._s_0.tug_underway7 == false) {
      (this->field16_0x40)._s_0.sav_seized = true;
      (this->field16_0x40)._s_0.tug_wait_base = true;
    }
    goto LAB_004314cc;
  }
  if (((this->field18_0xbc)._s_0.tugger != 0) && ((this->field16_0x40)._s_0.chase_tug == false)) {
    piVar1 = &(this->field18_0xbc)._s_0.ccafighter1;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.ccafighter2;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.ccatank1;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.ccatank2;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.svartil1;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.svartil2;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.ccaartil1;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.ccaartil2;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    piVar1 = &(this->field18_0xbc)._s_0.ccaartil3;
    bVar3 = IsAlive(piVar1);
    if (bVar3) {
      Attack(*piVar1,(this->field18_0xbc)._s_0.tugger,1);
    }
    (this->field16_0x40)._s_0.chase_tug = true;
  }
  fVar5 = Get_Time();
  if (((this->field17_0x84)._s_0.geys1check < fVar5) &&
     ((this->field16_0x40)._s_0.chase_tug == false)) {
    fVar5 = Get_Time();
    iVar4 = (this->field18_0xbc)._s_0.geys1;
    iVar2 = (this->field18_0xbc)._s_0.user;
    (this->field17_0x84)._s_0.geys1check = fVar5 + 150.0;
    fVar5 = GetDistance(iVar2,iVar4);
    piVar1 = &(this->field18_0xbc)._s_0.svartil1;
    if (200.0 <= fVar5) {
      bVar3 = IsAlive(piVar1);
      if (bVar3) {
        Attack(*piVar1,(this->field18_0xbc)._s_0.geys1,1);
      }
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.svartil2);
      if (!bVar3) goto LAB_00431761;
      iVar4 = (this->field18_0xbc)._s_0.geys1;
    }
    else {
      bVar3 = IsAlive(piVar1);
      if (bVar3) {
        Attack(*piVar1,(this->field18_0xbc)._s_0.user,1);
      }
      bVar3 = IsAlive(&(this->field18_0xbc)._s_0.svartil2);
      if (!bVar3) goto LAB_00431761;
      iVar4 = (this->field18_0xbc)._s_0.user;
    }
    Attack((this->field18_0xbc)._s_0.svartil2,iVar4,1);
  }
LAB_00431761:
  piVar1 = &(this->field18_0xbc)._s_0.sav;
  bVar3 = IsAlive(piVar1);
  if (bVar3) {
    fVar5 = Get_Time();
    if ((this->field17_0x84)._s_0.next_second < fVar5) {
      AddHealth(*piVar1,100.0);
      fVar5 = Get_Time();
      (this->field17_0x84)._s_0.next_second = fVar5 + 1.0;
    }
  }
  if ((this->field16_0x40)._s_0.sav_secure != false) {
    fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.nsdfrecycle);
    if ((fVar5 < 100.0) && ((this->field16_0x40)._s_0.game_over == false)) {
      AudioMessage("misn1001.wav");
      pcVar7 = "misn10w1.des";
      fVar5 = Get_Time();
      SucceedMission(fVar5 + 15.0,pcVar7);
      (this->field16_0x40)._s_0.game_over = true;
    }
  }
  if (((this->field16_0x40)._s_0.sav_seized != false) &&
     ((this->field16_0x40)._s_0.game_over == false)) {
    fVar5 = GetDistance(*piVar1,(this->field18_0xbc)._s_0.ccarecycle);
    if (fVar5 < 100.0) {
      AudioMessage("misn1002.wav");
      pcVar7 = "misn10f1.des";
      fVar5 = Get_Time();
      FailMission(fVar5 + 15.0,pcVar7);
      (this->field16_0x40)._s_0.game_over = true;
    }
  }
  bVar3 = IsAlive(piVar1);
  if ((!bVar3) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn1003.wav");
    pcVar7 = "misn10f2.des";
    fVar5 = Get_Time();
    FailMission(fVar5 + 15.0,pcVar7);
    (this->field16_0x40)._s_0.game_over = true;
  }
  bVar3 = IsAlive(&(this->field18_0xbc)._s_0.nsdfrecycle);
  if ((!bVar3) && ((this->field16_0x40)._s_0.game_over == false)) {
    AudioMessage("misn1004.wav");
    pcVar7 = "misn10f3.des";
    fVar5 = Get_Time();
    FailMission(fVar5 + 15.0,pcVar7);
    (this->field16_0x40)._s_0.game_over = true;
  }
  return;
}
