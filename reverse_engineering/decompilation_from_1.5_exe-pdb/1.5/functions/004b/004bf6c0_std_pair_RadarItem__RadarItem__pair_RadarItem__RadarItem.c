/*
 * Entry: 004bf6c0
 * Name: std::pair<RadarItem_*,RadarItem_*>::pair<RadarItem_*,RadarItem_*>
 * Namespace: std::pair<RadarItem_*,RadarItem_*>
 * Signature: pair<RadarItem_*,RadarItem_*> * pair<RadarItem_*,RadarItem_*>(pair<RadarItem_*,RadarItem_*> * this, RadarItem * * param_1, RadarItem * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<RadarItem_*,RadarItem_*> * __thiscall
std::pair<RadarItem_*,RadarItem_*>::pair<RadarItem_*,RadarItem_*>
          (pair<RadarItem_*,RadarItem_*> *this,RadarItem **param_1,RadarItem **param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
