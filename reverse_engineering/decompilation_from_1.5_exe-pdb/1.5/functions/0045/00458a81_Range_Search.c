/*
 * Entry: 00458a81
 * Name: Range::Search
 * Namespace: Range
 * Signature: void Search(Range * this, double param_1, double param_2, double param_3, Range_Search_Results * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
Range::Search(Range *this,double param_1,double param_2,double param_3,Range_Search_Results *param_4
             )

{
  Search(this,param_1 - param_3,param_2 - param_3,param_1 + param_3,param_2 + param_3,param_4);
  return;
}
