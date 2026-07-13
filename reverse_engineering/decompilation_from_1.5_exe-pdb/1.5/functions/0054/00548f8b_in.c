/*
 * Entry: 00548f8b
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, EULER * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,EULER *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  
  if (!binarySave) {
    in_prep();
    iVar3 = sscanf(inCurrent,"%*s =");
    pcVar1 = nextLine;
    *nextLine = '\r';
    inCurrent = pcVar1 + 2;
    if (iVar3 != 0) {
      return false;
    }
  }
  bVar2 = in(param_1,&param_2->mass,4);
  if ((((((bVar2) && (bVar2 = in(param_1,&param_2->mass_inv,4), bVar2)) &&
        (bVar2 = in(param_1,&param_2->v_mag,4), bVar2)) &&
       ((bVar2 = in(param_1,&param_2->v_mag_inv,4), bVar2 &&
        (bVar2 = in(param_1,&param_2->I,4), bVar2)))) &&
      ((bVar2 = in(param_1,&param_2->k_i,4), bVar2 &&
       ((bVar2 = in(param_1,&param_2->v,0xc), bVar2 &&
        (bVar2 = in(param_1,&param_2->omega,0xc), bVar2)))))) &&
     (bVar2 = in(param_1,&param_2->Accel,0xc), bVar2)) {
    return true;
  }
  return false;
}
