/*
 * Entry: 00514640
 * Name: Mapgrid_Goal::Compute_Raw_Priority
 * Namespace: Mapgrid_Goal
 * Signature: float Compute_Raw_Priority(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Mapgrid_Goal::Compute_Raw_Priority(Mapgrid_Goal *this)

{
  tag_team *ptVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  tagAIP_struct *ptVar5;
  float fVar6;
  
  ptVar1 = this->the_team;
  iVar2 = this->row;
  iVar3 = this->column;
  iVar4 = (ptVar1->strategic_targets).distance_from_base[iVar2][iVar3];
  fVar6 = (float)iVar4;
  if (((((this->enemy_units == 0) && (this->our_buildings == 0.0)) && (this->resources == 0)) &&
      ((this->enemy_buildings == 0.0 && (this->scripted_value == 0)))) &&
     ((fVar6 != 1.0 && ((ptVar1->strategic_targets).scouted[iVar2][iVar3] == 1)))) {
    this->_padding_ = 0;
    fVar6 = -1e+09;
  }
  else if ((this->the_map->ai_omniscient == 0) &&
          ((ptVar1->strategic_targets).scouted[iVar2][iVar3] == 0)) {
    fVar6 = fVar6 * (float)ptVar1->AIP->distance_priority + (float)ptVar1->AIP->exploration_priority
    ;
  }
  else {
    ptVar5 = ptVar1->AIP;
    fVar6 = (float)(ptVar5->threat_priority * this->threat) +
            (float)(ptVar5->resource_priority * this->resources) +
            (float)(ptVar5->scripted_priority * this->scripted_value) +
            (float)(int)((uint)(iVar4 == 1) * ptVar5->perimeter_priority) +
            (float)ptVar5->attack_enemy_base_priority * this->enemy_buildings +
            (float)ptVar5->defend_buildings_priority * this->our_buildings +
            (float)(int)((uint)(this->_padding_ != 0) * ptVar5->persistence_priority) +
            (float)(int)((uint)((ptVar1->strategic_targets).scouted[iVar2][iVar3] == 2) *
                        ptVar5->exploration_priority) + (float)ptVar5->distance_priority * fVar6;
  }
  this->_padding_ = (int)fVar6;
  return fVar6;
}
