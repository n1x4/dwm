/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-ohsnap-bold-*-*-*-12-*-*-*-*-*-*-*";
static const char colors[MAXCOLORS][ColLast][8] = {
	/* border     fg         bg       */
	{ "#222222", "#222222", "#424242" }, /* 0 = normal */
	{ "#876cbe", "#DDDDDD", "#424242" }, /* 1 = selected */
	{ "#FF2882", "#FFFFFF", "#424242" }, /* 2 = urgent */
	{ "#222222", "#b4aa30", "#424242" }, /* 3 = green */
	{ "#222222", "#c7a551", "#424242" }, /* 4 = yellow */
	{ "#222222", "#9fa590", "#424242" }, /* 5 = cyan */
	{ "#222222", "#9c818e", "#424242" }, /* 6 = magenta */
	{ "#222222", "#424242", "#424242" }, /* 7 = grey */
};
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool clicktofocus      = True;     /* Change focus only on click */
static const Bool viewontag         = True;     /* Switch view on tag switch */

static const Rule rules[] = {
	/* class          instance     title       tags mask     isfloating   iscentred   monitor */
	{ "Gimp",         NULL,        NULL,       0,            True,        False,      -1 },
	{ "MPlayer",      NULL,        NULL,       0,            True,        True,       -1 },
	{ "mplayer2",     NULL,        NULL,       0,            True,        True,       -1 },
	{ "Vlc",          NULL,        NULL,       0,            True,        True,       -1 },
	{ "Chromium",     NULL,        NULL,       1 << 5,       True,        True,       -1 },
        { "Firefox",      NULL,        NULL,       1 << 5,       True,        True,       -1 },
	{ "Firefox",      "Navigator", NULL,       1 << 5,       False,       False,      -1 },
};

/* layout(s) */
static const float mfact      = 0.5;   /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[F]",      NULL },        /* first entry is default */
	{ "[M]",      monocle },
	{ "[T]",      tile },        /* no layout function means floating behavior */
	{ "[B]",      bstack },
	{ "[G]",      gaplessgrid },
};

/* tagging */
static const Tag tags[] = {
	/* name       layout           mfact    nmaster */
	{ "main",     &layouts[0],     -1,      -1 },
	{ "term",     &layouts[0],     -1,      -1 },
	{ "misc",     &layouts[0],     -1,      -1 },
	{ "trnt",     &layouts[0],     -1,      -1 },
	{ "vid",      &layouts[0],     -1,      -1 },
	{ "http",     &layouts[0],     -1,      -1 },
};

/* key definitions */
/*#define ALTKEY Mod1Mask*/
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char terminal[]       = "urxvt";
static const char scratchpadname[] = "scratchy";
static const char *dmenucmd[]      = { "dmenu_run", "-i", "-p", "Run command:", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]       = { terminal, NULL };
static const char *tmuxcmd[]       = { terminal, "-e", "tmuxa", NULL };
static const char *scratchpadcmd[] = { terminal, "-name", scratchpadname, "-geometry", "80x20", NULL };
static const char *volmcmd[]       = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *voldcmd[]       = { "amixer", "-q", "sset", "Master", "1-", "unmute", NULL };
static const char *volucmd[]       = { "amixer", "-q", "sset", "Master", "1+", "unmute", NULL };
static const char *screenshotcmd[] = { "printscreen", NULL };

static Key keys[] = {
	/* modifier                     key         function        argument */
	{ MODKEY,                       XK_p,       spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_Return,  spawn,          {.v = tmuxcmd } },
	{ MODKEY,                       XK_x,       togglescratch,  {.v = scratchpadcmd } },
	{ 0,                            0x1008ff12, spawn,          {.v = volmcmd } },
	{ 0,                            0x1008ff11, spawn,          {.v = voldcmd } },
	{ 0,                            0x1008ff13, spawn,          {.v = volucmd } },
	{ 0,                            XK_Print,   spawn,          {.v = screenshotcmd } },
	{ MODKEY|ShiftMask,             XK_m,       togglemax,      {0} },
	{ MODKEY|ShiftMask,             XK_b,       togglebar,      {0} },
	{ MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,       pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,       pushup,         {0} },
	{ MODKEY,                       XK_a,       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_z,       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.01} },
	{ MODKEY,                       XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ MODKEY,                       XK_Tab,     focusurgent,    {0} },
	{ MODKEY|ShiftMask,             XK_c,       killclient,     {0} },
	{ MODKEY,                       XK_f,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_t,       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,       setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_g,       setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,    cycle,          {.i = -1 } },
	{ MODKEY,                       XK_Right,   cycle,          {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,    tagcycle,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,   tagcycle,       {.i = +1 } },
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	{ MODKEY|ShiftMask,             XK_q,        quit,         {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1} },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        cycle,          {.i = -1} },
	{ ClkTagBar,            0,              Button5,        cycle,          {.i = +1} },
};
