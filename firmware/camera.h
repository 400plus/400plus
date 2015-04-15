#ifndef CAMERA_H_
#define CAMERA_H_

// from ML's compiler.h
/** Compile time failure if a structure is not sized correctly */
#define SIZE_CHECK_STRUCT( struct_name, size ) \
	static int __attribute__((unused)) \
	__size_check_##struct_name[ \
		sizeof( struct struct_name ) == size ? 0 : -1 \
	]

struct vram_info_t {
	unsigned char * data;
	int width;
	int pitch;
	int height;
	int number; // the vram number
};

SIZE_CHECK_STRUCT(vram_info_t, 0x14);

typedef struct vram_info_t vram_info_t;
extern vram_info_t VramInfo[2];

struct lens_info_t {
	short id;
	short max_mm;
	short min_mm;
	short not_used;
	char *name;
}__attribute__((packed));

typedef struct lens_info_t lens_info_t;

// DigiProp Data Structure
struct dpr_data_t {              // [*] Used and tested, others unknown
	int ae;                      // 0x0000 [*] [1]
	int metering;                // 0x0004 [*] [2]
	int efcomp;                  // 0x0008 [*] [K]
	int drive;                   // 0x000c     [3]
	int wb;                      // 0x0010 [*] [4]
	int af;                      // 0x0014
	int af_point;                // 0x0018 [*] [5]
	int tv_val;                  // 0x001c [*] [F]
	int av_val;                  // 0x0020
	int av_comp;                 // 0x0024 [*]
	int iso;                     // 0x0028 [*] [J]
	int red_eye;                 // 0x002c
	int ae_bkt;                  // 0x0030 [*]
	int wb_bkt;                  // 0x0034
	int beep;                    // 0x0038 [*]
	int color_temp;              // 0x003c [*]
	int auto_power_off;          // 0x0040     [6]
	int view_type;               // 0x0044
	int review_time;             // 0x0048     [7]
	int auto_rotate;             // 0x004c     [8]
	int lcd_brightness;          // 0x0050     [9]
	int date_time;               // 0x0054     [A]
	int file_numbering;          // 0x0058     [B]
	int language;                // 0x005c [*]
	int video_system;            // 0x0060     [C]
	int picture_style_mode;      // 0x0064
	int histogram;               // 0x0068     [D]
	int disp_afpoint;            // 0x006c
	int color_space;             // 0x0070     [E]
	int img_format;              // 0x0074 [*] [G]
	int img_size;                // 0x0078 [*] [H]
	int img_quality;             // 0x007c [*] [I]
	int cfmenupos;               // 0x0080
	int menupos;                 // 0x0084
	int wbcomp_gm;               // 0x0088
	int wbcomp_ab;               // 0x008c
	int forbid_rel;              // 0x0090 - forbid release, shoot w/o CF
	int cf_set_button_func;      // 0x0094
	int cf_nr_for_long_exposure; // 0x0098
	int cf_efav_fix_x;           // 0x009c
	int cf_afael_active_button;  // 0x00a0
	int cf_emit_aux;             // 0x00a4 [*]
	int cf_explevel_inc_third;   // 0x00a8 [*]
	int cf_emit_flash;           // 0x00ac [*]
	int cf_extend_iso;           // 0x00b0 [*]
	int cf_aeb_sequence;         // 0x00b4
	int cf_si_indicate;          // 0x00b8
	int cf_menu_pos;             // 0x00bc
	int cf_mirror_up_lock;       // 0x00c0 [*]
	int cf_fpsel_method;         // 0x00c4
	int cf_flash_metering;       // 0x00c8
	int cf_flash_sync_rear;      // 0x00cc [*]
	int cf_safety_shift;         // 0x00d0 [*]
	int cf_lens_button;          // 0x00d4
	int cf_original_eval;        // 0x00d8
	int cf_qr_magnify;           // 0x00dc
	int batt_bclevel;            // 0x00e0
	int batt_type;               // 0x00e4
	int print_user_property;     // 0x00e8 (s/int/void */)
	int printer_property;        // 0x00ec (s/int/void */)
	int cluster_size;            // 0x00f0
	int remain_cluster;          // 0x00f4
	int file_id;                 // 0x00f8
	int avo;                     // 0x00fc
	int avmax;                   // 0x0100
	int ef_lens_exist;           // 0x0104
	int avail_shot;              // 0x0108
	int qrev_imgprop;            // 0x010c
	int printer_connect_type;    // 0x0110
	int mwbdat_red;              // 0x0114
	int mwbdat_green1;           // 0x0118
	int mwbdat_green2;           // 0x011c
	int mwbdat_blue;             // 0x0120
	int videojack_connect;       // 0x0124
	int incomp_image;            // 0x0128
	int status_busy_flag;        // 0x012c [*]
	int special_bc_result;       // 0x0130
	int reset_offtimer;          // 0x0134
	int printer_device_property; // 0x0138 (s/int/void */)
	int printer_job_property;    // 0x013c (s/int/void */)
	int dpof_setting;            // 0x0140
	int gui_mode;                // 0x0144
	int dp_request_return;       // 0x0148
	int commadp_chg_config;      // 0x014c
	int play_jump_type;          // 0x0150
	int capability_setting;      // 0x0154
	int selected_af_mode;        // 0x0158
	int disable_ui_lock;         // 0x015c
	int isd_style_flag;          // 0x0160
	int ptp;                     // 0x0164
	int playback_file_id;        // 0x0168
	int playback_file_id_pos;    // 0x016c
	int usb_connect_type;        // 0x0170
	int face_sensor_disable;     // 0x0174
	int field_178;               // 0x0178
	int field_17C;               // 0x017c
	int field_180;               // 0x0180
	int field_184;               // 0x0184
	int cf_tft_on_power_on;      // 0x0188
	int field_18C;               // 0x018c
	int field_190;               // 0x0190
};

