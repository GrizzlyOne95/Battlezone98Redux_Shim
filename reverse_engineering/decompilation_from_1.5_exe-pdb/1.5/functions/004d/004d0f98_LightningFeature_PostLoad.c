/*
 * Entry: 004d0f98
 * Name: LightningFeature::PostLoad
 * Namespace: LightningFeature
 * Signature: void PostLoad(LightningFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LightningFeature::PostLoad(LightningFeature *this)

{
  int iVar1;
  BoltEmitter **ppBVar2;
  int iVar3;
  BoltEmitter *pBVar4;
  BOLT_SET *pBVar5;
  
  pBVar5 = &BoltSet;
  for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pBVar5->bolts = 0;
    pBVar5 = (BOLT_SET *)&pBVar5->color;
  }
  BoltSet.bolts = GetINIInt("LightningBolt","Bolts",0,missionName);
  BoltSet.color = GetINIInt("LightningBolt","Color",DisplayInterface::colorWhite,missionName);
  iVar3 = GetINIInt("LightningBolt","minDelay",5000,missionName);
  BoltSet.minDelay = (float)iVar3 * 0.001;
  iVar3 = GetINIInt("LightningBolt","maxDelay",10000,missionName);
  BoltSet.maxDelay = (float)iVar3 * 0.001;
  iVar3 = GetINIInt("LightningBolt","Duration",200,missionName);
  BoltSet.duration = (float)iVar3 * 0.001;
  iVar1 = GetINIInt("LightningBolt","Distance",100,missionName);
  iVar3 = 0x10;
  BoltSet.distance = (float)iVar1;
  GetINIString("LightningBolt","Sound","",BoltSet.sound,0x10,missionName);
  if (0x10 < BoltSet.bolts) {
    BoltSet.bolts = 0x10;
  }
  ppBVar2 = this->activeList;
  pBVar4 = this->emitterList;
  do {
    *ppBVar2 = pBVar4;
    ppBVar2 = ppBVar2 + 1;
    pBVar4 = pBVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  this->activeNum = 0;
  iVar3 = 0;
  if (0 < BoltSet.bolts) {
    do {
      AddBoltEmitter(this,(_OBJ76 *)0x0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < BoltSet.bolts);
  }
  return;
}
