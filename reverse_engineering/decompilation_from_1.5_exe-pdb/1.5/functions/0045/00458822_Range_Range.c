/*
 * Entry: 00458822
 * Name: Range::Range
 * Namespace: Range
 * Signature: Range * Range(Range * this, double param_1, double param_2, double param_3, double param_4, double param_5, double param_6, int param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Range * __thiscall
Range::Range(Range *this,double param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,int param_7)

{
  longlong lVar1;
  data_handle_info *pdVar2;
  int *piVar3;
  int unaff_ESI;
  
  this->horizontal_resolution = 1.0 / param_1;
  this->vertical_resolution = 1.0 / param_2;
  this->left = param_5;
  this->top = param_3;
  Set_Rounding(unaff_ESI);
  param_5._0_4_ = SUB84((param_6 - param_5) * this->horizontal_resolution + Float2Int,0);
  this->width = param_5._0_4_ + 1;
  param_5._0_4_ = SUB84((param_4 - param_3) * this->vertical_resolution + Float2Int,0);
  this->height = param_5._0_4_ + 1;
  Set_Rounding(unaff_ESI);
  this->max_objects = param_7;
  pdVar2 = operator_new__(-(uint)((int)((ulonglong)(uint)param_7 * 8 >> 0x20) != 0) |
                          (uint)((ulonglong)(uint)param_7 * 8));
  this->objects = pdVar2;
  lVar1 = (ulonglong)(uint)(this->height * this->width) * 4;
  piVar3 = operator_new__(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
  this->firstObject = piVar3;
  Clear(this);
  return this;
}
