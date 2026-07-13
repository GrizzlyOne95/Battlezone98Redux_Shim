/*
 * Entry: 004d93c7
 * Name: Reticle::Render
 * Namespace: Reticle
 * Signature: void Render(Reticle * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Reticle::Render(Reticle *this)

{
  float fVar1;
  int iVar2;
  MAT_3D *pMVar3;
  int iVar4;
  MAT_3D *pMVar5;
  float *pfVar6;
  MAT_3D local_11c;
  MAT_3D local_dc;
  MAT_3D local_9c;
  float local_5c [6];
  float local_44;
  float local_40;
  float local_3c;
  double local_34;
  double local_2c;
  double local_24;
  double local_1c;
  double local_14;
  undefined8 local_c;
  
  if (((((View_Record.Current_View == COCKPIT_VIEW) || (View_Record.Current_View == BINOCULAR_VIEW))
       || (View_Record.Current_View == FIX_EXTERN_VIEW)) || (View_Record.Current_View == CHASE_VIEW)
      ) && (View_Record.Intenal_View != 0)) {
    pMVar3 = Matrix_Multiply(&local_9c,&this->sightMat,&View_Record.MainCam.Matrix);
    pfVar6 = local_5c;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar6 = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pfVar6 = pfVar6 + 1;
    }
    fVar1 = local_3c * 12.0 + (float)local_24;
    if (0.0001 < fVar1) {
      fVar1 = 1.0 / fVar1;
      local_c = (double)(View_Record.MainCam.Const_x * fVar1 * (local_44 * 12.0 + (float)local_34) +
                         View_Record.MainCam.Orig_x + (float)Float2Int);
      local_14 = (double)(fVar1 * View_Record.MainCam.Const_y * (local_40 * 12.0 + (float)local_2c)
                          + View_Record.MainCam.Orig_y + (float)Float2Int);
      DrawSprite(View_Record.MainCam.Buffer,this->reticleIndex,(int)local_c,local_14._0_4_,0x250004)
      ;
    }
    if (this->ladderIndex != 0) {
      pMVar3 = Matrix_Multiply(&local_9c,&this->horizMat,&View_Record.MainCam.Matrix);
      pMVar5 = &local_dc;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        pMVar5->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
      }
      local_c._4_4_ = -0x1e;
      do {
        pMVar3 = Build_Pitch_Matrix(&local_11c,(float)local_c._4_4_ * 0.017453292);
        pMVar5 = &local_9c;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          pMVar5->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar5 = (MAT_3D *)&pMVar5->right_y;
        }
        pMVar3 = Matrix_Multiply(&local_11c,&local_9c,&local_dc);
        pfVar6 = local_5c;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar6 = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pfVar6 = pfVar6 + 1;
        }
        fVar1 = local_3c * 12.0 + (float)local_24;
        if (0.0001 < fVar1) {
          fVar1 = 1.0 / fVar1;
          iVar4 = this->ladderIndex;
          local_1c = (double)(fVar1 * (local_44 * 12.0 + (float)local_34) *
                              View_Record.MainCam.Const_x + View_Record.MainCam.Orig_x +
                             (float)Float2Int);
          local_14 = (double)(fVar1 * (local_40 * 12.0 + (float)local_2c) *
                              View_Record.MainCam.Const_y + View_Record.MainCam.Orig_y +
                             (float)Float2Int);
          if (local_c._4_4_ != 0) {
            iVar4 = iVar4 + 2;
          }
          iVar2 = local_1c._0_4_;
          DrawSprite(View_Record.MainCam.Buffer,iVar4,local_1c._0_4_ + -0x28,local_14._0_4_,0x240004
                    );
          DrawSprite(View_Record.MainCam.Buffer,iVar4 + 1,iVar2 + 0x28,local_14._0_4_,0x260004);
        }
        local_c._4_4_ = local_c._4_4_ + 5;
      } while (local_c._4_4_ < 0x1f);
    }
  }
  return;
}
