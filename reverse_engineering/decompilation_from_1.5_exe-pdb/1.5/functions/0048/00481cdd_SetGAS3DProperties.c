/*
 * Entry: 00481cdd
 * Name: SetGAS3DProperties
 * Namespace: Global
 * Signature: void SetGAS3DProperties(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetGAS3DProperties(_gas_object *param_1)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  int in_EAX;
  int iVar3;
  MAT_3D *pMVar4;
  VECTOR_3D *pVVar5;
  float *pfVar6;
  MAT_3D local_b8;
  float local_78 [10];
  double local_50;
  double local_48;
  double local_40;
  float local_38;
  VECTOR_3D local_34;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  VECTOR_3D local_10;
  
  if (((((GM != (GAS_MASTER *)0x0) && (GM->listener != (IDirectSound3DListener *)0x0)) &&
       (in_EAX != 0)) &&
      ((*(_OBJ76 **)(in_EAX + 0x5c) != (_OBJ76 *)0x0 && (*(int *)(in_EAX + 0x58) != 0)))) &&
     ((*(uint *)(in_EAX + 0x14) & 0x100) != 0)) {
    iVar3 = is_user_vhcl(*(_OBJ76 **)(in_EAX + 0x5c));
    if (((iVar3 == 0) || (View_Record.Intenal_View == 0)) || (*(float *)(in_EAX + 0x20) != 0.0)) {
      pMVar4 = obj_rel_parent_matrix(&local_b8,*(_OBJ76 **)(in_EAX + 0x5c),(_OBJ76 *)0x0);
      pfVar6 = local_78;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pfVar6 = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pfVar6 = pfVar6 + 1;
      }
      local_28 = (float)local_50;
      local_24 = (float)local_48;
      local_20 = (float)local_40;
      local_1c = local_28;
      local_18 = local_24;
      local_14 = local_20;
      if (*(float *)(in_EAX + 0x20) != 0.0) {
        local_10.x = local_78[0];
        local_10.y = local_78[1];
        local_10.z = local_78[2];
        VVar1.y = local_24;
        VVar1.x = local_28;
        VVar1.z = local_20;
        VVar2.y = local_78[1];
        VVar2.x = local_78[0];
        VVar2.z = local_78[2];
        pVVar5 = AddMultVectors(&local_10,VVar1,*(float *)(in_EAX + 0x20) * 0.002,VVar2);
        local_1c = pVVar5->x;
        local_18 = pVVar5->y;
        local_14 = pVVar5->z;
      }
      ds3dBuffer.vPosition.x = local_1c;
      ds3dBuffer.vPosition.y = local_18;
      ds3dBuffer.vPosition.z = local_14;
      ClassGetVelocity(*(_OBJ76 **)(in_EAX + 0x5c),&local_34,&local_38);
      ds3dBuffer.vVelocity.x = local_34.x;
      ds3dBuffer.vVelocity.y = local_34.y;
      ds3dBuffer.vVelocity.z = local_34.z;
    }
    else {
      ds3dBuffer.vPosition.x = ds3dListener.vPosition.x;
      ds3dBuffer.vPosition.y = ds3dListener.vPosition.y;
      ds3dBuffer.vPosition.z = ds3dListener.vPosition.z;
      ds3dBuffer.vVelocity.x = ds3dListener.vVelocity.x;
      ds3dBuffer.vVelocity.y = ds3dListener.vVelocity.y;
      ds3dBuffer.vVelocity.z = ds3dListener.vVelocity.z;
    }
    if ((*(uint *)(in_EAX + 0x14) & 0x200) == 0) {
      ds3dBuffer.flMinDistance = explosionMinDist;
      ds3dBuffer.flMaxDistance = maxSoundDist;
      if ((*(uint *)(in_EAX + 0x14) & 0x7800) != 0x1800) {
        ds3dBuffer.flMinDistance = minSoundDist;
      }
    }
    else {
      ds3dBuffer.flMinDistance = minDiscardSoundDist;
      ds3dBuffer.flMaxDistance = maxDiscardSoundDist;
    }
    (**(code **)(**(int **)(in_EAX + 0x58) + 0x30))(*(int **)(in_EAX + 0x58),&ds3dBuffer,1);
  }
  return;
}
