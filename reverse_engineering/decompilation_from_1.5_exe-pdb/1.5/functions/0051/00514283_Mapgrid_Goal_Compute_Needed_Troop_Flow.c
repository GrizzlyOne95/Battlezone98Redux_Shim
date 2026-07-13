/*
 * Entry: 00514283
 * Name: Mapgrid_Goal::Compute_Needed_Troop_Flow
 * Namespace: Mapgrid_Goal
 * Signature: void Compute_Needed_Troop_Flow(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mapgrid_Goal::Compute_Needed_Troop_Flow(Mapgrid_Goal *this)

{
  int iVar1;
  int iVar2;
  tag_team *ptVar3;
  int iVar4;
  tagAIP_struct *ptVar5;
  int iVar6;
  int extraout_EAX;
  int extraout_EAX_00;
  uint uVar7;
  float10 extraout_ST0;
  float10 extraout_ST1;
  uint local_18;
  uint local_14;
  int local_10;
  
  this->_padding_ = 0;
  this->_padding_ = 0;
  iVar1 = this->row;
  iVar2 = this->column;
  ptVar3 = this->the_team;
  uVar7 = (uint)((ptVar3->strategic_targets).distance_from_base[iVar1][iVar2] == 1);
  if (((((this->enemy_units != 0) || (this->resources != 0)) || (this->our_buildings != 0.0)) ||
      ((this->enemy_buildings != 0.0 || (this->min_scripted_force != 0)))) ||
     ((uVar7 != 0 ||
      ((this->scripted_value != 0 || ((ptVar3->strategic_targets).scouted[iVar1][iVar2] != 1)))))) {
    local_10 = this->min_scripted_force;
    if (99 < local_10) {
      local_10 = local_10 + -100;
    }
    iVar4 = this->resources;
    _ftol2_sse();
    this->_padding_ = extraout_EAX;
    local_14 = (uint)(extraout_ST1 < (float10)this->our_buildings);
    local_18 = (uint)(extraout_ST1 < (float10)this->enemy_buildings);
    ptVar5 = ptVar3->AIP;
    iVar6 = ptVar3->AIP->min_building_defense_force;
    ceil((double)((float10)(int)(iVar6 * local_14) +
                  (float10)(int)(iVar6 * local_18) +
                  (float10)(int)(ptVar5->min_resource_force * (uint)(0 < iVar4)) +
                  (float10)(int)(ptVar5->min_perimeter_force * uVar7) +
                  (float10)(int)((uint)((ptVar3->strategic_targets).scouted[iVar1][iVar2] == 2) *
                                ptVar5->min_exploration_force) +
                  (float10)ptVar3->AIP->min_matching_force_ratio * extraout_ST0 + (float10)local_10)
        );
    _ftol2_sse();
    this->_padding_ = extraout_EAX_00;
    if (this->_padding_ == 4) {
      this->_padding_ = this->the_team->AIP->min_exploration_force;
      this->_padding_ = this->the_team->AIP->max_exploration_force;
    }
  }
  return;
}
