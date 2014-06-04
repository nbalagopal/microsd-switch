/*
 * Copyright (C) 2014  Joel Fernandes <agnel.joel@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Description:
 * This program is used to switch between host-mode and target-mode
 * on a MicroSD switcher controlled with an FTDI cable or device.
 */

#include <stdio.h>
#include <ftdi.h>
#include <string.h>

#define ENA 0x08  /* CTS (brown wire on FTDI cable) */

int main(int argc, char **argv)
{
	unsigned char c = 0, serial[10];
	struct ftdi_context ftdic;
	int ret = 0;

	/* Initialize context for subsequent function calls */
	ftdi_init(&ftdic);

	if (argc != 3) {
		printf("Usage: switch <serial-no> <host|target>\n");
		ret = 1;
		goto die;
	}

	if(!strcmp(argv[2], "host")) {
		c ^= ENA;
	} else if(!strcmp(argv[2], "target")) {
		;
	} else {
		printf("Usage: switch <serial-no> <host|target>\n");
		ret = 2;
		goto die;
	}

	strncpy(serial, argv[1], 10);

	/* Open FTDI device based host FT232R vendor/product IDs and serial no. */
	if(ftdi_usb_open_desc(&ftdic, 0x0403, 0x6001, NULL, serial) < 0) {
		printf("Can't open device\n");
		ret = 3;
		goto die;
	}

	printf("FTDI device serial no: %s opened successfully\n", argv[1]);

	/* Enable bitbang mode with a single output line */
	ftdi_enable_bitbang(&ftdic, ENA);

	ftdi_write_data(&ftdic, &c, 1);

	sleep(1);

	ftdi_usb_close(&ftdic);
die:
	return ret;
}
