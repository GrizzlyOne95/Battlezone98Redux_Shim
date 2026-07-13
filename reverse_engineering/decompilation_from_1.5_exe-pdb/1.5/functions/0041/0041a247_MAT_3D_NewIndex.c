/*
 * Entry: 0041a247
 * Name: MAT_3D_NewIndex
 * Namespace: Global
 * Signature: int MAT_3D_NewIndex(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MAT_3D_NewIndex(lua_State *param_1)

{
  float fVar1;
  float fVar2;
  MAT_3D *pMVar3;
  char *pcVar4;
  uint uVar5;
  VECTOR_3D *pVVar6;
  double dVar7;
  
  pMVar3 = GetMatrix(param_1,1);
  if (pMVar3 != (MAT_3D *)0x0) {
    pcVar4 = luaL_checklstring(param_1,2,(uint *)0x0);
    uVar5 = Hash(pcVar4,0x811c9dc5);
    if (uVar5 < 0xb96c4116) {
      if (uVar5 == 0xb96c4115) {
        dVar7 = luaL_checknumber(param_1,3);
        pMVar3->right_y = (float)dVar7;
      }
      else if (uVar5 < 0x44e771bd) {
        if (uVar5 == 0x44e771bc) {
          pVVar6 = GetVector(param_1,2);
          if (pVVar6 != (VECTOR_3D *)0x0) {
            fVar1 = pVVar6->y;
            fVar2 = pVVar6->z;
            pMVar3->posit_x = (double)pVVar6->x;
            pMVar3->posit_y = (double)fVar1;
            pMVar3->posit_z = (double)fVar2;
          }
        }
        else if (uVar5 == 0x21f7b0fc) {
          dVar7 = luaL_checknumber(param_1,3);
          pMVar3->up_y = (float)dVar7;
        }
        else if (uVar5 == 0x22f7b28f) {
          dVar7 = luaL_checknumber(param_1,3);
          pMVar3->up_x = (float)dVar7;
        }
        else if (uVar5 == 0x24f7b5b5) {
          dVar7 = luaL_checknumber(param_1,3);
          pMVar3->up_z = (float)dVar7;
        }
        else if ((uVar5 == 0x43430b20) &&
                (pVVar6 = GetVector(param_1,2), pVVar6 != (VECTOR_3D *)0x0)) {
          pMVar3->up_x = pVVar6->x;
          pMVar3->up_y = pVVar6->y;
          pMVar3->up_z = pVVar6->z;
        }
      }
      else if (uVar5 == 0x78e32de5) {
        pVVar6 = GetVector(param_1,2);
        if (pVVar6 != (VECTOR_3D *)0x0) {
          pMVar3->right_x = pVVar6->x;
          pMVar3->right_y = pVVar6->y;
          pMVar3->right_z = pVVar6->z;
        }
      }
      else if (uVar5 == 0xb66c3c5c) {
        dVar7 = luaL_checknumber(param_1,3);
        pMVar3->right_z = (float)dVar7;
      }
      else if (uVar5 == 0xb86c3f82) {
        dVar7 = luaL_checknumber(param_1,3);
        pMVar3->right_x = (float)dVar7;
      }
    }
    else if (uVar5 == 0xc5a81bb4) {
      dVar7 = luaL_checknumber(param_1,3);
      pMVar3->front_y = (float)dVar7;
    }
    else if (uVar5 == 0xc6a81d47) {
      dVar7 = luaL_checknumber(param_1,3);
      pMVar3->front_x = (float)dVar7;
    }
    else if (uVar5 == 0xc8a8206d) {
      dVar7 = luaL_checknumber(param_1,3);
      pMVar3->front_z = (float)dVar7;
    }
    else if (uVar5 == 0xe179dbd8) {
      pVVar6 = GetVector(param_1,2);
      if (pVVar6 != (VECTOR_3D *)0x0) {
        pMVar3->front_x = pVVar6->x;
        pMVar3->front_y = pVVar6->y;
        pMVar3->front_z = pVVar6->z;
      }
    }
    else if (uVar5 == 0xebf98a60) {
      dVar7 = luaL_checknumber(param_1,3);
      pMVar3->posit_y = dVar7;
    }
    else if (uVar5 == 0xecf98bf3) {
      dVar7 = luaL_checknumber(param_1,3);
      pMVar3->posit_x = dVar7;
    }
    else if (uVar5 == 0xeef98f19) {
      dVar7 = luaL_checknumber(param_1,3);
      pMVar3->posit_z = dVar7;
    }
  }
  return 0;
}
