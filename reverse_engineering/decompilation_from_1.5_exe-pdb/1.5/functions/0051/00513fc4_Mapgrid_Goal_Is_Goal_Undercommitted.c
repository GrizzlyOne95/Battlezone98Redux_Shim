/*
 * Entry: 00513fc4
 * Name: Mapgrid_Goal::Is_Goal_Undercommitted
 * Namespace: Mapgrid_Goal
 * Signature: int Is_Goal_Undercommitted(Mapgrid_Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Mapgrid_Goal::Is_Goal_Undercommitted(Mapgrid_Goal *this)

{
  int iVar1;
  float fVar2;
  
  iVar1 = Goal::Is_Goal_Undercommitted((Goal *)this);
  if (iVar1 == 0) {
    this->start_undercommitted_time = -1.0;
  }
  else {
    if (this->_padding_ != 3) {
      return iVar1;
    }
    if (this->start_undercommitted_time == -1.0) {
      fVar2 = Get_Time();
      this->start_undercommitted_time = fVar2;
    }
    fVar2 = Get_Time();
    if (180.0 <= fVar2 - this->start_undercommitted_time) {
      return 1;
    }
  }
  return 0;
}
