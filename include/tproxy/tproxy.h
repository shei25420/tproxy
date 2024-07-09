/*
 * include/tproxy/tproxy.h
 * This file defines everything related to tproxy.
 *
 * Copyright (C) Jiang Wenyuan, < koubunen AT gmail DOT com >
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, version 2.1
 * exclusively.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef _tproxy_H
#define _tproxy_H

#define tproxy_VERSION    "5.4.0.24-dev"
#define tproxy_COPYRIGHT  "2017-present, Jiang Wenyuan, <koubunen AT gmail DOT com >"

#include <haproxy/applet-t.h>

#include <tproxy/common.h>
#include <tproxy/shctx.h>
#include <tproxy/shmem.h>
#include <tproxy/http.h>
#include <tproxy/key.h>
#include <tproxy/store.h>
#include <tproxy/core.h>
#include <tproxy/cache.h>
#include <tproxy/nosql.h>
#include <tproxy/manager.h>


typedef struct tproxy {
    nst_core_t                 *cache;
    nst_core_t                 *nosql;

    struct {
        hpx_applet_t            cache;
        hpx_applet_t            nosql;
        hpx_applet_t            purger;
        hpx_applet_t            stats;
    } applet;

    nst_proxy_t               **proxy;
} tproxy_t;

extern tproxy_t tproxy;


void tproxy_init();

/* parser */
int tproxy_parse_global_cache(const char *file, int linenum, char **args);
int tproxy_parse_global_nosql(const char *file, int linenum, char **args);
int tproxy_parse_global_manager(const char *file, int linenum, char **args);

static inline void
tproxy_housekeeping() {
    nst_cache_housekeeping();
    nst_nosql_housekeeping();
}

static inline int
tproxy_check_applet(hpx_stream_t *s, hpx_channel_t *req, hpx_proxy_t *px) {
    return nst_manager(s, req, px) || nst_nosql_check_applet(s, req, px);
}

void tproxy_handle_chroot();

#endif /* _tproxy_H */
