#include <vxworks.h>
#include <ioLib.h>
#include <stdio.h>

#include "firmware.h"
#include "firmware/fio.h"

#include "main.h"

#include "display.h"
#include "languages.h"
#include "snapshots.h"
#include "utils.h"
#include "debug.h"

#include "cmodes.h"

cmodes_config_t cmodes_default = {
	recall_camera   : TRUE,
	recall_400plus  : TRUE,
	recall_ordering : FALSE,
	recall_settings : FALSE,
	recall_image    : TRUE,
	recall_cfn      : TRUE,
};

cmodes_config_t cmodes_config;

int amode_read   (AE_MODE ae_mode, snapshot_t *snapshot);
int amode_write  (AE_MODE ae_mode);
int amode_delete (AE_MODE ae_mode);

void cmode_recall_apply(int full);

void get_cmode_filenames(char filenames[][FILENAME_LENGTH], int cmode_id);
void get_amode_filenames(char filenames[][FILENAME_LENGTH], AE_MODE ae_mode);

void cmodes_read() {
	int   id;
	int   version =  0;
	int file    = -1;

	cmodes_config_t buffer;

	for (id = 0; id < CMODES_MAX; id ++) {
		sprintf(cmodes_default.names[id], "%s %X", LP_WORD(L_S_CMODE_NAME), id);
		cmodes_default.order[id] = id;
	}

	for (id = 0; id < CMODES_MODES; id ++) {
		cmodes_default.assign[id] = CMODE_NONE;
	}

	cmodes_config = cmodes_default;

	if ((file = FIO_OpenFile(MKPATH_NEW(CMODES_CONFIG), O_RDONLY)) == -1)
		if ((file = FIO_OpenFile(MKPATH_OLD(CMODES_CONFIG), O_RDONLY)) == -1)
			goto end;

	if (FIO_ReadFile(file, &version, sizeof(version)) != sizeof(version))
		goto end;

	if (version != SNAPSHOT_VERSION)
		goto end;

	if (FIO_ReadFile(file, &buffer, sizeof(buffer)) != sizeof(buffer))
		goto end;

	cmodes_config = buffer;

end:
	if (file != -1)
		FIO_CloseFile(file);
}

void cmodes_write() {
	const int version = SNAPSHOT_VERSION;
	int file = -1;

	if ((file = FIO_OpenFile(MKPATH_NEW(CMODES_CONFIG), O_CREAT | O_WRONLY)) == -1)
		if (status.folder_exists || (file = FIO_OpenFile(MKPATH_OLD(CMODES_CONFIG), O_CREAT | O_WRONLY)) == -1)
			goto end;

	FIO_WriteFile(file, (void*)&version,        sizeof(version));
	FIO_WriteFile(file, (void*)&cmodes_config, sizeof(cmodes_config));
	FIO_CloseFile(file);

end:
	if (file != -1)
		FIO_CloseFile(file);
}

void cmodes_restore() {
	cmodes_config = cmodes_default;

	cmodes_write();
}

void cmodes_delete() {
	int  id;

	for(id = 0; id < CMODES_MAX; id++)
		cmode_delete(id);
}

int cmode_read(int id, snapshot_t *cmode) {
	char filenames[2][FILENAME_LENGTH];

	get_cmode_filenames(filenames, id);

	return snapshot_read(filenames, cmode);
}

int cmode_write(int id) {
	char filenames[2][FILENAME_LENGTH];

	get_cmode_filenames(filenames, id);

	return snapshot_write(filenames);
}

int cmode_delete(int id) {
	char filenames[2][FILENAME_LENGTH];

	get_cmode_filenames(filenames, id);

	return snapshot_delete(filenames);
}

int amode_read(AE_MODE ae_mode, snapshot_t *mode) {
	char filenames[2][FILENAME_LENGTH];

	get_amode_filenames(filenames, ae_mode);

	return snapshot_read(filenames, mode);
}

int amode_write(AE_MODE ae_mode) {
	char filenames[2][FILENAME_LENGTH];

	get_amode_filenames(filenames, ae_mode);

	return snapshot_write(filenames);
}

int amode_delete(AE_MODE ae_mode) {
	char filenames[2][FILENAME_LENGTH];

	get_amode_filenames(filenames, ae_mode);

	return snapshot_delete(filenames);
}

void cmode_recall() {
	cmode_recall_apply(FALSE);
}

void cmode_apply() {
	cmode_recall_apply(TRUE);
}

void cmode_recall_apply(int full) {
	int current_cmode = get_current_cmode();

	snapshot_t snapshot;

	if(AE_IS_CREATIVE(status.main_dial_ae)) {
		// Update current status
		status.cmode_active = FALSE;

		// Try to find a mode file, and load it
		if (amode_read(status.main_dial_ae, &snapshot)) {
			amode_delete(status.main_dial_ae);
			snapshot_apply(&snapshot);
		}
	} else {
		// Only if a custom mode was loaded, and we can read it back
		if (current_cmode != CMODE_NONE && cmode_read(current_cmode, &snapshot)) {
			// Update current status
			status.cmode_active = TRUE;

			// First revert to AE mode
			snapshot_recall(&snapshot);

			if (full) {
				// Save current mode before overwriting other parameters
				if (!status.cmode_active)
					amode_write(DPData.ae);

				// Then apply full custom mode
				snapshot_apply(&snapshot);
			}
		} else {
			// Update current status
			status.cmode_active = FALSE;
		}
	}
}

void get_cmode_filenames(char filenames[][FILENAME_LENGTH], int cmode_id) {
	sprintf(filenames[0], "%s/%s/" CMODES_FILE, FOLDER_ROOT, FOLDER_NAME, cmode_id);
	sprintf(filenames[1], "%s/"    CMODES_FILE, FOLDER_ROOT, cmode_id);
}

void get_amode_filenames(char filenames[][FILENAME_LENGTH], AE_MODE ae_mode) {
	char id;

	switch (ae_mode) {
	case AE_MODE_P:
		id = 'P';
		break;
	case AE_MODE_TV:
		id = 'T';
		break;
	case AE_MODE_AV:
		id = 'A';
		break;
	case AE_MODE_M:
		id = 'M';
		break;
	case AE_MODE_ADEP:
		id = 'D';
		break;
	default:
		// This should never happen...
		id = 'X';
		break;
	}

	sprintf(filenames[0], "%s/%s/" AMODES_FILE, FOLDER_ROOT, FOLDER_NAME, id);
	sprintf(filenames[1], "%s/"    AMODES_FILE, FOLDER_ROOT, id);
}

int get_current_cmode() {
	if (AE_IS_AUTO(status.main_dial_ae))
		return cmodes_config.assign[status.main_dial_ae - AE_MODE_AUTO];
	else
		return CMODE_NONE;
}

void set_current_cmode(int cmode_id) {
	status.cmode_active = (cmode_id != CMODE_NONE);

	if (AE_IS_AUTO(status.main_dial_ae))
		cmodes_config.assign[status.main_dial_ae - AE_MODE_AUTO] = cmode_id;
}

