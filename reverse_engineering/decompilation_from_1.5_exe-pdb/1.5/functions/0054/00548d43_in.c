/*
 * Entry: 00548d43
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, MAT_3D * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,MAT_3D *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  void *unaff_EBX;
  float *pfVar3;
  int local_c;
  int local_8;
  
  if (binarySave) {
    bVar2 = in_data(0xb,(long)param_2,unaff_EBX);
  }
  else {
    in_prep();
    sscanf(inCurrent,"%*s [%d] =",&local_c);
    pcVar1 = nextLine;
    *nextLine = '\r';
    inCurrent = pcVar1 + 2;
    local_8 = 0;
    if (0 < local_c) {
      pfVar3 = &param_2->right_z;
      do {
        bVar2 = in(param_1,(float *)(pfVar3 + -2),4);
        if (((((!bVar2) || (bVar2 = in(param_1,pfVar3 + -1,4), !bVar2)) ||
             (bVar2 = in(param_1,pfVar3,4), !bVar2)) ||
            ((((bVar2 = in(param_1,pfVar3 + 1,4), !bVar2 ||
               (bVar2 = in(param_1,pfVar3 + 2,4), !bVar2)) ||
              ((bVar2 = in(param_1,pfVar3 + 3,4), !bVar2 ||
               ((bVar2 = in(param_1,pfVar3 + 4,4), !bVar2 ||
                (bVar2 = in(param_1,pfVar3 + 5,4), !bVar2)))))) ||
             (bVar2 = in(param_1,pfVar3 + 6,4), !bVar2)))) ||
           (((bVar2 = in(param_1,(double *)(pfVar3 + 8),8), !bVar2 ||
             (bVar2 = in(param_1,(double *)(pfVar3 + 10),8), !bVar2)) ||
            (bVar2 = in(param_1,(double *)(pfVar3 + 0xc),8), !bVar2)))) {
          return false;
        }
        local_8 = local_8 + 1;
        pfVar3 = pfVar3 + 0x10;
      } while (local_8 < local_c);
    }
    bVar2 = true;
  }
  return bVar2;
}
