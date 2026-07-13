/*
 * Entry: 0040bdbe
 * Name: APCProcess::InitReload
 * Namespace: APCProcess
 * Signature: void InitReload(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::InitReload(APCProcess *this)

{
  Team *this_00;
  AiPath *pAVar1;
  char cVar2;
  int iVar3;
  GameObject *this_01;
  GameObject *pGVar4;
  AiPath *this_02;
  GoNearAndSit *pGVar5;
  float fVar6;
  float local_14;
  int local_10;
  AiPath *local_8;
  
  iVar3 = (*(code *)**(undefined4 **)(*(int *)&this->field_0x2c + 0x20))();
  if (*(int *)(iVar3 + 0x20) == 0x41504300) {
    this_00 = *(Team **)(*(int *)&this->field_0x2c + 0x170);
    this_01 = Team::GetSlot(this_00,1);
    local_8 = (AiPath *)0x0;
    local_14 = 1e+30;
    if ((this_01 != (GameObject *)0x0) &&
       (cVar2 = (**(code **)(this_01->_padding_ + 100))(), cVar2 != '\0')) {
      local_8 = FindPlan(*(GameObject **)&this->field_0x2c,this_01);
      local_14 = AiPath::GetLength(local_8);
    }
    local_10 = 0x4b;
    do {
      pGVar4 = Team::GetSlot(this_00,local_10);
      pAVar1 = local_8;
      if (pGVar4 != (GameObject *)0x0) {
        this_02 = FindPlan(*(GameObject **)&this->field_0x2c,pGVar4);
        fVar6 = AiPath::GetLength(this_02);
        if (local_14 <= fVar6) {
          if (this_02 != (AiPath *)0x0) {
            AiPath::~AiPath(this_02);
            operator_delete(this_02);
          }
        }
        else {
          this_01 = pGVar4;
          local_14 = fVar6;
          pAVar1 = this_02;
          if (local_8 != (AiPath *)0x0) {
            AiPath::~AiPath(local_8);
            operator_delete(local_8);
          }
        }
      }
      local_8 = pAVar1;
      local_10 = local_10 + 1;
    } while (local_10 < 0x50);
    iVar3 = *(int *)(*(int *)&this->field_0x2c + 0x228);
    *(undefined4 *)(iVar3 + 0xd0) = 0;
    *(undefined4 *)(iVar3 + 0xd4) = 0;
    *(undefined4 *)(iVar3 + 0xc4) = 0;
    *(undefined4 *)(iVar3 + 200) = 0;
    if (this_01 == (GameObject *)0x0) {
      *(undefined4 *)&this->field_0x1c = 3;
    }
    else {
      iVar3 = GameObject::GetHandle(this_01);
      *(int *)&this->field_0x34 = iVar3;
      iVar3 = (*(code *)**(undefined4 **)(*(int *)&this->field_0x2c + 0x20))();
      fVar6 = *(float *)(iVar3 + 0x3d4);
      pGVar5 = operator_new(0x160);
      if (pGVar5 == (GoNearAndSit *)0x0) {
        pGVar5 = (GoNearAndSit *)0x0;
      }
      else {
        pGVar5 = GoNearAndSit::GoNearAndSit
                           (pGVar5,*(Craft **)&this->field_0x2c,this_01,local_8,fVar6 - 5.0);
      }
      *(GoNearAndSit **)&this->field_0x30 = pGVar5;
    }
  }
  else {
    *(undefined4 *)&this->field_0x1c = 3;
  }
  return;
}
