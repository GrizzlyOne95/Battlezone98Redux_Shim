/*
 * Entry: 0054801d
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, MAT_3D * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,MAT_3D *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  uint uVar2;
  float *pfVar3;
  void *unaff_EDI;
  int local_8;
  
  if (binarySave) {
    bVar1 = out_data(param_1,0xb,(long)param_2,unaff_EDI);
  }
  else {
    uVar2 = param_3 >> 6;
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,uVar2);
    local_8 = 0;
    if (uVar2 != 0) {
      pfVar3 = &param_2->right_z;
      do {
        bVar1 = out(param_1,(float *)(pfVar3 + -2),4,"  right_x");
        if (((((!bVar1) || (bVar1 = out(param_1,pfVar3 + -1,4,"  right_y"), !bVar1)) ||
             (bVar1 = out(param_1,pfVar3,4,"  right_z"), !bVar1)) ||
            ((((bVar1 = out(param_1,pfVar3 + 1,4,"  up_x"), !bVar1 ||
               (bVar1 = out(param_1,pfVar3 + 2,4,"  up_y"), !bVar1)) ||
              ((bVar1 = out(param_1,pfVar3 + 3,4,"  up_z"), !bVar1 ||
               ((bVar1 = out(param_1,pfVar3 + 4,4,"  front_x"), !bVar1 ||
                (bVar1 = out(param_1,pfVar3 + 5,4,"  front_y"), !bVar1)))))) ||
             (bVar1 = out(param_1,pfVar3 + 6,4,"  front_z"), !bVar1)))) ||
           (((bVar1 = out(param_1,(double *)(pfVar3 + 8),8,"  posit_x"), !bVar1 ||
             (bVar1 = out(param_1,(double *)(pfVar3 + 10),8,"  posit_y"), !bVar1)) ||
            (bVar1 = out(param_1,(double *)(pfVar3 + 0xc),8,"  posit_z"), !bVar1)))) {
          return false;
        }
        local_8 = local_8 + 1;
        pfVar3 = pfVar3 + 0x10;
      } while (local_8 < (int)uVar2);
    }
    bVar1 = true;
  }
  return bVar1;
}
