/*
 * Entry: 004587c1
 * Name: Range_Search_Results::Reset_Results
 * Namespace: Range_Search_Results
 * Signature: void Reset_Results(Range_Search_Results * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Range_Search_Results::Reset_Results(Range_Search_Results *this)

{
  if (this->empty == false) {
    this->x = this->x0;
    this->z = this->z0;
    this->curObject = this->firstObject[this->width * this->z0 + this->x0];
  }
  return;
}
