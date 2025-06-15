#!/bin/bash
# Error sound generator - Warning tone

if command -v sox >/dev/null 2>&1; then
    # Generate a warning/error sound (descending tone)
    sox -n -t wav - synth 0.2 sine 400 vol 0.6 : \
        synth 0.3 sine 300 vol 0.7 | \
    aplay - 2>/dev/null
elif command -v paplay >/dev/null 2>&1; then
    # Try system error sounds
    paplay /usr/share/sounds/freedesktop/stereo/dialog-error.oga 2>/dev/null || \
    paplay /usr/share/sounds/ubuntu/stereo/dialog-error.ogg 2>/dev/null || \
    echo -e "\a\a\a\a"
elif command -v aplay >/dev/null 2>&1; then
    # Try ALSA error sounds
    aplay /usr/share/sounds/alsa/Front_Right.wav 2>/dev/null || \
    echo -e "\a\a\a\a"
else
    # Fallback: rapid error bells
    echo -e "\a\a\a\a"
fi
