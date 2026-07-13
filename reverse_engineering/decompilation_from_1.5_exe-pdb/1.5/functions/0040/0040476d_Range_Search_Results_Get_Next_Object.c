/*
 * Entry: 0040476d
 * Name: Range_Search_Results::Get_Next_Object
 * Namespace: Range_Search_Results
 * Signature: bool Get_Next_Object(Range_Search_Results * this, int * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Range_Search_Results::Get_Next_Object(Range_Search_Results *this,int **param_1)

{
  int iVar1;
  data_handle_info *pdVar2;
  bool bVar3;
  
  if (this->empty == false) {
    if (this->curObject == -1) {
      do {
        this->x = this->x + 1;
        if (this->x1 < this->x) {
          this->z = this->z + 1;
          this->x = this->x0;
          if (this->z1 < this->z) {
            return false;
          }
        }
        iVar1 = this->firstObject[this->width * this->z + this->x];
        this->curObject = iVar1;
      } while (iVar1 == -1);
    }
    iVar1 = this->curObject;
    pdVar2 = this->objects;
    *param_1 = &pdVar2[iVar1].handle;
    this->curObject = pdVar2[iVar1].next;
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}
