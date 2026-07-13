/*
 * Entry: 005144a3
 * Name: Mapgrid_Goal::Compute_Matching_Value
 * Namespace: Mapgrid_Goal
 * Signature: float Compute_Matching_Value(Mapgrid_Goal * this, tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall Mapgrid_Goal::Compute_Matching_Value(Mapgrid_Goal *this,tag_squad *param_1)

{
  tagAIP_struct *ptVar1;
  tag_team *ptVar2;
  float10 fVar3;
  
  if ((((this->enemy_units == 0) && (this->our_buildings == 0.0)) && (this->resources == 0)) &&
     ((this->enemy_buildings == 0.0 && (this->scripted_value == 0)))) {
    if (((this->the_team->strategic_targets).distance_from_base[this->row][this->column] != 1) &&
       ((this->the_team->strategic_targets).scouted[this->row][this->column] == 1)) {
      fVar3 = (float10)-1e+09;
      goto LAB_00514639;
    }
  }
  fVar3 = (float10)(**(code **)(this->_padding_ + 0x10))(param_1);
  if ((this->the_map->ai_omniscient == 0) &&
     ((this->the_team->strategic_targets).scouted[this->row][this->column] == 0)) {
    ptVar1 = this->the_team->AIP;
    fVar3 = (fVar3 * (float10)ptVar1->distance_priority -
            (float10)(int)((uint)((Mapgrid_Goal *)param_1->my_strategic_goal != this) *
                           (uint)((Mapgrid_Goal *)param_1->my_strategic_goal != (Mapgrid_Goal *)0x0)
                          * ptVar1->persistence_priority)) + (float10)ptVar1->exploration_priority;
  }
  else {
    ptVar2 = this->the_team;
    ptVar1 = ptVar2->AIP;
    fVar3 = (float10)(ptVar1->scripted_priority * this->scripted_value) +
            (float10)(ptVar1->threat_priority * this->threat) +
            (float10)(ptVar1->resource_priority * this->resources) +
            (float10)ptVar1->attack_enemy_base_priority * (float10)this->enemy_buildings +
            (float10)ptVar1->defend_buildings_priority * (float10)this->our_buildings +
            (((float10)(int)((uint)((ptVar2->strategic_targets).distance_from_base[this->row]
                                    [this->column] == 1) * ptVar1->perimeter_priority) +
             (float10)(int)((uint)((ptVar2->strategic_targets).scouted[this->row][this->column] == 2
                                  ) * ptVar1->exploration_priority)) -
            (float10)(int)((uint)((Mapgrid_Goal *)param_1->my_strategic_goal != this) *
                           (uint)((Mapgrid_Goal *)param_1->my_strategic_goal != (Mapgrid_Goal *)0x0)
                          * ptVar1->persistence_priority)) +
            (float10)ptVar1->distance_priority * fVar3;
  }
  if ((float10)(float)this->_padding_ < fVar3) {
    this->_padding_ = (int)(float)fVar3;
  }
LAB_00514639:
  return (float)fVar3;
}
