/*
 * Entry: 00482309
 * Name: NextGAS
 * Namespace: Global
 * Signature: int NextGAS(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl NextGAS(int param_1)

{
  ulong *puVar1;
  _OBJ76 *p_Var2;
  _func___cdecl_int__gas_object_ptr_long *p_Var3;
  VECTOR_3D VVar4;
  _gas_object *p_Var5;
  _gas_object *p_Var6;
  bool bVar7;
  _OBJ76 *p_Var8;
  VECTOR_3D *pVVar9;
  int iVar10;
  _gas_object *unaff_EDI;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  _gas_object *local_10;
  int local_c;
  int local_8;
  
  CheckCDLooping();
  if (GASActive != 0) {
    if (GM == (GAS_MASTER *)0x0) {
      return 0;
    }
    if ((param_1 != 0) && (GM->listener != (IDirectSound3DListener *)0x0)) {
      UpdateSoundOrientation();
    }
    ClearCopies();
    local_1c = (float)View_Record.MainCam.View_Pyramid[0].x;
    local_18 = (float)View_Record.MainCam.View_Pyramid[0].y;
    local_8 = 0;
    local_c = 0;
    local_14 = (float)View_Record.MainCam.View_Pyramid[0].z;
    p_Var6 = firstSound;
joined_r0x00482373:
    p_Var5 = p_Var6;
    if (p_Var5 != (_gas_object *)0x0) {
      p_Var2 = p_Var5->obj76;
      local_10 = p_Var5->next;
      if ((p_Var2 == (_OBJ76 *)0x0) ||
         (p_Var8 = get_obj_from_handle_fast(p_Var5->objHandle,p_Var2), p_Var8 != (_OBJ76 *)0x0))
      goto LAB_004823a7;
      goto LAB_0048239c;
    }
    if (((GM->listener != (IDirectSound3DListener *)0x0) && (local_c != 0)) && (param_1 != 0)) {
      (**(code **)((int)*GM->listener + 0x44))(GM->listener);
    }
    GAS_DebugUpdate();
  }
  return 1;
LAB_004823a7:
  p_Var6 = local_10;
  if ((p_Var5->flags & 8) != 0) goto joined_r0x00482373;
  if ((p_Var2 != (_OBJ76 *)0x0) && (((p_Var5->gc).flags & 0x400) == 0)) {
    pVVar9 = obj_get_world_position(&local_28,p_Var2);
    VVar4.y = local_18;
    VVar4.x = local_1c;
    VVar4.z = local_14;
    bVar7 = TooFar(VVar4,*pVVar9);
    if ((bVar7) ||
       ((local_8 == GM->maxObjects ||
        (iVar10 = IncCopy(unaff_EDI), (p_Var5->gpi).maxCopies < iVar10)))) {
      if ((p_Var5->flags & 4) != 0) {
        StopGASObject(p_Var5);
      }
      p_Var6 = local_10;
      if ((p_Var5->gpi).loopMode == 1) goto joined_r0x00482373;
      goto LAB_0048239c;
    }
    local_8 = local_8 + 1;
  }
  if ((p_Var5->flags & 4) == 0) {
    StartGASObject(p_Var5,1);
    p_Var6 = local_10;
    goto joined_r0x00482373;
  }
  if ((p_Var5->gpi).loopMode == 2) {
    if ((p_Var5->storage).gsBytes.gsChar1 == '\0') {
      StopGASObject(p_Var5);
    }
    else {
      (p_Var5->storage).gsBytes.gsChar1 = '\0';
    }
  }
  iVar10 = IsObjectPlaying(p_Var5);
  if (iVar10 == 0) {
    p_Var3 = (p_Var5->gc).eofCallback;
    if (p_Var3 == (_func___cdecl_int__gas_object_ptr_long *)0x0) {
      if ((p_Var5->gpi).loopMode == 1) {
        p_Var5->flags = p_Var5->flags & 0xfffffffb;
        p_Var6 = local_10;
        goto joined_r0x00482373;
      }
LAB_0048239c:
      DeleteGASObject(p_Var5);
      p_Var6 = local_10;
      goto joined_r0x00482373;
    }
    iVar10 = (*p_Var3)(p_Var5,3);
    p_Var6 = local_10;
    if (iVar10 == 0) goto joined_r0x00482373;
  }
  if (p_Var5->obj76 != (_OBJ76 *)0x0) {
    puVar1 = &(p_Var5->gc).flags;
    *puVar1 = *puVar1 | 0x100;
  }
  iVar10 = (p_Var5->gpi).random;
  (p_Var5->gc).volume = (float)(p_Var5->gpi).volume;
  if (iVar10 != 1) {
    (p_Var5->gc).rate = (float)(p_Var5->gpi).sampleRate;
  }
  p_Var3 = (p_Var5->gc).modCallback;
  if ((p_Var3 == (_func___cdecl_int__gas_object_ptr_long *)0x0) ||
     (iVar10 = (*p_Var3)(p_Var5,2), p_Var6 = local_10, iVar10 != 0)) {
    SetGASAudioProperties((_gas_object *)0x0,(int)unaff_EDI);
    local_c = local_c + 1;
    p_Var6 = local_10;
  }
  goto joined_r0x00482373;
}
