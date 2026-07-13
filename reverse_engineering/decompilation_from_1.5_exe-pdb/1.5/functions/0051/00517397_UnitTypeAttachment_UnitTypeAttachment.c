/*
 * Entry: 00517397
 * Name: UnitTypeAttachment::UnitTypeAttachment
 * Namespace: UnitTypeAttachment
 * Signature: UnitTypeAttachment * UnitTypeAttachment(UnitTypeAttachment * this, GameObjectClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnitTypeAttachment * __thiscall
UnitTypeAttachment::UnitTypeAttachment(UnitTypeAttachment *this,GameObjectClass *param_1)

{
  char cVar1;
  OBJECT_CLASS_T OVar2;
  long64 lVar3;
  ushort uVar4;
  long64 *plVar5;
  char *pcVar6;
  int extraout_EAX;
  int iVar7;
  
  this->_padding_ = (int)&_vftable_;
  memset(&this->type,0,0x88);
  pcVar6 = (this->type).symbolid;
  plVar5 = &param_1->cfg;
  iVar7 = (int)pcVar6 - (int)plVar5;
  do {
    lVar3 = *plVar5;
    *(char *)(iVar7 + (int)plVar5) = (char)lVar3;
    plVar5 = (long64 *)((int)plVar5 + 1);
  } while ((char)lVar3 != '\0');
  (this->type).symbolid[8] = '\0';
  iVar7 = 0x34 - (int)pcVar6;
  do {
    cVar1 = *pcVar6;
    pcVar6[(int)&this->type + iVar7] = cVar1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  (this->type).buildcost = (ushort)param_1->scrapCost;
  OVar2 = param_1->class_id;
  if (((OVar2 == CLASS_ID_HELICOPTER) || (OVar2 == CLASS_ID_VEHICLE)) || (OVar2 == CLASS_ID_PERSON))
  {
    _ftol2_sse();
    iVar7 = 0xff;
    if (extraout_EAX < 0x100) {
      iVar7 = extraout_EAX;
    }
    (this->type).seeingrange = (uchar)iVar7;
  }
  else {
    (this->type).seeingrange = '\0';
  }
  uVar4 = (ushort)defaultPrereqType;
  if (unitcycles == 0) {
    prereqTypeCount = prereqTypeCount + 1;
    uVar4 = (ushort)prereqTypeCount;
  }
  (this->type).prereq.prereqtype = uVar4;
  (this->type).prereq.makers[0] = 0;
  (this->type).prereq.makers[1] = 0;
  (this->type).prereq.prereqs[0] = 0;
  (this->type).prereq.prereqs[1] = 0;
  (this->type).prereq.equivalence = 0;
  weapon0.firedelay = 1;
  weapon0.oinfo.hitpoints = 1;
  part0.nrweapons = 1;
  part0.weaponinfo[0].type = &weapon0;
  (this->type).partinfo.nrparts = 1;
  (this->type).partinfo.parts[0].parttype = &part0;
  (this->type).resource[0].maxstored = 0;
  (this->type).resource[1].maxstored = 0;
  (this->type).resource[2].maxstored = 0;
  (this->type).resource[3].maxstored = 0;
  (this->type).resource[4].maxstored = 0;
  if (param_1->sig == 0x53434156) {
    (this->type).resource[1].maxstored = (int)param_1[2].bBox.max.x;
  }
  (this->type).abilities =
       (tagUNITTYPE_ABILITIES)
       ((uint)(param_1->sig == 0x434e5354) * 2 | (uint)(this->type).abilities & 0xfffffffc);
  return this;
}
