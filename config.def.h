/* See LICENSE file for copyright and license details. */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>

#include "sfm.h"

/* Theme colors come from the environment at runtime.
 * Single source of truth: /usr/local/bin/set_system_theme, which writes
 * ~/.Xresources.d/system-colors and exports the pywal/wallust/base16 palette:
 * BACKGROUND, FOREGROUND, CURSOR, COLOR0..COLOR15 plus semantic aliases
 * ACCENT (=COLOR4), BORDER (=COLOR8), URGENT (=COLOR1), SELECTION, MUTED.
 * sfm.c:theme_init() overwrites the foreground/background of the pairs below
 * with truecolor values when a palette is found; the values here are
 * compile-time fallbacks. `pkill -HUP sfm` reloads the palette.
 * SYSTEM_COLORS_XRES overrides the Xresources file path. */

/* color pairs                            fg   bg   attr*/
static ColorPair color_blk       = { .fg = 95,  .bg = 0,   .attr = NORM };
static ColorPair color_brlnk     = { .fg = 0,   .bg = 9,   .attr = NORM };
static ColorPair color_chr       = { .fg = 94,  .bg = 0,   .attr = NORM };
static ColorPair color_dir       = { .fg = 31,  .bg = 0,   .attr = NORM };
static ColorPair color_exec      = { .fg = 91,  .bg = 0,   .attr = NORM };
static ColorPair color_sock      = { .fg = 92,  .bg = 0,   .attr = NORM };
static ColorPair color_ifo       = { .fg = 93,  .bg = 0,   .attr = NORM };
static ColorPair color_lnk       = { .fg = 96,  .bg = 0,   .attr = NORM };
static ColorPair color_other     = { .fg = 90,  .bg = 0,   .attr = NORM };
static ColorPair color_file      = { .fg = 243, .bg = 0,   .attr = NORM };

static ColorPair color_frame     = { .fg = 237, .bg = 0,   .attr = NORM };
static ColorPair color_panell    = { .fg = 166, .bg = 233, .attr = BOLD };
static ColorPair color_panelr    = { .fg = 5,   .bg = 233, .attr = BOLD };
static ColorPair color_status    = { .fg = 243, .bg = 0,   .attr = NORM };

static ColorPair color_search    = { .fg = 15,  .bg = 104, .attr = NORM };
static ColorPair color_selected  = { .fg = 21,  .bg = 118, .attr = NORM };

static ColorPair color_normal    = { .fg = 33,  .bg = 0,   .attr = NORM };
static ColorPair color_warn      = { .fg = 220, .bg = 0,   .attr = NORM };
static ColorPair color_err       = { .fg = 124, .bg = 0,   .attr = BOLD };


/* commands */
#if defined(__linux__)
#define CHFLAG "chattr"
#else
#define CHFLAG "chflags"
#endif
static const char *rm_cmd[]      = { "rm", "-rf" }; /* delete */
static const char *cp_cmd[]      = { "cp", "-r" }; /* copy */
static const char *chown_cmd[]   = { "chown", "-R" }; /* change file owner and group */
static const char *chmod_cmd[]   = { "chmod" }; /* change file mode bits */
static const char *chflags_cmd[] = { CHFLAG }; /* change file flags */
static const char *mv_cmd[]      = { "mv" }; /* move */
static const char delconf[]      = "yes";

static const size_t rm_cmd_len      = LEN(rm_cmd);
static const size_t cp_cmd_len      = LEN(cp_cmd);
static const size_t chown_cmd_len   = LEN(chown_cmd);
static const size_t chmod_cmd_len   = LEN(chmod_cmd);
static const size_t chflags_cmd_len = LEN(chflags_cmd);
static const size_t mv_cmd_len      = LEN(mv_cmd);
static const size_t delconf_len     = LEN(delconf);

/* bookmarks */
static const char root[]   = "/";

