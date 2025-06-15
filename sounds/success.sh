#!/bin/bash
# Success sound generator - Pleasant notification

if command -v sox >/dev/null 2>&1; then
    # Generate a pleasant success melody (C major chord progression)
    sox -n -t wav - synth 0.15 sine 523.25 vol 0.4 : \
        synth 0.15 sine 659.25 vol 0.4 : \
        synth 0.25 sine 783.99 vol 0.5 | \
    aplay - 2>/dev/null
elif command -v paplay >/dev/null 2>&1; then
    # Try system notification sounds first
    paplay /usr/share/sounds/freedesktop/stereo/complete.oga 2>/dev/null || \
    paplay /usr/share/sounds/ubuntu/stereo/dialog-information.ogg 2>/dev/null || \
    echo -e "\a\a\a"
elif command -v aplay >/dev/null 2>&1; then
    # Try ALSA sounds
    aplay /usr/share/sounds/alsa/Front_Left.wav 2>/dev/null || \
    echo -e "\a\a\a"
else
    # Fallback: pleasant terminal bell sequence
    echo -e "\a"
    sleep 0.1
    echo -e "\a"
    sleep 0.1
    echo -e "\a"
fi
