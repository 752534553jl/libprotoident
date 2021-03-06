/*
 *
 * Copyright (c) 2011-2016 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libprotoident.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"


static inline bool match_cw_09(uint32_t payload, uint32_t len) {

        if (len < 1300) {
                return false;
        }

        if (MATCH(payload, 0x09, 0x0b, 0x0d, 0xd0)) {
                return true;
        }
        if (MATCH(payload, 0x09, 0x0b, 0x00, 0x80)) {
                return true;
        }
        return false;
}

static inline bool match_cw_0a(uint32_t payload, uint32_t len) {

        if (len < 1300) {
                return false;
        }

        if (MATCHSTR(payload, "\x0a\x00\xff\xff")) {
                return true;
        }
        return false;
}

static inline bool match_contract_wars(lpi_data_t *data, lpi_module_t *mod UNUSED) {

        if (match_cw_09(data->payload[0], data->payload_len[0])) {
                if (match_cw_0a(data->payload[1], data->payload_len[1])) {
                        return true;
                }
        }

        if (match_cw_09(data->payload[1], data->payload_len[1])) {
                if (match_cw_0a(data->payload[0], data->payload_len[0])) {
                        return true;
                }
        }

	return false;
}

static lpi_module_t lpi_contract_wars = {
	LPI_PROTO_UDP_CONTRACT_WARS,
	LPI_CATEGORY_GAMING,
	"ContractWars",
	50,
	match_contract_wars
};

void register_contract_wars(LPIModuleMap *mod_map) {
	register_protocol(&lpi_contract_wars, mod_map);
}

