/* Ver archivo LICENSE para detalles de copyright y licencia. */

#include <X11/Xresource.h>
#include <X11/XF86keysym.h>
void reload_xresources(const Arg *arg);

/* audio */
static const char *volupcmd[]   = { "sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ +5% && pkill -RTMIN+10 dwmblocks", NULL };
static const char *voldowncmd[] = { "sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ -5% && pkill -RTMIN+10 dwmblocks", NULL };
static const char *mutecmd[]    = { "sh", "-c", "pactl set-sink-mute @DEFAULT_SINK@ toggle && pkill -RTMIN+10 dwmblocks", NULL };

/* espaciado */
static int gappih  = 6;
static int gappiv  = 6;
static int gappoh  = 8;
static int gappov  = 8;
static int smartgaps = 1;

/* apariencia */
static unsigned int borderpx   = 2;   /* borde en píxeles de las ventanas */
static unsigned int snap       = 32;  /* snap en píxeles */
static int showbar             = 1;   /* 0 oculta la barra */
static int topbar              = 1;   /* 0 pone la barra abajo */
static int swallowfloating     = 0;
static const char *fonts[]     = { "JetBrains Mono:size=11", "JoyPixels:pixelsize=11:antialias=true:autohint=true" };
static const char dmenufont[]  = "JetBrains Mono:size=11";
static char normbgcolor[]      = "#1a0000";
static char normbordercolor[]  = "#330000";
static char normfgcolor[]      = "#888888";
static char selfgcolor[]       = "#ff4444";
static char selbordercolor[]   = "#ff0000";
static char selbgcolor[]       = "#1a0000";

static const ResourcePref resources[] = {
	{ "normbgcolor",     STRING, &normbgcolor },
	{ "normbordercolor", STRING, &normbordercolor },
	{ "normfgcolor",     STRING, &normfgcolor },
	{ "selbgcolor",      STRING, &selbgcolor },
	{ "selbordercolor",  STRING, &selbordercolor },
	{ "selfgcolor",      STRING, &selfgcolor },
};

static const char *colors[][3] = {
	/*               fg           bg           borde           */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* etiquetas */
static const char *tags[] = { "\uf4fb", "\uf4ba", "\uf26b", "\uf1d8", "\uf544", "\uf001", "\uf4d8", "\uf55f", "\uf54c" };

static const Rule rules[] = {
	/* clase              instancia título          máscara    flotante    terminal    noswallow  monitor */
	{ "TelegramDesktop",  NULL,     NULL,           0,         1,          0,          0,         -1 },
	{ "obs",              NULL,     NULL,           0,         1,          0,          0,         -1 },
	{ "Lutris",           NULL,     NULL,           0,         1,          0,          0,         -1 },
	{ "firefox",          NULL,     NULL,           0,         0,          0,          0,         -1 },
	{ "St",               NULL,     NULL,           0,         0,          1,          0,         -1 },
	{ NULL,               NULL,     "Event Tester", 0,         0,          0,          1,         -1 }, /* xev */
	{ NULL,               NULL,     "calendar",     0,         1,          0,          1,         -1 }, /* popup calendario */
};

/* distribuciones */
static float mfact              = 0.55; /* proporción del área maestra [0.05..0.95] */
static int nmaster              = 1;    /* cantidad de clientes en el área maestra */
static int resizehints          = 1;    /* 1 respeta size hints al redimensionar en mosaico */
static const int lockfullscreen = 1;    /* 1 fuerza el foco en ventana fullscreen */
static const int refreshrate    = 120;  /* tasa de refresco (por segundo) al mover/redimensionar */

static const Layout layouts[] = {
	/* símbolo  función de distribución */
	{ "[]=",    tile },    /* primera entrada es la predeterminada */
	{ "><>",    NULL },    /* sin función = comportamiento flotante */
	{ "[M]",    monocle },
};

/* definición de teclas */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* macro para ejecutar comandos de shell (estilo pre dwm-5.0) */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* comandos */
static char dmenumon[2]            = "0"; /* monitor para dmenu, modificado en spawn() */
static const char *dmenucmd[]      = { "/bin/sh", "-c", "$HOME/scripts/dmenu.sh", NULL };
static const char *flamecmd[]      = { "flameshot", "gui", NULL };
static const char *lockcmd[]       = { "lock", NULL };
static const char *termcmd[]       = { "/bin/sh", "-c", "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
    /* modificador                  tecla      función         argumento */
    { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = flamecmd } },
    { MODKEY|ControlMask,           XK_s,      spawn,          SHCMD("mkdir -p ~/pix/screenshots && flameshot full -p ~/pix/screenshots/") },
    { MODKEY|ShiftMask,             XK_i,      spawn,          {.v = lockcmd } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_g,      togglebar,      {0} },
    { MODKEY,                       XK_f,      zoom,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_r,      togglefloating, {0} },
    { MODKEY,                       XK_t,      setlayout,      {0} },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_minus,  setgapswrapper, {.i = -1 } },
    { MODKEY,                       XK_equal,  setgapswrapper, {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,  setgapswrapper, {.i = 0  } },
    { MODKEY,                       XK_apostrophe, togglescratch, {.v = scratchpadcmd } },
    { MODKEY,                       XK_F5,     reload_xresources, {.v = NULL } },
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ControlMask,           XK_q,      quit,           {.i = 1} }, /* reiniciar */
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { 0, XF86XK_AudioLowerVolume,              spawn,          {.v = voldowncmd } },
    { 0, XF86XK_AudioMute,                     spawn,          {.v = mutecmd } },
    { 0, XF86XK_AudioRaiseVolume,              spawn,          {.v = volupcmd } },
};

/* definición de botones */
/* click puede ser ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin o ClkRootWin */
static Button buttons[] = {
    /* click                máscara         botón           función         argumento */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        spawn,          SHCMD("$HOME/.local/bin/calendar-popup") },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
