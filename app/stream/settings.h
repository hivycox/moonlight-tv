/*
 * This file is part of Moonlight Embedded.
 *
 * Copyright (C) 2015-2017 Iwan Timmer
 *
 * Moonlight is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight; if not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <Limelight.h>

#include <stdbool.h>

#define MAX_INPUTS 6

enum codecs { CODEC_UNSPECIFIED, CODEC_H264, CODEC_HEVC };

typedef struct _CONFIGURATION {
  STREAM_CONFIGURATION stream;
  int debug_level;
  char* app;
  char* action;
  char* address;
  char* mapping;
  char* platform;
  char* audio_device;
  char* config_file;
  char key_dir[4096];
  bool sops;
  bool localaudio;
  bool fullscreen;
  int rotate;
  bool unsupported;
  bool quitappafter;
  bool viewonly;
  char* inputs[MAX_INPUTS];
  int inputsCount;
  enum codecs codec;
} CONFIGURATION, *PCONFIGURATION;

#define CONF_DIR ".moonlight-tv"
#define CONF_NAME_STREAMING "streaming.conf"

#define RES_MERGE(w, h) ((w & 0xFFFF) << 16 | h & 0xFFFF)

#define RES_720P RES_MERGE(1280, 720)
#define RES_1080P RES_MERGE(1920, 1080)
#define RES_2K RES_MERGE(2560, 1440)
#define RES_4K RES_MERGE(3840, 2160)

char *settings_config_dir();

void config_save(char *filename, PCONFIGURATION config);

PCONFIGURATION settings_load();

void settings_save(PCONFIGURATION config);

int settings_optimal_bitrate(int w, int h, int fps);

bool settings_sops_supported(int w, int h, int fps);