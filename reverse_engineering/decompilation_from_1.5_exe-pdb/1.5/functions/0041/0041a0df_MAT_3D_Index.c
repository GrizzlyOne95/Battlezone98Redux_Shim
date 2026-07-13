/*
 * Entry: 0041a0df
 * Name: MAT_3D_Index
 * Namespace: Global
 * Signature: int MAT_3D_Index(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MAT_3D_Index(lua_State *param_1)

{
  float fVar1;
  MAT_3D *pMVar2;
  char *pcVar3;
  uint uVar4;
  VECTOR_3D *pVVar5;
  lua_State *unaff_EDI;
  float local_10;
  float local_c;
  
  pMVar2 = GetMatrix(param_1,1);
  pcVar3 = luaL_checklstring(param_1,2,(uint *)0x0);
  uVar4 = Hash(pcVar3,0x811c9dc5);
  if (uVar4 < 0xb96c4116) {
    if (uVar4 == 0xb96c4115) {
      fVar1 = pMVar2->right_y;
    }
    else if (uVar4 < 0x44e771bd) {
      if (uVar4 == 0x44e771bc) {
        local_10 = (float)pMVar2->posit_x;
        local_c = (float)pMVar2->posit_y;
        fVar1 = (float)pMVar2->posit_z;
LAB_0041a15c:
        pVVar5 = NewVector(unaff_EDI);
        pVVar5->x = local_10;
        pVVar5->y = local_c;
        pVVar5->z = fVar1;
        return 1;
      }
      if (uVar4 == 0x21f7b0fc) {
        fVar1 = pMVar2->up_y;
      }
      else if (uVar4 == 0x22f7b28f) {
        fVar1 = pMVar2->up_x;
      }
      else {
        if (uVar4 != 0x24f7b5b5) {
          if (uVar4 != 0x43430b20) {
            return 0;
          }
          local_10 = pMVar2->up_x;
          local_c = pMVar2->up_y;
          fVar1 = pMVar2->up_z;
          goto LAB_0041a15c;
        }
        fVar1 = pMVar2->up_z;
      }
    }
    else {
      if (uVar4 == 0x78e32de5) {
        local_10 = pMVar2->right_x;
        local_c = pMVar2->right_y;
        fVar1 = pMVar2->right_z;
        goto LAB_0041a15c;
      }
      if (uVar4 == 0xb66c3c5c) {
        fVar1 = pMVar2->right_z;
      }
      else {
        if (uVar4 != 0xb86c3f82) {
          return 0;
        }
        fVar1 = pMVar2->right_x;
      }
    }
  }
  else if (uVar4 == 0xc5a81bb4) {
    fVar1 = pMVar2->front_y;
  }
  else if (uVar4 == 0xc6a81d47) {
    fVar1 = pMVar2->front_x;
  }
  else if (uVar4 == 0xc8a8206d) {
    fVar1 = pMVar2->front_z;
  }
  else {
    if (uVar4 == 0xe179dbd8) {
      local_10 = pMVar2->front_x;
      local_c = pMVar2->front_y;
      fVar1 = pMVar2->front_z;
      goto LAB_0041a15c;
    }
    if (uVar4 == 0xebf98a60) {
      fVar1 = (float)pMVar2->posit_y;
    }
    else if (uVar4 == 0xecf98bf3) {
      fVar1 = (float)pMVar2->posit_x;
    }
    else {
      if (uVar4 != 0xeef98f19) {
        return 0;
      }
      fVar1 = (float)pMVar2->posit_z;
    }
  }
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
