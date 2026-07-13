/*
 * Entry: 004588d0
 * Name: Range::Search
 * Namespace: Range
 * Signature: void Search(Range * this, double param_1, double param_2, double param_3, double param_4, Range_Search_Results * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
Range::Search(Range *this,double param_1,double param_2,double param_3,double param_4,
             Range_Search_Results *param_5)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  int unaff_EDI;
  
  dVar1 = this->left;
  dVar2 = this->top;
  dVar3 = this->left;
  dVar4 = this->top;
  param_5->empty = false;
  param_5->width = this->width;
  param_5->objects = this->objects;
  param_5->firstObject = this->firstObject;
  Set_Rounding(unaff_EDI);
  param_2._0_4_ = SUB84(this->vertical_resolution * ((param_2 - dVar2) - 20.0) + Float2Int,0);
  param_5->z0 = param_2._0_4_;
  if (param_2._0_4_ < 0) {
    param_5->z0 = 0;
  }
  if (this->height <= param_5->z0) {
    param_5->empty = true;
  }
  param_2._0_4_ = SUB84(this->vertical_resolution * ((param_4 - dVar4) + 20.0) + Float2Int,0);
  param_5->z1 = param_2._0_4_;
  if (this->height <= param_2._0_4_) {
    param_5->z1 = this->height + -1;
  }
  if (param_5->z1 < 0) {
    param_5->empty = true;
  }
  param_2._0_4_ = SUB84(this->horizontal_resolution * ((param_1 - dVar1) - 20.0) + Float2Int,0);
  param_5->x0 = param_2._0_4_;
  if (param_2._0_4_ < 0) {
    param_5->x0 = 0;
  }
  if (this->width <= param_5->x0) {
    param_5->empty = true;
  }
  param_2._0_4_ = SUB84(this->horizontal_resolution * ((param_3 - dVar3) + 20.0) + Float2Int,0);
  param_5->x1 = param_2._0_4_;
  if (this->width <= param_2._0_4_) {
    param_5->x1 = this->width + -1;
  }
  if (param_5->x1 < 0) {
    param_5->empty = true;
  }
  Set_Rounding(unaff_EDI);
  Range_Search_Results::Reset_Results(param_5);
  return;
}
