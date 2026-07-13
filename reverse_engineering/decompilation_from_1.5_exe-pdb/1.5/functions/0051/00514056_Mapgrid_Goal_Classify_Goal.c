/*
 * Entry: 00514056
 * Name: Mapgrid_Goal::Classify_Goal
 * Namespace: Mapgrid_Goal
 * Signature: void Classify_Goal(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mapgrid_Goal::Classify_Goal(Mapgrid_Goal *this)

{
  tag_team *ptVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  ptVar1 = this->the_team;
  iVar2 = this->row;
  iVar3 = this->column;
  iVar4 = (ptVar1->strategic_targets).scouted[iVar2][iVar3];
  if (iVar4 == 0) {
    if ((ptVar1->strategic_targets).distance_from_scouted[iVar2][iVar3] < 2) {
      this->_padding_ = 4;
      return;
    }
  }
  else {
    bVar5 = (ptVar1->strategic_targets).distance_from_base[iVar2][iVar3] == 1;
    iVar2 = this->threat;
    if (((((iVar2 != 0) || (this->our_buildings != 0.0)) || (this->enemy_buildings != 0.0)) ||
        ((this->resources != 0 || (iVar4 != 1)))) || ((this->scripted_value != 0 || (bVar5)))) {
      if (0.0 < this->enemy_buildings) {
        this->_padding_ = 3;
        return;
      }
      if ((iVar2 == 0) && (0.0 < this->our_buildings)) {
        this->_padding_ = 1;
        return;
      }
      if (0 < iVar2) {
        this->_padding_ = 2;
        return;
      }
      if (0 < this->resources) {
        this->_padding_ = 8;
        return;
      }
      if (0 < this->scripted_value) {
        this->_padding_ = 5;
        return;
      }
      if (bVar5) {
        this->_padding_ = 6;
        return;
      }
      if (iVar4 == 2) {
        this->_padding_ = 7;
        return;
      }
    }
  }
  this->_padding_ = 0;
  return;
}
