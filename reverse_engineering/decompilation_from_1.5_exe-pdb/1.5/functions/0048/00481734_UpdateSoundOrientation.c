/*
 * Entry: 00481734
 * Name: UpdateSoundOrientation
 * Namespace: Global
 * Signature: void UpdateSoundOrientation(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateSoundOrientation(void)

{
  tagENTITY *ptVar1;
  MAT_3D *pMVar2;
  int iVar3;
  float *pfVar4;
  MAT_3D local_94;
  float local_54 [4];
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  double local_2c;
  double local_24;
  double local_1c;
  float local_14;
  VECTOR_3D local_10;
  
  if ((((GM != (GAS_MASTER *)0x0) && (GM->listener != (IDirectSound3DListener *)0x0)) &&
      (ptVar1 = Get_Camera_Owner(), ptVar1 != (tagENTITY *)0x0)) && (ptVar1->obj76 != (_OBJ76 *)0x0)
     ) {
    if (View_Record.Intenal_View == 0) {
      ds3dListener.flDistanceFactor = outsideDistanceFactor;
      ds3dListener.flRolloffFactor = outsideRolloffFactor;
      ds3dListener.flDopplerFactor = outsideDopplerFactor;
    }
    else {
      ds3dListener.flDistanceFactor = insideDistanceFactor;
      ds3dListener.flRolloffFactor = insideRolloffFactor;
      ds3dListener.flDopplerFactor = insideDopplerFactor;
    }
    pMVar2 = obj_rel_parent_matrix(&local_94,ptVar1->obj76,(_OBJ76 *)0x0);
    pfVar4 = local_54;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pfVar4 = pfVar4 + 1;
    }
    ds3dListener.vPosition.x = (float)local_2c;
    ds3dListener.vPosition.y = (float)local_24;
    ds3dListener.vPosition.z = (float)local_1c;
    ds3dListener.vOrientFront.x = local_3c;
    ds3dListener.vOrientFront.y = local_38;
    ds3dListener.vOrientFront.z = local_34;
    ds3dListener.vOrientTop.x = local_54[3];
    ds3dListener.vOrientTop.y = local_44;
    ds3dListener.vOrientTop.z = local_40;
    ClassGetVelocity(ptVar1->obj76,&local_10,&local_14);
    ds3dListener.vVelocity.x = local_10.x;
    ds3dListener.vVelocity.y = local_10.y;
    ds3dListener.vVelocity.z = local_10.z;
    (**(code **)((int)*GM->listener + 0x28))(GM->listener,&ds3dListener,1);
  }
  return;
}
