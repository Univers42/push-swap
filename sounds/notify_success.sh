#!/bin/bash
# Desktop notification for success

if command -v notify-send >/dev/null 2>&1; then
    notify-send "✅ Push Swap" "Compilation completed successfully!" \
        --icon=emblem-default \
        --urgency=normal \
        --expire-time=3000
fi

# Play success sound
if [ -f "sounds/success.sh" ]; then
    ./sounds/success.sh
fi
