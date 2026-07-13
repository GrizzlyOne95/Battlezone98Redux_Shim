/*
 * Entry: 004589e0
 * Name: Range::Insert
 * Namespace: Range
 * Signature: void Insert(Range * this, int param_1, double param_2, double param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Range::Insert(Range *this,int param_1,double param_2,double param_3)

{
  double dVar1;
  int iVar2;
  int *piVar3;
  data_handle_info *pdVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_EDI;
  int in_stack_00000008;
  
  dVar1 = (double)CONCAT44(param_2._0_4_,in_stack_00000008) - this->left;
  in_stack_00000008 = SUB84(dVar1,0);
  param_2._0_4_ = (undefined4)((ulonglong)dVar1 >> 0x20);
  dVar1 = this->top;
  Set_Rounding(unaff_EDI);
  in_stack_00000008 =
       SUB84(this->horizontal_resolution * (double)CONCAT44(param_2._0_4_,in_stack_00000008) +
             Float2Int,0);
  iVar6 = Clamp(in_stack_00000008,0,this->width + -1);
  in_stack_00000008 =
       SUB84(this->vertical_resolution * ((double)CONCAT44(param_3._0_4_,param_2._4_4_) - dVar1) +
             Float2Int,0);
  iVar7 = Clamp(in_stack_00000008,0,this->height + -1);
  Set_Rounding(unaff_EDI);
  iVar2 = this->width;
  piVar3 = this->firstObject;
  pdVar4 = this->objects;
  iVar5 = this->objectCount;
  pdVar4[iVar5].handle = param_1;
  pdVar4[iVar5].next = piVar3[iVar2 * iVar7 + iVar6];
  piVar3[iVar2 * iVar7 + iVar6] = this->objectCount;
  this->objectCount = this->objectCount + 1;
  return;
}
