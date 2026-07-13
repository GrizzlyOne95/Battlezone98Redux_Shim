/*
 * Entry: 00514270
 * Name: Mapgrid_Goal::Distance_From_Squad_To_Goal
 * Namespace: Mapgrid_Goal
 * Signature: double Distance_From_Squad_To_Goal(Mapgrid_Goal * this, tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __thiscall Mapgrid_Goal::Distance_From_Squad_To_Goal(Mapgrid_Goal *this,tag_squad *param_1)

{
  double dVar1;
  
  dVar1 = Schedule_Distance_From_Squad_To_Goal(this->the_map,param_1,this);
  return dVar1;
}
