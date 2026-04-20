# dotfiles-freebsd

Advertencia: Esta es mi configuracion privada en FreeBSD 15. Se recomienda utilizarla solo como inspiracion, ya que no hay garantia de que te funcione, se compilo en mi maquina y en mi maquina funciona.

dwm + st + dwmblocks + picom + dunst

Tambien hay algunos scripts utiles para que corran Discord, vms y algunas cosas mas.

<img width="1920" height="1073" alt="image" src="https://github.com/user-attachments/assets/58818d0e-84e0-4cab-934d-3541aa78c85b" />

## Wallpaper

El wallpaper del daemon ASCII esta incluido en `wallpapers/`. Originalmente de [Wallhaven](https://wallhaven.cc).

## Patches

### dwm
- **vanitygaps** — gaps configurables entre ventanas
- **status2d** — colores en la barra de estado via secuencias de escape
- **fancybar** — titulo de la ventana activa en la barra
- **swallow** — las terminales tragan ventanas GUI que spawnean
- **cfacts** — redimensionar ventanas individuales en el stack
- **scratchpad** — terminal flotante con keybind
- **movestack** — mover ventanas arriba/abajo en el stack
- **xresources** — cargar colores y config desde Xresources en caliente

### st
- **HarfBuzz** — renderizado avanzado de fuentes
- **alpha** — transparencia de fondo
- **scrollback** — scroll con teclado/mouse
- **externalpipe** — pipe de output a comandos externos
- **boxdraw** — mejor renderizado de caracteres de linea
- **xresources** — colores desde Xresources

## Dynamic color scheme

El script `scripts/newlook` cambia el wallpaper aleatoriamente y regenera el esquema de colores de todo el entorno usando `pywal`:

1. Elige un wallpaper random de `~/pix/wall/` y lo aplica con `xwallpaper`
2. `pywal` genera una paleta de colores a partir del wallpaper
3. Los colores se mergean via `xrdb` a las variables de dwm
4. `killall -USR1 dwm` recarga los colores en dwm sin reiniciar

La barra de dwm, los bordes de ventana y la terminal (st) cambian de color scheme automaticamente para coincidir con el wallpaper.

## Dependencias

| Programa | Uso |
|---|---|
| `xwallpaper` | fondo de pantalla |
| `pywal` | esquemas de color dinamicos |
| `dmenu` | lanzador de aplicaciones |
| `picom` | compositor (transparencias, blur, animaciones) |
| `dunst` | notificaciones |
| `flameshot` | capturas de pantalla |
| `xrandr` | configuracion de monitores |


<img width="1920" height="1073" alt="image" src="https://github.com/user-attachments/assets/83114646-089d-4908-ab6f-320e6c065876" />
