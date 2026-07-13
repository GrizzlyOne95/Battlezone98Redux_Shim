/*
 * Entry: 00582f24
 * Name: WiggleBurger
 * Namespace: Global
 * Signature: void WiggleBurger(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WiggleBurger(CAMERA *param_1)

{
  _GRAPHIC_BUFFER *p_Var1;
  MAT_3D *pMVar2;
  long extraout_EAX;
  long lVar3;
  long extraout_EAX_00;
  uint uVar4;
  long extraout_EAX_01;
  int iVar5;
  int unaff_EDI;
  MAT_3D *pMVar6;
  float fVar7;
  BITMAP_OPER BVar8;
  MAT_3D local_98;
  MAT_3D local_58;
  float local_18;
  float local_14;
  uint local_10;
  float local_c;
  float local_8;
  
  fVar7 = TimeStepLocal();
  if (useD3D == 0) {
    local_8 = TimeStepLocal();
    p_Var1 = param_1->Buffer;
    if (WiggleOneShotOn == 0) {
      local_10 = rand();
      local_10 = local_10 & 0xf;
      uVar4 = rand();
      local_c = (float)(uVar4 & 0xf);
      x = lpfilter(x,(float)(int)local_10,local_8);
      y = lpfilter(y,(float)(int)local_c,local_8);
      if (View_Record.Intenal_View == 0) {
        return;
      }
      BVar8 = ONE_THIRD_TRANSLUCENT_PIXELS;
      _ftol2_sse();
      lVar3 = extraout_EAX_01;
    }
    else {
      if (TargetOffset - 1.0 <= CurrentOffset) {
        TargetOffset = 0.0;
      }
      CurrentOffset = lpfilter(CurrentOffset,TargetOffset,local_8 + local_8);
      if ((CurrentOffset < 1.0) && (TargetOffset == 0.0)) {
        WiggleOneShotOn = 0;
        WiggleBurgerOn = 0;
      }
      if (View_Record.Intenal_View == 0) {
        return;
      }
      BVar8 = ONE_THIRD_TRANSLUCENT_PIXELS;
      _ftol2_sse();
      lVar3 = extraout_EAX;
    }
    _ftol2_sse();
    Graphic_Copy_Bitmap(p_Var1,p_Var1,extraout_EAX_00,lVar3,BVar8);
  }
  else {
    if (WiggleOneShotOn == 0) {
      CurrentOffset = 8.0;
    }
    else {
      if (TargetOffset - 1.0 <= CurrentOffset) {
        TargetOffset = 0.0;
      }
      CurrentOffset = lpfilter(CurrentOffset,TargetOffset,fVar7 * 5.0);
      if ((CurrentOffset < 1.0) && (TargetOffset == 0.0)) {
        WiggleOneShotOn = 0;
        WiggleBurgerOn = 0;
      }
    }
    if (View_Record.Intenal_View != 0) {
      local_14 = Get_TimeLocal();
      local_10 = Set_Rounding(unaff_EDI);
      local_8 = param_1->View_Angle * CurrentOffset * 0.003125;
      local_c = Noise1D(CurrentOffset * local_14 * 0.1 + 8.53);
      local_c = local_c * local_8;
      local_18 = Noise1D(CurrentOffset * local_14 * 0.1 + 17.67);
      local_18 = local_18 * local_8;
      fVar7 = Noise1D(CurrentOffset * local_14 * 0.05 + 5.19);
      pMVar2 = Build_Position_Rotation_Matrix
                         (&local_98,local_c,local_18,fVar7 * local_8 * 0.1,0.0,0.0,0.0);
      pMVar6 = &local_58;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar6->right_x = pMVar2->right_x;
        pMVar2 = (MAT_3D *)&pMVar2->right_y;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
      }
      pMVar2 = Matrix_Multiply(&local_98,&param_1->Matrix,&local_58);
      pMVar6 = &param_1->Matrix;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar6->right_x = pMVar2->right_x;
        pMVar2 = (MAT_3D *)&pMVar2->right_y;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
      }
      Set_Rounding(unaff_EDI);
    }
  }
  return;
}