//  0x194 is the number in the FW when it comes to DPR (as it's 0x198 too, they go together always)
SIZE_CHECK_STRUCT(dpr_data_t, 0x194);

typedef struct dpr_data_t dpr_data_t;

extern dpr_data_t DPData;
extern lens_info_t LensID;

extern int is_release_permitted; // can we shoot ?

// [1] Values for "ae"
typedef enum {
	AE_MODE_P = 0x00,
	AE_MODE_TV = 0x01,
	AE_MODE_AV = 0x02,
	AE_MODE_M = 0x03,
	AE_MODE_ADEP = 0x05,
	AE_MODE_AUTO = 0x08,
	AE_MODE_NIGHT = 0x09,
	AE_MODE_SPORTS = 0x0A,
	AE_MODE_PORTRAIT = 0x0B,
	AE_MODE_LANDSCAPE = 0x0C,
	AE_MODE_CLOSEUP = 0x0D,
	AE_MODE_FLASHOFF = 0x0E
} AE_MODE;

// [2] Values for "metering"
typedef enum {
	METERING_MODE_EVAL = 0, METERING_MODE_SPOT = 3
} METERING_MODE;

// [3] Values for "drive"
typedef enum {
	DRIVE_MODE_SINGLE = 0, DRIVE_MODE_BURST = 1, DRIVE_MODE_TIMER = 2
} DRIVE_MODE;

// [4] Values for "wb"
typedef enum {
	WB_MODE_AUTO = 0x00,
	WB_MODE_DAYLIGHT = 0x01,
	WB_MODE_COUDY = 0x02,
	WB_MODE_TUNGSTEN = 0x03,
	WB_MODE_FLUORESCENT = 0x04,
	WB_MODE_FLASH = 0x05,
	WB_MODE_CUSTOM = 0x06,
	WB_MODE_SHADE = 0x07,
	WB_MODE_COLORTEMP = 0x08
} WB_MODE;

// [5] Values for "af_point" (can be ORed together to form patterns)
typedef enum {
	AF_POINT_C = 0x0001, // Center
	AF_POINT_T = 0x0002, // Top
	AF_POINT_B = 0x0004, // Bottom
	AF_POINT_TL = 0x0008, // Top-left
	AF_POINT_TR = 0x0010, // Top-right
	AF_POINT_BL = 0x0020, // Bottom-left
	AF_POINT_BR = 0x0040, // Bottom-right
	AF_POINT_L = 0x0080, // Left
	AF_POINT_R = 0x0100 // Right
} AF_POINT;

