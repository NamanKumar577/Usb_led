savedcmd_blink.mod := printf '%s\n'   blink.o | awk '!x[$$0]++ { print("./"$$0) }' > blink.mod
