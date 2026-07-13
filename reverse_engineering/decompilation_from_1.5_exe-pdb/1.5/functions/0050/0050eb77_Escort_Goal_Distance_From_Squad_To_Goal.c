/*
 * Entry: 0050eb77
 * Name: Escort_Goal::Distance_From_Squad_To_Goal
 * Namespace: Escort_Goal
 * Signature: double Distance_From_Squad_To_Goal(Escort_Goal * this, tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __thiscall Escort_Goal::Distance_From_Squad_To_Goal(Escort_Goal *this,tag_squad *param_1)

{
  double dVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  int iVar4;
  Escort_Goal *local_c;
  Escort_Goal *local_8;
  
  if (this->_padding_ == 0) {
    local_c = this;
    local_8 = this;
    pVVar2 = (VECTOR_3D *)(**(code **)(this->damsel_in_distress->_padding_ + 0xc))();
    ScheduleGlue_Translate_Pos_To_Tiles(*pVVar2,(int *)&local_8,(int *)&local_c);
    iVar4 = param_1->y - (int)local_c;
    iVar3 = param_1->x - (int)local_8;
    dVar1 = SQRT((double)(iVar4 * iVar4 + iVar3 * iVar3)) * 10.0;
  }
  else {
    dVar1 = 100000000.0;
  }
  return dVar1;
}
