/*
 * Entry: 0054822a
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, EULER * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,EULER *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  int iVar2;
  
  if ((((((binarySave) || (iVar2 = fprintf((FILE *)param_1,"%s =\r\n",param_4), -1 < iVar2)) &&
        (bVar1 = out(param_1,&param_2->mass,4," mass"), bVar1)) &&
       ((bVar1 = out(param_1,&param_2->mass_inv,4," mass_inv"), bVar1 &&
        (bVar1 = out(param_1,&param_2->v_mag,4," v_mag"), bVar1)))) &&
      ((bVar1 = out(param_1,&param_2->v_mag_inv,4," v_mag_inv"), bVar1 &&
       ((bVar1 = out(param_1,&param_2->I,4," I"), bVar1 &&
        (bVar1 = out(param_1,&param_2->k_i,4," k_i"), bVar1)))))) &&
     ((bVar1 = out(param_1,&param_2->v,0xc," v"), bVar1 &&
      ((bVar1 = out(param_1,&param_2->omega,0xc," omega"), bVar1 &&
       (bVar1 = out(param_1,&param_2->Accel,0xc," Accel"), bVar1)))))) {
    return true;
  }
  return false;
}
