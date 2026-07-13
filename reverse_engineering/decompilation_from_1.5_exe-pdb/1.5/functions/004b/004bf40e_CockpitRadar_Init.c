/*
 * Entry: 004bf40e
 * Name: CockpitRadar::Init
 * Namespace: CockpitRadar
 * Signature: void Init(CockpitRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitRadar::Init(CockpitRadar *this)

{
  int iVar1;
  uint uVar2;
  
  if (useD3D == 0) {
    RADAR_BACKGROUND[0].index = GetSpriteIndex(RADAR_BACKGROUND[0].name);
    RADAR_BACKGROUND[1].index = GetSpriteIndex(RADAR_BACKGROUND[1].name);
  }
  else {
    RADAR_BACKGROUND[2].index = GetSpriteIndex(RADAR_BACKGROUND[2].name);
    RADAR_BACKGROUND[3].index = GetSpriteIndex(RADAR_BACKGROUND[3].name);
  }
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&RADAR_NUMBER[0].name + uVar2));
    *(int *)((int)&RADAR_NUMBER[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0x50);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&UNIT_TYPE_INFO[0].name + uVar2));
    *(int *)((int)&UNIT_TYPE_INFO[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 0x10;
  } while (uVar2 < 0x80);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&RADAR_PING[0].name + uVar2));
    *(int *)((int)&RADAR_PING[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 0x10;
  } while (uVar2 < 0xe0);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&COMPASS_DIR[0].name + uVar2));
    *(int *)((int)&COMPASS_DIR[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0x20);
  this->pingFrame = 0.0;
  nextBeep = -1e+30;
  this->scanner = (Scanner *)0x0;
  this->userObj = (GameObject *)0x0;
  this->timeSimulated = 0;
  this->timeBetweenSimulations = 200;
  return;
}
