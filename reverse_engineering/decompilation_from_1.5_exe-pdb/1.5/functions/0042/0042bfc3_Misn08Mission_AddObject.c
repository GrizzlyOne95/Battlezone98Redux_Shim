/*
 * Entry: 0042bfc3
 * Name: Misn08Mission::AddObject
 * Namespace: Misn08Mission
 * Signature: void AddObject(Misn08Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn08Mission::AddObject(Misn08Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0xf8)._s_0.nsdfmuf == 0) && (bVar1 = IsOdf(param_1,"avmu8"), bVar1)) {
    (this->field18_0xf8)._s_0.nsdfmuf = param_1;
  }
  else {
    piVar2 = &(this->field18_0xf8)._s_0.ccaapc;
    if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"svapc"), bVar1)) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0xf8)._s_0.guntower1;
      if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) {
        *piVar2 = param_1;
      }
      else {
        piVar2 = &(this->field18_0xf8)._s_0.guntower2;
        if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) {
          *piVar2 = param_1;
        }
      }
    }
  }
  return;
}
