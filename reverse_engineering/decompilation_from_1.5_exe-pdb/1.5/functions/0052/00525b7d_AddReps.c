/*
 * Entry: 00525b7d
 * Name: AddReps
 * Namespace: Global
 * Signature: _OBJ76 * AddReps(ObjectType * * param_1, _OBJ76 * param_2, long param_3, long param_4, long param_5, _func___cdecl_void__OBJ76_ptr__OBJ76_ptr * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

_OBJ76 * __cdecl
AddReps(ObjectType **param_1,_OBJ76 *param_2,long param_3,long param_4,long param_5,
       _func___cdecl_void__OBJ76_ptr__OBJ76_ptr *param_6)

{
  long64 *_Str1;
  OBJECT_CLASS_T OVar1;
  int iVar2;
  _OBJ76 *p_Var3;
  char *pcVar4;
  uint uVar5;
  StructObjectType *_Source;
  undefined4 unaff_EDI;
  bool bVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  _OBJ76 *local_184 [80];
  uint local_44;
  _func___cdecl_void__OBJ76_ptr__OBJ76_ptr *local_40;
  int local_3c;
  ObjectType **local_38;
  _OBJ76 *local_34;
  int local_30;
  uint local_2c;
  char local_28 [8];
  undefined1 local_20;
  char local_18 [8];
  undefined1 local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_38 = param_1;
  local_34 = param_2;
  local_40 = param_6;
  if (param_5 == 0) {
    local_184[0] = (_OBJ76 *)0x0;
  }
  else {
    local_184[0] = (_OBJ76 *)0x0;
    local_2c = 0;
    if (0 < param_3) {
      do {
        uVar5 = 0;
        if (0 < param_4) {
          do {
            local_30 = 0;
            if (0 < param_5) {
              local_3c = 0;
              local_44 = uVar5 | local_2c;
              do {
                _Source = (StructObjectType *)((int)&(*local_38)->GeometryFile + local_3c);
                if (local_44 == 0) {
                  _Str1 = &_Source->Parent;
                  iVar2 = _strnicmp((char *)_Str1,"world",5);
                  p_Var3 = local_34;
                  if (((iVar2 != 0) &&
                      (iVar2 = _strnicmp((char *)_Str1,"null",4), p_Var3 = local_34, iVar2 != 0)) &&
                     (p_Var3 = find_obj_prjid(local_34,CONCAT44(unaff_EDI,
                                                                *(undefined4 *)
                                                                 ((int)&_Source->Parent + 4))),
                     p_Var3 == (_OBJ76 *)0x0)) {
                    strncpy(local_18,(char *)_Str1,8);
                    local_10 = 0;
                    strncpy(local_28,(char *)_Source,8);
                    local_20 = 0;
                    DEBUG_systemWarning("Can\'t find parent %s for object %s");
                    p_Var3 = local_34;
                  }
                  p_Var3 = NewObj(p_Var3,_Source,(long64 *)_Source,0);
                  if (p_Var3 == (_OBJ76 *)0x0) {
                    return (_OBJ76 *)0x0;
                  }
                  bVar6 = local_40 != (_func___cdecl_void__OBJ76_ptr__OBJ76_ptr *)0x0;
                  local_184[local_30] = p_Var3;
                  if (bVar6) {
                    (*local_40)(p_Var3,local_34);
                  }
                }
                else {
                  p_Var3 = local_184[local_30];
                }
                OVar1 = p_Var3->class_id;
                if (((((OVar1 != CLASS_ID_HEADLIGHT_MASK) && (OVar1 != CLASS_ID_EYEPOINT)) &&
                     ((OVar1 != CLASS_ID_WEAPON_HARDPOINT &&
                      ((OVar1 != CLASS_ID_CANNON_HARDPOINT && (OVar1 != CLASS_ID_ROCKET_HARDPOINT)))
                      ))) && (OVar1 != CLASS_ID_MORTAR_HARDPOINT)) &&
                   ((((OVar1 != CLASS_ID_SPECIAL_HARDPOINT && (OVar1 != CLASS_ID_FLAME_EMITTER)) &&
                     (OVar1 != CLASS_ID_SMOKE_EMITTER)) && (OVar1 != CLASS_ID_DUST_EMITTER)))) {
                  uVar7 = uVar5;
                  uVar8 = local_2c;
                  pcVar4 = PrjID2Filename(_Source->GeometryFile,".geo");
                  GeoCache_AddRep(p_Var3,pcVar4,uVar7,uVar8);
                  if (((local_2c == 2) && (local_34 != (_OBJ76 *)0x0)) &&
                     (local_34->class_id == CLASS_ID_WEAPON)) {
                    lVar9 = 3;
                    uVar7 = uVar5;
                    pcVar4 = PrjID2Filename(_Source->GeometryFile,".geo");
                    GeoCache_AddRep(p_Var3,pcVar4,uVar7,lVar9);
                  }
                }
                local_30 = local_30 + 1;
                local_3c = local_3c + 100;
              } while (local_30 < param_5);
            }
            local_38 = local_38 + 1;
            uVar5 = uVar5 + 1;
          } while ((int)uVar5 < param_4);
        }
        local_2c = local_2c + 1;
      } while ((int)local_2c < param_3);
    }
  }
  return local_184[0];
}
