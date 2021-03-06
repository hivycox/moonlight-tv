#pragma once
#include "computer_manager.h"

#include <stdbool.h>

#include "libgamestream/client.h"

#ifndef NK_NUKLEAR_H_
#include "nuklear/config.h"
#include "nuklear.h"
#endif

#define MAIN_THREAD
#define WORKER_THREAD
#define THREAD_SAFE

MAIN_THREAD void coverloader_init();

MAIN_THREAD void coverloader_destroy();

MAIN_THREAD struct nk_image *coverloader_get(PSERVER_LIST node, int id, int target_width, int target_height);

MAIN_THREAD bool coverloader_dispatch_userevent(int which, void *data1, void *data2);

#ifndef _COVERLOADER_IMPL
#undef MAIN_THREAD
#undef WORKER_THREAD
#undef THREAD_SAFE
#endif