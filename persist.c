#include <vxworks.h>
#include <ioLib.h>

#include "firmware.h"
#include "firmware/fio.h"

#include "main.h"
#include "exposure.h"
#include "scripts.h"

#include "persist.h"

persist_t persist = {
	ev_comp     : EC_ZERO,
	last_script : SCRIPT_NONE,
};

int persist_read(void) {
	int result  = FALSE;
	int file    = -1;
	int   version = 0;

	persist_t persistent_buffer;

	if ((file = FIO_OpenFile(MKPATH_NEW(PERSIST_FILENAME), O_RDONLY)) == -1)
		if ((file = FIO_OpenFile(MKPATH_OLD(PERSIST_FILENAME), O_RDONLY)) == -1)
			goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != PERSIST_VERSION)
		goto end;

	if (FIO_ReadFile(file, &persistent_buffer, sizeof(persistent_buffer)) != sizeof(persistent_buffer))
		goto end;

	persist = persistent_buffer;
	result  = TRUE;

end:
	if (file != -1)
		FIO_CloseFile(file);

	return result;
}

void persist_write(void) {
	const int version = PERSIST_VERSION;
	int file = -1;

	if ((file = FIO_OpenFile(MKPATH_NEW(PERSIST_FILENAME), O_CREAT | O_WRONLY)) == -1)
		if (status.folder_exists || (file = FIO_OpenFile(MKPATH_OLD(PERSIST_FILENAME), O_CREAT | O_WRONLY)) == -1)
			goto end;

	FIO_WriteFile(file, (void*)&version, sizeof(version));
	FIO_WriteFile(file, &persist, sizeof(persist));

end:
	if (file != -1)
		FIO_CloseFile(file);
}
