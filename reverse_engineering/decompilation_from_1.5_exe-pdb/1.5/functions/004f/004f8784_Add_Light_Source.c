/*
 * Entry: 004f8784
 * Name: Add_Light_Source
 * Namespace: Global
 * Signature: void Add_Light_Source(_OBJ76 * param_1, LIGHT_TYPE param_2, float param_3, float param_4, VECTOR_3D * param_5, VECTOR_3D * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
Add_Light_Source(_OBJ76 *param_1,LIGHT_TYPE param_2,float param_3,float param_4,VECTOR_3D *param_5,
                VECTOR_3D *param_6)

{
  ulong *puVar1;
  float fVar2;
  long lVar3;
  DYNAMIC_LIGHT *pDVar4;
  int iVar5;
  float10 fVar6;
  char local_118 [256];
  char local_18 [4];
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  lVar3 = Lights_Struct.Light_Counter;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (TOD_tbl[Lights_Struct.TOD_entry].Day_Time != 1) {
    if (Lights_Struct.Light_Counter < 0x200) {
      iVar5 = 0;
      if (0 < Lights_Struct.Light_Counter) {
        pDVar4 = Lights_Struct.Lights_Array;
        do {
          if (pDVar4->Light_Owner == param_1) {
            strncpy(local_18,(char *)&param_1->id,8);
            sprintf(local_118,"Object \"%s\" with more than one light source",local_18);
            return;
          }
          iVar5 = iVar5 + 1;
          pDVar4 = pDVar4 + 1;
        } while (iVar5 < Lights_Struct.Light_Counter);
      }
      Lights_Struct.Light_Counter = Lights_Struct.Light_Counter + 1;
      if (param_6 == (VECTOR_3D *)0x0) {
        local_14 = 0.0;
        local_10 = 0.0;
        local_c = 0.0;
      }
      else {
        local_14 = param_6->x;
        local_10 = param_6->y;
        local_c = param_6->z;
      }
      if (param_3 < 20.0) {
        param_3 = 20.0;
      }
      fVar6 = (float10)param_4;
      if (fVar6 < (float10)0.17453292) {
        fVar6 = (float10)0.17453292;
      }
      if ((float10)1.5707963 < fVar6) {
        fVar6 = (float10)1.5707963;
      }
      fVar6 = (float10)fcos(fVar6);
      fVar6 = (float10)floor((double)((float10)-0.69315 /
                                     ((float10)0.6931471805599453 *
                                     (fVar6 + (float10)1.0) * (float10)0.5)));
      Lights_Struct.Lights_Array[lVar3].Light_Owner = param_1;
      if (param_2 == OMNIDIRECTIONAL) {
        Lights_Struct.Lights_Array[lVar3].flags = 0;
      }
      else if (param_2 == SPOTLIGHT) {
        Lights_Struct.Lights_Array[lVar3].flags = 1;
      }
      puVar1 = &Lights_Struct.Lights_Array[lVar3].flags;
      *puVar1 = *puVar1 | 8;
      Lights_Struct.Lights_Array[lVar3].Radius = param_3;
      Lights_Struct.Lights_Array[lVar3].Local_Posit.x = local_14;
      Lights_Struct.Lights_Array[lVar3].Local_Posit.y = local_10;
      Lights_Struct.Lights_Array[lVar3].Local_Posit.z = local_c;
      Lights_Struct.Lights_Array[lVar3].Att_Dist = 1.0 / (param_3 * param_3);
      Lights_Struct.Lights_Array[lVar3].Cone = (float)fVar6;
      if (param_2 == SPOTLIGHT) {
        if (param_5 == (VECTOR_3D *)0x0) {
          Lights_Struct.Lights_Array[lVar3].Local_Direction.x = -(param_1->transform).front_x;
          Lights_Struct.Lights_Array[lVar3].Local_Direction.y = -(param_1->transform).front_y;
          fVar2 = (param_1->transform).front_z;
        }
        else {
          Lights_Struct.Lights_Array[lVar3].Local_Direction.x = -param_5->x;
          Lights_Struct.Lights_Array[lVar3].Local_Direction.y = -param_5->y;
          fVar2 = param_5->z;
        }
        fVar2 = -fVar2;
      }
      else {
        fVar2 = 0.0;
        Lights_Struct.Lights_Array[lVar3].Local_Direction.x = 0.0;
        Lights_Struct.Lights_Array[lVar3].Local_Direction.y = 0.0;
      }
      Lights_Struct.Lights_Array[lVar3].Local_Direction.z = fVar2;
    }
    else {
      DEBUG_systemWarning("Too many lights sources in this mission");
    }
  }
  return;
}
