# Bootloader
#     This definition is optional, and if your keyboard supports multiple bootloaders of
#     different sizes, comment this out, and the correct address will be loaded
#     automatically (+60). See bootloader.mk for all options.
BOOTLOADER = qmk-dfu

RGBLIGHT_ENABLE = yes

BOOTMAGIC_ENABLE = yes       # Virtual DIP switch configuration(+1000)
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
#TAP_DANCE_ENABLE = yes       # Enable tap-dance
UNICODE_ENABLE = yes         # Unicode

KEY_OVERRIDE_ENABLE = yes
