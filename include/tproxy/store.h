/*
 * include/tproxy/store.h
 * This file defines everything related to tproxy store.
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

#ifndef _tproxy_STORE_H
#define _tproxy_STORE_H

#include <tproxy/common.h>
#include <tproxy/memory.h>
#include <tproxy/disk.h>


typedef struct nst_store {
    nst_memory_t                memory;
    nst_disk_t                  disk;
} nst_store_t;


static inline int
nst_store_init(nst_store_t *store, hpx_ist_t root, nst_shmem_t *shmem, int clean_temp, void *data) {

    if(nst_memory_init(&store->memory, shmem) != NST_OK) {
        return NST_ERR;
    }

    if(nst_disk_init(&store->disk, root, shmem, clean_temp, data) != NST_OK) {
        return NST_ERR;
    }

    return NST_OK;
}

void nst_store_memory_sync_disk(nst_core_t *core);

static inline int
nst_store_memory_on(uint8_t t) {
    return t & NST_STORE_MEMORY_ON;
}

static inline int
nst_store_memory_off(uint8_t t) {
    return t & NST_STORE_MEMORY_OFF;
}

static inline int
nst_store_disk_on(uint8_t t) {
    return t & NST_STORE_DISK_ON;
}

static inline int
nst_store_disk_off(uint8_t t) {
    return t & NST_STORE_DISK_OFF;
}

static inline int
nst_store_disk_sync(uint8_t t) {
    return t & NST_STORE_DISK_SYNC;
}

#endif /* _tproxy_STORE_H */
