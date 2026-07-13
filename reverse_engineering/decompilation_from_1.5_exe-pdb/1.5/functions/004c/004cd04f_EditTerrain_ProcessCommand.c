/*
 * Entry: 004cd04f
 * Name: EditTerrain::ProcessCommand
 * Namespace: EditTerrain
 * Signature: void ProcessCommand(EditTerrain * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::ProcessCommand(EditTerrain *this,VECTOR_3D *param_1)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  EditTerrain *this_00;
  float fVar7;
  int iVar8;
  FLOAT2INT local_20;
  FLOAT2INT local_18;
  tagPOINT local_10;
  int local_8;
  
  if ((edit_controls.edit_lmouse == '\0') && (edit_controls.edit_rmouse == '\0')) {
    this->lastLButton = 0;
    this->lastRButton = 0;
    return;
  }
  GetTerrainTileXZ(&local_10,param_1);
  puVar2 = GetTilePtr(local_10.x,local_10.y);
  WorldToGrid(this,&local_20,&local_18,param_1);
  puVar3 = GetZonePtr(local_20.i,local_18.i);
  local_8 = this->commandMenu->icon[this->commandDown].cmd;
  iVar4 = (uint)(edit_controls.edit_rmouse == '\0') * 2 + -1;
  if (((edit_controls.edit_lmouse == '\0') || (this->lastLButton != 0)) &&
     ((edit_controls.edit_rmouse == '\0' || (this->lastRButton != 0)))) {
    if (((edit_controls.edit_lmouse == '\0') || (this->lastLButton != 1)) &&
       ((edit_controls.edit_rmouse == '\0' || (this->lastRButton != 1))))
    goto switchD_004cd105_caseD_d;
    if (local_8 != 4) {
      if (local_8 != 10) {
        if (local_8 == 0xb) {
          iVar4 = 0;
          goto LAB_004cd35f;
        }
        if (local_8 != 0xc) {
          if (local_8 != 0x10) {
            if (local_8 != 0x15) goto switchD_004cd105_caseD_d;
            iVar4 = 0;
            goto LAB_004cd334;
          }
          iVar8 = 0;
          goto LAB_004cd349;
        }
      }
      iVar8 = 0;
      goto LAB_004cd371;
    }
    if (edit_controls.edit_control != '\0') goto LAB_004cd38b;
    if ((this->eyedropTile == 0xffffffff) ||
       (uVar6 = (uint)*puVar2, ((this->eyedropTile ^ uVar6) & 0xff80) == 0))
    goto switchD_004cd105_caseD_d;
LAB_004cd3d5:
    PushUndoTile(this,local_10.x,local_10.y,uVar6);
    iVar4 = RandomFlip(this_00,this->eyedropTile);
    *puVar2 = (ushort)iVar4;
    goto switchD_004cd105_caseD_d;
  }
  switch(local_8) {
  case 0:
    if (TerrainWireFrame == 0) {
      this->eyedropTile = (uint)*puVar2;
    }
    else {
      uVar1 = *puVar3;
      this->eyedropGrid = uVar1 & 0xfff;
      this->brushY = (float)(uVar1 & 0xfff) * 0.1;
    }
    break;
  case 1:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    uVar1 = *puVar2;
    uVar6 = uVar1 >> 4 & 0xf;
    if (iVar4 < 1) {
      sVar5 = (short)mix2PrevRotat[uVar6];
    }
    else {
      sVar5 = (short)mix2NextRotat[uVar6];
    }
    goto LAB_004cd1dd;
  case 2:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    uVar1 = *puVar2;
    sVar5 = (short)mix2NextFlipV[uVar1 >> 4 & 0xf];
    goto LAB_004cd1dd;
  case 3:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    uVar1 = *puVar2;
    sVar5 = (short)mix2NextFlipH[uVar1 >> 4 & 0xf];
LAB_004cd1dd:
    *puVar2 = sVar5 << 4 | uVar1 & 0xff0f;
    break;
  case 4:
    if (edit_controls.edit_control != '\0') {
LAB_004cd38b:
      uVar1 = GetEncodedMaterial(this,local_10.x,local_10.y);
      if (((*puVar2 ^ uVar1) & 0xff80) != 0) {
        PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
        *puVar2 = uVar1;
      }
      break;
    }
    if (this->eyedropTile == -1) break;
    uVar6 = (uint)*puVar2;
    goto LAB_004cd3d5;
  case 5:
    if (iVar4 < 1) {
      fVar7 = 0.5;
    }
    else {
      fVar7 = 2.0;
    }
    fVar7 = Clamp(fVar7 * this->viewZoom,1.7,16.0);
    this->viewZoom = fVar7;
    (this->viewCenter).x = param_1->x;
    fVar7 = param_1->z;
    (this->viewCenter).z = fVar7;
    fVar7 = Terrain_FindFloor((double)(this->viewCenter).x,(double)fVar7);
    (this->viewCenter).y = fVar7;
    break;
  case 6:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    CycleSolidTile(puVar2,iVar4);
    break;
  case 7:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    CycleCapTile(puVar2,iVar4);
    break;
  case 8:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    CycleDiagTile(puVar2,iVar4);
    break;
  case 9:
    PushUndoTile(this,local_10.x,local_10.y,(uint)*puVar2);
    CycleTileVariant(puVar2,iVar4);
    break;
  case 10:
  case 0xc:
    iVar8 = 1;
LAB_004cd371:
    CmdAddFlat(this,puVar3,local_20.i,local_18.i,iVar4,iVar8);
    break;
  case 0xb:
    iVar4 = 1;
LAB_004cd35f:
    CmdSetFlat(this,puVar3,local_20.i,local_18.i,iVar4);
    break;
  case 0x10:
    iVar8 = 1;
LAB_004cd349:
    CmdAddBell(this,puVar3,local_20.i,local_18.i,iVar4,iVar8);
    break;
  case 0x11:
    CmdSetBell(this,puVar3,local_20.i,local_18.i,iVar4,1);
    break;
  case 0x15:
    iVar4 = 1;
LAB_004cd334:
    CmdBlur(this,puVar3,local_20.i,local_18.i,iVar4);
  }
switchD_004cd105_caseD_d:
  this->lastLButton = (uint)(edit_controls.edit_lmouse != '\0');
  this->lastRButton = (uint)(edit_controls.edit_rmouse != '\0');
  return;
}