// [6] Values for "auto_power_off"
//     Number of seconds to wait, 0x00 for OFF

// [7] Values for "review_time"
//     Number of seconds to wait, 0x00 for OFF, 0xFF for HOLD
typedef enum {
	REVIEW_OFF  = 0x00,
	REVIEW_HOLD = 0xFF
} REVIEW_TIME;

// [8] Values for "auto_rotate"
typedef enum {
	AUTO_ROTATE_OFF = 0x00,
	AUTO_ROTATE_COMP_CAMERA = 0x01,
	AUTO_ROTATE_COMP = 0x02
} AUTO_ROTATE_MODE;

// [9] Values for "lcd_brightness"
//     Brightness in range 1 to 7

// [A] Values for "date_time"
typedef enum {
	DATE_TIME_YYMMDD = 0x01, DATE_TIME_DDMMYY = 0x02, DATE_TIME_MMDDYY = 0x03
} DATE_TIME_FORMAT;

// [B] Values for "file_numbering"
typedef enum {
	FILE_NUMBERING_CONT = 0x00, FILE_NUMBERING_AUTO = 0x01
} FILE_NUMBERING;

// [C] Values for "video_system"
typedef enum {
	VIDEO_SYSYEM_PAL = 0x00, VIDEO_SYSTEM_NTSC = 0x01
} VIDEO_SYSTEM;

// [D] Values for "histogram"
typedef enum {
	HISTOGRAM_BRIGHTNESS = 0x00, HISTOGRAM_RGB = 0x01
} HISTOGRAM_MODE;

// [E] Values for "color_space"
typedef enum {
	COLOR_SPACE_SRGB = 0x00, COLOR_SPACE_ADOBE = 0x01
} COLOR_SPACE;

// [F] Values for "tv_val"
//     0x10 => 30", ..., 0x98 => 1/4000
typedef enum {
	TV_VAL_BULB = 0x0C // Internal code for BULB mode
} TV_VAL;

// [G] Values for "img_format"
typedef enum {
	IMG_FORMAT_JPG = 0x01, IMG_FORMAT_RAW = 0x02
} IMG_FORMAT;

// [H] Values for "img_quality"
typedef enum {
	IMG_QUALITY_HIGH = 0x00, IMG_QUALITY_LOW = 0x01
} IMG_QUALITY;

// [I] Values for "img_size"
typedef enum {
	IMG_SIZE_L = 0x00, IMG_SIZE_M = 0x01, IMG_SIZE_S = 0x02
} IMG_SIZE;

// [J] ISO encoding
// Value xxyy.yzzz means:
//    xx = 01 always
//   yyy = Base ISO: 001 => 100, 010 => 200, 011 => 400, ...
//   zzz = Int. ISO: 000 => BaseISO, 001 => BaseISO + 1/8EV, 010 => BaseISO + 2/8EV, ...

// [K] EV encoding
// Value xyyy.yzzz means:
//      x = Sign: 0 => + , 1 => - (use two's complement for y and z)
//   yyyy = Base value: 0000 => 0EV, 0001 => 1EV, ...
//    yyy = Int. value: 000 => BaseEV, 011 => BaseEV + 1/3EV, 100 => BaseEV + 1/2EV, 101 => BaseEv + 2/3EV [*]
// [*]: Could this be like [J], so 011 => BaseEV + 3/8EV , 100 => BaseEV + 4/8EV, 101 => BaseEv + 5/8EV?
//      Could we have eight intermediate EV's, instead of three?

extern int shutter_lock;

extern int permit_or_inhibit_release(int);
extern int able_to_release(void); // checks the "is_release_permitted" and "BurstCounter", return 1 if we can shoot

#define AE_IS_AUTO(ae)     (ae) >= AE_MODE_AUTO
#define AE_IS_CREATIVE(ae) (ae) <  AE_MODE_AUTO

#define SELF_TIMER_MS 2000

#endif
