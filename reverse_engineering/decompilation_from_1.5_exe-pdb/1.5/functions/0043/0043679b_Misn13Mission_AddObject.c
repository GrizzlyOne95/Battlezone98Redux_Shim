/*
 * Entry: 0043679b
 * Name: Misn13Mission::AddObject
 * Namespace: Misn13Mission
 * Signature: void AddObject(Misn13Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn13Mission::AddObject(Misn13Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0xac)._s_0.sv1 == 0) && (bVar1 = IsOdf(param_1,"svapc13"), bVar1)) {
    (this->field18_0xac)._s_0.sv1 = param_1;
    return;
  }
  piVar2 = &(this->field18_0xac)._s_0.sv2;
  if ((((*piVar2 != 0) || (bVar1 = IsOdf(param_1,"svapc13"), !bVar1)) &&
      ((piVar2 = &(this->field18_0xac)._s_0.sv3, *piVar2 != 0 ||
       (bVar1 = IsOdf(param_1,"svhr13"), !bVar1)))) &&
     ((piVar2 = &(this->field18_0xac)._s_0.sv4, *piVar2 != 0 ||
      (bVar1 = IsOdf(param_1,"svhr13"), !bVar1)))) {
    bVar1 = IsOdf(param_1,"abtowe");
    if (bVar1) {
      (this->field18_0xac)._s_0.guntower1 = param_1;
      return;
    }
    piVar2 = &(this->field18_0xac)._s_0.controltower;
    if (((((((*piVar2 != 0) || (bVar1 = IsOdf(param_1,"abcomm"), !bVar1)) &&
           ((piVar2 = &(this->field18_0xac)._s_0.tank5, *piVar2 != 0 ||
            (bVar1 = IsOdf(param_1,"svtk13"), !bVar1)))) &&
          (((piVar2 = &(this->field18_0xac)._s_0.tank6, *piVar2 != 0 ||
            (bVar1 = IsOdf(param_1,"svtk13"), !bVar1)) &&
           ((piVar2 = &(this->field18_0xac)._s_0.tank7, *piVar2 != 0 ||
            (bVar1 = IsOdf(param_1,"svtk13"), !bVar1)))))) &&
         (((piVar2 = &(this->field18_0xac)._s_0.tank8, *piVar2 != 0 ||
           (bVar1 = IsOdf(param_1,"svtk13"), !bVar1)) &&
          ((piVar2 = &(this->field18_0xac)._s_0.nsdfmuf, *piVar2 != 0 ||
           (bVar1 = IsOdf(param_1,"avmuf"), !bVar1)))))) &&
        (((piVar2 = &(this->field18_0xac)._s_0.nsdfrig, *piVar2 != 0 ||
          (bVar1 = IsOdf(param_1,"avcnst"), !bVar1)) &&
         ((piVar2 = &(this->field18_0xac)._s_0.avscav1, *piVar2 != 0 ||
          (bVar1 = IsOdf(param_1,"avscav"), !bVar1)))))) &&
       ((piVar2 = &(this->field18_0xac)._s_0.avscav2, *piVar2 != 0 ||
        (bVar1 = IsOdf(param_1,"avscav"), !bVar1)))) {
      piVar2 = &(this->field18_0xac)._s_0.avscav3;
      if (*piVar2 != 0) {
        return;
      }
      bVar1 = IsOdf(param_1,"avscav");
      if (!bVar1) {
        return;
      }
      *piVar2 = param_1;
      return;
    }
  }
  *piVar2 = param_1;
  return;
}