/* software */
static const char *mpv[]          = { "mpv", "--fullscreen" };
static const char *sxiv[]         = { "sxiv" };
static const char *mupdf[]        = { "mupdf", "-I" };
static const char *libreoffice[]  = { "libreoffice" };
static const char *gimp[]         = { "gimp" };
static const char *r2[]           = { "r2", "-c", "vv" };

/* extensions*/
static const char *images[] = { "bmp", "jpg", "jpeg", "png", "gif", "webp", "xpm" };
static const char *pdf[]    = { "epub", "pdf" };
static const char *arts[]   = { "xcf" };
static const char *obj[]    = { "o", "a", "so" };
static const char *videos[] = { "avi", "flv", "wav", "webm", "wma", "wmv",
                                "m2v", "m4a", "m4v", "mkv", "mov", "mp3",
                                "mp4", "mpeg", "mpg" };
static const char *docs[]   = { "odt", "doc", "docx", "xls", "xlsx", "odp",
                                "ods", "pptx", "odg" };

static Rule rules[] = {
	RULE(videos, mpv,         DontWait),
	RULE(images, sxiv,        DontWait),
	RULE(pdf,    mupdf,       DontWait),
	RULE(docs,   libreoffice, DontWait),
	RULE(arts,   gimp,        DontWait),
	RULE(obj,    r2,          Wait)
};

/* normal keys */
static Key nkeys[] = {
	/* key                 function          arg */
	{ 'j',                 move_cursor,      { .i = +1 }              },
	{ XK_DOWN,             move_cursor,      { .i = +1 }              },
	{ 'k',                 move_cursor,      { .i = -1 }              },
	{ XK_UP,               move_cursor,      { .i = -1 }              },
	{ XK_CTRL('u'),        move_cursor,      { .i = -5 }              },
	{ XK_CTRL('d'),        move_cursor,      { .i = +5 }              },
	{ '{',                 move_cursor,      { .i = -10 }             },
	{ '}',                 move_cursor,      { .i = +10 }             },
	{ 'l',                 open_entry,       { 0 }                    },
	{ 'h',                 cd_to_parent,     { 0 }                    },
	{ 'q',                 quit,             { 0 }                    },
	{ 'G',                 move_bottom,      { 0 }                    },
	{ 'g',                 move_top,         { 0 }                    },
	{ XK_SPACE,            switch_pane,      { 0 }                    },
	{ '.',                 toggle_dotfiles,  { 0 }                    },
	{ XK_CTRL('r'),        refresh,          { 0 }                    },
	{ XK_CTRL('f'),        create_new_file,  { 0 }                    },
	{ XK_CTRL('m'),        create_new_dir,   { 0 }                    },
	{ 'd',                 delete_entry,     { 0 }                    },
	{ 'y',                 copy_entries,     { 0 }                    },
	{ 'p',                 paste_entries,    { 0 }                    },
	{ 'P',                 move_entries,     { 0 }                    },
	{ 'v',                 visual_mode,      { 0 }                    },
	{ XK_ESC,              normal_mode,      { 0 }                    },
	{ 's',                 select_cur_entry, { .i = InvertSelection } },
	{ 'x',                 select_all,       { .i = DontSelect }      },
	{ 'a',                 select_all,       { .i = Select }          },
	{ 'i',                 select_all,       { .i = InvertSelection } },
	{ '/',                 start_search,     { 0 }                    },
	{ 'n',                 move_to_match,    { .i = NextMatch }       },
	{ 'N',                 move_to_match,    { .i = PrevMatch }       },
};

static const size_t nkeyslen = LEN(nkeys);
//static const size_t ckeyslen = LEN(ckeys);

/* permissions */
static const mode_t new_dir_perm  = S_IRWXU;
static const mode_t new_file_perm = S_IRUSR | S_IWUSR;

/* dotfiles */
static int show_dotfiles = 1;

/* statusbar */
static const char dtfmt[] = "%F %R"; /* date time format */

#endif // CONFIG_H
