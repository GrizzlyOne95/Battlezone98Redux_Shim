/*
 * Entry: 00514021
 * Name: Mapgrid_Goal::Clear_Goal
 * Namespace: Mapgrid_Goal
 * Signature: void Clear_Goal(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Mapgrid_Goal::Clear_Goal(Mapgrid_Goal *this)

{
  this->enemy_buildings = 0.0;
  this->threat = 0;
  this->our_buildings = 0.0;
  this->new_threat = 0;
  this->last_rapid_base_defense_time = 0.0;
  this->enemy_units = 0;
  this->ground_units_strength = 0;
  this->our_units = 0;
  this->resources = 0;
  this->scripted_value = 0;
  this->min_scripted_force = 0;
  this->max_scripted_force = 0;
  this->rapid_defense_state = 0;
  this->neighbor_flags = '\0';
  this->an_enemy_handle = 0;
  return;
}
